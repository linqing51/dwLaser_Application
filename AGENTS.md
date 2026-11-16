# AGENTS.md — AI 智能体维护本仓库的最高优先级指令（必读）

> **本文件是所有 AI 智能体（含任何工具、任何新建会话/工作）在本仓库开展工作前必须首先阅读并严格遵守的规则。**
> 开始任何编译、修改、提交之前，先完整读完本文件；本文件的约束优先级高于会话中的临时推断。
> 本规则由仓库所有者确立并要求**永久生效、随仓库分发**，无需用户在每个会话重复说明。
> 最后更新：2026-11-16。

---

## 一、三条铁律（不可违反）

### 铁律 1：自编源码必须同时通过 AC5 与 AC6 两个编译器验证
- **AC5 = Arm Compiler 5（armcc，ARMCC V5.06）**，对应 Keil 工程 `uAC6=0`。
- **AC6 = Arm Compiler 6（armclang，Arm Compiler for Embedded 6.24，基于 LLVM/Clang）**，对应 `uAC6=1`。
- 凡本仓库**自编源码**（非第三方库、非 HAL/中间件），每次改动后都必须分别用 **AC5 和 AC6 两个版本各做一次完整 Rebuild**，两者均达到 **0 Error** 才算编译验证通过。
- 禁止只在一个编译器下通过就声称"编译通过"。AC6（armclang）语法更严格，常见差异（如 C11 关键字、隐式声明、`inline` 链接性质、宏拼写）必须在两个编译器下都成立。
- 第三方库（STM32 HAL、FreeRTOS、FatFs、USB Host、EasyLogger、mbedTLS 等）不要求双编译器零警告，但自编代码对它们的调用方式必须在两个编译器下都可编译。

> **本分支范围决定（2026-11-15，所有者明确拍板）：`run_treatment` 分支不进行 AC6 编译器迁移。**
> - 即不新增 FreeRTOS GCC/ARM_CM4F port、不为 armclang 清零而调整工程编译选项、不为此改动 FreeRTOS 等第三方库，也不处理 armclang 下的 static 声明冲突。
> - 当前 AC6（armclang）的 1368 个错误是**已知并有意搁置的阻断**，不是本分支待办：主因是 FreeRTOS 仍用 `portable/RVDS/ARM_CM4F` port（armclang 不识别 armcc 的 `__forceinline`，仓库无 GCC port），另有 dcHmiApp.c 9 处 static 声明冲突。
> - 因此本分支的编译验证落地标准为 **AC5（armcc）0 Error 并生成 hex**；AC6 双编译器 0 Error 的要求保留，待将来专门的"AC6 编译器迁移分支"统一完成，任何 AI 不得在本分支擅自启动该迁移。

### 铁律 2：本 Git 分支只做"病历相关功能 + EPROM 病历存储"，其他问题一律不在本分支解决
- 当前分支：`run_treatment`。
- **允许**在本分支修改的范围，仅限：
  - 病历/治疗记录相关功能（患者与记录结构、浮动区块、归一化双结构、断电原子提交、固件变化清空病历判据等）；
  - EPROM 病历存储布局与对应 CRC（病历分区、地址、CRC 校验、清空/恢复流程）。
- **禁止**在本分支顺手修复任何与病历/EPROM 病历存储无关的问题（包括但不限于历史编译错误、驱动重构、格式化、警告清理、其他功能优化）。
- 发现与本分支目标无关的问题：**只记录、不修复**，在报告中标注为"非本分支范围"，留待对应分支处理。

#### EPROM 数据保留策略（2026-11-15，所有者明确拍板，永久生效）
- **固件升级不保留任何 EPROM 病历数据。** 固件 CRC 变化（首次烧录 / 固件升级 / CRC 失败恢复）时，`dcHmiLoopInit` 调用 `treatmentEpromClear()` 清空病历区块是**预期设计行为，不是缺陷**；任何 AI 不得把它当作 bug 修复，也不得新增旧格式到新格式的数据迁移逻辑。
- FRAM 硬件块保护（状态寄存器 BP1/BP0）必须保持关闭（状态寄存器写 0x00）：病历记录从区块高端向下增长，开启 BP1=1 会保护高 1/2 阵列、使记录写入被静默拒绝而列表空白。存储越界一律由软件 `InRegion`/`FreeBytesPR` 防护，不依赖硬件块保护。

### 铁律 3：唯一活跃工程是 G5；其余电路板工程在本分支阶段全部停止维护、禁止修改
- **本分支唯一活跃、唯一允许编译验证与修改的工程：**
  - 工程目录：`MCU_Application/targetBoard_G5_TRI_A1_20260915/MDK-ARM`
  - 工程文件：`targetBoard_G5_TRI_A1_20260915.uvprojx`（单 Target，芯片 STM32F405，板型宏 `G5_TRI_A1_20260915`）
  - 板级配置目录：`MCU_Application/config/G5_TRI_A1_20260915`
