#!/bin/sh

if [ ! -d libroot ]; then
    ./build-libs.sh;
fi

echo '[x86]'
rm -rf objs
mkdir objs
cd objs
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/main.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/api.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/tag.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/vm.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/common.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/render.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/sound.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/font.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DWINMAIN2 /I../../../src /I../../win32/res ../../../src/platform/winmain.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/platform/d3drender.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src /I../dx12headers/include/directx ../../../src/platform/d3d12render.cc
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/platform/d3d11render.cc
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/platform/d3d9render.cc
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/platform/gdirender.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/platform/dsound.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/platform/dsvideo.cc
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/platform/stdfile.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src /I../libroot/include ../../../src/platform/glyph.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src /I../libroot/include ../../../src/platform/wave.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../src /I../libroot/include ../../../src/platform/image.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../src ../../../src/platform/cpuid.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../src ../../../src/platform/scalar.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../src /arch:SSE ../../../src/platform/sse.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../src /arch:SSE2 ../../../src/platform/sse2.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../src /arch:AVX  ../../../src/platform/avx.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../src /arch:AVX2 ../../../src/platform/avx2.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /DYY_NO_UNISTD_H /I../../../src ../../../src/lang/lexer.yy.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/parser.tab.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/ast.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/hir.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/lir.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/runtime.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/interpreter.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/intrinsics.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/jit-common.c
x86-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/jit-x86.c
cd ..
x86-lib.exe /nologo /OUT:libroot/lib-x86/libfuel.lib objs/main.obj objs/api.obj objs/tag.obj objs/vm.obj objs/common.obj objs/render.obj objs/sound.obj objs/font.obj objs/winmain.obj objs/d3drender.obj objs/d3d12render.obj objs/d3d11render.obj objs/d3d9render.obj objs/gdirender.obj objs/dsound.obj objs/dsvideo.obj objs/stdfile.obj objs/image.obj objs/glyph.obj objs/wave.obj objs/cpuid.obj objs/scalar.obj objs/sse.obj objs/sse2.obj objs/avx.obj objs/avx2.obj objs/lexer.yy.obj objs/parser.tab.obj objs/ast.obj objs/hir.obj objs/lir.obj objs/runtime.obj objs/interpreter.obj objs/intrinsics.obj objs/jit-common.obj objs/jit-x86.obj

echo '[x64]'
rm -rf objs
mkdir objs
cd objs
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/main.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/api.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/tag.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/vm.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/common.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/render.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/sound.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/font.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DWINMAIN2 /I../../../src /I../../win32/res ../../../src/platform/winmain.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/platform/d3drender.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src /I../dx12headers/include/directx ../../../src/platform/d3d12render.cc
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/platform/d3d11render.cc
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/platform/d3d9render.cc
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/platform/gdirender.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/platform/dsound.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/platform/dsvideo.cc
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/platform/stdfile.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src /I../libroot/include ../../../src/platform/glyph.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src /I../libroot/include ../../../src/platform/wave.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../src /I../libroot/include ../../../src/platform/image.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../src ../../../src/platform/cpuid.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../src ../../../src/platform/scalar.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../src /arch:SSE2 ../../../src/platform/sse2.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../src /arch:AVX  ../../../src/platform/avx.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_SSE_DISPATCH /I../../../src /arch:AVX2 ../../../src/platform/avx2.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /DYY_NO_UNISTD_H /I../../../src ../../../src/lang/lexer.yy.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/parser.tab.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/ast.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/hir.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/lir.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/runtime.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/interpreter.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/intrinsics.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/jit-common.c
x64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/jit-x86_64.c
cd ..
x64-lib.exe /nologo /OUT:libroot/lib-x64/libfuel.lib objs/main.obj objs/api.obj objs/tag.obj objs/vm.obj objs/common.obj objs/render.obj objs/sound.obj objs/font.obj objs/winmain.obj objs/d3drender.obj objs/d3d12render.obj objs/d3d11render.obj objs/d3d9render.obj objs/gdirender.obj objs/dsound.obj objs/dsvideo.obj objs/stdfile.obj objs/image.obj objs/glyph.obj objs/wave.obj objs/cpuid.obj objs/scalar.obj objs/sse2.obj objs/avx.obj objs/avx2.obj objs/lexer.yy.obj objs/parser.tab.obj objs/ast.obj objs/hir.obj objs/lir.obj objs/runtime.obj objs/interpreter.obj objs/intrinsics.obj objs/jit-common.obj objs/jit-x86_64.obj

