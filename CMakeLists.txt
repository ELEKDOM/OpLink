cmake_minimum_required(VERSION 3.19)

# OpLink Project contents two parts 'frontend' and 'backend' each part is a PlugFrame based application
set(OL_PROJ_VERSION "1.0.0")
project(OpLink VERSION ${OL_PROJ_VERSION} LANGUAGES CXX)
message(STATUS "OL_PROJ_VERSION = " ${OL_PROJ_VERSION})

# OpLink Core Lib version
set(OL_LIB_VERSION_MAJOR "1")
string(CONCAT OL_LIB_VERSION ${OL_LIB_VERSION_MAJOR} ".0.0")
message(STATUS "OL_LIB_VERSION = " ${OL_LIB_VERSION})

# OpLink backend Core Lib version
set(OL_BACKEND_LIB_VERSION_MAJOR "1")
string(CONCAT OL_BACKEND_LIB_VERSION ${OL_BACKEND_LIB_VERSION_MAJOR} ".0.0")
message(STATUS "OL_BACKEND_LIB_VERSION = " ${OL_BACKEND_LIB_VERSION})

option(OL_BUILD_BACKEND  "Build OpLink backend (server)" ON)
option(OL_BUILD_FRONTEND "Build OpLink frontend (GUI client)"   ON)

if(NOT OL_BUILD_BACKEND AND NOT OL_BUILD_FRONTEND)
  message(FATAL_ERROR "Nothing to build: enable OL_BUILD_BACKEND and/or OL_BUILD_FRONTEND.")
endif()

# Map OpLink options to PlugFrame options (must be set BEFORE add_subdirectory)
if(OL_BUILD_BACKEND)
  set(PF_BUILD_TEXT ON CACHE BOOL "Build PlugFrame TEXT components" FORCE)
else()
  set(PF_BUILD_TEXT OFF CACHE BOOL "Build PlugFrame TEXT components" FORCE)
endif()

if(OL_BUILD_FRONTEND)
  set(PF_BUILD_GUI ON CACHE BOOL "Build PlugFrame GUI components" FORCE)
else()
  set(PF_BUILD_GUI OFF CACHE BOOL "Build PlugFrame GUI components" FORCE)
endif()

# Global build settings (OpLink scope)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Required Qt Modules
find_package(Qt6 REQUIRED COMPONENTS Core Xml Network SerialPort)

# Optional Qt Modules only for "frontend" part
if(OL_BUILD_FRONTEND)
  find_package(Qt6 REQUIRED COMPONENTS Gui Widgets)
endif()

qt_standard_project_setup()

# PlugFrame dependency
set(PF_ROOT_DIR
    "${CMAKE_CURRENT_LIST_DIR}/../PlugFrame"
    CACHE PATH "Path to PlugFrame repository root"
)

if(NOT EXISTS "${PF_ROOT_DIR}/CMakeLists.txt")
  message(FATAL_ERROR "PlugFrame not found at: ${PF_ROOT_DIR} (expected a CMakeLists.txt). "
                      "Set -DPF_ROOT_DIR=/path/to/PlugFrame")
endif()

# Build PlugFrame, without launchers, as part of OpLink, but keep its build tree isolated
set(PF_BUILD_LAUNCHERS OFF CACHE BOOL "Build PlugFrame launchers" FORCE)
add_subdirectory("${PF_ROOT_DIR}" "${CMAKE_BINARY_DIR}/_deps/PlugFrame")

# OpLink sources
add_subdirectory(oplink)

# Others File only for IDE
add_custom_target(OpLink_other_files
    SOURCES
        README.md
        LICENSE.txt
        cmake/oplink_runtime_install.cmake
)

# OpLink runtime install (CMake-only)
#####################################

# OpLink runtime root directory
set(OL_RUNTIME_ROOT "${CMAKE_BINARY_DIR}" CACHE PATH
    "OpLink runtime root directory")

# Profil Configuration
set(OL_PROFILES_ROOT_DIR "" CACHE PATH "External conf root")
set(OL_SELECTED_PROFILE_NAME "" CACHE STRING "Profile subdir")
message(STATUS "OL_PROFILES_ROOT_DIR = " ${OL_PROFILES_ROOT_DIR})
message(STATUS "OL_SELECTED_PROFILE_NAME = " ${OL_SELECTED_PROFILE_NAME})

