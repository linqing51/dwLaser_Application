# 病历功能 UI 行为规格 — 覆盖 GDDC_PAGE_LIST_TREATMENT 等 11 个病历相关页面

本文件固化 11 个病历相关页面（页面清单见第十六节 16.1）的**强制交互行为**，涵盖 `GDDC_PAGE_LIST_TREATMENT` 的页码、搜索、关闭按钮、患者选择闭环、删除患者确认，`GDDC_PAGE_OPERATOR_USB` 及导出/导入确认页，`GDDC_PAGE_VERIFY_TREATMENT` 核对页的患者信息录入与保存，以及全部病历页面的**按键互锁**（第十六节）。任何 AI 维护这些页面前必须先读完本文件，并按此实现，不得擅自更改匹配口径、排序规则、显示格式、页面跳转出口、患者选择归属、删除确认流程与按键互锁规则。

> **最高优先级规格（2026-11-20）：导出后机内病历数据不清空。** 从设备导出病历到 U 盘后，机内患者表与治疗记录必须完整保留，不得删除或清空。本规格优先于任何软件功能改动与页面文案；确需“导出后清空本机病历”时，必须**先修改本规格并经用户明确确认**，之后才允许进行软件修改。任何 AI 不得擅自在导出流程中加入清空逻辑（详见第八节）。

- 实现位置：`MainApp/dcHmiApp.c`（过滤/排序/刷新）、`dcHmiNotifyButton.c`（按钮）、`dcHmiNotifyText.c`（文本输入）
- 控件 ID 定义：`MainApp/dcHmiRes.h`
- 每页固定显示 `LIST_TREATMENT_WINDOW_SIZE = 5` 个患者；患者数与记录数**无任何业务硬上限**，两表按剩余空间（`FreeBytesPR`）动态致密增长，总量上限即病历区块物理容量。RAM 侧不恢复按业务上限定尺寸的整行大数组，仅保留：
  - **紧凑排序索引** `sortedIndex`（`uint16`，2 字节/患者，按物理容量 `TREATMENT_PHYSICAL_PATIENT_CAP` 定尺寸，最坏 4710 字节），只存全局索引、不存整行；翻页/选择经该索引 O(1) 定位。
  - **RAM 排序键 + 患者表批量读**：重建时用 `treatmentPatientReadRows()` 分块连续批量读患者表（每块 16 行、1 次 FRAM 事务，地址自增），把命中患者的“全局索引 + 姓名”写入固定大小的 `ramKeys`（256 个），随后在 RAM 内纯 CPU 堆排序、排序过程零 FRAM 回读，再生成 `sortedIndex`。命中数超过 256 时自动回退到 FRAM 堆排序（正确、仅更慢）——这是 RAM 策略阈值，不是业务上限，不限制写入。
  - 记录侧仍用 2 字节 id 轻读（替代整行 28 字节），完整行仅在渲染时才读。

---

## 一、页码文本框 GDDC_PAGE_LIST_TREATMENT_TEXT_PAGE_NUM（控件 ID 18）

1. 显示当前窗口在“过滤后患者视图”中的页码，**格式固定为 `PAGE 当前页/总页数`**，例如 `PAGE 2/3`。
2. 总页数 = `ceil(filteredCount / 5)`（整数向上取整）；**空视图（0 个患者）强制按 1 页显示，输出 `PAGE 1/1`，严禁出现 `0/0`**。
3. 当前页 = `topIndex / 5 + 1`。
4. `topIndex` 必须恒为 5 的整数倍（整页对齐）：任何路径改完 `topIndex` 后，由 `listTreatmentClampWindow` 先向下对齐到整页边界、再夹到合法上限 `listTreatmentGetMaxTop()`，保证页码与窗口位置一致、且“上一页/下一页”按钮不会失效。
5. 所有会改变窗口或过滤的路径（翻页、搜索、新建、删除、U 盘导入、返回列表）都必须调用 `refreshListTreatmentDisplay()`，以同步刷新该文本框。
6. **U 盘导入（整体替换 EPROM）后必须先重建过滤**：导入会清空并改写全部患者/记录，RAM 中的 `filteredCount`、`sortedIndex`、`ramKeys` 是导入前的旧值；从 USB 流程返回列表页（`listTreatmentOperatorUsbBack`）时必须先 `listTreatmentRebuildFilter()`（按当前 `findText` 重建，保留搜索与窗口）再 `refreshListTreatmentDisplay()`，否则会显示空白/旧数量，只能关闭重进才正常。

---

## 二、搜索框 GDDC_PAGE_LIST_TREATMENT_TEXT_SEARCH_NAME 与姓名列 TEXT_NAME_0–4

1. **前缀匹配、大小写敏感（不忽略大小写）**：搜索框输入按姓名前缀**逐位直接比较**，任一位大小写不同即不匹配，输入字母全部命中才匹配；空串 = 不过滤、显示全部患者。
   - 输入小写 `l` 只命中小写 l 开头的姓名，**不**命中大写 `L` 开头；输入 `li` 只命中 `li` 开头的姓名。
   - 实现沿用 `listTreatmentMatchFind`，比较时直接 `name[i] != findText[i]`，不做大小写归一。
2. **大小写敏感的 ASCII 字典序全序排序**：命中结果必须先按字符原始值（ASCII）排序，再写入 `GDDC_PAGE_LIST_TREATMENT_TEXT_NAME_0–4`：
   - 从第一个不同的字符位决定先后，**大写字母（A–Z，码值 65–90）整体排在小写字母（a–z，97–122）之前**；短名先结束（如 `li` 排在 `linqing` 之前）。
   - 姓名比较沿用 `listTreatmentCompareName`，直接按原始字节 `(uint8_t)` 比较，不做大小写归一；姓名完全相同时，由 `listTreatmentOrderCmp` 再按患者原始存储索引决定先后。即排序键为“姓名 → 原始存储索引”的**全序键**，以原始索引为最终 tie-break，保证结果唯一确定；大顶堆排序本身不要求稳定，全序键已消除并列，无需依赖排序算法的稳定性。
3. **多字母前缀**：先按输入的多个字母过滤，再按其后一位字母继续字典序比较；本质仍是“前缀匹配 + 全名字典序”。
4. **患者表批量读 + RAM 内排序，翻页/选择零重扫**：`listTreatmentRebuildFilter()` 用 `treatmentPatientReadRows()` 分块连续批量读患者表（每块 16 行、单次 FRAM 事务、地址自增，替代逐行各一次事务），单遍把命中患者的全局索引收集到 `sortedIndex`、并把“全局索引 + 姓名”写入 RAM 键 `ramKeys`。命中数 ≤ 256 时由 `listTreatmentSortKeys()` 做**原地大顶堆排序**（无递归、栈占用恒定，纯内存比较、零 FRAM 回读，O(N log N)），再生成 `sortedIndex`；超过 256 则回退 `listTreatmentSortIndices()` 的 FRAM 堆排序。此后任意翻页、选择都直接经 `sortedIndex` O(1) 定位，不再重复扫描；仅在数据变化（新建/删除/U 盘载入）或查找字母变化时才重建。256 是 RAM 策略阈值而非业务上限，写入不受限。

### 标准示例（5 个用户：linqing, lijing, ksfjing, harqig, larsein）

| 搜索输入 | TEXT_NAME_0–4 显示顺序 |
|---|---|
| `l` | larsein, lijing, linqing |
| `k` | ksfjing |
| `h` | harqig |
| `li` | lijing, linqing |
| `lin` | linqing |
| `la` | larsein |
| 空串 | 全部患者，按字典序 |
| `L`（大写） | 无匹配（5 个用户均为小写，大小写敏感） |

**大小写混合排序补充**：若同时存在 `Linqing`、`lijing`、`Ksfjing`，空串（显示全部）时按 ASCII 码值排序为 `Ksfjing`（K=75）、`Linqing`（L=76）、`lijing`（l=108），即大写开头者整体排在小写开头者之前。

---

## 三、关闭按钮 GDDC_PAGE_LIST_TREATMENT_KEY_CLOSE（控件 ID 38）

1. 点击该按钮必须回到待机页 `GDDC_PAGE_STANDBY`，不得跳到其他页面、也不得仅关闭弹窗而停留原页。
2. `GDDC_PAGE_STANDBY` 是板级别名，在 G5 工程 `config/G5_TRI_A1_20260915/AppConfig.h` 中映射为 `GDDC_PAGE_STANDBY_DUAL_1470_635`；维护时一律引用 `GDDC_PAGE_STANDBY`，不要硬编码具体板型待机页。
3. 实现统一走 `returnStandbyDisplay()`：把状态机切回 `FSMSTEP_STANDBY`、显式写入 `NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY`，先 `updateStandbyDisplay()` 预刷新再 `SetScreen()`，避免目标页控件残留。
4. 本要求为**强制规格，任何时刻打开/维护此页都必须保留此行为**，不得改为返回其他页面或删除该退出出口。

---

## 四、USB 操作页 GDDC_PAGE_OPERATOR_USB（页面 ID 19）与导出/导入确认页（页面 ID 20/21）

### 4.0 操作页 GDDC_PAGE_OPERATOR_USB（页面 ID 19）

本节为**新增强制规格**，与旧描述冲突时以本节为准。控件编号必须与屏幕工程 `vTFT_HMI/GDDC_PAGE_OPERATOR_USB.tft` 完全一致（`GDDC_PAGE_OPERATOR_USB_TEXT_SUMMARY` = 1、`GDDC_PAGE_OPERATOR_USB_TEXT_SUMMARY_USB` = 2、`GDDC_PAGE_OPERATOR_USB_KEY_SAVE_UDISK` = 3、`GDDC_PAGE_OPERATOR_USB_KEY_LOAD_UDISK` = 4、`GDDC_PAGE_OPERATOR_USB_KEY_CLOSE` = 5）；若宏值被改成 10/11/12 等与屏幕工程不符的编号，按键事件无法命中，表现为按键无响应。

1. 列表页 `GDDC_PAGE_LIST_TREATMENT_KEY_OPERATOR_USB`（控件 40）按下（`state = 1`）调用 `enterOperatorUsbPage()`：置 `NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LIST_TREATMENT`、`NVRAM0[EM_DC_PAGE] = GDDC_PAGE_OPERATOR_USB`，先 `refreshOperatorUsbDisplay()` 预刷新本页控件，再 `SetScreen(GDDC_PAGE_OPERATOR_USB)`，避免上一页控件残留。
2. `GDDC_PAGE_OPERATOR_USB_TEXT_SUMMARY`（控件 1）显示机内病历储存概况，**文本控件内的显示内容一律英文**（英文显示为全工程至高规格，适用范围与人工授权要求见根目录 `AI_RULES.md`），格式固定为 `Existing patients: X, total treatment records: Y`，即“现有患者数量X，累计历史治疗记录Y”的英文表述：
   - `X` = `treatmentEpromGetPatientCount()`，机内去重患者数；
   - `Y` = `listTreatmentGetCount()`（即 `NVRAM0[DM_TREATMENT_NUM]`，负值防御返回 0），累计历史治疗记录数。
   - 该文本框在进入本页与页面冷加载完成时都必须刷新，不受列表页搜索过滤影响（全局口径）。
   - 文案为纯 ASCII，不存在屏幕字库中文编码（GB2312/UTF-8）不匹配导致乱码的风险。
3. `GDDC_PAGE_OPERATOR_USB_TEXT_SUMMARY_USB`（控件 2）在进入本页时显示 U 盘在位状态：`UDISK OK` / `NO UDISK`；导出/导入完成后显示本次结果，从确认页取消返回时清空。其内容统一由 `listTreatmentCtx.usbText` 维护、经 `refreshOperatorUsbDisplay()` 下发，页面冷加载重发同一内容，不会被在位状态覆盖；从列表页重新进入本页时才恢复为在位状态。
4. `GDDC_PAGE_OPERATOR_USB_KEY_SAVE_UDISK`（控件 3）按下调用 `listTreatmentSaveUsbStart()`，进入导出确认页 `GDDC_PAGE_OPERATOR_USB_SAVE`，不得直接读写 U 盘。
5. `GDDC_PAGE_OPERATOR_USB_KEY_LOAD_UDISK`（控件 4）按下调用 `listTreatmentLoadUsbStart()`，进入导入确认页 `GDDC_PAGE_OPERATOR_USB_LOAD`，不得直接覆盖机内病历。
6. `GDDC_PAGE_OPERATOR_USB_KEY_CLOSE`（控件 5）按下调用 `listTreatmentOperatorUsbBack()`：不改动 EPROM，置 `NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_TREATMENT`，刷新列表后 `SetScreen(GDDC_PAGE_LIST_TREATMENT)`，返回上一级病历列表页。
7. 进入本页时 `usbState` 必须为 0（空闲），否则触摸总闸会屏蔽按键。

### 4.1 确认页通用约定

导出确认页 `GDDC_PAGE_OPERATOR_USB_SAVE` 与导入确认页 `GDDC_PAGE_OPERATOR_USB_LOAD` 分别独立，由 `listTreatmentCtx.usbOp` 区分流程（`1` = 导出 SAVE，`2` = 导入 LOAD）；两个确认页上的文字按根目录 `AI_RULES.md` 至高规格**一律英文显示**。`GDDC_PAGE_OPERATOR_USB_KEY_SAVE_UDISK` / `GDDC_PAGE_OPERATOR_USB_KEY_LOAD_UDISK` **都不立即读写 U 盘**，先进入对应确认页。

### 4.2 导出 SAVE（usbOp = 1，点 GDDC_PAGE_OPERATOR_USB_KEY_SAVE_UDISK）

1. 进入时刷新以下两个文本框（屏幕工程该页只有控件 1、2；文案为英文，中文语义见括注）：
   - `GDDC_PAGE_OPERATOR_USB_SAVE_TEXT_SUMMARY_0`（控件 1，动态）：`Export X patients and Y saved treatment records to USB?`
     - “确认将共 X 位患者及共 Y 条已保存的治疗记录导出至 USB？”
     - `X` = 机内患者数 `treatmentEpromGetPatientCount()`；`Y` = 机内治疗记录数 `listTreatmentGetCount()`（即 `NVRAM0[DM_TREATMENT_NUM]`，负值防御返回 0），取**进入本页时**的机内当前值。
   - `GDDC_PAGE_OPERATOR_USB_SAVE_TEXT_SUMMARY_1`（控件 2）：`The existing patient backup in this USB will be replaced.`
     - “此 USB 中的原有患者备份将被替换。”
   - 原 `GDDC_PAGE_OPERATOR_USB_SAVE_TEXT_SUMMARY_2/3` 文案作废，本页不再向控件 3/4 写入。
2. `GDDC_PAGE_OPERATOR_USB_SAVE_KEY_CANCEL`（控件 10）：取消写入，不修改 U 盘与机内 EPROM，返回操作页 `GDDC_PAGE_OPERATOR_USB`，并**清空**该页 `GDDC_PAGE_OPERATOR_USB_TEXT_SUMMARY_USB`（写空串）；该页 `GDDC_PAGE_OPERATOR_USB_TEXT_SUMMARY` 保持进入本页前显示的内容不变。
3. `GDDC_PAGE_OPERATOR_USB_SAVE_KEY_OK`（控件 11）：授权把机内病历转换成 CSV 写入 U 盘，复用 `treatmentLogSaveToUdisk`，文件名由 `TREATMENTLOG_FILENAME` 宏指定（`/treatment_v1.csv`，覆盖同名文件）；实际写入在 `listTreatmentUsbLoop` 中执行一次，不在按键回调里阻塞。
4. 写入完成后自动返回 `GDDC_PAGE_OPERATOR_USB`，并在 `GDDC_PAGE_OPERATOR_USB_TEXT_SUMMARY_USB`（控件 2）显示本次备份概况：
   - 成功：`USB backup: X patients, Y treatment records`
     - `X` = 机内患者数 `treatmentEpromGetPatientCount()`；`Y` = 本次实际写入 U 盘的治疗记录数 `listTreatmentCtx.usbCount`。
   - 失败按错误码：`NO UDISK` / `NO RECORDS` / `USB OPEN FAILED` / `USB BACKUP FAILED`
5. 结果栏内容统一保存在 `listTreatmentCtx.usbText`，由 `refreshOperatorUsbDisplay()` 下发；因此回到操作页后的页面冷加载刷新不会把结果覆盖成 `UDISK OK`。重新从列表页进入操作页时，`usbText` 恢复为 U 盘在位状态（`UDISK OK` / `NO UDISK`）。
6. 导出流程**只写 U 盘、不删除机内病历**（强制规格，见第八节，优先于任何功能改动）；确认页只提示 U 盘原有备份将被替换，**不得出现任何“设备档案将被清除”的文案**，也不得据此实现清空。

### 4.3 导入 LOAD（usbOp = 2，点 GDDC_PAGE_OPERATOR_USB_KEY_LOAD_UDISK）

1. 进入时刷新以下两个文本框（屏幕工程该页只用控件 1、2；`X`/`Y` 取**进入本页时**的机内当前值）：
   - `GDDC_PAGE_OPERATOR_USB_LOAD_TEXT_SUMMARY_0`（控件 1，动态）：`Replace all X patients and Y treatment records on the device with the USB backup?`
     - “确认用 USB 的备份替换设备中全部 X 位患者及 Y 条治疗记录？”
     - `X` = 机内患者数 `treatmentEpromGetPatientCount()`；`Y` = 机内治疗记录数 `listTreatmentGetCount()`（即 `NVRAM0[DM_TREATMENT_NUM]`，负值防御返回 0）。
   - `GDDC_PAGE_OPERATOR_USB_LOAD_TEXT_SUMMARY_1`（控件 2，动态）：`Backup contents: X patients, Y treatment records.`
     - “备份内容：X 位患者, Y 条治疗记录。”，数值与上一条同源。
   - 原 `GDDC_PAGE_OPERATOR_USB_LOAD_TEXT_SUMMARY_2/3` 文案作废：控件 3 下发空串避免残留，控件 4 不写入（屏幕未建）。
2. `GDDC_PAGE_OPERATOR_USB_LOAD_KEY_CANCEL`（控件 10）：取消载入，不读写 U 盘、不修改机内 EPROM，返回操作页 `GDDC_PAGE_OPERATOR_USB`（与导出共用 `listTreatmentUsbCancel()`，返回时同时清空该页 `GDDC_PAGE_OPERATOR_USB_TEXT_SUMMARY_USB`）。
3. `GDDC_PAGE_OPERATOR_USB_LOAD_KEY_OK`（控件 11）：授权从 U 盘读取由 `TREATMENTLOG_FILENAME` 宏指定文件名的 CSV（`/treatment_v1.csv`）并载入本机病历空间，复用 `treatmentLogLoadFromUdisk`；实际读写在 `listTreatmentUsbLoop` 中执行一次，不在按键回调里阻塞。**授权后该键立即 `SetControlEnable(...,0)` 物理禁用，读取过程中重复按下不产生任何通知；读取与回读核对完成、恢复使能后才返回操作页**（见 4.4）。
4. 载入完成后自动返回 `GDDC_PAGE_OPERATOR_USB`，**必须再回读核对**：`treatmentLogVerifyUdisk()` 重新打开 U 盘同一 CSV，按索引逐条与本机 EPROM 病历比较全部字段（ID/姓名/性别/年龄/功率/波长/方案/能量/治疗时间），并要求 U 盘数据行数与机内条数完全一致。`GDDC_PAGE_OPERATOR_USB_TEXT_SUMMARY_USB`（控件 2）按下述口径显示：
   - 载入成功**且**回读比较完全相同：`Backup imported from USB. Device records have been replaced.`（“已从 USB 导入备份，设备档案已替换。”）
   - 载入失败，**或**比较存在任何差异（U 盘拔出、文件读不出、行数不一致、任一字段不同）：`USB backup import failed!`（“导入USB备份失败!”）
   - 旧口径（按 `TREATMENT_USB_ERR_*` 分别显示 `NO UDISK` / `NO FILE` / `BAD FILE` / `USB IMPORT FAILED`）作废，统一为上面两条。
5. 结果栏内容同样存入 `listTreatmentCtx.usbText`，由 `refreshOperatorUsbDisplay()` 下发，回到操作页后的冷加载刷新不会覆盖结果；返回时操作页 `GDDC_PAGE_OPERATOR_USB_TEXT_SUMMARY` 按载入后的机内数量刷新。

### 4.4 通用触摸与状态约束

1. 确认页等待期间（状态 6）只放行本页 `GDDC_PAGE_OPERATOR_USB_SAVE_KEY_CANCEL`/`GDDC_PAGE_OPERATOR_USB_LOAD_KEY_CANCEL` 与 `GDDC_PAGE_OPERATOR_USB_SAVE_KEY_OK`/`GDDC_PAGE_OPERATOR_USB_LOAD_KEY_OK`，读写执行期间（状态 7）屏蔽一切触摸。
2. **读写期间确认页两键必须物理禁用（强制）**：`listTreatmentUsbConfirm`（状态 6→7）在切页前对本页 `GDDC_PAGE_OPERATOR_USB_SAVE_KEY_OK`/`GDDC_PAGE_OPERATOR_USB_LOAD_KEY_OK`（控件 11）、`GDDC_PAGE_OPERATOR_USB_SAVE_KEY_CANCEL`/`GDDC_PAGE_OPERATOR_USB_LOAD_KEY_CANCEL`（控件 10）下发 `SetControlEnable(...,0)`（CANCEL 同时先 `SetButtonValue(0)`），使读写过程中即使反复按下也不产生任何触摸通知——既禁止中途取消，也禁止重复按确认键持续下发 `state=1`。读取/写入完成后，在返回操作页之前先弹起确认键、解除互锁，并对两键 `SetControlEnable(...,1)` 恢复使能，再 `SetScreen` 回操作页。
3. 确认/取消回调导出/导入通用：`listTreatmentUsbConfirm`（状态 6→7）、`listTreatmentUsbCancel`（状态 6→0 回操作页）。
4. 若确认页被别处切走（如关机确认/休眠），轮询检测到当前页不符即放弃本次流程、弹起两键并恢复使能后退出忙状态，避免触摸被永久屏蔽。

---

## 五、患者选择闭环（`GDDC_PAGE_STANDBY_KEY_ENTER_TREATMENT` / `GDDC_PAGE_LIST_TREATMENT_KEY_SELECT_PATIENT_0–4` / `GDDC_PAGE_STANDBY_TEXT_PATIENT_NAME`）

