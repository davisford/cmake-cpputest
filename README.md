cmake-cpputest
==============

Skeleton project for development in embedded C using the approach outlined in [Test Driven Development for Emedded C](http://pragprog.com/book/jgade/test-driven-development-for-embedded-c) with testing done via [CppUTest](http://cpputest.org/) and build done using [CMake](http://cmake.org/)

The demo source code used here (e.g. `LedDriver` example) was taken from the code from the book [Test Driven Development for Emedded C](http://pragprog.com/book/jgade/test-driven-development-for-embedded-c).  There isn't very much code, but I just used it as a simple demonstration of a cross-platform build environment that promotes tdd in embedded c.

**Goals**
* Support dual targeting local dev machine + raspberry pi embedded target...*almost: need to cross-compile cpputest and I think it will be there*
* Support cross-compiler builds...*CHECK*
* Support build platform independence...*works on Mac OS X and Linux (see below).  have not tested Windows*
* Provide a _good_ environment for getting started on a new project...*getting there*
* Out Of Source Build...*CHECK*

Why?  I'm going to build a [Raspberry Pi](http://raspberrypi.org) project, and compiling on the target is painful for a lot of reasons.  I'd prefer to develop, build, & test on a development machine, but still have the capability of building and running tests on the target.  This setup ought to work similarly for any target - not just the Raspberry Pi.  You can use it and modify it to suit your needs.

I typically use Mac OS or Linux (Ubuntu) to develop with.  Technically this should port to Windows with something like Cygwin, but I haven't bothered to try.

## pre-requisites
_NOTE_ I'm using Mac OSX and [homebrew](http://mxcl.github.com/homebrew/) which makes installation a bit simpler.  I also use [Sublime Text 2](http://www.sublimetext.com/2) as my editor along with the [SublimeClang plugin](https://github.com/quarnster/SublimeClang).  I've already configured the `cmake-tddc.sublime-project` file so stuff "should just work" in the editor (including intellisense and auto-compilation on save).

Assume the basic GNU toolchain (i.e. make, gcc, g++, etc.)

### Install [CMake](http://cmake.org)

With homebrew (Mac): `brew install cmake`
With aptitude (Ubuntu): `sudo apt-get cmake`

Useful links:
* [CMake Manual](http://cmake.org/cmake/help/v2.8.9/cmake.html)
* [CMake Wiki](http://www.itk.org/Wiki/CMake)
* [CMake Mailing List](http://cmake.3232098.n2.nabble.com/)

### Install [CppUTest](http://cpputest.org)

With git: `git clone git://github.com/cpputest/cpputest.git && cd cpputest && make` 
With homebrew: `brew install cpputest`

Now, create an environment variable that points to it.  Add the following line to `.bash_profile` or similar: `export CPPUTEST_HOME=/path/to/cpputest`

#### Cross-Compile CppUTest for embedded target
_TODO_

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

### Cross-Compile for Raspberry Pi
I gave up trying to do this on the Mac.  It might be possible, but I couldn't find anything decent on how to setup Gnu compiler toolchain for the Arm/Pi hardware like there is for Linux.  So, the path I'm taking is to use Linux to cross-compile when I need to, but I can still develop and test on the Mac using tdd/mocks.  Only if I want to cross-compile for the Pi and push the binaries will I need to switch.

So, this step is for Ubuntu only; I grab the pre-built toolchain for Pi:

```
$ mkdir -p ~/git/raspberrypi/ && cd ~/git/raspberrypi
$ git clone git://github.com/raspberrypi/tools.git
```

Now, create an environment variable that points to the tools.  Add the following line to `.bashrc` or similar: `export PI_TOOLS_HOME=~/git/raspberrypi/tools`

_this is my path, yours may be different_

Now, edit the file `Toolchain-raspberrypi-arm.cmake` and make sure the paths are consistent with `$PI_TOOLS_HOME`.  This is the [cross-compiler configuration for CMake](http://www.cmake.org/Wiki/CMake_Cross_Compiling#The_toolchain_file).

In order to build, you'll also need to cross-compile a version of CppUTest **TODO**, and you'll have to override the environment variable `$CPPUTEST_HOME` with the Arm version of the library.

Build as follows (create a different build directory for the Arm stuff so we don't intermix them)
```sh
$ mkdir pibuild && cd pibuild
$ cmake -DCMAKE_TOOLCHAIN_FILE=../Toolchain-raspberrypi-arm.cmake ..
```

With fingers crossed, it will build ok.






