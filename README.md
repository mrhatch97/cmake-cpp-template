This is a template for a C++ project using CMake. It is aimed at those who are
familiar with building C++ via a build tool such as `make`, but have little to
no experience with CMake. It incorporates automatic document generation using
Doxygen (if installed) as well as testing using CTest, which is included with 
CMake.

# Requirements
This project requires a modern version of CMake (3.13 or higher) and a C++
compiler that supports the C++11 standard to build out of the box. The C++
standard can be reduced, however; it is merely a requirement to compile the
example code.

# Usage
To use the template, begin by cloning the repository. If you plan on using git
and/or a remote git server, reconfigure the repository to point to the desired
origin. This tutorial does not aim to be a git tutorial.

Next, create a build directory. It is highly advised that this directory be
outside the cloned repository; this is why the provided .gitignore does not have
an exclusion for it. A suggestion is `~/build/cmake`. This is called an
out-of-source build.

Navigate to the created build directory. Run the following command:
`cmake -Bcmake-template /path/to/repository/root`.

To elaborate:
If your build directory is at `~/build/cmake` and your repository exists at
`~/src/cmake-cpp-template`, navigate to `~/build/cmake` and run 
`cmake -Bcmake-template ~/src/cmake-cpp-template`.

The -B option specifies the name of the desired build directory, and will create
it if it does not exist. CMake will then run the configuration step based on the
`CMakeLists.txt` found in the specified source directory. As CMake is a build
system *generator*, not a build system, the configuration step is when CMake
generates the actual build system. If not specified, CMake will use the system
default build tool (e.g. GNU Make for Linux systems).

Change directory into the newly created build directory. Assuming your build
tool is GNU Make, simply run `make` to build all targets. This will build a C++
static library `foo`, a unit test executable `test_factorial`, and a main
executable `fooapp`.

The main executable will reside inside the `app` directory, while the library
will reside inside `lib`. To run the tests using ctest, change directory into
`lib` and run `ctest`.

If Doxygen is installed and available to CMake on your system, HTML
documentation will also be produced inside `html`.

# Extending
The directory structure of the template is designed to be highly modular and
easily scalable as a project grows. The `CMakeLists.txt` files are heavily
commented to give an understanding as to how to configure CMake, and give an
idea of how to tailor it to fit your needs.

When searching for information about CMake online, ensure the advice given is
for *modern* CMake. There exist many examples of projects using old CMake
commands such as `include_directories`. These commands should not be used in new
CMake projects, instead target-based commands (`target_include_directories`)
should be preferred. The most up-to-date documentation on CMake can be found
[here](https://cmake.org/cmake/help/latest/).

```
.
├── app                            
│   ├── CMakeLists.txt             CMake configuration for application
│   └── src                        Application source code
│       └── main.cpp
├── CMakeLists.txt                 Main CMake configuration file
├── docs                           Doxygen configuration and files
│   └── Doxyfile.in
├── lib
│   ├── CMakeLists.txt             CMake configuration for library
│   ├── include                    Public include directory
│   │   └── foo
│   │       └── foo.h
│   ├── src                        Library source code
│   │   ├── foo.cpp
│   │   └── include                Private include directory
│   │       └── private
│   └── test
│       ├── CMakeLists.txt         CMake configuration for library tests
│       ├── include                Test util library include directory
│       │   └── test
│       │       └── util.h
│       └── test_factorial.cpp     Test cases
└── README.md
```
