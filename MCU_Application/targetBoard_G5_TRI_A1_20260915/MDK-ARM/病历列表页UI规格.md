# 病历列表页 UI 行为规格 — GDDC_PAGE_LIST_TREATMENT（页面 ID 13）

本文件固化病历列表页页码、搜索、关闭按钮、患者选择闭环、删除患者确认，USB 操作页与导出/导入确认页的**强制交互行为**，以及 11 个病历相关页面的**按键互锁**（第十六节）。任何 AI 维护此页面前必须先读完本文件，并按此实现，不得擅自更改匹配口径、排序规则、显示格式、页面跳转出口、患者选择归属、删除确认流程与按键互锁规则。

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

---

## 二、搜索框 GDDC_PAGE_LIST_TREATMENT_TEXT_SEARCH_NAME 与姓名列 TEXT_NAME_0–4

1. **前缀匹配、大小写敏感（不忽略大小写）**：搜索框输入按姓名前缀**逐位直接比较**，任一位大小写不同即不匹配，输入字母全部命中才匹配；空串 = 不过滤、显示全部患者。
   - 输入小写 `l` 只命中小写 l 开头的姓名，**不**命中大写 `L` 开头；输入 `li` 只命中 `li` 开头的姓名。
   - 实现沿用 `listTreatmentMatchFind`，比较时直接 `name[i] != findText[i]`，不做大小写归一。
2. **大小写敏感的 ASCII 字典序全序排序**：命中结果必须先按字符原始值（ASCII）排序，再写入 `TEXT_NAME_0–4`：
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

本节为**新增强制规格**，与旧描述冲突时以本节为准。控件编号必须与屏幕工程 `vTFT_HMI/GDDC_PAGE_OPERATOR_USB.tft` 完全一致（`TEXT_SUMMARY` = 1、`TEXT_SUMMARY_USB` = 2、`KEY_SAVE_UDISK` = 3、`KEY_LOAD_UDISK` = 4、`KEY_CANCEL` = 5）；若宏值被改成 10/11/12 等与屏幕工程不符的编号，按键事件无法命中，表现为按键无响应。

1. 列表页 `GDDC_PAGE_LIST_TREATMENT_KEY_OPERATOR_USB`（控件 40）按下（`state = 1`）调用 `enterOperatorUsbPage()`：置 `NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LIST_TREATMENT`、`NVRAM0[EM_DC_PAGE] = GDDC_PAGE_OPERATOR_USB`，先 `refreshOperatorUsbDisplay()` 预刷新本页控件，再 `SetScreen(19)`，避免上一页控件残留。
2. `TEXT_SUMMARY`（控件 1）显示机内病历储存概况，**文本控件内的显示内容一律英文**（英文显示为全工程至高规格，适用范围与人工授权要求见根目录 `AI_RULES.md`），格式固定为 `Existing patients: X, total treatment records: Y`，即“现有患者数量X，累计历史治疗记录Y”的英文表述：
   - `X` = `treatmentEpromGetPatientCount()`，机内去重患者数；
   - `Y` = `listTreatmentGetCount()`（即 `NVRAM0[DM_TREATMENT_NUM]`，负值防御返回 0），累计历史治疗记录数。
   - 该文本框在进入本页与页面冷加载完成时都必须刷新，不受列表页搜索过滤影响（全局口径）。
   - 文案为纯 ASCII，不存在屏幕字库中文编码（GB2312/UTF-8）不匹配导致乱码的风险。
3. `TEXT_SUMMARY_USB`（控件 2）在进入本页时显示 U 盘在位状态：`UDISK OK` / `NO UDISK`；导出/导入完成后显示本次结果，从确认页取消返回时清空。其内容统一由 `listTreatmentCtx.usbText` 维护、经 `refreshOperatorUsbDisplay()` 下发，页面冷加载重发同一内容，不会被在位状态覆盖；从列表页重新进入本页时才恢复为在位状态。
4. `KEY_SAVE_UDISK`（控件 3）按下调用 `listTreatmentSaveUsbStart()`，进入导出确认页 `GDDC_PAGE_OPERATOR_USB_SAVE`（页面 ID 20），不得直接读写 U 盘。
5. `KEY_LOAD_UDISK`（控件 4）按下调用 `listTreatmentLoadUsbStart()`，进入导入确认页 `GDDC_PAGE_OPERATOR_USB_LOAD`（页面 ID 21），不得直接覆盖机内病历。
6. `KEY_CANCEL`（控件 5）按下调用 `listTreatmentOperatorUsbBack()`：不改动 EPROM，置 `NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_TREATMENT`，刷新列表后 `SetScreen(13)`，返回上一级病历列表页。
7. 进入本页时 `usbState` 必须为 0（空闲），否则触摸总闸会屏蔽按键。

### 4.1 确认页通用约定

导出确认页 `GDDC_PAGE_OPERATOR_USB_SAVE`（页面 ID 20）与导入确认页 `GDDC_PAGE_OPERATOR_USB_LOAD`（页面 ID 21）分别独立，由 `listTreatmentCtx.usbOp` 区分流程（`1` = 导出 SAVE，`2` = 导入 LOAD）；两个确认页上的文字按根目录 `AI_RULES.md` 至高规格**一律英文显示**。`KEY_SAVE_UDISK` / `KEY_LOAD_UDISK` **都不立即读写 U 盘**，先进入对应确认页。

### 4.2 导出 SAVE（usbOp = 1，点 KEY_SAVE_UDISK）

