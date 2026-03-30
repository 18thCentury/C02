#!/usr/bin/env python3
"""Extract a readable map from iot_run.c.

Usage:
    python3 scripts/extract_iot_map.py
"""

from __future__ import annotations

import re
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
SOURCE = REPO_ROOT / "iot_run.c"
OUTPUT = REPO_ROOT / "docs" / "iot_map.md"

MODULE_PATTERN = re.compile(r'"(\.\./(?:app|opensource)/[^"\s]+\.(?:cpp|c))"')
FUN_DEF_PATTERN = re.compile(r"^\s*(?:undefined\d*|undefined|int|void|bool|char|float|double|long|uint|ushort|ulong|size_t)\s+(FUN_[0-9A-Fa-f]{8})\s*\(")
ENTRY_PATTERN = re.compile(r"processEntry\s+entry\s*\(void\)")
MAIN_PATTERN = re.compile(r"undefined4\s+FUN_004881dc\s*\(")


def with_line_numbers(lines: list[str], pattern: re.Pattern[str]) -> list[tuple[int, str]]:
    matched: list[tuple[int, str]] = []
    for idx, line in enumerate(lines, start=1):
        if pattern.search(line):
            matched.append((idx, line.rstrip("\n")))
    return matched


def main() -> None:
    if not SOURCE.exists():
        raise FileNotFoundError(f"missing source file: {SOURCE}")

    lines = SOURCE.read_text(encoding="utf-8", errors="replace").splitlines(keepends=True)

    entry_hits = with_line_numbers(lines, ENTRY_PATTERN)
    main_hits = with_line_numbers(lines, MAIN_PATTERN)

    modules: dict[str, list[int]] = {}
    for idx, line in enumerate(lines, start=1):
        for mod in MODULE_PATTERN.findall(line):
            modules.setdefault(mod, []).append(idx)

    fun_defs = with_line_numbers(lines, FUN_DEF_PATTERN)

    report: list[str] = []
    report.append("# iot_run.c 索引（自动生成）\n")
    report.append("\n")
    report.append("- 生成脚本：`scripts/extract_iot_map.py`\n")
    report.append(f"- 源文件：`{SOURCE.name}`\n")
    report.append(f"- 总行数：{len(lines)}\n")
    report.append(f"- FUN_函数定义数量（粗略统计）：{len(fun_defs)}\n")
    report.append("\n")

    report.append("## 入口定位\n\n")
    if entry_hits:
        for ln, text in entry_hits:
            report.append(f"- `processEntry entry` 在第 {ln} 行：`{text.strip()}`\n")
    else:
        report.append("- 未找到 `processEntry entry`\n")

    if main_hits:
        for ln, text in main_hits:
            report.append(f"- 主控函数 `FUN_004881dc` 在第 {ln} 行：`{text.strip()}`\n")
    else:
        report.append("- 未找到 `FUN_004881dc` 定义\n")

    report.append("\n## 模块路径线索\n\n")
    if modules:
        for mod, locs in sorted(modules.items()):
            preview = ", ".join(map(str, locs[:6]))
            suffix = " ..." if len(locs) > 6 else ""
            report.append(f"- `{mod}`：出现 {len(locs)} 次，行号示例：{preview}{suffix}\n")
    else:
        report.append("- 未识别到 `../app/*.cpp` 或 `../opensource/*.c` 路径\n")

    report.append("\n## 关键函数样例（前 40 个）\n\n")
    for ln, text in fun_defs[:40]:
        report.append(f"- L{ln}: `{text.strip()}`\n")

    OUTPUT.write_text("".join(report), encoding="utf-8")
    print(f"generated: {OUTPUT}")


if __name__ == "__main__":
    main()
