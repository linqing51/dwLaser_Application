# 病历列表页 UI 行为规格 — GDDC_PAGE_LIST_TREATMENT（页面 ID 13）

本文件固化病历列表页页码、搜索、关闭按钮、患者选择闭环、删除患者确认，以及 USB 操作页与导出/导入确认页的**强制交互行为**。任何 AI 维护此页面前必须先读完本文件，并按此实现，不得擅自更改匹配口径、排序规则、显示格式、页面跳转出口、患者选择归属与删除确认流程。

> **最高优先级规格（2026-11-20）：导出后机内病历数据不清空。** 从设备导出病历到 U 盘后，机内患者表与治疗记录必须完整保留，不得删除或清空。本规格优先于任何软件功能改动与页面文案；确需“导出后清空本机病历”时，必须**先修改本规格并经用户明确确认**，之后才允许进行软件修改。任何 AI 不得擅自在导出流程中加入清空逻辑（详见第八节）。

- 实现位置：`MainApp/dcHmiApp.c`（过滤/排序/刷新）、`dcHmiNotifyButton.c`（按钮）、`dcHmiNotifyText.c`（文本输入）
- 控件 ID 定义：`MainApp/dcHmiRes.h`
- 每页固定显示 `LIST_TREATMENT_WINDOW_SIZE = 5` 个患者；患者上限 `CONFIG_EPROM_TREATMENT_PATIENT_MAX = 100`

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
2. **大小写敏感的 ASCII 字典序稳定排序**：命中结果必须先按字符原始值（ASCII）排序，再写入 `TEXT_NAME_0–4`：
   - 从第一个不同的字符位决定先后，**大写字母（A–Z，码值 65–90）整体排在小写字母（a–z，97–122）之前**；短名先结束（如 `li` 排在 `linqing` 之前）；姓名完全相同者保持原相对顺序（稳定排序）。
   - 实现沿用 `listTreatmentCompareName`，直接按原始字节 `(uint8_t)` 比较，不做大小写归一。
3. **多字母前缀**：先按输入的多个字母过滤，再按其后一位字母继续字典序比较；本质仍是“前缀匹配 + 全名字典序”。
4. 排序在 `listTreatmentRebuildFilter()` 中基于本地姓名缓存完成（`listTreatmentCompareName` + `listTreatmentSortFiltered`），**不得在排序过程中反复物理读 EPROM**。

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

## 三、关闭按钮 GDDC_PAGE_LIST_TREATMENT_KEY_CLOSE（控件 ID 32）

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
   - `TEXT_SUMMARY_1`（控件 2）：`The existing patient backup in this USB will be replaced. The archives on the device will be cleared.`
     - “此 USB 中的原有患者备份将被替换。设备中的档案将被清除。”
   - 原 `TEXT_SUMMARY_2/3` 文案作废，本页不再向控件 3/4 写入。
2. `KEY_CANCEL`（控件 10）：取消写入，不修改 U 盘与机内 EPROM，返回操作页 `GDDC_PAGE_OPERATOR_USB`，并**清空**该页 `TEXT_SUMMARY_USB`（写空串）；该页 `TEXT_SUMMARY` 保持进入本页前显示的内容不变。
3. `KEY_OK`（控件 11）：授权把机内病历转换成 CSV 写入 U 盘，复用 `treatmentLogSaveToUdisk`，文件名由 `TREATMENTLOG_FILENAME` 宏指定（`/treatment_v1.csv`，覆盖同名文件）；实际写入在 `listTreatmentUsbLoop` 中执行一次，不在按键回调里阻塞。
4. 写入完成后自动返回 `GDDC_PAGE_OPERATOR_USB`，并在 `TEXT_SUMMARY_USB`（操作页控件 2）显示本次备份概况：
   - 成功：`USB backup: X patients, Y treatment records`
     - `X` = 机内患者数 `treatmentEpromGetPatientCount()`；`Y` = 本次实际写入 U 盘的治疗记录数 `listTreatmentCtx.usbCount`。
   - 失败按错误码：`NO UDISK` / `NO RECORDS` / `USB OPEN FAILED` / `USB BACKUP FAILED`
5. 结果栏内容统一保存在 `listTreatmentCtx.usbText`，由 `refreshOperatorUsbDisplay()` 下发；因此回到操作页后的页面冷加载刷新不会把结果覆盖成 `UDISK OK`。重新从列表页进入操作页时，`usbText` 恢复为 U 盘在位状态（`UDISK OK` / `NO UDISK`）。
6. 导出流程**只写 U 盘、不删除机内病历**（强制规格，见第八节，优先于任何功能改动）；`TEXT_SUMMARY_1` 中的 `The archives on the device will be cleared.` 仅为确认页提示文案，不代表实际行为，不得据此实现清空。

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

