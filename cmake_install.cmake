# Install script for directory: C:/Users/Myers/git/world-of-kirbycraft

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/ZDoom")
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
  include("C:/Users/Myers/git/world-of-kirbycraft/zlib/cmake_install.cmake")
  include("C:/Users/Myers/git/world-of-kirbycraft/jpeg-6b/cmake_install.cmake")
  include("C:/Users/Myers/git/world-of-kirbycraft/bzip2/cmake_install.cmake")
  include("C:/Users/Myers/git/world-of-kirbycraft/game-music-emu/cmake_install.cmake")
  include("C:/Users/Myers/git/world-of-kirbycraft/lzma/cmake_install.cmake")
  include("C:/Users/Myers/git/world-of-kirbycraft/tools/cmake_install.cmake")
  include("C:/Users/Myers/git/world-of-kirbycraft/dumb/cmake_install.cmake")
  include("C:/Users/Myers/git/world-of-kirbycraft/gdtoa/cmake_install.cmake")
  include("C:/Users/Myers/git/world-of-kirbycraft/wadsrc/cmake_install.cmake")
  include("C:/Users/Myers/git/world-of-kirbycraft/src/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/Myers/git/world-of-kirbycraft/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
