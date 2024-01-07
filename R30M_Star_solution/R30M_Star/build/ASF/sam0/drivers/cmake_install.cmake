# Install script for directory: /home/bmmhbt/Projects/R30_MiWi_Star_CMake/R30M_Star_solution/R30M_Star/src/ASF/sam0/drivers

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/arm-none-eabi-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/bmmhbt/Projects/R30_MiWi_Star_CMake/R30M_Star_solution/R30M_Star/build/ASF/sam0/drivers/extint/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/bmmhbt/Projects/R30_MiWi_Star_CMake/R30M_Star_solution/R30M_Star/build/ASF/sam0/drivers/nvm/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/bmmhbt/Projects/R30_MiWi_Star_CMake/R30M_Star_solution/R30M_Star/build/ASF/sam0/drivers/port/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/bmmhbt/Projects/R30_MiWi_Star_CMake/R30M_Star_solution/R30M_Star/build/ASF/sam0/drivers/rtc/rtc_sam_l_c/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/bmmhbt/Projects/R30_MiWi_Star_CMake/R30M_Star_solution/R30M_Star/build/ASF/sam0/drivers/sercom/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/bmmhbt/Projects/R30_MiWi_Star_CMake/R30M_Star_solution/R30M_Star/build/ASF/sam0/drivers/system/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/bmmhbt/Projects/R30_MiWi_Star_CMake/R30M_Star_solution/R30M_Star/build/ASF/sam0/drivers/tc/cmake_install.cmake")
endif()
