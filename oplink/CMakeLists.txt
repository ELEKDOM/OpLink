# OpLink Core Lib Target Name
set(OL_LIB_NAME
    "oplink-core-qt6"
    )
message(STATUS "OL_LIB_NAME = " ${OL_LIB_NAME})

# OpLink Core Lib include dir
set(OL_LIB_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core-lib")
message(STATUS "OL_LIB_INC_DIR = " ${OL_LIB_INC_DIR})

# OpLink Core Lib (frontend & backend)
add_subdirectory(core-lib)

# OpLink Backend Part
if(OL_BUILD_BACKEND)
    # OpLink backend Core Lib Target Name
    set(OL_BACKEND_LIB_NAME
        "oplink-core-backend-qt6"
        )
    message(STATUS "OL_BACKEND_LIB_NAME = " ${OL_BACKEND_LIB_NAME})

    # OpLink backend Core Lib include dir
    set(OL_BACKEND_LIB_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core-backend-lib")
    message(STATUS "OL_BACKEND_LIB_INC_DIR = " ${OL_BACKEND_LIB_INC_DIR})

    # OpLink backend Core Lib
    add_subdirectory(core-backend-lib)

    # OpLink backend Bundles
    add_subdirectory(backend-bundles)

    # OpLink backend Launcher
    add_subdirectory(backend-launcher)
endif()

# OpLink Frontend Part
if(OL_BUILD_FRONTEND)
    # OpLink front Bundles
    add_subdirectory(frontend-bundles)

    # OpLink frontend Launcher
    add_subdirectory(frontend-launcher)
endif()
