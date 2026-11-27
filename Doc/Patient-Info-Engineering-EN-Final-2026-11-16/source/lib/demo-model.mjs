// Demo-only limits: replace these when the official parameter specification arrives.
export const LIMITS = {
  power: [1, 100, 1],
  on: [10, 2000, 10],
  off: [10, 2000, 10],
  aim: [0, 100, 1],
};
export const ARCHIVE_VERSION = 1;
export const STORAGE_LIMITS = { patients: 380, records: 10, name: 18 };
export const PAGE_SIZE = { patients: 5, records: 5 };
export const DEVICES = {
  A: { label: 'Device A', model: 'dwLaser S2', serial: 'S2-A001' },
  B: { label: 'Device B', model: 'dwLaser S2', serial: 'S2-B001' },
  C: { label: 'Device C', model: 'dwLaser S2', serial: 'S2-C001' },
};
const uniqueId = () => globalThis.crypto.randomUUID();
export const canReadArchive = s => s.usb && s.volumes[s.usbDrive]?.schemaVersion === ARCHIVE_VERSION;
export function paginate(items, page, size) {
  const pages = Math.max(1, Math.ceil(items.length / size));
  const current = Math.max(0, Math.min(page, pages - 1));
  return { items: items.slice(current * size, (current + 1) * size), page: current, pages };
}
export const formatTime = (s) =>
  `${Math.floor(s / 60)
    .toString()
    .padStart(2, '0')}:${Math.floor((s + 0.00001) % 60)
    .toString()
    .padStart(2, '0')}`;
export const metrics = (p) => {
  const duty = p.mode === 'CW' ? 1 : p.on / (p.on + p.off);
  return {
    duty,
    average: p.power * duty,
    frequency: p.mode === 'CW' ? null : 1000 / (p.on + p.off),
  };
};
const normalize = (s) => s.trim().toLocaleLowerCase();
export const findMatches = (patients, name) =>
  patients.filter((p) => normalize(p.name) === normalize(name));
export const nextId = (patients, minimum = 1) =>
  `AR ${String(Math.max(minimum, Math.max(0, ...patients.map((p) => Number(p.id.replace(/\D/g, '')))) + 1)).padStart(4, '0')}`;
