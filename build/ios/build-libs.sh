#!/bin/sh

set -eu

rm -rf objs ios/libfuel.a libfuel-arm64.a libfuel-x86_64.a ios/libfuel-device.a ios/libfuel-sim.a

#####################################
echo 'Building arm64 device library.'

echo 'Stage1.'
if [ ! -d libroot-device ]; then
    IPHONEOS_DEPLOYMENT_TARGET=13.0 ../../lib/build-libs.sh device clang "-O2 -g0 -arch arm64 -isysroot `xcrun -sdk iphoneos --show-sdk-path` -fembed-bitcode -mios-version-min=13.0" ar;
fi

echo 'Stage2.'
mkdir -p objs
cd objs
IPHONEOS_DEPLOYMENT_TARGET=13.0 clang \
    -c \
    -arch arm64 \
    -fmodules \
    -I../../../src \
    -I../libroot-device/include \
    -I/System/Library/Frameworks \
    -DUSE_TRANSLATION \
    -O2 \
    -g0 \
    -target arm64-apple-ios13.0 \
    -isysroot `xcrun -sdk iphoneos --show-sdk-path` \
    -fembed-bitcode \
    -mios-version-min=13.0 \
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
    ../../../src/platform/stdfile.c \
    ../../../src/platform/image.c \
    ../../../src/platform/aunit.c \
    ../../../src/platform/glyph.c \
    ../../../src/platform/wave.c \
    ../../../src/platform/uimain.m \
    ../../../src/platform/GameRenderer.m \
    ../../../src/api.c \
    ../../../src/main.c \
    ../../../src/tag.c \
    ../../../src/vm.c \
    ../../../src/common.c \
    ../../../src/render.c \
    ../../../src/sound.c \
    ../../../src/font.c \
    ../../../src/translation.c

ar x ../libroot-device/lib/libpng.a
ar x ../libroot-device/lib/libjpeg.a
ar x ../libroot-device/lib/libwebp.a
ar x ../libroot-device/lib/libfreetype.a
ar x ../libroot-device/lib/libvorbisfile.a
ar x ../libroot-device/lib/libvorbis.a
ar x ../libroot-device/lib/libogg.a
ar x ../libroot-device/lib/libbrotlidec.a
ar x ../libroot-device/lib/libbrotlicommon.a
ar x ../libroot-device/lib/libbz2.a
ar x ../libroot-device/lib/libz.a
ar rcs ../ios/libfuel-device.a *.o
cd ..
rm -rf objs

########################################
echo 'Building arm64 simulator library.'

echo 'Stage1.'
if [ ! -d libroot-sim-arm64 ]; then
    IPHONEOS_DEPLOYMENT_TARGET=13.0 ../../lib/build-libs.sh sim-arm64 clang "-O2 -g0 -arch arm64 -isysroot `xcrun -sdk iphonesimulator --show-sdk-path`" ar;
fi

echo 'Stage2.'
mkdir -p objs
cd objs
IPHONEOS_DEPLOYMENT_TARGET=13.0 clang \
    -c \
    -arch arm64 \
    -fmodules \
    -I../../../src \
    -I../libroot-sim-arm64/include \
    -I/System/Library/Frameworks \
    -DUSE_TRANSLATION \
    -O2 \
    -g0 \
    -isysroot `xcrun -sdk iphonesimulator --show-sdk-path` \
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
    ../../../src/platform/stdfile.c \
    ../../../src/platform/image.c \
    ../../../src/platform/aunit.c \
    ../../../src/platform/glyph.c \
    ../../../src/platform/wave.c \
    ../../../src/platform/uimain.m \
    ../../../src/platform/GameRenderer.m \
    ../../../src/api.c \
    ../../../src/main.c \
    ../../../src/tag.c \
    ../../../src/vm.c \
    ../../../src/common.c \
    ../../../src/render.c \
    ../../../src/sound.c \
    ../../../src/font.c \
    ../../../src/translation.c
ar x ../libroot-sim-arm64/lib/libpng.a
ar x ../libroot-sim-arm64/lib/libjpeg.a
ar x ../libroot-sim-arm64/lib/libwebp.a
ar x ../libroot-sim-arm64/lib/libfreetype.a
ar x ../libroot-sim-arm64/lib/libvorbisfile.a
ar x ../libroot-sim-arm64/lib/libvorbis.a
ar x ../libroot-sim-arm64/lib/libogg.a
ar x ../libroot-sim-arm64/lib/libbrotlidec.a
ar x ../libroot-sim-arm64/lib/libbrotlicommon.a
ar x ../libroot-sim-arm64/lib/libbz2.a
ar x ../libroot-sim-arm64/lib/libz.a
ar rcs ../libfuel-sim-arm64.a *.o
cd ..
rm -rf objs

#########################################
echo 'Building x86_64 simulator library.'

echo 'Stage1.'
if [ ! -d libroot-sim-x86_64 ]; then
    IPHONEOS_DEPLOYMENT_TARGET=13.0 ../../lib/build-libs.sh sim-x86_64 clang "-O2 -g0 -arch x86_64 -isysroot `xcrun -sdk iphonesimulator --show-sdk-path`" ar;
fi

echo 'Stage2.'
mkdir -p objs
cd objs
IPHONEOS_DEPLOYMENT_TARGET=13.0 clang \
    -c \
    -arch x86_64 \
    -fmodules \
    -I../../../src \
    -I../libroot-sim-x86_64/include \
    -I/System/Library/Frameworks \
    -DUSE_TRANSLATION \
    -O2 \
    -g0 \
    -isysroot `xcrun -sdk iphonesimulator --show-sdk-path` \
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
    ../../../src/platform/stdfile.c \
    ../../../src/platform/image.c \
    ../../../src/platform/aunit.c \
    ../../../src/platform/glyph.c \
    ../../../src/platform/wave.c \
    ../../../src/platform/uimain.m \
    ../../../src/platform/GameRenderer.m \
    ../../../src/api.c \
    ../../../src/main.c \
    ../../../src/tag.c \
    ../../../src/vm.c \
    ../../../src/common.c \
    ../../../src/render.c \
    ../../../src/sound.c \
    ../../../src/font.c \
    ../../../src/translation.c
ar x ../libroot-sim-x86_64/lib/libpng.a
ar x ../libroot-sim-x86_64/lib/libjpeg.a
ar x ../libroot-sim-x86_64/lib/libwebp.a
ar x ../libroot-sim-x86_64/lib/libfreetype.a
ar x ../libroot-sim-x86_64/lib/libvorbisfile.a
ar x ../libroot-sim-x86_64/lib/libvorbis.a
ar x ../libroot-sim-x86_64/lib/libogg.a
ar x ../libroot-sim-x86_64/lib/libbrotlidec.a
ar x ../libroot-sim-x86_64/lib/libbrotlicommon.a
ar x ../libroot-sim-x86_64/lib/libbz2.a
ar x ../libroot-sim-x86_64/lib/libz.a
ar rcs ../libfuel-sim-x86_64.a *.o
cd ..
rm -rf objs

##################################################
echo 'Merging into a simulator Univeral Binary...'

lipo -create libfuel-sim-arm64.a libfuel-sim-x86_64.a -output ios/libfuel-sim.a

#rm -rf objs libfuel-sim-arm64.a libfuel-sim-x86_64.a
