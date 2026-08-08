# calc1/flexbison.gen/CMakeLists.txt

project(calc1_flexbison_gen)

add_library(flexbisonlib.calc1 STATIC calc1_lexer.flex.cpp calc1_parser.bison.cpp)

target_compile_definitions(flexbisonlib.calc1 PRIVATE $<$<PLATFORM_ID:CYGWIN>: GTEST_HAS_PTHREAD=1 _POSIX_C_SOURCE=200809L _GNU_SOURCE>)

target_compile_options(flexbisonlib.calc1 PRIVATE
  $<$<CXX_COMPILER_ID:GNU>: -std=c++26 -Wall -Werror -Wextra -pthread -fconcepts-diagnostics-depth=10>
  $<$<CXX_COMPILER_ID:MSVC>: -std:c++latest -W4 -WX>
  $<$<STREQUAL:${CMAKE_SYSTEM_NAME},Emscripten>: -std=c++26 -Wall -Werror -Wextra -pthread -Wno-unqualified-std-cast-call>
)
target_compile_options(flexbisonlib.calc1 PRIVATE
  $<$<AND:$<CONFIG:debug>,$<CXX_COMPILER_ID:GNU>>: -O0 -ggdb3>
  $<$<AND:$<CONFIG:release>,$<CXX_COMPILER_ID:GNU>>: -Og>
  $<$<AND:$<CONFIG:debug>,$<CXX_COMPILER_ID:MSVC>>: -Od -Zi>
  $<$<AND:$<CONFIG:debug>,$<STREQUAL:${CMAKE_SYSTEM_NAME},Emscripten>>: -O0 -ggdb3>
)

target_include_directories(flexbisonlib.calc1 PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/calc1
  $<$<CXX_COMPILER_ID:MSVC>: ${CMAKE_SOURCE_DIR}/thirdparty/flex>
  $<$<STREQUAL:${CMAKE_SYSTEM_NAME},Emscripten>: ${CMAKE_SOURCE_DIR}/thirdparty/flex>
)

