# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

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
CMAKE_COMMAND = /cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/Cmake/3.11.0/Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/Cmake/3.11.0/Linux-x86_64/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/abes/tutorial2017

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/abes/tutorial2017/build

# Utility rule file for MyAnalysisExampleClidGen.

# Include the progress variables for this target.
include MyNewProject/MyAnalysisExample/CMakeFiles/MyAnalysisExampleClidGen.dir/progress.make

MyNewProject/MyAnalysisExample/CMakeFiles/MyAnalysisExampleClidGen: MyNewProject/MyAnalysisExample/MyAnalysisExample_clid.db


MyNewProject/MyAnalysisExample/MyAnalysisExample_clid.db: /cvmfs/atlas.cern.ch/repo/sw/software/21.0/AtlasCore/21.0.20/InstallArea/x86_64-slc6-gcc62-opt/bin/genCLIDDB
MyNewProject/MyAnalysisExample/MyAnalysisExample_clid.db: /cvmfs/atlas.cern.ch/repo/sw/software/21.0/AtlasCore/21.0.20/InstallArea/x86_64-slc6-gcc62-opt/lib/libCLIDComps.so
MyNewProject/MyAnalysisExample/MyAnalysisExample_clid.db: x86_64-centos7-gcc62-opt/lib/libMyAnalysisExample.so
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/abes/tutorial2017/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating MyAnalysisExample_clid.db"
	cd /home/abes/tutorial2017/build/MyNewProject/MyAnalysisExample && /cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/Cmake/3.11.0/Linux-x86_64/bin/cmake -E make_directory /home/abes/tutorial2017/build/x86_64-centos7-gcc62-opt/share
	cd /home/abes/tutorial2017/build/MyNewProject/MyAnalysisExample && /cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/Cmake/3.11.0/Linux-x86_64/bin/cmake -E touch /home/abes/tutorial2017/build/MyNewProject/MyAnalysisExample/dummy_clid.db
	cd /home/abes/tutorial2017/build/MyNewProject/MyAnalysisExample && ../../atlas_build_run.sh genCLIDDB -p MyAnalysisExample -i /home/abes/tutorial2017/build/MyNewProject/MyAnalysisExample/dummy_clid.db -o /home/abes/tutorial2017/build/MyNewProject/MyAnalysisExample/MyAnalysisExample_clid.db

MyAnalysisExampleClidGen: MyNewProject/MyAnalysisExample/CMakeFiles/MyAnalysisExampleClidGen
MyAnalysisExampleClidGen: MyNewProject/MyAnalysisExample/MyAnalysisExample_clid.db
MyAnalysisExampleClidGen: MyNewProject/MyAnalysisExample/CMakeFiles/MyAnalysisExampleClidGen.dir/build.make

.PHONY : MyAnalysisExampleClidGen

# Rule to build all files generated by this target.
MyNewProject/MyAnalysisExample/CMakeFiles/MyAnalysisExampleClidGen.dir/build: MyAnalysisExampleClidGen

.PHONY : MyNewProject/MyAnalysisExample/CMakeFiles/MyAnalysisExampleClidGen.dir/build

MyNewProject/MyAnalysisExample/CMakeFiles/MyAnalysisExampleClidGen.dir/clean:
	cd /home/abes/tutorial2017/build/MyNewProject/MyAnalysisExample && $(CMAKE_COMMAND) -P CMakeFiles/MyAnalysisExampleClidGen.dir/cmake_clean.cmake
.PHONY : MyNewProject/MyAnalysisExample/CMakeFiles/MyAnalysisExampleClidGen.dir/clean

MyNewProject/MyAnalysisExample/CMakeFiles/MyAnalysisExampleClidGen.dir/depend:
	cd /home/abes/tutorial2017/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/abes/tutorial2017 /home/abes/tutorial2017/MyNewProject/MyAnalysisExample /home/abes/tutorial2017/build /home/abes/tutorial2017/build/MyNewProject/MyAnalysisExample /home/abes/tutorial2017/build/MyNewProject/MyAnalysisExample/CMakeFiles/MyAnalysisExampleClidGen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : MyNewProject/MyAnalysisExample/CMakeFiles/MyAnalysisExampleClidGen.dir/depend

