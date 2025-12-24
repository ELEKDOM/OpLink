# cmake/olink_runtime_install.cmake

message(STATUS "OL_RUNTIME_ROOT  = ${OL_RUNTIME_ROOT}")
message(STATUS "OL_PROFILES_ROOT_DIR = ${OL_PROFILES_ROOT_DIR}")
message(STATUS "OL_SELECTED_PROFILE_NAME = ${OL_SELECTED_PROFILE_NAME}")
message(STATUS "PF_CORE_LIB_FILE = ${PF_CORE_LIB_FILE}")
message(STATUS "PF_CORE_LIB_SONAME = ${PF_CORE_LIB_SONAME}")
message(STATUS "PF_CORE_LIB_LINKER = ${PF_CORE_LIB_LINKER}")
message(STATUS "OL_CORE_LIB_FILE = ${OL_CORE_LIB_FILE}")
message(STATUS "OL_CORE_LIB_SONAME = ${OL_CORE_LIB_SONAME}")
message(STATUS "OL_CORE_LIB_LINKER = ${OL_CORE_LIB_LINKER}")
message(STATUS "OL_CORE_BACKEND_LIB_FILE = ${OL_CORE_BACKEND_LIB_FILE}")
message(STATUS "OL_CORE_BACKEND_LIB_SONAME = ${OL_CORE_BACKEND_LIB_SONAME}")
message(STATUS "OL_CORE_LIB_LINKER = ${OL_CORE_BACKEND_LIB_LINKER}")
message(STATUS "PF_PLUGIN_FRAMEWORK_FILE = ${PF_PLUGIN_FRAMEWORK_FILE}")
message(STATUS "PF_PLUGIN_LOGGER_FILE = ${PF_PLUGIN_LOGGER_FILE}")
message(STATUS "PF_PLUGIN_USERS_FILE = ${PF_PLUGIN_USERS_FILE}")
message(STATUS "PF_PLUGIN_DISPLAY_FILE = ${PF_PLUGIN_DISPLAY_FILE}")
message(STATUS "PF_PLUGIN_GUIDISPLAY_FILE = ${PF_PLUGIN_GUIDISPLAY_FILE}")
message(STATUS "OL_BACKEND_PLUGIN_CONSOLE_FILE = ${OL_BACKEND_PLUGIN_CONSOLE_FILE}")
message(STATUS "OL_BACKEND_PLUGIN_ENGINE_FILE = ${OL_BACKEND_PLUGIN_ENGINE_FILE}")
message(STATUS "OL_BACKEND_PLUGIN_ENOCEANINFRASTRUCTURE_FILE = ${OL_BACKEND_PLUGIN_ENOCEANINFRASTRUCTURE_FILE}")
message(STATUS "OL_BACKEND_PLUGIN_HEATINGMANAGERSET_FILE = ${OL_BACKEND_PLUGIN_HEATINGMANAGERSET_FILE}")
message(STATUS "OL_BACKEND_PLUGIN_OBSERVABLEMODELLOADER_FILE = ${OL_BACKEND_PLUGIN_OBSERVABLEMODELLOADER_FILE}")
message(STATUS "OL_BACKEND_PLUGIN_OBSERVABLEMODELREGISTER_FILE = ${OL_BACKEND_PLUGIN_OBSERVABLEMODELREGISTER_FILE}")
message(STATUS "OL_BACKEND_PLUGIN_TCPBACKEND_FILE = ${OL_BACKEND_PLUGIN_TCPBACKEND_FILE}")
message(STATUS "OL_FRONTEND_PLUGIN_GUICONSOLE_FILE = ${OL_FRONTEND_PLUGIN_GUICONSOLE_FILE}")
message(STATUS "OL_FRONTEND_PLUGIN_TCPFRONTEND_FILE = ${OL_FRONTEND_PLUGIN_TCPFRONTEND_FILE}")

if(NOT DEFINED OL_RUNTIME_ROOT OR OL_RUNTIME_ROOT STREQUAL "")
  message(FATAL_ERROR "OL_RUNTIME_ROOT is not set")
endif()
if(NOT DEFINED OL_PROFILES_ROOT_DIR OR OL_PROFILES_ROOT_DIR STREQUAL "")
  message(FATAL_ERROR "OL_PROFILES_ROOT_DIR is not set")
endif()
if(NOT DEFINED OL_SELECTED_PROFILE_NAME OR OL_SELECTED_PROFILE_NAME STREQUAL "")
  message(FATAL_ERROR "OL_RUNTIME_ROOT is not set")
endif()
if(NOT DEFINED PF_CORE_LIB_FILE OR PF_CORE_LIB_FILE STREQUAL "")
  message(FATAL_ERROR "PF_CORE_LIB_FILE is not set")