本部分固化“待机页进入列表 → 选中患者 → 自动返回待机并显示患者名 → 后续病历归属该患者”的完整闭环。涉及控件：待机页 `GDDC_PAGE_STANDBY_KEY_ENTER_TREATMENT`（控件 46）、待机页 `GDDC_PAGE_STANDBY_TEXT_PATIENT_NAME`（控件 39）、列表页 `GDDC_PAGE_LIST_TREATMENT_KEY_SELECT_PATIENT_0–4`（控件 20–24）。

### 5.1 待机页进入列表页（已实现，必须保留）

1. 在待机页点 `GDDC_PAGE_STANDBY_KEY_ENTER_TREATMENT`（控件 46），按钮回调只置标志 `R_STANDBY_KEY_ENTER_LIST_TREATMENT_DOWN`。
2. 主循环待机状态机检测到该标志后：置 `FSMSTEP_LIST_TREATMENT`、`NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_TREATMENT`，先 `enterListTreatmentPage()` 重建患者视图并刷新，再 `SetScreen(13)`，随后清除进入标志。
3. 该入口行为为强制规格，不得改为直接进编辑页或其他页面。

### 5.2 列表页选中患者并自动返回待机页

1. 点 `GDDC_PAGE_LIST_TREATMENT_KEY_SELECT_PATIENT_0–4`（控件 20–24）调用 `listTreatmentSelect(slot)`，其中 `slot = control_id - GDDC_PAGE_LIST_TREATMENT_KEY_SELECT_PATIENT_0`（取值 0–4），分别对应窗口内 `GDDC_PAGE_LIST_TREATMENT_TEXT_NAME_0–4` 的患者。
2. `slot` 越界（`>= 5`）直接返回；对应视图位置 `viewPos = topIndex + slot` 若 `>= filteredCount`（空槽位）则不响应。
3. 命中有效患者时，`listTreatmentSelect` 必须依次完成：
   - 置 `selectedIndex = viewPos` 记录列表内选中位置；该字段仅作内部状态使用，不再驱动 `GDDC_PAGE_LIST_TREATMENT_KEY_SELECT_PATIENT_0–4` 按钮高亮。
   - 经 `listTreatmentGetViewPatient(viewPos, &pat)`（经紧凑索引 `sortedIndex[viewPos]` O(1) 定位全局索引，再单次回读整行）解析出患者原始记录，把稳定患者编号缓存到 `listTreatmentCtx.selectedPatientId`、姓名缓存到 `listTreatmentCtx.selectedPatientName`。
   - **自动返回待机页**：统一走 `returnStandbyDisplay()`（切回 `FSMSTEP_STANDBY`、`SetScreen(GDDC_PAGE_STANDBY)`），不得停留在列表页，也不得进入编辑页。

### 5.3 待机页 TEXT_PATIENT_NAME 显示选中患者名

1. 待机页患者名由 `updateStandbyDisplay()` 统一刷新（`returnStandbyDisplay()` 会先调用它预刷新），保证任何路径回到待机页显示都一致：
   - `selectedPatientId != 0`（已选患者）：`SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_PATIENT_NAME, selectedPatientName)`，显示刚选中的患者名字。
   - `selectedPatientId == 0`（开机后尚未选择）：向该控件写空串清空，**不得残留上一次/屏幕工程默认内容**。
2. 显示内容为患者姓名原文（`patientRecord_t.name`），不追加编号、不做大小写转换。

### 5.4 后续病历在该患者名下储存

1. 患者选择确立后，后续治疗记录通过 `selectedPatientId` 关联，**不新增 EPROM 寄存器**：`selectedPatientId`/`selectedPatientName` 与窗口、搜索等运行状态一致，放在 `listTreatmentCtx`（RAM/ZI 段），开机为 0（未选择），不做掉电持久化。
2. 保存沿用现有 `GDDC_PAGE_LIST_TREATMENT_KEY_CREATE_NEW` → 编辑页 → `GDDC_PAGE_EDIT_PATIENT_KEY_OK` 链路，`listTreatmentCreateStart()` 按是否已选患者分两条路径：
   - **已选患者（`selectedPatientId != 0`，老患者路径）**：先用 `treatmentPatientFind` + `treatmentPatientGetByIndex` 按 id 取出该患者，把 `treatmentLog` 的 `id`/`name`/`age`/`gender` 预填为该患者，**不清空患者信息、不新建患者**；`GDDC_PAGE_EDIT_PATIENT_KEY_OK` 后 `treatmentEpromAdd` 因该 id 已存在（`treatmentPatientFind` 成功），直接把治疗记录以该 `patientId` 为外键追加，归属到选中患者名下。
   - **未选患者（`selectedPatientId == 0`，新患者路径）**：保持既有行为，清空 `name`/`age`/`gender`、`id = 0` 占位，在编辑页录入后由 `treatmentEpromAdd` 自动新建患者并分配新 id。
3. 本闭环为强制规格：选中患者后任何保存路径都不得再为该次治疗新建重复患者；同一患者的多次治疗只在其名下追加记录，患者主表中该患者仍只出现一次。

### 5.5 以一次 ready 会话为单位的病历保存与核对页自动归属（强制规格，2026-11-25 修订）

本节固化病历记录的保存口径：**记录单位是一次 ready 会话，不是单次脚踏发射周期**；保存的是整个 ready 期间累计的发射时间/能量。与 5.4 的旧 CREATE 链路相互独立，激光流程以本节为准。

1. **ready 会话边界与累计口径**：
   - 进入 ready（`updateReadyDisplay`）时 `clearReleaseTimeEnergy()` 清零一次发射计数；此后整个 ready 期间（含多次踩下/弹起脚踏）`EM_LASER_TRIG_TIME` 等持续累加。脚踏弹起只是从 `FSMSTEP_LASER_EMITING` 回到 `FSMSTEP_LASER_WAIT_TRIGGER`，**不清零、不弹核对页**，用户可继续踩脚踏，发射时间/能量在原有基础上继续累加。
   - 因此单次脚踏弹起（发射→等待触发）不再触发核对页，也不产生独立记录；同一 ready 内的多次发射合并为一条记录。
2. **退出 ready 回待机时才弹一次核对页**：用户点 `GDDC_PAGE_READY_KEY_READY`（置 `R_STANDBY_KEY_STNADBY_UP`）正常退出 ready 时，`listTreatmentExitReadyVerify()` 调 `listTreatmentPendingCapture()`，用整个 ready 期间的累计值抓一次快照（含退出瞬间 RTC 时间戳）：
   - 整个 ready 确有发射（`EM_LASER_TRIG_TIME > 0`，`pendingValid = 1`）：调 `listTreatmentVerifyAfterLaser()` 把累计快照载入 `treatmentLog` 并进入核对页 `GDDC_PAGE_VERIFY_TREATMENT`（页面 22），整个 ready 只弹这一次。
   - 整个 ready 没有发射（`EM_LASER_TRIG_TIME = 0`，`pendingValid = 0`）：**不进入 `GDDC_PAGE_VERIFY_TREATMENT`、不进行患者新建或选择后储存**，直接经 `returnStandbyDisplay()` 回待机页。
   - 急停（`X_ESTOP_NC`）、故障（`R_FAULT`）、`FSMSTEP_READY_ERROR` 等异常退出路径不弹核对页，按原导航立即回待机，不打断安全处置。
3. **自动预填已选患者（不新建患者）**：`listTreatmentVerifyAfterLaser` 默认置 `treatmentLog.id = 0`，随后调 `listTreatmentPrefillSelectedPatient()`：
   - **已选患者（`selectedPatientId != 0`）且该患者仍存在**：经 `treatmentPatientFind` + `treatmentPatientGetByIndex` 取出该患者，把 `treatmentLog` 的 `id`/`name`/`age`/`gender` 覆盖为该患者，本次 ready 的累计治疗即自动选定储存在其名下，无需再手动选患者。
   - **未选择或选中患者已被删除（查不到）**：保持 `id = 0`，回退新患者路径，避免外键悬空。
4. **核对页各控件显示该 ready 的累计信息**：`listTreatmentRefreshVerifyDisplay` 必须按下表渲染，字段口径与本规格其他章节对该页的描述一致：
   - `GDDC_PAGE_VERIFY_TREATMENT_TEXT_ID`（控件 1）：已选患者显示其**真实 ID**（`treatmentLog.id`，4 位补零），不再显示新患者的建议 ID；仅 `id = 0` 时才显示预生成最小空缺 ID。
   - `GDDC_PAGE_VERIFY_TREATMENT_TEXT_NAME`（2）、`GDDC_PAGE_VERIFY_TREATMENT_TEXT_AGE`（3）、`GDDC_PAGE_VERIFY_TREATMENT_TEXT_GENDER`（9）及 `GDDC_PAGE_VERIFY_TREATMENT_MENU_GENDER`（20）：显示该患者姓名、年龄、性别（`Male`/`Female`，菜单男性在前，口径同 17.4）。
   - `GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_TIME`（4）：显示治疗结束 RTC 时间戳，格式 `YYYY-MM-DD HH:MM`（退出 ready 瞬间盖章，完整 4 位年）。
   - `GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_ENERGY`（5）、`GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_OUT_TIME`（6）、`GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_POWER`（7）、`GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_SCHEME`（8）：显示**整个 ready 累计**的发射能量、发射时长，以及功率、方案，口径同该页既有规则。
5. **SAVE_RECORD 确认储存**：点 `GDDC_PAGE_VERIFY_TREATMENT_KEY_SAVE_RECORD`（控件 30）：
   - `treatmentLog.id != 0`（已选患者）：直接调 `treatmentEpromAddToPatient(treatmentLog.id, &treatmentLog)`，以该患者为外键追加本次 ready 的累计治疗记录、**不新建患者**，随后清待存并经 `returnStandbyDisplay()` 回待机页。
   - `treatmentLog.id == 0`（新患者）：**在本页直接录入姓名/年龄/性别并校验落盘，不跳注册页**，完整流程见 5.6。
6. 本链路为强制规格：病历以 ready 会话为单位累计保存，脚踏弹起不弹页、不拆记录；只要已选患者且其仍存在，退出 ready 后核对页即默认归属该患者，SAVE_RECORD 不得再为本次治疗新建重复患者。

### 5.6 核对页 GDDC_PAGE_VERIFY_TREATMENT（页面 22）本页录入患者信息与 SELECT_TREATMENT 选择已有患者（强制规格，2026-11-25 修订）

本节固化 `GDDC_PAGE_VERIFY_TREATMENT` 的全部控件、本页直接录入患者姓名/年龄/性别的强制流程，以及 `GDDC_PAGE_VERIFY_TREATMENT_KEY_SELECT_TREATMENT` 经列表页选择已有患者的完整闭环。**患者信息在本页直接录入，点 `GDDC_PAGE_VERIFY_TREATMENT_KEY_SAVE_RECORD` 不再跳转到注册页 `GDDC_PAGE_REGISTER_PATIENT`。**

1. **`GDDC_PAGE_VERIFY_TREATMENT` 控件清单**（控件宏前缀均为 `GDDC_PAGE_VERIFY_TREATMENT`）：

   | 控件完整宏名 | 控件 ID | 类型 | 职责 | 本页可否编辑 |
   |---|---|---|---|---|
   | `GDDC_PAGE_VERIFY_TREATMENT_TEXT_ID` | 1 | 文本（只读） | 显示插空（最小空缺）患者 ID | 否 |
   | `GDDC_PAGE_VERIFY_TREATMENT_TEXT_NAME` | 2 | 文本输入 | 输入患者名字 | **是** |
   | `GDDC_PAGE_VERIFY_TREATMENT_TEXT_AGE` | 3 | 文本输入 | 输入患者年龄 | **是** |
   | `GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_TIME` | 4 | 文本（只读） | 该条记录的生成 RTC 时间 | 否 |
   | `GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_ENERGY` | 5 | 文本（只读） | 本次治疗累计总能量 | 否 |
   | `GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_OUT_TIME` | 6 | 文本（只读） | 本次治疗累计总时间 | 否 |
   | `GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_POWER` | 7 | 文本（只读） | 本次治疗的激光功率 | 否 |
   | `GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_SCHEME` | 8 | 文本（只读） | 本次治疗选择的方案/激光发射模式，显示方式沿用本规格既有定义 | 否 |
   | `GDDC_PAGE_VERIFY_TREATMENT_TEXT_GENDER` | 9 | 文本（只读） | HMI 显示患者性别（`Male`/`Female`），不承担输入 | 否 |
   | `GDDC_PAGE_VERIFY_TREATMENT_MENU_GENDER` | 20 | 菜单（下拉） | 选择患者性别，选择后经 `NotifyMenu` 回写 `treatmentLog.gender` | **是** |
   | `GDDC_PAGE_VERIFY_TREATMENT_KEY_SAVE_RECORD` | 30 | 按键 | 点击后储存 | — |
   | `GDDC_PAGE_VERIFY_TREATMENT_KEY_DISCARD_RECORD` | 31 | 按键 | 放弃储存该次记录 | — |
   | `GDDC_PAGE_VERIFY_TREATMENT_KEY_SELECT_TREATMENT` | 32 | 按键 | 跳 `GDDC_PAGE_LIST_TREATMENT` 选患者后回本页确认 | — |
   | `GDDC_PAGE_VERIFY_TREATMENT_KEY_GENDER` | 33 | 按键 | 展开性别下拉菜单 `GDDC_PAGE_VERIFY_TREATMENT_MENU_GENDER` 的触发键 | — |

2. **本页输入字段（NAME / AGE 文本输入，GENDER 菜单选择，强制流程）**：
   - 姓名、年龄两个文本框直接在本页输入，点击弹出屏幕系统键盘，输入完成经 `NotifyText` 回写 `treatmentLog`：
     - `GDDC_PAGE_VERIFY_TREATMENT_TEXT_NAME`（控件 2）：输入患者名字，口径同 17.4，超长截断到 `CONFIG_TREATMENT_NAME_LEN` 并补字符串结束符。
     - `GDDC_PAGE_VERIFY_TREATMENT_TEXT_AGE`（控件 3）：输入患者年龄，`NotifyText` 用 `sscanf` 转整数回写 `treatmentLog.age`。
   - 性别不在文本框打字：点 `GDDC_PAGE_VERIFY_TREATMENT_KEY_GENDER`（控件 33）展开下拉菜单 `GDDC_PAGE_VERIFY_TREATMENT_MENU_GENDER`（控件 20），菜单选项固定 `Male;Female`（索引 0=Male、1=Female）；选择后经 `NotifyMenu` 把索引映射为 `MALE = 1`/`FEMALE = 2` 回写 `treatmentLog.gender`，并由只读文本 `GDDC_PAGE_VERIFY_TREATMENT_TEXT_GENDER`（控件 9）显示 `Male`/`Female`。
   - 经 `GDDC_PAGE_VERIFY_TREATMENT_KEY_SELECT_TREATMENT` 选中已有患者后，这些字段显示该患者已存资料；保存走 `treatmentEpromAddToPatient` 只追加治疗记录、**不回写患者主表**，修改患者资料必须走 `GDDC_PAGE_EDIT_PATIENT`。
   - 屏幕工程（VisualTFT）须把 `GDDC_PAGE_VERIFY_TREATMENT_TEXT_NAME`/`GDDC_PAGE_VERIFY_TREATMENT_TEXT_AGE` 配置为可输入并关联系统键盘，`GDDC_PAGE_VERIFY_TREATMENT_TEXT_GENDER` 保持只读；固件在 `NotifyText` 增加 `GDDC_PAGE_VERIFY_TREATMENT` 分支处理姓名/年龄回写，性别经现有 `NotifyMenu` 分支处理。

3. **只读摘要字段（SUMMARY，控件 4–8）**：
   - `GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_TIME`（4）：该条记录生成 RTC 时间，格式 `YYYY-MM-DD HH:MM`（退出 ready 瞬间盖章，完整 4 位年）。
   - `GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_ENERGY`（5）：本次治疗累计总能量，格式 `x.x J`（0.1 J 精度）。
   - `GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_OUT_TIME`（6）：本次治疗累计总时间，格式 `MM:SS`。
   - `GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_POWER`（7）：本次治疗激光功率，格式 `x W`。
   - `GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_SCHEME`（8）：本次治疗选择的方案/激光发射模式，固定三种英文格式（强制，2026-11-25 修订）：自定义显 `Custom`；连续模式显 `<方案名> <序号> - CW`；**脉冲模式显 `<方案名> <序号> - Pulse - ON <正脉宽> / OFF <负脉宽> ms`**，其中 `ON` 后取 `treatmentLog.posWidth`（正脉宽）、`OFF` 后取 `treatmentLog.negWidth`（负脉宽），单位均为 ms，与历史记录页 13.2 方案行口径完全一致；脉冲模式不得只显示 `Pulse` 而漏掉正/负脉宽。

4. **三个按键行为**：
   - `GDDC_PAGE_VERIFY_TREATMENT_KEY_SAVE_RECORD`（控件 30）：点击后先在本页校验三字段——姓名非空（`listTreatmentNameValid`）、性别为 `MALE`/`FEMALE`、年龄在 `1 … PATIENT_AGE_LIMIT`：
     - 新患者（`treatmentLog.id = 0`）：校验通过后 `treatmentPatientCreate` 建 24 字节患者（分配最小空缺 ID，与 `GDDC_PAGE_VERIFY_TREATMENT_TEXT_ID` 显示一致），再 `treatmentEpromAddToPatient(newId, &treatmentLog)` 追加 28 字节治疗记录；**成功后把该新患者持久设为当前选中患者（更新 `selectedPatientId = newId`、`selectedPatientName`），再清待存、回待机页**——回待机 `GDDC_PAGE_STANDBY_TEXT_PATIENT_NAME` 即显示其名，且重新选择前再次激光核验经 `listTreatmentPrefillSelectedPatient` 自动归属该患者。**全程不切到注册页 `GDDC_PAGE_REGISTER_PATIENT`。**
     - 已有患者（`treatmentLog.id != 0`）：`treatmentEpromAddToPatient` 先校验患者存在，经 `SplitRecord` 构造 28 字节治疗记录（外键 = 该 id）追加，患者主表 24 字节不变。
     - 校验失败：在本页显示错误提示（不切页、不写盘），用户就地修改后重新保存。
     - 落盘失败（强制）：`treatmentPatientCreate` 或 `treatmentEpromAddToPatient` 返回非 `TREATMENT_EPROM_OK`（如 `TREATMENT_EPROM_ERR_FULL`/IO/欠压）时，在本页 `GDDC_PAGE_VERIFY_TREATMENT_TEXT_MSG` 显示 `Save failed, please retry!`，**保留 `pendingValid` 与待存数据、不回待机、不切页**；新患者若患者已建（`treatmentLog.id` 已为 newId），重试自动走"已有患者"分支，不会重复建患者。
   - `GDDC_PAGE_VERIFY_TREATMENT_KEY_DISCARD_RECORD`（控件 31）：放弃储存该次记录，进入放弃页 `GDDC_PAGE_DISCARD_TREATMENT`，沿用既有放弃/确认流程（见 5.5 及放弃页规格）。
   - `GDDC_PAGE_VERIFY_TREATMENT_KEY_SELECT_TREATMENT`（控件 32）：见第 5 条。

5. **`GDDC_PAGE_VERIFY_TREATMENT_KEY_SELECT_TREATMENT` 选择已有患者完整流程（经 `GDDC_PAGE_LIST_TREATMENT_KEY_SELECT_PATIENT_0–4`）**：
   - 点 `GDDC_PAGE_VERIFY_TREATMENT_KEY_SELECT_TREATMENT`（控件 32）：`listTreatmentVerifySelect` 置 `verifySelectMode = 1`，跳转到列表页 `GDDC_PAGE_LIST_TREATMENT`；该模式用于挑选已有患者，区别于普通列表选中（普通选中经 `returnStandbyDisplay` 回待机页）。
   - **选择患者（强制，2026-11-25 修订为持久归属）**：在列表页点 `GDDC_PAGE_LIST_TREATMENT_KEY_SELECT_PATIENT_0–4`（控件 20–24），其中 `GDDC_PAGE_LIST_TREATMENT_KEY_SELECT_PATIENT_i` 选中当前窗口第 `i` 行患者；`listTreatmentSelect` 的 `verifySelectMode` 分支把该患者 `id`/`name`/`age`/`gender` 填入 `treatmentLog`，清 `verifySelectMode`，**同时更新 `selectedPatientId`/`selectedPatientName` 持久记录本次选择**，再调 `listTreatmentEnterVerifyPage` 回 `GDDC_PAGE_VERIFY_TREATMENT`（本步不立即回待机，先回核对页 SAVE 本次记录）。
   - **持久归属与待机显示（强制）**：选中后该患者即成为当前归属患者——核对页点 SAVE 落盘后经 `returnStandbyDisplay` 回待机，`updateStandbyDisplay` 经 `listTreatmentWriteStandbyPatientName` 在 `GDDC_PAGE_STANDBY_TEXT_PATIENT_NAME` 显示该患者名；**在重新选择患者前，再次激光发射、停光弹核验页时，`listTreatmentVerifyAfterLaser` 经 `listTreatmentPrefillSelectedPatient` 自动回填该患者、记录默认归属其上**（新患者姓名/年龄/性别才空白）。只有再次经 SELECT_TREATMENT 改选、或该患者被删除（删除流程清空 `selectedPatientId`）才改变归属。
   - 回本页后：`GDDC_PAGE_VERIFY_TREATMENT_TEXT_ID` 显该患者真实 ID，`GDDC_PAGE_VERIFY_TREATMENT_TEXT_NAME`/`GDDC_PAGE_VERIFY_TREATMENT_TEXT_AGE`/`GDDC_PAGE_VERIFY_TREATMENT_TEXT_GENDER` 显该患者资料（只读），由用户确认是否在该患者上储存本次记录；点 `GDDC_PAGE_VERIFY_TREATMENT_KEY_SAVE_RECORD` 即按第 4 条“已有患者”路径追加。
   - **列表页 `GDDC_PAGE_LIST_TREATMENT_KEY_CLOSE`（不选择）**：`listTreatmentVerifySelectCancel` 清 `verifySelectMode`、回 `GDDC_PAGE_VERIFY_TREATMENT`（不回待机页），原待存治疗保留。
   - **列表页 `GDDC_PAGE_LIST_TREATMENT_KEY_CREATE_NEW`（不选已有患者、改为新建，强制，2026-11-25 新增）**：在 `verifySelectMode = 1` 下点 `GDDC_PAGE_LIST_TREATMENT_KEY_CREATE_NEW`，`listTreatmentRegisterNewPatient` 清空患者字段（治疗参数保留）、置 `registerReturnPage = GDDC_PAGE_LIST_TREATMENT` 并保持 `verifySelectMode = 1`，进入注册页 `GDDC_PAGE_REGISTER_PATIENT`。在注册页：
     - 点 `GDDC_PAGE_REGISTER_PATIENT_KEY_OK`：`listTreatmentRegisterConfirm` 校验通过后**只 `treatmentPatientCreate` 新建患者，不调用 `treatmentEpromAddToPatient`、不清 `pendingValid`、保持 `verifySelectMode = 1`**，随后经 `listTreatmentGoListPage` 回到列表页 `GDDC_PAGE_LIST_TREATMENT`。
     - 点 `GDDC_PAGE_REGISTER_PATIENT_KEY_CANCEL`：`listTreatmentRegisterCancel` 不写入，按 `registerReturnPage` 经 `listTreatmentGoListPage` 同样回到列表页 `GDDC_PAGE_LIST_TREATMENT`。
     - 两条出口都回到列表页，由操作者在列表中决定是否选中刚才新建的患者；选中后按本项上方“选择患者”路径回填并回核对页，待存治疗记录在核对页点 SAVE 时才落盘，此期间不回待机页、不丢失待存数据。