1. 进入时刷新以下两个文本框（屏幕工程该页只有控件 1、2；文案为英文，中文语义见括注）：
   - `TEXT_SUMMARY_0`（控件 1，动态）：`Export X patients and Y saved treatment records to USB?`
     - “确认将共 X 位患者及共 Y 条已保存的治疗记录导出至 USB？”
     - `X` = 机内患者数 `treatmentEpromGetPatientCount()`；`Y` = 机内治疗记录数 `listTreatmentGetCount()`（即 `NVRAM0[DM_TREATMENT_NUM]`，负值防御返回 0），取**进入本页时**的机内当前值。
   - `TEXT_SUMMARY_1`（控件 2）：`The existing patient backup in this USB will be replaced.`
     - “此 USB 中的原有患者备份将被替换。”
   - 原 `TEXT_SUMMARY_2/3` 文案作废，本页不再向控件 3/4 写入。
2. `KEY_CANCEL`（控件 10）：取消写入，不修改 U 盘与机内 EPROM，返回操作页 `GDDC_PAGE_OPERATOR_USB`，并**清空**该页 `TEXT_SUMMARY_USB`（写空串）；该页 `TEXT_SUMMARY` 保持进入本页前显示的内容不变。
3. `KEY_OK`（控件 11）：授权把机内病历转换成 CSV 写入 U 盘，复用 `treatmentLogSaveToUdisk`，文件名由 `TREATMENTLOG_FILENAME` 宏指定（`/treatment_v1.csv`，覆盖同名文件）；实际写入在 `listTreatmentUsbLoop` 中执行一次，不在按键回调里阻塞。
4. 写入完成后自动返回 `GDDC_PAGE_OPERATOR_USB`，并在 `TEXT_SUMMARY_USB`（操作页控件 2）显示本次备份概况：
   - 成功：`USB backup: X patients, Y treatment records`
     - `X` = 机内患者数 `treatmentEpromGetPatientCount()`；`Y` = 本次实际写入 U 盘的治疗记录数 `listTreatmentCtx.usbCount`。
   - 失败按错误码：`NO UDISK` / `NO RECORDS` / `USB OPEN FAILED` / `USB BACKUP FAILED`
5. 结果栏内容统一保存在 `listTreatmentCtx.usbText`，由 `refreshOperatorUsbDisplay()` 下发；因此回到操作页后的页面冷加载刷新不会把结果覆盖成 `UDISK OK`。重新从列表页进入操作页时，`usbText` 恢复为 U 盘在位状态（`UDISK OK` / `NO UDISK`）。
6. 导出流程**只写 U 盘、不删除机内病历**（强制规格，见第八节，优先于任何功能改动）；确认页只提示 U 盘原有备份将被替换，**不得出现任何“设备档案将被清除”的文案**，也不得据此实现清空。

### 4.3 导入 LOAD（usbOp = 2，点 KEY_LOAD_UDISK）

1. 进入时刷新以下两个文本框（屏幕工程该页只用控件 1、2；`X`/`Y` 取**进入本页时**的机内当前值）：
   - `TEXT_SUMMARY_0`（控件 1，动态）：`Replace all X patients and Y treatment records on the device with the USB backup?`
     - “确认用 USB 的备份替换设备中全部 X 位患者及 Y 条治疗记录？”
     - `X` = 机内患者数 `treatmentEpromGetPatientCount()`；`Y` = 机内治疗记录数 `listTreatmentGetCount()`（即 `NVRAM0[DM_TREATMENT_NUM]`，负值防御返回 0）。
   - `TEXT_SUMMARY_1`（控件 2，动态）：`Backup contents: X patients, Y treatment records.`
     - “备份内容：X 位患者, Y 条治疗记录。”，数值与上一条同源。
   - 原 `TEXT_SUMMARY_2/3` 文案作废：控件 3 下发空串避免残留，控件 4 不写入（屏幕未建）。
2. `KEY_CANCEL`（控件 10）：取消载入，不读写 U 盘、不修改机内 EPROM，返回操作页 `GDDC_PAGE_OPERATOR_USB`（与导出共用 `listTreatmentUsbCancel()`，返回时同时清空该页 `TEXT_SUMMARY_USB`）。
3. `KEY_OK`（控件 11）：授权从 U 盘读取由 `TREATMENTLOG_FILENAME` 宏指定文件名的 CSV（`/treatment_v1.csv`）并载入本机病历空间，复用 `treatmentLogLoadFromUdisk`；实际读写在 `listTreatmentUsbLoop` 中执行一次，不在按键回调里阻塞。
4. 载入完成后自动返回 `GDDC_PAGE_OPERATOR_USB`，**必须再回读核对**：`treatmentLogVerifyUdisk()` 重新打开 U 盘同一 CSV，按索引逐条与本机 EPROM 病历比较全部字段（ID/姓名/性别/年龄/功率/波长/方案/能量/治疗时间），并要求 U 盘数据行数与机内条数完全一致。`TEXT_SUMMARY_USB`（操作页控件 2）按下述口径显示：
   - 载入成功**且**回读比较完全相同：`Backup imported from USB. Device records have been replaced.`（“已从 USB 导入备份，设备档案已替换。”）
   - 载入失败，**或**比较存在任何差异（U 盘拔出、文件读不出、行数不一致、任一字段不同）：`USB backup import failed!`（“导入USB备份失败!”）
   - 旧口径（按 `TREATMENT_USB_ERR_*` 分别显示 `NO UDISK` / `NO FILE` / `BAD FILE` / `USB IMPORT FAILED`）作废，统一为上面两条。
5. 结果栏内容同样存入 `listTreatmentCtx.usbText`，由 `refreshOperatorUsbDisplay()` 下发，回到操作页后的冷加载刷新不会覆盖结果；返回时操作页 `TEXT_SUMMARY` 按载入后的机内数量刷新。

### 4.4 通用触摸与状态约束

1. 确认页等待期间（状态 6）只放行 CANCEL/CONFIRM，读写执行期间（状态 7）屏蔽一切触摸。
2. 确认/取消回调导出/导入通用：`listTreatmentUsbConfirm`（状态 6→7）、`listTreatmentUsbCancel`（状态 6→0 回操作页）。
3. 若确认页被别处切走（如关机确认/休眠），轮询检测到当前页不符即放弃本次流程并退出忙状态，避免触摸被永久屏蔽。

