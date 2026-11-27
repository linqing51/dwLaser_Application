import test from 'node:test';
import assert from 'node:assert/strict';
import { initialState, reducer, archiveError, DEVICES } from '../lib/demo-model.mjs';
const run = (s, ...actions) => actions.reduce(reducer, s);
const select = s => run(s, { type: 'PATIENT' }, { type: 'SELECT', id: 'AR 0001' });
const treat = s => run(s, { type: 'START' }, { type: 'PEDAL', down: true }, { type: 'TICK', dt: 2 },
  { type: 'STOP', timestamp: '2026-11-12T06:30:00.000Z' }, { type: 'SHOW_REVIEW' });
const save = s => run(treat(select(s)), { type: 'SAVE' }, { type: 'BACK' });
const transfer = s => run(s, { type: 'PATIENT' }, { type: 'TRANSFER' });
const exported = s => run(transfer(s), { type: 'REQUEST_EXPORT' }, { type: 'CONFIRM_EXPORT' });
const imported = s => run(transfer(s), { type: 'REQUEST_IMPORT' }, { type: 'CONFIRM_IMPORT' });

test('exports are independent backups and require explicit confirmation', () => {
  const s = save(initialState());
  const requested = run(transfer(s), { type: 'REQUEST_EXPORT' });
  assert.equal(requested.volumes.A, null);
  assert.equal(requested.transferConfirm, 'export');
  assert.equal(reducer(requested, { type: 'CANCEL_TRANSFER' }).volumes.A, null);
  assert.equal(reducer(transfer(s), { type: 'CONFIRM_EXPORT' }).volumes.A, null);
  const copied = reducer(requested, { type: 'CONFIRM_EXPORT' });
  assert.deepEqual(copied.volumes.A, s.deviceArchives.A);
  assert.notEqual(copied.volumes.A, copied.deviceArchives.A);
  assert.notEqual(copied.volumes.A.patients, copied.patients);
  assert.equal(copied.patients.length, 0);
  assert.equal(copied.deviceArchives.A.patients.length, 0);
  assert.equal(copied.nextPatientNumber, s.nextPatientNumber);
  const changed = run(copied, { type: 'REQUEST_IMPORT' }, { type: 'CONFIRM_IMPORT' }, { type: 'BACK' }, { type: 'EDIT_PATIENT', id: 'AR 0001' },
    { type: 'FORM', key: 'name', value: 'Changed Name' }, { type: 'SAVE' });
  assert.equal(changed.volumes.A.patients[0].name, 'Jhon Smith');
  assert.equal(changed.patients[0].name, 'Changed Name');
});

test('import replaces rather than merges only after confirmation; all identities and sources survive', () => {
  const source = exported(save(initialState()));
  const destination = transfer(reducer(source, { type: 'DEVICE', id: 'B' }));
  const requested = reducer(destination, { type: 'REQUEST_IMPORT' });
  assert.equal(requested.transferConfirm, 'import');
  assert.equal(requested.patients[0].name, 'Morgan Lee');
  assert.equal(requested.deviceArchives, source.deviceArchives);
  const canceled = reducer(requested, { type: 'CANCEL_TRANSFER' });
  assert.equal(canceled.deviceArchives, source.deviceArchives);
  assert.equal(reducer(canceled, { type: 'CONFIRM_IMPORT' }), canceled);
  const restored = reducer(requested, { type: 'CONFIRM_IMPORT' });
  assert.deepEqual(restored.patients, source.volumes.A.patients);
  assert.equal(restored.patients.length, source.volumes.A.patients.length);
  assert.notEqual(restored.patients, source.volumes.A.patients);
  assert.equal(restored.selectedId, null);
  assert.equal(restored.formPatientId, null);
  assert.equal(restored.deviceArchives.A, source.deviceArchives.A);
  assert.equal(restored.volumes, source.volumes);
  assert.equal(restored.patients[0].records[0].sourceDevice.serial, 'S2-A001');
});