1. 确认页等待期间（状态 6）只放行 CANCLE/CONFIRM，读写执行期间（状态 7）屏蔽一切触摸。
2. 确认/取消回调导出/导入通用：`listTreatmentUsbConfirm`（状态 6→7）、`listTreatmentUsbCancel`（状态 6→0 回操作页）。
3. 若确认页被别处切走（如关机确认/休眠），轮询检测到当前页不符即放弃本次流程并退出忙状态，避免触摸被永久屏蔽。

**屏幕工程现状（2026-11-20 核对）**：确认页已在屏幕工程 `vTFT_HMI/dwLaser.tftprj` 中建立——导出确认页为 `GDDC_PAGE_OPERATOR_USB_SAVE_CONFIRM.tft`（页面 ID 20），导入确认页为 `GDDC_PAGE_OPERATOR_USB_LOAD_CONFIRM.tft`（页面 ID 21）。导出确认页只有 `TEXT_SUMMARY_0/1`（控件 1/2），与本页规格一致；导入确认页建了 `TEXT_SUMMARY_0/1/2`（控件 1/2/3），固件只用控件 1/2，控件 3 保留但下发空串，`TEXT_SUMMARY_3`（控件 4）未建立、固件不写入。

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
   - 经 `filteredIndex[viewPos]` 与 `listTreatmentGetViewPatient(viewPos, &pat)` 解析出患者原始记录，把稳定患者编号缓存到 `listTreatmentCtx.selectedPatientId`、姓名缓存到 `listTreatmentCtx.selectedPatientName`。
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

本部分固化“列表页删除按钮 → 进入删除确认页 → 确认后级联删除患者及其全部病历”的强制闭环。涉及控件：列表页 `KEY_DELETE_0–4`（控件 25–29）、确认页 `GDDC_PAGE_DELETE_TREATMENT_CONFIRM`（页面 ID 14），确认页按钮 `KEY_DELETE`（控件 1）、`KEY_CANCLE`（控件 2），文本框 `TEXT_SUMMARY_0–3`（控件 10–13）。页面上所有文字按根目录 `AI_RULES.md` 至高规格一律英文显示。

### 6.1 列表页进入删除确认页（不立即删除）

1. 点 `KEY_DELETE_0–4`（控件 25–29）调用 `listTreatmentDeleteStart(slot)`，`slot = control_id - GDDC_PAGE_LIST_TREATMENT_KEY_DELETE_0`（取值 0–4），分别对应窗口内 `TEXT_NAME_0–4` 的患者。
2. `slot` 越界（`>= 5`）直接返回；`viewPos = topIndex + slot` 若 `>= filteredCount`（空槽位）不响应；视图位置取不到患者也不响应。
3. 命中后把该患者稳定编号缓存到 `listTreatmentCtx.deletePatientId`（非 0 即表示处于删除确认流程），**先只进入确认页、不得在列表页直接删除**；确认页文案（英文）：
   - `TEXT_SUMMARY_0`（控件 10，标题）：`Delete Patient?`
   - `TEXT_SUMMARY_1`（控件 11，动态）：`Delete patient <name> and all their treatment records?`（`<name>` 为该患者姓名原文）
   - `TEXT_SUMMARY_2`（控件 12，动态）：`This patient has <n> treatment record(s).`（`<n>` = `treatmentGetRecordCountForPatient(id)`，该患者已有病历数）
   - `TEXT_SUMMARY_3`（控件 13）：`This action cannot be undone.`
4. 置 `NVRAM0[EM_DC_PAGE] = GDDC_PAGE_DELETE_TREATMENT_CONFIRM` 后 `SetScreen(14)`，等待用户确认或取消。

### 6.2 确认删除（KEY_DELETE）

1. 点确认页 `KEY_DELETE`（控件 1）调用 `listTreatmentDeleteConfirm()`；仅当 `deletePatientId != 0` 时执行。
2. 调用数据层 `treatmentPatientDelete(deletePatientId)` 完成**级联删除**：墓碑并致密该患者的全部治疗记录，再逻辑删除并致密患者表——即同时删除患者名字与其全部历史病历，其他患者 id 与记录保持不变。
3. 删除后必须：
   - 清除 `deletePatientId`（退出删除流程）。
   - 若被删患者正是当前选中患者（`deletePatientId == selectedPatientId`），同时清空 `selectedPatientId`/`selectedPatientName`，避免后续病历外键与待机页患者名悬空。
   - 调用 `listTreatmentRebuildFilter()` + `refreshListTreatmentDisplay()` 重建患者视图（窗口由 `listTreatmentClampWindow` 自动夹取到合法范围），再返回列表页 `GDDC_PAGE_LIST_TREATMENT`。

