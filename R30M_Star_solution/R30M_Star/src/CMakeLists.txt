cmake_minimum_required(VERSION 3.19)

set(PROJECT_NAME R30M_Star_Proj)
set(PROJECT_BINARY_DIR "build")

set(MCPU cortex-m0plus)

# Project name is independent of the target name
# Semantic version number updated here 
project(    ${PROJECT_NAME}
            VERSION 0.1.0
            LANGUAGES C
)

# Modify the paths below for DFP and CMSIS include
# Pack updates appear in home_directory and original files appear in MPLAB X install directory
set(microchip_dfp_path "ASF/sam0/utils/cmsis/samr30" )
set(cmsis_include_path "ASF/thirdparty/CMSIS/Include" )


# does the startup file need to be here?
set(SOURCES
    main.c
    demo_output.c
    star_demo.c 
    task.c
    ASF/sam0/utils/cmsis/samr30/source/gcc/startup_samr30.c
)

# compile definitions that need to be accessable project wide
add_compile_definitions(
  DEBUG
  RTC_COUNT_ASYNC=true
  ARM_MATH_CM0PLUS=true
  PDS_ENABLE_WEAR_LEVELING
  SYSTICK_MODE
  __SAMR30E18A__
  SAL_TYPE=AT86RF2xx
  TC_ASYNC=true
  EXTINT_CALLBACK_MODE=true
  BOARD=SAMR30_MODULE_XPLAINED_PRO
  USART_CALLBACK_MODE=true
  SPI_CALLBACK_MODE=false
  PHY_AT86RF212B
  ENABLE_NETWORK_FREEZER
  PROTOCOL_STAR
)

add_compile_options(-mcpu=${MCPU} -mthumb)
# optimizations
add_compile_options(-fdata-sections -ffunction-sections -mlong-calls)
# warnings
add_compile_options(-Wall)
# miscellaneous
add_compile_options(-pipe -fno-strict-aliasing -Wall -Wstrict-prototypes -Wmissing-prototypes -Werror-implicit-function-declaration -Wpointer-arith -std=gnu99 -ffunction-sections -fdata-sections -Wchar-subscripts -Wcomment -Wformat=2 -Wimplicit-int -Wmain -Wparentheses -Wsequence-point -Wreturn-type -Wswitch -Wtrigraphs -Wunused -Wuninitialized -Wunknown-pragmas -Wfloat-equal -Wundef -Wshadow -Wbad-function-cast -Wwrite-strings -Wsign-compare -Waggregate-return  -Wmissing-declarations -Wformat -Wmissing-format-attribute -Wno-deprecated-declarations -Wpacked -Wredundant-decls -Wnested-externs -Wlong-long -Wunreachable-code -Wcast-align --param max-inline-insns-single=500)
#debug symbol creation
add_compile_options(-g)


# List of .c files
add_executable( ${PROJECT_NAME}.elf
                ${SOURCES}
                # ${LINKER_SCRIPT}
)

add_subdirectory(ASF/common)
add_subdirectory(ASF/common2/services/delay/sam0)
add_subdirectory(ASF/sam0)
add_subdirectory(ASF/thirdparty)

