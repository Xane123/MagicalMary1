# Install script for directory: D:/Git/Failure5

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/GZDoom")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("D:/Git/Failure5/zlib/cmake_install.cmake")
  include("D:/Git/Failure5/jpeg-6b/cmake_install.cmake")
  include("D:/Git/Failure5/bzip2/cmake_install.cmake")
  include("D:/Git/Failure5/game-music-emu/cmake_install.cmake")
  include("D:/Git/Failure5/lzma/cmake_install.cmake")
  include("D:/Git/Failure5/tools/cmake_install.cmake")
  include("D:/Git/Failure5/dumb/cmake_install.cmake")
  include("D:/Git/Failure5/gdtoa/cmake_install.cmake")
  include("D:/Git/Failure5/wadsrc/cmake_install.cmake")
  include("D:/Git/Failure5/wadsrc_bm/cmake_install.cmake")
  include("D:/Git/Failure5/wadsrc_lights/cmake_install.cmake")
  include("D:/Git/Failure5/src/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "D:/Git/Failure5/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
