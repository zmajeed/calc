# calc3/lexer/CMakeLists.txt

project(calc3_lexer)

# tests

add_executable(calc3_lexer.gtest calc3_lexer.gtest.cpp)

target_link_libraries(calc3_lexer.gtest flexbisonlib.calc3 gmock_main)

include(GoogleTest)
gtest_discover_tests(calc3_lexer.gtest DISCOVERY_MODE PRE_TEST EXTRA_ARGS --gtest_color=yes)
