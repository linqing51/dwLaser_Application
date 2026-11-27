import test from 'node:test';
import assert from 'node:assert/strict';
import { initialState, reducer, LIMITS } from '../lib/demo-model.mjs';

test('first parameter interaction dismisses the startup hint for every parameter', () => {
  for (const [key, value] of Object.entries({ power: 31, on: 610, off: 710, aim: 90, mode: 'CW' })) {
    const initial = initialState();
    const changed = reducer(initial, { type: 'PARAM', key, value });
    assert.equal(changed.showPatientHint, false, key);
    assert.equal(changed.params[key], value);
    assert.equal(changed.deviceArchives, initial.deviceArchives);
    assert.equal(changed.view, 'main');
  }
});

test('same mode, same value and boundary controls also dismiss the hint', () => {
  const initial = initialState();
  for (const [key, value] of Object.entries(initial.params)) {
    const next = reducer(initial, { type: 'PARAM', key, value });
    assert.equal(next.showPatientHint, false, key);
    assert.equal(next.params, initial.params);
  }
  const max = { ...initial, params: { ...initial.params, power: LIMITS.power[1] } };
  assert.equal(reducer(max, { type: 'PARAM', key: 'power', value: max.params.power + 1 }).showPatientHint, false);
});

test('touching a slider dismisses the hint without changing values or patient identity', () => {
  const initial = initialState();
  const next = reducer(initial, { type: 'PARAM_INTERACTION' });
  assert.equal(next.showPatientHint, false);
  assert.equal(next.params, initial.params);
  assert.equal(next.selectedId, initial.selectedId);
  assert.equal(next.patients, initial.patients);
  assert.equal(reducer(next, { type: 'PARAM_INTERACTION' }), next);
});

test('unrelated actions and invalid parameter commands do not dismiss the hint', () => {
  const initial = initialState();
  for (const action of [
    { type: 'USB_DRIVE', id: null }, { type: 'NOTICE', value: 'Example' },
    { type: 'PARAM', key: 'power', value: NaN }, { type: 'PARAM', key: 'mode', value: 'invalid' },
    { type: 'PARAM', key: 'unknown', value: 1 },
  ]) assert.equal(reducer(initial, action).showPatientHint, true);
  const list = { ...initial, view: 'list' };
  assert.equal(reducer(list, { type: 'PARAM_INTERACTION' }), list);
});

test('opening patients cancels the hint immediately; returning does not rearm it', () => {
  const initial = initialState();
  const list = reducer(initial, { type: 'PATIENT' });
  assert.equal(list.view, 'list');
  assert.equal(list.showPatientHint, false);
  const returned = reducer(list, { type: 'BACK' });
  assert.equal(returned.view, 'main');
  assert.equal(returned.showPatientHint, false);
  assert.equal(reducer(returned, { type: 'RESTART' }).showPatientHint, true);
});