- **除上述 G5 工程外，其他所有电路板工程在本 Git 分支阶段一律停止维护：不得修改其源文件、工程文件（.uvprojx）、include 路径、宏定义，也不得为"修复其编译错误"而改动它们。**
- 这些工程既有的历史编译错误属于已知历史破损，**不在本分支处理**（见铁律 2）。

---

## 二、工程状态清单（MCU_Application 下）

| 工程目录 | 本分支状态 | 是否允许修改 |
|---|---|---|
| `targetBoard_G5_TRI_A1_20260915` | **活跃（唯一）** | **是，按铁律 1/2 执行** |
| `targetBoard_FreeRTOS_6M3S_RASPI_A1_20260519` | 停止维护 | 否 |
| `targetBoard_M450_RASPI_2V0_20260703` | 停止维护 | 否 |
| `targetBoard_M450_RASPI_20260106` | 停止维护 | 否 |
| `targetBoard_G5_A0` | 停止维护 | 否 |
| `targetBoard_G5_A1` | 停止维护 | 否 |
| `targetBoard_G5_TRI_A1` | 停止维护 | 否 |
| `targetBoard_G5_TRI_A1_RASPI` | 停止维护 | 否 |
| `targetBoard_G9_A1` | 停止维护 | 否 |
| `targetBoard_G9_TRI_A1_RASPI` | 停止维护 | 否 |
| `targetBoard_M12_A1` | 停止维护 | 否 |

> 各停止维护工程目录内均放置有 `停止维护说明.md`，进入这些目录时应立即停止修改并回到本文件。

---

## 三、双编译器验证操作方法（仅对活跃 G5 工程执行）

工具链（本机实际安装路径，均不在系统 PATH，需显式指定）：
- Keil UV4：`C:\Keil_v5\UV4\UV4.exe`
- AC5（armcc）：`C:\Keil_v5\ARM\ARMCC\Bin\armcc.exe`（V5.06 update 7，build 960）
- AC6（armclang）：`C:\Keil_v5\ARM\ARMCLANG\Bin\armclang.exe`（Arm Compiler for Embedded 6.24）

切换编译器：在 G5 工程 `targetBoard_G5_TRI_A1_20260915.uvprojx` 中修改 `<uAC6>`：
- `uAC6=0` → 使用 AC5（armcc）；
- `uAC6=1` → 使用 AC6（armclang）。

命令行 Rebuild（`-r` 为强制完整重编，`-b` 可能只做增量；`-o` 输出日志，`-j0` 不弹对话框）：
```
UV4.exe -r targetBoard_G5_TRI_A1_20260915.uvprojx -o <日志文件> -j0
```
流程：
1. 设 `uAC6=0`，Rebuild → 保存 AC5 日志，确认 0 Error；
2. 设 `uAC6=1`，Rebuild → 保存 AC6 日志，确认 0 Error；
3. 两者都 0 Error 才判定编译验证通过；日志作为执行证据保存，不得虚构结果。

**工具链已知坑（CreateProcess failed）**：若工程 ARM Compiler 选项为 "Use default compiler version 5"（使用默认编译器版本5），命令行可能因全局默认解析异常，把 AC5 工程错误解析到 `ARMCLANG` 目录、却调用 AC5 文件名，拼出不存在的 `...\ARMCLANG\Bin\ArmCC` 而 CreateProcess failed。复位方式：Keil GUI → Options for Target(Alt+F7) → Target → ARM Compiler，明确选具体版本 `V5.06 update 7 (build 960)`（不要用"默认"），保存后工程新增 `<pArmCC>5060960::...\ARMCC</pArmCC>` 即恢复正常。

注意：`uAC6` 切换属于验证操作；验证结束后应使工程文件保持在仓库规定的编译器设置，不要遗留无关改动。

### 本机工具链安装清单（2026-11-16 实测，均不在系统 PATH，须用全路径调用）

| 工具 | 安装根目录 | 可执行文件全路径 | 实测版本 |
|---|---|---|---|
| Git for Windows | `C:\Program Files\Git` | `C:\Program Files\Git\cmd\git.exe` | git 2.55.0.windows.3 |
| Keil MDK（μVision） | `C:\Keil_v5` | `C:\Keil_v5\UV4\UV4.exe` | 5.43.1.0（MDK Plus 5.43） |
| AC5（armcc） | `C:\Keil_v5` | `C:\Keil_v5\ARM\ARMCC\Bin\armcc.exe` | ARM Compiler 5.06 update 7（build 960） |
| AC6（armclang） | `C:\Keil_v5` | `C:\Keil_v5\ARM\ARMCLANG\Bin\armclang.exe` | Arm Compiler for Embedded 6.24 |

