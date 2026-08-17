# calc3/parser/CMakeLists.txt

project(calc3_parser_bison)

# tests

add_executable(calc3_parser.gtest calc3_parser.gtest.cpp)

target_link_libraries(calc3_parser.gtest flexbisonlib.calc3 gmock_main)

include(GoogleTest)
gtest_discover_tests(calc3_parser.gtest DISCOVERY_MODE PRE_TEST EXTRA_ARGS --gtest_color=yes)
