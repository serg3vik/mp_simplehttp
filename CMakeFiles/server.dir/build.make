# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sie/__git_projects/mp_simplehttp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sie/__git_projects/mp_simplehttp

# Include any dependencies generated for this target.
include CMakeFiles/server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

CMakeFiles/server.dir/server/error_handler.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/server/error_handler.cpp.o: server/error_handler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sie/__git_projects/mp_simplehttp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/server.dir/server/error_handler.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/server/error_handler.cpp.o -c /home/sie/__git_projects/mp_simplehttp/server/error_handler.cpp

CMakeFiles/server.dir/server/error_handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/server/error_handler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sie/__git_projects/mp_simplehttp/server/error_handler.cpp > CMakeFiles/server.dir/server/error_handler.cpp.i

CMakeFiles/server.dir/server/error_handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/server/error_handler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sie/__git_projects/mp_simplehttp/server/error_handler.cpp -o CMakeFiles/server.dir/server/error_handler.cpp.s

CMakeFiles/server.dir/server/http_error.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/server/http_error.cpp.o: server/http_error.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sie/__git_projects/mp_simplehttp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/server.dir/server/http_error.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/server/http_error.cpp.o -c /home/sie/__git_projects/mp_simplehttp/server/http_error.cpp

CMakeFiles/server.dir/server/http_error.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/server/http_error.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sie/__git_projects/mp_simplehttp/server/http_error.cpp > CMakeFiles/server.dir/server/http_error.cpp.i

CMakeFiles/server.dir/server/http_error.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/server/http_error.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sie/__git_projects/mp_simplehttp/server/http_error.cpp -o CMakeFiles/server.dir/server/http_error.cpp.s

CMakeFiles/server.dir/server/main.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/server/main.cpp.o: server/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sie/__git_projects/mp_simplehttp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/server.dir/server/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/server/main.cpp.o -c /home/sie/__git_projects/mp_simplehttp/server/main.cpp

CMakeFiles/server.dir/server/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/server/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sie/__git_projects/mp_simplehttp/server/main.cpp > CMakeFiles/server.dir/server/main.cpp.i

CMakeFiles/server.dir/server/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/server/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sie/__git_projects/mp_simplehttp/server/main.cpp -o CMakeFiles/server.dir/server/main.cpp.s

CMakeFiles/server.dir/server/server.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/server/server.cpp.o: server/server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sie/__git_projects/mp_simplehttp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/server.dir/server/server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/server/server.cpp.o -c /home/sie/__git_projects/mp_simplehttp/server/server.cpp

CMakeFiles/server.dir/server/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/server/server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sie/__git_projects/mp_simplehttp/server/server.cpp > CMakeFiles/server.dir/server/server.cpp.i

CMakeFiles/server.dir/server/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/server/server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sie/__git_projects/mp_simplehttp/server/server.cpp -o CMakeFiles/server.dir/server/server.cpp.s

CMakeFiles/server.dir/server/mp_management/fd_pass.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/server/mp_management/fd_pass.cpp.o: server/mp_management/fd_pass.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sie/__git_projects/mp_simplehttp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/server.dir/server/mp_management/fd_pass.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/server/mp_management/fd_pass.cpp.o -c /home/sie/__git_projects/mp_simplehttp/server/mp_management/fd_pass.cpp

CMakeFiles/server.dir/server/mp_management/fd_pass.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/server/mp_management/fd_pass.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sie/__git_projects/mp_simplehttp/server/mp_management/fd_pass.cpp > CMakeFiles/server.dir/server/mp_management/fd_pass.cpp.i

CMakeFiles/server.dir/server/mp_management/fd_pass.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/server/mp_management/fd_pass.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sie/__git_projects/mp_simplehttp/server/mp_management/fd_pass.cpp -o CMakeFiles/server.dir/server/mp_management/fd_pass.cpp.s

