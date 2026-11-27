# AGENTS.md — AI 智能体入口（先读规则再改动）

> 本文件仅为 AI 智能体进入本仓库的入口，不维护具体规则与摘要。
> 做任何修改、编译、提交之前，必须先完整阅读仓库根目录 `AI_RULES.md` 并严格遵守；规则以 `AI_RULES.md` 为唯一权威，本文件与其冲突时一律以 `AI_RULES.md` 为准。

- 开发主线：`master` 为唯一主线；`run_treatment` 已合并并永久冻结（冻结点 tag `frozen/run_treatment`），不再提交。
- 唯一活跃工程：`MCU_Application/targetBoard_G5_TRI_A1_20260915`；其余电路板工程停止维护、禁止修改。
- 本机网络代理：访问外网（推送 GitHub、拉取依赖等）走本地 HTTP/HTTPS 代理 `127.0.0.1:7890`；Git 已配置 http.proxy 与 https.proxy 指向 `http://127.0.0.1:7890`。
- HMI 交互规格必读：`MCU_Application/Doc/病历列表页UI规格.md` 是全硬件板通用的病历 HMI 交互单一事实源；每次检测、审核或维护规则文件（含 `AI_RULES.md`）时，必须同时完整阅读该文件后再开展检查或改动；其与 `AI_RULES.md` 冲突时一律以 `AI_RULES.md` 为准。
- 工程质量门必查：`MCU_Application/Doc/工程质量门检查清单.md`（全硬件板通用）是构建、内存、FRAM、HMI、证据与提交各质量门的检查清单；每次改动后按其条目逐项核对，全部通过才算完成，时点数字以最新构建日志与 `.map` 实测为准。
- 规则变更只在 `AI_RULES.md` 进行，本文件不重复细则。
