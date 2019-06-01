project(server)
cmake_minimum_required(VERSION 2.8)



include_directories(
.
mp_management
)

#add_definitions(-DDAEMON_APP)

aux_source_directory(. SRC_LIST)
aux_source_directory(./mp_management SRC_LIST)

find_package (Threads)

add_executable(${PROJECT_NAME} ${SRC_LIST})
#add_executable(/home/sie/final ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
#target_link_libraries(/home/sie/final ${CMAKE_THREAD_LIBS_INIT})

#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#    COMMAND mkdir /home/sie/final && cp ${PROJECT_NAME} /home/sie/final/final
#    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#    COMMENT "Running CRC32 check..."
#)
