# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\NewsGUI_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\NewsGUI_autogen.dir\\ParseCache.txt"
  "NewsGUI_autogen"
  )
endif()
