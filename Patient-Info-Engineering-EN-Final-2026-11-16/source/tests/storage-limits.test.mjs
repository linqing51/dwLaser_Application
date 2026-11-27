import test from 'node:test';
import assert from 'node:assert/strict';
import { initialState, reducer, paginate, PAGE_SIZE, archiveError } from '../lib/demo-model.mjs';
const run = (s, ...actions) => actions.reduce(reducer, s);
const treat = s => run(s, { type: 'START' }, { type: 'PEDAL', down: true }, { type: 'TICK', dt: 2 },
  { type: 'STOP', timestamp: '2026-11-12T06:30:00.000Z' }, { type: 'SHOW_REVIEW' });
const sized = count => {
  const s = initialState();
  const patients = Array.from({ length: count }, (_, i) => ({ uid: `patient-${i}`, id: `AR ${String(i + 1).padStart(4, '0')}`,
    name: `Patient ${i + 1}`, age: '', gender: '', date: '', records: [] }));
  return { ...s, patients, nextPatientNumber: count + 1,
    deviceArchives: { ...s.deviceArchives, A: { ...s.deviceArchives.A, patients, nextPatientNumber: count + 1 } } };
};
const register = (s, name) => run(s, { type: 'PATIENT' }, { type: 'NEW' },
  { type: 'FORM', key: 'name', value: name }, { type: 'SAVE' });

test('patient 380 can be saved, patient 381 is blocked without deleting or renumbering', () => {
  const full = register(sized(379), 'Last Patient');
  assert.equal(full.view, 'main');
  assert.equal(full.patients.length, 380);
  assert.equal(full.selectedId, 'AR 0380');
  const blocked = register(full, 'Extra Patient');
  assert.equal(blocked.view, 'edit');
  assert.match(blocked.error, /380/);
  assert.equal(blocked.deviceArchives, full.deviceArchives);
  assert.equal(blocked.patients, full.patients);
  assert.equal(blocked.nextPatientNumber, 381);
  const freed = run(blocked, { type: 'BACK' }, { type: 'DELETE_PATIENT', id: 'AR 0001' }, { type: 'BACK' });
  const retried = register(freed, 'Extra Patient');
  assert.equal(retried.patients.length, 380);
  assert.equal(retried.selectedId, 'AR 0381');
});

test('full patient storage still permits existing-patient treatment and demographic edits', () => {
  const selected = run(sized(380), { type: 'PATIENT' }, { type: 'SELECT', id: 'AR 0001' });
  const saved = reducer(treat(selected), { type: 'SAVE' });
  assert.equal(saved.view, 'success');
  assert.equal(saved.patients.length, 380);
  const edited = run(saved, { type: 'BACK' }, { type: 'PATIENT' }, { type: 'EDIT_PATIENT', id: 'AR 0001' },
    { type: 'FORM', key: 'name', value: 'Corrected Name' }, { type: 'SAVE' });
  assert.equal(edited.view, 'list');
  assert.equal(edited.patients[0].name, 'Corrected Name');
  assert.equal(edited.patients.length, 380);
});

test('unsaved new-patient treatment survives a full device and manual cleanup', () => {
  const review = run(treat(sized(380)), { type: 'FORM', key: 'name', value: 'New Patient' });
  const blocked = reducer(review, { type: 'SAVE' });
  assert.equal(blocked.pending, review.pending);
  assert.equal(blocked.deviceArchives, review.deviceArchives);
  const freed = run(blocked, { type: 'MANAGE' }, { type: 'DELETE_PATIENT', id: 'AR 0380' }, { type: 'BACK' });
  assert.equal(freed.pending, review.pending);
  assert.equal(freed.form.name, 'New Patient');
  const saved = reducer(freed, { type: 'SAVE' });
  assert.equal(saved.view, 'success');
  assert.equal(saved.patients.length, 380);
  assert.equal(saved.patients.at(-1).id, 'AR 0381');
  assert.deepEqual(saved.patients.at(-1).records, [review.pending]);
});

