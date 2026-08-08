# calc1/lexer/CMakeLists.txt

project(calc1_lexer)

# tests

add_executable(calc1_lexer.gtest calc1_lexer.gtest.cpp)

target_compile_definitions(calc1_lexer.gtest PRIVATE $<$<PLATFORM_ID:CYGWIN>: GTEST_HAS_PTHREAD=1 _POSIX_C_SOURCE=200809L _GNU_SOURCE>)

target_compile_options(calc1_lexer.gtest PRIVATE
  $<$<CXX_COMPILER_ID:GNU>: -Wall -Werror -Wextra -std=c++26 -pthread -fconcepts-diagnostics-depth=10>
  $<$<CXX_COMPILER_ID:MSVC>: -std:c++latest -W4 -WX>
  $<$<CXX_COMPILER_ID:Clang>: -Wall -Werror -Wextra -std=c++26 -pthread -Wno-unqualified-std-cast-call>
)
target_compile_options(calc1_lexer.gtest PRIVATE
  $<$<AND:$<CONFIG:debug>,$<CXX_COMPILER_ID:GNU>>: -O0 -ggdb3>
  $<$<AND:$<CONFIG:release>,$<CXX_COMPILER_ID:GNU>>: -Og>
  $<$<AND:$<CONFIG:debug>,$<CXX_COMPILER_ID:MSVC>>: -Od -Zi>
  $<$<AND:$<CONFIG:debug>,$<CXX_COMPILER_ID:Clang>>: -O0 -ggdb3>
  $<$<AND:$<CONFIG:release>,$<CXX_COMPILER_ID:Clang>>: -Og>
)

target_link_libraries(calc1_lexer.gtest flexbisonlib.calc1 gmock_main)

include(GoogleTest)
gtest_discover_tests(calc1_lexer.gtest DISCOVERY_MODE PRE_TEST EXTRA_ARGS --gtest_color=yes)
