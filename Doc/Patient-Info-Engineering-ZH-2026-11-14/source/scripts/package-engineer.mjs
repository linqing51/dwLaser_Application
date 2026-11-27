import { cpSync, existsSync, mkdirSync, readFileSync, readdirSync, renameSync, statSync, writeFileSync } from 'node:fs';
import { resolve, join } from 'node:path';
import { execFileSync } from 'node:child_process';
import assert from 'node:assert/strict';

const source = resolve('.');
const workspace = resolve('..');
const html = readFileSync(join(source, 'dist/index.html'), 'utf8');
assert(!/<script[^>]+src=|<link[^>]+rel="stylesheet"/.test(html), 'External JS/CSS found');
assert(!/localStorage|sessionStorage|indexedDB/.test(html), 'Browser persistence found');
const fonts = [...html.matchAll(/data:font\/otf;base64,([A-Za-z0-9+/=]+)/g)].map(m => Buffer.from(m[1], 'base64'));
assert.equal(fonts.length, 3);
for (const name of readdirSync(join(source, 'app/fonts'))) {
  assert(fonts.some(font => font.equals(readFileSync(join(source, 'app/fonts', name)))), `Missing embedded font: ${name}`);
}
for (const file of new Set(html.match(/assets\/[\w-]+\.png/g))) assert(existsSync(join(source, 'dist', file)), file);

const chineseHtml = html.replace('<html lang="en">', '<html lang="zh-CN">')
  .replace('<title>OPTION 3 · dwLaser Patient Info</title>', '<title>方案 3 · dwLaser 患者信息</title>')
  .replace('Laser device patient record interface demo. No hardware connection.', '激光设备患者信息交互演示，不连接真实硬件。');
assert(chineseHtml.includes('<html lang="zh-CN">'));
assert.equal(chineseHtml.match(/<script type="module">([\s\S]*?)<\/script>/)?.[1], html.match(/<script type="module">([\s\S]*?)<\/script>/)?.[1]);

