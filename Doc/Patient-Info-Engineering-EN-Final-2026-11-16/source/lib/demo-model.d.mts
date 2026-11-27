export type Params = {
  power: number;
  on: number;
  off: number;
  aim: number;
  mode: string;
};
export type Snapshot = {
  uid: string;
  sourceDevice: { label: string; model: string; serial: string };
  power: number;
  mode: string;
  on: number;
  off: number;
  wavelength: number;
  protocol: string;
  seconds: number;
  energy: number;
  endedAt: string;
  date?: string;
};
export type Patient = {
  uid: string;
  id: string;
  name: string;
  gender: string;
  age: string;
  date: string;
  records: Snapshot[];
};
export type Archive = { archiveId: string; schemaVersion: number; patients: Patient[]; nextPatientNumber: number };
export type State = {
  view: string;
  showPatientHint: boolean;
  params: Params;
  usb: boolean;
  deviceId: string;
  usbDrive: string;
  usbWriteError: boolean;
  deviceWriteError: boolean;
  newPatientConfirmed: boolean;
  volumes: Record<string, Archive | null>;
  deviceArchives: Record<string, Archive>;
  transferBack: string;
  transferConfirm: 'import' | 'export' | null;
  warning: boolean;
  firing: boolean;
  seconds: number;
  energy: number;
  pending: Snapshot | null;
  nextPatientNumber: number;
  selectedId: string | null;
  formPatientId: string | null;
  formMode: string;
  listBack: string;
  managePatientId: string | null;
  patients: Patient[];
  form: { id: string; name: string; gender: string; age: string };
  error: string;
  notice: string;
  acousticEnergy: number;
  acousticTime: number;
};
export const LIMITS: Record<
  'power' | 'on' | 'off' | 'aim',
  [number, number, number]
>;
export function formatTime(seconds: number): string;
export function formatTreatmentDate(value?: string, locale?: string): string;
export function metrics(params: Params): {
  duty: number;
  average: number;
  frequency: number | null;
};
export function findMatches(patients: Patient[], name: string): Patient[];
export function nextId(patients: Patient[], minimum?: number): string;
export function initialState(): State;
export const ARCHIVE_VERSION: number;
export const STORAGE_LIMITS: { patients: number; records: number; name: number };
export const PAGE_SIZE: { patients: number; records: number };
export function paginate<T>(items: T[], page: number, size: number): { items: T[]; page: number; pages: number };
export const DEVICES: Record<string, { label: string; model: string; serial: string }>;
export function canReadArchive(state: State): boolean;
export function archiveError(archive: unknown): string;
export function openReview(state: State): State;
export type Action = {
  type: string;
  index?: number;
  key?: string;
  value?: number | string | boolean;
  down?: boolean;
  dt?: number;
  id?: string | null;
  date?: string;
  timestamp?: string;
};
export function reducer(state: State, action: Action): State;
