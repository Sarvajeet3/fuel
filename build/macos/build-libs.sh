#!/bin/sh

set -eu

rm -rf objs libroot libroot-arm64 libroot-x86_64

#####################################
echo 'Building arm64 libraries..'

echo 'Stage1.'
if [ ! -d libroot-arm64 ]; then
    MACOSX_DEPLOYMENT_TARGET=10.13 ../../lib/build-libs.sh "arm64" clang "-O2 -g0 -arch arm64 -isysroot `xcrun --sdk macosx --show-sdk-path`" ar;
fi

echo 'Stage2.'
mkdir -p objs
cd objs
MACOSX_DEPLOYMENT_TARGET=10.13 clang \
    -c \
    -fmodules \
    -arch arm64 \
    -target arm64-apple-macos10.13 \
    -isysroot `xcrun --sdk macosx --show-sdk-path` \
    -mmacosx-version-min=10.13 \
    -I`xcrun --sdk macosx --show-sdk-path`/include \
    -I../../../src \
    -I../libroot-arm64/include \
    -I/System/Library/Frameworks \
    -DUSE_JIT \
    -DUSE_MAIN2 \
    -DUSE_TRANSLATION \
    -O2 \
    -g0 \
    -ffast-math \
    -ftree-vectorize \
    -std=gnu11 \
    -Wno-sign-conversion \
    -Wno-sign-compare \
    -Wno-conversion \
    -Wno-multichar \
    -Wno-strict-aliasing \
    -Wno-deprecated-declarations \
    ../../../src/lang/lexer.yy.c \
    ../../../src/lang/parser.tab.c \
    ../../../src/lang/ast.c \
    ../../../src/lang/hir.c \
    ../../../src/lang/lir.c \
    ../../../src/lang/runtime.c \
    ../../../src/lang/interpreter.c \
    ../../../src/lang/intrinsics.c \
    ../../../src/lang/jit-common.c \
    ../../../src/lang/jit-arm64.c \
    ../../../src/lang/jit-x86_64.c \
    ../../../src/platform/stdfile.c \
    ../../../src/platform/image.c \
    ../../../src/platform/aunit.c \
    ../../../src/platform/glyph.c \
    ../../../src/platform/wave.c \
    ../../../src/platform/nsmain.m \
    ../../../src/platform/GameRenderer.m \
    ../../../src/api.c \
    ../../../src/main.c \
    ../../../src/tag.c \
    ../../../src/vm.c \
    ../../../src/common.c \
    ../../../src/render.c \
    ../../../src/translation.c
ar rcs ../libroot-arm64/lib/libfuel.a *.o
cd ..
rm -rf objs

#####################################
echo 'Building x86_64 libraries..'

echo 'Stage1.'
if [ ! -d libroot-x86_64 ]; then
    MACOSX_DEPLOYMENT_TARGET=10.13 ../../lib/build-libs.sh "x86_64" clang "-O2 -g0 -arch x86_64 -isysroot `xcrun --sdk macosx --show-sdk-path`" ar
fi

echo 'Stage2.'
mkdir -p objs
cd objs
MACOSX_DEPLOYMENT_TARGET=10.13 clang \
    -c \
    -fmodules \
    -arch x86_64 \
    -target x86_64-apple-macos10.13 \
    -isysroot `xcrun --sdk macosx --show-sdk-path` \
    -mmacosx-version-min=10.13 \
    -I`xcrun --sdk macosx --show-sdk-path`/include \
    -I../../../src \
    -I../libroot-x86_64/include \
    -I/System/Library/Frameworks \
    -DUSE_JIT \
    -DUSE_MAIN2 \
    -DUSE_TRANSLATION \
    -O2 \
    -g0 \
    -ffast-math \
    -ftree-vectorize \
    -std=gnu11 \
    -Wno-sign-conversion \
    -Wno-sign-compare \
    -Wno-conversion \
    -Wno-multichar \
    -Wno-strict-aliasing \
    -Wno-deprecated-declarations \
    ../../../src/lang/lexer.yy.c \
    ../../../src/lang/parser.tab.c \
    ../../../src/lang/ast.c \
    ../../../src/lang/hir.c \
    ../../../src/lang/lir.c \
    ../../../src/lang/runtime.c \
    ../../../src/lang/interpreter.c \
    ../../../src/lang/intrinsics.c \
    ../../../src/lang/jit-common.c \
    ../../../src/lang/jit-arm64.c \
    ../../../src/lang/jit-x86_64.c \
    ../../../src/platform/stdfile.c \
    ../../../src/platform/image.c \
    ../../../src/platform/aunit.c \
    ../../../src/platform/glyph.c \
    ../../../src/platform/wave.c \
    ../../../src/platform/nsmain.m \
    ../../../src/platform/GameRenderer.m \
    ../../../src/api.c \
    ../../../src/main.c \
    ../../../src/tag.c \
    ../../../src/vm.c \
    ../../../src/common.c \
    ../../../src/render.c \
    ../../../src/translation.c
ar rcs ../libroot-x86_64/lib/libfuel.a *.o
cd ..
rm -rf objs

#####################################
echo 'Merging into Univeral Binary libraries...'

mkdir libroot
mkdir libroot/lib
cp -R libroot-arm64/include libroot/include

lipo -create libroot-arm64/lib/libfuel.a libroot-x86_64/lib/libfuel.a -output libroot/lib/libfuel.a
lipo -create libroot-arm64/lib/libpng.a libroot-x86_64/lib/libpng.a -output libroot/lib/libpng.a
lipo -create libroot-arm64/lib/libjpeg.a libroot-x86_64/lib/libjpeg.a -output libroot/lib/libjpeg.a
lipo -create libroot-arm64/lib/libwebp.a libroot-x86_64/lib/libwebp.a -output libroot/lib/libwebp.a
lipo -create libroot-arm64/lib/libfreetype.a libroot-x86_64/lib/libfreetype.a -output libroot/lib/libfreetype.a
lipo -create libroot-arm64/lib/libvorbisfile.a libroot-x86_64/lib/libvorbisfile.a -output libroot/lib/libvorbisfile.a
lipo -create libroot-arm64/lib/libvorbis.a libroot-x86_64/lib/libvorbis.a -output libroot/lib/libvorbis.a
lipo -create libroot-arm64/lib/libogg.a libroot-x86_64/lib/libogg.a -output libroot/lib/libogg.a
lipo -create libroot-arm64/lib/libbrotlidec.a libroot-x86_64/lib/libbrotlidec.a -output libroot/lib/libbrotlidec.a
lipo -create libroot-arm64/lib/libbrotlicommon.a libroot-x86_64/lib/libbrotlicommon.a -output libroot/lib/libbrotlicommon.a
lipo -create libroot-arm64/lib/libbz2.a libroot-x86_64/lib/libbz2.a -output libroot/lib/libbz2.a
lipo -create libroot-arm64/lib/libz.a libroot-x86_64/lib/libz.a -output libroot/lib/libz.a

rm -rf objs libroot-arm64 libroot-x86_64
