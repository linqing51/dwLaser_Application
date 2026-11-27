import test from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync, existsSync } from 'node:fs';
import { createRequire } from 'node:module';
import { resolve, dirname } from 'node:path';
import { fileURLToPath } from 'node:url';
import { createElement } from 'react';
import { renderToStaticMarkup } from 'react-dom/server';
import ts from 'typescript';
import * as model from '../lib/demo-model.mjs';
import * as webmcp from '../lib/webmcp.mjs';
import { translate, messages } from '../lib/i18n.mjs';

const root = fileURLToPath(new URL('..', import.meta.url));
const require = createRequire(import.meta.url);
// Render the actual components in memory. This checks text and field values, not browser layout.
function components(locale) {
  const cache = new Map();
  function load(file) {
    if (cache.has(file)) return cache.get(file).exports;
    const module = { exports: {} };
    cache.set(file, module);
    let source = readFileSync(file, 'utf8');
    if (file.endsWith('/app/page.tsx')) source += '\nexport { MainScreen, Surgery, Edit, PatientList, UsbTransfer, DiscardConfirmation };';
    const output = ts.transpileModule(source, { compilerOptions: {
      module: ts.ModuleKind.CommonJS, jsx: ts.JsxEmit.ReactJSX, target: ts.ScriptTarget.ES2022, esModuleInterop: true,
    } }).outputText;
    const localRequire = id => {
      if (id === '@/lib/i18n.mjs') return { t: (key, ...values) => translate(key, locale, values), isChinese: locale === 'zh-CN' };
      if (id === '@/lib/demo-model.mjs') return model;
      if (id === '@/lib/webmcp.mjs') return webmcp;
      if (id.startsWith('@/') || id.startsWith('.')) {
        const base = id.startsWith('@/') ? resolve(root, id.slice(2)) : resolve(dirname(file), id);
        const path = [base, base + '.tsx', base + '.ts'].find(existsSync);
        if (path) return load(path);
      }
      return require(id);
    };
    new Function('require', 'module', 'exports', output)(localRequire, module, module.exports);
    return module.exports;
  }
  return load(resolve(root, 'app/page.tsx'));
}

test('all translation templates preserve placeholders and English originals', () => {
  for (const [key, value] of Object.entries(messages)) {
    const slots = text => [...text.matchAll(/\{\d+\}/g)].map(m => m[0]).sort();
    assert.deepEqual(slots(value), slots(key), key);
    if (!key.includes('{')) assert.equal(translate(key, 'en'), key);
  }
  assert.equal(translate('Select {0} {1}', 'zh-CN', ['Ankita', 'AR 0002']), '选择患者 Ankita AR 0002');
  assert.equal(translate('Backup exported to USB B. Device records were cleared.', 'zh-CN'), '备份已导出至 USB B，设备档案已清空。');
  assert.equal(translate('Backup imported from USB A. Device records were replaced.', 'zh-CN'), '已从 USB A 导入备份，设备档案已替换。');
});

test('all static model error and notice messages have Chinese translations', () => {
  const source = readFileSync(resolve(root, 'lib/demo-model.mjs'), 'utf8');
  for (const [, text] of source.matchAll(/(?:error|notice):\s*'([^']+)'/g)) assert.ok(messages[text], text);
});

for (const locale of ['en', 'zh-CN']) test(`${locale} renders translated controls without changing IDs, enums or five-row pagination`, () => {
  const ui = components(locale), send = () => {}, initial = model.initialState();
  const render = (component, s = initial) => renderToStaticMarkup(createElement(component, { s, send }));
  const text = key => translate(key, locale);
  const main = render(ui.MainScreen);
  assert.ok(main.includes(text('Ready')));
  assert.ok(main.includes('patient-entry-hint'));
  assert.ok(!render(ui.MainScreen, model.reducer(initial, { type: 'PARAM', key: 'power', value: 31 })).includes('patient-entry-hint'));
  const list = render(ui.PatientList);
  assert.ok(list.includes(text('Select Patient')));
  assert.ok(list.includes(text('Delete Patient')));
  assert.equal((list.match(/class="patient-entry"/g) || []).length, 5);
  assert.ok(list.includes(translate('Page {0} of {1}', locale, [1, 2])));
  assert.ok(list.includes('AR 0002'));
  const historyState = { ...initial, view: 'edit', formPatientId: 'AR 0002', pending: initial.patients.find(p => p.id === 'AR 0002').records[0] };
  const managed = render(ui.PatientList, model.reducer(historyState, { type: 'MANAGE' }));
  assert.ok(managed.includes('history-popup'));
  assert.ok(managed.includes('Ankita · AR 0002'));
  assert.equal((managed.match(/class="history-record"/g) || []).length, 5);
  assert.ok(managed.includes(translate('Page {0} of {1}', locale, [1, 2])));
  assert.ok(managed.includes(text('Back to Review')));
  assert.ok(!managed.includes(text('USB Transfer')));
  assert.ok(!managed.includes('patient-directory'));
  const registration = model.reducer(model.reducer(initial, { type: 'PATIENT' }), { type: 'NEW' });
  const edit = render(ui.Edit, registration);
  assert.ok(edit.includes(`value="Male">${text('Male')}`));
  assert.ok(edit.includes(`value="Female">${text('Female')}`));
  assert.ok(edit.includes(text('Save and Select Patient')));
  const transfer = render(ui.UsbTransfer, { ...initial, transferConfirm: 'export' });
  assert.ok(transfer.includes(text('Export Patient Backup?')));
  assert.ok(transfer.includes(text('Export and Clear Device')));
  const surgery = render(ui.Surgery);
  assert.ok(surgery.includes(text('Standby')));
  if (locale === 'zh-CN') {
    assert.ok(!main.includes('Aiming Beam'));
    assert.ok(!list.includes('Delete Patient'));
    assert.ok(!edit.includes('Not specified'));
    assert.ok(!transfer.includes('Device records will be retained.'));
  }
});
