cmake_minimum_required(VERSION 3.10)
project(steamvr_bridge)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(steamvr_bridge
    src/bridge_impl.cpp
    src/pose_adapter.cpp
)

add_executable(bridge bridge.cpp)
target_link_libraries(bridge steamvr_bridge)
