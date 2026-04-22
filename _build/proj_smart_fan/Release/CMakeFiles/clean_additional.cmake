# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "C:\\Users\\Adam\\Documents\\Atmel Studio\\7.0\\proj_smart_fan\\out\\proj_smart_fan\\Release.eep"
  "C:\\Users\\Adam\\Documents\\Atmel Studio\\7.0\\proj_smart_fan\\out\\proj_smart_fan\\Release.hex"
  "C:\\Users\\Adam\\Documents\\Atmel Studio\\7.0\\proj_smart_fan\\out\\proj_smart_fan\\Release.lss"
  "C:\\Users\\Adam\\Documents\\Atmel Studio\\7.0\\proj_smart_fan\\out\\proj_smart_fan\\Release.srec"
  "C:\\Users\\Adam\\Documents\\Atmel Studio\\7.0\\proj_smart_fan\\out\\proj_smart_fan\\Release.usersignatures"
  )
endif()
