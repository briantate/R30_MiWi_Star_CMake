# R30_MiWi_Star_CMake
This is a port of an ASF example project with capability to build with cmake under vscode. The project has also been simplified to the basic MiWi star functions used by the SAMR30M xplained pro to make it easier to understand

# VSCode
* open this project from the R30M_Star directory so vscode can access the build/flash/debug tasks
    * is there a way to make the top level directory find this as well?

# Toolchain
* Currently installing gcc, cmake, and ninja onto my host machine and pointing vscode to the
* In the future, I may use the vcpkg capabilities to bootstrap the embedded development environment
    * see: https://devblogs.microsoft.com/cppblog/vcpkg-artifacts/ 

# GCC
* Currently using v10.3.0

# CMAKE
* I inspected the compiler and linker settings from the .cproj Atmel studio file and tried to mimic these in the top level CMakeLists.txt file
* how to move all the necessary includes/targets into the CMakeLists.txt for the ASF directory?
    * this way the project level CMakeLists.txt doesn't have to know about all the include paths

# NINJA
* currently v1.10.1

# OPENOCD
* Currently using v0.11.0
* a custom samr30m board file was created as there is not one available in the openocd scripts (as of openOCD 0.11.0)
    * this board file specifies using a cmsis-dap
    * I initially tried to use a SAM-ICE but wasn't able to figure out how to make it use SWD protocol. It defaulted to JTAG and wouldn't allow me to override it

# Debug plugin setup
* Currently using "cortex-debug" vscode extension from Marus
* launch.json
    * this is the main settings file for the debugger extension.
    * you can have multiple debug configurations. 
        * the "type" field specifies which debug extension you are using
    * To view peripheral registers, you must point cortex-debug to the ATSAMR30E18A.svd. I found this in the dfp for SAMR30 in the microchip packs archive
    * Note: you must compile with the "-g" option in order to generate debug symbols
* tasks.json
    * to run the "Flash" task, go to Terminal->Run Task... then select "Flash"
    * how to write the user row on SAML21 with openocd to clear the BOOTPROT flags?