---

## 五、患者选择闭环（KEY_ENTER_TREATMENT / KEY_SELECT_PATIENT_0–4 / TEXT_PATIENT_NAME）

本部分固化“待机页进入列表 → 选中患者 → 自动返回待机并显示患者名 → 后续病历归属该患者”的完整闭环。涉及控件：待机页 `KEY_ENTER_TREATMENT`（控件 46）、待机页 `TEXT_PATIENT_NAME`（控件 39）、列表页 `KEY_SELECT_PATIENT_0–4`（控件 20–24）。

### 5.1 待机页进入列表页（已实现，必须保留）

1. 在待机页点 `GDDC_PAGE_STANDBY_KEY_ENTER_TREATMENT`（控件 46），按钮回调只置标志 `R_STANDBY_KEY_ENTER_LIST_TREATMENT_DOWN`。
2. 主循环待机状态机检测到该标志后：置 `FSMSTEP_LIST_TREATMENT`、`NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_TREATMENT`，先 `enterListTreatmentPage()` 重建患者视图并刷新，再 `SetScreen(13)`，随后清除进入标志。
3. 该入口行为为强制规格，不得改为直接进编辑页或其他页面。

### 5.2 列表页选中患者并自动返回待机页

1. 点 `KEY_SELECT_PATIENT_0–4`（控件 20–24）调用 `listTreatmentSelect(slot)`，其中 `slot = control_id - GDDC_PAGE_LIST_TREATMENT_KEY_SELECT_PATIENT_0`（取值 0–4），分别对应窗口内 `TEXT_NAME_0–4` 的患者。
2. `slot` 越界（`>= 5`）直接返回；对应视图位置 `viewPos = topIndex + slot` 若 `>= filteredCount`（空槽位）则不响应。
3. 命中有效患者时，`listTreatmentSelect` 必须依次完成：
   - 置 `selectedIndex = viewPos`，使列表页对应 `SELECT_PATIENT` 按钮高亮（沿用 `refreshListTreatmentDisplay`）。
   - 经 `listTreatmentGetViewPatient(viewPos, &pat)`（经紧凑索引 `sortedIndex[viewPos]` O(1) 定位全局索引，再单次回读整行）解析出患者原始记录，把稳定患者编号缓存到 `listTreatmentCtx.selectedPatientId`、姓名缓存到 `listTreatmentCtx.selectedPatientName`。
   - **自动返回待机页**：统一走 `returnStandbyDisplay()`（切回 `FSMSTEP_STANDBY`、`SetScreen(GDDC_PAGE_STANDBY)`），不得停留在列表页，也不得进入编辑页。

### 5.3 待机页 TEXT_PATIENT_NAME 显示选中患者名

1. 待机页患者名由 `updateStandbyDisplay()` 统一刷新（`returnStandbyDisplay()` 会先调用它预刷新），保证任何路径回到待机页显示都一致：
   - `selectedPatientId != 0`（已选患者）：`SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_PATIENT_NAME, selectedPatientName)`，显示刚选中的患者名字。
   - `selectedPatientId == 0`（开机后尚未选择）：向该控件写空串清空，**不得残留上一次/屏幕工程默认内容**。
2. 显示内容为患者姓名原文（`patientRecord_t.name`），不追加编号、不做大小写转换。

### 5.4 后续病历在该患者名下储存

1. 患者选择确立后，后续治疗记录通过 `selectedPatientId` 关联，**不新增 EPROM 寄存器**：`selectedPatientId`/`selectedPatientName` 与窗口、搜索等运行状态一致，放在 `listTreatmentCtx`（RAM/ZI 段），开机为 0（未选择），不做掉电持久化。
2. 保存沿用现有 `KEY_CREATE_NEW` → 编辑页 → OK 链路，`listTreatmentCreateStart()` 按是否已选患者分两条路径：
   - **已选患者（`selectedPatientId != 0`，老患者路径）**：先用 `treatmentPatientFind` + `treatmentPatientGetByIndex` 按 id 取出该患者，把 `treatmentLog` 的 `id`/`name`/`age`/`gender` 预填为该患者，**不清空患者信息、不新建患者**；编辑页 OK 后 `treatmentEpromAdd` 因该 id 已存在（`treatmentPatientFind` 成功），直接把治疗记录以该 `patientId` 为外键追加，归属到选中患者名下。
   - **未选患者（`selectedPatientId == 0`，新患者路径）**：保持既有行为，清空 `name`/`age`/`gender`、`id = 0` 占位，在编辑页录入后由 `treatmentEpromAdd` 自动新建患者并分配新 id。
3. 本闭环为强制规格：选中患者后任何保存路径都不得再为该次治疗新建重复患者；同一患者的多次治疗只在其名下追加记录，患者主表中该患者仍只出现一次。

---

## 六、删除患者确认（KEY_DELETE_0–4 / GDDC_PAGE_DELETE_TREATMENT_CONFIRM）

本部分固化“列表页删除按钮 → 进入删除确认页 → 确认后级联删除患者及其全部病历”的强制闭环。涉及控件：列表页 `KEY_DELETE_0–4`（控件 25–29）、确认页 `GDDC_PAGE_DELETE_TREATMENT_CONFIRM`（页面 ID 14），确认页按钮 `KEY_DELETE`（控件 1）、`KEY_CANCEL`（控件 2），文本框控件 3–6（`TEXT_NAME_ID`=3、`TEXT_SUMMARY_0`=4、`TEXT_SUMMARY_1`=5、`TEXT_SUMMARY_2`=6）。页面上所有文字按根目录 `AI_RULES.md` 至高规格一律英文显示。

### 6.1 列表页进入删除确认页（不立即删除）