set(_ol_install_args
  "-DOL_RUNTIME_ROOT=${OL_RUNTIME_ROOT}"
  "-DOL_PROFILES_ROOT_DIR=${OL_PROFILES_ROOT_DIR}"
  "-DOL_SELECTED_PROFILE_NAME=${OL_SELECTED_PROFILE_NAME}"

  # Forward build options to the script so it applies the same BACKEND/FRONTEND conditional logic
  "-DOL_BUILD_BACKEND=${OL_BUILD_BACKEND}"
  "-DOL_BUILD_FRONTEND=${OL_BUILD_FRONTEND}"

  # Mandatory PlugFrame's components
  "-DPF_CORE_LIB_FILE=$<TARGET_FILE:plugframe-core-qt6>"
  "-DPF_CORE_LIB_SONAME=$<$<PLATFORM_ID:Linux>:$<TARGET_SONAME_FILE:plugframe-core-qt6>>"
  "-DPF_CORE_LIB_LINKER=$<$<PLATFORM_ID:Linux>:$<TARGET_LINKER_FILE:plugframe-core-qt6>>"
  "-DPF_PLUGIN_FRAMEWORK_FILE=$<TARGET_FILE:framework-qt6>"
  "-DPF_PLUGIN_LOGGER_FILE=$<TARGET_FILE:logger-qt6>"

  # Core Lib For Backend and Frontend part
  "-DOL_CORE_LIB_FILE=$<TARGET_FILE:oplink-core-qt6>"
  "-DOL_CORE_LIB_SONAME=$<$<PLATFORM_ID:Linux>:$<TARGET_SONAME_FILE:oplink-core-qt6>>"
  "-DOL_CORE_LIB_LINKER=$<$<PLATFORM_ID:Linux>:$<TARGET_LINKER_FILE:oplink-core-qt6>>"
)

if(OL_BUILD_BACKEND)
  list(APPEND _ol_install_args
    # PlugFrame's components for Backend part
    "-DPF_PLUGIN_DISPLAY_FILE=$<TARGET_FILE:display-qt6>"
    "-DPF_PLUGIN_USERS_FILE=$<TARGET_FILE:users-qt6>"

    # OpLink's Backend part
    "-DOL_CORE_BACKEND_LIB_FILE=$<TARGET_FILE:oplink-core-backend-qt6>"
    "-DOL_CORE_BACKEND_LIB_SONAME=$<$<PLATFORM_ID:Linux>:$<TARGET_SONAME_FILE:oplink-core-backend-qt6>>"
    "-DOL_CORE_BACKEND_LIB_LINKER=$<$<PLATFORM_ID:Linux>:$<TARGET_LINKER_FILE:oplink-core-backend-qt6>>"
    "-DOL_BACKEND_PLUGIN_CONSOLE_FILE=$<TARGET_FILE:oplinkB-console-qt6>"
    "-DOL_BACKEND_PLUGIN_ENGINE_FILE=$<TARGET_FILE:oplinkB-engine-qt6>"
    "-DOL_BACKEND_PLUGIN_ENOCEANINFRASTRUCTURE_FILE=$<TARGET_FILE:oplinkB-enoceaninfrastructure-qt6>"
    "-DOL_BACKEND_PLUGIN_HEATINGMANAGERSET_FILE=$<TARGET_FILE:oplinkB-heatingmanagerset-qt6>"
    "-DOL_BACKEND_PLUGIN_OBSERVABLEMODELLOADER_FILE=$<TARGET_FILE:oplinkB-observablemodelloader-qt6>"
    "-DOL_BACKEND_PLUGIN_OBSERVABLEMODELREGISTER_FILE=$<TARGET_FILE:oplinkB-observablemodelregister-qt6>"
    "-DOL_BACKEND_PLUGIN_TCPBACKEND_FILE=$<TARGET_FILE:oplinkB-tcpbackend-qt6>"
  )
endif()

if(OL_BUILD_FRONTEND)
  list(APPEND _ol_install_args
    # PlugFrame's components for Frontend part
    "-DPF_GUI_LIB_FILE=$<TARGET_FILE:plugframe-gui-qt6>"
    "-DPF_GUI_LIB_SONAME=$<$<PLATFORM_ID:Linux>:$<TARGET_SONAME_FILE:plugframe-gui-qt6>>"
    "-DPF_GUI_LIB_LINKER=$<$<PLATFORM_ID:Linux>:$<TARGET_LINKER_FILE:plugframe-gui-qt6>>"
    "-DPF_PLUGIN_GUIDISPLAY_FILE=$<TARGET_FILE:guidisplay-qt6>"

    # "OpLink's Frontend part"
    "-DOL_FRONTEND_PLUGIN_GUICONSOLE_FILE=$<TARGET_FILE:oplinkF-guiconsole-qt6>"
    "-DOL_FRONTEND_PLUGIN_TCPFRONTEND_FILE=$<TARGET_FILE:oplinkF-tcpfrontend-qt6>"
  )
endif()

add_custom_target(oplink_runtime_install
  COMMAND ${CMAKE_COMMAND} ${_ol_install_args}
    -P "${PROJECT_SOURCE_DIR}/cmake/oplink_runtime_install.cmake"
  COMMENT "OpLink runtime install"
)

add_dependencies(oplink_runtime_install
  plugframe-core-qt6
  framework-qt6
  logger-qt6
  oplink-core-qt6
)

if(OL_BUILD_BACKEND)
  add_dependencies(oplink_runtime_install
    display-qt6
    oplink-core-backend-qt6
    users-qt6
    oplinkB-console-qt6
    oplinkB-engine-qt6
    oplinkB-enoceaninfrastructure-qt6
    oplinkB-heatingmanagerset-qt6
    oplinkB-observablemodelloader-qt6
    oplinkB-observablemodelregister-qt6
    oplinkB-tcpbackend-qt6
  )
endif()

if(OL_BUILD_FRONTEND)
  add_dependencies(oplink_runtime_install
    plugframe-gui-qt6
    guidisplay-qt6
    oplinkF-guiconsole-qt6
    oplinkF-tcpfrontend-qt6
  )
endif()

