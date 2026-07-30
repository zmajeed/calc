# ast_calc/flexbison.gen/CMakeLists.txt

project(ast_calc_flexbison_gen)

add_library(flexbisonlib.astcalc STATIC ast_calc_lexer.flex.cpp ast_calc_parser.bison.cpp)

target_compile_definitions(flexbisonlib.astcalc PRIVATE $<$<PLATFORM_ID:CYGWIN>: GTEST_HAS_PTHREAD=1 _POSIX_C_SOURCE=200809L _GNU_SOURCE>)

target_compile_options(flexbisonlib.astcalc PRIVATE
  $<$<CXX_COMPILER_ID:GNU>: -std=c++26 -Wall -Werror -Wextra -pthread -fconcepts-diagnostics-depth=10>
  $<$<CXX_COMPILER_ID:MSVC>: -std:c++latest -W4 -WX>
  $<$<STREQUAL:${CMAKE_SYSTEM_NAME},Emscripten>: -std=c++26 -Wall -Werror -Wextra -pthread -Wno-unqualified-std-cast-call>
)
target_compile_options(flexbisonlib.astcalc PRIVATE
  $<$<AND:$<CONFIG:debug>,$<CXX_COMPILER_ID:GNU>>: -O0 -ggdb3>
  $<$<AND:$<CONFIG:release>,$<CXX_COMPILER_ID:GNU>>: -Og>
  $<$<AND:$<CONFIG:debug>,$<CXX_COMPILER_ID:MSVC>>: -Od -Zi>
  $<$<AND:$<CONFIG:debug>,$<STREQUAL:${CMAKE_SYSTEM_NAME},Emscripten>>: -O0 -ggdb3>
)

target_include_directories(flexbisonlib.astcalc PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/ast_calc
  $<$<CXX_COMPILER_ID:MSVC>: ${CMAKE_SOURCE_DIR}/thirdparty/flex>
  $<$<STREQUAL:${CMAKE_SYSTEM_NAME},Emscripten>: ${CMAKE_SOURCE_DIR}/thirdparty/flex>
)

target_link_libraries(flexbisonlib.astcalc ast_calc_astlib)

enable_testing()