6. **强制约束与既有控件说明**：
   - 新患者的姓名/年龄经 `GDDC_PAGE_VERIFY_TREATMENT_TEXT_NAME`/`GDDC_PAGE_VERIFY_TREATMENT_TEXT_AGE` 文本输入、性别经 `GDDC_PAGE_VERIFY_TREATMENT_MENU_GENDER` 菜单选择，一律在 `GDDC_PAGE_VERIFY_TREATMENT` 本页完成，`GDDC_PAGE_VERIFY_TREATMENT_KEY_SAVE_RECORD` 不得再跳注册页 `GDDC_PAGE_REGISTER_PATIENT`。
   - `GDDC_PAGE_VERIFY_TREATMENT_KEY_SELECT_TREATMENT` 只改变本次治疗记录的归属患者，不新建患者、不修改任何患者主信息；任何保存路径对已存在患者都只追加一条治疗记录，同一患者在患者主表中仍只出现一次，不得产生重复患者。
   - 性别三控件分工（强制）：`GDDC_PAGE_VERIFY_TREATMENT_MENU_GENDER`（控件 20）是性别选择的唯一输入控件，经 `NotifyMenu` 回写；`GDDC_PAGE_VERIFY_TREATMENT_KEY_GENDER`（控件 33）仅用于展开该下拉菜单；`GDDC_PAGE_VERIFY_TREATMENT_TEXT_GENDER`（控件 9）只读显示 `Male`/`Female`、不承担输入。
   - **进入本页前无条件清空（强制，2026-11-25 新增）**：每次经 `listTreatmentEnterVerifyPage` 进入 `GDDC_PAGE_VERIFY_TREATMENT` 时，渲染函数 `listTreatmentRefreshVerifyDisplay` 在最开头先调用 `listTreatmentClearVerifyFields()`，把 `GDDC_PAGE_VERIFY_TREATMENT_TEXT_NAME`（控件 2）、`GDDC_PAGE_VERIFY_TREATMENT_TEXT_AGE`（控件 3）、`GDDC_PAGE_VERIFY_TREATMENT_TEXT_GENDER`（控件 9）、`GDDC_PAGE_VERIFY_TREATMENT_TEXT_MSG`（控件 10）一律下发空串清空，再按当前 `treatmentLog` 执行“先清后绘”；已选患者的资料会在随后正常回填，新患者则保持空白。`GDDC_PAGE_VERIFY_TREATMENT_TEXT_MSG` 进入时不再显示默认引导语、保持空白，仅在字段校验或落盘失败时显示具体错误，杜绝上一次内容残留。
   - **新患者路径“数据层清空” + 冷加载重发（强制，2026-11-25 新增）**：停光快照 `listTreatmentCtx.pending` 整条复制 `treatmentLog`（`listTreatmentPendingCapture`），可能带着上一次新建患者的姓名/年龄/性别。`listTreatmentVerifyAfterLaser` 先把 `treatmentLog.id` 置 0，再调 `listTreatmentPrefillSelectedPatient`：**当其返回 0（无选中患者、走新患者路径）时，必须把 `treatmentLog.age` 置 0、`gender` 置 0、`name` 清空**，再进入核对页；只有选中患者（返回 1）才回填其资料。同时在 `NotifyScreen` 的 `GDDC_PAGE_VERIFY_TREATMENT` 分支，冷加载完成后重新调用 `listTreatmentRefreshVerifyDisplay` 重发，保证屏幕不残留旧控件值。最终效果：新患者弹出核对页时姓名/年龄/性别一律空白，仅治疗参数（时间/能量/功率/方案）保留。
   - **进入本页三键弹起基线 + 冷加载兜底（强制，2026-11-25 新增）**：上一次点 `GDDC_PAGE_VERIFY_TREATMENT_KEY_SAVE_RECORD` 成功后会立即切回待机，切走瞬间按钮可能停在物理按下态（按下时的释放帧受活动触摸竞争、切页后 state=0 兜底帧又不在当前页），屏幕冷加载重绘核对页时会恢复该按下态，导致再次进入时 SAVE 键卡按下。修复在固件：新增 `listTreatmentReleaseVerifyKeys()`，对 `GDDC_PAGE_VERIFY_TREATMENT_KEY_SAVE_RECORD`（30）、`GDDC_PAGE_VERIFY_TREATMENT_KEY_DISCARD_RECORD`（31）、`GDDC_PAGE_VERIFY_TREATMENT_KEY_SELECT_TREATMENT`（32）一律下发 `SetButtonValue(...,0)`；`listTreatmentEnterVerifyPage` 在切页前先调用一次建立未按下基线，并在 `NotifyScreen` 的 `GDDC_PAGE_VERIFY_TREATMENT` 分支冷加载完成后再调用一次兜底（防止切页前帧被冷加载覆盖）。任何路径进入核对页三键均为弹起态，且不改变使能/灰化。

### 5.7 进入 READY 页画面冻结防闪烁（强制规格，2026-11-25 新增）

点 `GDDC_PAGE_STANDBY_KEY_STANDBY` 从待机进入 `GDDC_PAGE_READY` 时，主循环必须在 `updateReadyDisplay` 预刷新与 `SetScreen` 切页前后用画面更新指令成对包裹，消除整屏重绘造成的“闪一下”：

1. **根因**：`SetScreen` 切换页面时屏幕要加载并绘制新页面（全屏背景图＋全部控件），若不冻结，该清屏/逐元素绘制过程实时可见，肉眼即一次闪烁；该现象在提交 957b3cb8 基线上同样存在，属切页机制固有、而非某次功能改动引入。
2. **强制顺序**（`dcHmiLoop` 进入 READY 分支）：
   - 置 `EM_DC_PAGE = GDDC_PAGE_READY` 后先 `SetScreenUpdateEnable(0)` 禁止画面更新，屏幕保持 STANDBY 静态画面；
   - 冻结期间依次 `readyPageTouchEnable(0)`、`readyKeyValue(1)`、`updateReadyDisplay()` 完成后台 READY 页控件预填，再 `SetScreen(GDDC_PAGE_READY)` 切页——屏幕内部完成加载渲染但不输出；
   - 最后 `SetScreenUpdateEnable(1)` 立即更新，把完整 READY 页（背景图＋已预填控件）一次性重绘，无中间清屏/逐元素过程，故不闪烁。
3. **配对纪律**：冻结期间屏幕仍正常接收并缓存指令，仅暂停视觉输出；`SetScreenUpdateEnable(0)` 与 `(1)` 必须严格成对，中间不得有提前 `return`/`continue` 分支，防止屏幕被永久冻结。

---

## 六、删除患者确认（KEY_DELETE_0–4 / GDDC_PAGE_DELETE_TREATMENT）

本部分固化“列表页删除按钮 → 进入删除确认页 → 确认后级联删除患者及其全部病历”的强制闭环。涉及控件：列表页 `GDDC_PAGE_LIST_TREATMENT_KEY_DELETE_0–4`（控件 25–29）、确认页 `GDDC_PAGE_DELETE_TREATMENT`，确认页按钮 `GDDC_PAGE_DELETE_TREATMENT_KEY_OK`（控件 1）、`GDDC_PAGE_DELETE_TREATMENT_KEY_CANCEL`（控件 2），文本框 `GDDC_PAGE_DELETE_TREATMENT_TEXT_NAME_ID`（控件 3）、`GDDC_PAGE_DELETE_TREATMENT_TEXT_SUMMARY_0`（控件 4）、`GDDC_PAGE_DELETE_TREATMENT_TEXT_SUMMARY_1`（控件 5）、`GDDC_PAGE_DELETE_TREATMENT_TEXT_SUMMARY_2`（控件 6）。页面上所有文字按根目录 `AI_RULES.md` 至高规格一律英文显示。

### 6.1 列表页进入删除确认页（不立即删除）

1. 点 `GDDC_PAGE_LIST_TREATMENT_KEY_DELETE_0–4`（控件 25–29）调用 `listTreatmentDeleteStart(slot)`，`slot = control_id - GDDC_PAGE_LIST_TREATMENT_KEY_DELETE_0`（取值 0–4），分别对应窗口内 `GDDC_PAGE_LIST_TREATMENT_TEXT_NAME_0–4` 的患者。
2. `slot` 越界（`>= 5`）直接返回；`viewPos = topIndex + slot` 若 `>= filteredCount`（空槽位）不响应；视图位置取不到患者也不响应。
3. 命中后把该患者稳定编号缓存到 `listTreatmentCtx.deletePatientId`（非 0 即表示处于删除确认流程），**先只进入确认页、不得在列表页直接删除**；确认页文案（英文）：
   - `GDDC_PAGE_DELETE_TREATMENT_TEXT_NAME_ID`（控件 3，标题）：`Delete Patient?`
   - `GDDC_PAGE_DELETE_TREATMENT_TEXT_SUMMARY_0`（控件 4，动态）：`Delete patient <name> and all their treatment records?`（`<name>` 为该患者姓名原文）
   - `GDDC_PAGE_DELETE_TREATMENT_TEXT_SUMMARY_1`（控件 5，动态）：`This patient has <n> treatment record(s).`（`<n>` = `treatmentGetRecordCountForPatient(id)`，该患者已有病历数）
   - `GDDC_PAGE_DELETE_TREATMENT_TEXT_SUMMARY_2`（控件 6）：`This action cannot be undone.`
4. 置 `NVRAM0[EM_DC_PAGE] = GDDC_PAGE_DELETE_TREATMENT` 后 `SetScreen(GDDC_PAGE_DELETE_TREATMENT)`，等待用户确认或取消。

### 6.2 确认删除（`GDDC_PAGE_DELETE_TREATMENT_KEY_OK`）

1. 点确认页 `GDDC_PAGE_DELETE_TREATMENT_KEY_OK`（控件 1）调用 `listTreatmentDeleteConfirm()`；仅当 `deletePatientId != 0` 时执行。
2. 调用数据层 `treatmentPatientDelete(deletePatientId)` 完成**级联删除**：墓碑并致密该患者的全部治疗记录，再逻辑删除并致密患者表——即同时删除患者名字与其全部历史病历，其他患者 id 与记录保持不变。
3. 删除后必须：
   - 清除 `deletePatientId`（退出删除流程）。
   - 若被删患者正是当前选中患者（`deletePatientId == selectedPatientId`），同时清空 `selectedPatientId`/`selectedPatientName`，避免后续病历外键与待机页患者名悬空。
   - 调用 `listTreatmentRebuildFilter()` + `refreshListTreatmentDisplay()` 重建患者视图（窗口由 `listTreatmentClampWindow` 自动夹取到合法范围），再返回列表页 `GDDC_PAGE_LIST_TREATMENT`。

### 6.3 取消删除（`GDDC_PAGE_DELETE_TREATMENT_KEY_CANCEL`）

1. 点确认页 `GDDC_PAGE_DELETE_TREATMENT_KEY_CANCEL`（控件 2）调用 `listTreatmentDeleteCancel()`；仅当 `deletePatientId != 0` 时执行。
2. 不做任何 EPROM 删除，清除 `deletePatientId`，刷新并返回列表页 `GDDC_PAGE_LIST_TREATMENT`，患者表与病历保持原样。

### 6.4 触摸放行与状态约束

1. 删除确认页等待期间，触摸总闸 `listTreatmentUsbButtonAllowed` 只放行本页 `GDDC_PAGE_DELETE_TREATMENT_KEY_OK`/`GDDC_PAGE_DELETE_TREATMENT_KEY_CANCEL`，其余控件与其他页面触摸一律屏蔽；删除为本地同步操作，在确认回调内一次执行完毕，不设异步忙状态。
2. `deletePatientId` 与其他运行状态一致放 `listTreatmentCtx`（RAM/ZI），开机为 0（不在删除流程），不新增 EPROM 寄存器、不做掉电持久化。
3. 本闭环为强制规格：任何时刻维护都必须保留“先确认后删除”，不得改为点 DELETE 直接删除、不得跳过确认页。

---

## 七、维护约束

- 仅在 `run_treatment` 分支、唯一活跃工程 `targetBoard_G5_TRI_A1_20260915` 内修改；UTF-8 编码与代码风格统一遵循仓库根 `AI_RULES.md`（权威规则主文件）。
- 文本控件英文显示与非 ASCII 符号转换要求已提升为**全工程至高规格**，统一以根目录 `AI_RULES.md` 的“显示文本一律英文、非 ASCII 符号一律转换”条款为准（适用全部页面，修改或开口子须经仓库所有者人工授权）；本文件不再维护局部规则，原中点 `·` 等非 ASCII 分隔符一律改为 ASCII 符号。
- 改动后按 `AI_RULES.md` 第 2 节做 AC5 与 AC6 完整 Rebuild、**两者均 0 Error 才算通过**（AC5 还须正常生成 hex）；无硬件时只能称为“编译级验证”，不得声称上板功能/时序已验证。
- 若控件 ID、页面编号或本文件描述的规则发生变化，必须同步更新本文件，保持规格与代码一致。

---

## 八、导出后机内病历数据保留（最高优先级强制规格）

1. 执行导出（`GDDC_PAGE_OPERATOR_USB_KEY_SAVE_UDISK` → `GDDC_PAGE_OPERATOR_USB_SAVE` → `GDDC_PAGE_OPERATOR_USB_SAVE_KEY_OK`，最终调用 `treatmentLogSaveToUdisk`）后，机内患者表与治疗记录必须**完整保留**，患者数、记录数与导出前一致。
2. 导出流程中**禁止**调用任何删除/清空病历的接口，包括 `treatmentEpromClear()`、`treatmentPatientDelete()`、`treatmentEpromDelete()`，也不得以“释放空间”“防止重复导入”等理由间接清空。
3. 不论 CSV 写入成功、失败，或 U 盘中途拔出，机内数据都不得被修改；失败只允许在操作页结果栏提示错误码。
4. 导出完成返回 `GDDC_PAGE_OPERATOR_USB` 时，`GDDC_PAGE_OPERATOR_USB_TEXT_SUMMARY` 的患者数/记录数照常按机内实际数量刷新（正常情况下与导出前相同）。
5. **本规格优先于任何软件功能改动与页面文案。** 确需“导出后清空本机病历”时，必须先修改本节并经用户明确确认，确认后才允许修改代码；任何 AI 不得擅自添加、预留或预埋清空逻辑。
6. 代码核对（2026-11-20）：`treatmentLogSaveToUdisk` 只按槽位读取并写 CSV，不调用任何删除接口；`treatmentEpromClear()` 现有调用点仅为 `dcHmiLoopInit` 的固件 CRC 变化清空与工程模式“清空 EPROM”，均与导出无关，符合本节要求。

---

## 九、病历数据规则：治疗时刻 RTC 与姓名长度（强制规格）

1. **治疗时刻必须落盘**：每条治疗记录保存“退出 ready 回待机瞬间”（一次 ready 会话结束）的 RTC 时刻（完整 4 位年 + 月/日/时/分/秒），用于病历追溯；不得只保存不显示、也不得留空。
2. 数据结构：RAM 复合视图 `treatmentLog_t` 与片上 `treatmentRecord_t` 均带 `rtcYear/rtcMonth/rtcDay/rtcHour/rtcMinute/rtcSecond`，片上存年份后两位（实际年 = +2000，0 = 未记录）。
3. 采集与保存链路：`listTreatmentPendingCapture()` 在退出 ready 时抓取 RTC 存入待存快照 `listTreatmentCtx.pending`（ready 会话内只在退出时抓一次）；`listTreatmentCreateStart()` 必须把快照的 6 个 RTC 字段回填到 `treatmentLog`，编辑页 `GDDC_PAGE_EDIT_PATIENT_KEY_OK` 后随 `treatmentEpromAdd` 写入 EPROM；漏抓兜底路径（发射时间计数判断）必须用当前 RTC 补齐。
4. **U 盘 CSV 必须带时间并带回**：当前 `rtc` 为第 10 列，格式 `YYYY-MM-DD HH:MM:SS`；未记录时间时该列留空。当前完整表头为 13 列（`id` 加 AR 前缀，`rtc` 后追加 `pulseMode,posWidth,negWidth`），详见第十三至十五节。
   - 导入解析：列数 ≥ 9 即接受，旧版 9 列/10 列备份仍可载入，时间按“未记录”、脉冲按 CW 处理；有新列但格式/范围非法则整行载入失败。
   - 导入回读核对（`treatmentLogVerifyUdisk`）必须同时比较 RTC 6 个字段与脉冲三字段，不允许跳过。
   - 客户端如 Excel 另存，需保持该列格式（空格分隔日期与时间，不拆成两列）。
5. **患者姓名长度 18 个字符**：由 `treatment.h` 的 `CONFIG_TREATMENT_NAME_LEN = 18` 定义，缓冲区 `TREATMENT_NAME_SIZE = 19`（含结束符），`treatmentLog_t.name` 与 `patientRecord_t.name` 共用该长度；固件在姓名录入处按 `TREATMENT_NAME_SIZE - 1` 截断，屏幕输入控件 `text_len_max` 保持 255，以固件截断为准。
6. 姓名长度改变会改变片上患者行尺寸（当前 24 字节），存量病历与新结构不兼容；沿用既有约定——固件 CRC 变化时 `dcHmiLoopInit` 清空整片 EPROM，不做迁移与向后兼容。
7. 本节的 RTC 列与姓名长度属于数据规格，任何后续改动必须先更新本节，并同步 `minicsvApp.c` 的列定义（`TREATMENT_CSV_COLUMNS_MIN` / `TREATMENT_CSV_COLUMNS_RTC` / `TREATMENT_CSV_COLUMNS`）与 `treatmentCsvHeader`。
8. **字段字节偏移一律用 `offsetof`，禁止写死魔法数字（强制，防数据偏移）**：凡对片上结构做字节级局部写入（如记录 `magic` 状态位、患者正文 `age` 起始），其地址偏移必须取 `offsetof(treatmentRecord_t, magic)` / `offsetof(patientRecord_t, age)`（在 treatment.c 内封装为 `REC_MAGIC_OFFSET` / `PAT_BODY_OFFSET`），严禁直接写 `+ 7`、`+ 2` 等硬编码常量；行尺寸与地址几何一律用 `sizeof`/`PAT_BYTES`/`REC_BYTES`。这样结构字段增减、对齐变化时偏移由编译器自动跟随，不会把正文或状态位写到错误位置。`offsetof`/`sizeof` 均为编译期常量，替换不改变任何运行时行为与镜像尺寸。仅数学取整（如位图字节数 `(n+7)/8`）不属于字段偏移，不受此限。

---

## 十、空槽位控件隐藏与搜索框清空（强制规格，2026-11-20）

1. **空槽位判定**：窗口内槽位 `i` 的视图位置 `viewPos = topIndex + i`，当 `viewPos >= filteredCount` 时该槽位为空（搜索命中不足一屏、空视图、末页未满均适用）。用户所述“搜索后只有 2 个对应病人时，槽位 2–4 全部空白”即本条的具体情形；本条对 0–4 任意数量空槽位统一生效，不只限于 2 个病人的场景。
2. **空槽位文本**：`GDDC_PAGE_LIST_TREATMENT_TEXT_NAME_i`、`GDDC_PAGE_LIST_TREATMENT_TEXT_ID_i`、`GDDC_PAGE_LIST_TREATMENT_TEXT_RECORD_COUNT_i` 三个文本框一律下发空串，不显示任何内容。
3. **空槽位按键**：`GDDC_PAGE_LIST_TREATMENT_KEY_SELECT_PATIENT_i`、`GDDC_PAGE_LIST_TREATMENT_KEY_DELETE_i`、`GDDC_PAGE_LIST_TREATMENT_KEY_EDIT_RECORD_i` 三个按键必须同时 `SetControlVisiable(..., 0)` 隐藏、`SetControlEnable(..., 0)` 禁止触摸；各回调函数既有的空槽位 `viewPos >= filteredCount` 直接返回防护继续保留，作为双保险。
4. **有效槽位恢复**：每次 `refreshListTreatmentDisplay()` 对全部 5 个槽位显式下发状态——有效槽位三个按键 `SetControlVisiable/Enable(..., 1)`，保证过滤、翻页、删除后重新占用的槽位按键能正常显示与触摸，不依赖屏幕工程的默认控件状态。
5. **搜索框清空**：每次经 `enterListTreatmentPage()` 进入本页（含点 `GDDC_PAGE_LIST_TREATMENT_KEY_CLOSE` 回到待机页后再次进入），除清空 RAM 中 `findText` 外，必须向 `GDDC_PAGE_LIST_TREATMENT_TEXT_SEARCH_NAME` 下发空串，使屏幕搜索框同步清空，随后按空串重建视图、显示全部患者。
6. **例外路径**：`listTreatmentOperatorUsbBack()` 从 USB 操作页返回时保留当前搜索内容与窗口位置，不清空搜索框，不适用本条第 5 点。

