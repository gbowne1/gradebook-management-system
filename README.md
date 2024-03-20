# Gradebook Management System

This is a C++ Gradebook Management System for the Kindergarten and 1st through 12th Grades.

[![C++](https://img.shields.io/badge/C++-00599C?logo=C%2B%2B&logoColor=white&style=flat-square)](https://en.cppreference.com/)

## Features

- Load students, teachers, assignments, classes and grades from CSV files
- View and modify loaded data
- Save students and grades to CSV files

## Getting Started

This step describes the prerequisites and install steps for the libraries needed to build and run the project.

### Prerequisites

- [CMake](https://cmake.org/) - v3.14+
- C++ Compiler - C++ 14+ - Currently tested with [g++](https://gcc.gnu.org/) only
- [Google Test](https://github.com/google/googletest) - Only needed for linting, as CMake fetches Google Test automatically during build
- Operating system - Currently the following operating systems are supported: [Ubuntu](https://ubuntu.com/download) and [Debian](https://www.debian.org/index.en.html)

### Installing

Currently, there are no install steps that are strictly necessary. However, if you wish to include Google Test in your local library, you may do so by following these steps:

```sh
git clone https://github.com/google/googletest.git
cd googletest
cmake -B build .
cd build
cmake --build .
cmake --install .
```

## Building the project

This project is built using CMake and Make. Here is an example on how to build the project:

```sh
cmake -B build .
cd build
make
```

And then run the executable:

```sh
cd gradebook
./gradebook
```

## Generating the documentation

The documentation can be generated with Doxygen in the HTML and LaTeX formats. In order to do so, you must first install Doxygen and Graphviz:
```sh
# Ubuntu 22.04
sudo apt-add-repository universe
sudo apt-get update
sudo apt-get install doxygen
sudo apt-get install graphviz
```

Then run Doxygen:
```sh
doxygen doxygen.conf
```

Two folders named `html` and `latex` should appear.

## Running the tests

This project uses [Google Test](https://github.com/google/googletest) for unit testing. In order to run unit tests, the flag `-DTESTING=ON` must be passed to the CMake command. Here is an example on how to build and run tests:

```sh
# Build with CMake and Make
cmake -DTESTING=ON -B build .
cd build
make
# Run tests
cd tests
./gradebook_test [--gtest_filter=...]
```

## Contributing

Please see the [Contributing](.github/CONTRIBUTING.md) file for more information.

## Versioning

Versioning is not available for this project yet.

## Authors

- Gregory Bowne - [@gbowne1](https://github.com/gbowne1)

## License

This project is licensed under the [MIT License](https://opensource.org/license/mit) - see the [LICENSE](LICENSE) file for details.
