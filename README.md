# C02 Industrial IoT Refactor

本仓库包含两部分内容：

1. `iot_run.c`：原始反编译文本（保留用于追溯）；
2. `src/` + `include/`：按工业项目结构重建的可编译 IoT 应用。

## 目标

- 忠于 `iot_run.c`，优先复刻关键启动行为；
- 在可复刻基础上完成工程化（模块、配置、日志、构建系统）；
- 支持后续逐步替换为真实串口/MQTT/Modbus/Web 硬件协议实现。

## 目前已完成的 1:1 启动行为复刻（核心路径）

已在 `LegacyBootstrap` 中对 `FUN_004881dc` 的关键分支进行可维护实现：

- `/tmp/.system.ini` 缺失时创建，并输出 `SYSTEM   START`；
- 固定输出 `start iot` 启动标志；
- 复刻 `hisTech.ini` 与 `/tmp/hisTech.ini` 的分支逻辑：
  - 缺失两者 -> `iot init v1 START`；
  - 本地存在且 `tech_mode=1` -> 复制到 `/tmp`，`iot init v2 START`；
  - 本地存在且 `tech_mode=0` -> 移动到 `/tmp`，`iot init v1 manual START`；
  - `/tmp/hisTech.ini` 已存在 -> `iot   UPDATE ...`，且 `tech_mode=1` 时回拷本地文件。

- 增强配置读取：支持空白裁剪、布尔/整数默认值读取；
- 新增参数采集：启动时采集 machine/kernel/hostname/uptime/meminfo 并写回 `runtime.*` 配置键。

## 项目结构

- `include/iot/`：公共接口（应用、日志、配置、模块抽象、启动兼容层）；
- `include/iot/modules/`：业务模块接口声明；
- `src/`：核心实现；
- `src/modules/`：模块实现；
- `config/system.ini`：运行配置示例；
- `iot_run.c`：原始反编译代码归档。

## 构建与运行

```bash
cmake -S . -B build
cmake --build build
./build/iot_app
```
