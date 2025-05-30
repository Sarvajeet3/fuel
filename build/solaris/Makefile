CC=cc
LD=ld
AR=ar
STRIP=strip

CPPFLAGS=\
	-DUSE_TRANSLATION \
	-DUSE_X11_SOFTRENDER \
	-I../../src \
	-I./libroot-solaris/include \
	-I./libroot-solaris/include/png \
	-I./libroot-solaris/include/freetype \
	-I/usr/local/include \
	-I/usr/X11R6/include

CFLAGS=\
	-O2 \
	-g0 \
	-std=gnu11

LDFLAGS=\
	-lpthread \
	-lm \
	-L/usr/X11R6/lib \
	-lX11 \
	-lXpm \
	./libroot-solaris/lib/libpng.a \
	./libroot-solaris/lib/libjpeg.a \
	./libroot-solaris/lib/libwebp.a \
	./libroot-solaris/lib/libfreetype.a \
	./libroot-solaris/lib/libbz2.a \
	./libroot-solaris/lib/libz.a \
	./libroot-solaris/lib/libbrotlidec.a \
	./libroot-solaris/lib/libbrotlicommon.a \
	./libroot-solaris/lib/libvorbisfile.a \
	./libroot-solaris/lib/libvorbis.a \
	./libroot-solaris/lib/libogg.a

OBJS_LANG=\
	objs/lexer.yy.o \
	objs/parser.tab.o \
	objs/ast.o \
	objs/hir.o \
	objs/lir.o \
	objs/runtime.o \
	objs/interpreter.o \
	objs/intrinsics.o \
	objs/jit-common.o

OBJS_PLATFORM=\
	objs/x11main.o \
	objs/x11softrender.o \
	objs/icon.o \
	objs/glrender.o \
	objs/bsdsound.o \
	objs/gstplay.o \
	objs/stdfile.o \
	objs/image.o \
	objs/glyph.o \
	objs/wave.o

OBJS_ENGINE=\
	objs/api.o \
	objs/common.o \
	objs/tag.o \
	objs/vm.o \
	objs/render.o \
	objs/sound.o \
	objs/font.o \
	objs/main.o

OBJS_TOP=\
	objs/translation.o

#
# Main Target
#

all: fuel

fuel: $(OBJS_LANG) $(OBJS_PLATFORM) $(OBJS_ENGINE) $(OBJS_TOP)
	$(CC) -o fuel $(CFLAGS) $(OBJS_LANG) $(OBJS_PLATFORM) $(OBJS_ENGINE) $(OBJS_TOP) $(LDFLAGS)

#
# src/language
#

objs/lexer.yy.o: ../../src/lang/lexer.yy.c
	@mkdir -p objs
	$(CC) -c -o objs/lexer.yy.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/lexer.yy.c

objs/parser.tab.o: ../../src/lang/parser.tab.c
	@mkdir -p objs
	$(CC) -c -o objs/parser.tab.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/parser.tab.c

objs/ast.o: ../../src/lang/ast.c
	@mkdir -p objs
	$(CC) -c -o objs/ast.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/ast.c

objs/hir.o: ../../src/lang/hir.c
	@mkdir -p objs
	$(CC) -c -o objs/hir.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/hir.c

objs/lir.o: ../../src/lang/lir.c
	@mkdir -p objs
	$(CC) -c -o objs/lir.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/lir.c

objs/runtime.o: ../../src/lang/runtime.c
	@mkdir -p objs
	$(CC) -c -o objs/runtime.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/runtime.c

objs/interpreter.o: ../../src/lang/interpreter.c
	@mkdir -p objs
	$(CC) -c -o objs/interpreter.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/interpreter.c

objs/intrinsics.o: ../../src/lang/intrinsics.c
	@mkdir -p objs
	$(CC) -c -o objs/intrinsics.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/intrinsics.c

objs/jit-common.o: ../../src/lang/jit-common.c
	@mkdir -p objs
	$(CC) -c -o objs/jit-common.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/jit-common.c

#
# src/platform
#

