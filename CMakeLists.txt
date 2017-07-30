if("${CMAKE_VERSION}" VERSION_LESS 3.1.0)
	message("Not a valid CMake version")
	message("On Ubuntu >= 16.04, install or upgrade via:")
	message("	sudo apt-get install cmake")
	message("")
	message("Official website: https://cmake.org/download/")
	message(FATAL_ERROR "Update CMake and try again" )
endif()

# Warning: Changing this modifies CMake's internal workings
# and leads to wrong toolchain detection
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(elka_data_collection)

set(ELKA_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(ELKA_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}")

set(PYBIND11_CPP_STANDARD -std=c++11)

#=============================================================================
# configuration
#
# must come before project to set toolchain
set(OS "ubuntu")

set(Boost_USE_MULTITHREADED ON)

find_package(Boost
  COMPONENTS system thread
  REQUIRED
)

if (Boost_FOUND)
	include_directories(${BOOST_INCLUDE_DIRS})
else()
	message(FATAL_ERROR "Cannot find C++ Boost" )
endif()

# Define GNU standard installation directories
include(GNUInstallDirs)

# Add support for external project building
include(ExternalProject)

# Add support for using python interpreter
set(PYTHON_VERSION_MAJOR 2)
set(PYTHON_VERSION_MINOR 7)
include(FindPythonInterp)

list(APPEND CMAKE_MODULE_PATH "${ELKA_SOURCE_DIR}/cmake")
message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

include(common/elka_base)

# Setup install paths
if(NOT CMAKE_INSTALL_PREFIX)
  if (${OS} STREQUAL "posix" or ${OS} STREQUAL "ubuntu")
		set(CMAKE_INSTALL_PREFIX "/usr" CACHE PATH "Install path prefix" FORCE)
	endif()
endif()
if (CMAKE_INSTALL_PREFIX)
	message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
endif()

# cmake modules
include(ExternalProject)

# Add libraries, subdirectories, etc to include all source and header files
include_directories(
  ${ELKA_BINARY_DIR}/inc
  ${ELKA_BINARY_DIR}/src
  ${ELKA_SOURCE_DIR}/inc
  ${ELKA_SOURCE_DIR}/inc/uORB
  ${ELKA_SOURCE_DIR}/src
  ${ELKA_SOURCE_DIR}/src/elka_comm
)

link_directories(
  ${ELKA_BINARY_DIR}/src/elka_comm/common
  ${ELKA_BINARY_DIR}/src/elka_comm/gnd_station
  ${ELKA_BINARY_DIR}/python
  ${ELKA_SOURCE_DIR}/python
)

set(ELKA_LINK_LIBS "")

add_definitions(
  -D__ELKA_UBUNTU
)

#=============================================================================

#=============================================================================
# git
#

elka_add_git_submodule(TARGET git_gencpp PATH "tools/gencpp")
elka_add_git_submodule(TARGET git_genmsg PATH "tools/genmsg")
elka_add_git_submodule(TARGET git_elka_comm PATH "src/elka_comm")

add_custom_target(submodule_clean
  WORKING_DIRECTORY ${ELKA_SOURCE_DIR}
	COMMAND git submodule deinit -f .
	COMMAND rm -rf .git/modules/*
	)

#=============================================================================
# source code generation
#

add_subdirectory(msg)
elka_generate_messages(TARGET msg_gen
	MSG_FILES ${msg_files}
	OS ${OS}
	INCLUDES ${msg_include_paths}
	DEPENDS git_genmsg git_gencpp
)

#=============================================================================
# Set C/C++ compile and linking flags
set(GCC_COVERAGE_COMPILE_FLAGS "-fpic -Wl,--no-as-needed")

set(GXX_COVERAGE_COMPILE_FLAGS "-std=c++11")

set(GXX_COVERAGE_LINK_FLAGS "-Wl,--no-undefined -Wl,--no-as-needed")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS} ${GXX_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER__FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_subdirectory(src)

#TODO set PYTHONPATH
set(PYTHON_MODULES
	${ELKA_BINARY_DIR}/src/elka_comm/common
	${ELKA_BINARY_DIR}/src/elka_comm/gnd_station
)
