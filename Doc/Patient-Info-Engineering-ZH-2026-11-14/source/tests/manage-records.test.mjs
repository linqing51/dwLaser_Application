import test from 'node:test';
import assert from 'node:assert/strict';
import { initialState, reducer } from '../lib/demo-model.mjs';
const run = (s, ...actions) => actions.reduce(reducer, s);
const blockedReview = () => run(initialState(),
  { type: 'PATIENT' }, { type: 'SELECT', id: 'AR 0002' }, { type: 'START' },
  { type: 'PEDAL', down: true }, { type: 'TICK', dt: 2 },
  { type: 'STOP', timestamp: '2026-11-14T06:00:00.000Z' }, { type: 'SHOW_REVIEW' }, { type: 'SAVE' });

test('Manage Records targets the review patient and returns after cleanup without losing the treatment', () => {
  const review = blockedReview();
  const history = reducer(review, { type: 'MANAGE' });
  assert.equal(history.managePatientId, 'AR 0002');
  assert.equal(history.pending, review.pending);
  assert.equal(history.form, review.form);
  const freed = reducer(history, { type: 'DELETE_RECORD', id: history.managePatientId, index: 3 });
  assert.equal(freed.managePatientId, 'AR 0002');
  const back = reducer(freed, { type: 'BACK' });
  assert.equal(back.view, 'edit');
  assert.equal(back.managePatientId, null);
  assert.equal(back.pending, review.pending);
  assert.equal(back.formPatientId, 'AR 0002');
  const saved = reducer(back, { type: 'SAVE' });
  assert.equal(saved.view, 'success');
  assert.deepEqual(saved.patients.find(p => p.id === 'AR 0002').records.at(-1), review.pending);
});

test('history has no USB entry and failed deletion preserves patient history', () => {
  const history = reducer(blockedReview(), { type: 'MANAGE' });
  assert.equal(reducer(history, { type: 'TRANSFER' }), history);
  const failed = run(history, { type: 'DEVICE_WRITE_ERROR', value: true }, { type: 'DELETE_RECORD', id: 'AR 0002', index: 0 });
  assert.equal(failed.patients, history.patients);
  assert.equal(failed.managePatientId, 'AR 0002');
  assert.equal(failed.pending, history.pending);
  assert.match(failed.error, /Unable to save/);
});

test('Change Patient still opens the patient list; managing a new patient has no history target', () => {
  const review = blockedReview();
  assert.equal(reducer(review, { type: 'PICK' }).managePatientId, null);
  const newPatient = run(review, { type: 'PICK' }, { type: 'NEW' }, { type: 'MANAGE' });
  assert.equal(newPatient.view, 'list');
  assert.equal(newPatient.managePatientId, null);
  assert.equal(newPatient.pending, review.pending);
});