for (const [folder, releaseName, chinese] of [
  ['Patient-Info-Engineering-2026-11-14', 'Laser-UI-Demo-Scheme3', false],
  ['Patient-Info-Engineering-ZH-2026-11-14', 'Laser-UI-Demo-Scheme3-ZH', true],
]) {
const target = join(workspace, folder);
const release = join(workspace, releaseName);
mkdirSync(target, { recursive: true });
mkdirSync(release, { recursive: true });
for (const destination of [target, release]) {
  writeFileSync(join(destination, 'index.html'), chinese ? chineseHtml : html);
  if (chinese) writeFileSync(join(destination, 'english.html'), html);
  cpSync(join(source, 'public/assets'), join(destination, 'assets'), { recursive: true });
  cpSync(join(source, 'DEMO交互说明.md'), join(destination, '使用说明.md'));
  cpSync(join(source, 'README.md'), join(destination, '实现说明.md'));
  cpSync(join(source, 'UI-SPEC.md'), join(destination, '字号与颜色规格.md'));
}
const sourceOut = join(target, 'source');
mkdirSync(sourceOut, { recursive: true });
const included = ['app', 'components', 'hooks', 'lib', 'public', 'tests', 'scripts', 'package.json',
  'pnpm-lock.yaml', 'tsconfig.json', 'next-env.d.ts', 'vite.static.config.ts', 'standalone.tsx', 'index.html',
  'README.md', 'DEMO交互说明.md', 'UI-SPEC.md'];
for (const path of included) cpSync(join(source, path), join(sourceOut, path), { recursive: true });
writeFileSync(join(target, '打开方式.txt'),
  (chinese ? '中文版：先解压整个文件夹，再双击 index.html；english.html 可查看英文版。两版共用 assets 文件夹，请保留。\n' : '英文版：先解压整个文件夹，再双击 index.html，请保留 assets 文件夹。\n') +
  '无需联网、安装开发环境或字体。中文优先使用电脑自带微软雅黑，其次苹方。\n' +
  '高亮测试：首次进入参数界面患者图标亮起；调节任一参数或点击患者图标立即熄灭。重启模拟设备后重新提示。\n' +
  '默认按1024×600原尺寸显示，演示控件位于下方。窗口较小时取消“原始尺寸 / Actual Size”可缩放查看。\n' +
  '分页测试：设备 A / Device A → 患者图标 → Ankita · AR 0002 → 治疗记录（10）/ Treatment Records (10) → 下一页 / Next。\n' +
  '满记录测试：选择 Ankita · AR 0002 → 模拟治疗 → 待机 → 保存记录 → 管理记录；直接打开该患者历史。删除旧记录后，点击返回核对继续保存。\n' +
  '删除测试：选择患者后重新打开患者列表，直接点击同行“删除患者 / Delete Patient”；确认后删除患者及历史，并清除当前选择。\n' +
  'USB B 演示：选择 USB B → 患者列表 → USB 导入／导出 → 从 USB 导入 → 替换并导入；设备变为2位患者、合计2条记录。导出成功会清空设备，失败时保留原数据。\n' +
  '跨设备测试：Device A → USB Transfer 导出到 USB A → Device B → USB Transfer 导入并确认替换。\n' +
  '本原型的设备存储与 USB 均为内存模拟；Restart Demo Device 保留已保存数据，刷新网页重置整个演示。\n' +
  '使用说明.md：演示操作；实现说明.md：工程交接；字号与颜色规格.md：UI规格；source：完整源码。\n');
writeFileSync(join(target, '验证记录.md'),
  '# 交付验证 · 2026-11-14\n\n' +
  '- 81 项自动测试通过，包括设备独立保存、380/381人、10/11条记录、18/19字符、五条分页、整库确认导入、导入导出失败及满容量清理后重试。\n' +
  '- 删除已选患者后清除关联，保留未保存治疗并要求重新选择；删除失败保留关联，删除其他患者不影响当前治疗，USB 备份不变。\n' +
  '- 新增样式冲突回归检查：修复前可检测到患者页面继承旧320×380px列表尺寸；改用独立类名后通过。此项为源码检查，不等同于浏览器视觉验收。\n' +
  '- 新增高亮测试：全部参数、数值不变、边界值、滑块触碰及患者列表入口均熄灭；返回不重新点亮，重启后重新提示。\n' +
  '- 中英文界面共用编译脚本；已通过 React 静态渲染检查，两版都呈现5人列表，中文按钮和提示翻译，患者ID及性别内部字段值保持一致。此项不是浏览器视觉验证。\n' +
  '- Manage Records 直接打开当前患者历史；治疗历史无 USB 入口，删除旧记录后直接返回核对并保存，失败时保留原记录及本次治疗。中英文静态渲染确认此路径不呈现患者列表。\n' +
  '- TypeScript 类型检查、离线构建通过。\n' +
  '- 英文版3个字体文件已核对内嵌字节；中文版使用电脑自带中文字体，所有图片引用可在交付包内找到。\n' +
  '- JS/CSS/字体内嵌；未使用浏览器持久存储；不包含英文讲解稿。\n' +
  '- 固定弹窗按976×576布局，记录区5×56px；已测量内嵌字体的长姓名、摘要和删除按钮文字宽度。\n' +
  '- 患者列表改为每页5人，5×72px行高、单行底栏；10人分页测试确认为两页，保留原字号与44px点击高度。\n' +
  '- Select Patient 与 Delete Patient 已放在患者列表同一行；按内嵌字体测量，18个宽字母姓名及 Selected 标记仍能容纳。\n' +
  '- 自动浏览器访问此前受到 file:// 策略限制，本次未执行逐页浏览器视觉验收；需在工程师浏览器和实机检查固定弹窗、分页、触摸及键盘。\n' +
  '- 尚未连接物理 USB 或激光硬件；模拟测试不能代替真实设备验证。\n');
const collect = directory => readdirSync(directory).flatMap(name => {
  const path = join(directory, name);
  return statSync(path).isDirectory() ? collect(path) : [path];
});
const files = collect(target);
assert(!files.some(path => /Customer-Demo-Script|node_modules|\.DS_Store/.test(path)));
const archive = join(workspace, `${folder}.zip`);
const stagedArchive = join(workspace, `${folder}.building-${process.pid}.zip`);
assert(!existsSync(stagedArchive));
execFileSync('python3', [join(source, 'scripts/zip-delivery.py'), stagedArchive, workspace, folder]);
execFileSync('/usr/bin/unzip', ['-tq', stagedArchive]);
renameSync(stagedArchive, archive);
// Refresh the familiar demo ZIP too, using an explicit list that excludes the old speech script.
const demoFiles = ['index.html', ...(chinese ? ['english.html'] : []), '使用说明.md', '实现说明.md', '字号与颜色规格.md', ...readdirSync(join(release, 'assets')).map(name => `assets/${name}`)];
const stagedDemo = join(workspace, `${releaseName}.building-${process.pid}.zip`);
assert(!existsSync(stagedDemo));
execFileSync('python3', [join(source, 'scripts/zip-delivery.py'), stagedDemo, workspace,
  ...demoFiles.map(name => `${releaseName}/${name}`)]);
execFileSync('/usr/bin/unzip', ['-tq', stagedDemo]);
renameSync(stagedDemo, join(workspace, `${releaseName}.zip`));
console.log(`Engineering package: ${archive}\nFiles: ${files.length}\nBytes: ${statSync(archive).size}`);

}
