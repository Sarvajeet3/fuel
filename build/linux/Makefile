CC=cc
LD=ld
AR=ar
STRIP=strip

CPPFLAGS=\
	-DUSE_JIT \
	-DUSE_TRANSLATION \
	-DUSE_X11_OPENGL \
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
	-lX11 \
	-lXpm \
	-lGL \
	-lGLX \
	-lpthread \
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
	objs/jit-common.o \
	objs/jit-arm64.o \
	objs/jit-arm32.o \
	objs/jit-x86_64.o \
	objs/jit-x86.o \
	objs/jit-ppc64.o \
	objs/jit-ppc32.o \
	objs/jit-mips64.o \
	objs/jit-mips32.o

OBJS_PLATFORM=\
	objs/x11main.o \
	objs/x11opengl.o \
	objs/x11softrender.o \
	objs/icon.o \
	objs/glrender.o \
	objs/asound.o \
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

all: fuelcore

fuelcore: $(OBJS_LANG) $(OBJS_PLATFORM) $(OBJS_ENGINE) $(OBJS_TOP)
	$(CC) -o $@ $(CFLAGS) $^ $(LDFLAGS)

#
# src/language
#

objs/lexer.yy.o: ../../src/lang/lexer.yy.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) -O2 -g0 $(CFLAGS) -Wno-sign-conversion -Wno-sign-compare -Wno-conversion $<

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

objs/jit-arm64.o: ../../src/lang/jit-arm64.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/jit-arm32.o: ../../src/lang/jit-arm32.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/jit-x86_64.o: ../../src/lang/jit-x86_64.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/jit-x86.o: ../../src/lang/jit-x86.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/jit-ppc64.o: ../../src/lang/jit-ppc64.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/jit-ppc32.o: ../../src/lang/jit-ppc32.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/jit-mips64.o: ../../src/lang/jit-mips64.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/jit-mips32.o: ../../src/lang/jit-mips32.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

#
# src/platform
#

objs/x11main.o: ../../src/platform/x11main.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/x11opengl.o: ../../src/platform/x11opengl.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/x11softrender.o: ../../src/platform/x11softrender.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/icon.o: ../../src/platform/icon.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/glrender.o: ../../src/platform/glrender.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/asound.o: ../../src/platform/asound.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

#objs/gstplay.o: ../../src/platform/gstplay.c
#	@mkdir -p objs
#	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) `pkg-config --cflags gstreamer-1.0 gstreamer-video-1.0` $<

objs/gstplay.o: ../../src/platform/gstplay.c
	@mkdir -p objs
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

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

objs/sound.o: ../../src/sound.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/font.o: ../../src/font.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

#
# Top-level
#

objs/translation.o: ../../src/translation.c
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

setup:
	sudo apt-get install build-essential libx11-dev libxpm-dev mesa-common-dev libasound2-dev || true
	sudo dnf install patch libX11-devel libXpm-devel alsa-lib-devel mesa-libGL-devel || true

clean:
	rm -rf libroot objs fuelcore