test('A to B to C transfers preserve IDs while new treatment sources reflect each device', () => {
  let s = save(initialState());
  const uid = s.patients[0].uid;
  for (const id of ['B', 'C']) {
    s = exported(s);
    s = imported(reducer(s, { type: 'DEVICE', id }));
    s = run(s, { type: 'BACK' }, { type: 'BACK' });
    s = save(s);
    assert.equal(s.patients[0].uid, uid);
    assert.equal(s.patients[0].id, 'AR 0001');
  }
  assert.deepEqual(s.patients[0].records.map(r => r.sourceDevice), Object.values(DEVICES));
  assert.equal(new Set(s.patients[0].records.map(r => r.uid)).size, 3);
  assert.equal(s.deviceArchives.A.patients.length, 0);
  assert.equal(s.deviceArchives.B.patients.length, 0);
});

test('treatment, transition and review block device changes; pending review blocks import but allows backup', () => {
  const surgery = run(select(initialState()), { type: 'START' }, { type: 'PEDAL', down: true }, { type: 'TICK', dt: 1 });
  const transition = reducer(surgery, { type: 'STOP' });
  const review = reducer(transition, { type: 'SHOW_REVIEW' });
  for (const s of [surgery, transition, review]) assert.equal(reducer(s, { type: 'DEVICE', id: 'B' }), s);
  const transferring = run(review, { type: 'PICK' }, { type: 'TRANSFER' });
  assert.equal(reducer(transferring, { type: 'REQUEST_IMPORT' }), transferring);
  assert.equal(reducer({ ...transferring, transferConfirm: 'import' }, { type: 'CONFIRM_IMPORT' }).pending, review.pending);
  const backup = run(transferring, { type: 'REQUEST_EXPORT' }, { type: 'CONFIRM_EXPORT' });
  assert.equal(backup.pending, review.pending);
  assert.equal(backup.volumes.A.patients[0].records.length, 0);
  assert.equal(backup.selectedId, null);
  assert.equal(backup.formPatientId, null);
  assert.equal(backup.patients.length, 0);
  const saved = run(backup, { type: 'BACK' }, { type: 'BACK' }, { type: 'FORM', key: 'name', value: 'New Patient' }, { type: 'SAVE' });
  assert.equal(saved.view, 'success');
  assert.equal(saved.patients[0].records.length, 1);
  assert.equal(saved.volumes.A.patients[0].records.length, 0);
});

test('USB removal and swapping cancel transfer confirmation and cannot target another drive', () => {
  for (const id of [null, 'B']) {
    const ready = run(transfer(initialState()), { type: 'REQUEST_EXPORT' });
    const changed = reducer(ready, { type: 'USB_DRIVE', id });
    assert.equal(changed.transferConfirm, null);
    assert.equal(reducer(changed, { type: 'CONFIRM_EXPORT' }), changed);
    assert.equal(changed.volumes, ready.volumes);
    assert.equal(changed.deviceArchives, ready.deviceArchives);
  }
  const backed = exported(initialState());
  const importing = run(reducer(backed, { type: 'DEVICE', id: 'B' }), { type: 'PATIENT' }, { type: 'TRANSFER' }, { type: 'REQUEST_IMPORT' });
  const removed = reducer(importing, { type: 'USB_DRIVE', id: null });
  assert.equal(removed.transferConfirm, null);
  assert.equal(reducer(removed, { type: 'CONFIRM_IMPORT' }).deviceArchives, importing.deviceArchives);
});

test('missing, empty or incompatible USB blocks transfers without blocking local patient operations', () => {
  const initial = initialState();
  assert.match(reducer(transfer(initial), { type: 'REQUEST_IMPORT' }).error, /No patient backup/);
  const absent = reducer(initial, { type: 'USB_DRIVE', id: null });
  for (const type of ['REQUEST_IMPORT', 'REQUEST_EXPORT'])
    assert.match(reducer(transfer(absent), { type }).error, /USB drive not detected/);
  const backed = exported(initial);
  const unsupported = reducer(backed, { type: 'USB_VERSION', value: 2 });
  for (const type of ['REQUEST_IMPORT', 'REQUEST_EXPORT']) {
    const denied = reducer(unsupported, { type });
    assert.equal(denied.transferConfirm, null);
    assert.match(denied.error, /version not supported/);
    assert.equal(denied.deviceArchives, backed.deviceArchives);
    assert.equal(denied.volumes, unsupported.volumes);
  }
  const main = run(unsupported, { type: 'BACK' }, { type: 'NEW' }, { type: 'FORM', key: 'name', value: 'New Patient' }, { type: 'SAVE' });
  assert.equal(save(main).view, 'main');
  assert.equal(run(treat(main), { type: 'SAVE' }).patients[0].records.length, 1);
});

