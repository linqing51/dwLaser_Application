import test from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';

test('full-screen patient directory does not inherit a legacy fixed-size list box', () => {
  const page = readFileSync(new URL('../app/page.tsx', import.meta.url), 'utf8');
  const css = readFileSync(new URL('../app/globals.css', import.meta.url), 'utf8')
    .replace(/\/\*[\s\S]*?\*\//g, '');
  const component = page.slice(page.indexOf('function PatientList('));
  const rootClasses = component.match(/<section className="([^"]+)"/);
  assert.ok(rootClasses, 'PatientList must have an identifiable root panel.');
  const classes = new Set(rootClasses[1].split(/\s+/));
  // Source-level regression guard, not a substitute for browser layout validation.
  for (const rule of css.matchAll(/([^{}]+)\{([^{}]*)\}/g)) {
    const matched = rule[1].split(',').some(selector => {
      const direct = selector.trim();
      return /^(?:\.[\w-]+)+$/.test(direct)
        && direct.slice(1).split('.').every(name => classes.has(name));
    });
    if (!matched) continue;
    for (const size of rule[2].matchAll(/(?:^|;)\s*(width|height|max-width|max-height)\s*:\s*(\d+(?:\.\d+)?)px\s*(?=;|$)/g)) {
      const native = size[1].includes('width') ? 1024 : 600;
      assert.ok(Number(size[2]) >= native,
        `${rule[1].trim()} restricts the full-screen patient panel to ${size[1]}: ${size[2]}px (expected ${native}px or automatic sizing).`);
    }
  }
});