---

## 十一、病历数量文本框 TEXT_RECORD_COUNT_0–4 显示格式（强制规格，2026-11-20）

1. **有效槽位（有对应病人）**：`GDDC_PAGE_LIST_TREATMENT_TEXT_RECORD_COUNT_i` 显示固定英文格式 `Records: X`，其中 `X` 为该患者实际已记录的病历数量；**X 可以为 0**，此时显示 `Records: 0`。`X` 由 `refreshListTreatmentDisplay()` 预读窗口 5 行后，**单遍记录 id 轻读（2 字节/条）一次性统计**窗口各患者的记录数，不再为每个患者各做一次整行全表扫描。
2. **空槽位**：仍按第十节下发空串，不显示任何内容。
3. 文案为纯 ASCII（英文字母、冒号、空格与数字），符合根目录 `AI_RULES.md` 显示文本一律英文的至高规格，屏幕现有字体（font 6，ASC_CHS_20）可直接渲染，无需改屏幕工程。
4. 曾提出的中文“病历数量X”方案：与 `AI_RULES.md` 英文显示至高规格冲突，且屏幕资源无中文字体（`dwLaser.fidx` 仅含 30 个 ASCII 字体，`charset.txt` 不含“病历数量”字形），经确认**不采用**。将来若要恢复中文显示，必须先经仓库所有者人工授权并修改 `AI_RULES.md` 至高规格，再完成屏幕中文字体工程（VisualTFT 配置中文字体、加入字形、重建并烧录屏幕资源），固件按 GB2312/GBK 编码下发。

---

## 十二、USB 三页面按键自锁（强制规格，2026-11-21）

1. **适用范围**：`GDDC_PAGE_OPERATOR_USB`、`GDDC_PAGE_OPERATOR_USB_SAVE`、`GDDC_PAGE_OPERATOR_USB_LOAD` 三个页面上的**全部 7 个按键控件**——`GDDC_PAGE_OPERATOR_USB` 页 `GDDC_PAGE_OPERATOR_USB_KEY_SAVE_UDISK`（控件 3）、`GDDC_PAGE_OPERATOR_USB_KEY_LOAD_UDISK`（控件 4）、`GDDC_PAGE_OPERATOR_USB_KEY_CLOSE`（控件 5）；`GDDC_PAGE_OPERATOR_USB_SAVE`/`GDDC_PAGE_OPERATOR_USB_LOAD` 页 `GDDC_PAGE_OPERATOR_USB_SAVE_KEY_OK`（控件 11）/`GDDC_PAGE_OPERATOR_USB_LOAD_KEY_OK`（控件 11）、`GDDC_PAGE_OPERATOR_USB_SAVE_KEY_CANCEL`（控件 10）/`GDDC_PAGE_OPERATOR_USB_LOAD_KEY_CANCEL`（控件 10）。屏幕工程中 7 个按键均为 `button_type = 1`（自锁型，按下后不自行弹起），该属性为强制配置，不得改为自弹型。
2. **弹起机制不另立规则**：这 7 个按键的释放位置、无条件弹起（含空操作）、切页安全解锁与中止路径，**统一遵循第十六节**，由 `treatmentReleaseButton` 经 `NotifyButton` 层处理，本节不再维护各自的弹起时机，避免与第十六节口径漂移。
3. **唯一需在本节点明的异步特性**：`GDDC_PAGE_OPERATOR_USB_SAVE_KEY_OK`/`GDDC_PAGE_OPERATOR_USB_LOAD_KEY_OK`（控件 11）按下只授权（`usbState` 6→7），实际 CSV 读写（含导入后的回读核对）在 `listTreatmentUsbLoop` 中完成，故该确认键按第十六节的异步例外在 loop 工作完成后释放，而非 notify 立即释放。
4. 任何后续在这三页新增的自锁按键，先在本节登记控件 ID，其释放仍统一遵循第十六节。
5. **进入确认页的按键基线与读写期间两键物理禁用（强制）**：进入 `GDDC_PAGE_OPERATOR_USB_SAVE`/`GDDC_PAGE_OPERATOR_USB_LOAD` 时，固件必须在 `SetScreen` 前显式对本页确认键（`GDDC_PAGE_OPERATOR_USB_SAVE_KEY_OK`/`GDDC_PAGE_OPERATOR_USB_LOAD_KEY_OK`，控件 11）、取消键（`GDDC_PAGE_OPERATOR_USB_SAVE_KEY_CANCEL`/`GDDC_PAGE_OPERATOR_USB_LOAD_KEY_CANCEL`，控件 10）下发 `SetButtonValue(...,0)` 并恢复触摸使能，建立“两键均未按下且可用”基线——屏幕会保留自锁键运行态、不随切页复位，不主动清零会出现进入即两键同时显示按下。确认键按下进入状态 7 后，固件须对本页确认键、取消键全部 `SetControlEnable(...,0)`（取消键先 `SetButtonValue(0)`），使读写过程中按下任一键都不产生任何触摸通知：禁止中途取消，也禁止读取期间重复按确认键持续发出 `state=1`。读写完成后在返回操作页前先弹起确认键、解除互锁，并对两键 `SetControlEnable(...,1)` 恢复使能；下次进入确认页时进入基线也会再次统一恢复。
6. **确认页取消键返回操作页时重建操作页按键基线（强制）**：点 `GDDC_PAGE_OPERATOR_USB_SAVE_KEY_CANCEL`/`GDDC_PAGE_OPERATOR_USB_LOAD_KEY_CANCEL`（状态 6→0）返回操作页 `GDDC_PAGE_OPERATOR_USB` 时，进入确认页前对操作页 SAVE/LOAD 下发的释放帧在切页前已发，但屏幕对自锁键运行态保留不可靠，LOAD 键可能停在按下态。故 `listTreatmentUsbCancel` 在 `SetScreen` 前必须调用 `refreshOperatorUsbDisplay()`（此时确认页仍为当前页，帧目标操作页），重建操作页 SAVE/LOAD/CLOSE“全部未按下”基线并清空 `GDDC_PAGE_OPERATOR_USB_TEXT_SUMMARY_USB`，再切页。

---

## 十三、患者历史治疗记录页 GDDC_PAGE_LIST_RECORD（页面 ID 15，强制规格，2026-11-21）

### 13.1 进入与数据来源

1. 在病历列表页 `GDDC_PAGE_LIST_TREATMENT` 点击 `GDDC_PAGE_LIST_TREATMENT_KEY_EDIT_RECORD_0–4`（控件 31–35），由 `listTreatmentRecordEnter(slot)` 处理：按窗口槽位解析出对应患者，把稳定患者编号写入 `recordPatientId`，再调用 `listTreatmentRecordEnumerate()` 令窗口缓存失效并收集当前窗口；随后在 `SetScreen(GDDC_PAGE_LIST_RECORD)` **之前**先对本页控件 20–28（`GDDC_PAGE_LIST_RECORD_KEY_DELETE_0–4`/`GDDC_PAGE_LIST_RECORD_KEY_PAGE_UP`/`GDDC_PAGE_LIST_RECORD_KEY_PAGE_DOWN`/`GDDC_PAGE_LIST_RECORD_KEY_CLOSE`/`GDDC_PAGE_LIST_RECORD_KEY_EDIT_PATIENT`，均为按钮）统一下发 `SetButtonValue(...,0)` 建立“全部按键未按下”基线，并调用 `refreshListRecordDisplay()` 完成渲染，最后才切页。
   - **入口按钮区分（不得混淆）**：进入本页的是 `GDDC_PAGE_LIST_TREATMENT_KEY_EDIT_RECORD_0–4`（控件 31–35）；同页 `GDDC_PAGE_LIST_TREATMENT_KEY_SELECT_PATIENT_0–4`（控件 20–24）按第五节只做“选中患者并自动返回待机页”，不进入本页。
   - **为何在进入函数内渲染（强制）**：本工程 `DeviceScreenNotify=0`，屏幕冷加载回传（`NotifyScreen`）不可靠，不能只靠它渲染；进入函数先“清键+渲染”再切页，与 `GDDC_PAGE_LIST_TREATMENT`/`GDDC_PAGE_OPERATOR_USB` 进入路径一致，否则会出现进入即空白、按键停在按下态。`NotifyScreen` 的冷加载分支保留为兜底重发。
2. 枚举口径（无条数硬上限、无整行缓存数组）：`listTreatmentRecordCollectWindow()` 单遍扫描扁平记录，用 `treatmentRecordGetPatientIdByIndex()` **只读记录行首 2 字节外键 id**（替代整行 28 字节），按 `rowId == recordPatientId` 过滤并统计记录总数（`recordCount`，`uint16`），仅把当前窗口 5 条的全局索引缓存到 `recordWindow[0..4]`；翻页时按 `recordTop` 重新轻扫收集对应窗口，完整行在渲染时才读，记录按存储顺序（即追加/时间先后）呈现，条数仅受区块物理容量约束。
3. 页面冷加载时（`screen_id` 分发）必须重新枚举并调用 `refreshListRecordDisplay()`，保证掉电重启回到本页时显示与存储一致。

### 13.2 控件与显示格式

1. **姓名行 `GDDC_PAGE_LIST_RECORD_TEXT_NAME`（控件 1）**：固定格式 `姓名 - AR 编号`，例如 `John Smith - AR 0001`（AR 前缀规则见第十五节）。
2. **时间/能量行 `GDDC_PAGE_LIST_RECORD_TEXT_TIME_ENERGY_0–4`（控件 2–6）**，固定格式：
   `记录时间 - 发射能量 - 发射时间 - 功率 - 波长`
   示例：`2026-11-10 18:00 - 262.7 J - 00:19 - 30 W - 1470 nm`
   - 记录时间取 RTC，格式 `YYYY-MM-DD HH:MM`；未记录时间时该段显示 `---- --:--`。
   - **各数据来源的时间口径**：①AUTOFILL 演示记录由 `demoBuildRecord` 生成，末尾经 `demoStampRandomRtc` 随机附一条合规 RTC——完整年取 2001–2099（`demoRandRange`），月 1–12，日按 `demoDaysInMonth` 取 1..当月天数（闰年规则与 `RtcCheckDate` 一致，2 月闰年 29 天），时 0–23、分 0–59、秒 0–59，故演示记录均显示真实格式时间；②CSV 导入记录仅当源文件第 10 列 RTC 非空才带时间，空列即无时间（显 `----`）；③真实治疗记录在退出 ready 回待机时由 `RtcGetDateTime` 盖章，只要硬件 RTC 已正确校时即显示完整时间。已知边界：片上 `rtcYear` 用 0 表示“无时间”，而 2000 年（`sDate.Year=0`）落盘也为 0，二者无法区分；因此随机年份下限刻意避开 2000、从 2001 起（落盘 1–99，永不为 0），保证可回读显时间。
   - 发射能量底层为 0.1 J（decijoule），显示时除以 10 保留 1 位小数（用整数运算拆整/分，不用浮点）。
   - 发射时间取秒，格式 `MM:SS`；功率取 `laserPower`，单位 `W`；波长单波长如 `1470 nm`，双波长如 `1470+980 nm`。
3. **方案/脉宽行 `GDDC_PAGE_LIST_RECORD_TEXT_SCHEME_WIDTH_0–4`（控件 7–11）**：
   - 连续模式：`大类 序号 - CW`，示例 `Phlebology 1 - CW`。
   - 脉冲模式：`大类 序号 - Pulse - ON 正脉宽 / OFF 负脉宽 ms`，示例 `Phlebology 1 - Pulse - ON 600 / OFF 700 ms`。
   - 自定义方案（`protocol == eCustiom`）：仅显示 `Custom`，不带序号与模式。
   - 大类名称复用 `treatmentProtocolName`，序号为 `schemeIndex + 1`。
4. **页码 `GDDC_PAGE_LIST_RECORD_TEXT_PAGE`（控件 12）**：固定格式 `PAGE 当前页/总页数`，例如 `PAGE 1/2`；总页数 = `ceil(recordCount/5)`，无记录时强制 `PAGE 1/1`，严禁 `0/0`。
5. 全部文案为纯 ASCII，符合根目录 `AI_RULES.md` 英文显示至高规格。

### 13.3 空槽位隐藏（不足 5 条）

1. 当槽位 `i` 的记录位置 `recordTop + i >= recordCount` 时该槽为空（如仅 3 条记录，则槽 3–4 为空）。
2. 空槽的 `GDDC_PAGE_LIST_RECORD_TEXT_TIME_ENERGY_i`、`GDDC_PAGE_LIST_RECORD_TEXT_SCHEME_WIDTH_i` 两个文本控件必须 `SetControlVisiable(..., 0)` 隐藏、不显示任何内容；`GDDC_PAGE_LIST_RECORD_KEY_DELETE_i` 必须同时隐藏并 `SetControlEnable(..., 0)` 禁止点击。
3. 有效槽位每次刷新显式恢复可见/可点状态，不依赖屏幕默认值。
4. **删除后不足 5 条的具体口径（强制，承接 13.4 示例）**：删除 c 后只剩 a、b、d、e 共 4 条，第 5 槽（`i = 4`）为空——`GDDC_PAGE_LIST_RECORD_TEXT_TIME_ENERGY_4`（控件 6）、`GDDC_PAGE_LIST_RECORD_TEXT_SCHEME_WIDTH_4`（控件 11）必须清空（`SetControlVisiable(..., 0)` 隐藏、不显示任何内容），`GDDC_PAGE_LIST_RECORD_KEY_DELETE_4`（控件 24）必须同时隐藏并 `SetControlEnable(..., 0)` 禁止点击；其余空槽同理。该规则由 `refreshListRecordDisplay()` 在每次删除确认返回后统一执行，不依赖手动刷新。

### 13.4 翻页与按键

1. `GDDC_PAGE_LIST_RECORD_KEY_PAGE_UP`（控件 25）/`GDDC_PAGE_LIST_RECORD_KEY_PAGE_DOWN`（控件 26）：`recordTop` 分别减/加 5，由 `listTreatmentRecordMaxTop()` 夹取到合法整页边界，到首页/末页停止；**窗口确实移动后必须在函数内调用 `refreshListRecordDisplay()` 重新渲染**（仅改 `recordTop` 不渲染则画面不更新）。
2. `GDDC_PAGE_LIST_RECORD_KEY_DELETE_0–4`（控件 20–24）功能：**按下某个 DELETE 键，将删除该键所在行对应的那一条历史治疗记录**。槽位与记录一一对应——第 `i` 行记录的信息显示在 `GDDC_PAGE_LIST_RECORD_TEXT_TIME_ENERGY_i`（控件 2–6）与 `GDDC_PAGE_LIST_RECORD_TEXT_SCHEME_WIDTH_i`（控件 7–11），`GDDC_PAGE_LIST_RECORD_KEY_DELETE_i`（控件 20–24）即删除该行记录。
   - **示例**：当前窗口有 a、b、c、d、e 共 5 条记录，依次显示在 `GDDC_PAGE_LIST_RECORD_TEXT_TIME_ENERGY_0` 至 `GDDC_PAGE_LIST_RECORD_TEXT_TIME_ENERGY_4` 行；点击 `GDDC_PAGE_LIST_RECORD_KEY_DELETE_2`（控件 22）即删除第 3 行记录 c，随后重新刷新本页显示（剩余 a、b、d、e 重排到前 4 行，末行空出）。
   - 删除经确认页 `GDDC_PAGE_DELETE_RECORD` 闭环执行（先确认后删除，见第十四节），防卡按下的禁用/清零机制见 16.10；删除后不足 5 条时空槽文本与 DELETE 键的隐藏、禁用见 13.3。
3. `GDDC_PAGE_LIST_RECORD_KEY_CLOSE`（控件 27）：notify 先 `treatmentReleaseButton` 弹起本键，再由 `listTreatmentRecordClose()` 清空 `recordPatientId` 并返回病历列表页 `GDDC_PAGE_LIST_TREATMENT`。
4. `GDDC_PAGE_LIST_RECORD_KEY_EDIT_PATIENT`（控件 28）：notify 先释放本键，再由 `listTreatmentRecordEditPatient()` 跳转患者信息编辑页 `GDDC_PAGE_EDIT_PATIENT`，行为见 13.5。
5. 本页全部按键在屏幕工程均为 `button_type = 1`（自锁型）。**释放时序（强制，按按键分类）**：
   - `GDDC_PAGE_LIST_RECORD_KEY_CLOSE`/`GDDC_PAGE_LIST_RECORD_KEY_EDIT_PATIENT`：notify 先 `treatmentReleaseButton`（当前页仍在时下发清零）再切页，禁止先切页再发释放帧（设备切走后可能忽略该帧导致按键残留）；
   - `GDDC_PAGE_LIST_RECORD_KEY_PAGE_UP`/`GDDC_PAGE_LIST_RECORD_KEY_PAGE_DOWN`：走 `listTreatmentRecordPageKey` 动作期禁用、完成后清零恢复（见 16.8）；
   - `GDDC_PAGE_LIST_RECORD_KEY_DELETE_0–4`：禁用优先、确认页返回时统一清零（见 16.10），不在手指仍触摸时立即清零。
   各路径统一遵循第十六节。

### 13.5 患者信息编辑（`GDDC_PAGE_EDIT_PATIENT` 复用）

> **命名口径（避免歧义）**：本页页面 ID 宏为 `GDDC_PAGE_EDIT_PATIENT`（`SetScreen` 跳转目标）；本页控件统一以 `GDDC_PAGE_EDIT_PATIENT_*` 为前缀（如 `GDDC_PAGE_EDIT_PATIENT_TEXT_ID`、`GDDC_PAGE_EDIT_PATIENT_KEY_OK`）。即现场所称“EDIT_TREATMENT 页面”即 `GDDC_PAGE_EDIT_PATIENT`，二者指同一页面，固件不混用。

1. 点 `GDDC_PAGE_LIST_RECORD_KEY_EDIT_PATIENT` 由 `listTreatmentRecordEditPatient()` 预填该患者姓名/年龄/性别，ID 行显示 `AR 编号`，并置 `editPatientMode = 1`，`SetScreen(GDDC_PAGE_EDIT_PATIENT)`。
2. `GDDC_PAGE_EDIT_PATIENT_KEY_OK` 在该模式下改走 `listTreatmentEditPatientConfirm()`：调用 `treatmentPatientUpdate()` 原地更新患者信息（id 不变、不追加治疗记录），完成后回记录页 `GDDC_PAGE_LIST_RECORD` 并清 `editPatientMode = 0`。
3. `GDDC_PAGE_EDIT_PATIENT_KEY_CANCEL` 在该模式下走 `listTreatmentEditPatientCancel()`：不更新，回记录页 `GDDC_PAGE_LIST_RECORD`。正常新建/追加流程（`editPatientMode = 0`）仍走原 `listTreatmentCreateConfirm/Cancel`，行为不变。

---

## 十四、单条治疗记录删除确认页 GDDC_PAGE_DELETE_RECORD（页面 ID 16，强制规格，2026-11-21）

1. **进入确认页（不直接删除）**：记录页 `GDDC_PAGE_LIST_RECORD` 点击 `GDDC_PAGE_LIST_RECORD_KEY_DELETE_0–4`（控件 20–24）由统一入口 `listTreatmentRecordDeleteKey(slot)` 处理：先禁用 5 个 DELETE 键关闭触摸窗口，再由 `listTreatmentRecordDeleteStart(slot)` 缓存待删记录全局索引到 `deleteRecordGlobalIndex`、下发确认页内容，并在切页前对 `GDDC_PAGE_DELETE_RECORD_KEY_OK`/`GDDC_PAGE_DELETE_RECORD_KEY_CANCEL` 建立未按下基线后 `SetScreen(GDDC_PAGE_DELETE_RECORD)`，即按下 DELETE 后先弹出确认页；不在记录页直接删除，也不在手指仍触摸时立即清零（防卡按下，见 16.10）。
2. **控件**：`GDDC_PAGE_DELETE_RECORD_TEXT_NAME`（控件 1）、`GDDC_PAGE_DELETE_RECORD_TEXT_SUMMARY_0`（控件 2）、`GDDC_PAGE_DELETE_RECORD_KEY_CANCEL`（控件 10）、`GDDC_PAGE_DELETE_RECORD_KEY_OK`（控件 11）。
   - **`GDDC_PAGE_DELETE_RECORD_TEXT_NAME`（控件 1）显示待删记录所属病人**：按“病人姓名 - AR 编号”格式展示该条历史记录对应的病人名字和 ID（与记录页姓名行同口径，见 13.2），不显示通用标题。
3. **`GDDC_PAGE_DELETE_RECORD_TEXT_SUMMARY_0`（控件 2）显示待删记录摘要**：按“治疗日期 - 发射能量 - 发射时间 - 发射功率”四字段展示该条记录的真实数据（不是通用提示语），供用户核对将要删除的对象；该记录无 RTC 时日期段显 `---- --:--`。
4. **`GDDC_PAGE_DELETE_RECORD_KEY_OK`（控件 11）**：`listTreatmentDeleteRecordConfirm()` 调用 `treatmentRecordDeleteByIndex(idx)` 删除该条（墓碑 + 安全压缩），清空缓存索引、重新枚举；**在 `SetScreen(GDDC_PAGE_LIST_RECORD)` 之前**先对记录页控件 20–28 清零、调 `refreshListRecordDisplay()` 重渲染并 `listTreatmentRecordUpdatePageKeys()` 恢复使能，再返回上一级记录页（不依赖切页后的 `NotifyScreen`）。
5. **`GDDC_PAGE_DELETE_RECORD_KEY_CANCEL`（控件 10）**：`listTreatmentDeleteRecordCancel()` 放弃删除、不做任何 EPROM 写入，清空缓存索引；同样在 `SetScreen(GDDC_PAGE_LIST_RECORD)` 前完成清零/重渲染/使能恢复后直接返回上一级记录页。
6. **对应关系与示例**：DELETE 键与窗口行一一对应，`GDDC_PAGE_LIST_RECORD_KEY_DELETE_i` 删除第 i 行（该行信息显示在 `GDDC_PAGE_LIST_RECORD_TEXT_TIME_ENERGY_i`、`GDDC_PAGE_LIST_RECORD_TEXT_SCHEME_WIDTH_i`）。当前窗口有 a、b、c、d、e 共 5 条记录时，点击 `GDDC_PAGE_LIST_RECORD_KEY_DELETE_2`（控件 22）即删除第 3 行记录 c，确认返回后重新刷新本页，剩余 a、b、d、e 重排到前 4 行；只剩 4 条记录后第 5 槽为空，`GDDC_PAGE_LIST_RECORD_KEY_DELETE_4`（控件 24）必须隐藏并 `SetControlEnable(..., 0)`（空槽两文本同样清空隐藏，见 13.3）。
7. 两个按键均为自锁型，其释放统一遵循第十六节（notify 层无条件 `treatmentReleaseButton`）；本闭环为强制规格，不得改为点 DELETE 直接删除或跳过确认。

