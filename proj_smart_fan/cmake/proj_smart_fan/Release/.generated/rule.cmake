# The following functions contains all the flags passed to the different build stages.

set(PACK_REPO_PATH "C:/Users/mikol/.mchp_packs" CACHE PATH "Path to the root of a pack repository.")

function(proj_smart_fan_Release_Release_avr_gcc_assemble_rule target)
    set(options
        "-x"
        "assembler-with-cpp"
        "${MP_EXTRA_AS_PRE}"
        "-mmcu=atmega328pb"
        "-BC:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/ATmega_DFP/1.7.374/gcc/dev/atmega328pb"
        "-c"
        "-Wa,--defsym=__MPLAB_BUILD=1${MP_EXTRA_AS_POST}")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__ATmega328PB__"
        PRIVATE "Release=Release")
    target_include_directories(${target} PRIVATE "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/ATmega_DFP/1.7.374/include")
endfunction()
function(proj_smart_fan_Release_Release_avr_gcc_assembleWithPreprocess_rule target)
    set(options
        "-x"
        "assembler-with-cpp"
        "${MP_EXTRA_AS_PRE}"
        "-mmcu=atmega328pb"
        "-BC:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/ATmega_DFP/1.7.374/gcc/dev/atmega328pb"
        "-c"
        "-Wa,--defsym=__MPLAB_BUILD=1${MP_EXTRA_AS_POST}")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__ATmega328PB__"
        PRIVATE "Release=Release")
    target_include_directories(${target} PRIVATE "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/ATmega_DFP/1.7.374/include")
endfunction()
function(proj_smart_fan_Release_Release_avr_gcc_compile_rule target)
    set(options
        "-g"
        "-gdwarf-2"
        "${MP_EXTRA_CC_PRE}"
        "-mmcu=atmega328pb"
        "-BC:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/ATmega_DFP/1.7.374/gcc/dev/atmega328pb"
        "-x"
        "c"
        "-c"
        "-funsigned-char"
        "-funsigned-bitfields"
        "-Os"
        "-ffunction-sections"
        "-fdata-sections"
        "-fpack-struct"
        "-fshort-enums"
        "-Wall")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__ATmega328PB__"
        PRIVATE "NDEBUG"
        PRIVATE "Release=Release")
    target_include_directories(${target} PRIVATE "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/ATmega_DFP/1.7.374/include")
endfunction()
function(proj_smart_fan_Release_Release_avr_gcc_compile_cpp_rule target)
    set(options
        "-g"
        "-gdwarf-2"
        "${MP_EXTRA_CC_PRE}"
        "-mmcu=atmega328pb"
        "-BC:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/ATmega_DFP/1.7.374/gcc/dev/atmega328pb"
        "-x"
        "c++"
        "-c"
        "-O0"
        "-ffunction-sections"
        "-fdata-sections")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__ATmega328PB__"
        PRIVATE "Release=Release")
    target_include_directories(${target} PRIVATE "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/ATmega_DFP/1.7.374/include")
endfunction()
function(proj_smart_fan_Release_link_rule target)
    set(options
        "-gdwarf-2"
        "${MP_EXTRA_LD_PRE}"
        "-mmcu=atmega328pb"
        "-BC:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/ATmega_DFP/1.7.374/gcc/dev/atmega328pb"
        "-Wl,--defsym=__MPLAB_BUILD=1${MP_EXTRA_LD_POST}"
        "-Wl,--gc-sections")
    list(REMOVE_ITEM options "")
    target_link_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__ATmega328PB__"
        PRIVATE "Release=Release")
    target_link_libraries(${target} PRIVATE "m")
endfunction()
function(proj_smart_fan_Release_objcopy_ihex_rule target)
    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${OBJCOPY}
        ARGS --output-target=ihex ${proj_smart_fan_Release_image_name} ${proj_smart_fan_Release_image_base_name}.hex
        WORKING_DIRECTORY ${proj_smart_fan_Release_output_dir})
endfunction()
function(proj_smart_fan_Release_objcopy_eep_rule target)
    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${OBJCOPY}
        ARGS --only-section=.eeprom --change-section-lma .eeprom=0 --no-change-warnings --output-target=ihex ${proj_smart_fan_Release_image_name} ${proj_smart_fan_Release_image_base_name}.eep
        WORKING_DIRECTORY ${proj_smart_fan_Release_output_dir})
endfunction()
function(proj_smart_fan_Release_objcopy_lss_rule target)
    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${OBJDUMP}
        ARGS --disassemble --wide --demangle --line-numbers --section-headers --source ${proj_smart_fan_Release_image_name} > ${proj_smart_fan_Release_image_base_name}.lss
        WORKING_DIRECTORY ${proj_smart_fan_Release_output_dir})
endfunction()
function(proj_smart_fan_Release_objcopy_srec_rule target)
    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${OBJCOPY}
        ARGS --output-target=srec --remove-section=.eeprom --remove-section=.fuse --remove-section=.lock --remove-section=.signature ${proj_smart_fan_Release_image_name} ${proj_smart_fan_Release_image_base_name}.srec
        WORKING_DIRECTORY ${proj_smart_fan_Release_output_dir})
endfunction()
function(proj_smart_fan_Release_objcopy_sig_rule target)
    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${OBJCOPY}
        ARGS --only-section=.user_signatures --change-section-lma .user_signatures=0 --no-change-warnings --output-target=ihex ${proj_smart_fan_Release_image_name} ${proj_smart_fan_Release_image_base_name}.usersignatures
        WORKING_DIRECTORY ${proj_smart_fan_Release_output_dir})
endfunction()
