cmake-cpputest
==============

Skeleton project for development in embedded C using the approach outlined in [Test Driven Development for Emedded C](http://pragprog.com/book/jgade/test-driven-development-for-embedded-c) with testing done via [CppUTest](http://cpputest.org/) and build done using [CMake](http://cmake.org/)

The demo source code used here (e.g. `LedDriver` example) was taken from the code from the book [Test Driven Development for Emedded C](http://pragprog.com/book/jgade/test-driven-development-for-embedded-c).  There isn't very much code, but I just used it as a simple demonstration of a cross-platform build environment that promotes tdd in embedded c.

**Goals**
* Support dual targeting...*not yet, still just targeting dev machine*
* Support cross-compiler builds...*not yet, soon*
* Support build platform independence...*only tested on Mac OSX; probably works fine on Linux; theoretically should work on Windows with CMake -- who knows*
* Provide a _good_ environment for getting started on a new project...*getting there - unit test framework is integrated*
* Out Of Source Build...*CHECK*

Why?  I want a cross-platform skeleton project that allows me to quickly start building something on any machine: Linux, Windows, Mac for C or C++.  I want good test support for it.  I want to be able to cross-compile for embedded targets -- although this I will probably do with a branch.

## pre-requisites
_NOTE_ I'm using Mac OSX and [homebrew](http://mxcl.github.com/homebrew/) which makes installation a bit simpler.  I also use [Sublime Text 2](http://www.sublimetext.com/2) as my editor along with the [SublimeClang plugin](https://github.com/quarnster/SublimeClang).  I've already configured the `cmake-tddc.sublime-project` file so stuff "should just work" in the editor (including intellisense and auto-compilation on save).

Assume the basic GNU toolchain (i.e. make, gcc, g++, etc.)

### Install [CMake](http://cmake.org)

With homebrew: `brew install cmake`
With aptitude: `sudo apt-get cmake`

Useful links:
* [CMake Manual](http://cmake.org/cmake/help/v2.8.9/cmake.html)
* [CMake Wiki](http://www.itk.org/Wiki/CMake)
* [CMake Mailing List](http://cmake.3232098.n2.nabble.com/)

### Install [CppUTest](http://cpputest.org)

With git: `git clone git://github.com/cpputest/cpputest.git && cd cpputest && make` 
With homebrew: `brew install cpputest`

Now, create an environment variable that points to it.  Add the following line to `.bash_profile` or similar: `export CPPUTEST_HOME=/path/to/cpputest`

### Build
```sh
$ mkdir build && cd build
$ cmake ..
$ make
```

### Run Tests
```sh
~/git/cmake-cpputest$ cd build && ./bin/RunAllTests

/Users/davis/git/cmake-cpputest/tests/LedDriver/LedDriverTest.cpp:26: error: Failure in TEST(LedDriver, FirstTest)
  Start here

.
Errors (1 failures, 1 tests, 1 ran, 0 checks, 0 ignored, 0 filtered out, 0 ms)
```

Test fails b/c I call the `FAIL` macro - so the environment is setup ok.