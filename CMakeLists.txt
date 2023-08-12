cmake_minimum_required(VERSION 3.12)
project(HelloWorld)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# 设置SystemC库的路径
set(SYSTEMC_HOME "/home/ts/software/systemc-2.3.3")
set(SystemC_INCLUDE_DIRS "${SYSTEMC_HOME}/include")
set(SystemC_LIBRARY_DIRS "${SYSTEMC_HOME}/lib-linux64")
set(SystemC_LIBRARIES "-lsystemc")

message(STATUS "${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# # 添加可执行文件
# add_executable(demo main.cpp)


# # 设置编译器选项和库路径
# target_include_directories(demo PRIVATE ${SystemC_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include)
# target_link_directories(demo PRIVATE ${SystemC_LIBRARY_DIRS})
# target_link_libraries(demo PRIVATE ${SystemC_LIBRARIES})

add_executable(fir src/main.cpp src/tb.cpp src/fir.cpp)
target_include_directories(fir PRIVATE ${SystemC_INCLUDE_DIRS})
target_link_directories(fir PRIVATE ${SystemC_LIBRARY_DIRS})
target_link_libraries(fir PRIVATE ${SystemC_LIBRARIES})