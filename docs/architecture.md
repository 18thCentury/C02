# 架构与代码阅读指南

## 1. 代码现状判断

`iot_run.c` 是反编译产物，混合了：

- 类型重建（大量 `typedef`）；
- 动态链接符号包装；
- 业务函数（命名为 `FUN_地址`）；
- 第三方库代码片段（例如 OpenSSL、Mongoose、Paho MQTT）。

因此它不是“可直接维护的源工程”，而是“可分析文本”。本项目整理重点是建立索引和可读路径。

## 2. 程序入口链路

从可识别入口开始：

1. `processEntry entry`（反编译入口壳）；
2. 调用 `FUN_00422ae4`；
3. `FUN_00422ae4` 内通过 `__libc_start_main` 启动 `thunk_FUN_004881dc`；
4. `thunk_FUN_004881dc` 进一步落到主逻辑 `FUN_004881dc`。

## 3. `FUN_004881dc` 的主流程（推断）

该函数可视为 `serial_main` / 程序主控：

- 初始化日志与基础运行环境；
- 读取/写入 `/tmp/.system.ini`、`hisTech.ini` 等状态文件；
- 根据配置和状态执行“首次启动 / 更新启动”分支；
- 启动后续线程或服务模块。

## 4. 可识别业务模块（由日志源码路径字符串推断）

通过 `"../app/*.cpp"` 字符串可推断历史源码模块：

- `serial.cpp`：主流程、认证、启动控制；
- `pushThread.cpp`：网络探测、MQTT 推送线程；
- `mqttService.cpp`：MQTT 消息处理与远程更新；
- `modbus-server.cpp`：Modbus 服务线程；
- `webservice.cpp`：Web 参数设置与接口相关；
- `ipset.cpp`：网络与 MAC/接口设置；
- `power.cpp`：电源/PCIE 复位；
- `cpp_base.cpp`：基础配置与工具函数。

另外可见 `../opensource/mongoose.c`，说明嵌入了 Mongoose HTTP/Web 相关能力。

## 5. 建议的后续重构路线

> 当前提交不改动 `iot_run.c` 的语义，仅增强可读性。若继续推进，可按以下顺序：

1. 在 `iot_run.c` 上建立“函数重命名表”（`FUN_xxx -> 语义名`）；
2. 抽取主流程图（启动、线程创建、退出条件）；
3. 按模块建立独立文档（MQTT、Modbus、Web、Network）；
4. 对高价值函数补充伪代码与状态机图；
5. 最终再考虑分文件重组（前提是可验证行为一致）。
