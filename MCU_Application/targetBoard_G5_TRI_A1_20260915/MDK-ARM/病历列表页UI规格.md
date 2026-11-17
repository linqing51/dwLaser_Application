# 病历列表页 UI 行为规格 — GDDC_PAGE_LIST_TREATMENT（页面 ID 13）

本文件固化病历列表页页码、搜索、关闭按钮、患者选择闭环、删除患者确认，以及 USB 导出/导入确认页的**强制交互行为**。任何 AI 维护此页面前必须先读完本文件，并按此实现，不得擅自更改匹配口径、排序规则、显示格式、页面跳转出口、患者选择归属与删除确认流程。

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

## 四、USB 导出/导入确认页 GDDC_PAGE_OPERATOR_USB_CONFIRM（页面 ID 16）

操作页 `KEY_SAVE_UDISK`（控件 3，导出）与 `KEY_LOAD_UDISK`（控件 4，导入）**都不立即读写 U 盘**，先进入本确认页；页面上所有文字**一律英文显示**。两个流程共用本页面，由 `listTreatmentCtx.usbOp` 区分（`1` = 导出 SAVE，`2` = 导入 LOAD）。

### 4.1 导出 SAVE（usbOp = 1，点 KEY_SAVE_UDISK）

1. 进入时刷新以下文本框（控件 ID 见 `dcHmiRes.h`）：
   - `TEXT_SUMMARY_0`（控件 1，标题）：`Export Patient Backup?`
   - `TEXT_SUMMARY_1`（控件 2）：`Export patients and saved treatment records to USB?`
   - `TEXT_SUMMARY_2`（控件 3）：`The existing patient backup on this USB will be replaced. The records on the device will be erased.`
   - `TEXT_SUMMARY_3`（控件 4，预留）：清空（单空格）
2. `KEY_CANCLE`（控件 10）：取消写入、不修改 U 盘，返回操作页 `GDDC_PAGE_OPERATOR_USB`。
3. `KEY_CONFIRM`（控件 11）：授权把机内病历转换成 CSV，复用 `treatmentLogSaveToUdisk`（文件名 `TREATMENTLOG_FILENAME` = `/treatment_v1.csv`，覆盖同名文件）；实际写入在 `listTreatmentUsbLoop` 中执行一次，不在按键回调里阻塞。
4. 完成后自动返回 `GDDC_PAGE_OPERATOR_USB`，并在 `TEXT_SUMMARY_USB`（操作页控件 2）显示本次结果：
   - 成功：`USB Backup Successful`
   - 失败按错误码：`NO UDISK` / `NO RECORDS` / `USB OPEN FAILED` / `USB BACKUP FAILED`

### 4.2 导入 LOAD（usbOp = 2，点 KEY_LOAD_UDISK）

1. 进入时刷新以下文本框（数量取进入确认页时的**机内**当前值）：
   - `TEXT_SUMMARY_0`（控件 1，标题）：`Replace Device Records?`
   - `TEXT_SUMMARY_1`（控件 2）：`Replace all patients and treatment records on the device with the USB backup?`
   - `TEXT_SUMMARY_2`（控件 3，动态）：`Backup contents: x patients · y treatment records.`
     - `x` = 机内患者数 `treatmentEpromGetPatientCount()`；`y` = 机内治疗记录数 `listTreatmentGetCount()`（即 `NVRAM0[DM_TREATMENT_NUM]`，负值防御返回 0）。
   - `TEXT_SUMMARY_3`（控件 4）：`The current device records will be replaced. To keep them, export to another USB first. This action cannot be undone.`
2. `KEY_CANCLE`（控件 10）：取消操作、不修改机内 EPROM，返回操作页 `GDDC_PAGE_OPERATOR_USB`。
3. `KEY_CONFIRM`（控件 11）：授权读取 U 盘 CSV 并覆盖本机 EPROM，复用 `treatmentLogLoadFromUdisk`；实际读取在 `listTreatmentUsbLoop` 中执行一次，不在按键回调里阻塞。
4. 完成后自动返回 `GDDC_PAGE_OPERATOR_USB`，并在 `TEXT_SUMMARY_USB`（操作页控件 2）显示本次结果：
   - 成功：`Backup imported from USB. Device records have been replaced.`
   - 失败按错误码：`NO UDISK` / `NO FILE` / `BAD FILE` / `USB IMPORT FAILED`

### 4.3 通用触摸与状态约束

1. 确认页等待期间（状态 6）只放行 CANCLE/CONFIRM，读写执行期间（状态 7）屏蔽一切触摸。
2. 确认/取消回调导出/导入通用：`listTreatmentUsbConfirm`（状态 6→7）、`listTreatmentUsbCancel`（状态 6→0 回操作页）。
3. 若确认页被别处切走（如关机确认/休眠），轮询检测到当前页不符即放弃本次流程并退出忙状态，避免触摸被永久屏蔽。

**屏幕工程待办（重要）**：确认页 16 目前在屏幕工程 `vTFT_HMI/dwLaser.tftprj` 中**尚未建立**（无对应 .tft 页面），需在大彩 VisualTFT 中新建该页面并按控件 ID 1–4、10、11 做出文本框与按钮，否则 `SetScreen(16)` 无对应页面。固件侧控件 ID 已就绪；`TEXT_SUMMARY_2` 中的中点 `·` 能否显示取决于屏幕字库。

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

本部分固化“列表页删除按钮 → 进入删除确认页 → 确认后级联删除患者及其全部病历”的强制闭环。涉及控件：列表页 `KEY_DELETE_0–4`（控件 25–29）、确认页 `GDDC_PAGE_DELETE_TREATMENT_CONFIRM`（页面 ID 14），确认页按钮 `KEY_DELETE`（控件 1）、`KEY_CANCLE`（控件 2），文本框 `TEXT_SUMMARY_0–3`（控件 10–13）。页面上所有文字一律英文显示。

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
- 改动后按 `活跃工程说明.md` 做 AC5 Rebuild，**0 Error 才算通过**；无硬件时只能称为“编译级验证”，不得声称上板功能/时序已验证。
- 若控件 ID、页面编号或本文件描述的规则发生变化，必须同步更新本文件，保持规格与代码一致。
