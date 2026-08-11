# calc3/calc3_api/CMakeLists.txt

project(calc3_api)

# library

add_library(calc3_apilib INTERFACE calc3_api.h)

target_compile_definitions(calc3_apilib INTERFACE $<$<PLATFORM_ID:CYGWIN>: GTEST_HAS_PTHREAD=1 _POSIX_C_SOURCE=200809L _GNU_SOURCE>)

target_compile_options(calc3_apilib INTERFACE
  $<$<CXX_COMPILER_ID:GNU>: -std=c++26 -Wall -Werror -Wextra -pthread -fconcepts-diagnostics-depth=10>
  $<$<CXX_COMPILER_ID:MSVC>: -std:c++latest -W4 -WX>
  $<$<CXX_COMPILER_ID:Clang>: -Wall -Werror -Wextra -std=c++26 -pthread -Wno-unqualified-std-cast-call>
)
target_compile_options(calc3_apilib INTERFACE
  $<$<AND:$<CONFIG:debug>,$<CXX_COMPILER_ID:GNU>>: -O0 -ggdb3>
  $<$<AND:$<CONFIG:release>,$<CXX_COMPILER_ID:GNU>>: -Og>
  $<$<AND:$<CONFIG:debug>,$<CXX_COMPILER_ID:MSVC>>: -Od -Zi>
  $<$<AND:$<CONFIG:debug>,$<CXX_COMPILER_ID:Clang>>: -O0 -ggdb3>
  $<$<AND:$<CONFIG:release>,$<CXX_COMPILER_ID:Clang>>: -Og>
)

target_include_directories(calc3_apilib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(calc3_apilib INTERFACE flexbisonlib.calc3)


# tests

add_executable(calc3_api.gtest calc3_api.gtest.cpp)

target_compile_definitions(calc3_api.gtest PRIVATE $<$<PLATFORM_ID:CYGWIN>: GTEST_HAS_PTHREAD=1 _POSIX_C_SOURCE=200809L _GNU_SOURCE>)

target_compile_options(calc3_api.gtest PRIVATE
  $<$<CXX_COMPILER_ID:GNU>: -Wall -Werror -Wextra -std=c++26 -pthread -fconcepts-diagnostics-depth=10>
  $<$<CXX_COMPILER_ID:MSVC>: -std:c++latest -W4 -WX>
  $<$<CXX_COMPILER_ID:Clang>: -Wall -Werror -Wextra -std=c++26 -pthread -Wno-unqualified-std-cast-call>
)
target_compile_options(calc3_api.gtest PRIVATE
  $<$<AND:$<CONFIG:debug>,$<CXX_COMPILER_ID:GNU>>: -O0 -ggdb3>
  $<$<AND:$<CONFIG:release>,$<CXX_COMPILER_ID:GNU>>: -Og>
  $<$<AND:$<CONFIG:debug>,$<CXX_COMPILER_ID:MSVC>>: -Od -Zi>
  $<$<AND:$<CONFIG:debug>,$<CXX_COMPILER_ID:Clang>>: -O0 -ggdb3>
  $<$<AND:$<CONFIG:release>,$<CXX_COMPILER_ID:Clang>>: -Og>
)

target_link_libraries(calc3_api.gtest PRIVATE calc3_apilib gmock_main)

include(GoogleTest)
gtest_discover_tests(calc3_api.gtest DISCOVERY_MODE PRE_TEST EXTRA_ARGS --gtest_color=yes)