CMakeFiles/server.dir/server/mp_management/fileutils.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/server/mp_management/fileutils.cpp.o: server/mp_management/fileutils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sie/__git_projects/mp_simplehttp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/server.dir/server/mp_management/fileutils.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/server/mp_management/fileutils.cpp.o -c /home/sie/__git_projects/mp_simplehttp/server/mp_management/fileutils.cpp

CMakeFiles/server.dir/server/mp_management/fileutils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/server/mp_management/fileutils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sie/__git_projects/mp_simplehttp/server/mp_management/fileutils.cpp > CMakeFiles/server.dir/server/mp_management/fileutils.cpp.i

CMakeFiles/server.dir/server/mp_management/fileutils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/server/mp_management/fileutils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sie/__git_projects/mp_simplehttp/server/mp_management/fileutils.cpp -o CMakeFiles/server.dir/server/mp_management/fileutils.cpp.s

CMakeFiles/server.dir/server/mp_management/manager.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/server/mp_management/manager.cpp.o: server/mp_management/manager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sie/__git_projects/mp_simplehttp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/server.dir/server/mp_management/manager.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/server/mp_management/manager.cpp.o -c /home/sie/__git_projects/mp_simplehttp/server/mp_management/manager.cpp

CMakeFiles/server.dir/server/mp_management/manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/server/mp_management/manager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sie/__git_projects/mp_simplehttp/server/mp_management/manager.cpp > CMakeFiles/server.dir/server/mp_management/manager.cpp.i

CMakeFiles/server.dir/server/mp_management/manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/server/mp_management/manager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sie/__git_projects/mp_simplehttp/server/mp_management/manager.cpp -o CMakeFiles/server.dir/server/mp_management/manager.cpp.s

CMakeFiles/server.dir/server/mp_management/worker.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/server/mp_management/worker.cpp.o: server/mp_management/worker.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sie/__git_projects/mp_simplehttp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/server.dir/server/mp_management/worker.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/server/mp_management/worker.cpp.o -c /home/sie/__git_projects/mp_simplehttp/server/mp_management/worker.cpp

CMakeFiles/server.dir/server/mp_management/worker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/server/mp_management/worker.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sie/__git_projects/mp_simplehttp/server/mp_management/worker.cpp > CMakeFiles/server.dir/server/mp_management/worker.cpp.i

CMakeFiles/server.dir/server/mp_management/worker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/server/mp_management/worker.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sie/__git_projects/mp_simplehttp/server/mp_management/worker.cpp -o CMakeFiles/server.dir/server/mp_management/worker.cpp.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/server/error_handler.cpp.o" \
"CMakeFiles/server.dir/server/http_error.cpp.o" \
"CMakeFiles/server.dir/server/main.cpp.o" \
"CMakeFiles/server.dir/server/server.cpp.o" \
"CMakeFiles/server.dir/server/mp_management/fd_pass.cpp.o" \
"CMakeFiles/server.dir/server/mp_management/fileutils.cpp.o" \
"CMakeFiles/server.dir/server/mp_management/manager.cpp.o" \
"CMakeFiles/server.dir/server/mp_management/worker.cpp.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

server: CMakeFiles/server.dir/server/error_handler.cpp.o
server: CMakeFiles/server.dir/server/http_error.cpp.o
server: CMakeFiles/server.dir/server/main.cpp.o
server: CMakeFiles/server.dir/server/server.cpp.o
server: CMakeFiles/server.dir/server/mp_management/fd_pass.cpp.o
server: CMakeFiles/server.dir/server/mp_management/fileutils.cpp.o
server: CMakeFiles/server.dir/server/mp_management/manager.cpp.o
server: CMakeFiles/server.dir/server/mp_management/worker.cpp.o
server: CMakeFiles/server.dir/build.make
server: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sie/__git_projects/mp_simplehttp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: server

.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend:
	cd /home/sie/__git_projects/mp_simplehttp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sie/__git_projects/mp_simplehttp /home/sie/__git_projects/mp_simplehttp /home/sie/__git_projects/mp_simplehttp /home/sie/__git_projects/mp_simplehttp /home/sie/__git_projects/mp_simplehttp/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server.dir/depend