objs/x11main.o: ../../src/platform/x11main.c
	@mkdir -p objs
	$(CC) -c -o objs/x11main.o $(CPPFLAGS) $(CFLAGS) ../../src/platform/x11main.c

objs/x11softrender.o: ../../src/platform/x11softrender.c
	@mkdir -p objs
	$(CC) -c -o objs/x11softrender.o $(CPPFLAGS) $(CFLAGS) ../../src/platform/x11softrender.c

objs/icon.o: ../../src/platform/icon.c
	@mkdir -p objs
	$(CC) -c -o objs/icon.o $(CPPFLAGS) $(CFLAGS) ../../src/platform/icon.c

objs/glrender.o: ../../src/platform/glrender.c
	@mkdir -p objs
	$(CC) -c -o objs/glrender.o $(CPPFLAGS) $(CFLAGS) ../../src/platform/glrender.c

objs/bsdsound.o: ../../src/platform/bsdsound.c
	@mkdir -p objs
	$(CC) -c -o objs/bsdsound.o $(CPPFLAGS) $(CFLAGS) ../../src/platform/bsdsound.c

objs/gstplay.o: ../../src/platform/gstplay.c
	@mkdir -p objs
	$(CC) -c -o objs/gstplay.o $(CPPFLAGS) $(CFLAGS) ../../src/platform/gstplay.c

objs/stdfile.o: ../../src/platform/stdfile.c
	@mkdir -p objs
	$(CC) -c -o objs/stdfile.o $(CPPFLAGS) $(CFLAGS) ../../src/platform/stdfile.c

objs/image.o: ../../src/platform/image.c libroot-solaris
	@mkdir -p objs
	$(CC) -c -o objs/image.o $(CPPFLAGS) $(CFLAGS) ../../src/platform/image.c

objs/glyph.o: ../../src/platform/glyph.c libroot-solaris
	@mkdir -p objs
	$(CC) -c -o objs/glyph.o $(CPPFLAGS) $(CFLAGS) ../../src/platform/glyph.c

objs/wave.o: ../../src/platform/wave.c libroot-solaris
	@mkdir -p objs
	$(CC) -c -o objs/wave.o $(CPPFLAGS) $(CFLAGS) ../../src/platform/wave.c

#
# engine
#

objs/api.o: ../../src/api.c
	@mkdir -p objs
	$(CC) -c -o objs/api.o $(CPPFLAGS) $(CFLAGS) ../../src/api.c

objs/common.o: ../../src/common.c
	@mkdir -p objs
	$(CC) -c -o objs/common.o $(CPPFLAGS) $(CFLAGS) ../../src/common.c

objs/main.o: ../../src/main.c
	@mkdir -p objs
	$(CC) -c -o objs/main.o $(CPPFLAGS) $(CFLAGS) ../../src/main.c

objs/tag.o: ../../src/tag.c
	@mkdir -p objs
	$(CC) -c -o objs/tag.o $(CPPFLAGS) $(CFLAGS) ../../src/tag.c

objs/vm.o: ../../src/vm.c
	@mkdir -p objs
	$(CC) -c -o objs/vm.o $(CPPFLAGS) $(CFLAGS) ../../src/vm.c

objs/render.o: ../../src/render.c
	@mkdir -p objs
	$(CC) -c -o objs/render.o $(CPPFLAGS) $(CFLAGS) ../../src/render.c

objs/sound.o: ../../src/sound.c
	@mkdir -p objs
	$(CC) -c -o objs/sound.o $(CPPFLAGS) $(CFLAGS) ../../src/sound.c

objs/font.o: ../../src/font.c
	@mkdir -p objs
	$(CC) -c -o objs/font.o $(CPPFLAGS) $(CFLAGS) ../../src/font.c

#
# Top-level
#

objs/translation.o: ../../src/translation.c
	@mkdir -p objs
	$(CC) -c -o objs/translation.o $(CPPFLAGS) $(CFLAGS) ../../src/translation.c

#
# libroot
#

libroot-solaris:
	@../../lib/build-libs.sh "solaris" $(CC) "-O2" $(AR)

#
# Phony
#

clean:
	rm -rf libroot-solaris objs fuel