# Include directories - need at least DFP and CMSIS directories
target_include_directories( ${PROJECT_NAME}.elf 
                            PUBLIC
                              . 
                              config
                              ASF
                              ASF/sam0/boards
                              ASF/sam0/utils
                              ASF/sam0/utils/cmsis/samr30/include
                              ASF/sam0/utils/cmsis/samr30/source
                              ASF/sam0/utils/header_files
                              ASF/sam0/utils/preprocessor
                              ASF/sam0/utils/stdio/stdio_serial
                              ASF/sam0/drivers/extint
                              ASF/sam0/drivers/nvm
                              ASF/sam0/drivers/port
                              ASF/sam0/drivers/rtc
                              ASF/sam0/drivers/sercom
                              ASF/sam0/drivers/sercom/spi
                              ASF/sam0/drivers/sercom/usart
                              ASF/sam0/drivers/system
                              ASF/sam0/drivers/system/pinmux
                              ASF/sam0/drivers/system/reset
                              ASF/sam0/drivers/system/reset/reset_sam_l
                              ASF/sam0/drivers/system/interrupt
                              ASF/sam0/drivers/system/interrupt/system_interrupt_samr30
                              ASF/sam0/drivers/system/power
                              ASF/sam0/drivers/system/power/power_sam_l
                              ASF/sam0/drivers/system/clock
                              ASF/sam0/drivers/system/clock/clock_samr30
                              ASF/sam0/drivers/tc
                              ASF/common/boards
                              ASF/common/utils
                              ASF/common/services/serial
                              ASF/common2/services/delay
                              ASF/common2/services/delay/sam0
                              ASF/thirdparty/wireless/addons/sio2host/uart
                              ASF/thirdparty/wireless/miwi/include
                              ASF/thirdparty/wireless/miwi/source/miwi_p2p_star
                              ASF/thirdparty/wireless/miwi/source/sys
                              ASF/thirdparty/wireless/miwi/source/mimac
                              ASF/thirdparty/wireless/miwi/source/mimac/phy
                              ASF/thirdparty/wireless/miwi/services/pds/inc
                              ASF/thirdparty/wireless/miwi/services/pds/inc/nv
                              ASF/thirdparty/wireless/miwi/services/pds/inc/nv/External
                              ASF/thirdparty/wireless/miwi/services/pds/inc/wl
                              ASF/thirdparty/wireless/miwi/services/sleep_mgr
                              ASF/thirdparty/wireless/addons/sio2host/uart
                              ASF/thirdparty/wireless/services/nvm
                              ASF/thirdparty/wireless/services/common_hw_timer
                              ASF/thirdparty/wireless/services/common_hw_timer/sam0
                              ASF/thirdparty/wireless/services/sal/inc
                              ASF/thirdparty/wireless/services/trx_access
                              ASF/thirdparty/CMSIS/Include
                              ASF/thirdparty/CMSIS/Lib/GCC
)

set(LINKER_SCRIPT ../src/ASF/thirdparty/wireless/miwi/services/pds/src/wl/linkerscripts/samr30/gcc/samr30e18a_flash.ld)

target_link_options( ${PROJECT_NAME}.elf
                      PUBLIC "-mthumb"
                      PUBLIC "-Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map"
                      # General
                      # PUBLIC "--specs==nano.specs -Wl"
                      # Optimization
                      PUBLIC "-Wl,--gc-sections"
                      PUBLIC "-mcpu=cortex-m0plus"
                      # Miscellaneous
                      PUBLIC "-Wl,--entry=Reset_Handler"
                      PUBLIC "-Wl,--cref"
                      PUBLIC "-mthumb"
                      PUBLIC "-T${LINKER_SCRIPT}"
)


# # General
# add_link_options(--specs==nano.specs,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
# # Optimization
# add_link_options(-Wl,-gc-sections)
# # Miscellaneous
# add_link_options(-mcpu=${MCPU} -mthumb -mthumb-interwork)
# add_link_options(-T ${LINKER_SCRIPT})

target_link_directories(${PROJECT_NAME}.elf
                        PRIVATE
                         ASF/thirdparty/CMSIS/Lib/GCC 
                         ASF/thirdparty/wireless/services/common_hw_timer/sam0/lib
)

target_link_libraries( ${PROJECT_NAME}.elf
                        PUBLIC
                          sam0_lib_hw_timer
                          arm_cortexM0l_math
                          m
)

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")

# Debug statements
# include(CMakePrintHelpers)
# cmake_print_variables(LINKER_SCRIPT)
#cmake_print_properties( TARGETS HelloWorld.elf PROPERTIES COMPILE_OPTIONS INCLUDE_DIRECTORIES COMPILE_DEFINITIONS SOURCES LINK_OPTIONS)
#cmake_print_variables( home_directory microchip_dfp_path cmsis_include_path)
