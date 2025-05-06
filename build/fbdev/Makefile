CC=cc
LD=ld
AR=ar
STRIP=strip

CPPFLAGS=\
	-DUSE_LINUXFB \
	-I../../src \
	-I./libroot/include

CFLAGS=\
	-O2 \
	-g0 \
	-ffast-math \
	-ftree-vectorize \
	-std=gnu11 \
	-Wall \
	-Werror \
	-Wextra \
	-Wundef \
	-Wconversion \
	-Wno-multichar \
	-Wno-strict-aliasing \
	-Wno-format-truncation

LDFLAGS=\
	./libroot/lib/libpng.a \
	./libroot/lib/libjpeg.a \
	./libroot/lib/libwebp.a \
	./libroot/lib/libfreetype.a \
	./libroot/lib/libvorbisfile.a \
	./libroot/lib/libvorbis.a \
	./libroot/lib/libogg.a \
	./libroot/lib/libbrotlidec.a \
	./libroot/lib/libbrotlicommon.a \
	./libroot/lib/libbz2.a \
	./libroot/lib/libz.a \
	-lasound \
	-lm

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
	objs/fbmain.o \
	objs/asound.o \
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
	objs/main.o

OBJS_TOP=

#
# Main Target
#

all: fuel

fuel: $(OBJS_LANG) $(OBJS_PLATFORM) $(OBJS_ENGINE) $(OBJS_TOP)
	$(CC) -o $@ $(CFLAGS) $^ $(LDFLAGS)

#
# src/language
#

objs/lexer.yy.o: ../../src/lang/lexer.yy.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) -Wno-sign-conversion -Wno-sign-compare -Wno-conversion $<

objs/parser.tab.o: ../../src/lang/parser.tab.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/ast.o: ../../src/lang/ast.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/hir.o: ../../src/lang/hir.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/lir.o: ../../src/lang/lir.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/runtime.o: ../../src/lang/runtime.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/interpreter.o: ../../src/lang/interpreter.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/intrinsics.o: ../../src/lang/intrinsics.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/jit-common.o: ../../src/lang/jit-common.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

#
# src/platform
#

objs/fbmain.o: ../../src/platform/fbmain.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/asound.o: ../../src/platform/asound.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/stdfile.o: ../../src/platform/stdfile.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/image.o: ../../src/platform/image.c libroot
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/glyph.o: ../../src/platform/glyph.c libroot
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/wave.o: ../../src/platform/wave.c libroot
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

#
# engine
#

objs/api.o: ../../src/api.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/common.o: ../../src/common.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/main.o: ../../src/main.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/tag.o: ../../src/tag.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/vm.o: ../../src/vm.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/render.o: ../../src/render.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

#
# libroot
#

libroot:
	@../../lib/build-libs.sh "" $(CC) "-O2 -g0" $(AR)

#
# Phony
#

clean:
	rm -rf libroot objs fuel