const emptyForm = (patients, minimum = 1) => ({
  id: nextId(patients, minimum),
  name: '',
  gender: '',
  age: '',
});
export function initialState() {
  const patients = [
    {
      id: 'AR 0001',
      name: 'Jhon Smith',
      gender: 'Male',
      age: '38',
      date: '19-08-2026',
      records: [],
    },
    {
      id: 'AR 0009',
      name: 'Jhon Smith',
      gender: 'Male',
      age: '60',
      date: '13-05-2026',
      records: [],
    },
    ...[
      'Ankita',
      'Ankita',
      'Jenna C. Hassan',
      'Ankita',
      'Ankita',
      'Mohamed Oujda',
      'Mohamed Oujda',
      'Mohamed Oujda',
    ].map((name, i) => ({
      id: `AR ${String([2, 3, 4, 5, 6, 7, 8, 10][i]).padStart(4, '0')}`,
      name,
      gender: '',
      age: '',
      date: '',
      records: [],
    })),
  ].map(patient => ({ ...patient, uid: uniqueId() }));
  // Fictional records for demonstrating both fixed history pages at first launch.
  patients.find(p => p.id === 'AR 0002').records = Array.from({ length: 10 }, (_, i) => ({
    uid: uniqueId(), sourceDevice: { ...DEVICES.A }, power: 30, mode: 'Pulsed', on: 600, off: 700,
    wavelength: 1470, protocol: 'Phlebology 1', seconds: 10 + i, energy: 138.5 + i * 13.8,
    endedAt: `2026-11-${String(i + 1).padStart(2, '0')}T10:00:00.000Z`,
  }));
  const archive = patients => ({ archiveId: uniqueId(), schemaVersion: ARCHIVE_VERSION, patients,
    nextPatientNumber: Math.max(0, ...patients.map(p => Number(p.id.replace(/\D/g, '')))) + 1 });
  return {
    view: 'main',
    showPatientHint: true,
    params: { power: 30, on: 600, off: 700, aim: 100, mode: 'Pulsed' },
    usb: true,
    deviceId: 'A',
    usbDrive: 'A',
    usbWriteError: false,
    deviceWriteError: false,
    newPatientConfirmed: false,
    volumes: { A: null, B: archive(['Emma Wilson', 'Daniel Chen'].map((name, i) => ({
      uid: uniqueId(), id: `AR 000${i + 1}`, name, age: String(40 + i * 5), gender: i ? 'Male' : 'Female', date: '',
      records: [{ uid: uniqueId(), sourceDevice: { ...DEVICES.B }, power: 25, mode: 'CW', on: 600, off: 700,
        wavelength: 1470, protocol: 'Phlebology 1', seconds: 10, energy: 250,
        endedAt: `2026-11-${12 + i}T08:00:00.000Z` }],
    }))) },
    deviceArchives: {
      A: archive(patients),
      B: archive([{ uid: uniqueId(), id: 'AR 0001', name: 'Morgan Lee', age: '42', gender: 'Female', date: '', records: [] }]),
      C: archive([]),
    },
    transferBack: 'list',
    transferConfirm: null,
    warning: false,
    firing: false,
    seconds: 0,
    energy: 0,
    pending: null,
    selectedId: null,
    nextPatientNumber: 11,
    formPatientId: null,
    formMode: 'treatment',
    listBack: 'main',
    managePatientId: null,
    patients,
    form: emptyForm(patients),
    error: '',
    notice: '',
    acousticEnergy: 964,
    acousticTime: 8,
  };
}
const patientForm = p => ({ id: p.id, name: p.name, age: p.age, gender: p.gender });
const deviceError = s => s.deviceWriteError ? 'Unable to save changes to the device. Retry. No data was changed.' : '';
export function archiveError(archive) {
  if (!archive) return 'No patient backup found on this USB drive.';
  if (archive.schemaVersion !== ARCHIVE_VERSION) return 'USB archive version not supported. No data was changed.';
  if (!Array.isArray(archive.patients) || typeof archive.archiveId !== 'string' || !archive.archiveId)
    return 'Invalid patient archive. No data was changed.';
  if (archive.patients.length > STORAGE_LIMITS.patients) return 'Import exceeds the limit of 380 patients. No data was changed.';
  const ids = new Set(), uids = new Set(), recordIds = new Set();
  let maximumId = 0;
  for (const p of archive.patients) {
    if (!p || typeof p.name !== 'string' || !p.name.trim() || [...p.name].length > STORAGE_LIMITS.name)
      return 'Patient names must contain 1–18 characters. No data was changed.';
    if (typeof p.id !== 'string' || !/^AR \d{4,}$/.test(p.id) || typeof p.uid !== 'string' || !p.uid || ids.has(p.id) || uids.has(p.uid))
      return 'Invalid or duplicate patient ID. No data was changed.';
    ids.add(p.id); uids.add(p.uid); maximumId = Math.max(maximumId, Number(p.id.slice(3)));
    if (typeof p.age !== 'string' || (p.age !== '' && (!/^\d+$/.test(p.age) || Number(p.age) > 130)) || !['', 'Male', 'Female'].includes(p.gender))
      return 'Invalid patient details. No data was changed.';
    if (!Array.isArray(p.records)) return 'Invalid treatment records. No data was changed.';
    if (p.records.length > STORAGE_LIMITS.records) return 'Import exceeds 10 records per patient. No data was changed.';
    for (const r of p.records) {
      if (!r || typeof r.uid !== 'string' || !r.uid || recordIds.has(r.uid) || typeof r.endedAt !== 'string' || !Number.isFinite(Date.parse(r.endedAt))
        || !['power', 'on', 'off', 'wavelength', 'seconds', 'energy'].every(key => Number.isFinite(r[key]) && r[key] >= 0)
        || !['CW', 'Pulsed'].includes(r.mode) || typeof r.protocol !== 'string'
        || !['label', 'model', 'serial'].every(key => typeof r.sourceDevice?.[key] === 'string'))
        return 'Invalid or duplicate treatment record. No data was changed.';
      recordIds.add(r.uid);
    }
  }
  if (!Number.isSafeInteger(archive.nextPatientNumber) || archive.nextPatientNumber <= maximumId)
    return 'Invalid patient numbering information. No data was changed.';
  return '';
}
const transferError = (s, operation) => !s.usb ? 'USB drive not detected. Insert a USB drive and try again.'
  : operation === 'import' ? archiveError(s.volumes[s.usbDrive])
  : s.volumes[s.usbDrive] && !canReadArchive(s) ? 'USB archive version not supported. Use another USB drive.' : '';
