# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles/SudoStrap_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/SudoStrap_autogen.dir/ParseCache.txt"
  "SudoStrap_autogen"
  )
endif()
