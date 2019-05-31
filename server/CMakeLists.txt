project(server)
cmake_minimum_required(VERSION 2.8)

include_directories(
.
mp_management
)

add_definitions(-DDAEMON_APP)

aux_source_directory(. SRC_LIST)
aux_source_directory(./mp_management SRC_LIST)

find_package (Threads)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

