'use client';
/* oxlint-disable next/no-img-element -- Original screenshot assets remain unoptimized for the offline demo. */
import {
  useEffect,
  useLayoutEffect,
  useReducer,
  useRef,
  useState,
  type CSSProperties,
  type Dispatch,
  type ReactNode,
} from 'react';
import { flushSync } from 'react-dom';
import { registerDemoTools } from '@/lib/webmcp.mjs';
import { Slider } from '@/components/ui/slider';
import { Checkbox } from '@/components/ui/checkbox';
import {
  Dialog,
  DialogContent,
  DialogDescription,
  DialogTitle,
} from '@/components/ui/dialog';
import {
  initialState,
  reducer,
  formatTime,
  formatTreatmentDate as formatModelTreatmentDate,
  metrics,
  findMatches,
  LIMITS,
  STORAGE_LIMITS,
  PAGE_SIZE,
  paginate,
  type Action,
} from '@/lib/demo-model.mjs';

import { t, isChinese } from '@/lib/i18n.mjs';
const formatTreatmentDate = (value?: string) => t(formatModelTreatmentDate(value, isChinese ? 'zh-CN' : 'en-GB'));

type State = ReturnType<typeof initialState>;
type Send = Dispatch<Action>;
const rect = (
  left: number,
  top: number,
  width: number,
  height: number,
): CSSProperties => ({ position: 'absolute', left, top, width, height });
function Hit({
  label,
  x,
  y,
  w,
  h,
  onClick,
  children,
  className = '',
  disabled = false,
}: {
  label: string;
  x: number;
  y: number;
  w: number;
  h: number;
  onClick: () => void;
  children?: React.ReactNode;
  className?: string;
  disabled?: boolean;
}) {
  return (
    <button
      type="button"
      className={`hit ${className}`}
      style={rect(x, y, w, h)}
      aria-label={label}
      title={label}
      onClick={onClick}
      disabled={disabled}
    >
      {children}
    </button>
  );
}
function MainScreen({ s, send }: { s: State; send: Send }) {
  const p = s.params,
    m = metrics(p),
    change = (key: string, value: number | string) =>
      send({ type: 'PARAM', key, value });
  return (
    <>
      <img
        className="reference"
        src="assets/main.png"
        alt=""
        draggable="false"
      />
      {isChinese && <>
        <span className="translated-label translated-welcome" style={rect(235, 36, 300, 32)}>{t('Welcome to dwLaser S2')}</span>
        <span className="translated-label" style={rect(57, 334, 170, 26)}>{t('Average Power')}</span>
        <span className="translated-label" style={rect(300, 334, 170, 26)}>{t('Frequency')}</span>
        <span className="translated-label" style={rect(543, 334, 160, 26)}>{t('Duty Cycle')}</span>
        <span className="translated-label" style={rect(129, 439, 180, 30)}>{t('Aiming Beam')}</span>
        <span className="translated-label translated-pulse" style={rect(874, 278, 57, 21)}>{t('T On')}</span>
        <span className="translated-label translated-pulse" style={rect(874, 361, 57, 21)}>{t('T Off')}</span>
      </>}
      <div className="power-zone">
        <output className="power-value" aria-label={t("Power value")}>
          {p.power}
          <span>W</span>
        </output>
      </div>
      <Hit
        label={t("Decrease power")}
        x={190}
        y={140}
        w={63}
        h={77}
        onClick={() => change('power', p.power - 1)}
      />
      <Hit
        label={t("Increase power")}
        x={518}
        y={140}
        w={65}
        h={77}
        onClick={() => change('power', p.power + 1)}
      />
      <div className="power-slider" style={rect(57, 260, 650, 20)}
        onPointerDownCapture={() => send({ type: 'PARAM_INTERACTION' })}
        onKeyDownCapture={e => { if (['ArrowLeft', 'ArrowRight', 'ArrowUp', 'ArrowDown', 'Home', 'End', 'PageUp', 'PageDown'].includes(e.key)) send({ type: 'PARAM_INTERACTION' }); }}>
        <Slider
          aria-label={t("Power")}
          value={[p.power]}
          min={LIMITS.power[0]}
          max={LIMITS.power[1]}
          onValueChange={(v) => change('power', Array.isArray(v) ? v[0] : v)}
        />
      </div>
      <output
        className="parameter"
        style={rect(57, 364, 160, 28)}
        aria-label={t("Average Power")}
      >
        {m.average.toFixed(1)}
        <span>W</span>
      </output>
      <output
        className="parameter"
        style={rect(300, 364, 160, 28)}
        aria-label={t("Frequency")}
      >
        {m.frequency === null ? (isChinese ? '不适用' : 'N/A') : m.frequency.toFixed(2)}
        <span>Hz</span>
      </output>
      <output
        className="parameter"
        style={rect(543, 364, 160, 28)}
        aria-label={t("Duty Cycle")}
      >
        {(m.duty * 100).toFixed(1)}
        <span>%</span>
      </output>
      <Hit
        label={t("Continuous wave (CW)")}
        x={763}
        y={131}
        w={220}
        h={41}
        className={p.mode === 'CW' ? 'selected' : ''}
        onClick={() => change('mode', 'CW')}
      >
        <span className="mode-label">{t("CW")}</span>
      </Hit>
      <Hit
        label={t("Pulsed mode")}
        x={763}
        y={184}
        w={220}
        h={41}
        className={p.mode === 'Pulsed' ? 'selected' : ''}
        onClick={() => change('mode', 'Pulsed')}
      >
        <span className="mode-label">{t("Pulsed")}</span>
      </Hit>
      <output
        className="pulse-value"
        style={rect(820, 302, 110, 38)}
        aria-label={t("Pulse Width / T On")}
      >
        {p.on}ms
      </output>
      <output
        className="pulse-value"
        style={rect(820, 385, 110, 39)}
        aria-label={t("T Off")}
      >
        {p.off}ms
      </output>
      {(
        [
          ['on', 301],
          ['off', 384],
        ] as const
      ).map(([key, y]) => (
        <div key={key}>
          <Hit
            label={t('Decrease {0}', t(key === 'on' ? 'Pulse Width / T On' : 'T Off'))}
            x={763}
            y={Number(y)}
            w={55}
            h={41}
            onClick={() => change(String(key), p[key] - 10)}
            disabled={p.mode === 'CW'}
          />
          <Hit
            label={t('Increase {0}', t(key === 'on' ? 'Pulse Width / T On' : 'T Off'))}
            x={931}
            y={Number(y)}
            w={55}
            h={41}
            onClick={() => change(String(key), p[key] + 10)}
            disabled={p.mode === 'CW'}
          />
        </div>
      ))}
      {p.mode === 'CW' && (
        <div
          className="cw-inactive"
          style={rect(747, 275, 251, 153)}
          aria-hidden="true"
        />
      )}
      <output className="aim-value" style={rect(537, 438, 122, 34)}>
        {p.aim.toFixed(1)}
      </output>
      <Hit
        label={t("Decrease aiming beam intensity")}
        x={493}
        y={438}
        w={42}
        h={35}
        onClick={() => change('aim', p.aim - 1)}
      />
      <Hit
        label={t("Increase aiming beam intensity")}
        x={661}
        y={438}
        w={43}
        h={35}
        onClick={() => change('aim', p.aim + 1)}
      />
      <div className="aim-slider" style={rect(57, 488, 648, 13)}
        onPointerDownCapture={() => send({ type: 'PARAM_INTERACTION' })}
        onKeyDownCapture={e => { if (['ArrowLeft', 'ArrowRight', 'ArrowUp', 'ArrowDown', 'Home', 'End', 'PageUp', 'PageDown'].includes(e.key)) send({ type: 'PARAM_INTERACTION' }); }}>
        <Slider
          aria-label={t("Aiming Beam")}
          value={[p.aim]}
          min={0}
          max={100}
          onValueChange={(v) => change('aim', Array.isArray(v) ? v[0] : v)}
        />
      </div>
      <output
        className={`warning ${s.warning ? 'active' : ''}`}
        style={rect(55, 542, 652, 34)}
        aria-label={t("Warning")}
      >
        {s.warning ? t("Interlock error") : ''}
      </output>
      <Hit
        label={t("Ready: enter treatment screen")}
        x={747}
        y={528}
        w={252}
        h={60}
        className="ready"
        onClick={() => send({ type: 'START' })}
      > {t("Ready")} </Hit>
      <Hit
        label={t("Patient: select, register or manage patients")}
        className={s.showPatientHint ? 'patient-entry-hint' : ''}
        x={883}
        y={23}
        w={52}
        h={56}
        onClick={() => send({ type: 'PATIENT' })}
      >
        {s.showPatientHint && <span className="startup-patient-icon" aria-hidden="true"
          style={{ backgroundImage: 'url("assets/pending.png")' }} />}
      </Hit>
      {[
        [35, 31, 690, 42],
        [753, 27, 52, 52],
        [820, 27, 50, 52],
        [940, 27, 52, 52],
      ].map(([x, y, w, h], i) => (
        <Hit
          key={i}
          label={t(['Clinical application', 'Treatment presets', 'Save treatment preset', 'Settings'][i])}
          x={x}
          y={y}
          w={w}
          h={h}
          onClick={() =>
            send({ type: 'NOTICE', value: 'This function is not available in this demo.' })
          }
        />
      ))}
    </>
  );
}
function Surgery({ s, send }: { s: State; send: Send }) {
  return (
    <>
      <img
        className="reference"
        src="assets/treatment.png"
        alt=""
        draggable="false"
      />
      {isChinese && <>
        <span className="translated-label translated-welcome" style={rect(275, 34, 280, 36)}>{t('Welcome to dwLaser S2')}</span>
        <span className="translated-label" style={rect(754, 112, 222, 30)}>{t('Acoustic energy interval')}</span>
        <span className="translated-label" style={rect(754, 324, 222, 30)}>{t('Acoustic time interval')}</span>
      </>}
      <div className="surgery-panel" style={rect(22, 101, 713, 490)}>
        <span className="energy-label">{t("Energy")}</span>
        <output className="energy" aria-label={t("Energy")}>
          {s.energy.toFixed(1)} J
        </output>
        <output
          className={`firing ${s.firing ? 'on' : ''}`}
          aria-label={t("Software status")}
        >
          {s.warning ? t("WARNING") : s.firing ? t("FIRING") : t("READY")}
        </output>
        <div className="surgery-box power-box">
          <label htmlFor="surgery-power">{t("◴ Power")}</label>
          <output id="surgery-power">{s.params.power.toFixed(1)}W</output>
        </div>
        <div className="surgery-box time-box">
          <label htmlFor="surgery-timer">{t("◷ Treatment Time")}</label>
          <output id="surgery-timer" aria-label={t("Timer")}>
            {formatTime(s.seconds)}
          </output>
        </div>
      </div>
      <output className="acoustic" style={rect(799, 203, 132, 35)}>
        {s.acousticEnergy.toFixed(1)}J
      </output>
      <output className="acoustic" style={rect(811, 415, 120, 35)}>
        {s.acousticTime.toFixed(1)}S
      </output>
      {(
        [
          ['acousticEnergy', 202],
          ['acousticTime', 414],
        ] as const
      ).map(([key, y]) => (
        <div key={key}>
          <Hit
            label={t(key === 'acousticEnergy' ? 'Decrease energy alert interval' : 'Decrease time alert interval')}
            x={761}
            y={Number(y)}
            w={38}
            h={44}
            onClick={() => send({ type: 'ACOUSTIC', key, value: s[key] - 1 })}
          />
          <Hit
            label={t(key === 'acousticEnergy' ? 'Increase energy alert interval' : 'Increase time alert interval')}
            x={942}
            y={Number(y)}
            w={38}
            h={44}
            onClick={() => send({ type: 'ACOUSTIC', key, value: s[key] + 1 })}
          />
        </div>
      ))}
      <Hit
        label={t("Standby: end session and return")}
        x={747}
        y={527}
        w={252}
        h={62}
        className="standby"
        onClick={() => send({ type: 'STOP', timestamp: new Date().toISOString() })}
      > {t("Standby")} </Hit>
    </>
  );
}
function PatientIdentity({ s }: { s: State }) {
  const person = s.patients.find(p => p.id === s.selectedId);
  return <div className="patient-identity" aria-label={t("Current patient")}>
    <strong>{person ? `${person.name} · ${person.id}` : t("No patient selected")}</strong>
  </div>;
}
function Edit({ s, send }: { s: State; send: Send }) {
  const registration = s.formMode === 'registration';
  const profile = s.formMode === 'profile';
  const treatment = s.formMode === 'treatment';
  const compact = !!s.formPatientId && !profile;
  const field = (key: string, value: string) => send({ type: 'FORM', key, value });
  return <form className="patient-panel" noValidate aria-label={t("Patient information")}
    onSubmit={e => { e.preventDefault(); send({ type: 'SAVE' }); }}>
    <header><div><span className="eyebrow">{t("PATIENT INFO")}</span>
      <h2>{profile ? t("Edit Patient") : registration ? t("Register Patient") : t("Review Treatment Record")}</h2></div>
      <span className="panel-step">{t("Device Storage")}</span></header>
    <div className="panel-body">
    {compact ? <div className="review-patient-summary">
      <h3>{s.form.name}</h3><p>{s.form.id} · {s.form.age ? t('{0} years', s.form.age) : t("Age not specified")} · {t(s.form.gender || 'Gender not specified')}</p>
      <span>{t("Verify the patient name and ID before saving.")}</span>
    </div> : <div className="patient-fields">
      <label>{t("Patient ID")}<input aria-label={t("Patient ID")} value={s.form.id} readOnly /></label>
      <label>{t("Patient name")} <em>*</em><small className="patient-name-hint">{t("Max. 18 characters, including spaces")}</small><input aria-label={t("Patient Name")} maxLength={STORAGE_LIMITS.name} required
        readOnly={!!s.formPatientId && !profile} value={s.form.name} onChange={e => field('name', e.target.value)}
        placeholder={t("Enter patient name")} autoComplete="off" /></label>
      <label>{t("Gender")} <small>{t("Optional")}</small><select aria-label={t("Gender")} disabled={!!s.formPatientId && !profile}
        value={s.form.gender} onChange={e => field('gender', e.target.value)}>
        <option value="">{t("Not specified")}</option><option value="Male">{t("Male")}</option><option value="Female">{t("Female")}</option>
      </select></label>
      <label>{t("Age")} <small>{t("Optional")}</small><input aria-label={t("Age")} inputMode="numeric" maxLength={3}
        readOnly={!!s.formPatientId && !profile} value={s.form.age} onChange={e => field('age', e.target.value)} placeholder={t("Not specified")} /></label>
    </div>}
    {treatment && <div className="patient-choice"><span>{s.formPatientId ? t("Patient for this treatment record") : t("Enter new patient details, or select an existing patient.")}</span>
      <button type="button" className="text-action" onClick={() => send({ type: 'PICK' })}>{s.formPatientId ? t("Change Patient") : t("Select Patient")}</button></div>}
    <div className="treatment-summary">
      {!treatment ? <><strong>{t("Patient Details")}</strong><p>{profile ? t("Update patient details on this device. Patient ID and treatment history will remain unchanged.") : t("Save patient details to this device and select this patient. No treatment record will be created.")}</p></> : <>
        <strong>{t("Treatment Summary")} <span>{formatTreatmentDate(s.pending?.endedAt)}</span></strong>
        <div className="summary-values"><span><small>{t("Energy")}</small>{s.pending?.energy.toFixed(1)} <b>J</b></span>
          <span><small>{t("Output time")}</small>{formatTime(s.pending?.seconds || 0)}</span>
          <span><small>{t("Power")}</small>{s.pending?.power} <b>W</b></span></div>
        <p>{t(s.pending?.protocol || '')} · {s.pending?.wavelength} nm · {t(s.pending?.mode || '')}</p>
      </>}
    </div>
    <div className="panel-feedback" role="alert">{t(s.error)}</div>
    </div>
    <footer>{!treatment
      ? <button type="button" className="secondary-action" onClick={() => send({ type: 'BACK' })}>{t("Cancel")}</button>
      : <button type="button" className="discard-action" onClick={() => send({ type: 'REQUEST_DISCARD' })}>{t("Discard Record")}</button>}
      {s.error && /full|10 records/.test(s.error) && <button type="button" className="text-action" onClick={() => send({ type: 'MANAGE' })}>{t("Manage Records")}</button>}
      <button type="submit" className="primary-action">{profile ? t("Save Changes") : registration ? t("Save and Select Patient") : t("Save Record")}</button></footer>
  </form>;
}
function Duplicates({ s, send }: { s: State; send: Send }) {
  const [page, setPage] = useState(0);
  const result = paginate(findMatches(s.patients, s.form.name), page, s.pending ? 2 : 3);
  return <section className="patient-panel paged-list"><header><div><span className="eyebrow">{t("PATIENT INFO")}</span><h2>{t("Patients with Matching Names")}</h2></div></header>
    <p className="panel-description">{t("Verify the patient ID and details. A matching name does not confirm identity.")}</p>
    <div className="patient-results">{result.items.map(p => <button key={p.id} className="patient-option"
      onClick={() => send({ type: 'CHOOSE', id: p.id })}>
      <span><strong>{p.name}</strong><small>{p.id} · {p.age || t("Age not specified")} · {t(p.gender || 'Gender not specified')}</small></span>
      <span>{t("Use This Patient ›")}</span></button>)}</div>
    <PageControls page={result.page} pages={result.pages} onPage={setPage} />
    <footer><button className="secondary-action" onClick={() => send({ type: 'BACK' })}>{s.pending ? t("Back to Review") : t("Back")}</button>
      <button className="primary-action" onClick={() => send({ type: 'CHOOSE', id: null })}>{t("Use as New Patient")}</button></footer>
  </section>;
}
function PageControls({ page, pages, onPage, children }: {
  page: number; pages: number; onPage: (page: number) => void; children?: ReactNode;
}) {
  return <div className="page-controls"><div className="page-message" role="status">{children}</div>
    <button className="secondary-action" disabled={page === 0} onClick={() => onPage(page - 1)}>{t("Previous")}</button>
    <span className="page-number">{t('Page {0} of {1}', page + 1, pages)}</span>
    <button className="secondary-action" disabled={page + 1 === pages} onClick={() => onPage(page + 1)}>{t("Next")}</button>
  </div>;
}
function DeviceModal({ title, onClose, children, className = '', inactive = false }: {
  title: string; onClose: () => void; children: ReactNode; className?: string; inactive?: boolean;
}) {
  const dialog = useRef<HTMLDivElement>(null);
  useEffect(() => {
    if (inactive) return;
    const previous = document.activeElement as HTMLElement | null;
    dialog.current?.focus();
    return () => previous?.focus();
  }, [inactive]);
  return <div className="device-modal-layer" inert={inactive} aria-hidden={inactive || undefined}>
    <div className={`device-modal ${className}`} role="dialog" aria-modal="true" aria-label={title}
      tabIndex={-1} ref={dialog} onKeyDown={event => {
        if (event.key === 'Escape') { event.stopPropagation(); onClose(); }
        if (event.key !== 'Tab') return;
        const controls = Array.from(event.currentTarget.querySelectorAll<HTMLElement>('button:not(:disabled), input:not(:disabled), select:not(:disabled)'));
        const first = controls[0], last = controls.at(-1);
        if (!first || !last) { event.preventDefault(); return; }
        if (event.shiftKey && (document.activeElement === first || document.activeElement === event.currentTarget)) {
          event.preventDefault(); last.focus();
        } else if (!event.shiftKey && document.activeElement === last) { event.preventDefault(); first.focus(); }
      }}>{children}</div>
  </div>;
}
function PatientList({ s, send }: { s: State; send: Send }) {
  const [query, setQuery] = useState('');
  const [page, setPage] = useState(0);
  const [history, setHistory] = useState<string | null>(s.managePatientId);
  const closeHistory = () => s.managePatientId ? send({ type: 'BACK' }) : setHistory(null);
  const [historyPage, setHistoryPage] = useState(0);
  const [deletion, setDeletion] = useState<{ id: string; index?: number } | null>(null);
  const deletingPatient = s.patients.find(p => p.id === deletion?.id);
  const deletingRecord = deletion?.index !== undefined ? deletingPatient?.records[deletion.index] : null;
  const historyPatient = s.patients.find(p => p.id === history);
  const records = paginate((historyPatient?.records || []).map((record, index) => ({ record, index }))
    .sort((a, b) => Date.parse(b.record.endedAt) - Date.parse(a.record.endedAt)), historyPage, PAGE_SIZE.records);
  const filtered = [...s.patients].filter(p => `${p.name} ${p.id}`.toLowerCase().includes(query.trim().toLowerCase()))
    .sort((a,b) => a.name.localeCompare(b.name));
  const result = paginate(filtered, page, PAGE_SIZE.patients);
  return <>{!s.managePatientId && <section className="patient-panel paged-list patient-directory" inert={!!historyPatient || !!deletion}><header><div><span className="eyebrow">{t('PATIENT INFO')} · {s.patients.length} / 380</span><h2>{s.pending ? t("Select Patient") : t("Patients")}</h2></div>
    <div className="list-header-actions"><button className="secondary-action" onClick={() => send({ type: 'TRANSFER' })}>{t("USB Transfer")}</button>
      <button className="primary-action" onClick={() => send({ type: 'NEW' })}>{t("+ New Patient")}</button></div></header>
    <input className="patient-search" aria-label={t("Search patients")} placeholder={t("Search by name or patient ID")} value={query} onChange={e => { setQuery(e.target.value); setPage(0); }} />
    <div className="patient-results">{!filtered.length && <p className="empty-patients">{t("No patients found. Select New Patient to register a patient.")}</p>}
      {result.items.map(p => <div className="patient-entry" key={p.id}>
        <div className="patient-option"><span><strong>{p.name}{s.selectedId === p.id && <em>{t("Selected")}</em>}</strong>
          <small>{p.id} · {p.age ? t('{0} years', p.age) : t("Age not specified")} · {t(p.gender || 'Gender not specified')}</small></span>
          <div className="row-actions"><button className="text-action" aria-haspopup="dialog" onClick={() => { setHistory(p.id); setHistoryPage(0); }}>{t('Treatment Records ({0})', p.records.length)}</button>
          <button className="select-patient" aria-label={t('Select {0} {1}', p.name, p.id)} onClick={() => send({ type: 'SELECT', id: p.id })}>{t("Select Patient")}</button>
          <button className="delete-action" aria-label={t('Delete patient {0} {1}', p.name, p.id)} aria-haspopup="dialog" onClick={() => setDeletion({ id: p.id })}>{t("Delete Patient")}</button></div></div>
      </div>)}
    </div>
    {(s.error || s.patients.length >= STORAGE_LIMITS.patients) && <p className="patient-list-feedback" role="alert">
      {t(s.error || '380 patients saved. Delete an unused patient to add another.')}</p>}
    <footer className="patient-list-footer"><button className="secondary-action" onClick={() => send({ type: 'BACK' })}>{s.pending ? t("Back to Review") : t("Close")}</button>
      {!s.pending && s.selectedId && <button className="secondary-action" onClick={() => send({ type: 'UNSELECT' })}>{t("Clear Patient Selection")}</button>}
      <PageControls page={result.page} pages={result.pages} onPage={setPage} /></footer>
    </section>}
    {historyPatient && <DeviceModal title={t("Treatment Records")} className="history-popup" onClose={closeHistory} inactive={!!deletion}>
      <header><div><span className="eyebrow">{t('TREATMENT RECORDS')} · {historyPatient.records.length} / 10</span>
        <h2>{historyPatient.name} · {historyPatient.id}</h2></div></header>
      <div className="history-page">{records.items.length ? records.items.map(({ record: r, index }) => <div className="history-record" key={r.uid}>
        <div className="history-description"><p>{formatTreatmentDate(r.endedAt)} · {r.energy.toFixed(1)} J · {formatTime(r.seconds)} · {r.power} W · {r.wavelength} nm</p>
          <small>{t(r.protocol)} · {t(r.mode)}{r.mode === 'Pulsed' ? t(' · On {0} / Off {1} ms', r.on, r.off) : ''} · {r.sourceDevice.serial}</small></div>
        <button className="delete-action" onClick={() => setDeletion({ id: historyPatient.id, index })}>{t("Delete Treatment Record")}</button>
      </div>) : <p className="empty-patients">{t("No treatment records saved.")}</p>}</div>
      <PageControls page={records.page} pages={records.pages} onPage={setHistoryPage}>{t(s.error || 'Newest first · 5 records per page')}</PageControls>
      <footer>{!s.pending && <button className="secondary-action" onClick={() => send({ type: 'EDIT_PATIENT', id: historyPatient.id })}>{t("Edit Patient")}</button>}
        <button className="secondary-action" onClick={closeHistory}>{s.managePatientId ? t("Back to Review") : t("Close")}</button></footer>
    </DeviceModal>}
    {deletingPatient && <DeviceModal title={deletingRecord ? t("Delete Treatment Record?") : t("Delete Patient?")} className="confirmation-popup" onClose={() => setDeletion(null)}>
        <h2>{deletingRecord ? t("Delete Treatment Record?") : t("Delete Patient?")}</h2>
        <p>{deletingRecord
          ? t("Delete this treatment record from the device? Other records and patient details will be retained.")
          : t('Delete this patient and all {0} associated treatment records from the device?', deletingPatient.records.length)}</p>
        <p><strong>{deletingPatient?.name}</strong> · {deletingPatient?.id}</p>
        {!deletingRecord && (deletingPatient.id === s.selectedId || deletingPatient.id === s.formPatientId) && <p>{s.pending
          ? t("This patient is selected for the current treatment. The unsaved treatment will be retained. Select or register a patient before saving it.")
          : t("This is the selected patient. Deleting this patient will also clear the current patient selection.")}</p>}
        {deletingRecord && <p>{formatTreatmentDate(deletingRecord.endedAt)} · {deletingRecord.energy.toFixed(1)} J · {formatTime(deletingRecord.seconds)} · {deletingRecord.power} W</p>}
        <p>{t("This action cannot be undone.")}</p>
        <div className="delete-dialog-actions">
          <button className="secondary-action" onClick={() => setDeletion(null)}>{t("Cancel")}</button>
          <button className="confirm-delete" onClick={() => {
            if (!deletion) return;
            send({ type: deletion.index === undefined ? 'DELETE_PATIENT' : 'DELETE_RECORD', id: deletion.id, index: deletion.index });
            if (deletion.index === undefined && !s.deviceWriteError) setHistory(null);
            setDeletion(null);
          }}>{deletingRecord ? t("Delete Treatment Record") : t("Delete Patient")}</button>
        </div>
    </DeviceModal>}
  </>;
}
function DiscardConfirmation({ s, send }: { s: State; send: Send }) {
  return <><div className="guard-shade" />
    <section className="pending-guard" role="alertdialog" aria-label={t("Discard Treatment Record?")}>
      <span className="eyebrow">{t("CONFIRM DISCARD")}</span><h2>{t("Discard Treatment Record?")}</h2>
      <p>{s.form.name || t("No patient selected")} · {s.form.id}</p>
      <p>{s.pending?.energy.toFixed(1)} J · {formatTime(s.pending?.seconds || 0)} · {s.pending?.power} W</p>
      <p>{t("This treatment record will be discarded. Existing patient details and saved records will be retained. This action cannot be undone.")}</p>
      <button autoFocus className="secondary-action" onClick={() => send({ type: 'BACK' })}>{t("Back to Review")}</button>
      <button className="confirm-delete" onClick={() => send({ type: 'DISCARD' })}>{t("Discard Record")}</button>
    </section></>;
}
function UsbTransfer({ s, send }: { s: State; send: Send }) {
  const backup = s.usb ? s.volumes[s.usbDrive] : null;
  const recordCount = (patients: State['patients']) => patients.reduce((sum, p) => sum + p.records.length, 0);
  const importing = s.transferConfirm === 'import';
  return <><section className="patient-panel transfer-panel" inert={!!s.transferConfirm}>
    <header><div><span className="eyebrow">{t("PATIENT INFO")}</span><h2>{t("USB Transfer")}</h2></div>
      <span className="panel-step">{s.usb ? t('USB {0} connected', s.usbDrive) : t("No USB connected")}</span></header>
    <div className="transfer-summary"><strong>{t("Device Storage")}</strong><p>{t('{0} / 380 patients · {1} treatment records', s.patients.length, recordCount(s.patients))}</p></div>
    <div className="transfer-option"><div><h3>{t("Export to USB")}</h3><p>{t("Export all saved patients and treatment records, then clear device storage.")}</p></div>
      <button className="primary-action" disabled={!s.usb} onClick={() => send({ type: 'REQUEST_EXPORT' })}>{t("Export to USB")}</button></div>
    <div className="transfer-option"><div><h3>{t("Import from USB")}</h3><p>{s.pending ? t("Save or discard the current treatment before importing.") : t("Replace all device records with a USB backup.")}</p></div>
      <button className="secondary-action" disabled={!s.usb || !!s.pending} onClick={() => send({ type: 'REQUEST_IMPORT' })}>{t("Import from USB")}</button></div>
    <p className="transfer-status">{!s.usb ? t("Insert a USB drive to transfer records. Device storage remains available.")
      : !backup ? t("No patient backup on this USB drive.") : backup.schemaVersion !== 1 ? t("USB archive version not supported.")
      : t('USB backup: {0} patients · {1} treatment records', backup.patients.length, recordCount(backup.patients))}</p>
    <div className="transfer-feedback" role="status">{t(s.error || s.notice)}</div>
    <footer><button className="secondary-action" onClick={() => send({ type: 'BACK' })}>{t("Back")}</button>
      <span className="footer-note">{s.pending ? t("The current unsaved treatment is not included in the backup.") : t("USB backups do not update automatically.")}</span></footer>
  </section>
  {s.transferConfirm && <DeviceModal title={importing ? t("Replace Device Records?") : t("Export Patient Backup?")} className="confirmation-popup" onClose={() => send({ type: 'CANCEL_TRANSFER' })}>
    <h2>{importing ? t("Replace Device Records?") : t("Export Patient Backup?")}</h2>
    {importing ? <>
      <p>{t('Replace all {0} patients and {1} treatment records on this device with the backup on USB {2}?', s.patients.length, recordCount(s.patients), s.usbDrive)}</p>
      <p>{t('Backup: {0} patients · {1} treatment records.', backup?.patients.length, recordCount(backup?.patients || []))}</p>
      <p>{t("Existing device records will be removed. Export them to another USB drive first if needed. This action cannot be undone.")}</p>
    </> : <>
      <p>{t('Export {0} patients and {1} saved treatment records to USB {2}?', s.patients.length, recordCount(s.patients), s.usbDrive)}</p>
      <p>{backup ? t("The existing patient backup on this USB drive will be replaced.") : t("A patient backup will be created on this USB drive.")} {t("Device records will be cleared.")}</p>
      {s.pending && <p>{t("The current unsaved treatment is not included.")}</p>}
    </>}
    <div className="delete-dialog-actions"><button className="secondary-action" onClick={() => send({ type: 'CANCEL_TRANSFER' })}>{t("Cancel")}</button>
      <button className={importing ? 'confirm-delete' : 'primary-action'} onClick={() => send({ type: importing ? 'CONFIRM_IMPORT' : 'CONFIRM_EXPORT' })}>{importing ? t("Replace and Import") : t("Export and Clear Device")}</button></div>
  </DeviceModal>}</>;
}
function ReviewOverlay({ s, send }: { s: State; send: Send }) {
  const dialog = useRef<HTMLDivElement>(null);
  useEffect(() => { dialog.current?.focus(); }, [s.view]);
  return <>
    <div inert><MainScreen s={s} send={() => {}} /><PatientIdentity s={s} /></div>
    <div className="review-backdrop" />
    <div className={`review-card${s.view === 'list' ? ' review-management' : ''}`} role="dialog" aria-modal="true" aria-label={t("Treatment record review")}
      tabIndex={-1} ref={dialog} onKeyDown={event => {
        if (event.key !== 'Tab') return;
        const controls = Array.from(event.currentTarget.querySelectorAll<HTMLElement>('button:not(:disabled), input:not(:disabled), select:not(:disabled), [tabindex="0"]'));
        const first = controls[0], last = controls.at(-1);
        if (!first || !last) { event.preventDefault(); return; }
        if (event.shiftKey && (document.activeElement === first || document.activeElement === event.currentTarget)) {
          event.preventDefault(); last.focus();
        } else if (!event.shiftKey && document.activeElement === last) {
          event.preventDefault(); first.focus();
        }
      }}>
      {s.view === 'edit' && <Edit s={s} send={send} />}
      {s.view === 'list' && <PatientList s={s} send={send} />}
      {s.view === 'duplicates' && <Duplicates s={s} send={send} />}
      {s.view === 'discard' && <DiscardConfirmation s={s} send={send} />}
      {s.view === 'transfer' && <UsbTransfer s={s} send={send} />}
    </div>
  </>;
}
export default function Home() {
  const [s, send] = useReducer(reducer, undefined, initialState),
    [scale, setScale] = useState(1),
    [nativeSize, setNativeSize] = useState(true),
    [help, setHelp] = useState(false);
  const screen = useRef<HTMLDivElement>(null),
    previousView = useRef('main');
  const stateRef = useRef(s);
  useLayoutEffect(() => {
    stateRef.current = s;
  }, [s]);
  useEffect(
    () =>
      registerDemoTools(
        (
          document as Document & {
            modelContext?: Parameters<typeof registerDemoTools>[0];
          }
        ).modelContext,
        () => stateRef.current,
        (values: Record<string, number | string>) =>
          flushSync(() => {
            for (const [key, value] of Object.entries(values))
              send({ type: 'PARAM', key, value });
          }),
      ),
    [],
  );
  useEffect(() => {
    const resize = () =>
      setScale(
        Math.max(
          0.18,
          nativeSize ? 1 : Math.min((innerWidth - 32) / 1024, (innerHeight - 260) / 600, 1.5),
        ),
      );
    resize();
    addEventListener('resize', resize);
    return () => removeEventListener('resize', resize);
  }, [nativeSize]);
  useEffect(() => {
    if (!s.notice) return;
    const t = setTimeout(() => send({ type: 'NOTICE', value: '' }), 2800);
    return () => clearTimeout(t);
  }, [s.notice]);
  useEffect(() => {
    if (s.view !== 'review-transition') return;
    // Visual sequencing only: output was already stopped synchronously by STOP.
    let timer: ReturnType<typeof setTimeout>;
    const frame = requestAnimationFrame(() => {
      timer = setTimeout(() => send({ type: 'SHOW_REVIEW' }), 450);
    });
    return () => { cancelAnimationFrame(frame); clearTimeout(timer); };
  }, [s.view]);
  useEffect(() => {
    if (s.view !== 'success') return;
    const t = setTimeout(
      () => send({ type: 'BACK' }),
      1500,
    );
    return () => clearTimeout(t);
  }, [s.view]);
  useEffect(() => {
    if (!s.firing) return;
    let last = performance.now();
    const t = setInterval(() => {
      const now = performance.now();
      send({ type: 'TICK', dt: (now - last) / 1000 });
      last = now;
    }, 50);
    return () => clearInterval(t);
  }, [s.firing]);
  useEffect(() => {
    const release = () => send({ type: 'PEDAL', down: false });
    const visibility = () => {
      if (document.hidden) release();
    };
    addEventListener('blur', release);
    document.addEventListener('visibilitychange', visibility);
    return () => {
      removeEventListener('blur', release);
      document.removeEventListener('visibilitychange', visibility);
    };
  }, []);
  useEffect(() => {
    if (previousView.current !== s.view) {
      previousView.current = s.view;
      if (!s.pending || s.view === 'review-transition') screen.current?.focus();
    }
  }, [s.view]);
  useEffect(() => {
    const escape = (e: KeyboardEvent) => {
      if (e.key === 'Escape' && !help) {
        if (s.view === 'surgery') send({ type: 'PEDAL', down: false });
        else if (s.view !== 'main') send({ type: 'BACK' });
      }
    };
    addEventListener('keydown', escape);
    return () => removeEventListener('keydown', escape);
  }, [s.view, help]);
  const modal = ['edit', 'duplicates', 'success', 'list', 'discard', 'review-transition', 'transfer'].includes(
    s.view,
  );
  return (
    <main className={`demo-shell${nativeSize ? ' native-size' : ''}`}>
      <div
        className="device-wrap"
        style={{ width: 1024 * scale, height: 600 * scale }}
      >
        <div
          ref={screen}
          tabIndex={-1}
          className="device"
          aria-label={`dwLaser S2 — ${t(s.view)}`}
          style={{ transform: `scale(${scale})` }}
        >
          {s.view === 'main' && <><MainScreen s={s} send={send} /><PatientIdentity s={s} /></>}
          {s.view === 'surgery' && <><Surgery s={s} send={send} /><PatientIdentity s={s} /></>}
          {s.view === 'review-transition' && <div inert><MainScreen s={s} send={() => {}} /><PatientIdentity s={s} /></div>}
          {s.pending && s.view !== 'review-transition' && <ReviewOverlay s={s} send={send} />}
          {!s.pending && s.view === 'edit' && <Edit s={s} send={send} />}
          {!s.pending && s.view === 'duplicates' && <Duplicates s={s} send={send} />}
          {!s.pending && s.view === 'list' && <PatientList s={s} send={send} />}
          {!s.pending && s.view === 'transfer' && <UsbTransfer s={s} send={send} />}
          {s.view === 'success' && (
            <>
              <img
                className="reference"
                src="assets/success.png"
                alt=""
              />
              <span className="success-label" aria-hidden="true">{t("Saved Successfully")}</span>
              <Hit
                label={t("Saved Successfully. Select to return to the main screen.")}
                x={0}
                y={0}
                w={1024}
                h={600}
                className="message-dismiss"
                onClick={() => send({ type: 'BACK' })}
              />
              <output className="sr-only">{t("Treatment record saved successfully.")} </output>
            </>
          )}
        </div>
      </div>
      <div className="demo-controls">
        <span className="demo-tag"> {t("OPTION 3")} <span>{t("Register before treatment · Review before saving")}</span>
        </span>
        <label htmlFor="demo-device">{t("Simulated device")} <select id="demo-device" value={s.deviceId} disabled={!!s.pending || s.view === 'surgery'}
            onChange={e => send({ type: 'DEVICE', id: e.target.value })}>
            <option value="A">{t("Device A · S2-A001")}</option><option value="B">{t("Device B · S2-B001")}</option><option value="C">{t("Device C · S2-C001")}</option>
          </select>
        </label>
        <label htmlFor="demo-usb">{t("Simulated drive")} <select id="demo-usb" value={s.usb ? s.usbDrive : ''}
            onChange={e => send({ type: 'USB_DRIVE', id: e.target.value || null })}>
            <option value="A">USB A</option><option value="B">USB B</option><option value="">{t("No USB")}</option>
          </select>
        </label>
        <label htmlFor="demo-write-error">
          <Checkbox id="demo-write-error" checked={s.usbWriteError}
            onCheckedChange={value => send({ type: 'USB_WRITE_ERROR', value })} /> {t("Simulate USB write failure")} </label>
        <label htmlFor="demo-device-error">
          <Checkbox id="demo-device-error" checked={s.deviceWriteError}
            onCheckedChange={value => send({ type: 'DEVICE_WRITE_ERROR', value })} /> {t("Simulate device storage failure")} </label>
        <label htmlFor="demo-usb-version">
          <Checkbox id="demo-usb-version" checked={!!s.volumes[s.usbDrive] && s.volumes[s.usbDrive]?.schemaVersion !== 1} disabled={!s.usb || !s.volumes[s.usbDrive]}
            onCheckedChange={value => send({ type: 'USB_VERSION', value: value ? 2 : 1 })} /> {t("Simulate newer USB format")} </label>
        <label htmlFor="demo-native-size">
          <Checkbox id="demo-native-size" checked={nativeSize}
            onCheckedChange={value => setNativeSize(!!value)} /> {t("Actual Size (1024 × 600)")} </label>
        <button className="fullscreen" disabled={!!s.pending || s.view === 'surgery'}
          onClick={() => send({ type: 'RESTART' })}>{t("Restart Demo Device")}</button>
        <label htmlFor="demo-warning">
          <Checkbox
            id="demo-warning"
            checked={s.warning}
            onCheckedChange={(value) => send({ type: 'WARNING', value })}
            disabled={modal}
          /> {t("Simulate interlock fault")} </label>
        <button
          className={`pedal ${s.firing ? 'pressed' : ''}`}
          disabled={s.view !== 'surgery' || s.warning}
          onPointerDown={(e) => {
            e.currentTarget.setPointerCapture(e.pointerId);
            send({ type: 'PEDAL', down: true });
          }}
          onPointerUp={() => send({ type: 'PEDAL', down: false })}
          onPointerCancel={() => send({ type: 'PEDAL', down: false })}
          onLostPointerCapture={() => send({ type: 'PEDAL', down: false })}
          onKeyDown={(e) => {
            if (e.key === ' ' || e.key === 'Enter') {
              e.preventDefault();
              send({ type: 'PEDAL', down: true });
            }
          }}
          onKeyUp={(e) => {
            if (e.key === ' ' || e.key === 'Enter')
              send({ type: 'PEDAL', down: false });
          }}
          onBlur={() => send({ type: 'PEDAL', down: false })}
        > {t("Press and Hold Footswitch (Simulated)")} </button>
        <button className="fullscreen" onClick={() => setHelp(true)}> {t("Demo Instructions")} </button>
        <button
          className="fullscreen"
          onClick={() => {
            const operation = document.fullscreenElement
              ? document.exitFullscreen()
              : document.documentElement.requestFullscreen();
            operation.catch(() =>
              send({
                type: 'NOTICE',
                value: 'Full screen is unavailable. Use your browser’s full-screen controls.',
              }),
            );
          }}
        > {t("Full Screen")} </button>
      </div>
      <p className="demo-storage-note">{t("Devices A/B/C have separate simulated internal storage. USB A/B hold exported backups. Restart Demo Device retains saved data; reloading this webpage resets the simulation. No physical storage is accessed. Ankita · AR 0002 has 10 sample records for pagination.")}</p>
      <output className="demo-status" aria-live="polite">
        {t(s.notice) ||
          (s.view === 'surgery'
            ? t("Hold the simulated footswitch to deliver output; release to pause. Select Standby to end the session.")
            : s.pending
              ? t("Review the patient and treatment summary. Save or discard the record to continue.")
              : s.view === 'success'
                ? t("Treatment record saved to simulated device storage. Returning to the main screen.")
                : t("Select or register a patient, or select Ready to proceed without a patient."))}
      </output>
      <Dialog open={help} onOpenChange={setHelp}>
        <DialogContent className="help-dialog">
          <DialogTitle>{t("Demo Instructions")}</DialogTitle>
          <DialogDescription> {t("Interface demonstration only. USB and footswitch inputs are simulated.")} </DialogDescription>
          <ol>
            <li>{t("Before treatment, register or select a patient. Alternatively, select Ready without selecting a patient.")}</li>
            <li>{t("Hold the simulated footswitch to generate output. Select Standby to stop simulated output and return to the parameter screen. The review card then opens automatically.")}</li>
            <li>{t("Patient details and treatment records are saved on the simulated device, even with No USB selected. Limits: 380 patients, 10 records per patient and 18 characters per name, including spaces.")}</li>
            <li>{t("USB B contains two sample patients with one treatment record each. Select USB B, open USB Transfer from the patient list, then select Import from USB and confirm replacement.")}</li>
            <li>{t("Open USB Transfer to export a backup. Switch to Device B or C, then import that backup. Import requires confirmation and replaces the destination device archive. Simply connecting a USB does not load its patients.")}</li>
            <li>{t("Open Treatment Records for Ankita · AR 0002 to see 10 sample records across two pages. Use Previous and Next; no swiping is required. Full storage blocks new records without deleting existing data.")}</li>
            <li>{t("Simulate device storage failure tests saving and deleting on the device. Simulate USB write failure tests export retries. Simulate newer USB format tests unsupported backups without changing device records.")}</li>
            <li>{t("Actual Size displays the device at 1024 × 600 without scaling. Scroll below the device to reach the demo controls. Turn it off to fit the demonstration in a smaller window.")}</li>
            <li>
              {t('Enter Jhon Smith to display matching names. Select an existing patient or confirm a new patient, then review and select Save Record.')}
            </li>
            <li>{t("Save Record completes the review. Discard Record requires confirmation. If record storage is full, Manage Records opens the current patient history for deletion. USB Transfer is available only on the patient list. Export clears saved device records after success; the unsaved treatment is retained and requires patient selection again.")}</li>
          </ol>
          <p> {t("The patient icon is highlighted on first entering the parameter screen after startup. It turns off when you start adjusting a parameter, open Patient Info or select Ready, and stays off until restart. Patient identity is display-only. Restart Demo Device retains saved device data and USB backups; reloading this webpage resets the entire simulation. Device switching, importing and restarting are unavailable during unresolved treatment. Use fictional patient details only.")} </p>
          <p className="help-note"> {t("Demo ranges: power 1–100 W; T On / T Off 10–2000 ms; aiming beam 0–100. T On represents pulse duration. These are demonstration values, not device specifications. Preset and settings screens are outside this demo.")} </p>
        </DialogContent>
      </Dialog>
    </main>
  );
}
