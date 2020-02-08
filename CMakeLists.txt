# Set the minimum version of CMake that can run this build configuration
# Also influences behavior of CMake if set to an older version than the
# installed binary's version
cmake_minimum_required (VERSION 3.13)

# Define the project - a project is a set of code that can be built
# independently (3rd party dependencies notwithstanding)
project(project-name
	VERSION 0.1.0.0 # Project version as major.minor.patch.tweak
	LANGUAGES CXX # Languages used in the project, e.g. CXX for C++.
	DESCRIPTION "Project description" # A short description of the project. Used
	                                  # by Doxygen.
)

# Defines common installation directories for your system, e.g. /lib, /bin
include(GNUInstallDirs)

# Check to see if Doxygen is installed on the system and detectable by CMake
find_package(Doxygen)

# Defines a build option, controllable by the builder, deciding whether
# the build should be configured to produce documentation or not.
# Defaults to building docs only if Doxygen is found.
option(BUILD_DOCUMENTATION "Build Doxygen documentation" ${DOXYGEN_FOUND})

if(BUILD_DOCUMENTATION)
	if(DOXYGEN_FOUND)
		# Preprocess the Doxyfile.in file to replace CMake placeholders with
		# their final values
		set(DOXYGEN_IN ${CMAKE_CURRENT_LIST_DIR}/docs/Doxyfile.in)
		set(DOXYGEN_OUT ${PROJECT_BINARY_DIR}/Doxyfile)

		configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
		message("-- Doxygen build enabled")

		# Define build system target (e.g. make docs) to run Doxygen using the
		# generated Doxyfile.
		add_custom_target(docs ALL
			COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
			WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
			COMMENT "Generating API docs with Doxygen"
			VERBATIM
		)

	else()
		message(FATAL_ERROR 
			"Doxygen generation requested but package was not found"
		)
	endif()
endif()

# Read and process the CMakeLists.txt in lib.
add_subdirectory(lib)

# Enable CTest support
include(CTest)

# Unless builder disables this, add tests to the build
if(BUILD_TESTING)
	# Run CMakeLists.txt in the test subdirectory
	add_subdirectory(test)
endif()

# Read and process the CMakeLists.txt in app.
# If you don't want to build an executable, simply delete this and the app
# directory.
add_subdirectory(app)
