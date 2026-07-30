# ast_calc/parser/CMakeLists.txt

project(ast_calc_parser_bison)

add_executable(astcalcparser ast_calc_parser.cpp)

target_compile_definitions(astcalcparser PRIVATE
  $<$<PLATFORM_ID:CYGWIN>: GTEST_HAS_PTHREAD=1 _POSIX_C_SOURCE=200809L _GNU_SOURCE>
)

target_compile_options(astcalcparser PRIVATE
  $<$<CXX_COMPILER_ID:GNU>: -Wall -Werror -Wextra -std=c++26 -pthread -fconcepts-diagnostics-depth=10>
  $<$<CXX_COMPILER_ID:MSVC>: -std:c++latest -W4 -WX>
  $<$<CXX_COMPILER_ID:Clang>: -Wall -Werror -Wextra -std=c++26 -pthread -Wno-unqualified-std-cast-call>
)
target_compile_options(astcalcparser PRIVATE
  $<$<AND:$<CONFIG:debug>,$<CXX_COMPILER_ID:GNU>>: -O0 -ggdb3>
  $<$<AND:$<CONFIG:release>,$<CXX_COMPILER_ID:GNU>>: -Og>
  $<$<AND:$<CONFIG:debug>,$<CXX_COMPILER_ID:MSVC>>: -Od -Zi>
  $<$<AND:$<CONFIG:debug>,$<CXX_COMPILER_ID:Clang>>: -O0 -ggdb3>
  $<$<AND:$<CONFIG:release>,$<CXX_COMPILER_ID:Clang>>: -Og>
)

target_link_libraries(astcalcparser flexbisonlib.astcalc)
target_link_libraries(astcalcparser
  $<$<CXX_COMPILER_ID:MSVC>: getoptlib>
)

# tests

add_executable(ast_calc_parser.gtest ast_calc_parser.gtest.cpp)

target_compile_definitions(ast_calc_parser.gtest PRIVATE $<$<PLATFORM_ID:CYGWIN>: GTEST_HAS_PTHREAD=1 _POSIX_C_SOURCE=200809L _GNU_SOURCE>)

target_compile_options(ast_calc_parser.gtest PRIVATE
  $<$<CXX_COMPILER_ID:GNU>: -Wall -Werror -Wextra -std=c++26 -pthread -fconcepts-diagnostics-depth=10>
  $<$<CXX_COMPILER_ID:MSVC>: -std:c++latest -W4 -WX>
  $<$<CXX_COMPILER_ID:Clang>: -Wall -Werror -Wextra -std=c++26 -pthread -Wno-unqualified-std-cast-call>
)
target_compile_options(ast_calc_parser.gtest PRIVATE
  $<$<AND:$<CONFIG:debug>,$<CXX_COMPILER_ID:GNU>>: -O0 -ggdb3>
  $<$<AND:$<CONFIG:release>,$<CXX_COMPILER_ID:GNU>>: -Og>
  $<$<AND:$<CONFIG:debug>,$<CXX_COMPILER_ID:MSVC>>: -Od -Zi>
  $<$<AND:$<CONFIG:debug>,$<CXX_COMPILER_ID:Clang>>: -O0 -ggdb3>
  $<$<AND:$<CONFIG:release>,$<CXX_COMPILER_ID:Clang>>: -Og>
)

target_link_libraries(ast_calc_parser.gtest flexbisonlib.astcalc gmock_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(ast_calc_parser.gtest DISCOVERY_MODE PRE_TEST EXTRA_ARGS --gtest_color=yes)

