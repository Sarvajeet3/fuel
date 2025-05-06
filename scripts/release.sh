#!/bin/sh

set -eu

VERSION=`cat ReleaseNotes | head -n1 | cut -d ' ' -f 2`

echo Building version $VERSION

rm -rf fuel-$VERSION
mkdir fuel-$VERSION

#
# Windows
#

echo "Building for Windows."

mkdir -p fuel-$VERSION/windows
mkdir -p fuel-$VERSION/projects

# fuelcore.exe
cd build/win32 && make && cd ../..
cp build/win32/fuelcore.exe fuel-$VERSION/windows/fuelcore.exe

# fuelcore-arm64.exe
cd build/winarm64 && make && cd ../..
cp build/winarm64/fuelcore-arm64.exe fuel-$VERSION/windows/fuelcore-arm64.exe

# fuellang.exe
cd build/lang-cli && make clean && make CC=i686-w64-mingw32-gcc fuellang.exe && cd ../..
cp build/lang-cli/fuellang.exe fuel-$VERSION/windows/fuellang.exe

# fuelpack.exe
cd build/pack-cli && make clean && make CC=i686-w64-mingw32-gcc fuelpack.exe && cd ../..
cp build/pack-cli/fuelpack.exe fuel-$VERSION/windows/fuelpack.exe

# fuel.exe
cd build/fuel-cli && make clean && make CC=i686-w64-mingw32-gcc CPPFLAGS="-I../../src -DUSE_BINDIST" fuel.exe && cd ../..
cp build/fuel-cli/fuel.exe fuel-$VERSION/windows/fuel.exe

#
# macOS
#

echo "Building for macOS."

mkdir -p fuel-$VERSION/macos

# DMG
cd build/macos && make fuelcore.dmg && cd ../..
cp build/macos/fuelcore.dmg fuel-$VERSION/macos/fuelcore.dmg

# fuellang
cd build/lang-cli && make clean && make fuellang CC=clang CPPFLAGS="-I../../src" CFLAGS="-O2 -g0 -arch arm64 -arch x86_64 -isysroot `xcrun --sdk macosx --show-sdk-path`" && cd ../..
cp build/lang-cli/fuellang fuel-$VERSION/macos/fuellang

# fuelpack
cd build/pack-cli && make clean && make fuelpack CC=clang CPPFLAGS="-I../../src" CFLAGS="-O2 -g0 -arch arm64 -arch x86_64 -isysroot `xcrun --sdk macosx --show-sdk-path`" && cd ../..
cp build/pack-cli/fuelpack fuel-$VERSION/macos/fuelpack

# fuel
cd build/fuel-cli && make clean && make fuel CC=clang CPPFLAGS="-I../../src -DUSE_BINDIST" CFLAGS="-O2 -g0 -arch arm64 -arch x86_64 -isysroot `xcrun --sdk macosx --show-sdk-path`" && cd ../..
cp build/fuel-cli/fuel fuel-$VERSION/macos/fuel

#
# Linux x86_64
#

echo "Building for Linux x86_64."

mkdir -p fuel-$VERSION/linux-x86_64

cd build/linux && make clean && cd ../..
docker run --rm -it -v "$PWD":/src -w /src/build/linux ubuntu18-x86_64 make
docker run --rm -it -v "$PWD":/src -w /src/build/lang-cli ubuntu18-x86_64 make
docker run --rm -it -v "$PWD":/src -w /src/build/pack-cli ubuntu18-x86_64 make
docker run --rm -it -v "$PWD":/src -w /src/build/fuel-cli ubuntu18-x86_64 make CPPFLAGS="-I../../src -DUSE_BINDIST"
cp build/linux/fuelcore fuel-$VERSION/linux-x86_64/fuelcore
cp build/lang-cli/fuellang fuel-$VERSION/linux-x86_64/fuellang
cp build/pack-cli/fuelpack fuel-$VERSION/linux-x86_64/fuelpack
cp build/fuel-cli/fuel fuel-$VERSION/linux-x86_64/fuel

#
# Linux Arm64
#

echo "Building for Linux Arm64."

mkdir -p fuel-$VERSION/linux-arm64

cd build/linux && make clean && cd ../..
docker run --rm -it -v "$PWD":/src -w /src/build/linux ubuntu18-arm64 make
docker run --rm -it -v "$PWD":/src -w /src/build/lang-cli ubuntu18-arm64 make
docker run --rm -it -v "$PWD":/src -w /src/build/pack-cli ubuntu18-arm64 make
docker run --rm -it -v "$PWD":/src -w /src/build/fuel-cli ubuntu18-arm64 make CPPFLAGS="-I../../src -DUSE_BINDIST"
cp build/linux/fuelcore fuel-$VERSION/linux-arm64/fuelcore
cp build/lang-cli/fuellang fuel-$VERSION/linux-arm64/fuellang
cp build/pack-cli/fuelpack fuel-$VERSION/linux-arm64/fuelpack
cp build/fuel-cli/fuel fuel-$VERSION/linux-arm64/fuel

#
# iOS
#

echo "Building for iOS..."

mkdir -p fuel-$VERSION/projects

cd build/ios && make src && cd ../..
cp -R build/ios/ios-src fuel-$VERSION/projects/ios

#
# Android
#

echo "Building for Android..."

mkdir -p fuel-$VERSION/projects

cd build/android && make src && cd ../..
cp -R build/android/android-src fuel-$VERSION/projects/android

#
# Wasm
#

echo "Building for Wasm..."

mkdir -p fuel-$VERSION/projects/web

cd build/wasm && make && cd ../..
cp build/wasm/index.html fuel-$VERSION/projects/web/
cp build/wasm/index.js fuel-$VERSION/projects/web/
cp build/wasm/index.wasm fuel-$VERSION/projects/web/

#
# Sample
#

mkdir -p fuel-$VERSION/sample
mkdir -p fuel-$VERSION/sample/images

cp sample/main.fuel fuel-$VERSION/sample/
cp sample/images/apple.png fuel-$VERSION/sample/images/

#
# Documentation
#

echo "Building documentation..."

rm -rf documents
rm -f docs/*~

mkdocs build

# Re-link / to /index.html for local view.
find site -name "*.html" -exec sed -i '' -E 's#href="([^"]+)/"#href="\1/index.html"#g' {} +

mv site fuel-$VERSION/documentation

#
# Zip
#

cp README.md fuel-$VERSION/README.txt
echo '' >> fuel-$VERSION/README.txt
cat LICENSE >> fuel-$VERSION/README.txt
echo '' >> fuel-$VERSION/README.txt
cat ReleaseNotes >> fuel-$VERSION/README.txt

zip -r fuel-$VERSION.zip fuel-$VERSION
tar czf fuel-$VERSION.tar.gz fuel-$VERSION

#
# Upload
#

yes '' | gh release create "$VERSION" --title "$VERSION" --notes "" fuel-$VERSION.zip fuel-$VERSION.tar.gz

rm -rf fuel-$VERSION fuel-$VERSION.zip fuel-$VERSION.tar.gz