echo '[arm64]'
rm -rf objs
mkdir objs
cd objs
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/main.c
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/api.c
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/tag.c
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/vm.c
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/common.c
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/render.c
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/sound.c
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/font.c
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DWINMAIN2 /I../../../src /I../../win32/res ../../../src/platform/winmain.c
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/platform/d3drender.c
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src /I../dx12headers/include/directx ../../../src/platform/d3d12render.cc
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/platform/d3d11render.cc
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/platform/d3d9render.cc
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/platform/gdirender.c
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/platform/dsound.c
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/platform/dsvideo.cc
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src ../../../src/platform/stdfile.c
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src /I../libroot/include ../../../src/platform/glyph.c
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src /I../libroot/include ../../../src/platform/wave.c
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /I../../../src /I../libroot/include ../../../src/platform/image.c
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /DYY_NO_UNISTD_H /I../../../src ../../../src/lang/lexer.yy.c
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/parser.tab.c
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/ast.c
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/hir.c
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/lir.c
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/runtime.c
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/interpreter.c
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/intrinsics.c
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/jit-common.c
arm64-cl.exe /nologo /c /MT /O2 /DUNICODE /D_UNICODE /DUSE_JIT /I../../../src ../../../src/lang/jit-arm64.c
cd ..
arm64-lib.exe /nologo /OUT:libroot/lib-arm64/libfuel.lib objs/main.obj objs/api.obj objs/tag.obj objs/vm.obj objs/common.obj objs/render.obj objs/sound.obj objs/font.obj objs/winmain.obj objs/d3drender.obj objs/d3d12render.obj objs/d3d11render.obj objs/d3d9render.obj objs/gdirender.obj objs/dsound.obj objs/dsvideo.obj objs/stdfile.obj objs/image.obj objs/glyph.obj objs/wave.obj objs/lexer.yy.obj objs/parser.tab.obj objs/ast.obj objs/hir.obj objs/lir.obj objs/runtime.obj objs/interpreter.obj objs/intrinsics.obj objs/jit-common.obj objs/jit-arm64.obj

rm -rd vs-src/lib
mkdir vs-src/lib

cp libroot/lib-x86/libfuel.lib vs-src/lib/
cp libroot/lib-x86/zlib.lib vs-src/lib/
cp libroot/lib-x86/libpng.lib vs-src/lib/
cp libroot/lib-x86/jpeg.lib vs-src/lib/
cp libroot/lib-x86/libbz2.lib vs-src/lib/
cp libroot/lib-x86/libwebp.lib vs-src/lib/
cp libroot/lib-x86/libogg.lib vs-src/lib/
cp libroot/lib-x86/libvorbis.lib vs-src/lib/
cp libroot/lib-x86/freetype.lib vs-src/lib/

cp libroot/lib-x64/libfuel.lib vs-src/lib/
cp libroot/lib-x64/zlib.lib vs-src/lib/
cp libroot/lib-x64/libpng.lib vs-src/lib/
cp libroot/lib-x64/jpeg.lib vs-src/lib/
cp libroot/lib-x64/libbz2.lib vs-src/lib/
cp libroot/lib-x64/libwebp.lib vs-src/lib/
cp libroot/lib-x64/libogg.lib vs-src/lib/
cp libroot/lib-x64/libvorbis.lib vs-src/lib/
cp libroot/lib-x64/freetype.lib vs-src/lib/

cp libroot/lib-arm64/libfuel.lib vs-src/lib/
cp libroot/lib-arm64/zlib.lib vs-src/lib/
cp libroot/lib-arm64/libpng.lib vs-src/lib/
cp libroot/lib-arm64/jpeg.lib vs-src/lib/
cp libroot/lib-arm64/libbz2.lib vs-src/lib/
cp libroot/lib-arm64/libwebp.lib vs-src/lib/
cp libroot/lib-arm64/libogg.lib vs-src/lib/
cp libroot/lib-arm64/libvorbis.lib vs-src/lib/
cp libroot/lib-arm64/freetype.lib vs-src/lib/

rm -rf vs-src/res
mkdir vs-src/res
cp ../win32/res/icon.ico vs-src/res/
cp ../win32/res/manifest.xml vs-src/res/
cp ../win32/res/resource.h vs-src/res/
cp ../win32/res/resource.rc vs-src/res/

