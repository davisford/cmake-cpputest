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
This is the approach I took.  It seemed easier than messing with the cross-compiler.  This is a one-time build, since the code for CppUTest will not change often.  I wanted to setup the `Emulator` anyway with QEMU, so it kills two birds with one stone.

Install [QEMU](http://wiki.qemu.org/Main_Page)
```sh
$ sudo apt-get install qemu qemu-system
```

Download the [Raspbian Wheezy Image](http://www.raspberrypi.org/downloads)
```sh
$ wget http://files.velocix.com/c1410/images/raspbian/2012-08-16-wheezy-raspbian/2012-08-16-wheezy-raspbian.zip
$ unzip ./2012-08-16-wheezy-raspbian.zip
```

Download the QEMU Kernel Image
```sh
$ wget http://xecdesign.com/downloads/linux-qemu/kernel-qemu
```

Launch the image.  Consult [QEMU docs](http://wiki.qemu.org/Manual) or [online tutorials](http://xecdesign.com/qemu-emulating-raspberry-pi-the-easy-way/) for tweaks.  I had to use the `-cpu arm1136-r2` target.

```sh
$ qemu-system-arm -kernel ./kernel-qemu -cpu arm1136-r2 -m 256 -M versatilepb -no-reboot -serial stdio -append "root=/dev/sda2 panic=1" -hda ./2012-08-16-wheezy-raspbian.img
```

Now, in the emulator, grab the source for CppUTest from git and build it

```sh
$ mkdir ~/git && cd ~/git
$ git clone git://github.com/cpputest/cpputest && cd cpputest
$ make
```

Now, kill the emulator, mount the filesystem and copy the library to the host.  Run `fdisk` to figure out the start sector.

```sh
$ mkdir -p /mnt/pi
$ fdisk -lu ./2012-08-16-wheezy-raspbian.img 

Disk ./2012-08-16-wheezy-raspbian.img: 1939 MB, 1939865600 bytes
255 heads, 63 sectors/track, 235 cylinders, total 3788800 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk identifier: 0x000108cb

                           Device Boot      Start         End      Blocks   Id  System
./2012-08-16-wheezy-raspbian.img1            8192      122879       57344    c  W95 FAT32 (LBA)
./2012-08-16-wheezy-raspbian.img2          122880     3788799     1832960   83  Linux

$ sudo mount -t ext4 -o loop,offset=$((512*122880)) ./2012-08-16-wheezy-raspbian.img /mnt/pi
```

Now, on the host, just copy the library over:

```sh
$ cp /mnt/pi/home/pi/git/cpputest/lib/libCppUTest.a .
$ sudo umount /mnt/pi
```

Now, you can create a directory for Arm CppUTest with the header files in `/include` dir and the library in `/lib` and update the environment variable `CPPUTEST_HOME` for CMake, and it should cross-compile successfully


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

In order to build, you'll also need to [cross-compile a version of CppUTest](#cross-compile-cpputest-for-embedded-target), and you'll have to override the environment variable `$CPPUTEST_HOME` with the Arm version of the library.

Build as follows (create a different build directory for the Arm stuff so we don't intermix them)
```sh
$ mkdir pibuild && cd pibuild
$ cmake -DCMAKE_TOOLCHAIN_FILE=../Toolchain-raspberrypi-arm.cmake ..
```

With fingers crossed, it will build ok.