endif()
if(NOT DEFINED OL_CORE_LIB_FILE OR OL_CORE_LIB_FILE STREQUAL "")
  message(FATAL_ERROR "OL_CORE_LIB_FILE is not set")
endif()
if(NOT DEFINED OL_CORE_BACKEND_LIB_FILE OR OL_CORE_BACKEND_LIB_FILE STREQUAL "")
  message(FATAL_ERROR "OL_CORE_BACKEND_LIB_FILE is not set")
endif()
if(NOT DEFINED PF_PLUGIN_FRAMEWORK_FILE OR PF_PLUGIN_FRAMEWORK_FILE STREQUAL "")
  message(FATAL_ERROR "PF_PLUGIN_FRAMEWORK_FILE is not set")
endif()
if(NOT DEFINED PF_PLUGIN_LOGGER_FILE OR PF_PLUGIN_LOGGER_FILE STREQUAL "")
  message(FATAL_ERROR "PF_PLUGIN_LOGGER_FILE is not set")
endif()
if(NOT DEFINED PF_PLUGIN_USERS_FILE OR PF_PLUGIN_USERS_FILE STREQUAL "")
  message(FATAL_ERROR "PF_PLUGIN_USERS_FILE is not set")
endif()
if(NOT DEFINED PF_PLUGIN_DISPLAY_FILE OR PF_PLUGIN_DISPLAY_FILE STREQUAL "")
  message(FATAL_ERROR "PF_PLUGIN_DISPLAY_FILE is not set")
endif()
if(NOT DEFINED PF_PLUGIN_GUIDISPLAY_FILE OR PF_PLUGIN_GUIDISPLAY_FILE STREQUAL "")
  message(FATAL_ERROR "PF_PLUGIN_GUIDISPLAY_FILE is not set")
endif()
if(NOT DEFINED OL_BACKEND_PLUGIN_CONSOLE_FILE OR OL_BACKEND_PLUGIN_CONSOLE_FILE STREQUAL "")
  message(FATAL_ERROR "OL_BACKEND_PLUGIN_CONSOLE_FILE is not set")
endif()
if(NOT DEFINED OL_BACKEND_PLUGIN_ENGINE_FILE OR OL_BACKEND_PLUGIN_ENGINE_FILE STREQUAL "")
  message(FATAL_ERROR "OL_BACKEND_PLUGIN_ENGINE_FILE is not set")
endif()
if(NOT DEFINED OL_BACKEND_PLUGIN_ENOCEANINFRASTRUCTURE_FILE OR OL_BACKEND_PLUGIN_ENOCEANINFRASTRUCTURE_FILE STREQUAL "")
  message(FATAL_ERROR "OL_BACKEND_PLUGIN_ENOCEANINFRASTRUCTURE_FILE is not set")
endif()
if(NOT DEFINED OL_BACKEND_PLUGIN_HEATINGMANAGERSET_FILE OR OL_BACKEND_PLUGIN_HEATINGMANAGERSET_FILE STREQUAL "")
  message(FATAL_ERROR "OL_BACKEND_PLUGIN_HEATINGMANAGERSET_FILE is not set")
endif()
if(NOT DEFINED OL_BACKEND_PLUGIN_OBSERVABLEMODELLOADER_FILE OR OL_BACKEND_PLUGIN_OBSERVABLEMODELLOADER_FILE STREQUAL "")
  message(FATAL_ERROR "OL_BACKEND_PLUGIN_OBSERVABLEMODELLOADER_FILE is not set")
endif()
if(NOT DEFINED OL_BACKEND_PLUGIN_OBSERVABLEMODELREGISTER_FILE OR OL_BACKEND_PLUGIN_OBSERVABLEMODELREGISTER_FILE STREQUAL "")
  message(FATAL_ERROR "OL_BACKEND_PLUGIN_OBSERVABLEMODELREGISTER_FILE is not set")
endif()
if(NOT DEFINED OL_BACKEND_PLUGIN_TCPBACKEND_FILE OR OL_BACKEND_PLUGIN_TCPBACKEND_FILE STREQUAL "")
  message(FATAL_ERROR "OL_BACKEND_PLUGIN_TCPBACKEND_FILE is not set")
endif()
if(NOT DEFINED OL_FRONTEND_PLUGIN_GUICONSOLE_FILE OR OL_FRONTEND_PLUGIN_GUICONSOLE_FILE STREQUAL "")
  message(FATAL_ERROR "OL_FRONTEND_PLUGIN_GUICONSOLE_FILE is not set")
endif()
if(NOT DEFINED OL_FRONTEND_PLUGIN_TCPFRONTEND_FILE OR OL_FRONTEND_PLUGIN_TCPFRONTEND_FILE STREQUAL "")
  message(FATAL_ERROR "OL_FRONTEND_PLUGIN_TCPFRONTEND_FILE is not set")
