# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/sie/__git_projects/mp_simplehttp/CMakeFiles /home/sie/__git_projects/mp_simplehttp/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/sie/__git_projects/mp_simplehttp/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named final

# Build rule for target.
final: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 final
.PHONY : final

# fast build rule for target.
final/fast:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/build
.PHONY : final/fast

server/error_handler.o: server/error_handler.cpp.o

.PHONY : server/error_handler.o

# target to build an object file
server/error_handler.cpp.o:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/server/error_handler.cpp.o
.PHONY : server/error_handler.cpp.o

server/error_handler.i: server/error_handler.cpp.i

.PHONY : server/error_handler.i

# target to preprocess a source file
server/error_handler.cpp.i:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/server/error_handler.cpp.i
.PHONY : server/error_handler.cpp.i

server/error_handler.s: server/error_handler.cpp.s

.PHONY : server/error_handler.s

# target to generate assembly for a file
server/error_handler.cpp.s:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/server/error_handler.cpp.s
.PHONY : server/error_handler.cpp.s

server/http_error.o: server/http_error.cpp.o

.PHONY : server/http_error.o

# target to build an object file
server/http_error.cpp.o:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/server/http_error.cpp.o
.PHONY : server/http_error.cpp.o

server/http_error.i: server/http_error.cpp.i

.PHONY : server/http_error.i

# target to preprocess a source file
server/http_error.cpp.i:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/server/http_error.cpp.i
.PHONY : server/http_error.cpp.i

server/http_error.s: server/http_error.cpp.s

.PHONY : server/http_error.s

# target to generate assembly for a file
server/http_error.cpp.s:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/server/http_error.cpp.s
.PHONY : server/http_error.cpp.s

server/main.o: server/main.cpp.o

.PHONY : server/main.o

# target to build an object file
server/main.cpp.o:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/server/main.cpp.o
.PHONY : server/main.cpp.o

server/main.i: server/main.cpp.i

.PHONY : server/main.i

# target to preprocess a source file
server/main.cpp.i:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/server/main.cpp.i
.PHONY : server/main.cpp.i

server/main.s: server/main.cpp.s

.PHONY : server/main.s

# target to generate assembly for a file
server/main.cpp.s:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/server/main.cpp.s
.PHONY : server/main.cpp.s

server/mp_management/fd_pass.o: server/mp_management/fd_pass.cpp.o

.PHONY : server/mp_management/fd_pass.o

# target to build an object file
server/mp_management/fd_pass.cpp.o:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/server/mp_management/fd_pass.cpp.o
.PHONY : server/mp_management/fd_pass.cpp.o

server/mp_management/fd_pass.i: server/mp_management/fd_pass.cpp.i

.PHONY : server/mp_management/fd_pass.i

# target to preprocess a source file
server/mp_management/fd_pass.cpp.i:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/server/mp_management/fd_pass.cpp.i
.PHONY : server/mp_management/fd_pass.cpp.i

server/mp_management/fd_pass.s: server/mp_management/fd_pass.cpp.s

.PHONY : server/mp_management/fd_pass.s

# target to generate assembly for a file
server/mp_management/fd_pass.cpp.s:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/server/mp_management/fd_pass.cpp.s
.PHONY : server/mp_management/fd_pass.cpp.s

server/mp_management/fileutils.o: server/mp_management/fileutils.cpp.o

.PHONY : server/mp_management/fileutils.o

# target to build an object file
server/mp_management/fileutils.cpp.o:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/server/mp_management/fileutils.cpp.o
.PHONY : server/mp_management/fileutils.cpp.o

server/mp_management/fileutils.i: server/mp_management/fileutils.cpp.i

.PHONY : server/mp_management/fileutils.i

# target to preprocess a source file
server/mp_management/fileutils.cpp.i:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/server/mp_management/fileutils.cpp.i
.PHONY : server/mp_management/fileutils.cpp.i

server/mp_management/fileutils.s: server/mp_management/fileutils.cpp.s

.PHONY : server/mp_management/fileutils.s

# target to generate assembly for a file
server/mp_management/fileutils.cpp.s:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/server/mp_management/fileutils.cpp.s
.PHONY : server/mp_management/fileutils.cpp.s

server/mp_management/manager.o: server/mp_management/manager.cpp.o

.PHONY : server/mp_management/manager.o

# target to build an object file
server/mp_management/manager.cpp.o:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/server/mp_management/manager.cpp.o
.PHONY : server/mp_management/manager.cpp.o

server/mp_management/manager.i: server/mp_management/manager.cpp.i

.PHONY : server/mp_management/manager.i

# target to preprocess a source file
server/mp_management/manager.cpp.i:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/server/mp_management/manager.cpp.i
.PHONY : server/mp_management/manager.cpp.i

server/mp_management/manager.s: server/mp_management/manager.cpp.s

.PHONY : server/mp_management/manager.s

# target to generate assembly for a file
server/mp_management/manager.cpp.s:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/server/mp_management/manager.cpp.s
.PHONY : server/mp_management/manager.cpp.s

server/mp_management/worker.o: server/mp_management/worker.cpp.o

.PHONY : server/mp_management/worker.o

# target to build an object file
server/mp_management/worker.cpp.o:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/server/mp_management/worker.cpp.o
.PHONY : server/mp_management/worker.cpp.o

server/mp_management/worker.i: server/mp_management/worker.cpp.i

.PHONY : server/mp_management/worker.i

# target to preprocess a source file
server/mp_management/worker.cpp.i:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/server/mp_management/worker.cpp.i
.PHONY : server/mp_management/worker.cpp.i

server/mp_management/worker.s: server/mp_management/worker.cpp.s

.PHONY : server/mp_management/worker.s

# target to generate assembly for a file
server/mp_management/worker.cpp.s:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/server/mp_management/worker.cpp.s
.PHONY : server/mp_management/worker.cpp.s

server/server.o: server/server.cpp.o

.PHONY : server/server.o

# target to build an object file
server/server.cpp.o:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/server/server.cpp.o
.PHONY : server/server.cpp.o

server/server.i: server/server.cpp.i

.PHONY : server/server.i

# target to preprocess a source file
server/server.cpp.i:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/server/server.cpp.i
.PHONY : server/server.cpp.i

server/server.s: server/server.cpp.s

.PHONY : server/server.s

# target to generate assembly for a file
server/server.cpp.s:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/server/server.cpp.s
.PHONY : server/server.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... final"
	@echo "... edit_cache"
	@echo "... server/error_handler.o"
	@echo "... server/error_handler.i"
	@echo "... server/error_handler.s"
	@echo "... server/http_error.o"
	@echo "... server/http_error.i"
	@echo "... server/http_error.s"
	@echo "... server/main.o"
	@echo "... server/main.i"
	@echo "... server/main.s"
	@echo "... server/mp_management/fd_pass.o"
	@echo "... server/mp_management/fd_pass.i"
	@echo "... server/mp_management/fd_pass.s"
	@echo "... server/mp_management/fileutils.o"
	@echo "... server/mp_management/fileutils.i"
	@echo "... server/mp_management/fileutils.s"
	@echo "... server/mp_management/manager.o"
	@echo "... server/mp_management/manager.i"
	@echo "... server/mp_management/manager.s"
	@echo "... server/mp_management/worker.o"
	@echo "... server/mp_management/worker.i"
	@echo "... server/mp_management/worker.s"
	@echo "... server/server.o"
	@echo "... server/server.i"
	@echo "... server/server.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
