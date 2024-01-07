# R30_MiWi_Star_CMake
This is a port of a Microchip Studio ASF example project for the SAMR30M Xplained Pro board with capability to build with cmake under vscode. The project has also been simplified to the basic MiWi star functions used by the SAMR30M to make it easier to understand

# Hardware
* Targeted at the SAMR30M XPRO board from Microchip 
* Currently using the Atmel ICE programmer, but any CMSIS-DAP will work
    * You can change to other debugger type by modifying the openOCD setup in .vscode/tasks.json and .vscode/launch.json

# VSCode
* open this project from the R30M_Star directory so vscode can access the build/flash/debug tasks
    * ToDo: is there a way to make the top level directory find this as well?

## Debug plugin setup
* Currently using "cortex-debug" vscode extension from Marus
* launch.json
    * this is the main settings file for the debugger extension.
    * you can have multiple debug configurations. 
        * the "type" field specifies which debug extension you are using
    * To view peripheral registers, you must point cortex-debug to the ATSAMR30E18A.svd. I found this in the dfp for SAMR30 in the microchip packs archive
    * Note: you must compile with the "-g" option in order to generate debug symbols
* tasks.json
    * to run the "Flash" task, go to Terminal->Run Task... then select "Flash"
    * ToDo: how to write the user row on SAML21 with openocd to clear the BOOTPROT flags?

# Toolchain
* Currently installing gcc, cmake, ninja, and openocd onto my host machine and pointing vscode to the
* ToDo: In the future, I may use the vcpkg capabilities to bootstrap the embedded development environment
    * see: https://devblogs.microsoft.com/cppblog/vcpkg-artifacts/ 

## GCC
* Currently using v10.3.0

## CMAKE
* Currently using v3.25.1
* I inspected the compiler and linker settings from the .cproj Atmel studio file and tried to mimic these in the top level CMakeLists.txt file
* ToDo: how to move all the necessary includes/targets into the CMakeLists.txt for the ASF directory?
    * this way the project level CMakeLists.txt doesn't have to know about all the include paths

## NINJA
* currently v1.10.1

## OPENOCD
* Currently using v0.11.0
* a custom samr30m board file was created as there is not one available in the openocd scripts (as of openOCD 0.11.0)
    * this board file specifies using a cmsis-dap
    * I initially tried to use a SAM-ICE but wasn't able to figure out how to make it use SWD protocol. It defaulted to JTAG and wouldn't allow me to override it