- `C:\Keil_v5` 下一级目录：`ARM`、`C251`、`C51`、`Eclipse`、`UV4`、`license_terms`。
- 命令行调用 Git 须用全路径，如 `"C:\Program Files\Git\cmd\git.exe" -C <仓库路径> ...`；路径含空格必须加引号，直接写 `git` 会因不在 PATH 而失败。
- 上述工具若重新安装或升级导致路径/版本变化，应重新实测并更新本表与"最后更新"日期。

---

## 四、源码编码规则（统一 UTF-8，以后编辑必须遵循）

1. **强制 UTF-8**：所有自编源码（`.c`/`.h`，含注释与字符串中的中文）一律以 **UTF-8 编码**保存；严禁使用 GBK、ANSI、Latin-1 等其他编码，也不得在保存时让编辑器回退成系统默认 ANSI 代码页。
2. **BOM 约定**：新建或另存源文件统一使用 **UTF-8 带 BOM**（文件头字节 `EF BB BF`，与多数现有 `.c` 文件及 `treatment.c` 文件头约定一致）。仓库内既有的 UTF-8 无 BOM 头文件（部分 `*.h`）保持现状、可正常编译，**不做批量转换**；但对其修改后仍须以 UTF-8 保存，不得改变编码。
3. **编辑器设置**：在 Keil / VS Code / 其他编辑器中显式把编码选为 UTF-8（带 BOM 优先），关闭"自动检测/自动转 ANSI"类选项；保存后若发现中文乱码，应撤销并重新以 UTF-8 保存，不得带乱码继续。
4. **验证**：涉及含中文文件的改动，按铁律 1 完成编译验证（本分支以 AC5 0 Error 为准），确认 UTF-8 中文注释与字符串未产生告警或乱码；无硬件时不声称运行时显示效果，仅称编译级验证。

---

## 五、代码风格规范（自编代码统一遵循）

> **适用范围**：以下为**目标风格**，强制用于**新建文件及新增/修改的代码**。现有历史代码（Tab 缩进、`/* */`、大括号另起行等）**不做全库批量重排**（受铁律 2 约束，批量格式化属无关改动且污染 diff）。**改动到既有文件时，仅对新增或实际修改的那部分代码应用新风格，不重排未改动的旧代码，也不顺手格式化相邻行**，保持 diff 最小。

1. **缩进 2 空格**：每级缩进统一用 **2 个空格**，禁止使用 Tab，避免 Tab/空格混用。**Keil 已配置好**：`Edit → Configuration → Editor → C/C++ Files` 中已勾选 **Insert spaces for tabs** 且 **Tab size = 2**，即编辑 C/C++ 时按 Tab 键自动插入 2 个空格；其他编辑器（VS Code 等）也须把 Tab 设为 2 空格。
2. **注释只用 `//`**：统一使用 `//` 行注释，**不使用** `/* ... */` 块注释（多行说明用多行 `//`）；注释侧重解释"为什么"。
3. **大括号与函数名同行（K&R 风格）**：函数及 `if/for/while/switch` 的左大括号写在声明行末尾，不另起一行：
```c
retType funcName(uint16_t arg) {
  if(arg > 0) {
    // ...
  }
}
```
4. **局部变量：小驼峰（camelCase）**：首字母小写、后续单词首字母大写，如 `firstName`、`recordCount`。
5. **全局变量：大驼峰（PascalCase）**：首字母大写，如 `FirstName`、`GlobalState`。
6. **配置宏：CONFIG 前缀、集中管理**：新增配置性宏一律以 `CONFIG` 开头、全大写，并集中放入板级 `AppConfig.h`；板级硬件/EPROM 地址/总线类宏按既有分层归属 `BoardConfig.h`、`sPlcConfig.h`，不新建零散配置头，也不在 `.c` 内随意 `#define` 配置项。

---

## 六、行为守则

1. **先读本文件再动手**：任何新建会话首次进入本仓库，先读本 AGENTS.md，再读活跃工程目录，不要凭任务名自行扩大范围。
2. **最小改动、不越界**：只改 G5 活跃工程中与病历/EPROM 病历存储相关的内容；不碰停止维护工程；不修复无关问题。
3. **证据为准**：编译结果以 Keil 日志为准，0 Error 必须有对应日志支撑；无硬件时不得声称功能、时序、断电原子性已通过上板验证，只能称为"编译级验证"。
4. **不改变对外接口签名**：兼容修复优先保持头文件函数签名，必要时用同名薄适配并标注影响面。
5. **Git 纪律**：优先新增提交而非 `--amend`；不使用 `--no-verify`；不擅自 `reset --hard`、强推；提交信息应体现病历/EPROM 主题。
6. **Keil 自动产物**：编译可能自动改写各工程 `RTE_Components.h`、`.dbgconf` 等 RTE 文件，这些不属于业务改动，提交前应核对并恢复无关工程的自动改动。

---

## 七、生效与变更

- 本文件随仓库版本控制分发，对所有 AI 智能体与维护者具有约束力。
- 若仓库所有者明确修改上述规则，应同步更新本文件并更新"最后更新"日期；在本文件未修改前，一切以本文件为准。