---

## 十五、患者 ID 编码规则（AR 前缀，强制规格，2026-11-21）

1. **编码格式**：`AR` + 一个空格 + 至少 4 位递增数字，不足 4 位前面补零，例如 `AR 0001`、`AR 0002`、`AR 0011`。
2. **EPROM 只存数字**：为节省空间，患者行 `patientRecord_t.id` 与记录外键均只存 `uint16_t` 递增数字，不存 `AR` 前缀或空格；在 HMI 显示与 CSV 导出/导入时由软件自动加/去 `AR ` 前缀。
3. **自动生成、不可手动修改**：新建患者编号**最小空缺优先回收复用、无空缺才取最大数字加 1**（`treatmentPatientSuggestId` / `FirstFreePatientId`），不接受手动输入；删除患者留下的编号会被后续新患者优先复用，但既有患者自身编号永不重编号。
4. **新患者分配新 ID，老患者复用**：再次治疗选择已有患者时追加治疗记录、沿用原 ID；新建患者的具体编号由数据层按当前最大 ID 递增分配（某个时点的已分配编号属于运行数据，不在本强制规格中记录）。
5. **同名不代表同一患者**：选择已有患者即复用其 ID；选择 Create New Patient 则生成新 ID，即使姓名相同也视为不同患者。
6. **CSV 落地**：导出 ID 列输出 `AR 0001`，导入由 `treatmentCsvParseId()` 解析回数字（同时兼容旧版纯数字列）；ID 数字范围对齐片上 `PATIENT_ID_LIMIT`。
7. 本规则任何改动必须先更新本节，并同步 HMI 显示、`minicsvApp.c` 前缀处理与 `treatment.c` 分配逻辑。

---

## 十六、病历相关 11 页按键互锁（强制规格，2026-11-21）

### 16.1 适用范围与目标

1. 本规格适用于以下 **11 个病历相关页面**上的全部按键控件：

| 页面 ID | 页面宏 |
|---|---|
| 13 | `GDDC_PAGE_LIST_TREATMENT` |
| 14 | `GDDC_PAGE_DELETE_TREATMENT` |
| 15 | `GDDC_PAGE_LIST_RECORD` |
| 16 | `GDDC_PAGE_DELETE_RECORD` |
| 17 | `GDDC_PAGE_EDIT_PATIENT` |
| 18 | `GDDC_PAGE_REGISTER_PATIENT` |
| 19 | `GDDC_PAGE_OPERATOR_USB` |
| 20 | `GDDC_PAGE_OPERATOR_USB_SAVE` |
| 21 | `GDDC_PAGE_OPERATOR_USB_LOAD` |
| 22 | `GDDC_PAGE_VERIFY_TREATMENT` |
| 23 | `GDDC_PAGE_DISCARD_TREATMENT` |

2. 目标：任一按键按下（置 1）后，到该按键被单片机重新清零（置 0）的这段“在途”时间内，**同页及跨页的其他所有按键都必须锁定、无法按下**，防止在途动作（FRAM 读写、切页、删除、U 盘读写等）未完成时误触其他按键。
3. 非上述 11 页的页面（待机、方案、诊断、校准、选项、READY 等）不参与本互锁，其按键行为保持原样，互锁门对这些页面直接放行。

### 16.2 触发、锁定与放行语义

1. **触发（Arm）**：在 11 页内任一按键上报 `state = 1`（按下），且当前无在途按键时，互锁立即记录该按键的“画面 + 控件 ID”并进入在途态。
2. **锁定**：在途期间，凡画面或控件 ID 与在途按键不一致的其他按键上报 `state = 1`，一律拒绝（`NotifyButton` 直接 `return`，不执行任何功能）；锁定对同页其他按键与跨页按键同等生效。
3. **同一按键重复通知放行**：在途按键自身重复上报 `state = 1`（屏幕重发/轮询）时放行，不视为新按键，保证在途动作自身的事件链路不被自己的锁阻断。
4. **弹起释放（统一在 notify 层无条件执行）**：
   - 11 页全部按键均为 `button_type = 1`（自锁型，屏幕不会自行补发 `state = 0`），故**每个按键都在 `NotifyButton` 对应分支 `if(state)` 内、调用功能函数之后无条件调用 `treatmentReleaseButton(screen, control)`**；该函数下发 `SetButtonValue(..., 0)` 并同步解除互锁。
   - 释放不得放在功能函数内部的守卫之后：即使功能函数因空槽位、边界、忙状态或校验失败而提前 return（空操作），按键仍必须弹起，严禁出现“按下后无任何路径释放”的死锁。
   - **唯一例外（异步确认键）**：`GDDC_PAGE_OPERATOR_USB_SAVE_KEY_OK`/`GDDC_PAGE_OPERATOR_USB_LOAD_KEY_OK` 按下只授权（`usbState` 6→7），实际 CSV 读写在 `listTreatmentUsbLoop` 中完成；该确认键必须在 loop 工作全部执行完毕后才释放，不在 notify 释放。
   - 若确认页被别处切走（中止路径），由 loop 对该页确认键/取消键统一弹起（见 16.3）。
5. 互锁只保存“是否在途 + 画面 ID + 控件 ID”三个标量，不按页面或控件数量分配数组，RAM 开销恒定。

### 16.3 切页安全解锁（防永久锁死）

1. 页面切换完成通知 `NotifyScreen(screen_id)` 触发时，若新页面与在途按键所在页面**不同**（原页面被切走，其按键无法再走正常复位路径），强制解除互锁，避免新页面被上一页遗留的在途锁永久屏蔽。
2. 若新页面与在途按键所在页面**相同**（同一页面的加载/重发通知），不解锁，避免在途动作期间被误放行；在途按键仍由其功能完成路径正常释放。
3. USB 确认页被别处切走的中止路径（见第十二节、4.4）继续对该页确认键/取消键显式弹起，弹起即经 `treatmentReleaseButton` 同步解锁，与本条切页解锁互为兜底。

### 16.4 与现有触摸状态门的分层关系

1. `NotifyButton` 顶部按顺序串联两道门，**两道都放行才继续分发**：
   - 第一道 `treatmentButtonLockAllowed(screen, control, state)`：本规格的 11 页按键互锁，先判定；
   - 第二道 `listTreatmentUsbButtonAllowed(screen, control)`：既有的 USB 忙/删除确认流程状态门（删除确认等待、U 盘读写忙等期间屏蔽无关触摸），保留不变。
2. 两道门职责不同、不得互相替代：互锁门管“单键在途期间其他键不可按”，状态门管“特定业务流程期间只放行指定控件”；新增业务流程状态门时应接在互锁门之后，不得绕过互锁门。

### 16.5 页面实现位置与启用状态

1. `GDDC_PAGE_VERIFY_TREATMENT`、`GDDC_PAGE_DISCARD_TREATMENT` 已建立 `SetScreen`/`NotifyButton` 分支并启用（退出 ready 且有发射时自动弹出 `GDDC_PAGE_VERIFY_TREATMENT`，放弃记录进入 `GDDC_PAGE_DISCARD_TREATMENT`），其按键在 `NotifyButton` 分支内无条件 `treatmentReleaseButton`，与本规格一致；页面重编号后原 `GDDC_PAGE_READY` 顺延为页面 24。
2. 实现位置：
   - 互锁状态与判定/放行/释放函数（`treatmentIsLockPage`、`treatmentBtnLockArm/Release/Reset`、`treatmentButtonLockAllowed`、`treatmentReleaseButton`）：`MainApp/dcHmiApp.c`，对外声明在 `MainApp/dcHmiApp.h`。
   - 互锁门接入与各自锁键释放点：`MainApp/dcHmiNotifyButton.c`、`MainApp/dcHmiApp.c`。
3. 本规格为强制规格：任何新增病历相关页面若需要同样的“在途互锁”，必须先在 16.1 表中登记页面 ID，并确认其按键在 `NotifyButton` 分支内无条件调用 `treatmentReleaseButton`（异步动作键在其完成路径释放），否则该页面按键可能在途后无法正常解锁。

### 16.6 进入/重进页面的按键未按下基线

1. 页面在被显示前必须保证其上全部按键处于未按下（`SetButtonValue(...,0)`）状态，不得依赖按键在切页前后无应答的逐个复位；进入与重新进入（含从其他页返回、翻页、过滤重建）同等适用。
2. `GDDC_PAGE_LIST_TREATMENT` 的该基线在 `refreshListTreatmentDisplay()` 内、渲染槽位之前建立：对全部 20 个按钮（控件 20–29、31–40，经 `GDDC_PAGE_LIST_TREATMENT_KEY_SELECT_PATIENT_0`…`GDDC_PAGE_LIST_TREATMENT_KEY_DELETE_4` 与 `GDDC_PAGE_LIST_TREATMENT_KEY_EDIT_RECORD_0`…`GDDC_PAGE_LIST_TREATMENT_KEY_OPERATOR_USB` 两段符号宏循环）显式清零；进入路径均先 refresh 再 `SetScreen`，故页面显示前清零已生效。
3. 选中患者不再用按钮 down 态高亮，其归属由 `selectedPatientId/Name` 保持（见第五节）；其他页面若出现同类残留按下，按本基线在其 refresh 中显式清零。

### 16.7 翻页键边界禁用（确定性防卡按下，强制）

1. **问题边界**：`GDDC_PAGE_LIST_RECORD` 的 `GDDC_PAGE_LIST_RECORD_KEY_PAGE_UP`/`GDDC_PAGE_LIST_RECORD_KEY_PAGE_DOWN` 为自锁键，其清零帧若在按下通知后立即回发，可能与屏幕触摸状态机的“置 1”提交竞争，使按键视觉停在按下态。正常翻页时功能函数先经 `refreshListRecordDisplay()` 下发约 27 帧阻塞 UART（数十毫秒），清零帧天然落在触摸提交之后；但在**首/末页边界继续按翻页键**（功能函数判定不移动、空操作、零帧）时无此间隔，曾尝试在释放前加固定 30 ms settle（见附录 A 第 16 条）仍无法彻底消除，证明该自锁竞争不能靠清零帧时序可靠解决。
2. **最终方案——边界禁用（从源头杜绝）**：在 `refreshListRecordDisplay()` 末尾，按钳制后的 `recordTop` 与 `maxTop` 确定性设置两键触摸使能：
   - `GDDC_PAGE_LIST_RECORD_KEY_PAGE_UP`：`recordTop > 0` 时使能，已在首页（`recordTop = 0`）时 `SetControlEnable(...,0)` 禁用；
   - `GDDC_PAGE_LIST_RECORD_KEY_PAGE_DOWN`：`recordTop < maxTop` 时使能，已在末页（`recordTop = maxTop`）时禁用。
   被禁用的按键不响应触摸、不产生 `state=1` 通知、不进入自锁态，因此边界处根本无法按下，彻底消除卡按下。
3. **状态一致性**：进入、上翻/下翻（`GDDC_PAGE_LIST_RECORD_KEY_PAGE_UP`/`GDDC_PAGE_LIST_RECORD_KEY_PAGE_DOWN`）、冷加载（`NotifyScreen`）四条重渲染路径全部经 `refreshListRecordDisplay()` 重算，翻回可移动方向即自动恢复使能；0 条或不足 1 页记录时两键均禁用。该写法与本函数对空槽 DELETE 键的 `SetControlEnable` 处理同构。
4. 有效移动到末页的那一次按下，仍由 notify 在功能函数后经 `treatmentReleaseButton` 显式清零（先在刷新中禁用、再下发 0），不会残留按下态；上一版的 30 ms settle 已撤回，`treatmentReleaseButton` 恢复为直接 `SetButtonValue(0)`+解锁。
5. 禁用键的灰化视觉与边界禁用实际效果待上板确认；`GDDC_PAGE_LIST_TREATMENT` 翻页键为同构结构，已按同款方案落地，见 16.9。

### 16.8 动作期禁用 + 完成后清零恢复（确定性防连按，强制）

1. **问题边界**：16.7 解决“到边界后继续按”，但在**翻页动作的阻塞刷新期间快速连按**，第二次触摸会在按键仍使能时被屏幕接受、其 `state=1` 进入队列，物理置 1 与主机清零交错。此前的 settle 延时与去抖冷却（见附录 A 第 16/18 条）均为概率性时序，未能彻底消除，证明必须在动作期间直接关闭按键触摸。
2. **确定性序列（固化于 `listTreatmentRecordPageKey(dir)`，两键在 notify 的唯一入口）**：
   - **步骤①动作开始即禁用**：先对 `GDDC_PAGE_LIST_RECORD_KEY_PAGE_UP`、`GDDC_PAGE_LIST_RECORD_KEY_PAGE_DOWN` 同时 `SetControlEnable(...,0)`，关闭整个动作窗口的触摸；此后阻塞刷新期间屏幕物理上不接受任何新连按、不产生第二次 `state=1`。
   - **步骤②去抖并翻页**：以 `HAL_GetTick` 维护 `s_recordPageLastTick`，冷却窗口 `RECORD_PAGE_DEBOUNCE_MS`（当前 250 ms，参考值-非实测验收线）仅兜底禁用命令到达前已进入队列的重复帧；窗口外才执行 PageUp/PageDown（只移动窗口+渲染文本，不再管理使能）。
   - **步骤③完成后清零再恢复**：翻页完成（手指已抬起）后先对源按键 `SetButtonValue(...,0)` 清除按下视觉，再调用 `listTreatmentRecordUpdatePageKeys()` 按新位置恢复使能——可移动方向恢复触摸，边界方向保持禁用。
3. **使能管理单点化**：新增 `listTreatmentRecordUpdatePageKeys()` 统一按 `recordTop/maxTop` 设置两键使能（首页禁用 `GDDC_PAGE_LIST_RECORD_KEY_PAGE_UP`、末页禁用 `GDDC_PAGE_LIST_RECORD_KEY_PAGE_DOWN`、0 条时两键均禁用），进入、动作完成、冷加载（`NotifyScreen`）三条路径均调用它；`refreshListRecordDisplay()` 只渲染文本、不再触碰按键使能。
4. 互锁解除仍由 notify 在入口返回后的 `treatmentReleaseButton` 统一完成（其再次下发 0 为幂等兜底），故被禁用/去抖路径都有显式释放，不会残留或永久锁死；仅增加一个 `uint32` 时间戳，RAM 开销恒定。
5. 250 ms 为工程参考值，动作期禁用的灰化/恢复手感与连按实际效果待上板确认；若仍有极端连按问题，优先确认禁用帧是否及时到达，再据实调整常量并在附录 A 留痕，不在各功能函数内分散加延时。

### 16.9 `GDDC_PAGE_LIST_TREATMENT` 翻页键非阻塞延迟释放（确定性防卡按下，强制）

1. **适用范围与根因**：`GDDC_PAGE_LIST_TREATMENT` 的 `GDDC_PAGE_LIST_TREATMENT_KEY_PAGE_UP`（控件 36）/`GDDC_PAGE_LIST_TREATMENT_KEY_PAGE_DOWN`（控件 37）为自锁翻页键。多轮帧序调整（settle、去抖、动作期禁用、render-only）上板仍卡按下，根因是**自锁键在手指仍触摸时，活动触摸会压过主机的 `SetButtonValue(0)`，且固件拿不到手指抬起事件**；`GDDC_PAGE_LIST_TREATMENT` 每次刷新全表扫描记录数（动作约百 ms），尾部清零时手指大概率未抬。证据：按另一键（手指已离开原键）触发的 refresh 基线能成功清零，且对禁用控件写 0 有效。因此本条不再试图“赢得清零竞争”，改为等手指抬起后再清零。
2. **使能单点管理**：`listTreatmentUpdatePageKeys()` 按钳制后的 `topIndex` 与 `listTreatmentGetMaxTop()` 确定性设置两键使能——首页（`topIndex=0`）禁 PAGE_UP、末页（`topIndex=maxTop`）禁 PAGE_DOWN，0 条/不足 1 页两键全禁。该 helper 不在 refresh 内调用，仅在延迟释放轮询及进入/各切屏返回路径显式调用。
3. **按下入口（`listTreatmentPageKey(dir)`，notify 在 state=1 的唯一入口，dir 0=UP、1=DOWN）**：
   - **步骤①动作开始即禁用**：先对两键同时 `SetControlEnable(0)`，阻塞刷新期间屏幕物理上不接受新连按；
   - **步骤②去抖并翻页**：`s_listPageLastTick` + `LIST_PAGE_DEBOUNCE_MS`（150 ms，参考值）决定一次点按爆发是否只翻一页，窗口外才 `MoveUp/MoveDown`（refresh 只渲染、不碰使能，按键全程禁用）；
   - **步骤③不立即清零，装填延迟释放**：置 `s_listPageReleasePending`、记录 `s_listPageReleaseTick=HAL_GetTick()` 与源控件 `s_listPageControl`，按键保持禁用；每次连按都刷新该计时，保证从最后一次按下起再等满释放窗口。
4. **非阻塞延迟释放轮询（`listTreatmentPageReleaseLoop()`，在 dcHmiLoop 每拍调用）**：当最后一次按下后经过 `LIST_PAGE_RELEASE_DELAY_MS`（150 ms，参考值-非实测验收线），手指确定抬起、两键仍禁用且键上无活动触摸，才依次：对两键 `SetButtonValue(0)` → `UpdatePageKeys()` 按新位置恢复使能 → `treatmentBtnLockRelease()` 精确解除互锁。清零时键上无触摸，故确定性清得掉，不依赖时序运气。
5. **互锁口径**：notify 两 case 不立即调 `treatmentReleaseButton`，互锁在按下时由 `treatmentButtonLockAllowed` 武装、在延迟释放时解除；窗口内同键重复放行、异键屏蔽，窗口保证最终一定触发，不会永久锁死。`refreshListTreatmentDisplay()` 保持 20 键清零基线但只渲染、不碰使能（与 `GDDC_PAGE_LIST_RECORD` 同构）；冷加载工程模式分支不改动。
6. **动作提速（跟手关键）**：早期 refresh 第二步对最多 2019 条记录逐条发独立 SPI 事务读 2 字节 id，每事务命令/地址开销累积约百 ms。现数据层新增 `treatmentRecordReadRows()`（单事务地址自增，8 个 28 字节行/块连续读），refresh 改为分块批量读、提取每行首字段 `patientId` 计数，数据时钟占主导，记录扫描耗时由约百 ms 降到约 20–30 ms；页面内容因此更快响应，且 150 ms 释放窗口下翻页上限约 6.7 页/秒。
7. **代价与待确认**：每次翻页后按键有约 150 ms 灰化延迟；新增块缓冲 `listRecordChunk`（8×28=224 B，ZI 增）。无硬件，灰化/手感与慢按/长接触（>150 ms）是否仍复现待上板确认；若仍有极端 case，优先改屏幕“瞬变”按钮（方法 A，手指抬起自动回发 state=0，可零额外延迟、物理不卡）。

### 16.10 `GDDC_PAGE_LIST_RECORD` DELETE 键禁用优先 + 切页前清零（确定性防卡按下，强制）

1. **问题与根因**：`GDDC_PAGE_LIST_RECORD_KEY_DELETE_0–4`（20–24）为自锁键，手指仍触摸时主机 `SetButtonValue(0)` 必被活动触摸压过；且本工程 `DeviceScreenNotify=0`，切页后的 `NotifyScreen` 回传不可靠。旧实现把返回后的清零/重渲染/使能恢复寄托在 `NotifyScreen(15)`，该回调不触发时 DELETE 键残留按下、5 个 DELETE 键保持禁用（锁定）、文本不上回缩。结论：**一切清理必须在 `SetScreen` 之前完成，不能依赖返回回调。**
2. **进入确认页（统一入口 `listTreatmentRecordDeleteKey(slot)`，notify 在 state=1 的唯一入口）**：
   - 先校验槽位与 `recordTop+slot < recordCount`，非法则复位互锁直接返回，不做禁用；
   - 清掉可能残留的 `deleteRecordGlobalIndex`（异常中断的上一次流程），使 `DeleteStart` 守卫通过；
   - **步骤①动作开始即对 5 个 DELETE 键 `SetControlEnable(0)`**：阻塞切页期间这些键物理上不接受新触摸、不产生重复 `state=1`；
   - **步骤②调 `listTreatmentRecordDeleteStart(slot)`**：置确认索引/文案，切页前对 `GDDC_PAGE_DELETE_RECORD_KEY_OK`/`GDDC_PAGE_DELETE_RECORD_KEY_CANCEL` 下发 `SetButtonValue(0)` 建立未按下基线（防止进入即取消键按下），再 `SetScreen(GDDC_PAGE_DELETE_RECORD)`；
   - **步骤③ `treatmentBtnLockReset()` 解除本页互锁**：`GDDC_PAGE_DELETE_RECORD_KEY_OK`/`GDDC_PAGE_DELETE_RECORD_KEY_CANCEL` 会重新武装，即使内部早退也不残留锁。
3. **返回记录页（切页前完成，OK 与 CANCEL 同构）**：`listTreatmentDeleteRecordConfirm/Cancel` 在 `SetScreen(15)` 之前，确认页仍为当前页时依次：对 20–28 全部 `SetButtonValue(0)` 清按下态 → `refreshListRecordDisplay()` 重渲染（剩余记录上移回缩，空槽文本隐藏、DELETE 键按 occupied 隐藏并禁用/使能）→ `listTreatmentRecordUpdatePageKeys()` 恢复翻页键。此时原 DELETE 手指已抬起、键上无活动触摸，清零确定性生效。
4. **范围约束**：只禁用 5 个 DELETE 键（20–24），不碰 `GDDC_PAGE_LIST_RECORD_KEY_CLOSE`（27）/`GDDC_PAGE_LIST_RECORD_KEY_EDIT_PATIENT`（28），这两个键始终保持使能、无独立使能管理；`GDDC_PAGE_DELETE_RECORD` 的 `GDDC_PAGE_DELETE_RECORD_KEY_OK`/`GDDC_PAGE_DELETE_RECORD_KEY_CANCEL` 触摸与数据层删除/压缩逻辑不变。`NotifyScreen(15)` 保留为兜底重发，不再作为主清理路径。
5. **待确认**：无硬件，禁用灰化、确认页切换与返回后按键弹起/记录是否删除/文本回缩待上板确认；若仍有极端 case，同样可改屏幕“瞬变”按钮（方法 A）根治。

