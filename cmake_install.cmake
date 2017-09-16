# Install script for directory: C:/Users/Myers/Documents/GitHub/MaryMagicalAdventure

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/GZDoom")
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

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Documentation" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/docs" TYPE DIRECTORY FILES "C:/Users/Myers/Documents/GitHub/MaryMagicalAdventure/docs/")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/Myers/Documents/GitHub/MaryMagicalAdventure/zlib/cmake_install.cmake")
  include("C:/Users/Myers/Documents/GitHub/MaryMagicalAdventure/jpeg-6b/cmake_install.cmake")
  include("C:/Users/Myers/Documents/GitHub/MaryMagicalAdventure/bzip2/cmake_install.cmake")
  include("C:/Users/Myers/Documents/GitHub/MaryMagicalAdventure/game-music-emu/cmake_install.cmake")
  include("C:/Users/Myers/Documents/GitHub/MaryMagicalAdventure/lzma/cmake_install.cmake")
  include("C:/Users/Myers/Documents/GitHub/MaryMagicalAdventure/tools/cmake_install.cmake")
  include("C:/Users/Myers/Documents/GitHub/MaryMagicalAdventure/dumb/cmake_install.cmake")
  include("C:/Users/Myers/Documents/GitHub/MaryMagicalAdventure/gdtoa/cmake_install.cmake")
  include("C:/Users/Myers/Documents/GitHub/MaryMagicalAdventure/wadsrc/cmake_install.cmake")
  include("C:/Users/Myers/Documents/GitHub/MaryMagicalAdventure/wadsrc_bm/cmake_install.cmake")
  include("C:/Users/Myers/Documents/GitHub/MaryMagicalAdventure/wadsrc_lights/cmake_install.cmake")
  include("C:/Users/Myers/Documents/GitHub/MaryMagicalAdventure/wadsrc_extra/cmake_install.cmake")
  include("C:/Users/Myers/Documents/GitHub/MaryMagicalAdventure/src/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/Myers/Documents/GitHub/MaryMagicalAdventure/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
