import test from 'node:test';
import assert from 'node:assert/strict';
import { initialState, reducer, formatTreatmentDate } from '../lib/demo-model.mjs';
const run = (s, ...actions) => actions.reduce(reducer, s);
const firstEnd = '2026-10-25T15:59:59.000Z';
const secondEnd = '2026-10-26T16:00:01.000Z';
const register = (name = 'Preop Patient', s = initialState()) =>
  run(s, { type: 'PATIENT' }, { type: 'NEW' }, { type: 'FORM', key: 'name', value: name }, { type: 'SAVE' });
const treat = (s, timestamp = firstEnd, seconds = 3) =>
  run(s, { type: 'START' }, { type: 'PEDAL', down: true }, { type: 'TICK', dt: seconds },
    { type: 'STOP', timestamp }, { type: 'SHOW_REVIEW' });
const patient = (s, id = 'AR 0011') => s.patients.find(p => p.id === id);
const savedList = () => run(treat(register()), { type: 'SAVE' }, { type: 'BACK' }, { type: 'PATIENT' });

test('patient registration and treatment save use device storage without USB', () => {
  const initial = reducer(initialState(), { type: 'USB', value: false });
  const registered = register('Offline Patient', initial);
  assert.equal(registered.view, 'main');
  assert.equal(registered.selectedId, 'AR 0011');
  assert.deepEqual(patient(registered).records, []);
  assert.equal(registered.deviceArchives.A.patients, registered.patients);
  assert.equal(registered.volumes, initial.volumes);
  const saved = reducer(treat(registered), { type: 'SAVE' });
  assert.equal(saved.view, 'success');
  assert.equal(patient(saved).records.length, 1);
  assert.equal(saved.volumes, initial.volumes);
});
test('preselected patient is prefilled and Save appends once then clears association', () => {
  const registered = register();
  const review = treat(registered);
  assert.equal(review.form.name, 'Preop Patient');
  assert.equal(review.formPatientId, registered.selectedId);
  const saved = reducer(review, { type: 'SAVE' });
  assert.equal(saved.view, 'success');
  assert.equal(saved.selectedId, null);
  assert.equal(saved.pending, null);
  assert.equal(saved.patients.length, registered.patients.length);
  assert.deepEqual(patient(saved).records, [review.pending]);
  assert.equal(reducer(saved, { type: 'SAVE' }), saved);
});
test('canceling a new registration and zero-output treatment retain the current patient', () => {
  const selected = register();
  const canceled = run(selected, { type: 'PATIENT' }, { type: 'NEW' },
    { type: 'FORM', key: 'name', value: 'Not saved' }, { type: 'BACK' }, { type: 'BACK' });
  assert.equal(canceled.view, 'main');
  assert.equal(canceled.selectedId, selected.selectedId);
  assert.equal(canceled.deviceArchives, selected.deviceArchives);
  const stopped = run(canceled, { type: 'PARAM', key: 'power', value: 31 }, { type: 'START' }, { type: 'STOP' });
  assert.equal(stopped.selectedId, selected.selectedId);
  assert.equal(stopped.pending, null);
  assert.equal(stopped.view, 'main');
  const cleared = run(stopped, { type: 'PATIENT' }, { type: 'UNSELECT' });
  assert.equal(cleared.selectedId, null);
  assert.equal(cleared.deviceArchives, selected.deviceArchives);
});
test('pending treatment blocks Ready, Back and restart until explicit resolution', () => {
  const review = treat(register());
  const attempted = run(review, { type: 'PARAM', key: 'power', value: 70 }, { type: 'START' }, { type: 'BACK' }, { type: 'RESTART' });
  assert.equal(attempted.view, 'edit');
  assert.equal(attempted.pending, review.pending);
  assert.equal(attempted.params.power, review.params.power);
  assert.equal(reducer(attempted, { type: 'DISCARD' }), attempted);
  const discarded = run(attempted, { type: 'REQUEST_DISCARD' }, { type: 'DISCARD' });
  assert.equal(discarded.view, 'main');
  assert.equal(discarded.pending, null);
  assert.equal(discarded.selectedId, null);
  assert.equal(discarded.deviceArchives, review.deviceArchives);
  assert.equal(reducer(discarded, { type: 'START' }).view, 'surgery');
});
test('USB removal never changes selected patient, open history data or review inputs', () => {
  const registered = register();
  const list = run(registered, { type: 'PATIENT' }, { type: 'USB_DRIVE', id: null });
  assert.equal(list.view, 'list');
  assert.equal(list.patients, registered.patients);
  assert.equal(list.selectedId, registered.selectedId);
  const review = treat(registered);
  const changed = run(review, { type: 'USB_DRIVE', id: null }, { type: 'USB_DRIVE', id: 'B' });
  assert.equal(changed.view, 'edit');
  assert.equal(changed.selectedId, review.selectedId);
  assert.equal(changed.form, review.form);
  assert.equal(changed.pending, review.pending);
  assert.equal(changed.deviceArchives, review.deviceArchives);
  assert.equal(reducer(changed, { type: 'SAVE' }).view, 'success');
});
test('changing a review patient updates header and form without writing the record', () => {
  const review = treat(register());
  const changed = run(review, { type: 'PICK' }, { type: 'SELECT', id: 'AR 0009' });
  assert.equal(changed.formPatientId, 'AR 0009');
  assert.equal(changed.selectedId, 'AR 0009');
  assert.equal(changed.form.age, '60');
  assert.equal(changed.deviceArchives, review.deviceArchives);
  assert.equal(changed.pending, review.pending);
  const saved = reducer(changed, { type: 'SAVE' });
  assert.equal(patient(saved, 'AR 0009').records.length, 1);
  assert.equal(patient(saved).records.length, 0);
});
test('pre-registration duplicate choices return to confirmation before device write', () => {
  const duplicate = register(' JHON SMITH ');
  assert.equal(duplicate.view, 'duplicates');
  const existing = reducer(duplicate, { type: 'CHOOSE', id: 'AR 0009' });
  assert.equal(existing.view, 'edit');
  assert.equal(existing.formPatientId, 'AR 0009');
  assert.equal(existing.deviceArchives, duplicate.deviceArchives);
  const selected = reducer(existing, { type: 'SAVE' });
  assert.equal(selected.view, 'main');
  assert.equal(selected.selectedId, 'AR 0009');
  assert.equal(selected.patients.length, 10);
  assert.deepEqual(patient(selected, 'AR 0009').records, []);
  const fresh = reducer(duplicate, { type: 'CHOOSE', id: null });
  assert.equal(fresh.view, 'edit');
  assert.equal(fresh.deviceArchives, duplicate.deviceArchives);
  const created = reducer(fresh, { type: 'SAVE' });
  assert.equal(created.view, 'main');
  assert.equal(created.patients.length, 11);
  assert.equal(patient(created).name, 'JHON SMITH');
  assert.deepEqual(patient(created).records, []);
});
test('new demo sessions reset data and never restore unfinished treatment or patient selection', () => {
  const saved = savedList();
  const review = treat(run(saved, { type: 'SELECT', id: 'AR 0011' }));
  assert.ok(review.pending);
  const fresh = initialState();
  assert.equal(fresh.pending, null);
  assert.equal(fresh.selectedId, null);
  assert.equal(fresh.view, 'main');
  assert.equal(patient(fresh), undefined);
  assert.equal(fresh.deviceArchives.A.patients.length, 10);
  assert.notEqual(fresh.deviceArchives, review.deviceArchives);
});
test('device restart preserves simulated device contents but clears device state', () => {
  const saved = savedList();
  const selected = reducer(saved, { type: 'SELECT', id: 'AR 0011' });
  const restarted = reducer(selected, { type: 'RESTART' });
  assert.equal(restarted.view, 'main');
  assert.equal(restarted.deviceArchives, selected.deviceArchives);
  assert.equal(patient(restarted).records.length, 1);
  assert.equal(restarted.selectedId, null);
  assert.equal(restarted.pending, null);
  assert.equal(restarted.showPatientHint, true);
  const absent = run(selected, { type: 'USB_DRIVE', id: null }, { type: 'RESTART' });
  assert.equal(absent.usb, false);
  assert.equal(absent.patients, selected.patients);
  assert.equal(absent.deviceArchives, selected.deviceArchives);
});
test('devices keep independent archives even when the same USB is connected', () => {
  const original = register();
  const changed = reducer(original, { type: 'DEVICE', id: 'B' });
  assert.equal(changed.selectedId, null);
  assert.equal(changed.patients.length, 1);
  assert.equal(changed.patients[0].name, 'Morgan Lee');
  const changedUsb = reducer(changed, { type: 'USB_DRIVE', id: 'B' });
  assert.equal(changedUsb.patients, changed.patients);
  const restored = reducer(changedUsb, { type: 'DEVICE', id: 'A' });
  assert.equal(restored.patients, original.patients);
  assert.equal(restored.selectedId, null);
});
test('connecting or swapping a USB does not import patients automatically', () => {
  const original = initialState();
  const changed = run(original, { type: 'USB_DRIVE', id: 'B' }, { type: 'USB_DRIVE', id: 'A' });
  assert.equal(changed.patients, original.patients);
  assert.equal(changed.deviceArchives, original.deviceArchives);
  assert.equal(changed.selectedId, null);
});
test('patient deletion removes its records, preserves other data and never reuses an ID', () => {
  const saved = savedList();
  const deleted = reducer(saved, { type: 'DELETE_PATIENT', id: 'AR 0011' });
  assert.equal(patient(deleted), undefined);
  assert.deepEqual(deleted.patients, saved.patients.slice(0, -1));
  assert.equal(deleted.deviceArchives.B, saved.deviceArchives.B);
  const remounted = run(deleted, { type: 'USB_DRIVE', id: 'B' }, { type: 'USB_DRIVE', id: 'A' }, { type: 'BACK' }, { type: 'RESTART' });
  assert.equal(patient(remounted), undefined);
  assert.equal(remounted.nextPatientNumber, 12);
  const next = register('Next Patient', remounted);
  assert.equal(next.selectedId, 'AR 0012');
});
test('each Standby ends one treatment; deleting one record retains the other', () => {
  let s = savedList();
  s = reducer(s, { type: 'SELECT', id: 'AR 0011' });
  const second = treat(s, secondEnd, 5);
  assert.equal(second.pending.seconds, 5);
  s = run(second, { type: 'SAVE' }, { type: 'BACK' }, { type: 'PATIENT' });
  assert.deepEqual(patient(s).records.map(r => r.endedAt), [firstEnd, secondEnd]);
  assert.deepEqual(patient(s).records.map(r => r.seconds), [3, 5]);
  const deleted = reducer(s, { type: 'DELETE_RECORD', id: 'AR 0011', index: 1 });
  assert.equal(deleted.patients.length, s.patients.length);
  assert.deepEqual(patient(deleted).records, [patient(s).records[0]]);
  assert.equal(patient(deleted).date, formatTreatmentDate(firstEnd));
  const empty = reducer(deleted, { type: 'DELETE_RECORD', id: 'AR 0011', index: 0 });
  assert.deepEqual(patient(empty).records, []);
  assert.equal(patient(empty).date, '');
  assert.equal(patient(reducer(empty, { type: 'RESTART' })).records.length, 0);
});
test('pending review permits old-record deletion without discarding the pending snapshot', () => {
  const saved = savedList();
  const picker = run(treat(run(saved, { type: 'SELECT', id: 'AR 0011' })), { type: 'PICK' });
  for (const action of [
    { type: 'EDIT_PATIENT', id: 'AR 0011' },
    { type: 'UNSELECT' },
  ]) assert.equal(reducer(picker, action), picker);
  const deleted = reducer(picker, { type: 'DELETE_RECORD', id: 'AR 0011', index: 0 });
  assert.equal(patient(deleted).records.length, 0);
  assert.equal(deleted.pending, picker.pending);
  assert.equal(deleted.formPatientId, 'AR 0011');
  const savedAgain = run(deleted, { type: 'BACK' }, { type: 'SAVE' });
  assert.equal(savedAgain.view, 'success');
  assert.equal(patient(savedAgain).records.length, 1);
  assert.deepEqual(patient(savedAgain).records[0], picker.pending);
  for (const index of [-1, 100, 0.5, undefined])
    assert.equal(reducer(saved, { type: 'DELETE_RECORD', id: 'AR 0011', index }), saved);
  assert.equal(reducer(saved, { type: 'DELETE_PATIENT', id: 'missing' }), saved);
});
test('deleting the selected patient clears the association and form after device write succeeds', () => {
  const ready = run(savedList(), { type: 'SELECT', id: 'AR 0011' }, { type: 'PATIENT' },
    { type: 'TRANSFER' }, { type: 'REQUEST_EXPORT' }, { type: 'CONFIRM_EXPORT' },
    { type: 'REQUEST_IMPORT' }, { type: 'CONFIRM_IMPORT' }, { type: 'BACK' }, { type: 'SELECT', id: 'AR 0011' }, { type: 'PATIENT' });
  assert.equal(ready.selectedId, 'AR 0011');
  const deleted = reducer(ready, { type: 'DELETE_PATIENT', id: 'AR 0011' });
  assert.equal(deleted.view, 'list');
  assert.equal(patient(deleted), undefined);
  assert.equal(deleted.selectedId, null);
  assert.equal(deleted.formPatientId, null);
  assert.equal(deleted.form.name, '');
  assert.equal(deleted.form.id, 'AR 0012');
  assert.equal(deleted.nextPatientNumber, ready.nextPatientNumber);
  assert.deepEqual(deleted.patients, ready.patients.filter(p => p.id !== 'AR 0011'));
  assert.equal(deleted.deviceArchives.B, ready.deviceArchives.B);
  assert.equal(deleted.volumes, ready.volumes);
  assert.equal(deleted.volumes.A.patients.find(p => p.id === 'AR 0011').records.length, 1);
  const main = reducer(deleted, { type: 'BACK' });
  assert.equal(main.view, 'main');
  assert.equal(main.selectedId, null);
});
test('deleting the review patient retains the unsaved treatment and requires an explicit new patient choice', () => {
  const ready = run(treat(run(savedList(), { type: 'SELECT', id: 'AR 0011' })), { type: 'PICK' });
  const deleted = reducer(ready, { type: 'DELETE_PATIENT', id: 'AR 0011' });
  assert.equal(deleted.view, 'edit');
  assert.equal(deleted.pending, ready.pending);
  assert.equal(deleted.selectedId, null);
  assert.equal(deleted.formPatientId, null);
  assert.equal(deleted.form.name, '');
  assert.equal(deleted.newPatientConfirmed, false);
  const attempted = run(deleted, { type: 'SAVE' }, { type: 'START' }, { type: 'RESTART' });
  assert.equal(attempted.view, 'edit');
  assert.match(attempted.error, /name is required/);
  assert.equal(attempted.pending, ready.pending);
  assert.equal(attempted.deviceArchives, deleted.deviceArchives);
  assert.equal(patient(attempted), undefined);
  const reassigned = run(deleted, { type: 'PICK' }, { type: 'SELECT', id: 'AR 0009' }, { type: 'SAVE' });
  assert.equal(reassigned.view, 'success');
  assert.deepEqual(patient(reassigned, 'AR 0009').records, [ready.pending]);
  assert.equal(patient(reassigned), undefined);
  const registered = run(deleted, { type: 'FORM', key: 'name', value: 'Preop Patient' }, { type: 'SAVE' });
  assert.equal(registered.view, 'success');
  assert.equal(patient(registered), undefined);
  const fresh = patient(registered, 'AR 0012');
  assert.notEqual(fresh.uid, patient(ready).uid);
  assert.deepEqual(fresh.records, [ready.pending]);
});
test('deleting another patient keeps the current review identity and unsaved treatment unchanged', () => {
  const ready = run(treat(run(savedList(), { type: 'SELECT', id: 'AR 0011' })), { type: 'PICK' });
  const deleted = reducer(ready, { type: 'DELETE_PATIENT', id: 'AR 0009' });
  assert.equal(deleted.view, 'list');
  assert.equal(deleted.selectedId, ready.selectedId);
  assert.equal(deleted.formPatientId, ready.formPatientId);
  assert.equal(deleted.form, ready.form);
  assert.equal(deleted.pending, ready.pending);
  assert.equal(patient(deleted), patient(ready));
  assert.equal(patient(deleted, 'AR 0009'), undefined);
});
test('failed deletion of a selected patient retains its data and association until a successful retry', () => {
  const saved = savedList();
  const selected = run(saved, { type: 'SELECT', id: 'AR 0011' });
  for (const ready of [reducer(selected, { type: 'PATIENT' }), reducer(treat(selected), { type: 'PICK' })]) {
    const failed = run(ready, { type: 'DEVICE_WRITE_ERROR', value: true }, { type: 'DELETE_PATIENT', id: 'AR 0011' });
    assert.match(failed.error, /Unable to save changes/);
    assert.equal(failed.view, 'list');
    assert.equal(failed.patients, ready.patients);
    assert.equal(failed.deviceArchives, ready.deviceArchives);
    assert.equal(failed.selectedId, ready.selectedId);
    assert.equal(failed.formPatientId, ready.formPatientId);
    assert.equal(failed.form, ready.form);
    assert.equal(failed.pending, ready.pending);
    const retried = run(failed, { type: 'DEVICE_WRITE_ERROR', value: false }, { type: 'DELETE_PATIENT', id: 'AR 0011' });
    assert.equal(retried.selectedId, null);
    assert.equal(retried.formPatientId, null);
    assert.equal(retried.pending, ready.pending);
    assert.equal(patient(retried), undefined);
  }
});
test('patient deletion is available only through the patient list, not during output or review transition', () => {
  const selected = register();
  const surgery = run(selected, { type: 'START' }, { type: 'PEDAL', down: true }, { type: 'TICK', dt: 2 });
  const transition = reducer(surgery, { type: 'STOP' });
  const review = reducer(transition, { type: 'SHOW_REVIEW' });
  for (const state of [selected, surgery, transition, review])
    assert.equal(reducer(state, { type: 'DELETE_PATIENT', id: 'AR 0011' }), state);
});
test('editing demographics updates device storage while preserving patient ID and treatment history', () => {
  const saved = savedList();
  const edited = run(saved, { type: 'EDIT_PATIENT', id: 'AR 0011' },
    { type: 'FORM', key: 'name', value: 'Corrected Name' },
    { type: 'FORM', key: 'age', value: '45' },
    { type: 'FORM', key: 'gender', value: 'Female' });
  assert.equal(edited.deviceArchives, saved.deviceArchives);
  const updated = reducer(edited, { type: 'SAVE' });
  assert.equal(updated.view, 'list');
  assert.equal(patient(updated).name, 'Corrected Name');
  assert.equal(patient(updated).age, '45');
  assert.equal(patient(updated).gender, 'Female');
  assert.equal(patient(updated).id, patient(saved).id);
  assert.equal(patient(updated).records, patient(saved).records);
  assert.equal(updated.nextPatientNumber, saved.nextPatientNumber);
  assert.equal(updated.deviceArchives.A.patients, updated.patients);
  assert.equal(updated.deviceArchives.B, saved.deviceArchives.B);
});
test('startup highlight clears after Patient or Ready and stays clear between treatments', () => {
  const initial = initialState();
  assert.equal(initial.showPatientHint, true);
  const opened = run(initial, { type: 'PATIENT' }, { type: 'BACK' });
  assert.equal(opened.showPatientHint, false);
  assert.equal(opened.selectedId, null);
  const noOutput = run(initial, { type: 'START' }, { type: 'STOP' });
  assert.equal(noOutput.showPatientHint, false);
  const completed = run(treat(initial), { type: 'REQUEST_DISCARD' }, { type: 'DISCARD' });
  assert.equal(completed.showPatientHint, false);
});
test('all unresolved treatment navigation returns to review and discard works without USB', () => {
  const review = treat(register());
  const picker = reducer(review, { type: 'PICK' });
  const newForm = reducer(picker, { type: 'NEW' });
  const confirm = reducer(review, { type: 'REQUEST_DISCARD' });
  for (const state of [review, picker, newForm, confirm]) {
    const back = reducer(state, { type: 'BACK' });
    assert.equal(back.view, 'edit');
    assert.equal(back.pending, review.pending);
  }
  const removed = reducer(review, { type: 'USB', value: false });
  const discarded = run(removed, { type: 'REQUEST_DISCARD' }, { type: 'DISCARD' });
  assert.equal(discarded.view, 'main');
  assert.equal(discarded.pending, null);
  assert.equal(discarded.deviceArchives, review.deviceArchives);
});

