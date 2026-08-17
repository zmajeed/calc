# calc2/lexer/CMakeLists.txt

project(calc2_lexer)

# tests

add_executable(calc2_lexer.gtest calc2_lexer.gtest.cpp)

target_link_libraries(calc2_lexer.gtest flexbisonlib.calc2 gmock_main)

include(GoogleTest)
gtest_discover_tests(calc2_lexer.gtest DISCOVERY_MODE PRE_TEST EXTRA_ARGS --gtest_color=yes)
