project(server)
cmake_minimum_required(VERSION 2.8)

include_directories(
.
mp_management
)

aux_source_directory(. SRC_LIST)
aux_source_directory(./mp_management SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST})