endif()

# runtime directories
#####################
set(OL_BIN_DIR    "${OL_RUNTIME_ROOT}/bin")
set(OL_LIBS_DIR    "${OL_BIN_DIR}/libs")
# runtime backend directories
set(OL_BACKEND_BUNDLES_DIR "${OL_BIN_DIR}/oplink_backend/bundles")
set(OL_BACKEND_CONF_DIR "${OL_BIN_DIR}/oplink_backend/conf")
set(OL_BACKEND_LOGS_DIR "${OL_BIN_DIR}/oplink_backend/logs")
# runtime guiconsole plugframe directories
set(OL_FRONTEND_BUNDLES_DIR "${OL_BIN_DIR}/oplink_frontend/bundles")
set(OL_FRONTEND_CONF_DIR "${OL_BIN_DIR}/oplink_frontend/conf")
set(OL_FRONTEND_LOGS_DIR "${OL_BIN_DIR}/oplink_frontend/logs")

# create all directories
########################
execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${OL_BIN_DIR}")
execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${OL_LIBS_DIR}")
execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${OL_BACKEND_BUNDLES_DIR}")
execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${OL_BACKEND_CONF_DIR}")
execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${OL_BACKEND_LOGS_DIR}")
execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${OL_FRONTEND_BUNDLES_DIR}")
execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${OL_FRONTEND_CONF_DIR}")
execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${OL_FRONTEND_LOGS_DIR}")

# helpers
#########

function(ol_copy_lib lib_file lib_soname lib_linker)
  if(NOT EXISTS "${lib_file}")
    message(FATAL_ERROR "Missing lib real file: ${lib_file}")
  endif()

  execute_process(COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                  "${lib_file}" "${OL_LIBS_DIR}")

  # Linux specific
  if(lib_soname AND lib_linker)
    get_filename_component(_real_name   "${lib_file}" NAME)
    get_filename_component(_soname_name "${lib_soname}" NAME)
    get_filename_component(_linker_name "${lib_linker}" NAME)

    # soname -> real
    execute_process(COMMAND "${CMAKE_COMMAND}" -E create_symlink
                    "${_real_name}" "${OL_LIBS_DIR}/${_soname_name}")

    # linker -> soname
    execute_process(COMMAND "${CMAKE_COMMAND}" -E create_symlink
                    "${_soname_name}" "${OL_LIBS_DIR}/${_linker_name}")
  endif()

endfunction()