1. 点 `KEY_DELETE_0–4`（控件 25–29）调用 `listTreatmentDeleteStart(slot)`，`slot = control_id - GDDC_PAGE_LIST_TREATMENT_KEY_DELETE_0`（取值 0–4），分别对应窗口内 `TEXT_NAME_0–4` 的患者。
2. `slot` 越界（`>= 5`）直接返回；`viewPos = topIndex + slot` 若 `>= filteredCount`（空槽位）不响应；视图位置取不到患者也不响应。
3. 命中后把该患者稳定编号缓存到 `listTreatmentCtx.deletePatientId`（非 0 即表示处于删除确认流程），**先只进入确认页、不得在列表页直接删除**；确认页文案（英文）：
   - `TEXT_NAME_ID`（控件 3，标题）：`Delete Patient?`
   - `TEXT_SUMMARY_0`（控件 4，动态）：`Delete patient <name> and all their treatment records?`（`<name>` 为该患者姓名原文）
   - `TEXT_SUMMARY_1`（控件 5，动态）：`This patient has <n> treatment record(s).`（`<n>` = `treatmentGetRecordCountForPatient(id)`，该患者已有病历数）
   - `TEXT_SUMMARY_2`（控件 6）：`This action cannot be undone.`
4. 置 `NVRAM0[EM_DC_PAGE] = GDDC_PAGE_DELETE_TREATMENT_CONFIRM` 后 `SetScreen(14)`，等待用户确认或取消。

### 6.2 确认删除（KEY_DELETE）

1. 点确认页 `KEY_DELETE`（控件 1）调用 `listTreatmentDeleteConfirm()`；仅当 `deletePatientId != 0` 时执行。
2. 调用数据层 `treatmentPatientDelete(deletePatientId)` 完成**级联删除**：墓碑并致密该患者的全部治疗记录，再逻辑删除并致密患者表——即同时删除患者名字与其全部历史病历，其他患者 id 与记录保持不变。
3. 删除后必须：
   - 清除 `deletePatientId`（退出删除流程）。
   - 若被删患者正是当前选中患者（`deletePatientId == selectedPatientId`），同时清空 `selectedPatientId`/`selectedPatientName`，避免后续病历外键与待机页患者名悬空。
   - 调用 `listTreatmentRebuildFilter()` + `refreshListTreatmentDisplay()` 重建患者视图（窗口由 `listTreatmentClampWindow` 自动夹取到合法范围），再返回列表页 `GDDC_PAGE_LIST_TREATMENT`。

### 6.3 取消删除（KEY_CANCEL）

1. 点确认页 `KEY_CANCEL`（控件 2）调用 `listTreatmentDeleteCancel()`；仅当 `deletePatientId != 0` 时执行。
2. 不做任何 EPROM 删除，清除 `deletePatientId`，刷新并返回列表页 `GDDC_PAGE_LIST_TREATMENT`，患者表与病历保持原样。

### 6.4 触摸放行与状态约束

1. 删除确认页等待期间，触摸总闸 `listTreatmentUsbButtonAllowed` 只放行本页 `KEY_DELETE`/`KEY_CANCEL`，其余控件与其他页面触摸一律屏蔽；删除为本地同步操作，在确认回调内一次执行完毕，不设异步忙状态。
2. `deletePatientId` 与其他运行状态一致放 `listTreatmentCtx`（RAM/ZI），开机为 0（不在删除流程），不新增 EPROM 寄存器、不做掉电持久化。
3. 本闭环为强制规格：任何时刻维护都必须保留“先确认后删除”，不得改为点 DELETE 直接删除、不得跳过确认页。

---

## 七、维护约束

- 仅在 `run_treatment` 分支、唯一活跃工程 `targetBoard_G5_TRI_A1_20260915` 内修改；遵循仓库根 `AGENTS.md` 的 UTF-8 编码与代码风格要求。
- 文本控件英文显示与非 ASCII 符号转换要求已提升为**全工程至高规格**，统一以根目录 `AI_RULES.md` 的“显示文本一律英文、非 ASCII 符号一律转换”条款为准（适用全部页面，修改或开口子须经仓库所有者人工授权）；本文件不再维护局部规则，原中点 `·` 等非 ASCII 分隔符一律改为 ASCII 符号。
- 改动后按 `活跃工程说明.md` 做 AC5 Rebuild，**0 Error 才算通过**；无硬件时只能称为“编译级验证”，不得声称上板功能/时序已验证。
- 若控件 ID、页面编号或本文件描述的规则发生变化，必须同步更新本文件，保持规格与代码一致。

---

## 八、导出后机内病历数据保留（最高优先级强制规格）

1. 执行导出（列表页 `KEY_SAVE_UDISK` → `GDDC_PAGE_OPERATOR_USB_SAVE` → `KEY_OK`，最终调用 `treatmentLogSaveToUdisk`）后，机内患者表与治疗记录必须**完整保留**，患者数、记录数与导出前一致。
2. 导出流程中**禁止**调用任何删除/清空病历的接口，包括 `treatmentEpromClear()`、`treatmentPatientDelete()`、`treatmentEpromDelete()`，也不得以“释放空间”“防止重复导入”等理由间接清空。
3. 不论 CSV 写入成功、失败，或 U 盘中途拔出，机内数据都不得被修改；失败只允许在操作页结果栏提示错误码。
4. 导出完成返回 `GDDC_PAGE_OPERATOR_USB` 时，`TEXT_SUMMARY` 的患者数/记录数照常按机内实际数量刷新（正常情况下与导出前相同）。
5. **本规格优先于任何软件功能改动与页面文案。** 确需“导出后清空本机病历”时，必须先修改本节并经用户明确确认，确认后才允许修改代码；任何 AI 不得擅自添加、预留或预埋清空逻辑。
6. 代码核对（2026-11-20）：`treatmentLogSaveToUdisk` 只按槽位读取并写 CSV，不调用任何删除接口；`treatmentEpromClear()` 现有调用点仅为 `dcHmiLoopInit` 的固件 CRC 变化清空与工程模式“清空 EPROM”，均与导出无关，符合本节要求。

