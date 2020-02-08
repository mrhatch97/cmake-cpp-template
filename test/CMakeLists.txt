message("-- foo tests enabled")

# Creates a custom target called build_tests; each test will be added as a
# dependency of this target
add_custom_target(build_tests)
# Creates a custom target called check which runs CTest. Depends on build_tests,
# so will automatically build tests if they are not already built.
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS build_tests)

# Add an INTERFACE library for test utilities - this is simply a header-only
# library.
add_library(foo_test INTERFACE)

# Set the include directories for the header-only test library.
target_include_directories(foo_test
	INTERFACE
		${CMAKE_CURRENT_LIST_DIR}/include
		${PROJECT_SOURCE_DIR}/lib/src/include
)

# Defines a macro that accepts a test name and creates the necessary test
# executable, links it to the required libraries, registers it with CTest, and
# adds it to the build_tests target.
macro(add_quick_test test_name)
	# A CTest test is simply a C++ executable which signals success by returning
	# 0 from main.
	add_executable(test_${test_name}
		test_${test_name}.cpp)

	# Link the executable to the library under test and the test utility library
	target_link_libraries(test_${test_name}
		PRIVATE
			foo
			foo_test)

	# Register the test with CTest. Ensure it runs with the test directory as
	# its working directory.
	add_test(NAME ${test_name}
		COMMAND test_${test_name}
		WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test)

	# Add the executable as a dependency of build_tests. This ensures that all
	# test executables are built when e.g. `make build_tests` is run.
	add_dependencies(build_tests test_${test_name})
endmacro()

# Example of creating a test. This expects a c++ file called test_factorial.cpp
# to exist in the test directory, which contains a valid main() function.
add_quick_test(factorial)
