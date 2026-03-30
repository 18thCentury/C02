# iot_run.c 索引（自动生成）

- 生成脚本：`scripts/extract_iot_map.py`
- 源文件：`iot_run.c`
- 总行数：220181
- FUN_函数定义数量（粗略统计）：2720

## 入口定位

- `processEntry entry` 在第 14276 行：`void processEntry entry(void)`
- 主控函数 `FUN_004881dc` 在第 71322 行：`undefined4 FUN_004881dc(undefined4 param_1,undefined4 param_2)`

## 模块路径线索

- `../app/cpp_base.cpp`：出现 3 次，行号示例：17482, 17837, 17868
- `../app/ipset.cpp`：出现 6 次，行号示例：63916, 63935, 63966, 64195, 64212, 64241
- `../app/modbus-server.cpp`：出现 5 次，行号示例：64894, 64904, 64913, 64937, 64945
- `../app/mqttService.cpp`：出现 4 次，行号示例：66008, 66019, 66033, 66056
- `../app/power.cpp`：出现 2 次，行号示例：66199, 66203
- `../app/pushThread.cpp`：出现 26 次，行号示例：66680, 66688, 66695, 66696, 66717, 66757 ...
- `../app/serial.cpp`：出现 14 次，行号示例：6292, 6328, 6361, 6369, 6372, 6423 ...
- `../app/webservice.cpp`：出现 2 次，行号示例：75732, 77528
- `../opensource/mongoose.c`：出现 29 次，行号示例：105027, 105395, 105415, 105437, 105450, 105478 ...

## 关键函数样例（前 40 个）

- L5402: `void FUN_00412840(void)`
- L5411: `void FUN_00412850(char *param_1,time_t param_2,int param_3,time_t param_4)`
- L5420: `void FUN_00412860(int param_1)`
- L5429: `void FUN_00412870(undefined4 param_1)`
- L5438: `void FUN_00412880(int param_1,undefined4 param_2,undefined4 param_3,time_t param_4)`
- L5447: `void FUN_00412890(undefined4 param_1,undefined4 param_2,undefined4 param_3,time_t param_4)`
- L5456: `void FUN_004128a0(undefined4 param_1)`
- L5465: `void FUN_004128b0(int param_1,int *param_2,uint *param_3,uint *param_4)`
- L5474: `void FUN_004128c0(int *param_1)`
- L5483: `void FUN_004128d0(int param_1,undefined4 param_2,int param_3,undefined2 *param_4)`
- L5492: `void FUN_004128e0(char *param_1,int param_2,uint param_3,undefined4 param_4)`
- L5501: `void FUN_004128f0(void)`
- L5510: `void FUN_00412900(int param_1,undefined4 param_2,undefined4 param_3,time_t param_4)`
- L5519: `void FUN_00412910(void)`
- L5528: `void FUN_00412920(void)`
- L5537: `undefined8 FUN_00412930(int *param_1,int param_2)`
- L5548: `void FUN_00412940(uint *param_1,int *param_2,undefined4 param_3,time_t param_4)`
- L5557: `void FUN_00412950(sem_t *param_1,int param_2,undefined4 param_3,time_t param_4)`
- L5566: `void FUN_00412960(__time_t *param_1)`
- L5575: `void FUN_00412970(int *param_1,int *param_2)`
- L5584: `void FUN_00412980(int param_1)`
- L5593: `void FUN_00412990(undefined4 param_1)`
- L5602: `void FUN_004129a0(int param_1,int param_2)`
- L5611: `void FUN_004129b0(size_t param_1,size_t param_2,size_t param_3,size_t param_4)`
- L5620: `void FUN_004129c0(int param_1)`
- L5629: `void FUN_004129d0(int param_1,undefined4 param_2,int param_3,undefined2 *param_4)`
- L5638: `void FUN_004129e0(int param_1,undefined4 param_2,int *param_3,time_t param_4)`
- L5647: `void FUN_004129f0(undefined4 param_1,undefined4 param_2,int param_3,time_t param_4)`
- L5656: `void FUN_00412a00(int param_1,undefined4 param_2,undefined4 param_3,time_t param_4)`
- L5665: `void FUN_00412a10(int *param_1,int param_2,char *param_3,time_t param_4)`
- L5674: `void FUN_00412a20(byte *param_1,char *param_2,undefined4 *param_3,time_t param_4)`
- L5683: `void FUN_00412a30(int *param_1,undefined4 param_2,undefined4 param_3,time_t param_4)`
- L5692: `void FUN_00412a40(int param_1)`
- L5701: `void FUN_00412a50(void)`
- L5710: `void FUN_00412a60(void)`
- L5719: `void FUN_00412a70(int param_1,undefined4 param_2,uint param_3,int param_4)`
- L5728: `void FUN_00412a80(void)`
- L5737: `void FUN_00412a90(int param_1,int *param_2,int *param_3,time_t param_4,int param_5,int *param_6)`
- L5746: `void FUN_00412aa0(int param_1,undefined4 param_2,undefined4 param_3,time_t param_4)`
- L5755: `void FUN_00412ab0(int param_1)`