---

## 九、病历数据规则：治疗时刻 RTC 与姓名长度（强制规格）

1. **治疗时刻必须落盘**：每条治疗记录保存“停光瞬间”的 RTC 时刻（完整 4 位年 + 月/日/时/分/秒），用于病历追溯；不得只保存不显示、也不得留空。
2. 数据结构：RAM 复合视图 `treatmentLog_t` 与片上 `treatmentRecord_t` 均带 `rtcYear/rtcMonth/rtcDay/rtcHour/rtcMinute/rtcSecond`，片上存年份后两位（实际年 = +2000，0 = 未记录）。
3. 采集与保存链路：`listTreatmentPendingCapture()` 在停光瞬间抓取 RTC 存入待存快照 `listTreatmentCtx.pending`；`listTreatmentCreateStart()` 必须把快照的 6 个 RTC 字段回填到 `treatmentLog`，编辑页 `KEY_OK` 后随 `treatmentEpromAdd` 写入 EPROM；漏抓兜底路径（发射时间计数判断）必须用当前 RTC 补齐。
4. **U 盘 CSV 必须带时间并带回**：当前 `rtc` 为第 10 列，格式 `YYYY-MM-DD HH:MM:SS`；未记录时间时该列留空。当前完整表头为 13 列（`id` 加 AR 前缀，`rtc` 后追加 `pulseMode,posWidth,negWidth`），详见第十三至十五节。
   - 导入解析：列数 ≥ 9 即接受，旧版 9 列/10 列备份仍可载入，时间按“未记录”、脉冲按 CW 处理；有新列但格式/范围非法则整行载入失败。
   - 导入回读核对（`treatmentLogVerifyUdisk`）必须同时比较 RTC 6 个字段与脉冲三字段，不允许跳过。
   - 客户端如 Excel 另存，需保持该列格式（空格分隔日期与时间，不拆成两列）。
5. **患者姓名长度 18 个字符**：由 `treatment.h` 的 `CONFIG_TREATMENT_NAME_LEN = 18` 定义，缓冲区 `TREATMENT_NAME_SIZE = 19`（含结束符），`treatmentLog_t.name` 与 `patientRecord_t.name` 共用该长度；固件在姓名录入处按 `TREATMENT_NAME_SIZE - 1` 截断，屏幕输入控件 `text_len_max` 保持 255，以固件截断为准。
6. 姓名长度改变会改变片上患者行尺寸（当前 24 字节），存量病历与新结构不兼容；沿用既有约定——固件 CRC 变化时 `dcHmiLoopInit` 清空整片 EPROM，不做迁移与向后兼容。
7. 本节的 RTC 列与姓名长度属于数据规格，任何后续改动必须先更新本节，并同步 `minicsvApp.c` 的列定义（`TREATMENT_CSV_COLUMNS_MIN` / `TREATMENT_CSV_COLUMNS_RTC` / `TREATMENT_CSV_COLUMNS`）与 `treatmentCsvHeader`。

---

## 十、空槽位控件隐藏与搜索框清空（强制规格，2026-11-20）

1. **空槽位判定**：窗口内槽位 `i` 的视图位置 `viewPos = topIndex + i`，当 `viewPos >= filteredCount` 时该槽位为空（搜索命中不足一屏、空视图、末页未满均适用）。用户所述“搜索后只有 2 个对应病人时，槽位 2–4 全部空白”即本条的具体情形；本条对 0–4 任意数量空槽位统一生效，不只限于 2 个病人的场景。
2. **空槽位文本**：`TEXT_NAME_i`、`TEXT_ID_i`、`TEXT_RECORD_COUNT_i` 三个文本框一律下发空串，不显示任何内容。
3. **空槽位按键**：`KEY_SELECT_PATIENT_i`、`KEY_DELETE_i`、`KEY_EDIT_RECORD_i` 三个按键必须同时 `SetControlVisiable(..., 0)` 隐藏、`SetControlEnable(..., 0)` 禁止触摸；各回调函数既有的空槽位 `viewPos >= filteredCount` 直接返回防护继续保留，作为双保险。
4. **有效槽位恢复**：每次 `refreshListTreatmentDisplay()` 对全部 5 个槽位显式下发状态——有效槽位三个按键 `SetControlVisiable/Enable(..., 1)`，保证过滤、翻页、删除后重新占用的槽位按键能正常显示与触摸，不依赖屏幕工程的默认控件状态。
5. **搜索框清空**：每次经 `enterListTreatmentPage()` 进入本页（含点 `KEY_CLOSE` 回到待机页后再次进入），除清空 RAM 中 `findText` 外，必须向 `GDDC_PAGE_LIST_TREATMENT_TEXT_SEARCH_NAME` 下发空串，使屏幕搜索框同步清空，随后按空串重建视图、显示全部患者。
6. **例外路径**：`listTreatmentOperatorUsbBack()` 从 USB 操作页返回时保留当前搜索内容与窗口位置，不清空搜索框，不适用本条第 5 点。

---

## 十一、病历数量文本框 TEXT_RECORD_COUNT_0–4 显示格式（强制规格，2026-11-20）