for (const [label, prepare, action, verify] of [
  ['pre-registration', () => run(initialState(), { type: 'PATIENT' }, { type: 'NEW' },
    { type: 'FORM', key: 'name', value: 'Retry Registration' }),
    { type: 'SAVE' }, s => { assert.equal(s.view, 'main'); assert.equal(patient(s).name, 'Retry Registration'); }],
  ['treatment save', () => treat(register()), { type: 'SAVE' },
    s => { assert.equal(s.view, 'success'); assert.equal(patient(s).records.length, 1); assert.equal(s.pending, null); }],
  ['patient deletion', savedList, { type: 'DELETE_PATIENT', id: 'AR 0011' },
    s => assert.equal(patient(s), undefined)],
  ['record deletion', savedList, { type: 'DELETE_RECORD', id: 'AR 0011', index: 0 },
    s => assert.deepEqual(patient(s).records, [])],
  ['profile correction', () => run(savedList(), { type: 'EDIT_PATIENT', id: 'AR 0011' },
    { type: 'FORM', key: 'name', value: 'Retry Name' }), { type: 'SAVE' },
    s => { assert.equal(s.view, 'list'); assert.equal(patient(s).name, 'Retry Name'); }],
]) {
  test(`Device write failure leaves ${label} unchanged and allows a successful retry`, () => {
    const ready = prepare();
    const failed = run(ready, { type: 'DEVICE_WRITE_ERROR', value: true }, action);
    assert.match(failed.error, /Unable to save changes to the device/);
    assert.equal(failed.view, ready.view);
    assert.equal(failed.deviceArchives, ready.deviceArchives);
    assert.equal(failed.patients, ready.patients);
    assert.equal(failed.nextPatientNumber, ready.nextPatientNumber);
    assert.equal(failed.pending, ready.pending);
    assert.deepEqual(failed.form, ready.form);
    const retried = run(failed, { type: 'DEVICE_WRITE_ERROR', value: false }, action);
    assert.equal(retried.error, '');
    assert.notEqual(retried.deviceArchives.A, ready.deviceArchives.A);
    assert.equal(retried.deviceArchives.B, ready.deviceArchives.B);
    verify(retried);
  });
}

