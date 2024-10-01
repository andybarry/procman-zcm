cmake_minimum_required(VERSION 2.8.11)

project(procman)

set(CMAKE_CXX_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# Create a directory for build-generated header files
set(INCLUDE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/include)
execute_process(COMMAND mkdir -p ${INCLUDE_OUTPUT_PATH})

# build ZCM types.
include(cmake/zcmtypes.cmake)
zcmtypes_build(INCLUDE_BUILD_PATH ${INCLUDE_OUTPUT_PATH}
               TYPES
               zcmtypes/procman_zcm_cmd_t.zcm
               zcmtypes/procman_zcm_cmd_status_t.zcm
               zcmtypes/procman_zcm_discovery_t.zcm
               zcmtypes/procman_zcm_deputy_info_t.zcm
               zcmtypes/procman_zcm_orders_t.zcm
               zcmtypes/procman_zcm_output_t.zcm
               zcmtypes/procman_zcm_cmd_desired_t.zcm
               zcmtypes/procman_zcm_run_script_t.zcm)

add_subdirectory(src)
add_subdirectory(python)

# Install the icon file
set(ICON_SOURCE_PATH ${CMAKE_SOURCE_DIR}/doc/images/procman_icon.svg)
set(ICON_INSTALL_PATH share/icons/hicolor/scalable/apps)
install(FILES ${ICON_SOURCE_PATH} DESTINATION ${ICON_INSTALL_PATH})