1. **有效槽位（有对应病人）**：`TEXT_RECORD_COUNT_i` 显示固定英文格式 `Records: X`，其中 `X` 为该患者实际已记录的病历数量；**X 可以为 0**，此时显示 `Records: 0`。`X` 由 `refreshListTreatmentDisplay()` 预读窗口 5 行后，**单遍记录 id 轻读（2 字节/条）一次性统计**窗口各患者的记录数，不再为每个患者各做一次整行全表扫描。
2. **空槽位**：仍按第十节下发空串，不显示任何内容。
3. 文案为纯 ASCII（英文字母、冒号、空格与数字），符合根目录 `AI_RULES.md` 显示文本一律英文的至高规格，屏幕现有字体（font 6，ASC_CHS_20）可直接渲染，无需改屏幕工程。
4. 曾提出的中文“病历数量X”方案：与 `AI_RULES.md` 英文显示至高规格冲突，且屏幕资源无中文字体（`dwLaser.fidx` 仅含 30 个 ASCII 字体，`charset.txt` 不含“病历数量”字形），经确认**不采用**。将来若要恢复中文显示，必须先经仓库所有者人工授权并修改 `AI_RULES.md` 至高规格，再完成屏幕中文字体工程（VisualTFT 配置中文字体、加入字形、重建并烧录屏幕资源），固件按 GB2312/GBK 编码下发。

---

## 十二、USB 三页面按键自锁（强制规格，2026-11-21）

1. **适用范围**：`GDDC_PAGE_OPERATOR_USB`（页面 19）、`GDDC_PAGE_OPERATOR_USB_SAVE`（页面 20）、`GDDC_PAGE_OPERATOR_USB_LOAD`（页面 21）三个页面上的**全部 7 个按键控件**——19 页 `KEY_SAVE_UDISK`（3）、`KEY_LOAD_UDISK`（4）、`KEY_CANCEL`（5）；20/21 页 `KEY_OK`（11）、`KEY_CANCEL`（10）。屏幕工程中 7 个按键均为 `button_type = 1`（自锁型，按下后不自行弹起），该属性为强制配置，不得改为自弹型。
2. **弹起机制不另立规则**：这 7 个按键的释放位置、无条件弹起（含空操作）、切页安全解锁与中止路径，**统一遵循第十六节**，由 `treatmentReleaseButton` 经 `NotifyButton` 层处理，本节不再维护各自的弹起时机，避免与第十六节口径漂移。
3. **唯一需在本节点明的异步特性**：20/21 页 `KEY_OK`（11）按下只授权（`usbState` 6→7），实际 CSV 读写（含导入后的回读核对）在 `listTreatmentUsbLoop` 中完成，故该 OK 按第十六节的异步例外在 loop 工作完成后释放，而非 notify 立即释放。
4. 任何后续在这三页新增的自锁按键，先在本节登记控件 ID，其释放仍统一遵循第十六节。

---

## 十三、患者历史治疗记录页 GDDC_PAGE_LIST_RECORD（页面 ID 15，强制规格，2026-11-21）

### 13.1 进入与数据来源

1. 在病历列表页（13）点击 `KEY_EDIT_RECORD_0–4`（控件 31–35），由 `listTreatmentRecordEnter(slot)` 处理：按窗口槽位解析出对应患者，把稳定患者编号写入 `recordPatientId`，再调用 `listTreatmentRecordEnumerate()` 令窗口缓存失效并收集当前窗口，最后 `SetScreen(15)`。
2. 枚举口径（无条数硬上限、无整行缓存数组）：`listTreatmentRecordCollectWindow()` 单遍扫描扁平记录，用 `treatmentRecordGetPatientIdByIndex()` **只读记录行首 2 字节外键 id**（替代整行 28 字节），按 `rowId == recordPatientId` 过滤并统计记录总数（`recordCount`，`uint16`），仅把当前窗口 5 条的全局索引缓存到 `recordWindow[0..4]`；翻页时按 `recordTop` 重新轻扫收集对应窗口，完整行在渲染时才读，记录按存储顺序（即追加/时间先后）呈现，条数仅受区块物理容量约束。
3. 页面冷加载时（`screen_id` 分发）必须重新枚举并调用 `refreshListRecordDisplay()`，保证掉电重启回到本页时显示与存储一致。

### 13.2 控件与显示格式

1. **姓名行 `TEXT_NAME`（控件 1）**：固定格式 `姓名 - AR 编号`，例如 `John Smith - AR 0001`（AR 前缀规则见第十五节）。
2. **时间/能量行 `TEXT_TIEM_ENERGY_0–4`（控件 2–6）**，固定格式：
   `记录时间 - 发射能量 - 发射时间 - 功率 - 波长`
   示例：`2026-11-10 18:00 - 262.7 J - 00:19 - 30 W - 1470 nm`
   - 记录时间取 RTC，格式 `YYYY-MM-DD HH:MM`；未记录时间时该段显示 `---- --:--`。
   - 发射能量底层为 0.1 J（decijoule），显示时除以 10 保留 1 位小数（用整数运算拆整/分，不用浮点）。
   - 发射时间取秒，格式 `MM:SS`；功率取 `laserPower`，单位 `W`；波长单波长如 `1470 nm`，双波长如 `1470+980 nm`。
3. **方案/脉宽行 `TEXT_SCHEME_WIDTH_0–4`（控件 7–11）**：
   - 连续模式：`大类 序号 - CW`，示例 `Phlebology 1 - CW`。
   - 脉冲模式：`大类 序号 - Pulse - ON 正脉宽 / OFF 负脉宽 ms`，示例 `Phlebology 1 - Pulse - ON 600 / OFF 700 ms`。
   - 自定义方案（`protocol == eCustiom`）：仅显示 `Custom`，不带序号与模式。
   - 大类名称复用 `treatmentProtocolName`，序号为 `schemeIndex + 1`。
4. **页码 `TEXT_PAGE`（控件 12）**：固定格式 `PAGE 当前页/总页数`，例如 `PAGE 1/2`；总页数 = `ceil(recordCount/5)`，无记录时强制 `PAGE 1/1`，严禁 `0/0`。
5. 全部文案为纯 ASCII，符合根目录 `AI_RULES.md` 英文显示至高规格。

### 13.3 空槽位隐藏（不足 5 条）

