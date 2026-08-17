# calc2/parser/CMakeLists.txt

project(calc2_parser_bison)

# tests

add_executable(calc2_parser.gtest calc2_parser.gtest.cpp)

target_link_libraries(calc2_parser.gtest flexbisonlib.calc2 gmock_main)

include(GoogleTest)
gtest_discover_tests(calc2_parser.gtest DISCOVERY_MODE PRE_TEST EXTRA_ARGS --gtest_color=yes)