test('failed export retains the prior USB backup and can retry; failed import retains destination data', () => {
  const backed = exported(initialState());
  const prepared = run(backed, { type: 'USB_WRITE_ERROR', value: true }, { type: 'REQUEST_EXPORT' });
  const failed = reducer(prepared, { type: 'CONFIRM_EXPORT' });
  assert.match(failed.error, /Unable to write to USB/);
  assert.equal(failed.volumes, prepared.volumes);
  assert.equal(failed.deviceArchives, prepared.deviceArchives);
  const retry = run(failed, { type: 'USB_WRITE_ERROR', value: false }, { type: 'REQUEST_EXPORT' }, { type: 'CONFIRM_EXPORT' });
  assert.equal(retry.error, '');
  const destination = transfer(reducer(retry, { type: 'DEVICE', id: 'B' }));
  const importFailed = run(destination, { type: 'DEVICE_WRITE_ERROR', value: true }, { type: 'REQUEST_IMPORT' }, { type: 'CONFIRM_IMPORT' });
  assert.match(importFailed.error, /Unable to save changes/);
  assert.equal(importFailed.deviceArchives, destination.deviceArchives);
  assert.equal(importFailed.volumes, destination.volumes);
  const importRetry = run(importFailed, { type: 'DEVICE_WRITE_ERROR', value: false }, { type: 'REQUEST_IMPORT' }, { type: 'CONFIRM_IMPORT' });
  assert.equal(importRetry.error, '');
  assert.deepEqual(importRetry.patients, backed.patients);
});

test('invalid and over-limit imports are rejected atomically, with no truncation or silent merging', () => {
  const saved = exported(initialState());
  const mutations = [
    a => { a.patients = Array.from({ length: 381 }, () => a.patients[0]); },
    a => { a.patients[0].name = 'A'.repeat(19); },
    a => { a.patients[0].records = Array.from({ length: 11 }, () => a.patients[2].records[0]); },
    a => { a.patients[1].id = a.patients[0].id; },
    a => { a.patients[1].uid = a.patients[0].uid; },
    a => { a.patients[2].records[0].endedAt = 'invalid date'; },
    a => { a.patients[2].records[0].energy = Infinity; },
    a => { a.patients[2].records[1].uid = a.patients[2].records[0].uid; },
    a => { a.nextPatientNumber = 1; },
    a => { a.patients[0].age = '131'; },
  ];
  for (const mutate of mutations) {
    const archive = structuredClone(saved.volumes.A);
    mutate(archive);
    assert.ok(archiveError(archive));
    const ready = { ...saved, volumes: { ...saved.volumes, A: archive } };
    const rejected = run(ready, { type: 'REQUEST_IMPORT' }, { type: 'CONFIRM_IMPORT' });
    assert.equal(rejected.transferConfirm, null);
    assert.equal(rejected.deviceArchives, saved.deviceArchives);
    assert.equal(rejected.patients, saved.patients);
    assert.equal(rejected.volumes.A, archive);
    assert.ok(rejected.error);
  }
});

test('restoring an older backup never lowers the device patient-number counter', () => {
  let s = exported(initialState());
  s = run(s, { type: 'BACK' }, { type: 'NEW' }, { type: 'FORM', key: 'name', value: 'Later Patient' }, { type: 'SAVE' });
  assert.equal(s.nextPatientNumber, 12);
  s = imported(s);
  assert.equal(s.patients.length, 10);
  assert.equal(s.nextPatientNumber, 12);
  assert.equal(s.deviceArchives.A.nextPatientNumber, 12);
  assert.equal(s.volumes.A.nextPatientNumber, 11);
});

test('cross-device equal display IDs are not an instruction to merge different patients', () => {
  const s = initialState();
  assert.equal(s.deviceArchives.A.patients[0].id, s.deviceArchives.B.patients[0].id);
  assert.notEqual(s.deviceArchives.A.patients[0].uid, s.deviceArchives.B.patients[0].uid);
  const source = exported(s);
  const restored = imported(reducer(source, { type: 'DEVICE', id: 'B' }));
  assert.equal(restored.patients[0].uid, source.volumes.A.patients[0].uid);
  assert.ok(!restored.patients.some(p => p.name === 'Morgan Lee'));
});