test('Standby stops output before review transition and no transition action restarts it', () => {
  const firing = run(register(), { type: 'START' }, { type: 'PEDAL', down: true }, { type: 'TICK', dt: 2 });
  assert.equal(firing.firing, true);
  assert.equal(reducer(firing, { type: 'RESTART' }), firing);
  const returned = reducer(firing, { type: 'STOP', timestamp: firstEnd });
  assert.equal(returned.view, 'review-transition');
  assert.equal(returned.firing, false);
  assert.ok(returned.pending);
  const attempted = run(returned, { type: 'PEDAL', down: true }, { type: 'TICK', dt: 5 },
    { type: 'START' }, { type: 'PARAM', key: 'power', value: 90 }, { type: 'BACK' },
    { type: 'PATIENT' }, { type: 'RESTART' }, { type: 'STOP', timestamp: secondEnd });
  assert.equal(attempted.view, 'review-transition');
  assert.equal(attempted.firing, false);
  assert.equal(attempted.seconds, 2);
  assert.equal(attempted.energy, returned.energy);
  assert.equal(attempted.params.power, returned.params.power);
  assert.equal(attempted.pending, returned.pending);
  const reviewed = reducer(attempted, { type: 'SHOW_REVIEW' });
  assert.equal(reviewed.view, 'edit');
  assert.equal(reviewed.firing, false);
  assert.equal(reviewed.pending, returned.pending);
  const triedAgain = run(reviewed, { type: 'PEDAL', down: true }, { type: 'TICK', dt: 10 }, { type: 'START' });
  assert.equal(triedAgain.view, 'edit');
  assert.equal(triedAgain.firing, false);
  assert.equal(triedAgain.seconds, 2);
});

