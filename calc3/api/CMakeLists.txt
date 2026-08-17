# calc3/calc3_api/CMakeLists.txt

project(calc3_api)

# library

add_library(calc3_apilib INTERFACE calc3_api.h)

target_include_directories(calc3_apilib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(calc3_apilib INTERFACE flexbisonlib.calc3)


# tests

add_executable(calc3_api.gtest calc3_api.gtest.cpp)

target_link_libraries(calc3_api.gtest PRIVATE calc3_apilib gmock_main)

include(GoogleTest)
gtest_discover_tests(calc3_api.gtest DISCOVERY_MODE PRE_TEST EXTRA_ARGS --gtest_color=yes)

