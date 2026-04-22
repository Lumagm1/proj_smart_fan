# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "C:\\Users\\Adam\\Documents\\Atmel Studio\\7.0\\proj_smart_fan\\out\\proj_smart_fan\\Debug.eep"
  "C:\\Users\\Adam\\Documents\\Atmel Studio\\7.0\\proj_smart_fan\\out\\proj_smart_fan\\Debug.hex"
  "C:\\Users\\Adam\\Documents\\Atmel Studio\\7.0\\proj_smart_fan\\out\\proj_smart_fan\\Debug.lss"
  "C:\\Users\\Adam\\Documents\\Atmel Studio\\7.0\\proj_smart_fan\\out\\proj_smart_fan\\Debug.srec"
  "C:\\Users\\Adam\\Documents\\Atmel Studio\\7.0\\proj_smart_fan\\out\\proj_smart_fan\\Debug.usersignatures"
  )
endif()
