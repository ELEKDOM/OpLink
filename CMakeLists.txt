cmake_minimum_required(VERSION 3.19)

# OpLink Project contents two parts 'frontend' and 'backend' each part is a PlugFrame based application
set(OL_PROJ_VERSION "1.0.0")
project(OpLink VERSION ${OL_PROJ_VERSION} LANGUAGES CXX)
message(STATUS "OL_PROJ_VERSION = " ${OL_PROJ_VERSION})

# Disable RPATH generation to avoid embedding build-time or host-specific paths
# into binaries. Runtime library resolution is handled explicitly (LD_LIBRARY_PATH),
# ensuring predictable and portable execution across environments.
set(CMAKE_SKIP_RPATH TRUE)

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
