# Install script for directory: C:/Users/SenorMonopoly/Projects/OpenGL/Code/Gensys/Gensys1.0/Dependencies/assimp-master

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Assimp")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libassimp5.4.1-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-5.4" TYPE FILE FILES
    "C:/Users/SenorMonopoly/Projects/OpenGL/Code/Gensys/Gensys1.0/Dependencies/assimp-master/build/generated/assimpConfig.cmake"
    "C:/Users/SenorMonopoly/Projects/OpenGL/Code/Gensys/Gensys1.0/Dependencies/assimp-master/build/generated/assimpConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libassimp5.4.1-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-5.4/assimpTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-5.4/assimpTargets.cmake"
         "C:/Users/SenorMonopoly/Projects/OpenGL/Code/Gensys/Gensys1.0/Dependencies/assimp-master/build/CMakeFiles/Export/48d9c4119e0f845c087d34dc4fbb1ef2/assimpTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-5.4/assimpTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-5.4/assimpTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-5.4" TYPE FILE FILES "C:/Users/SenorMonopoly/Projects/OpenGL/Code/Gensys/Gensys1.0/Dependencies/assimp-master/build/CMakeFiles/Export/48d9c4119e0f845c087d34dc4fbb1ef2/assimpTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-5.4" TYPE FILE FILES "C:/Users/SenorMonopoly/Projects/OpenGL/Code/Gensys/Gensys1.0/Dependencies/assimp-master/build/CMakeFiles/Export/48d9c4119e0f845c087d34dc4fbb1ef2/assimpTargets-debug.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-5.4" TYPE FILE FILES "C:/Users/SenorMonopoly/Projects/OpenGL/Code/Gensys/Gensys1.0/Dependencies/assimp-master/build/CMakeFiles/Export/48d9c4119e0f845c087d34dc4fbb1ef2/assimpTargets-minsizerel.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-5.4" TYPE FILE FILES "C:/Users/SenorMonopoly/Projects/OpenGL/Code/Gensys/Gensys1.0/Dependencies/assimp-master/build/CMakeFiles/Export/48d9c4119e0f845c087d34dc4fbb1ef2/assimpTargets-relwithdebinfo.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-5.4" TYPE FILE FILES "C:/Users/SenorMonopoly/Projects/OpenGL/Code/Gensys/Gensys1.0/Dependencies/assimp-master/build/CMakeFiles/Export/48d9c4119e0f845c087d34dc4fbb1ef2/assimpTargets-release.cmake")
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/SenorMonopoly/Projects/OpenGL/Code/Gensys/Gensys1.0/Dependencies/assimp-master/build/contrib/zlib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/SenorMonopoly/Projects/OpenGL/Code/Gensys/Gensys1.0/Dependencies/assimp-master/build/code/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/SenorMonopoly/Projects/OpenGL/Code/Gensys/Gensys1.0/Dependencies/assimp-master/build/test/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libassimp5.4.1-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/SenorMonopoly/Projects/OpenGL/Code/Gensys/Gensys1.0/Dependencies/assimp-master/build/assimp.pc")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/SenorMonopoly/Projects/OpenGL/Code/Gensys/Gensys1.0/Dependencies/assimp-master/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