test('canceling either same-name registration choice preserves the original patient', () => {
  const selected = register();
  const duplicate = run(selected, { type: 'PATIENT' }, { type: 'NEW' },
    { type: 'FORM', key: 'name', value: 'Jhon Smith' }, { type: 'SAVE' });
  assert.equal(duplicate.view, 'duplicates');
  for (const id of ['AR 0009', null]) {
    const chosen = reducer(duplicate, { type: 'CHOOSE', id });
    assert.equal(chosen.view, 'edit');
    assert.equal(chosen.selectedId, selected.selectedId);
    assert.equal(chosen.deviceArchives, selected.deviceArchives);
    const canceled = run(chosen, { type: 'BACK' }, { type: 'BACK' });
    assert.equal(canceled.view, 'main');
    assert.equal(canceled.selectedId, selected.selectedId);
    assert.equal(canceled.formPatientId, null);
    assert.equal(canceled.deviceArchives, selected.deviceArchives);
  }
});
test('canceling a profile edit releases the noncurrent patient for deletion', () => {
  const selected = register();
  const edited = run(selected, { type: 'PATIENT' }, { type: 'EDIT_PATIENT', id: 'AR 0009' },
    { type: 'FORM', key: 'name', value: 'Unsaved Correction' });
  const canceled = reducer(edited, { type: 'BACK' });
  assert.equal(canceled.view, 'list');
  assert.equal(canceled.formPatientId, null);
  assert.equal(canceled.deviceArchives, selected.deviceArchives);
  assert.equal(patient(canceled, 'AR 0009').name, 'Jhon Smith');
  const deleted = reducer(canceled, { type: 'DELETE_PATIENT', id: 'AR 0009' });
  assert.equal(patient(deleted, 'AR 0009'), undefined);
  assert.equal(deleted.selectedId, selected.selectedId);
  assert.equal(patient(deleted).name, 'Preop Patient');
});
