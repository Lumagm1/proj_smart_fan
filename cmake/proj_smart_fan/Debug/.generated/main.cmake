include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(proj_smart_fan_Debug_library_list )

# Handle files with suffix s, for group Debug-avr-gcc
if(proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_assemble)
add_library(proj_smart_fan_Debug_Debug_avr_gcc_assemble OBJECT ${proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_assemble})
    proj_smart_fan_Debug_Debug_avr_gcc_assemble_rule(proj_smart_fan_Debug_Debug_avr_gcc_assemble)
    list(APPEND proj_smart_fan_Debug_library_list "$<TARGET_OBJECTS:proj_smart_fan_Debug_Debug_avr_gcc_assemble>")

endif()

# Handle files with suffix S, for group Debug-avr-gcc
if(proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_assembleWithPreprocess)
add_library(proj_smart_fan_Debug_Debug_avr_gcc_assembleWithPreprocess OBJECT ${proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_assembleWithPreprocess})
    proj_smart_fan_Debug_Debug_avr_gcc_assembleWithPreprocess_rule(proj_smart_fan_Debug_Debug_avr_gcc_assembleWithPreprocess)
    list(APPEND proj_smart_fan_Debug_library_list "$<TARGET_OBJECTS:proj_smart_fan_Debug_Debug_avr_gcc_assembleWithPreprocess>")

endif()

# Handle files with suffix [cC], for group Debug-avr-gcc
if(proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_compile)
add_library(proj_smart_fan_Debug_Debug_avr_gcc_compile OBJECT ${proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_compile})
    proj_smart_fan_Debug_Debug_avr_gcc_compile_rule(proj_smart_fan_Debug_Debug_avr_gcc_compile)
    list(APPEND proj_smart_fan_Debug_library_list "$<TARGET_OBJECTS:proj_smart_fan_Debug_Debug_avr_gcc_compile>")

endif()

# Handle files with suffix cpp, for group Debug-avr-gcc
if(proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_compile_cpp)
add_library(proj_smart_fan_Debug_Debug_avr_gcc_compile_cpp OBJECT ${proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_compile_cpp})
    proj_smart_fan_Debug_Debug_avr_gcc_compile_cpp_rule(proj_smart_fan_Debug_Debug_avr_gcc_compile_cpp)
    list(APPEND proj_smart_fan_Debug_library_list "$<TARGET_OBJECTS:proj_smart_fan_Debug_Debug_avr_gcc_compile_cpp>")

endif()

# Handle files with suffix elf, for group Debug-avr-gcc
if(proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_objcopy_ihex)
add_library(proj_smart_fan_Debug_Debug_avr_gcc_objcopy_ihex OBJECT ${proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_objcopy_ihex})
    proj_smart_fan_Debug_Debug_avr_gcc_objcopy_ihex_rule(proj_smart_fan_Debug_Debug_avr_gcc_objcopy_ihex)
    list(APPEND proj_smart_fan_Debug_library_list "$<TARGET_OBJECTS:proj_smart_fan_Debug_Debug_avr_gcc_objcopy_ihex>")

endif()

# Handle files with suffix elf, for group Debug-avr-gcc
if(proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_objcopy_eep)
add_library(proj_smart_fan_Debug_Debug_avr_gcc_objcopy_eep OBJECT ${proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_objcopy_eep})
    proj_smart_fan_Debug_Debug_avr_gcc_objcopy_eep_rule(proj_smart_fan_Debug_Debug_avr_gcc_objcopy_eep)
    list(APPEND proj_smart_fan_Debug_library_list "$<TARGET_OBJECTS:proj_smart_fan_Debug_Debug_avr_gcc_objcopy_eep>")

endif()

# Handle files with suffix elf, for group Debug-avr-gcc
if(proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_objcopy_lss)
add_library(proj_smart_fan_Debug_Debug_avr_gcc_objcopy_lss OBJECT ${proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_objcopy_lss})
    proj_smart_fan_Debug_Debug_avr_gcc_objcopy_lss_rule(proj_smart_fan_Debug_Debug_avr_gcc_objcopy_lss)
    list(APPEND proj_smart_fan_Debug_library_list "$<TARGET_OBJECTS:proj_smart_fan_Debug_Debug_avr_gcc_objcopy_lss>")

endif()

# Handle files with suffix elf, for group Debug-avr-gcc
if(proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_objcopy_srec)
add_library(proj_smart_fan_Debug_Debug_avr_gcc_objcopy_srec OBJECT ${proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_objcopy_srec})
    proj_smart_fan_Debug_Debug_avr_gcc_objcopy_srec_rule(proj_smart_fan_Debug_Debug_avr_gcc_objcopy_srec)
    list(APPEND proj_smart_fan_Debug_library_list "$<TARGET_OBJECTS:proj_smart_fan_Debug_Debug_avr_gcc_objcopy_srec>")

endif()

# Handle files with suffix elf, for group Debug-avr-gcc
if(proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_objcopy_sig)
add_library(proj_smart_fan_Debug_Debug_avr_gcc_objcopy_sig OBJECT ${proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_objcopy_sig})
    proj_smart_fan_Debug_Debug_avr_gcc_objcopy_sig_rule(proj_smart_fan_Debug_Debug_avr_gcc_objcopy_sig)
    list(APPEND proj_smart_fan_Debug_library_list "$<TARGET_OBJECTS:proj_smart_fan_Debug_Debug_avr_gcc_objcopy_sig>")

endif()


# Main target for this project
add_executable(proj_smart_fan_Debug_image_epnbb79Y ${proj_smart_fan_Debug_library_list})

set_target_properties(proj_smart_fan_Debug_image_epnbb79Y PROPERTIES
    OUTPUT_NAME "Debug"
    SUFFIX ".elf"
    ADDITIONAL_CLEAN_FILES "${output_extensions}"
    RUNTIME_OUTPUT_DIRECTORY "${proj_smart_fan_Debug_output_dir}")
target_link_libraries(proj_smart_fan_Debug_image_epnbb79Y PRIVATE ${proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_link})

#Add objcopy steps
proj_smart_fan_Debug_objcopy_ihex_rule(proj_smart_fan_Debug_image_epnbb79Y)
proj_smart_fan_Debug_objcopy_eep_rule(proj_smart_fan_Debug_image_epnbb79Y)
proj_smart_fan_Debug_objcopy_lss_rule(proj_smart_fan_Debug_image_epnbb79Y)
proj_smart_fan_Debug_objcopy_srec_rule(proj_smart_fan_Debug_image_epnbb79Y)
proj_smart_fan_Debug_objcopy_sig_rule(proj_smart_fan_Debug_image_epnbb79Y)
# Add the link options from the rule file.
proj_smart_fan_Debug_link_rule( proj_smart_fan_Debug_image_epnbb79Y)