1. 当槽位 `i` 的记录位置 `recordTop + i >= recordCount` 时该槽为空（如仅 3 条记录，则槽 3–4 为空）。
2. 空槽的 `TEXT_TIEM_ENERGY_i`、`TEXT_SCHEME_WIDTH_i` 两个文本控件必须 `SetControlVisiable(..., 0)` 隐藏、不显示任何内容；`KEY_DELETE_i` 必须同时隐藏并 `SetControlEnable(..., 0)` 禁止点击。
3. 有效槽位每次刷新显式恢复可见/可点状态，不依赖屏幕默认值。

### 13.4 翻页与按键

1. `KEY_PAGE_UP`（25）/`KEY_PAGE_DOWN`（26）：`recordTop` 分别减/加 5，由 `listTreatmentRecordMaxTop()` 夹取到合法整页边界，到首页/末页停止。
2. `KEY_CLOSE`（27，宏名 `GDDC_PAGE_LIST_RECORD_KEY_CLOSE`）：清空 `recordPatientId` 后返回病历列表页（13）。
3. `KEY_EDIT_PATIENT`（28，宏名 `GDDC_PAGE_LIST_RECORD_KEY_EDIT_PATIENT`）：跳转患者信息编辑页（17），行为见 13.5。
4. 本页全部按键在屏幕工程均为 `button_type = 1`（自锁型）；其释放统一遵循第十六节（notify 层无条件 `treatmentReleaseButton`），本节不另写弹起时机。

### 13.5 患者信息编辑（页面 17 复用）

1. 点 `KEY_EDIT_PATIENT` 由 `listTreatmentRecordEditPatient()` 预填该患者姓名/年龄/性别，ID 行显示 `AR 编号`，并置 `editPatientMode = 1`，`SetScreen(17)`。
2. 编辑页 OK 在该模式下改走 `listTreatmentEditPatientConfirm()`：调用 `treatmentPatientUpdate()` 原地更新患者信息（id 不变、不追加治疗记录），完成后回记录页（15）并清 `editPatientMode = 0`。
3. 编辑页 CANCEL 在该模式下走 `listTreatmentEditPatientCancel()`：不更新，回记录页（15）。正常新建/追加流程（`editPatientMode = 0`）仍走原 `listTreatmentCreateConfirm/Cancel`，行为不变。

---

## 十四、单条治疗记录删除确认页 GDDC_PAGE_DELETE_RECORD（页面 ID 16，强制规格，2026-11-21）

1. 记录页（15）点击 `KEY_DELETE_0–4`（20–24）由 `listTreatmentRecordDeleteStart(slot)` 缓存待删记录全局索引到 `deleteRecordGlobalIndex`，下发确认文案后 `SetScreen(16)`；不在记录页直接删除。
2. 控件：`TEXT_NAME`（1）、`TEXT_SUMMARY_0`（2）、`KEY_CANCEL`（10）、`KEY_OK`（11）。
3. `KEY_OK`：`listTreatmentDeleteRecordConfirm()` 调用 `treatmentRecordDeleteByIndex(idx)` 删除该条（墓碑 + 安全压缩），清空缓存索引、重新枚举并夹取窗口后回记录页（15）。
4. `KEY_CANCEL`：`listTreatmentDeleteRecordCancel()` 不删除，清空缓存索引后回记录页（15）。
5. 两个按键均为自锁型，其释放统一遵循第十六节（notify 层无条件 `treatmentReleaseButton`）；本闭环为强制规格，不得改为点 DELETE 直接删除或跳过确认。

---

## 十五、患者 ID 编码规则（AR 前缀，强制规格，2026-11-21）

1. **编码格式**：`AR` + 一个空格 + 至少 4 位递增数字，不足 4 位前面补零，例如 `AR 0001`、`AR 0002`、`AR 0011`。
2. **EPROM 只存数字**：为节省空间，患者行 `patientRecord_t.id` 与记录外键均只存 `uint16_t` 递增数字，不存 `AR` 前缀或空格；在 HMI 显示与 CSV 导出/导入时由软件自动加/去 `AR ` 前缀。
3. **自动生成、不可手动修改**：新建患者时取现有患者 ID 中最大数字加 1，不接受手动输入；删除患者不回收、不重编号。
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
| 14 | `GDDC_PAGE_DELETE_TREATMENT_CONFIRM` |
| 15 | `GDDC_PAGE_LIST_RECORD` |
| 16 | `GDDC_PAGE_DELETE_RECORD` |
| 17 | `GDDC_PAGE_EDIT_PATIENT` |
| 18 | `GDDC_PAGE_REGISTER_PATIENT` |
| 19 | `GDDC_PAGE_OPERATOR_USB` |
| 20 | `GDDC_PAGE_OPERATOR_USB_SAVE` |
| 21 | `GDDC_PAGE_OPERATOR_USB_LOAD` |
| 23 | `GDDC_PAGE_VERIFY_TREATMENT` |
| 24 | `GDDC_PAGE_DISCARD_TREATMENT` |

2. 目标：任一按键按下（置 1）后，到该按键被单片机重新清零（置 0）的这段“在途”时间内，**同页及跨页的其他所有按键都必须锁定、无法按下**，防止在途动作（FRAM 读写、切页、删除、U 盘读写等）未完成时误触其他按键。
3. 非上述 11 页的页面（待机、方案、诊断、校准、选项、READY 等）不参与本互锁，其按键行为保持原样，互锁门对这些页面直接放行。

### 16.2 触发、锁定与放行语义

