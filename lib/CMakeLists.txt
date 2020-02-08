# Create a static library target named "foo"
add_library(foo STATIC
	src/foo.cpp # Specify source files (not headers!) for foo here

	# Note: Do NOT use file glob expressions. It is advised that the
	# library have at least one explicitly-specified source file here.
	# More can be added via target_sources from subdirectories.
)

# Set the public and private include directories for foo
target_include_directories(foo
	PUBLIC
		# Path to public include directory at build-time
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
		# Path to public include directory at install-time
		$<INSTALL_INTERFACE:include>
	PRIVATE
		# Path to private include directory at build-time
		${CMAKE_CURRENT_LIST_DIR}/src/include
)

# Example of targeting a C++ compile feature; sets standard to C++11
# Since this option is PUBLIC, any targets that link to this library
# will also compile against C++11
target_compile_features(foo
	PUBLIC
		cxx_std_11
)

# Example of adding a compile definition (preprocessor definition)
# Since this option is private, it will only be defined during the build
# for foo and not for any clients
target_compile_definitions(foo
	PRIVATE
		# Only on debug builds, define the preprocessor variable FOO_DEBUG
		$<$<CONFIG:Debug>:FOO_DEBUG>
)

# Install foo (e.g. libfoo.a) to the standard installation paths under the 
# build's binary directory
# Also export its targets as fooConfig
install(TARGETS foo EXPORT fooConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Install the public include directory.
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Export all targets (e.g. the library target, foo) to a cmake file for use by
# clients under the foo namespace. Thus a client can link against this library
# by accessing foo::foo.
export(TARGETS foo
	FILE fooConfig.cmake
	NAMESPACE foo::
)

# Install the configuration file exporting foo's configuration.
install(EXPORT fooConfig
	DESTINATION share/foo/cmake
)
