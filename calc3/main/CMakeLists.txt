# calc3/main/CMakeLists.txt

project(calc3_main)

add_executable(calc3 calc3.cpp)

target_compile_definitions(calc3 PRIVATE
  $<$<PLATFORM_ID:CYGWIN>: GTEST_HAS_PTHREAD=1 _POSIX_C_SOURCE=200809L _GNU_SOURCE>
)

target_compile_options(calc3 PRIVATE
  $<$<CXX_COMPILER_ID:GNU>: -Wall -Werror -Wextra -std=c++26 -pthread -fconcepts-diagnostics-depth=10>
  $<$<CXX_COMPILER_ID:MSVC>: -std:c++latest -W4 -WX>
  $<$<CXX_COMPILER_ID:Clang>: -Wall -Werror -Wextra -std=c++26 -pthread -Wno-unqualified-std-cast-call>
)
target_compile_options(calc3 PRIVATE
  $<$<AND:$<CONFIG:debug>,$<CXX_COMPILER_ID:GNU>>: -O0 -ggdb3>
  $<$<AND:$<CONFIG:release>,$<CXX_COMPILER_ID:GNU>>: -Og>
  $<$<AND:$<CONFIG:debug>,$<CXX_COMPILER_ID:MSVC>>: -Od -Zi>
  $<$<AND:$<CONFIG:debug>,$<CXX_COMPILER_ID:Clang>>: -O0 -ggdb3>
  $<$<AND:$<CONFIG:release>,$<CXX_COMPILER_ID:Clang>>: -Og>
)

target_link_libraries(calc3 PRIVATE flexbisonlib.calc3 isocline)
target_link_libraries(calc3 PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>: getoptlib>
)

# tests

include(calc3.ctest.cmake)
