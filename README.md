# C02 IoT 反编译代码整理项目

该仓库原始内容是一个超大体量的单文件反编译结果（`iot_run.c`），可读性较差，无法直接按普通 C/C++ 项目方式构建。

本次整理目标：

- 保留原始反编译文本，避免破坏证据链与可追溯性；
- 提供“入口 -> 模块 -> 关键行为”的阅读路径；
- 提供可重复执行的脚本，自动从 `iot_run.c` 提取模块线索和函数统计；
- 将分析结果沉淀在 `docs/`，便于二次逆向。

## 仓库结构

- `iot_run.c`：原始反编译代码。
- `scripts/extract_iot_map.py`：自动提取模块、入口函数、源码路径线索、`FUN_xxx` 函数统计。
- `docs/architecture.md`：人工整理的架构解读与阅读顺序。
- `docs/iot_map.md`：由脚本生成的索引文档（可重复生成）。

## 快速开始

```bash
python3 scripts/extract_iot_map.py
```

执行后会刷新 `docs/iot_map.md`。

## 建议阅读顺序

1. 先看 `docs/architecture.md` 了解主干逻辑和模块划分；
2. 再看 `docs/iot_map.md` 通过行号跳回 `iot_run.c` 做深入分析；
3. 最后在 `iot_run.c` 里对具体 `FUN_` 函数重命名并提取子模块（建议后续阶段进行）。
