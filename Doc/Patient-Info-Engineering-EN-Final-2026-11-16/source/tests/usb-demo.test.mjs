import test from 'node:test';
import assert from 'node:assert/strict';
import { initialState, reducer, archiveError } from '../lib/demo-model.mjs';
const run = (s, ...actions) => actions.reduce(reducer, s);
test('USB B starts with two patients and two records; confirmed import replaces all original patients', () => {
  const initial = initialState();
  const backup = initial.volumes.B;
  assert.equal(archiveError(backup), '');
  assert.equal(backup.patients.length, 2);
  assert.deepEqual(backup.patients.map(p => p.records.length), [1, 1]);
  const ready = run(initial, { type: 'USB_DRIVE', id: 'B' }, { type: 'PATIENT' }, { type: 'TRANSFER' }, { type: 'REQUEST_IMPORT' });
  assert.equal(ready.patients, initial.patients);
  assert.equal(reducer(ready, { type: 'CANCEL_TRANSFER' }).patients, initial.patients);
  const imported = reducer(ready, { type: 'CONFIRM_IMPORT' });
  assert.deepEqual(imported.patients, backup.patients);
  assert.ok(!imported.patients.some(p => initial.patients.some(old => old.uid === p.uid)));
  assert.equal(imported.nextPatientNumber, initial.nextPatientNumber);
});
test('export failures retain device records and USB; successful retry clears only the active device', () => {
  for (const failure of ['USB_WRITE_ERROR', 'DEVICE_WRITE_ERROR']) {
    const initial = initialState();
    const ready = run(initial, { type: 'PATIENT' }, { type: 'TRANSFER' }, { type: failure, value: true }, { type: 'REQUEST_EXPORT' });
    const failed = reducer(ready, { type: 'CONFIRM_EXPORT' });
    assert.equal(failed.patients, initial.patients);
    assert.equal(failed.deviceArchives, initial.deviceArchives);
    assert.equal(failed.volumes, initial.volumes);
    const saved = run(failed, { type: failure, value: false }, { type: 'REQUEST_EXPORT' }, { type: 'CONFIRM_EXPORT' });
    assert.deepEqual(saved.volumes.A, initial.deviceArchives.A);
    assert.deepEqual(saved.patients, []);
    assert.equal(saved.deviceArchives.B, initial.deviceArchives.B);
    assert.equal(saved.volumes.B, initial.volumes.B);
    assert.equal(saved.nextPatientNumber, initial.nextPatientNumber);
  }
});
