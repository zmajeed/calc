# ast_calc/wasm/CMakeLists.txt

# webassembly cmakefile

cmake_minimum_required(VERSION 4.2)
project(ast_calc_wasm CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ast_calc_wasm ../src/parser_api/ast_calc_parse.cpp)

target_link_options(ast_calc_wasm PRIVATE
    "--bind"
    "-sMODULARIZE=1"
    "-sEXPORT_ES6=1"
    "-sENVIRONMENT=node,web"
    "-sFILESYSTEM=0"
    "-O3"
)

set_target_properties(ast_calc_wasm PROPERTIES SUFFIX ".mjs")
