cmake_minimum_required(VERSION 3.16)
project(iot_industrial_app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(iot_core
    src/app.cpp
    src/logger.cpp
    src/config_store.cpp
    src/legacy_bootstrap.cpp
    src/parameter_collector.cpp
    src/modules/serial_module.cpp
    src/modules/mqtt_module.cpp
    src/modules/modbus_module.cpp
    src/modules/web_module.cpp
    src/modules/network_module.cpp
    src/modules/power_module.cpp
)

target_include_directories(iot_core PUBLIC include)

add_executable(iot_app src/main.cpp)
target_link_libraries(iot_app PRIVATE iot_core)
