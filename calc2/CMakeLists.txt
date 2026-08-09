# calc2/CMakeLists.txt

project(calc2_top)

# don't run bison, flex for windows and webassembly builds
if(WIN32 OR EMSCRIPTEN)
  message("Use checked-in pre-generated calc2 bison, flex files from flexbison.gen directory")
  add_subdirectory(flexbison.gen)
else()
  message("Generate calc2 bison, flex files from grammar directory")
  add_subdirectory(grammar)
endif()

add_subdirectory(parser)
add_subdirectory(lexer)
add_subdirectory(api)
add_subdirectory(main)

