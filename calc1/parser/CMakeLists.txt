# calc1/parser/CMakeLists.txt

project(calc1_parser_bison)

# tests

add_executable(calc1_parser.gtest calc1_parser.gtest.cpp)

target_link_libraries(calc1_parser.gtest flexbisonlib.calc1 gmock_main)

include(GoogleTest)
gtest_discover_tests(calc1_parser.gtest DISCOVERY_MODE PRE_TEST EXTRA_ARGS --gtest_color=yes)
