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

### Steps

Open a terminal and enter a Fuel direcotry, then type the following.

```
cd build/windows
./setup.sh          # This will install build dependencies. First time only.
./build-libs.sh     # This will build libraries. First time only.
make
```

A file named `fuel.exe` will be built.

## Linux

### Prerequisite

* A Linux machine
* `Ubuntu` or `Debian` installed
* `GNU Make` installed

### Steps

Open a terminal and enter a Fuel direcotry, then type the following.

```
cd build/linux
make setup          # This will install build dependencies. First time only.
make
```

A file named `fuel` will be built.

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
cd build/freebsd
make setup          # This will install build dependencies. First time only.
make
```

A file named `fuel` will be built.

## NetBSD

### Prerequisite

* A `NetBSD` machine
* `elfctl` installed (by pkg_add)

Note that `elfctl` is a build dependency and not needed for a run.

### Steps

Open a terminal and enter a Fuel direcotry, then type the following.

```
cd build/netbsd
sudo make nproc          # This will create nproc script. First time only.
make
```

A file named `fuel` will be built.

## OpenBSD

### Prerequisite

* An `OpenBSD` machine
* `gtar` and `gmake` installed (by pkg_add)

Note that `gtar` and `gmake` are build dependencies and not needed for a run.

### Steps

Open a terminal and enter a Fuel direcotry, then type the following.

```
cd build/openbsd
sudo make nproc          # This will create nproc script. First time only.
make
```

A file named `fuel` will be built.
