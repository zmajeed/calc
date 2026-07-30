# ast_calc/CMakeLists.txt

project(ast_calc_parser_src)

if(WIN32 OR CMAKE_CXX_COMPILER_ID STREQUAL Clang)
# reference implementation of c++26 indirect, polymorphic for vc++, clang
# library name is xyz_value_types

  FetchContent_Declare(
    value_types
    GIT_REPOSITORY https://github.com/jbcoe/value_types
    GIT_TAG main
    GIT_SHALLOW TRUE
  )
  FetchContent_MakeAvailable(value_types)
endif()

# don't run bison, flex for windows and webassembly builds
if(WIN32 OR EMSCRIPTEN)
  message("Use checked-in generated bison, flex files from flexbison.gen")
  add_subdirectory(flexbison.gen)
else()
  message("Generate bison, flex files from src/grammar")
  add_subdirectory(grammar)
endif()

add_subdirectory(parser)
add_subdirectory(lexer)

add_subdirectory(ast)

enable_testing()
