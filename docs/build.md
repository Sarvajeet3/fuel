How To Build Fuel
==================

## Windows (Visual Studio)

### Prerequisite

* A `Windows 11` PC with an Intel, AMD, or Arm64 processor
* `Visual Studio 2022 Community` installed
* `Git for Windows` installed
* `Fuel` source tree downloaded

### Steps

Open the Visual Studio project at `fuel/build/visualstudio/visualstudio.sln`.
Build the project on Visual Studio.

### Limitation

Currently x64 binary fails to run because the JIT compiler generates
codes in the SYSV calling convention, not the Microsoft one.

## Windows (WSL2)

### Prerequisite

* A `Windows 11` PC with an Intel, AMD, or Arm64 processor
* `WSL2` environment installed
* `Ubuntu` or `Debian` installed
* Run the folowing:
```
sudo apt-get install mingw-w64
```

### Steps

Open a terminal and enter a Fuel direcotry, then type the following.

```
cd build/win32
make
```

## Windows (MSYS2)

### Prerequisite

* A `Windows 11` PC with an Intel, AMD, or Arm64 processor
* `MSYS2` environment installed

### Steps

Open a terminal and enter a Fuel direcotry, then type the following.

```
cd build/win32
make CC=gcc CXX=g++ LD=ld AR=ar STRIP=strip WINDRES=windres
```

## Linux

### Prerequisite

* A Linux machine
* `Ubuntu` or `Debian` installed
* `GNU Make` installed

On Debian or Ubuntu:
```
sudo apt-get install build-essential libx11-dev libxpm-dev mesa-common-dev libasound2-dev
```

On RedHat, Rocky Linux, Fedora, etc.:
```
sudo dnf install patch libX11-devel libXpm-devel alsa-lib-devel mesa-libGL-devel
```

### Steps

Open a terminal and enter a Fuel direcotry, then type the following.

```
./configure
make
sudo make install
```

## macOS

### Prerequisite

* A Mac with an Apple Silicon or Intel processor
* `macOS 15` installed
* `Xcode 16` installed

### Steps

First, open a terminal and enter a Fuel direcotry, then type the following.

```
cd build/macos
./build-libs.sh
```

The, open the Xcode project at `fuel/build/macos`, and build the project on Xcode.

## iOS

### Prerequisite

* A Mac with an Apple Silicon or Intel processor
* `macOS 15` installed
* `Xcode 16` installed

### Steps

First, open a terminal and enter a Fuel direcotry, then type the following.

```
cd build/ios
./build-libs.sh
make src
```

Then, open the Xcode project at `fuel/build/ios/ios-src`.
Build the project on Xcode.
Note that you need to copy game files into `Resources` folder.

## Android

### Prerequisite

* A machine with one of:
    * `Windows 11`
    * `macOS 15`
    * `Linux`
* `Android Studio`

### Steps

First, open a terminal and enter a Fuel direcotry, then type the following.

```
cd build/android
make src
```

Then, open the Android Studio project at `fuel/build/android/android-src`.
Build the project on Android Studio.
Note that you need to copy game files into `assets` folder.

## FreeBSD

### Prerequisite

* A `FreeBSD` machine

### Steps

Open a terminal and enter a Fuel direcotry, then type the following.

```
./configure
make
sudo make install
```

## NetBSD

### Prerequisite

* A `NetBSD` machine

### Steps

Open a terminal and enter a Fuel direcotry, then type the following.

```
./configure
make
sudo make install
```

## OpenBSD

### Prerequisite

* An `OpenBSD` machine
* `gtar` and `gmake` installed (by pkg_add)

Note that `gtar` and `gmake` are build dependencies and not needed for a run.

### Steps

Open a terminal and enter a Fuel direcotry, then type the following.

```
./configure
make
sudo make install
```
