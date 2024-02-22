cmake_minimum_required(VERSION 3.10)
project(Demo)

#  指定 C++ 标准版本
set(CMAKE_CXX_STANDARD 17)

# 一般无需设置，windows下需要添加bat后缀
# 设置编译器为emcc（Emscripten）
# set(CMAKE_CXX_COMPILER em++.bat)

# 重定向输出目录
set(BIN_OUTPUT_DIR ${PROJECT_SOURCE_DIR}/build/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR} CACHE STRING "cmake var" FORCE)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BIN_OUTPUT_DIR} CACHE STRING "cmake var" FORCE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_OUTPUT_DIR} CACHE STRING "cmake var" FORCE)

set(WASM_DIR ${PROJECT_SOURCE_DIR}/wasm)

SET(JS_PARAM "\
 --pre-js ${WASM_DIR}/pre.js")

SET(INIT_MEM_SIZE 16MB)
SET(MAX_MEM_SIZE 4096MB)

# 设置内存参数
# MALLOC 使用emmalloc作为内存分配器
# INITIAL_MEMORY 初始内存大小
# ALLOW_MEMORY_GROWTH 允许内存增长
SET(MEM_LINK_CONF "\
 -s MALLOC=emmalloc\
 -s INITIAL_MEMORY=${INIT_MEM_SIZE} \
 -s ALLOW_MEMORY_GROWTH=1 \
 -s MEMORY_GROWTH_GEOMETRIC_STEP=1 \
 -s MEMORY_GROWTH_GEOMETRIC_CAP=64MB \
 -s TOTAL_STACK=8MB \
 -s MAXIMUM_MEMORY=${MAX_MEM_SIZE} ")

# 指定编译参数
# MODULARIZE 模块化
# EXPORT_NAME 指定导出的函数名
set(CMAKE_EXE_LINKER_FLAGS
    "${JS_PARAM} \
    -std=c++17 \
    -lembind \
    -s MODULARIZE=1 \
    -s WASM=1 \
    -s EXPORT_NAME=\"ModuleInit\"")

include_directories(${CMAKE_SOURCE_DIR}/include)

# 文件查找
FILE(GLOB SRC ${CMAKE_SOURCE_DIR}/src/*.cpp)

# 添加可执行文件
add_executable(Module ${SRC})
