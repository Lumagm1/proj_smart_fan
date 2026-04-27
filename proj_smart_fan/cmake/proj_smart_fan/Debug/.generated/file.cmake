# The following variables contains the files used by the different stages of the build process.
set(proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_assemble)
set_source_files_properties(${proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_assemble} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_assemble})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_assembleWithPreprocess)
set_source_files_properties(${proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_assembleWithPreprocess} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_assembleWithPreprocess})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_compile
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../adc.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../i2c.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../lcd.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../main.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../uart_dbug.c")
set_source_files_properties(${proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_compile} PROPERTIES LANGUAGE C)
set(proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_compile_cpp)
set_source_files_properties(${proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_compile_cpp} PROPERTIES LANGUAGE CXX)
set(proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_link)
set(proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_objcopy_ihex)
set(proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_objcopy_eep)
set(proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_objcopy_lss)
set(proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_objcopy_srec)
set(proj_smart_fan_Debug_Debug_avr_gcc_FILE_TYPE_objcopy_sig)
set(proj_smart_fan_Debug_image_name "Debug.elf")
set(proj_smart_fan_Debug_image_base_name "Debug")

# The output directory of the final image.
set(proj_smart_fan_Debug_output_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../out/proj_smart_fan")

# The full path to the final image.
set(proj_smart_fan_Debug_full_path_to_image ${proj_smart_fan_Debug_output_dir}/${proj_smart_fan_Debug_image_name})

# Potential output file extensions
set(output_extensions
    .hex
    .lss
    .eep
    .srec
    .usersignatures)
list(TRANSFORM output_extensions PREPEND "${proj_smart_fan_Debug_output_dir}/${proj_smart_fan_Debug_image_base_name}")
