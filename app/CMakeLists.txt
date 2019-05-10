# Create an executable named fooapp
add_executable(fooapp
	src/main.cpp
)

target_link_libraries(fooapp
	foo
)

# Install fooapp (e.g. fooapp.exe) to the standard installation paths under the 
# build's binary directory
install(TARGETS foo
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
)
