# 入口指引 — 请先阅读仓库根目录 AGENTS.md

本目录的所有 AI 维护工作，均以**仓库根目录 `D:\GitHub\dwLaser_Application\AGENTS.md`** 为最高优先级指令。

核心结论（摘要，完整内容以根 AGENTS.md 为准）：

1. 自编源码必须同时通过 **AC5（armcc，uAC6=0）与 AC6（armclang，uAC6=1）** 两个编译器的 Rebuild，均 0 Error 才算通过。
2. 当前分支 `run_treatment` 只做**病历相关功能与 EPROM 病历存储**，其他问题不在本分支解决。
3. 本分支唯一活跃工程：`targetBoard_G5_TRI_A1_20260915`；其余 targetBoard 工程全部停止维护、禁止修改（各目录内有 `停止维护说明.md`）。
4. 自编源码统一使用 **UTF-8 编码**（新建/另存文件带 BOM），严禁 GBK/ANSI 等其他编码，任何编辑保存都必须遵循（详见根 AGENTS.md 第四节）。
5. 代码风格（详见根 AGENTS.md 第五节）：**2 空格缩进、`//` 注释、大括号与函数名同行**；局部变量小驼峰如 `firstName`、全局变量大驼峰如 `FirstName`；配置宏以 `CONFIG` 开头并集中放入 `AppConfig.h`。Keil 已勾选 Insert spaces for tabs、Tab size=2（按 Tab 即 2 空格）。目标风格仅用于新建/修改部分，不做全库批量重排、不格式化相邻行。

**进入任何具体工程前，请先回到根目录阅读完整 AGENTS.md。**