test('record 10 is allowed; record 11 is blocked until an explicitly selected old record is deleted', () => {
  const full = initialState();
  const selected = run(full, { type: 'PATIENT' }, { type: 'SELECT', id: 'AR 0002' });
  const review = treat(selected);
  const blocked = reducer(review, { type: 'SAVE' });
  assert.match(blocked.error, /10 records/);
  assert.equal(blocked.pending, review.pending);
  assert.equal(blocked.deviceArchives, full.deviceArchives);
  assert.equal(blocked.patients.find(p => p.id === 'AR 0002').records.length, 10);
  const freed = run(blocked, { type: 'MANAGE' }, { type: 'DELETE_RECORD', id: 'AR 0002', index: 3 }, { type: 'BACK' });
  assert.equal(freed.pending, review.pending);
  const saved = reducer(freed, { type: 'SAVE' });
  const records = saved.patients.find(p => p.id === 'AR 0002').records;
  assert.equal(saved.view, 'success');
  assert.equal(records.length, 10);
  assert.deepEqual(records.at(-1), review.pending);
  assert.equal(records[0], full.patients.find(p => p.id === 'AR 0002').records[0]);
  assert.ok(!records.some(r => r.uid === full.patients.find(p => p.id === 'AR 0002').records[3].uid));
  assert.equal(reducer(saved, { type: 'SAVE' }), saved);
});

test('18-character names are accepted, 19 are rejected for creation and editing without truncation', () => {
  for (const name of ['A'.repeat(18), 'A'.repeat(8) + ' ' + 'B'.repeat(9)]) {
    const s = register(initialState(), name);
    assert.equal(s.view, 'main');
    assert.equal(s.patients.at(-1).name, name);
  }
  for (const name of ['A'.repeat(19), 'A'.repeat(18) + ' ']) {
    const s = initialState();
    const rejected = register(s, name);
    assert.match(rejected.error, /18 characters/);
    assert.equal(rejected.form.name, name);
    assert.equal(rejected.deviceArchives, s.deviceArchives);
    const edited = run(s, { type: 'PATIENT' }, { type: 'EDIT_PATIENT', id: 'AR 0001' },
      { type: 'FORM', key: 'name', value: name }, { type: 'SAVE' });
    assert.equal(edited.deviceArchives, s.deviceArchives);
    assert.match(edited.error, /18 characters/);
  }
});

test('capacity and name checks apply to imported archives at the exact supported limits', () => {
  const s = sized(380);
  s.patients[0].name = 'A'.repeat(18);
  s.patients[0].records = initialState().patients.find(p => p.id === 'AR 0002').records;
  assert.equal(archiveError(s.deviceArchives.A), '');
  const ready = { ...s, view: 'transfer', volumes: { ...s.volumes, A: structuredClone(s.deviceArchives.A) } };
  const imported = run(ready, { type: 'REQUEST_IMPORT' }, { type: 'CONFIRM_IMPORT' });
  assert.equal(imported.error, '');
  assert.equal(imported.patients.length, 380);
  assert.equal(imported.patients[0].records.length, 10);
});

test('ten records occupy exactly two pages of five; deletions clamp the current page', () => {
  const records = initialState().patients.find(p => p.id === 'AR 0002').records;
  const one = paginate(records, 0, PAGE_SIZE.records);
  const two = paginate(records, 1, PAGE_SIZE.records);
  assert.equal(one.pages, 2);
  assert.equal(two.pages, 2);
  assert.equal(one.items.length, 5);
  assert.equal(two.items.length, 5);
  assert.deepEqual([...one.items, ...two.items], records);
  assert.equal(paginate(records.slice(0, 5), 1, PAGE_SIZE.records).page, 0);
  assert.equal(paginate([], 3, PAGE_SIZE.records).page, 0);
  assert.equal(paginate([], 3, PAGE_SIZE.records).pages, 1);
  const tenPatients = sized(10).patients;
  const patientPageOne = paginate(tenPatients, 0, PAGE_SIZE.patients);
  const patientPageTwo = paginate(tenPatients, 1, PAGE_SIZE.patients);
  assert.equal(patientPageOne.pages, 2);
  assert.equal(patientPageOne.items.length, 5);
  assert.equal(patientPageTwo.items.length, 5);
  assert.deepEqual([...patientPageOne.items, ...patientPageTwo.items], tenPatients);
  const patients = sized(380).patients;
  const pages = Array.from({ length: Math.ceil(380 / PAGE_SIZE.patients) }, (_, i) => paginate(patients, i, PAGE_SIZE.patients).items).flat();
  assert.deepEqual(pages, patients);
});
