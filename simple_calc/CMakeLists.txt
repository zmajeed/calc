# simple_calc/CMakeLists.txt

project(simple_calc_parser_src)

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

enable_testing()
