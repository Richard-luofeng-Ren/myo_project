# Install script for directory: C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/build/cmake/lib

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/libs/base/cmake_install.cmake")
  include("C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/libs/net/cmake_install.cmake")
  include("C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/libs/core/cmake_install.cmake")
  include("C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/libs/adv/cmake_install.cmake")
  include("C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/libs/aui/cmake_install.cmake")
  include("C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/libs/html/cmake_install.cmake")
  include("C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/libs/propgrid/cmake_install.cmake")
  include("C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/libs/ribbon/cmake_install.cmake")
  include("C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/libs/richtext/cmake_install.cmake")
  include("C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/libs/webview/cmake_install.cmake")
  include("C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/libs/stc/cmake_install.cmake")
  include("C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/libs/xrc/cmake_install.cmake")
  include("C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/libs/media/cmake_install.cmake")
  include("C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/libs/gl/cmake_install.cmake")
  include("C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/libs/qa/cmake_install.cmake")
  include("C:/Users/Richard/Desktop/myoProject/myo-sdk-win-0.9.0/wxWidgets/install/libs/xml/cmake_install.cmake")

endif()