function(ol_copy_bundle dest bundle_name plugin_file)
  if(NOT EXISTS "${plugin_file}")
    message(FATAL_ERROR "Bundle '${bundle_name}' missing: ${plugin_file}")
  endif()

  if(dest STREQUAL "backend" OR dest STREQUAL "both")
    set(dst_backend "${OL_BIN_DIR}/oplink_backend/bundles/${bundle_name}")
    execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${dst_backend}")
    execute_process(COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${plugin_file}" "${dst_backend}")
  endif()

  if(dest STREQUAL "frontend" OR dest STREQUAL "both")
    set(dst_frontend "${OL_BIN_DIR}/oplink_frontend/bundles/${bundle_name}")
    execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${dst_frontend}")
    execute_process(COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${plugin_file}" "${dst_frontend}")
  endif()

  if(NOT (dest STREQUAL "backend" OR dest STREQUAL "frontend" OR dest STREQUAL "both"))
    message(FATAL_ERROR "ol_copy_bundle(): invalid dest='${dest}' (use backend|frontend|both)")
  endif()
endfunction()

function(ol_copy_conf_file src_file dst_dir)
  if(NOT EXISTS "${src_file}")
    message(FATAL_ERROR "Missing conf file: ${src_file}")
  endif()

  execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${dst_dir}")
  execute_process(COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                  "${src_file}" "${dst_dir}")
endfunction()

# core-libs install
###################
ol_copy_lib(${PF_CORE_LIB_FILE} ${PF_CORE_LIB_SONAME} ${PF_CORE_LIB_LINKER})
ol_copy_lib(${OL_CORE_LIB_FILE} ${OL_CORE_LIB_SONAME} ${OL_CORE_LIB_LINKER})
ol_copy_lib(${OL_CORE_BACKEND_LIB_FILE} ${OL_CORE_BACKEND_LIB_SONAME} ${OL_CORE_BACKEND_LIB_LINKER})

# bundles install
#################
ol_copy_bundle("both"     "framework"                 "${PF_PLUGIN_FRAMEWORK_FILE}")
ol_copy_bundle("both"     "logger"                    "${PF_PLUGIN_LOGGER_FILE}")
ol_copy_bundle("backend"  "users"                     "${PF_PLUGIN_USERS_FILE}")
ol_copy_bundle("backend"  "display"                   "${PF_PLUGIN_DISPLAY_FILE}")
ol_copy_bundle("backend"  "console"                   "${OL_BACKEND_PLUGIN_CONSOLE_FILE}")
ol_copy_bundle("backend"  "engine"                    "${OL_BACKEND_PLUGIN_ENGINE_FILE}")
ol_copy_bundle("backend"  "enoceaninfrastructure"     "${OL_BACKEND_PLUGIN_ENOCEANINFRASTRUCTURE_FILE}")
ol_copy_bundle("backend"  "heatingmanagerset"         "${OL_BACKEND_PLUGIN_HEATINGMANAGERSET_FILE}")
ol_copy_bundle("backend"  "observablemodelloader"     "${OL_BACKEND_PLUGIN_OBSERVABLEMODELLOADER_FILE}")
ol_copy_bundle("backend"  "observablemodelregister"   "${OL_BACKEND_PLUGIN_OBSERVABLEMODELREGISTER_FILE}")
ol_copy_bundle("backend"  "tcpbackend"                "${OL_BACKEND_PLUGIN_TCPBACKEND_FILE}")
ol_copy_bundle("frontend" "guidisplay"                "${PF_PLUGIN_GUIDISPLAY_FILE}")
ol_copy_bundle("frontend" "guiconsole"                "${OL_FRONTEND_PLUGIN_GUICONSOLE_FILE}")
ol_copy_bundle("frontend" "tcpfrontend"               "${OL_FRONTEND_PLUGIN_TCPFRONTEND_FILE}")

# bundles and launcher conf files
#################################

set(OL_PROFILE_DIR "${OL_PROFILES_ROOT_DIR}/${OL_SELECTED_PROFILE_NAME}")

# backend
#########

# Launcher conf properties.ini
ol_copy_conf_file(
  "${OL_PROFILE_DIR}/oplink/backend/properties.ini"
  "${OL_BIN_DIR}/oplink_backend/conf"
)

# Logger bundle conf
ol_copy_conf_file(
  "${OL_PROFILE_DIR}/oplink/backend/log.ini"
  "${OL_BIN_DIR}/oplink_backend/bundles/logger/conf"
)

# Users bundle conf
ol_copy_conf_file(
  "${OL_PROFILE_DIR}/oplink/backend/users.ini"
  "${OL_BIN_DIR}/oplink_backend/bundles/users/conf"
)
ol_copy_conf_file(
  "${OL_PROFILE_DIR}/oplink/backend/user_remote_monitoring.xml"
  "${OL_BIN_DIR}/oplink_backend/bundles/users/conf"
)

# Enoceaninfrastructure bundle conf
ol_copy_conf_file(
  "${OL_PROFILE_DIR}/oplink/backend/infrastructure_enocean.xml"
  "${OL_BIN_DIR}/oplink_backend/bundles/enoceaninfrastructure/conf"
)

# Heatingmanagerset bundle conf
ol_copy_conf_file(
  "${OL_PROFILE_DIR}/oplink/backend/heating_pwt_manager1.xml"
  "${OL_BIN_DIR}/oplink_backend/bundles/heatingmanagerset/conf"
)

# Observablemodelloader bundle conf
ol_copy_conf_file(
  "${OL_PROFILE_DIR}/oplink/backend/observable_models.xml"
  "${OL_BIN_DIR}/oplink_backend/bundles/observablemodelloader/conf"
)

# Tcpbackend bundle conf
ol_copy_conf_file(
  "${OL_PROFILE_DIR}/oplink/backend/listen_addr.ini"
  "${OL_BIN_DIR}/oplink_backend/bundles/tcpbackend/conf"
)

# frontend
##########

# Launcher conf
ol_copy_conf_file(
  "${OL_PROFILE_DIR}/oplink/frontend/properties.ini"
  "${OL_BIN_DIR}/oplink_frontend/conf"
)

ol_copy_conf_file(
  "${OL_PROFILE_DIR}/oplink/frontend/elekdom.qss"
  "${OL_BIN_DIR}/oplink_frontend/conf"
)

# Logger bundle conf
ol_copy_conf_file(
  "${OL_PROFILE_DIR}/oplink/frontend/log.ini"
  "${OL_BIN_DIR}/oplink_frontend/bundles/logger/conf"
)

# Guiconsole bundle conf
ol_copy_conf_file(
  "${OL_PROFILE_DIR}/oplink/frontend/guiconsole.ini"
  "${OL_BIN_DIR}/oplink_frontend/bundles/guiconsole/conf"
)



# finished!
###########
message(STATUS "OpLink runtime installed at: ${OL_BIN_DIR}")
