# src/ASF
add_subdirectory(thirdparty)
add_subdirectory(sam0)
add_subdirectory(common)
add_subdirectory(common2/services/delay)

target_include_directories( ${PROJECT_NAME}.elf 
    PRIVATE
        sam0
)