1. **触发（Arm）**：在 11 页内任一按键上报 `state = 1`（按下），且当前无在途按键时，互锁立即记录该按键的“画面 + 控件 ID”并进入在途态。
2. **锁定**：在途期间，凡画面或控件 ID 与在途按键不一致的其他按键上报 `state = 1`，一律拒绝（`NotifyButton` 直接 `return`，不执行任何功能）；锁定对同页其他按键与跨页按键同等生效。
3. **同一按键重复通知放行**：在途按键自身重复上报 `state = 1`（屏幕重发/轮询）时放行，不视为新按键，保证在途动作自身的事件链路不被自己的锁阻断。
4. **弹起释放（统一在 notify 层无条件执行）**：
   - 11 页全部按键均为 `button_type = 1`（自锁型，屏幕不会自行补发 `state = 0`），故**每个按键都在 `NotifyButton` 对应分支 `if(state)` 内、调用功能函数之后无条件调用 `treatmentReleaseButton(screen, control)`**；该函数下发 `SetButtonValue(..., 0)` 并同步解除互锁。
   - 释放不得放在功能函数内部的守卫之后：即使功能函数因空槽位、边界、忙状态或校验失败而提前 return（空操作），按键仍必须弹起，严禁出现“按下后无任何路径释放”的死锁。
   - **唯一例外（异步 OK）**：USB 确认页 20/21 的 `KEY_OK` 按下只授权（`usbState` 6→7），实际 CSV 读写在 `listTreatmentUsbLoop` 中完成；该 OK 必须在 loop 工作全部执行完毕后才释放，不在 notify 释放。
   - 若确认页被别处切走（中止路径），由 loop 对该页 OK/CANCEL 统一弹起（见 16.3）。
5. 互锁只保存“是否在途 + 画面 ID + 控件 ID”三个标量，不按页面或控件数量分配数组，RAM 开销恒定。

### 16.3 切页安全解锁（防永久锁死）

1. 页面切换完成通知 `NotifyScreen(screen_id)` 触发时，若新页面与在途按键所在页面**不同**（原页面被切走，其按键无法再走正常复位路径），强制解除互锁，避免新页面被上一页遗留的在途锁永久屏蔽。
2. 若新页面与在途按键所在页面**相同**（同一页面的加载/重发通知），不解锁，避免在途动作期间被误放行；在途按键仍由其功能完成路径正常释放。
3. USB 确认页被别处切走的中止路径（见第十二节、4.4）继续对该页 OK/CANCEL 显式弹起，弹起即经 `treatmentReleaseButton` 同步解锁，与本条切页解锁互为兜底。

### 16.4 与现有触摸状态门的分层关系

1. `NotifyButton` 顶部按顺序串联两道门，**两道都放行才继续分发**：
   - 第一道 `treatmentButtonLockAllowed(screen, control, state)`：本规格的 11 页按键互锁，先判定；
   - 第二道 `listTreatmentUsbButtonAllowed(screen, control)`：既有的 USB 忙/删除确认流程状态门（删除确认等待、U 盘读写忙等期间屏蔽无关触摸），保留不变。
2. 两道门职责不同、不得互相替代：互锁门管“单键在途期间其他键不可按”，状态门管“特定业务流程期间只放行指定控件”；新增业务流程状态门时应接在互锁门之后，不得绕过互锁门。

### 16.5 未启用页面与实现位置

1. 页面 23 `GDDC_PAGE_VERIFY_TREATMENT`、页面 24 `GDDC_PAGE_DISCARD_TREATMENT` 当前固件尚未建立 `SetScreen`/`NotifyButton` 分支（未启用），但已纳入互锁页面判定；将来启用时其按键自动适用本规格，无需再改互锁门。
2. 实现位置：
   - 互锁状态与判定/放行/释放函数（`treatmentIsLockPage`、`treatmentBtnLockArm/Release/Reset`、`treatmentButtonLockAllowed`、`treatmentReleaseButton`）：`MainApp/dcHmiApp.c`，对外声明在 `MainApp/dcHmiApp.h`。
   - 互锁门接入与各自锁键释放点：`MainApp/dcHmiNotifyButton.c`、`MainApp/dcHmiApp.c`。
3. 本规格为强制规格：任何新增病历相关页面若需要同样的“在途互锁”，必须先在 16.1 表中登记页面 ID，并确认其按键在 `NotifyButton` 分支内无条件调用 `treatmentReleaseButton`（异步动作键在其完成路径释放），否则该页面按键可能在途后无法正常解锁。

---

## 附录 A：变更日志与历史核对记录

> 本附录只记录“某时点的屏幕工程/数据状态”与每次规格变更，不承载强制规则；正文各节只保留不随时间变化的规则。下列状态为对应日期的核对快照，最新状态以实际屏幕工程与代码为准。

1. **2026-11-20**：USB 确认页在屏幕工程 `vTFT_HMI/dwLaser.tftprj` 中建立——导出确认页 `GDDC_PAGE_OPERATOR_USB_SAVE_CONFIRM.tft`（页面 20）仅控件 1/2；导入确认页 `GDDC_PAGE_OPERATOR_USB_LOAD_CONFIRM.tft`（页面 21）建控件 1/2/3，固件只用 1/2，控件 3 下发空串、控件 4 未建立不写入。
2. **2026-11-21**：删除患者确认页 14 在 `GDDC_PAGE_DELETE_TREATMENT_CONFIRM.tft` 中建立（按钮 1–2、文本 3–6），与 `dcHmiRes.h` 宏值一致；同日核对 USB 三页（19/20/21）共 7 个按键均为 `button_type = 1`。
3. **2026-11-22**：
   - 导出确认页文案删去 `The archives on the device will be cleared.`，`TEXT_SUMMARY_1` 只保留“U 盘原有备份将被替换”，与第八节“导出不清空”口径一致；
   - 宏名拼写更正：`..._KEY_CANCLE` → `..._KEY_CANCEL`、`..._RECODE` → `..._RECORD`（控件数字 ID 不变，.tft 内部 name 保留旧拼写、不影响通信）；
   - 第十二节、13.4、第十四节的弹起细节收敛为统一引用第十六节，不再各自维护；
   - 排序措辞改为“姓名 → 原始存储索引”的全序键（原始索引为最终 tie-break），不再称堆排序为稳定排序；
   - 正文各时点快照移入本附录，强制规格只保留规则。
