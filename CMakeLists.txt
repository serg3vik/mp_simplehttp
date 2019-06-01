project(final)
cmake_minimum_required(VERSION 2.8)
add_compile_options(-std=c++11)

include_directories(
./server
./server/mp_management
)

#add_definitions(-DDAEMON_APP)

aux_source_directory(./server SRC_LIST)
aux_source_directory(./server/mp_management SRC_LIST)

find_package (Threads)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

# add_custom_command(TARGET ./server/${PROJECT_NAME} POST_BUILD
#     COMMAND mkdir /home/sie/final && cp ./server/${PROJECT_NAME} /home/sie/final/final
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#     COMMENT "Running CRC32 check..."
# )
