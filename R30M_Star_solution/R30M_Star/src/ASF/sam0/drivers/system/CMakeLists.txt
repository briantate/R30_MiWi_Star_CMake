# src/ASF/sam0/drivers/system
add_subdirectory(clock/clock_samr30)
add_subdirectory(interrupt)
add_subdirectory(pinmux)

target_sources( ${PROJECT_NAME}.elf
    PRIVATE
        system.c
)

target_include_directories( ${PROJECT_NAME}.elf
    PRIVATE
        clock
        interrupt
        pinmux
        power
        reset
)