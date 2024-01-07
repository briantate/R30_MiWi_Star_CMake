# src/ASF/sam0
add_subdirectory(boards/samr30_module_xplained_pro)
add_subdirectory(drivers)
add_subdirectory(utils)

target_include_directories( ${PROJECT_NAME}.elf 
    PRIVATE
        drivers
        utils
)