# calc3/flexbison.gen/CMakeLists.txt

project(calc3_flexbison_gen)

add_library(flexbisonlib.calc3 STATIC calc3_lexer.flex.cpp calc3_parser.bison.cpp)

target_include_directories(flexbisonlib.calc3 PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/calc3
  $<$<CXX_COMPILER_ID:MSVC>: ${CMAKE_SOURCE_DIR}/thirdparty/flex>
  $<$<STREQUAL:${CMAKE_SYSTEM_NAME},Emscripten>: ${CMAKE_SOURCE_DIR}/thirdparty/flex>
)

target_link_libraries(flexbisonlib.calc3 PUBLIC calc3_astlib)
