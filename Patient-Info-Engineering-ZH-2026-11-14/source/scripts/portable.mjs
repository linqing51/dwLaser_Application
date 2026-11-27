import { readFileSync, writeFileSync } from 'node:fs';
import { resolve } from 'node:path';
// Inline the compiled JS/CSS so double-clicking index.html works without a server.
// PNGs remain in assets/ to retain the supplied design at its original resolution.
const dir = resolve('dist');
let html = readFileSync(resolve(dir, 'index.html'), 'utf8');
html = html.replace(
  /<script\b[^>]*src="([^"]+)"[^>]*><\/script>/g,
  (_, src) =>
    `<script type="module">${readFileSync(resolve(dir, src), 'utf8').replaceAll('</script', '<\\/script')}</script>`,
);
html = html.replace(
  /<link\b[^>]*rel="stylesheet"[^>]*href="([^"]+)"[^>]*>/g,
  (_, src) => `<style>${readFileSync(resolve(dir, src), 'utf8')}</style>`,
);
if (/<script[^>]+src=|<link[^>]+rel="stylesheet"/.test(html))
  throw new Error('Portable build still contains external JS/CSS.');
writeFileSync(resolve(dir, 'index.html'), html);
console.log('Portable browser demo: dist/index.html');
