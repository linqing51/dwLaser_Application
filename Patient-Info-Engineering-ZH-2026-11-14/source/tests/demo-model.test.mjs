import test from 'node:test';
import assert from 'node:assert/strict';
import {
  initialState,
  reducer,
  metrics,
  formatTime,
  formatTreatmentDate,
  LIMITS,
  findMatches,
} from '../lib/demo-model.mjs';
const run = (s, ...actions) => actions.reduce(reducer, s);
const endedAt = '2026-09-07T15:59:59.000Z';
const treated = () =>
  run(
    initialState(),
    { type: 'START' },
    { type: 'PEDAL', down: true },
    { type: 'TICK', dt: 65 },
    { type: 'PEDAL', down: false },
    { type: 'STOP', timestamp: endedAt },
    { type: 'SHOW_REVIEW' },
  );
const edit = (name = 'New Patient') =>
  run(treated(), { type: 'FORM', key: 'name', value: name });
test('patient button opens the list and Back returns to main', () => {
  const s = reducer(initialState(), { type: 'PATIENT' });
  assert.equal(s.view, 'list');
  assert.equal(reducer(s, { type: 'BACK' }).view, 'main');
});
test('output accumulates only with pedal held and ends in a fixed snapshot', () => {
  let s = run(initialState(), { type: 'START' }, { type: 'TICK', dt: 10 });
  assert.equal(s.seconds, 0);
  s = run(
    s,
    { type: 'PEDAL', down: true },
    { type: 'TICK', dt: 2 },
    { type: 'PEDAL', down: false },
    { type: 'TICK', dt: 10 },
    { type: 'STOP', timestamp: endedAt },
  );
  assert.equal(s.seconds, 2);
  assert.equal(s.energy, ((30 * 600) / 1300) * 2);
  assert.equal(s.pending.seconds, 2);
  assert.equal(s.pending.power, 30);
  assert.equal(s.pending.endedAt, endedAt);
  assert.equal(s.firing, false);
  assert.equal(s.view, 'review-transition');
  assert.equal(reducer(s, { type: 'SHOW_REVIEW' }).view, 'edit');
});
test('no-output session ends without a treatment record', () => {
  const s = run(initialState(), { type: 'START' }, { type: 'STOP' });
  assert.equal(s.view, 'main');
  assert.equal(s.pending, null);
  assert.equal(s.firing, false);
});
test('warning blocks entering Ready and stops firing', () => {
  let s = run(
    initialState(),
    { type: 'WARNING', value: true },
    { type: 'START' },
    { type: 'PEDAL', down: true },
    { type: 'TICK', dt: 5 },
  );
  assert.equal(s.view, 'main');
  assert.equal(s.seconds, 0);
  s = run(
    initialState(),
    { type: 'START' },
    { type: 'PEDAL', down: true },
    { type: 'TICK', dt: 1 },
    { type: 'WARNING', value: true },
    { type: 'TICK', dt: 5 },
  );
  assert.equal(s.firing, false);
  assert.equal(s.seconds, 1);
});
test('parameter edits cannot change the pending treatment snapshot', () => {
  const s = treated();
  const next = reducer(s, { type: 'PARAM', key: 'power', value: 77 });
  assert.equal(next.pending, s.pending);
  assert.equal(next.params.power, 30);
});
test('parameters are bounded on main and locked during treatment', () => {
  for (const [key, [min, max]] of Object.entries(LIMITS)) {
    assert.equal(reducer(initialState(), { type: 'PARAM', key, value: -999 }).params[key], min);
    assert.equal(reducer(initialState(), { type: 'PARAM', key, value: 999999 }).params[key], max);
  }
  const surgery = reducer(initialState(), { type: 'START' });
  assert.equal(reducer(surgery, { type: 'PARAM', key: 'power', value: 77 }), surgery);
});
test('CW and pulsed values follow one formula', () => {
  assert.equal(metrics({ ...initialState().params, mode: 'CW' }).average, 30);
  assert.equal(metrics({ ...initialState().params, mode: 'CW' }).frequency, null);
  assert.equal(metrics(initialState().params).frequency, 1000 / 1300);
  assert.equal(formatTime(485), '08:05');
});
test('name is required while gender and age are optional', () => {
  const missing = reducer(edit('  '), { type: 'SAVE' });
  assert.equal(missing.view, 'edit');
  assert.match(missing.error, /required/);
  const saved = reducer(edit(), { type: 'SAVE' });
  assert.equal(saved.view, 'success');
  assert.equal(saved.patients.at(-1).gender, '');
  assert.equal(saved.patients.at(-1).age, '');
});
test('invalid age cannot save or change device data', () => {
  for (const age of ['-1', '131', '1.2', 'abc']) {
    const before = run(edit(), { type: 'FORM', key: 'age', value: age });
    const s = reducer(before, { type: 'SAVE' });
    assert.equal(s.view, 'edit');
    assert.ok(s.error);
    assert.equal(s.deviceArchives, before.deviceArchives);
  }
});
test('Back cannot bypass mandatory review and preserves the snapshot', () => {
  const s = edit();
  const next = reducer(s, { type: 'BACK' });
  assert.equal(next.view, 'edit');
  assert.equal(next.pending, s.pending);
});
test('device storage failure retains patients, unsaved review inputs and snapshot for retry', () => {
  const before = run(edit(), { type: 'FORM', key: 'gender', value: 'Female' }, { type: 'FORM', key: 'age', value: '25' });
  const failed = run(before, { type: 'DEVICE_WRITE_ERROR', value: true }, { type: 'SAVE' });
  assert.equal(failed.view, 'edit');
  assert.match(failed.error, /Unable to save changes to the device/);
  assert.equal(failed.pending, before.pending);
  assert.deepEqual(failed.form, before.form);
  assert.equal(failed.patients, before.patients);
  assert.equal(failed.deviceArchives, before.deviceArchives);
  const saved = run(failed, { type: 'DEVICE_WRITE_ERROR', value: false }, { type: 'SAVE' });
  assert.equal(saved.view, 'success');
  assert.equal(saved.patients.at(-1).name, before.form.name);
  assert.equal(saved.patients.at(-1).age, '25');
});
test('save writes the complete snapshot to device and uses treatment end time', () => {
  const before = edit('Patient 新');
  const saved = reducer(before, { type: 'SAVE', date: '2099-12-31' });
  assert.equal(saved.view, 'success');
  assert.equal(saved.pending, null);
  assert.equal(saved.patients.length, before.patients.length + 1);
  assert.equal(saved.patients.at(-1).name, 'Patient 新');
  assert.deepEqual(saved.patients.at(-1).records[0], before.pending);
  assert.equal(saved.patients.at(-1).date, formatTreatmentDate(endedAt));
  assert.equal(saved.deviceArchives.A.patients, saved.patients);
  assert.equal(saved.deviceArchives.B, before.deviceArchives.B);
  assert.equal(run(saved, { type: 'BACK' }, { type: 'PATIENT' }).view, 'list');
});
test('case-insensitive exact names trigger duplicate selection', () => {
  const s = reducer(edit(' JHON SMITH '), { type: 'SAVE' });
  assert.equal(s.view, 'duplicates');
  assert.equal(findMatches(s.patients, s.form.name).length, 2);
});
test('choosing a duplicate previews demographics and requires final Save', () => {
  const before = edit('Jhon Smith');
  const chosen = run(before, { type: 'SAVE' }, { type: 'CHOOSE', id: 'AR 0009' });
  assert.equal(chosen.view, 'edit');
  assert.equal(chosen.selectedId, 'AR 0009');
  assert.equal(chosen.form.age, '60');
  assert.equal(chosen.pending, before.pending);
  assert.equal(chosen.deviceArchives, before.deviceArchives);
  const saved = reducer(chosen, { type: 'SAVE' });
  assert.equal(saved.view, 'success');
  assert.equal(saved.patients.length, before.patients.length);
  assert.equal(saved.patients.find(p => p.id === 'AR 0009').records.length, 1);
  assert.equal(saved.pending, null);
});
test('confirmed new duplicate name saves once without repeating the duplicate prompt', () => {
  const before = edit('Jhon Smith');
  const chosen = run(before, { type: 'SAVE' }, { type: 'CHOOSE', id: null });
  assert.equal(chosen.view, 'edit');
  assert.equal(chosen.newPatientConfirmed, true);
  assert.equal(chosen.deviceArchives, before.deviceArchives);
  const saved = reducer(chosen, { type: 'SAVE' });
  assert.equal(saved.view, 'success');
  assert.equal(saved.patients.at(-1).id, 'AR 0011');
  assert.equal(new Set(saved.patients.map(p => p.id)).size, saved.patients.length);
  assert.equal(saved.patients.length, before.patients.length + 1);
});
test('USB removal during duplicate selection leaves device patient choices available', () => {
  const before = reducer(edit('Jhon Smith'), { type: 'SAVE' });
  const chosen = run(before, { type: 'USB', value: false }, { type: 'CHOOSE', id: 'AR 0001' });
  assert.equal(chosen.view, 'edit');
  assert.equal(chosen.formPatientId, 'AR 0001');
  assert.equal(chosen.pending, before.pending);
  assert.equal(chosen.patients, before.patients);
  assert.equal(chosen.deviceArchives, before.deviceArchives);
  assert.equal(reducer(chosen, { type: 'SAVE' }).view, 'success');
});
test('repeat Save and invalid duplicate selection cannot append records', () => {
  const saved = reducer(edit(), { type: 'SAVE' });
  assert.equal(reducer(saved, { type: 'SAVE' }), saved);
  const duplicate = reducer(edit('Jhon Smith'), { type: 'SAVE' });
  assert.equal(reducer(duplicate, { type: 'CHOOSE', id: 'AR 0002' }), duplicate);
});
