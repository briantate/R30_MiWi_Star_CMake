# R30_MiWi_Star_CMake
This is a port of an ASF example project with capability to build with cmake. The project has also been simplified to the basic MiWi star functions used by the SAMR30M xplained pro to make it easier to understand

# VSCode
* open this project from the R30M_Star directory so vscode can access the build/flash/debug tasks
    * is there a way to make the top level directory find this as well?

# Toolchain
* possibly use the vcpkg capabilities to bootstrap the embedded development environment?
    * see: https://devblogs.microsoft.com/cppblog/vcpkg-artifacts/ 
    * gcc, cmake, and ninja

# CMAKE
* how to move all the necessary includes/targets into the CMakeLists.txt for the ASF directory?
    * this way the project level CMakeLists.txt doesn't have to know about all the include paths

# OPENOCD
* a custom samr30m board file was created as there is not one available in the openocd scripts
    * this board file specifies using a cmsis-dap
    * I initially tried to use a SAM-ICE but wasn't able to figure out how to make it use SWD protocol. It defaulted to JTAG

# Debug plugin setup
* currently using the Embedded tools plugin from ms-vscode
* tasks.json
    * to run the "Flash" task, go to Terminal->Run Task... then select "Flash"
    * how to write the user row on SAML21 with openocd to clear the BOOTPROT flags?
* launch.json
    * This depends on the ATSAMR30E18A.svd file being in the .vscode directory. I found this in the dfp for SAMR30 in the microchip packs archive