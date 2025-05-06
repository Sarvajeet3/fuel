#!/bin/sh

rm -rf objs
mkdir objs
cd objs
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/lang/lexer.yy.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/lang/parser.tab.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/lang/ast.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/lang/hir.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/lang/lir.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/lang/runtime.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/lang/interpreter.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/lang/intrinsics.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/lang/jit-common.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/lang/jit-arm64.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/lang/jit-x86_64.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/lang/jit-x86.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -DMAIN2 -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/platform/x11main.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/platform/x11opengl.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/platform/x11softrender.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/platform/glrender.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/platform/asound.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/platform/gstplay.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/platform/stdfile.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/platform/image.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/platform/glyph.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/platform/wave.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/api.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/common.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/main.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/tag.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/vm.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/render.c
cc -c -DUSE_JIT -DUSE_TRANSLATION -DUSE_X11_OPENGL -I../../../src -I../libroot/include -O2 -g0 -ffast-math -ftree-vectorize -Wno-format-truncation -std=gnu11 ../../../src/translation.c
ar rcs ../libroot/lib/libfuel.a *.o
cd ..
rm -rf objs

rm -rf linux-src-$1
mkdir linux-src-$1
mkdir linux-src-$1/lib

cp linux-src/Makefile linux-src-$1/
cp linux-src/entry.c linux-src-$1/
cp ../../src/platform/icon.c linux-src-$1/
cp libroot/lib/libfuel.a linux-src-$1/lib/
cp libroot/lib/libbrotlicommon.a linux-src-$1/lib/
cp libroot/lib/libpng.a linux-src-$1/lib/
cp libroot/lib/libbrotlidec.a linux-src-$1/lib/
cp libroot/lib/libvorbis.a linux-src-$1/lib/
cp libroot/lib/libbz2.a linux-src-$1/lib/
cp libroot/lib/libvorbisfile.a linux-src-$1/lib/
cp libroot/lib/libfreetype.a linux-src-$1/lib/
cp libroot/lib/libwebp.a linux-src-$1/lib/
cp libroot/lib/libjpeg.a linux-src-$1/lib/
cp libroot/lib/libz.a linux-src-$1/lib/
cp libroot/lib/libogg.a linux-src-$1/lib/
