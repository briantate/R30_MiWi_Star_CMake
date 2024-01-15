# R30_MiWi_Star_CMake
This is a port of a Microchip Studio ASF example project for the SAMR30M Xplained Pro board with capability to build with cmake under vscode. The project has also been simplified to the basic MiWi star functions used by the SAMR30M to make it easier to understand

# Hardware
* Targeted at the SAMR30M XPRO board from Microchip
* Currently using the Atmel ICE programmer, but any CMSIS-DAP will work
    * You can change to other debugger type by modifying the openOCD setup in .vscode/tasks.json and .vscode/launch.json

# Development Environment setup

## VSCode installation:
- Visual Studio Code
  - https://code.visualstudio.com/
  - Extensions to install:
    - "C/C++ Extension Pack" Extension from Microsoft
    - "cortex-debug" Extension from marus25

### Extension setup
* Install "C/C++ Extension Pack" Extension from Microsoft
    * This should also include "CMake" and "CMake Tools" extensions. If not, install them manually as well
* Install "cortex-debug" extension from marus25
    * launch.json
        * this is the main settings file for the debugger extension.
        * you can have multiple debug configurations.
            * the "type" field specifies which debug extension you are using
        * To view peripheral registers, you must point cortex-debug to the ATSAMR30E18A.svd. I found this in the dfp for SAMR30 in the microchip packs archive
        * Note: you must compile with the "-g" option in order to generate debug symbols

## Toolchain Installation:
* gcc, cmake, ninja, and openocd are needed to build and debug this project
    * Option 1: install them on your machine and add them the PATH
    * Option 2: bootstrap the environment using vcpkg

### Option 1: Manually install the toolchain on your PC and add them to the PATH
- CMake v3.19 or newer
  - https://cmake.org/install/
- Ninja v1.11.1 or newer
  - https://ninja-build.org/
  - Windows:
    - extract this into C:\Users\%username%\.local\bin
    - may need to create this directory and add it to your path
- OpenOCD v0.11.0 or newer
    - download from one of the mirrors indicated here https://openocd.org/pages/getting-openocd.html
    - Windows:
        - extract this into C:\Users\%username%\.local\bin
        - may need to create this directory and add it to your path
- GCC v10.3.0 or newer
    - download and install the latest arm-non-eabi from https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads
        - Windows:
            - extract this into C:\Users\%username%\.local\bin
            - may need to create this directory and add it to your path


### Option 2: vcpkg-artifacts
* vcpkg-artifacts Setup: use the vcpkg to bootstrap the embedded development environment with the needed artifacts
    * see: https://devblogs.microsoft.com/cppblog/vcpkg-artifacts/
    * Open a shell (in windows you must have admin priveledges)
    * Setting up vcpkg for the first time:
        * acquire vcpkg:
            * Linux/Mac: . <(curl https://aka.ms/vcpkg-init.sh -L)
            * Windows cmd: curl -LO https://aka.ms/vcpkg-init.cmd && .\vcpkg-init.cmd
    * Subsequent instances of a terminal can be quickly bootstrapped using the following commands:
        * Linux/Mac: > . ~/.vcpkg/vcpkg-init.sh
        * Windows cmd: > vcpkg-init.cmd
    * activate vcpkg:
        * vcpkg activate
            * This activates gcc, cmake, ninja, and openocd according to the vcpkg-configuration.json file in this project

# Opening the Project in VSCode
* In vscode, open this project from the R30M_Star folder to build/flash/debug either project
    * ToDo: is there a way to make the top level directory find this as well?
    * ToDo: how to pull the project name into something that can be read by the openocd config files as well as the cmake build tasks

# Building the project:
* Make sure you have a clean cmake setup, open the vscode pallet and run "CMake: Delete Cache and Reconfigure"
* Select the "gcc" kit from the project's "cmake" directory
* Build either by running "CMake: Build" from the command pallet, or by clicking the "Build" button at the bottom left of vscode

# Programming the device into the MCU Flash:
* Terminal->Run Task... then select "Flash"
        * NOTE: IF THE BOOTLOADER PROTECTION FUSE IS ON, YOU MAY GET THE ERROR "Error: SAMD: NVM lock error"
            * This seems to go away on the second programming attempt. It may be an issue with the openocd "bootloader" command

# Debugging the application:
* Make sure your cmsis-dap adapter is connected to your PC and the SAMR30 debugging connector
* Click on the "Run and Debug" icon on the left hand side of vscode to open the debugging window
* In the dropdown, select "Debug Launch (OpenOCD)"
    * There is also a configuration to attach to a running target called "Debug Attach (OpenOCD)"
* Click the "Play" button to start debugging (or use F5 key)
    * the "launch.json" file in the ".vscode" directory tells the cortex-debug extension how to launch the appropriate tools for debugging
    * it also points to the "ATSAMR30E18A.svd" file which has the debugging symbols for the peripheral registers. This allows you to peek at those registers through the debugging window

# ASF usage information for SAMR30:
* https://asf.microchip.com/docs/latest/search.html?device=samr30

# CMake Project setup: how I turned an Atmel Studio project into a CMake buildable project

## Cmake changes/updates
* I inspected the compiler and linker settings from the .cproj Atmel studio file and tried to mimic these in the top level CMakeLists.txt file
* ToDo: how to move all the necessary includes/targets into the CMakeLists.txt for the ASF directory?
    * this way the project level CMakeLists.txt doesn't have to know about all the include paths

## OPENOCD
* a custom samr30m board file was created as there is not one available in the openocd scripts (as of openOCD 0.11.0)
    * this board file specifies using a cmsis-dap
    * I initially tried to use a SAM-ICE but wasn't able to figure out how to make it use SWD protocol. It defaulted to JTAG and wouldn't allow me to override it