# calc1/main/CMakeLists.txt

project(calc1_main)

add_executable(calc1 calc1.cpp)

target_link_libraries(calc1 flexbisonlib.calc1)
target_link_libraries(calc1 $<$<CXX_COMPILER_ID:MSVC>: getoptlib>)

# tests

include(calc1.ctest.cmake)