---

## 十七、新建患者注册页 GDDC_PAGE_REGISTER_PATIENT（页面 ID 18，强制规格，2026-11-22）

### 17.1 进入入口

经注册页 `GDDC_PAGE_REGISTER_PATIENT`（18）新建患者，当前只有一条入口：

- **列表页手动新建（与 ready 流程完全无关）**：在 `GDDC_PAGE_LIST_TREATMENT` 点击 `GDDC_PAGE_LIST_TREATMENT_KEY_CREATE_NEW`（控件 39）进入注册页 `GDDC_PAGE_REGISTER_PATIENT`，仅用于手动建立新患者；该入口不要求发射过激光，也不依赖 ready -> standby 的状态转换，随时可从列表页发起。

> 注：激光核对页 `GDDC_PAGE_VERIFY_TREATMENT` 的新患者已改为在核对页本页直接录入姓名/年龄/性别（见 5.6），**不再跳转注册页 `GDDC_PAGE_REGISTER_PATIENT`**；注册页不再承担激光流程的患者录入。

### 17.2 按键出口

- `GDDC_PAGE_REGISTER_PATIENT_KEY_CANCEL`（控件 21；编辑页对应 `GDDC_PAGE_EDIT_PATIENT_KEY_CANCEL`）：**不写入任何数据**，返回列表页 `GDDC_PAGE_LIST_TREATMENT`。
- `GDDC_PAGE_REGISTER_PATIENT_KEY_OK`（控件 20；编辑页对应 `GDDC_PAGE_EDIT_PATIENT_KEY_OK`）：校验通过后**新建一个患者**（仅建立患者，不追加治疗记录），随后返回对应页面。

### 17.3 患者 ID 自动生成（`GDDC_PAGE_REGISTER_PATIENT_TEXT_ID`，控件 1）

进入注册页时，`GDDC_PAGE_REGISTER_PATIENT_TEXT_ID`（控件 1；编辑页对应 `GDDC_PAGE_EDIT_PATIENT_TEXT_ID`）自动生成并显示下一个患者 ID：

1. **无空缺**：取机内最大 ID 加 1。例如最后一个 ID 为 `0098`，则生成 `0099`；
2. **有空缺优先补空缺**：若最大 ID 之前存在一个或多个空缺，取其中**最小**的空缺 ID。例如机内有 `0001`–`0011`、`0013`、`0098`，则生成 `0012`；
3. ID 以 4 位数字显示、不足补零；取值范围 `1 … PATIENT_ID_LIMIT（32767）`，`AR ` 前缀的显示口径按第十五节。

### 17.4 姓名、年龄、性别字段

- **姓名** `GDDC_PAGE_REGISTER_PATIENT_TEXT_NAME`（控件 2）：输入内容作为患者名称；长度超过系统约定 `CONFIG_TREATMENT_NAME_LEN`（18 个字符）时，**截断到 18 个字符**并补字符串结束符。
- **年龄** `GDDC_PAGE_REGISTER_PATIENT_TEXT_AGE`（控件 3）：对应数值作为患者年龄，**按实际人类有效年龄判断**输入是否合法（非数字、负数、0 或超出人类有效年龄上限均判非法）。**进入本页时若年龄未填写（`age = 0`）必须保持完全空白、不得显示数字 `0`（强制，2026-11-25 新增）**：`dcHmiShowTreatmentCommon` 仅在 `age != 0` 时才格式化输出数字，`age = 0` 时下发空串；该口径同时适用于复用此函数的 `GDDC_PAGE_EDIT_PATIENT` 及待存记录显示。
- **性别（全局编码，强制）**：全工程统一 `GENDER_ENUM` 逻辑编码——**男性 `MALE = 1`，女性 `FEMALE = 2`**（treatment.h 定义，持久层与 `treatmentLog` 均用此值）。
- **HMI 性别选项顺序（强制，三页统一）**：`GDDC_PAGE_EDIT_PATIENT`、`GDDC_PAGE_REGISTER_PATIENT`、`GDDC_PAGE_VERIFY_TREATMENT` 三页的性别菜单（分别为 `GDDC_PAGE_EDIT_PATIENT_MENU_GENDER`、`GDDC_PAGE_REGISTER_PATIENT_MENU_GENDER`、`GDDC_PAGE_VERIFY_TREATMENT_MENU_GENDER`）一律**男性排在女性前面**，菜单索引 `0 = Male（男）`、`1 = Female（女）`；显示字符串固定为 `Male` / `Female`（不再使用旧拼写 `FeMale`），菜单索引与逻辑编码由交互点做 `MALE↔0`、`FEMALE↔1` 映射。三页性别均经各自性别菜单下拉选择、由性别文本控件（`GDDC_PAGE_EDIT_PATIENT_TEXT_GENDER`、`GDDC_PAGE_REGISTER_PATIENT_TEXT_GENDER`、`GDDC_PAGE_VERIFY_TREATMENT_TEXT_GENDER`）只读显示，性别文本控件不承担文本输入（`GDDC_PAGE_VERIFY_TREATMENT` 分工见 5.6）。
- **进入页面自动刷新性别文本（强制）**：跳转到 `GDDC_PAGE_REGISTER_PATIENT`/`GDDC_PAGE_EDIT_PATIENT`/`GDDC_PAGE_VERIFY_TREATMENT` 后，固件在 `SetScreen` 之前按当前患者性别自动向对应性别文本控件（`GDDC_PAGE_REGISTER_PATIENT_TEXT_GENDER`/`GDDC_PAGE_EDIT_PATIENT_TEXT_GENDER`/`GDDC_PAGE_VERIFY_TREATMENT_TEXT_GENDER`）下发性别文本——男性显 `Male`、女性显 `Female`、未选择显空串；不依赖手动选择，也不允许残留上一页值。
- **进入注册页前无条件清空（强制，2026-11-25 新增）**：每次经 `listTreatmentEnterRegisterPage` 进入 `GDDC_PAGE_REGISTER_PATIENT` 时，函数在最开头先调用 `listTreatmentClearRegisterFields()`，把 `GDDC_PAGE_REGISTER_PATIENT_TEXT_NAME`（控件 2）、`GDDC_PAGE_REGISTER_PATIENT_TEXT_AGE`（控件 3）、`GDDC_PAGE_REGISTER_PATIENT_TEXT_GENDER`（控件 4）、`GDDC_PAGE_REGISTER_PATIENT_TEXT_SUMMARY_0`（控件 5）一律下发空串清空，再执行“先清后绘”（随后由 `dcHmiShowTreatmentCommon` 与性别文本逻辑按当前 `treatmentLog` 回填，未选择则保持空白），杜绝上一次录入内容残留。

### 17.5 非法输入提示

姓名、年龄、性别中**任一项缺失或不符合人类实际情况**时，禁止写入并停留在注册页，在 `GDDC_PAGE_REGISTER_PATIENT_TEXT_SUMMARY_0`（控件 5）显示：

> "Invalid input, please re-enter!"

用户重新填写至全部合法后，按 `GDDC_PAGE_REGISTER_PATIENT_KEY_OK` 才允许新建患者。

### 17.6 按键松开兜底释放（确定性防卡按下，强制，2026-11-25 新增）

1. **问题边界**：点 `GDDC_PAGE_REGISTER_PATIENT_KEY_OK`（控件 20）时，若姓名/性别/年龄校验失败，固件停留在本页（见 17.5）。按下瞬间（`state = 1`）下发的 `SetButtonValue(...,0)` 释放帧可能与仍在进行的物理触摸竞争、被活动触摸压过，使按钮视觉停在按下态；此前松开（`state = 0`）分支没有任何兜底释放。
2. **释放规则**：按下（`state = 1`）仍先调用 `treatmentReleaseButton` 再执行 `listTreatmentRegisterConfirm`（保留“动作内切页前先清零”的意图）；**新增松开（`state = 0`）分支再下发一次 `SetButtonValue(...,0)`**——此时手指已抬起、无活动触摸，释放帧可靠生效，保证按钮一定弹起，不依赖按下时那一帧的时序。
3. **同口径适用**：核对页 `GDDC_PAGE_VERIFY_TREATMENT_KEY_SAVE_RECORD`（控件 30）结构与校验失败停留路径完全相同，按相同方式在 `state = 0` 补 `SetButtonValue(...,0)` 兜底，避免核对页本页校验失败时同样卡按下。
4. 校验成功的切页路径不受影响：切页后旧页不可见，松开帧即便落到旧页也无副作用；本规则只收口“校验失败、停留本页”的卡按下。

### 17.7 弹出层返回按键释放与切页后重发清空（确定性，强制，2026-11-25 新增）

1. **弹出层返回的卡按下**：本页点 `GDDC_PAGE_REGISTER_PATIENT_TEXT_NAME`/`GDDC_PAGE_REGISTER_PATIENT_TEXT_AGE` 弹出系统键盘、点 `GDDC_PAGE_REGISTER_PATIENT_KEY_GENDER`（控件 22）弹出性别下拉菜单，这些是屏幕内置弹出层；弹出层关闭返回时屏幕重绘本页，可能把 `GDDC_PAGE_REGISTER_PATIENT_KEY_OK`（控件 20）等按钮恢复成按下态。由于 `DeviceScreenNotify = 0`，固件无法靠画面切换通知捕获该返回。
2. **延迟重新确认弹起**：在控件通知（`NotifyText` 键盘确认、`NotifyMenu` 菜单选择）时调用 `treatmentPopupReleaseArm` 装填，由 `treatmentPopupReleaseLoop` 非阻塞等待 `POPUP_RELEASE_DELAY_MS`（150 ms，参考值）弹出层完全关闭、重绘完成后，对本页按钮范围重新下发 `SetButtonValue(...,0)`；只重发按钮值、不改变使能，故无灰化、不影响手感。注册/编辑页覆盖 `KEY_OK`/`KEY_CANCEL`（20/21），核对页覆盖 `GDDC_PAGE_VERIFY_TREATMENT_KEY_SAVE_RECORD`/`GDDC_PAGE_VERIFY_TREATMENT_KEY_DISCARD_RECORD`（30/31）。
3. **二次进入字段未清空（冷加载窗口）**：`SetScreen` 切到本页时屏幕存在冷加载窗口——切页“前”下发的清空帧会被加载重绘覆盖，切页“后立即”下发的帧又会在冷加载窗口丢帧，两者都不可靠，导致再次进入时残留第一次输入。
4. **预刷新 + 冷加载完成重发（确定性）**：把“先清空再渲染”封装为 `listTreatmentRenderRegisterDisplay`。`listTreatmentEnterRegisterPage` 在 `SetScreenUpdateEnable(0)` 冻结后先调用它预刷新后台注册页，再 `SetScreen`、`SetScreenUpdateEnable(1)` 解冻；**同时在 `NotifyScreen` 的 `GDDC_PAGE_REGISTER_PATIENT` 分支（屏幕冷加载完成后必上报 `MSG_GET_CURRENT_SCREEN`）再次调用 `listTreatmentRenderRegisterDisplay` 重发**，此时冷加载已结束、帧不丢失，可靠清空，与待机/记录等页面的冷加载重发模式一致。冻结保证整个过程无旧值闪烁。

---

## 附录 A：变更日志与历史核对记录

> 本附录只记录“某时点的屏幕工程/数据状态”与每次规格变更，不承载强制规则；正文各节只保留不随时间变化的规则。下列状态为对应日期的核对快照，最新状态以实际屏幕工程与代码为准。

1. **2026-11-20**：USB 确认页在屏幕工程 `vTFT_HMI/dwLaser.tftprj` 中建立——导出确认页 `GDDC_PAGE_OPERATOR_USB_SAVE.tft`（页面 20）仅控件 1/2；导入确认页 `GDDC_PAGE_OPERATOR_USB_LOAD.tft`（页面 21）建控件 1/2/3，固件只用 1/2，控件 3 下发空串、控件 4 未建立不写入。
2. **2026-11-21**：删除患者确认页 14 在 `GDDC_PAGE_DELETE_TREATMENT.tft` 中建立（按钮 1–2、文本 3–6），与 `dcHmiRes.h` 宏值一致；同日核对 USB 三页（19/20/21）共 7 个按键均为 `button_type = 1`。
3. **2026-11-22**：
   - 导出确认页文案删去 `The archives on the device will be cleared.`，`TEXT_SUMMARY_1` 只保留“U 盘原有备份将被替换”，与第八节“导出不清空”口径一致；
   - 宏名拼写更正：`..._KEY_CANCLE` → `..._KEY_CANCEL`、`..._RECODE` → `..._RECORD`（控件数字 ID 不变，.tft 内部 name 保留旧拼写、不影响通信）；
   - 第十二节、13.4、第十四节的弹起细节收敛为统一引用第十六节，不再各自维护；
   - 排序措辞改为“姓名 → 原始存储索引”的全序键（原始索引为最终 tie-break），不再称堆排序为稳定排序；
   - 正文各时点快照移入本附录，强制规格只保留规则。
   - 页面 13 建立进入/重进“按键未按下”基线：`refreshListTreatmentDisplay` 对全部 20 个按钮（20–29、31–40）显式清零，取消 `SELECT_PATIENT` 按钮 down 态高亮（见 16.6）。
   - 新增第十七节：新建患者注册页（18）规格，固化两个入口（核对页 22 的 SAVE_RECORD、列表页 13 的 CREATE_NEW）、CANCEL 返回上一页、OK 仅建患者、ID 自动补最小空缺（无空缺取最大 ID+1）、姓名超长截断、年龄/性别校验与非法输入 SUMMARY_0 提示。固件已对齐（最小空缺 ID 位图分配、仅建患者路径、SUMMARY_0 英文提示、核对页 22/放弃页 23 接线与激光停光自动弹页），并通过 AC5 Rebuild：0 Error、2 Warning（usbh_cdc.c 固定基线），hex 正常生成（Code=238156，ZI=121204）。
