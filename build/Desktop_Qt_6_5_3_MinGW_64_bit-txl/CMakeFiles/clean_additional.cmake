# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\ContactSystem_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ContactSystem_autogen.dir\\ParseCache.txt"
  "ContactSystem_autogen"
  )
endif()
