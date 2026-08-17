# calc3/main/CMakeLists.txt

project(calc3_main)

add_executable(calc3 calc3.cpp)

target_link_libraries(calc3 PRIVATE flexbisonlib.calc3 isocline)
target_link_libraries(calc3 PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>: getoptlib>
)

# tests

include(calc3.ctest.cmake)