### 6.3 取消删除（KEY_CANCLE）

1. 点确认页 `KEY_CANCLE`（控件 2）调用 `listTreatmentDeleteCancel()`；仅当 `deletePatientId != 0` 时执行。
2. 不做任何 EPROM 删除，清除 `deletePatientId`，刷新并返回列表页 `GDDC_PAGE_LIST_TREATMENT`，患者表与病历保持原样。

### 6.4 触摸放行与状态约束

1. 删除确认页等待期间，触摸总闸 `listTreatmentUsbButtonAllowed` 只放行本页 `KEY_DELETE`/`KEY_CANCLE`，其余控件与其他页面触摸一律屏蔽；删除为本地同步操作，在确认回调内一次执行完毕，不设异步忙状态。
2. `deletePatientId` 与其他运行状态一致放 `listTreatmentCtx`（RAM/ZI），开机为 0（不在删除流程），不新增 EPROM 寄存器、不做掉电持久化。
3. 本闭环为强制规格：任何时刻维护都必须保留“先确认后删除”，不得改为点 DELETE 直接删除、不得跳过确认页。

**屏幕工程待办（重要）**：删除确认页 14 需在大彩 VisualTFT 工程 `vTFT_HMI/dwLaser.tftprj` 中按控件 ID 1–2、10–13 建立按钮与文本框，否则 `SetScreen(14)` 无对应页面；固件侧控件 ID 已就绪。

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
4. **U 盘 CSV 必须带时间并带回**：第 10 列 `rtc`，格式 `YYYY-MM-DD HH:MM:SS`；未记录时间时该列留空。表头为 `id,name,gender,age,power,wave,protocol,energy,time,rtc`。
   - 导入解析：列数 ≥ 9 即接受，旧版 9 列备份仍可载入，时间按“未记录”处理；有第 10 列但格式/范围非法则整行载入失败。
   - 导入回读核对（`treatmentLogVerifyUdisk`）必须同时比较 RTC 6 个字段，不允许跳过时间字段。
   - 客户端如 Excel 另存，需保持该列格式（空格分隔日期与时间，不拆成两列）。
5. **患者姓名长度 18 个字符**：由 `treatment.h` 的 `CONFIG_TREATMENT_NAME_LEN = 18` 定义，缓冲区 `TREATMENT_NAME_SIZE = 19`（含结束符），`treatmentLog_t.name` 与 `patientRecord_t.name` 共用该长度；固件在姓名录入处按 `TREATMENT_NAME_SIZE - 1` 截断，屏幕输入控件 `text_len_max` 保持 255，以固件截断为准。
6. 姓名长度改变会改变片上患者行尺寸（当前 24 字节），存量病历与新结构不兼容；沿用既有约定——固件 CRC 变化时 `dcHmiLoopInit` 清空整片 EPROM，不做迁移与向后兼容。
7. 本节的 RTC 列与姓名长度属于数据规格，任何后续改动必须先更新本节，并同步 `minicsvApp.c` 的列定义（`TREATMENT_CSV_COLUMNS_MIN` / `TREATMENT_CSV_COLUMNS`）与 `treatmentCsvHeader`。

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

1. **有效槽位（有对应病人）**：`TEXT_RECORD_COUNT_i` 显示固定英文格式 `Records: X`，其中 `X = treatmentGetRecordCountForPatient(pat.id)`，即该患者实际已记录的病历数量；**X 可以为 0**，此时显示 `Records: 0`。
2. **空槽位**：仍按第十节下发空串，不显示任何内容。
3. 文案为纯 ASCII（英文字母、冒号、空格与数字），符合根目录 `AI_RULES.md` 显示文本一律英文的至高规格，屏幕现有字体（font 6，ASC_CHS_20）可直接渲染，无需改屏幕工程。
4. 曾提出的中文“病历数量X”方案：与 `AI_RULES.md` 英文显示至高规格冲突，且屏幕资源无中文字体（`dwLaser.fidx` 仅含 30 个 ASCII 字体，`charset.txt` 不含“病历数量”字形），经确认**不采用**。将来若要恢复中文显示，必须先经仓库所有者人工授权并修改 `AI_RULES.md` 至高规格，再完成屏幕中文字体工程（VisualTFT 配置中文字体、加入字形、重建并烧录屏幕资源），固件按 GB2312/GBK 编码下发。