4. **2026-11-22（全工程合规审计）**：按 AI_RULES.md 两条至高规格与本规格全面核对——显示文本无 ASCII 违背、控件类型与驱动接口零跨类误用、无 CANCLE/RECODE 残留、自编源码全部 UTF-8、停止维护工程零改动、EPROM 块保护关闭与固件 CRC 变化清空均符合。同步修正 16.1 表与 16.5 的过时页面编号（核对页 22、放弃页 23，READY 顺延 24）及"未启用"表述，与当前 dcHmiRes.h 及固件实现一致。
5. **2026-11-22（历史旧命名修复）**：按 AI_RULES.md 至高规格 2，将 `dcHmiRes.h` 全部历史控件类型词统一为合规名——`BUTTON`→`KEY`、`TEXTDISPLAY`→`TEXT`，并同步页面改名（删除确认页 `GDDC_PAGE_DELETE_TREATMENT_CONFIRM`→`GDDC_PAGE_DELETE_TREATMENT`，USB 确认页去掉 `_CONFIRM`）。自编代码共 780 处控件引用 + 11 处页面引用整词替换，禁止新旧并存；控件数字 ID、对外函数签名均不变。AC5 Rebuild：0 Error、2 Warning（usbh_cdc.c 固定基线），hex 正常生成，Code/ZI 与改前完全一致（Code=238156，ZI=121204），证明纯改名、零行为变化。`R_` 前缀的 PLC 内部继电器/标志资源（如 `R_RENAME_TEXTDISPLAY_READ_DONE`）不属 HMI 控件命名空间，保持原样。
6. **2026-11-22（修复 USB 导入失败 #86）**：导出 CSV 数据行以 `AR ` 前缀开头（第十五节），但导入第二遍写入与 `treatmentLogVerifyUdisk` 的行首过滤只放行数字开头行、误跳过全部 `AR ` 行，导致预检计数正确却零写入、回读核对失败，统一提示 `USB backup import failed!`。将两处过滤改为与第一遍预检一致（同时接受 `AR ` 与数字开头），字段校验逻辑不变。主机端按完整字段规则复算 1875 行全部通过，区块容量 2019 条足以容纳。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线），hex 正常生成（Code=238172，较改前 +16，ZI=121204 不变）。无硬件，仅完成编译级与数据级验证，导入实际写 FRAM 与回读结果待上板确认。
7. **2026-11-23（修复确认页 20/21 按键状态 #87/#88）**：进入确认页时未显式清零自锁键，屏幕保留运行态导致进入即 OK/CANCEL 同时显示按下；OK 确认后仅靠 `SetControlEnable` 禁用 CANCEL，未显式弹起、视觉与状态基线不完整。修复：`enterOperatorUsbConfirmPage` 在 `SetScreen` 前对 OK/CANCEL 先 `SetButtonValue(...,0)` 再恢复触摸使能；`listTreatmentUsbConfirm` 状态 7 时对 CANCEL 先 `SetButtonValue(...,0)` 再 `SetControlEnable(...,0)`。功能上状态 7 本就由互锁门 + USB 触摸门屏蔽一切操作，CANCEL 不可能真正取消，本次补齐显式基线与锁定。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线），hex 正常生成（Code=238196，较改前 +24，ZI=121204 不变）。无硬件，按下态视觉与禁用灰化效果待上板确认。
8. **2026-11-23（修复导入后列表页未刷新 #89）**：导入整体替换 EPROM 后，RAM 中的 `filteredCount`/`sortedIndex`/`ramKeys` 仍为导入前旧值；从 USB 操作页 CANCEL 返回列表页（`listTreatmentOperatorUsbBack`）只调 `refreshListTreatmentDisplay` 重渲染、未重建过滤，导入前若为 0 条则 `filteredCount=0`，整页渲染空白，须关闭重进才正常。修复：该返回路径在渲染前先 `listTreatmentRebuildFilter()`（按当前 `findText` 重建，保留搜索与窗口）。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线），hex 正常生成（Code=238200，较改前 +4，ZI=121204 不变）。无硬件，返回即显示姓名/记录数的实际效果待上板确认。
9. **2026-11-23（修复取消载入后 LOAD 键卡按下 #90）**：点 LOAD_UDISK 进确认页后再 CANCEL 返回操作页，进入确认页前对 LOAD 下发的释放帧在切页前已发，但屏幕对自锁键运行态保留不可靠，LOAD 键停在按下态。修复：`listTreatmentUsbCancel`（导出/导入确认页通用）在 `SetScreen(19)` 前调用 `refreshOperatorUsbDisplay()`，重建 19 页 SAVE/LOAD/CANCEL 全部未按下基线并清空 `SUMMARY_USB`，同时删去原来单独的 `SetTextValue` 空串。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线），hex 正常生成（Code=238196，ZI=121204 不变）。无硬件，LOAD 键实际弹起效果待上板确认。
10. **2026-11-23（补强历史记录页 15 软件规格 #91）**：按现场梳理固化本页全量行为——入口为列表页 `KEY_EDIT_RECORD_0–4`（明确 `KEY_SELECT_PATIENT_0–4` 只回待机、不进本页）；`TEXT_NAME` 显示“姓名 - AR 编号”，`TEXT_TIEM_ENERGY_0–4` 按“记录时间 - 能量 J - 发射时间 MM:SS - 功率 W - 波长”五字段、`TEXT_SCHEME_WIDTH_0–4` 按 CW/Pulse（含正/负脉宽）显示；DELETE 走删除确认页、PAGE_UP/DOWN 翻页、`TEXT_PAGE` 显示 `PAGE 当前/总页`、CLOSE 返回列表页、EDIT_PATIENT 进编辑页 17；删除后不足 5 条时空槽两文本清空、对应 DELETE 隐藏并禁用（新增第 4 条具体口径）。经核对当前固件 `refreshListRecordDisplay()` 已实现上述全部行为，本次为文档对齐、无代码改动，显示仍为英文 ASCII。
11. **2026-11-23（确认入口更正并明确编辑页命名 #91）**：现场更正本页入口为列表页 `KEY_EDIT_RECORD_0–4`（与固件一致，此前口述的 SELECT_PATIENT 作废）；同时明确“EDIT_TREATMENT 页面”即页面 17——页面 ID 宏为 `GDDC_PAGE_EDIT_PATIENT`，其控件前缀为 `GDDC_PAGE_EDIT_TREATMENT_*`，已在 13.5 加注。本次仍为文档对齐、无代码改动，无需重新编译。
12. **2026-11-23（修复记录页进入空白与按键不弹起 #92）**：现场反馈进入页面 15 无任何显示、按键进入非弹起态且操作后不弹起。根因：本页是 11 个病历页中唯一进入函数不重置按键、不渲染、只靠屏幕冷加载回传（`NotifyScreen`）的页面，而本工程 `DeviceScreenNotify=0` 使该回传不可靠，故空白且按键残留；另翻页函数只改 `recordTop` 不重渲染，CLOSE/EDIT_PATIENT/DELETE 均“先切页再发释放帧”，设备切走后可能忽略。修复：①`listTreatmentRecordEnter` 在 `SetScreen` 前对控件 20–28 统一清零并调 `refreshListRecordDisplay()` 渲染；②翻页窗口移动后在函数内重渲染；③上述按键在 notify 改为“先释放再切页/动作”。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线），hex 正常生成（Code=238236，较改前 +40，ZI=121204 不变）。无硬件，显示与实际弹起效果待上板确认。
13. **2026-11-23（诊断记录时间全显 `---- --:--` #93）**：现场反馈所有记录时间段均为横线。经核对显示逻辑（`log.rtcYear >= 2000` 才显示时间，否则 `----`）与 record↔log 换算（落盘减 2000、回读加 2000，0 为“无时间”哨兵）均正确，结论为数据本身无 RTC：AUTOFILL 的 `demoBuildRecord` 从不写 `rtcYear`、导入 CSV 的 RTC 列为空；真实治疗记录由停光时 `RtcGetDateTime` 盖章，RTC 正确校时即可显示。本次为诊断与文档补充、无代码改动，无需重新编译。已在 13.2.2 注明数据来源口径与 2000 年哨兵边界。
14. **2026-11-23（AUTOFILL 演示记录随机附合规时间 #94）**：承接 #93，所有者拍板 AUTOFILL 演示记录需带随机合规 RTC。改动均在 `treatment.c`：新增局部宏 `DEMO_RTC_YEAR_MIN/MAX`（2001–2099）、`demoDaysInMonth`（含闰年 2 月，规则同 `RtcCheckDate`）与 `demoStampRandomRtc`（复用 `demoRandRange` 生成年/月/日/时/分/秒，日期与月/闰年匹配），并在 `demoBuildRecord` 末尾调用。年份下限刻意避开 2000，使落盘值为 1–99 永不为 0，规避“无时间”哨兵冲突、保证回读显时间。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线），hex 正常生成（Code=238404，较 #92 +168，RO-data=18592 +12，ZI=121204 不变）。主机按同规则模拟 10 万条记录交叉校验零非法、片上年份不含 0。无硬件，页面 15 实际时间显示待上板确认。
15. **2026-11-23（选中患者激光后核对页自动归属 #96）**：新增规则固化“选中患者 → 激光停光 → 核对页自动归属其名下”。改动均在 `dcHmiApp.c`：新增 `listTreatmentPrefillSelectedPatient`（已选患者仍存在则把 id/name/age/gender 填入 `treatmentLog`，未选或被删返回 0 走新患者兜底），`listTreatmentVerifyAfterLaser` 不再无条件置 id=0、改为调用该 helper 自动预填；`listTreatmentRefreshVerifyDisplay` 的 ID 控件对已选患者显真实 ID（id=0 才显建议 ID）。SAVE_RECORD 时 id 非 0 直接 `treatmentEpromAddToPatient` 归属、不新建患者。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线），hex 正常生成（Code=238488，较 #94 +84，ZI=121204 不变）。已在第五节新增 5.5。无硬件，核对页自动归属与各控件显示待上板确认。
16. **2026-11-23（修复边界翻页键卡按下 #97）**：现场确认卡按下仅出现在“首/末页继续按 PAGE_UP/PAGE_DOWN”。代码级核对释放帧本就每次下发，根因为时序竞争：正常翻页功能函数先经 `refreshListRecordDisplay()` 下发约 27 帧阻塞 UART（数十毫秒），清零帧天然落在屏幕触摸置 1 提交之后；边界空操作零帧，清零帧与触摸置 1 紧邻竞争，按键视觉停在按下态。修复集中在 `treatmentReleaseButton`：新增常量 `BTN_RELEASE_SETTLE_MS`（30 ms，参考值-非实测验收线），下发清零前先 `softDelayMs` 等待 settle，再 `SetButtonValue(...,0)` 并解锁，对 11 页全部自锁键统一生效（含页面 13 同构翻页键）；HMI 接收为中断入队，忙等不丢帧，调用点均在主循环、单次忙等最坏 30 ms。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线），hex 正常生成（Code=238496，较 #96 +8，ZI=121204 不变）。已新增 16.7。无硬件，边界实际弹起与 30 ms 是否足够待上板确认。
17. **2026-11-23（边界 settle 未彻底解决，改确定性边界禁用 #97 收口）**：现场反馈第 16 条的 30 ms settle 仍未彻底消除边界卡按下。结论：该自锁竞争无法靠清零帧时序可靠解决，遂撤回 settle（删除 `BTN_RELEASE_SETTLE_MS`，`treatmentReleaseButton` 恢复直接 `SetButtonValue(0)`+解锁），改为在 `refreshListRecordDisplay()` 末尾按钳制后 `recordTop`/`maxTop` 确定性管理两键使能——首页（`recordTop=0`）禁用 PAGE_UP、末页（`recordTop=maxTop`）禁用 PAGE_DOWN，禁用键不响应触摸、不发 state=1、不进自锁态，从源头无法按下；进入/翻页/冷加载四条重渲染路径均经同一刷新重算，离开边界自动恢复，0 条或不足 1 页时两键均禁用。有效移动到末页的那一次按下仍由 notify 显式清零。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线），hex 正常生成（Code=238540，较 #96 +52，ZI=121204 不变）。16.7 已重写为边界禁用。无硬件，禁用灰化与边界实际效果待上板确认。
18. **2026-11-23（翻页瞬间快速连按去抖 #98）**：现场反馈在翻页动作瞬间快速连按 PAGE_UP/PAGE_DOWN 仍可能出现按键状态错误或一次连按翻多页。第二次触摸在第一次阻塞刷新期间已落屏、其 state=1 进入接收队列，物理置 1 与主机清零交错。新增 `listTreatmentRecordPageKey(dir)` 作为两键统一入口（声明入 dcHmiApp.h），以 `HAL_GetTick` 维护 `s_recordPageLastTick`：距上次有效翻页小于 `RECORD_PAGE_DEBOUNCE_MS`（250 ms，参考值）的连按不移动窗口，先 `softDelayMs(RECORD_PAGE_TAP_SETTLE_MS)`（40 ms，参考值）等触摸提交，再由 notify 的 `treatmentReleaseButton` 权威清零；超时窗口外才记为新的有效翻页。去抖只决定是否翻页，释放/解锁仍统一在 notify，被吞掉的连按也有显式释放；仅新增一个 uint32 时间戳。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线），hex 正常生成（Code=238592，较 #97 +52，RW-data=1568 +4，ZI=121204 不变）。已新增 16.8。无硬件，去抖手感与连按状态待上板确认。
19. **2026-11-23（去抖仍未彻底，改动作期禁用+完成后清零恢复 #98 收口）**：现场反馈第 18 条的去抖/settle 仍可能在快速连按时出错。结论：概率性时序不可靠，改为确定性地在动作期间关闭触摸。重构：新增 `listTreatmentRecordUpdatePageKeys()` 单点管理两键使能（首页禁 PAGE_UP、末页禁 PAGE_DOWN、0 条全禁），`refreshListRecordDisplay()` 只渲染文本、不再碰使能；`listTreatmentRecordPageKey(dir)` 改为三步——①动作开始立即对两键 `SetControlEnable(0)` 关闭触摸窗口；②250 ms 冷却仅兜底已入队重复帧，窗口外才翻页；③完成后先 `SetButtonValue(0)` 清按下视觉再 `UpdatePageKeys` 恢复使能。进入/动作完成/冷加载三路径均调用 UpdatePageKeys，互锁解除仍由 notify 的 `treatmentReleaseButton` 幂等兜底；删除上一版 `RECORD_PAGE_TAP_SETTLE_MS` 与软延时。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线），hex 正常生成（Code=238648，较第 18 条 +56，RW=1568、ZI=121204 不变）。16.8 已重写。无硬件，动作期禁用灰化与连按实际效果待上板确认。
20. **2026-11-23（页面 13 翻页键同款确定性方案 #99）**：现场确认页面 15 方案“快速按下状态异常、边界继续按下状态不对均已解决”，要求把同款方案应用到页面 13 的 PAGE_UP（36）/PAGE_DOWN（37）。改动均在页面 13 符号体系：新增 `listTreatmentUpdatePageKeys()` 单点管理使能（首页禁 PAGE_UP、末页禁 PAGE_DOWN、0 条/不足 1 页全禁），在 `refreshListTreatmentDisplay()` 末尾统一调用，进入/过滤重建/翻页/USB 返回等所有经 refresh 路径建立一致基线；新增 `listTreatmentPageKey(dir)` 统一入口（声明入 dcHmiApp.h），三步——①动作开始立即对两键 `SetControlEnable(0)`；②以 `HAL_GetTick` 维护 `s_listPageLastTick`，`LIST_PAGE_DEBOUNCE_MS`（250 ms，参考值）冷却仅兜底已入队重复帧，窗口外才 `listTreatmentMoveUp/MoveDown`；③完成后先 `SetButtonValue(0)` 清视觉再 `UpdatePageKeys` 恢复。notify 两 case 改走该入口，`treatmentReleaseButton` 仍幂等兜底解锁；保留 refresh 原 20 键清零基线，冷加载工程模式分支不改动。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线），hex 正常生成（Code=238804，较第 19 条 +156，RW=1576、ZI=121200）。已新增 16.9。无硬件，灰化/边界/翻页手感待上板确认。
21. **2026-11-23（页面 13 使能架构对齐页面 15，修 PAGE_DOWN 卡按下 #100）**：上板反馈 PAGE_UP 快速按下很少出错，但 PAGE_DOWN 仍容易定在按下态、再按一次恢复。代码级根因：第 20 条在 `refreshListTreatmentDisplay()` 末尾调用 `UpdatePageKeys`，使动作尚未完全结束就提前重新使能、禁用窗口出现缺口；叠加页面 13 每次刷新全表扫描记录数（动作较长，尾部手指仍在触摸），屏幕在清零帧后因持续接触重新锁存且不再发通知，固件与屏幕状态脱节。修复：refresh 改为只渲染、不碰使能（与页面 15 `refreshListRecordDisplay` 同构），保留 20 键清零基线；`listTreatmentUpdatePageKeys()` 改为在进入页、查找过滤、wrapper 动作完成、以及各 `SetScreen(13)` 返回路径（USB 返回/新建确认与取消/注册核对返回/删除患者确认与取消/记录页关闭/删除记录共 10 处）切屏前显式调用，禁用窗口保持到 wrapper 末尾“先清零、后使能”。MoveUp/Down 内的 refresh 不再提前使能，由 wrapper 统一恢复。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线），hex 正常生成（Code=238832，较第 20 条 +28，RW=1576、ZI=121200 不变）。16.9 已重写。无硬件，灰化/手感与长动作是否仍复现待上板确认；若仍复现，下一步缩短 refresh 全表扫描耗时。
22. **2026-11-23（非阻塞延迟释放，不再与活动触摸竞争 #101）**：第 21 条上板仍卡按下，且 UP 也开始卡、按 UP 能让卡住的 DOWN 弹起。据此确定根因：自锁键在手指仍触摸时活动触摸压过主机写 0、固件又无手指抬起事件，长动作（全表扫描）使尾部清零必败。改为非阻塞延迟释放状态机：`listTreatmentPageKey` 保留“动作开始禁用两键 + 250 ms 去抖决定是否翻页”，但删除尾部立即清零/使能，改为置 `s_listPageReleasePending`、记录 `s_listPageReleaseTick` 与源控件 `s_listPageControl`，按键保持禁用；新增 `listTreatmentPageLoop()` 挂入 dcHmiLoop，最后一次按下后经 `LIST_PAGE_RELEASE_DELAY_MS`（200 ms，参考值）手指确定抬起、两键仍禁用且无活动触摸，才两键清零 → `UpdatePageKeys` 恢复使能 → `treatmentBtnLockRelease` 解锁；连按每次刷新计时。notify 两 case 移除立即 `treatmentReleaseButton`，互锁延迟到释放点解除，窗口保证必触发。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线），hex 正常生成（Code=238916，较第 21 条 +84，RW=1584 +8、ZI=121200 不变）。16.9 已重写。代价：约 200 ms 灰化延迟、约 4 页/秒。无硬件，手感与极端长按（>200 ms）待上板确认；若仍失败，转屏幕“瞬变”按钮根治。
23. **2026-11-24（翻页跟手提速：连续批量读 + 定时器对齐 #102）**：上板确认卡按下已消除，但翻页明显变慢不跟手。两个独立根因：① refresh 第二步对最多 2019 条记录逐条发独立 SPI 事务读 2 字节 id，每事务命令/地址开销累积约百 ms；② 去抖 250 ms 比释放 200 ms 还长，成为实际速率瓶颈（约 2.4–4 页/秒）。数据层新增 `treatmentRecordReadRows(startIndex,buf,bufBytes)`：记录高端向下，从本批最低地址（最大索引）单事务地址自增连续读若干 28 字节行，数据按索引递减序返回；refresh 新增块缓冲 `listRecordChunk`（8 行，224 B），分块批量读并提取每行首字段 `patientId` 计数，记录扫描由约百 ms 降到约 20–30 ms。定时器对齐缩短：`LIST_PAGE_DEBOUNCE_MS` 250→150、`LIST_PAGE_RELEASE_DELAY_MS` 200→150，去抖不再双重限速，翻页上限约 6.7 页/秒且页面内容更快响应。保留 `treatmentRecordGetPatientIdByIndex`（记录页窗口仍在用）。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线），hex 正常生成（Code=239064，较第 22 条 +148，RW=1588 +4、ZI=121428 +228）。16.9 已更新。无硬件，150 ms 灰化手感与慢按/长接触（>150 ms）待上板确认；若仍有极端 case，转屏幕“瞬变”按钮（方法 A）实现零额外延迟。
24. **2026-11-24（记录页 DELETE 键禁用优先 + 返回清零，修删不掉/卡按下 #103）**：现场反馈页面 15 的 `KEY_DELETE_0–4`（20–24）删不掉记录且按键始终保持按下态。代码级根因与翻页键同源：DELETE 为自锁键，旧 notify 在手指仍触摸时先 `treatmentReleaseButton` 写 0，必被活动触摸压过而卡按下；且确认页返回/冷加载（`NotifyScreen(15)`）此前只枚举渲染、不清按钮值，残留按下态无法恢复。新增统一入口 `listTreatmentRecordDeleteKey(slot)`（声明入 dcHmiApp.h）：先校验槽位/`recordTop+slot<recordCount`（非法仅复位互锁返回），清掉残留 `deleteRecordGlobalIndex`，再①对 5 个 DELETE 键 `SetControlEnable(0)` 关闭触摸窗口；②调 `listTreatmentRecordDeleteStart(slot)` 置索引/文案并 `SetScreen(16)`；③`treatmentBtnLockReset()` 解除本页互锁（确认页重新武装）。`NotifyScreen(15)` 枚举前先对 20–28 全部 `SetButtonValue(0)` 清残留，随后 refresh 按 occupied 重使能 DELETE、`UpdatePageKeys` 恢复翻页键；只禁用 DELETE 20–24，不碰 CLOSE(27)/EDIT_PATIENT(28)，确认页与数据层删除/压缩逻辑不变。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线），hex 正常生成（Code=239172，较第 23 条 +108，RW=1588、ZI=121428 不变）。已新增 16.10。无硬件，禁用灰化/确认页切换/返回弹起与记录是否删除待上板确认。
25. **2026-11-24（确认页返回改切页前清理，修 CANCEL 进入即按下/DELETE 锁定/文本不回缩 #105）**：上板复现三个问题——①进确认页 16 后 CANCEL 键显示按下态；②点 OK 删除返回记录页后 DELETE_0–4 仍按下、其余 DELETE 键被锁定无法按；③TIME_ENERGY/SCHEME_WIDTH 文本未向上回缩。代码级根因：本工程 `DeviceScreenNotify=0`，切页后的 `NotifyScreen(15)` 回传不可靠，而旧的 Confirm/Cancel 把清零/重渲染/使能恢复全寄托在该回调，回调不触发则 DELETE 键保持禁用（锁定）、画面不重渲染。修复：①`DeleteStart` 切页前对确认页 OK/CANCEL 下发 `SetButtonValue(0)` 建立未按下基线；②`listTreatmentDeleteRecordConfirm/Cancel` 在 `SetScreen(15)` 之前（确认页仍为当前页）依次对 20–28 清零 → `refreshListRecordDisplay()` 重渲染（剩余记录上移回缩、空槽文本隐藏、DELETE 按 occupied 隐藏禁用/使能）→ `listTreatmentRecordUpdatePageKeys()` 恢复翻页键；`NotifyScreen(15)` 保留为兜底、不再作主路径。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线），hex 正常生成（Code=239580，较第 24 条 +408，RW=1588、ZI=121428 不变）。16.10 与第十四节已重写。无硬件，确认页进入基线、返回弹起/锁定解除与文本回缩待上板确认。
26. **2026-11-24（读写期间确认页 OK 一并物理禁用，修重复按仍发 state=1 #107）**：现场确认 LOAD 页 `KEY_OK` 功能正常（读 CSV、回读核对、返回操作页均正常），但读取过程中继续按该键仍会持续发出按下通知，与预期不符。根因：第 25 条只在确认时对 CANCEL 做了 `SetControlEnable(0)`，OK 仅靠状态7软件门被动拒绝——固件不执行动作，但屏幕控件未禁用、触摸仍会产生通知帧。修复：`listTreatmentUsbConfirm` 状态 7 时在 CANCEL 之外，对 OK 也下发 `SetControlEnable(...,0)`，读写期间两键触摸均不产生任何通知；`listTreatmentUsbLoop` 完成路径在 `treatmentReleaseButton(OK)` 弹起解锁后，对 OK/CANCEL 两键 `SetControlEnable(...,1)` 恢复使能，再 `SetScreen` 回操作页（中止路径本就恢复两键使能）。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线），hex 正常生成（Code=239612，较第 25 条 +32，RW=1588、ZI=121428 不变）。4.3、4.4 与第十三节第 5 条已更新。无硬件，禁用灰化、读取期间按下无通知与返回后使能恢复待上板确认。
27. **2026-11-24（全局性别编码男=1女=2、菜单男性在前、进入页面自动刷新性别文本 #108）**：用户拍板全局性别逻辑编码——男性 `MALE=1`、女性 `FEMALE=2`（与 treatment.h 既有 `GENDER_ENUM` 一致，`gender=0` 表示未选择），并要求 HMI 菜单与程序选项男性排在女性前面。改动：①三个屏幕工程（17 EDIT_PATIENT、18 REGISTER_PATIENT、22 VERIFY_TREATMENT）`MENU_GENDER` 的 options 由 `FeMale;Male;` 改为 `Male;Female;`，菜单索引 `0=男(MALE)`、`1=女(FEMALE)`；②菜单索引↔逻辑编码映射随翻转同步——`dcHmiShowTreatmentCommon` 改 `(gender==MALE)?0:1`，`NotifyMenu` 两处改 `(item==0)?MALE:FEMALE`，核对页 `listTreatmentRefreshVerifyDisplay` 性别段重排（MALE→索引0/"Male"，FEMALE→索引1/"Female"）并把女性文本由旧拼写 `FeMale` 统一为 `Female`；③进入页面自动刷新 `TEXT_GENDER`：`listTreatmentEnterRegisterPage` 切页前按性别下发 `Male`/`Female`/空串，编辑页 `listTreatmentRecordEditPatient` 补同口径刷新（公共函数只更新菜单不更新文本），核对页在显示函数内一并处理。CSV 导入按字符串 `Male`/`Female` 解析、与菜单索引无关，不受影响。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线，自编代码零警告），hex 正常生成（Code=239752，较第 26 条 +140，RO=18592、RW=1588、ZI=121428 均不变）。17.4 与核对页条目已重写。无硬件，菜单顺序、进入自动刷新与三页性别文本待上板确认；.tft 菜单顺序需在 VisualTFT 重新编译并烧录屏幕后才生效，未烧录前上板会与固件映射不一致。
28. **2026-11-24（双重规格全面审计：字段偏移改 offsetof，修数据偏移隐患 #109–112）**：按至高规格（ASCII/控件命名）与病历软件规格双重要求对存储链路做全面审计。用 armcc 编译期负数组断言实测结构布局：`patientRecord_t` sizeof=24（id=0/age=2/gender=3/name=4），`treatmentRecord_t` sizeof=28（patientId=0/recSeq=2/laserPower=4/waveProto=6/magic=7/releaseEnergy=8/releaseTime=12/rtcYear=16/modeScheme=22/reserved1=23/posWidth=24/negWidth=26），自然对齐、无实际错位；地址几何、split/join、CSV 13 列映射、HMI 类型化解析、SPI 24 位地址均正确。发现并修复两类问题：①treatment.h 顶部注释把记录行误写为 24 字节，更正为 28；②全部字节级局部写入的硬编码偏移（记录 magic 的 `+7` 共 7 处、患者正文的 `+2` 共 5 处）改为新增宏 `REC_MAGIC_OFFSET=offsetof(treatmentRecord_t,magic)`、`PAT_BODY_OFFSET=offsetof(patientRecord_t,age)`，正文长度同步用 `PAT_BYTES-PAT_BODY_OFFSET`；位图取整 `(n+7)/8` 为数学运算保留。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线，自编代码零警告），hex 正常生成（Code=239756，较第 27 条 +4，RO=18592、RW=1588、ZI=121428 均不变），证明纯编译期替换、零运行时行为变化。第九节新增第 8 条固化 offsetof 规则。无硬件，偏移自动跟随与实际读写位置待上板确认。
29. **2026-11-24（修复两阶段提交判断常量笔误，AUTOFILL/USB 载入误报 IO #113–114）**：上板 AUTOFILL 与 U 盘载入均失败，屏幕报 `DEMO FILL ERR:2`（`TREATMENT_DEMO_ERR_IO`）。根因不是偏移量（`REC_MAGIC_OFFSET`/`PAT_BODY_OFFSET` 实测仍为 7/2），而是第 28 条把硬编码 `+7` 替换为 `REC_MAGIC_OFFSET` 时，两处 COMMIT 点的错误判断常量被一并误改：`treatmentRecordAdd` 与 `RecordReplaceAt` 中写成了 `if(RowWrite(...) != TREATMENT_EPROM_ERR_IO)`，正确应为 `!= TREATMENT_EPROM_OK`。`RowWrite` 成功返回 `TREATMENT_EPROM_OK=0`，使 `0 != ERR_IO(4)` 恒为真，COMMIT 写入即使成功也立即返回 `TREATMENT_EPROM_ERR_IO`；两条路径（AUTOFILL 经 `treatmentEpromAdd`、USB 载入经 `treatmentEpromWriteAt` 追加路径）都汇聚到 `treatmentRecordAdd`，故首个 COMMIT 点必败。修复：两处判断常量改回 `TREATMENT_EPROM_OK`，并全量核对 12 处 `if(RowWrite...)` 均为 `!= TREATMENT_EPROM_OK`，无其他同类笔误。验证盲区教训：第 28 条的“反汇编/段表等价”比较的两个版本（hard/off）都基于同一含笔误的工作区文件构造、仅改偏移表达，保留了共有的判断常量错误，故只能证明偏移表达等价、无法证明判断逻辑正确——基线本身带 bug 时等价性证明不成立；改判断类语句时必须逐字核对返回值语义（成功判 `OK`，不是判 `ERR_IO`）。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线），hex 正常生成（Code=239752，较第 28 条 −4，RO=18592、RW=1588、ZI=121428 均不变）。无硬件，AUTOFILL 填满与 U 盘载入实际写入待上板确认。
30. **2026-11-25（病历保存口径改为 ready 会话级累计 #124）**：用户澄清病历记录单位不是单次脚踏发射周期，而是一次 ready 会话——进入 ready 后只要有过激光发射，退出 ready 回待机时才弹一次核对页 22，保存整个 ready 期间累计的发射时间/能量（多次踩脚踏累加为一条记录）。改动均在 `dcHmiApp.c`：①删除每次脚踏弹起（发射→等待触发）即抓快照并弹页的 `listTreatmentStepWatch`（连同其 dcHmiLoop 调用与 `driveStep` 字段），新增 `listTreatmentExitReadyVerify()`——在正常点 READY 键退出（`R_STANDBY_KEY_STNADBY_UP`）时调 `listTreatmentPendingCapture()` 用整个 ready 累计值抓一次快照，确有发射（`EM_LASER_TRIG_TIME > 0`）才调 `listTreatmentVerifyAfterLaser()` 弹一次核对页并返回 1，无发射返回 0 直接回待机；②等待触发态与发射态两个退出点在 `returnStandbyDisplay` 前接入该判定，弹页即 return 不回待机；急停/故障/READY_ERROR 异常路径不弹页。发射计数本就只在进入 ready 时清零、ready 内持续累加，故累计口径天然满足，数据层零改动。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线，自编零警告），hex 正常生成（Code=241344，较仿真脚踏版 +4，RO=18660、RW=1612、ZI=121424）。无硬件，多次踩脚踏累计、退出才弹一次、无发射不弹等待上板确认。
31. **2026-11-25（补核对页 22 控件清单与 SELECT_TREATMENT 规格 #125）**：核查页面 22 两个行为并补齐规格缺失。代码级结论：①SAVE_RECORD 对已有患者（`id != 0`）经 `treatmentEpromAddToPatient` 只追加 28 字节治疗记录、患者主表 24 字节不变；对新患者（`id == 0`）跳注册页 18，注册确认时 `treatmentPatientCreate` 建患者 + `treatmentEpromAddToPatient` 一并落治疗记录。页面 22 的 `TEXT_NAME`/`TEXT_AGE` 为纯显示、无文本输入回调，本页不录入姓名/年龄，新患者信息统一在注册页填；`MENU_GENDER` 可改但已有患者路径不回写患者主表。②SELECT_TREATMENT（控件 32）经 `listTreatmentVerifySelect` 置 `verifySelectMode = 1` 进列表页 13，选中患者填入 `treatmentLog` 回核对页 22（不回待机），CLOSE 走 `listTreatmentVerifySelectCancel` 取消回核对页，再 SAVE_RECORD 即把治疗记录追加到选中患者、其历史记录页 15 可见；功能完整闭环。本次为文档对齐、零代码改动：新增 5.6 节（页面 22 完整控件表、本页可编辑边界、SAVE 两路径落盘时序、SELECT_TREATMENT 完整流程与强制约束）。无代码改动，无需重新编译。
32. **2026-11-25（核对页 22 改为本页直接录入患者信息，废弃跳注册页 #126）**：用户拍板新流程——患者姓名、年龄、性别在核对页 `GDDC_PAGE_VERIFY_TREATMENT`（22）本页直接输入，点 SAVE_RECORD 不再跳注册页 18。本次为规格固化、零代码改动：①重写 5.6 节——`TEXT_NAME`/`TEXT_AGE`（控件 2/3）对新患者改为可键盘输入（关联屏幕系统键盘，经 `NotifyText` 回写 `treatmentLog`，复用 17/18 页同名控件逻辑），`MENU_GENDER` 本页选择；SAVE_RECORD 对新患者先在本页校验（姓名非空、性别、年龄 1–150），通过则 `treatmentPatientCreate` 建患者 + `treatmentEpromAddToPatient` 落治疗记录、不切页，失败在本页提示、就地修改；已有患者仍只读、只追加记录。②同步修订 5.5 第 5 条新患者口径；17.1 移除“核对页 SAVE_RECORD 进注册页”入口，注册页 18 仅保留列表页 `CREATE_NEW` 手动新建，17.2 CANCEL 改为回列表页。驱动层已具备 `NotifyText` 文本输入回调与 `ShowKeyboard` 系统键盘，本页录入可行；后续代码落地需同步改 VisualTFT 屏幕工程（NAME/AGE 控件可输入）与固件 `NotifyText` 分支。无代码改动，无需重新编译。
33. **2026-11-25（细化页面 22 控件职责，性别改 TEXT_GENDER 文本框输入 #127）**：用户逐控件明确页面 22 规格，本次为文档固化、零代码改动。控件口径：①`TEXT_ID`（1）只读，显示插空（最小空缺）患者 ID；②`TEXT_NAME`（2）输入患者名字、`TEXT_AGE`（3）输入患者年龄、`TEXT_GENDER`（9）输入患者性别（输入 `Male`/`Female`，按字符串映射 `MALE`/`FEMALE`）——三者均为本页文本输入控件；③SUMMARY 系列只读：`TIME`（4）记录生成 RTC、`ENERGY`（5）累计总能量、`OUT_TIME`（6）累计总时间、`POWER`（7）激光功率、`SCHEME`（8）方案/发射模式且显示方式沿用既有规则；④三按键：SAVE_RECORD（30）校验后储存、DISCARD_RECORD（31）放弃、SELECT_TREATMENT（32）跳页面 13 经 `GDDC_PAGE_LIST_TREATMENT_KEY_SELECT_PATIENT_0–4`（控件 20–24）选患者后回 22 确认是否在该患者储存，CLOSE 取消回 22。重写 5.6 控件表与流程，明确 `MENU_GENDER`（20）/`KEY_GENDER`（33）不承担本页性别输入职责、停用待落地核对；同步修订 17.4，把页面 22 性别与 17/18 的 `MENU_GENDER` 下拉区分。无代码改动，无需重新编译。
34. **2026-11-25（一致性审查收口：ID 回收、恢复 AC6、性别三页统一、完整宏名全量改写 #128–131）**：用户对《AI_RULES.md》与本规格一致性审查的全部问题逐条拍板，本次为纯文档修订、代码零改动。①患者 ID 口径统一为"回收补空缺"——新建患者最小空缺优先复用、无空缺才取最大 ID 加 1，`NEXT_ID` 仅作高水位（见第十五节第 3 条、17.3），推翻"单调递增不回收"旧文；②本分支恢复 AC6 验证——自编源码 AC5（armcc）与 AC6（armclang）各自完整 Rebuild 均须 0 Error，为将来分支合并做准备；AC6 当前错误（FreeRTOS 缺 GCC/ARM_CM4F port、dcHmiApp.c static 冲突）如实记为待完成的迁移配套工作，而非标准豁免；③性别三页统一——`GDDC_PAGE_EDIT_PATIENT`、`GDDC_PAGE_REGISTER_PATIENT`、`GDDC_PAGE_VERIFY_TREATMENT` 均由 `MENU_GENDER` 下拉选择（经 `NotifyMenu` 回写 `MALE=1`/`FEMALE=2`）、`TEXT_GENDER` 只读显示，页面 22 回退到与 17/18 一致的菜单方案，`TEXT_GENDER` 不再承担文本输入；④完整宏名全量改写——正文一切正式指代必须写完整宏名（明确"哪个页面下的哪个控件"），禁止"页面 13""OK 15"这类简写，仅在 16.1 对照表与变更日志中保留编号；⑤明确 Ready 无实际激光发射退出到 STANDBY 时不进入 `GDDC_PAGE_VERIFY_TREATMENT`，`GDDC_PAGE_LIST_TREATMENT_KEY_CREATE_NEW` 是手动新建患者、与 Ready→Standby 状态流程完全无关；⑥核对头文件后纠正 13.5 控件前缀（实际为 `GDDC_PAGE_EDIT_PATIENT_*`，原误写 `GDDC_PAGE_EDIT_TREATMENT_*`）。无代码改动，无需重新编译。
35. **2026-11-25（修复落盘失败被静默忽略：treatmentEpromAddToPatient 返回值统一检查 #144）**：用户要求修复"先建患者、再加记录"两步流程中第二步返回值被 `(void)` 忽略的问题——原模式在接近满盘（剩余空间够建患者 24B、不够加记录 28B）或 IO/欠压错误时，会出现患者已建但治疗记录未存、却仍清 `pendingValid` 回待机且无提示。改动均在 `dcHmiApp.c`：`listTreatmentVerifySaveRecord`（已有患者/新患者两路径）与 `listTreatmentRegisterConfirm`（`hadPending` 分支）共 3 处，把 `(void)treatmentEpromAddToPatient(...)` 改为接收 `ce` 并判断，非 `TREATMENT_EPROM_OK` 即在本页提示 `Save failed, please retry!`、保留 `pendingValid` 与待存、不回待机不切页；成功才清待存回待机。新患者失败后 `treatmentLog.id` 已为 newId，重试走"已有患者"分支、不会重复建患者。`treatment.c` 内 demo 填充调用点本就正确处理返回值。AC5 Rebuild：0 Error、2 Warning（`usbh_cdc` 固定基线，自编零警告），hex 正常生成（Code=241660，较改前 +48，ZI=121424 不变）。HMI 实际提示与重试手感待上板确认。
36. **2026-11-25（进入核对页22/注册页18前无条件清空指定显示控件 #146）**：用户要求新增强制规则——每次进入 `GDDC_PAGE_VERIFY_TREATMENT`（22）与 `GDDC_PAGE_REGISTER_PATIENT`（18）前，先把指定显示控件清空再渲染，杜绝上一次录入/提示残留。固件在 `dcHmiApp.c` 新增两个静态函数 `listTreatmentClearVerifyFields()`（清空 `GDDC_PAGE_VERIFY_TREATMENT_TEXT_NAME`/`GDDC_PAGE_VERIFY_TREATMENT_TEXT_AGE`/`GDDC_PAGE_VERIFY_TREATMENT_TEXT_GENDER`/`GDDC_PAGE_VERIFY_TREATMENT_TEXT_MSG`，控件 2/3/9/10）与 `listTreatmentClearRegisterFields()`（清空 `GDDC_PAGE_REGISTER_PATIENT_TEXT_NAME`/`GDDC_PAGE_REGISTER_PATIENT_TEXT_AGE`/`GDDC_PAGE_REGISTER_PATIENT_TEXT_GENDER`/`GDDC_PAGE_REGISTER_PATIENT_TEXT_SUMMARY_0`，控件 2/3/4/5），分别在 `listTreatmentRefreshVerifyDisplay`、`listTreatmentEnterRegisterPage` 最开头调用，执行“先清后绘”；已选患者资料随后正常回填，新患者保持空白。`GDDC_PAGE_VERIFY_TREATMENT_TEXT_MSG` 进入时不再显示默认引导语、保持空白，仅校验/落盘失败时显示具体错误。正文规则见 5.6 第 6 条与 17.4。AC5 Rebuild 结果以编译日志为准，HMI 实际清空手感待上板确认。
37. **2026-11-25（注册页年龄空白+选择模式新建返回层级+核对页脉宽补全 #147/#148/#149）**：用户上板发现并要求三项修复，均固化为强制规则。① 注册页 `GDDC_PAGE_REGISTER_PATIENT_TEXT_AGE`（控件 3）进入时残留数字 `0`：改 `dcHmiShowTreatmentCommon`，仅 `age != 0` 才格式化数字、`age = 0` 下发空串，保持完全空白（口径覆盖编辑页17/待存显示）。② 核对页22 点 `GDDC_PAGE_VERIFY_TREATMENT_KEY_SELECT_TREATMENT` 进列表13（`verifySelectMode=1`）后改点 `GDDC_PAGE_LIST_TREATMENT_KEY_CREATE_NEW` 新建患者：注册页点 `GDDC_PAGE_REGISTER_PATIENT_KEY_OK` 只 `treatmentPatientCreate` 建患者、不 AddToPatient、保留 `pendingValid` 与 `verifySelectMode`，点 `GDDC_PAGE_REGISTER_PATIENT_KEY_CANCEL` 不写入，两出口都经 `listTreatmentGoListPage` 回列表页13，由操作者决定是否选中新建患者，选中再回核对页22。③ 核对页 `GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_SCHEME`（控件 8）脉冲模式漏脉宽：改为 `<方案名> <序号> - Pulse - ON <posWidth> / OFF <negWidth> ms`，与历史记录页13.2 同口径。正文见 5.6 第 3/5 条与 17.4。AC5 Rebuild 结果以编译日志为准，HMI 实际效果待上板确认。
38. **2026-11-25（进入 READY 画面冻结防闪烁 #150）**：用户反馈点 `GDDC_PAGE_STANDBY_KEY_STANDBY` 进入 READY 时屏幕“闪一下”。先回退提交 957b3cb8 基线 A/B 验证，确认该版本同样闪烁，属 `SetScreen` 切页整屏重绘的固有现象、非功能改动引入。修复：在 `dcHmiLoop` 进入 READY 分支，于 `updateReadyDisplay` 预刷新与 `SetScreen` 前后成对调用 `SetScreenUpdateEnable(0)`/`(1)`，冻结期间屏幕保持 STANDBY 并缓存后台 READY 页更新，解冻时一次性重绘完整 READY 页，消除中间清屏/逐元素绘制。正文规则见新增 5.7。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线），Code=241880，hex 正常生成；实际防闪手感待上板确认。
39. **2026-11-25（注册页/核对页校验失败按键松开兜底释放，修卡按下 #151）**：用户上板发现注册页 `GDDC_PAGE_REGISTER_PATIENT`（18）姓名/性别/年龄填写有误时，点 `GDDC_PAGE_REGISTER_PATIENT_KEY_OK` 显示 `Invalid input, please re-enter!` 后该键未弹起。代码级根因：按下（`state=1`）立即回发的 `SetButtonValue(...,0)` 与仍在进行的物理触摸竞争、被活动触摸压过，而松开（`state=0`）无任何兜底。修复在 `dcHmiNotifyButton.c`：`GDDC_PAGE_REGISTER_PATIENT_KEY_OK` 与同构的 `GDDC_PAGE_VERIFY_TREATMENT_KEY_SAVE_RECORD` 两 case 保留按下分支“先 `treatmentReleaseButton` 再校验”，新增 `else`（`state=0`）分支再下发一次 `SetButtonValue(...,0)`，手指抬起后无活动触摸、释放帧可靠生效。正文规则见新增 17.6。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线，自编零警告），Code=241888，hex 正常生成；实际按键弹起手感待上板确认。
40. **2026-11-25（弹出层返回按键释放 + 二次进入切页后重发清空，修卡按下/残留 #152/#153）**：用户上板发现两个问题——①从系统键盘/性别下拉菜单等弹出层返回注册页时 `GDDC_PAGE_REGISTER_PATIENT_KEY_OK` 未弹起；②第二次进入注册页时姓名/性别/年龄残留第一次输入。代码级根因：弹出层关闭重绘会恢复按钮按下态，且 `DeviceScreenNotify=0` 无法捕获返回；`SetScreen` 切页加载重绘会覆盖切页“前”的清空帧。修复均在固件：新增 `treatmentPopupReleaseArm`/`treatmentPopupReleaseLoop`（挂入 `dcHmiLoop`），在 `NotifyText`/`NotifyMenu` 装填、延迟 150 ms 弹出层关闭后对本页按钮重发 `SetButtonValue(...,0)`，不改使能、无灰化；`listTreatmentEnterRegisterPage` 改为 `SetScreenUpdateEnable(0)` 冻结 → `SetScreen` → 切页后 `listTreatmentClearRegisterFields` 清空并重新渲染 → `SetScreenUpdateEnable(1)` 解冻，清空帧落在屏幕加载之后、可靠生效且无旧值闪烁。正文规则见新增 17.7。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线，自编零警告），Code=242140，hex 正常生成；实际弹起与清空手感待上板确认。
41. **2026-11-25（注册页冷加载完成重发清空，修 READY 流程后再进注册页残留 #154）**：用户上板发现先用 `GDDC_PAGE_LIST_TREATMENT_KEY_CREATE_NEW` 新建过患者、再进 READY 发射激光回 STANDBY 后，再次进入注册页时姓名/年龄/性别仍残留上一次输入。代码级根因：屏幕切页存在冷加载窗口，切页“前”的清空帧被加载重绘覆盖、切页“后立即”的帧在冷加载窗口丢帧（#153 方案仍不可靠）；而 `NotifyScreen` 中注册页分支原本为空，未像其他页面那样在加载完成后重发。修复在固件：将“先清空再渲染”封装为 `listTreatmentRenderRegisterDisplay`；`listTreatmentEnterRegisterPage` 改为冻结后预刷新后台 → `SetScreen` → 解冻；并在 `NotifyScreen` 的 `GDDC_PAGE_REGISTER_PATIENT` 分支（冷加载完成必上报）再次调用该渲染函数重发，帧不丢失、可靠清空。正文规则见 17.7 第 3/4 条。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线，自编零警告），Code=242148，hex 正常生成；实际清空手感待上板确认。
42. **2026-11-25（核对页新患者路径数据层清空 + 冷加载重发，修核对页带旧患者信息 #155）**：用户上板发现之前新建过患者后，激光停光自动弹出核对页 `GDDC_PAGE_VERIFY_TREATMENT`（22）时仍带上过去患者的姓名/年龄/性别，新患者这三项应为空白。代码级根因：停光快照 `listTreatmentCtx.pending` 整条复制 `treatmentLog`（含旧患者字段），`listTreatmentVerifyAfterLaser` 只把 `id` 置 0、未清 name/age/gender，且 `NotifyScreen` 无核对页分支。修复在固件：`listTreatmentVerifyAfterLaser` 中当 `listTreatmentPrefillSelectedPatient` 返回 0（无选中患者）时，将 `age` 置 0、`gender` 置 0、`name` 清空，选中患者才回填；并在 `NotifyScreen` 新增 `GDDC_PAGE_VERIFY_TREATMENT` 分支，冷加载完成后重新 `listTreatmentRefreshVerifyDisplay` 重发。正文规则见 5.6 第 6 条新增子项。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线，自编零警告），Code=242176，hex 正常生成；实际空白手感待上板确认。
43. **2026-11-25（核对页选择患者持久归属 + 待机显示 + 后续自动归属，#156）**：用户要求治疗结束弹核对页、点 `GDDC_PAGE_VERIFY_TREATMENT_KEY_SELECT_TREATMENT`（32）进列表页选具体患者（`GDDC_PAGE_LIST_TREATMENT_KEY_SELECT_PATIENT_0–4`）后，要把该患者记录为当前选中患者，回待机页 `GDDC_PAGE_STANDBY_TEXT_PATIENT_NAME` 显示其名，且重新选择前再次激光核验默认归属该患者。代码级根因：`listTreatmentSelect` 的 `verifySelectMode` 分支原只把患者填入 `treatmentLog`、刻意不更新 `selectedPatientId/Name`（旧口径“不改变待机页归属”），导致选择不持久、待机名不更新、下次核验无法自动回填。修复在固件：该分支在填 `treatmentLog` 后同步更新 `selectedPatientId`/`selectedPatientName`（保留回核对页 SAVE 流程，不立即回待机）；SAVE 落盘后 `returnStandbyDisplay` → `updateStandbyDisplay` 经 `listTreatmentWriteStandbyPatientName` 显示患者名；下次激光 `listTreatmentVerifyAfterLaser` 经 `listTreatmentPrefillSelectedPatient` 自动回填该患者。正文规则见 5.6 第 5 条（旧“不改变归属”表述已修订）。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线，自编零警告），Code=242204，hex 正常生成；实际归属与待机显示待上板确认。
44. **2026-11-25（核对页本页新建患者持久归属 + 待机显示，#157）**：用户要求在核对页 `GDDC_PAGE_VERIFY_TREATMENT`（22）本页直接录入新患者姓名/年龄/性别并 SAVE 储存后，回待机页 `GDDC_PAGE_STANDBY_TEXT_PATIENT_NAME` 也要显示该新建患者名，且重新选择前后续治疗记录归属该患者。代码级根因：`listTreatmentVerifySaveRecord` 新患者成功路径（`treatmentPatientCreate` + `AddToPatient` 成功后）原只清 `pendingValid` 回待机，未设置 `selectedPatientId/Name`，导致待机名空白、下次激光仍走新患者路径而非归属。修复在固件：新患者成功落盘后、回待机前，设置 `selectedPatientId = newId`、`selectedPatientName = treatmentLog.name`；回待机经 `listTreatmentWriteStandbyPatientName` 显示其名，下次激光 `listTreatmentVerifyAfterLaser` 经 `listTreatmentPrefillSelectedPatient` 自动回填归属。正文规则见 5.6 第 4 条新患者子项。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线，自编零警告），Code=242244，hex 正常生成；实际新建归属与待机显示待上板确认。
45. **2026-11-25（核对页进入三键弹起基线，修 SAVE 键再次进入卡按下 #158）**：用户上板发现核对页 `GDDC_PAGE_VERIFY_TREATMENT`（22）的 `GDDC_PAGE_VERIFY_TREATMENT_KEY_SAVE_RECORD`（30）在使用过一次后，再次进入该页时按钮停在按下态、未弹起。代码级根因：SAVE 成功路径在按下（state=1）时先 `treatmentReleaseButton` 再 `returnStandbyDisplay` 切页，切走瞬间手指仍可能压着按钮（活动触摸竞争），切页后手指松开的 state=0 帧已不在当前页，屏幕保存并在下次冷加载重绘时恢复按下态；而 `listTreatmentEnterVerifyPage` 原未对按键做弹起基线。修复在固件：新增 `listTreatmentReleaseVerifyKeys()` 对三键（SAVE=30/DISCARD=31/SELECT=32）下发 `SetButtonValue(...,0)`，进入函数切页前调用一次、`NotifyScreen` 冷加载完成后再调用一次兜底。正文规则见 5.6 第 6 条新增子项。AC5 Rebuild：0 Error、2 Warning（usbh_cdc 固定基线，自编零警告），Code=242292，hex 正常生成；实际弹起手感待上板确认。
