set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)

add_executable(procman-deputy
    event_loop.cpp
    procman_deputy.cpp)

find_package(PkgConfig REQUIRED)
pkg_check_modules(ZCM REQUIRED zcm)
include_directories(${ZCM_INCLUDE_DIRS})

target_link_libraries(procman-deputy
                      procman
                      procman_zcmtypes
                      ${ZCM_LDFLAGS})

install(TARGETS procman-deputy DESTINATION bin)

add_executable(event_loop_test event_loop_test.cpp event_loop.cpp)