export function formatTreatmentDate(value, locale = 'en-GB') {
  if (!value) return 'Date unavailable';
  return new Intl.DateTimeFormat(locale, { day: '2-digit', month: 'short', year: 'numeric',
    hour: '2-digit', minute: '2-digit', hour12: false }).format(new Date(value));
}
function writeDevice(s, patients, nextPatientNumber, changes) {
  const error = deviceError(s);
  if (error) return { ...s, error, notice: '' };
  return { ...s, ...changes, patients, nextPatientNumber, error: '',
    deviceArchives: { ...s.deviceArchives, [s.deviceId]: { ...s.deviceArchives[s.deviceId], patients, nextPatientNumber } } };
}
export function openReview(s) {
  const person = s.patients.find(p => p.id === s.selectedId);
  return { ...s, view: 'edit', showPatientHint: false, firing: false,
    formMode: 'treatment', listBack: 'edit', newPatientConfirmed: false,
    formPatientId: person?.id || null,
    form: person ? patientForm(person) : emptyForm(s.patients, s.nextPatientNumber),
    error: '', notice: '' };
}
function selectPatient(s, person) {
  if (s.view === 'duplicates' && s.formMode === 'registration') return { ...s,
    view: 'edit', formPatientId: person.id, form: patientForm(person),
    newPatientConfirmed: false, error: '', notice: '' };
  return { ...s, view: s.pending || s.view === 'duplicates' ? 'edit' : 'main',
    selectedId: person.id,
    formPatientId: person.id, form: patientForm(person), newPatientConfirmed: false,
    error: '', notice: '' };
}
function changeUsb(s, driveId) {
  if (driveId !== null && !Object.hasOwn(s.volumes, driveId)) return s;
  if ((driveId === null && !s.usb) || (s.usb && driveId === s.usbDrive)) return s;
  return { ...s, usb: driveId !== null, usbDrive: driveId || s.usbDrive, transferConfirm: null,
    ...(s.view === 'transfer' ? { error: '', notice: '' } : {}) };
}
function finishSave(s) {
  const error = deviceError(s);
  if (error) return { ...s, view: 'edit', error, notice: '' };
  const found = s.patients.find(p => p.id === s.formPatientId);
  if (s.formMode === 'profile') {
    if (!found) return s;
    const updated = { ...found, name: s.form.name.trim(), age: s.form.age, gender: s.form.gender };
    return writeDevice(s, s.patients.map(p => p.id === found.id ? updated : p), s.nextPatientNumber,
      { view: 'list', formPatientId: null, listBack: 'main', notice: 'Patient details updated on device.' });
  }
  if (!found && s.patients.length >= STORAGE_LIMITS.patients)
    return { ...s, view: 'edit', error: 'Device full (380 patients). Export all device records or delete an unused patient in Manage Records.' };
  const person = found || { ...s.form, uid: uniqueId(), id: nextId(s.patients, s.nextPatientNumber),
    name: s.form.name.trim(), date: '', records: [] };
  const nextPatientNumber = found ? s.nextPatientNumber : Number(person.id.replace(/\D/g, '')) + 1;
  if (s.formMode === 'registration') {
    const changes = { view: 'main', selectedId: person.id, formPatientId: null,
      notice: 'Patient saved to device and selected.' };
    return writeDevice(s, found ? s.patients : [...s.patients, person], nextPatientNumber, changes);
  }
  if (!s.pending) return s;
  if (person.records.length >= STORAGE_LIMITS.records)
    return { ...s, view: 'edit', error: '10 records saved. Delete an old record in Manage Records, or export from the patient list.' };
  const saved = { ...person, date: formatTreatmentDate(s.pending.endedAt), records: [...person.records, { ...s.pending }] };
  return writeDevice(s, found ? s.patients.map(p => p.id === found.id ? saved : p) : [...s.patients, saved],
    nextPatientNumber, { view: 'success', selectedId: null, formPatientId: null, pending: null });
}
export function reducer(s, a) {
  switch (a.type) {
    case 'PARAM_INTERACTION':
      return s.view === 'main' && !s.pending && s.showPatientHint ? { ...s, showPatientHint: false } : s;
    case 'PARAM': {
      if (s.view !== 'main' || s.pending) return s;
      let value = a.value;
      if (a.key === 'mode') {
        if (!['CW', 'Pulsed'].includes(value)) return s;
      } else {
        const limits = LIMITS[a.key];
        if (!limits || !Number.isFinite(value)) return s;
        value = Math.min(
          limits[1],
          Math.max(limits[0], Math.round(value / limits[2]) * limits[2]),
        );
      }
      if (s.params[a.key] === value) return s.showPatientHint ? { ...s, showPatientHint: false } : s;
      return {
        ...s,
        showPatientHint: false,
        params: { ...s.params, [a.key]: value },
      };
    }
    case 'START':
      return s.view !== 'main'
        ? s
        : s.pending
          ? openReview(s)
        : s.warning
          ? { ...s, showPatientHint: false, notice: 'Clear the simulated interlock fault before selecting Ready.' }
          : {
              ...s,
              view: 'surgery',
              showPatientHint: false,
              seconds: 0,
              energy: 0,
              firing: false,
              notice: '',
            };
    case 'PEDAL':
      return {
        ...s,
        firing: !!a.down && s.view === 'surgery' && !s.warning,

      };
    case 'TICK':
      return s.view === 'surgery' &&
        s.firing &&
        !s.warning &&
        Number.isFinite(a.dt) &&
        a.dt > 0
        ? {
            ...s,
            seconds: s.seconds + a.dt,
            energy: s.energy + metrics(s.params).average * a.dt,
          }
        : s;
    case 'STOP': {
      if (s.view !== 'surgery') return s;
      if (s.seconds <= 0) return { ...s, view: 'main', firing: false };
      return { ...s, view: 'review-transition', firing: false, pending: {
        uid: uniqueId(), sourceDevice: { ...DEVICES[s.deviceId] },
        power: s.params.power, mode: s.params.mode, on: s.params.on, off: s.params.off,
        wavelength: 1470, protocol: 'Phlebology 1', seconds: s.seconds, energy: s.energy,
        endedAt: a.timestamp || new Date().toISOString(),
      } };
    }
    case 'SHOW_REVIEW':
      return s.view === 'review-transition' && s.pending ? openReview(s) : s;
    case 'PATIENT': {
      if (s.view !== 'main') return s;
      if (s.pending) return openReview(s);
      return { ...s, view: 'list', showPatientHint: false, listBack: 'main', managePatientId: null,
        formPatientId: null, error: '', notice: '' };
    }
    case 'NEW':
      return s.view === 'list' ? {
        ...s, view: 'edit', form: emptyForm(s.patients, s.nextPatientNumber), formPatientId: null, selectedId: s.pending ? null : s.selectedId, newPatientConfirmed: false,
        formMode: s.pending ? 'treatment' : 'registration', managePatientId: null, error: '',
      } : s;
    case 'PICK':
      return s.view === 'edit' ? { ...s, view: 'list', listBack: 'edit', managePatientId: null, error: '' } : s;
    case 'MANAGE':
      return s.view === 'edit' ? { ...s, view: 'list', listBack: 'edit',
        managePatientId: s.patients.find(p => p.id === s.formPatientId)?.id || null, error: '' } : s;
    case 'SELECT': {
      if (s.view !== 'list') return s;
      const person = s.patients.find(p => p.id === a.id);
      return person ? selectPatient(s, person) : s;
    }
    case 'EDIT_PATIENT': {
      if (s.view !== 'list' || s.pending) return s;
      const person = s.patients.find(p => p.id === a.id);
      return person ? { ...s, view: 'edit', formMode: 'profile', formPatientId: person.id,
        form: patientForm(person), error: '' } : s;
    }
    case 'DELETE_PATIENT': {
      if (s.view !== 'list') return s;
      const patient = s.patients.find(p => p.id === a.id);
      if (!patient) return s;
      const patients = s.patients.filter(p => p.id !== a.id);
      const linked = a.id === s.selectedId || a.id === s.formPatientId;
      return writeDevice(s, patients, s.nextPatientNumber, {
        notice: 'Patient and associated treatment records deleted from device.',
        ...(linked ? { selectedId: null, formPatientId: null, managePatientId: null, newPatientConfirmed: false,
          form: emptyForm(patients, s.nextPatientNumber),
          ...(s.pending ? { view: 'edit', formMode: 'treatment', listBack: 'edit',
            notice: 'Patient deleted. Select or register a patient to save the current treatment.' } : {}) } : {}),
      });
    }
    case 'DELETE_RECORD': {
      if (s.view !== 'list') return s;
      const patient = s.patients.find(p => p.id === a.id);
      if (!patient || !Number.isInteger(a.index) || a.index < 0 || a.index >= patient.records.length) return s;
      const records = patient.records.filter((_, index) => index !== a.index);
      return writeDevice(s, s.patients.map(p => p.id === a.id ? {
        ...p, records, date: records.length ? formatTreatmentDate(records.at(-1).endedAt) : '',
      } : p), s.nextPatientNumber, { notice: 'Treatment record deleted from device. Patient details retained.' });
    }
    case 'UNSELECT':
      return s.view === 'list' && !s.pending ? { ...s, view: 'main', selectedId: null } : s;
    case 'REQUEST_DISCARD':
      return s.view === 'edit' && s.pending ? { ...s, view: 'discard' } : s;
    case 'DISCARD':
      return s.view === 'discard' && s.pending ? { ...s, view: 'main', pending: null, selectedId: null,
        formPatientId: null, form: emptyForm(s.patients, s.nextPatientNumber), notice: 'Treatment record discarded. Verify the next patient before selecting Ready.' } : s;
    case 'FORM':
      return s.view === 'edit' && (!s.formPatientId || s.formMode === 'profile') && ['name', 'age', 'gender'].includes(a.key)
        ? { ...s, form: { ...s.form, [a.key]: a.value }, newPatientConfirmed: a.key === 'name' ? false : s.newPatientConfirmed, error: '' }
        : s;
    case 'SAVE': {
      if (s.view !== 'edit' || (s.formMode === 'treatment' && !s.pending)) return s;
      if (!s.form.name.trim())
        return { ...s, error: 'Patient name is required.' };
      if ([...s.form.name].length > STORAGE_LIMITS.name)
        return { ...s, error: 'Patient name must be 18 characters or fewer, including spaces.' };
      if (
        s.form.age !== '' &&
        (!/^\d+$/.test(s.form.age) || Number(s.form.age) > 130)
      )
        return {
          ...s,
          error:
            'Enter a whole number from 0 to 130 for age.',
        };
      if (s.formPatientId || s.newPatientConfirmed || s.formMode === 'profile') return finishSave(s);
      if (findMatches(s.patients, s.form.name).length) return { ...s, view: 'duplicates', error: '' };
      return finishSave(s);
    }
    case 'CHOOSE': {
      if (s.view !== 'duplicates') return s;
      if (!a.id) return { ...s, view: 'edit', newPatientConfirmed: true, formPatientId: null,
        selectedId: s.pending ? null : s.selectedId };
      const person = findMatches(s.patients, s.form.name).find(p => p.id === a.id);
      return person ? selectPatient(s, person) : s;
    }
    case 'BACK':
      if (s.view === 'review-transition') return s;
      if (s.view === 'transfer') return { ...s, view: s.transferBack, transferConfirm: null, error: '', notice: '' };
      return {
        ...s,
        view: s.pending ? 'edit' : s.view === 'duplicates' ? 'edit' : s.view === 'edit' ? 'list' : 'main',
        managePatientId: null,
        formPatientId: !s.pending && s.view === 'edit' ? null : s.formPatientId,
        error: '',
        firing: false,
      };
    case 'TRANSFER':
      return s.view === 'list' && !s.managePatientId ? { ...s, view: 'transfer', transferBack: s.view, transferConfirm: null, error: '', notice: '' } : s;
    case 'REQUEST_EXPORT':
    case 'REQUEST_IMPORT': {
      if (s.view !== 'transfer' || (a.type === 'REQUEST_IMPORT' && s.pending)) return s;
      const operation = a.type === 'REQUEST_EXPORT' ? 'export' : 'import';
      const error = transferError(s, operation);
      return { ...s, transferConfirm: error ? null : operation, error, notice: '' };
    }
    case 'CANCEL_TRANSFER':
      return { ...s, transferConfirm: null, error: '' };
    case 'CONFIRM_EXPORT': {
      if (s.view !== 'transfer' || s.transferConfirm !== 'export') return s;
      const error = transferError(s, 'export') || (s.usbWriteError ? 'Unable to write to USB. No data was changed. Retry.' : '') || deviceError(s);
      if (error) return { ...s, transferConfirm: null, error };
      return { ...s, transferConfirm: null, error: '', patients: [], selectedId: null, formPatientId: null, managePatientId: null,
        form: s.formPatientId ? emptyForm([], s.nextPatientNumber) : s.form,
        deviceArchives: { ...s.deviceArchives, [s.deviceId]: { ...s.deviceArchives[s.deviceId], patients: [] } },
        volumes: { ...s.volumes, [s.usbDrive]: structuredClone(s.deviceArchives[s.deviceId]) },
        notice: `Backup exported to USB ${s.usbDrive}. Device records were cleared.` };
    }
    case 'CONFIRM_IMPORT': {
      if (s.view !== 'transfer' || s.transferConfirm !== 'import' || s.pending) return s;
      const error = transferError(s, 'import') || deviceError(s);
      if (error) return { ...s, transferConfirm: null, error };
      const archive = structuredClone(s.volumes[s.usbDrive]);
      archive.nextPatientNumber = Math.max(archive.nextPatientNumber, s.nextPatientNumber);
      return { ...s, transferConfirm: null, error: '', selectedId: null, formPatientId: null,
        deviceArchives: { ...s.deviceArchives, [s.deviceId]: archive }, patients: archive.patients,
        nextPatientNumber: archive.nextPatientNumber, form: emptyForm(archive.patients, archive.nextPatientNumber),
        notice: `Backup imported from USB ${s.usbDrive}. Device records were replaced.` };
    }
    case 'USB':
      return changeUsb(s, a.value ? s.usbDrive : null);
    case 'USB_DRIVE':
      return changeUsb(s, a.id);
    case 'USB_WRITE_ERROR':
      return { ...s, usbWriteError: !!a.value };
    case 'DEVICE_WRITE_ERROR':
      return { ...s, deviceWriteError: !!a.value };
    case 'USB_VERSION': {
      if (!s.usb || !s.volumes[s.usbDrive] || ![1, 2].includes(a.value)) return s;
      return { ...s, transferConfirm: null, error: '', volumes: { ...s.volumes,
        [s.usbDrive]: { ...s.volumes[s.usbDrive], schemaVersion: a.value } } };
    }
    case 'DEVICE':
    case 'RESTART': {
      if (s.pending || s.view === 'surgery') return s;
      const deviceId = a.type === 'DEVICE' ? a.id : s.deviceId;
      if (!DEVICES[deviceId] || (a.type === 'DEVICE' && deviceId === s.deviceId)) return s;
      const boot = initialState();
      const { patients, nextPatientNumber } = s.deviceArchives[deviceId];
      return { ...boot, deviceId, deviceArchives: s.deviceArchives, volumes: s.volumes, usb: s.usb, usbDrive: s.usbDrive,
        patients, nextPatientNumber, form: emptyForm(patients, nextPatientNumber) };
    }
    case 'WARNING':
      return { ...s, warning: !!a.value, firing: false };
    case 'NOTICE':
      return { ...s, notice: a.value };
    case 'ACOUSTIC':
      return s.view === 'surgery'
        ? { ...s, [a.key]: Math.max(1, Math.min(9999, a.value)) }
        : s;
    default:
      return s;
  }
}
