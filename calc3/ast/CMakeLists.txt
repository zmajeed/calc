# calc3/ast/CMakeLists.txt

project(calc3_ast)

# library

add_library(calc3_astlib INTERFACE)
target_sources(calc3_astlib INTERFACE calc3_ast.h)

target_include_directories(calc3_astlib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(calc3_astlib INTERFACE
  $<$<CXX_COMPILER_ID:MSVC>: xyz_value_types>
  $<$<CXX_COMPILER_ID:Clang>: xyz_value_types>
)

# tests

add_executable(calc3_ast.gtest calc3_ast.gtest.cpp)

target_link_libraries(calc3_ast.gtest calc3_astlib gmock_main)

include(GoogleTest)
gtest_discover_tests(calc3_ast.gtest DISCOVERY_MODE PRE_TEST EXTRA_ARGS --gtest_color=yes)

