# Install script for directory: C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/wxWidgets")
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

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  message(STATUS "Installing: Headers...")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/include/wx")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/include/msvc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/vc_x64_dll" TYPE DIRECTORY FILES "C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/lib/vc_x64_dll/mswud")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/vc_x64_dll" TYPE DIRECTORY FILES "C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/lib/vc_x64_dll/mswu")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/wxWidgets/vc_x64_dll/wxWidgetsTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/wxWidgets/vc_x64_dll/wxWidgetsTargets.cmake"
         "C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/CMakeFiles/Export/8e36a1dcfc6739ee8dcb85c2821b53a4/wxWidgetsTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/wxWidgets/vc_x64_dll/wxWidgetsTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/wxWidgets/vc_x64_dll/wxWidgetsTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/wxWidgets/vc_x64_dll" TYPE FILE FILES "C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/CMakeFiles/Export/8e36a1dcfc6739ee8dcb85c2821b53a4/wxWidgetsTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/wxWidgets/vc_x64_dll" TYPE FILE FILES "C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/CMakeFiles/Export/8e36a1dcfc6739ee8dcb85c2821b53a4/wxWidgetsTargets-debug.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/wxWidgets/vc_x64_dll" TYPE FILE FILES "C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/CMakeFiles/Export/8e36a1dcfc6739ee8dcb85c2821b53a4/wxWidgetsTargets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/wxWidgets" TYPE FILE FILES
    "C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/lib/wxWidgetsConfig.cmake"
    "C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/lib/wxWidgetsConfigVersion.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/libs/cmake_install.cmake")
  include("C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/utils/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
