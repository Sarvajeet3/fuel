CC=x86_64-w64-mingw32-gcc
CXX=x86_64-w64-mingw32-g++
LD=x86_64-w64-mingw32-ld
AR=x86_64-w64-mingw32-ar
STRIP=x86_64-w64-mingw32-strip
WINDRES=x86_64-w64-mingw32-windres

CPPFLAGS=\
	-I../win32/res \
	-I../../src \
	-I./libroot/include \
	-DUSE_JIT \
	-DUSE_TRANSLATION \
	-DUSE_SSE_DISPATCH

CFLAGS=\
	-O2 \
	-g0 \
	-fno-exceptions \
	-fno-stack-protector \
	-fomit-frame-pointer \
	-municode \
	-ffast-math \
	-ftree-vectorize \
	-finput-charset=utf-8 \
	-fexec-charset=utf-8 \
	-Wall \
	-Werror \
	-Wextra \
	-Wundef \
	-Wconversion \
	-Wno-unknown-pragmas \
	-Wno-multichar \
	-Wno-strict-aliasing

CXXFLAGS = \
	-fno-rtti

LDFLAGS=\
	-static \
	-lstdc++ \
	-lgcc \
	-mwindows \
	-lgdi32 \
	-lole32 \
	-ldsound \
	-ldxguid \
	-lstrmiids \
	-Wl,--gc-sections \
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
	./libroot/lib/libz.a

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
	objs/jit-x86_64.o

OBJS_PLATFORM=\
	objs/winmain.o \
	objs/d3drender.o \
	objs/d3d12render.o \
	objs/d3d11render.o \
	objs/d3d9render.o \
	objs/gdirender.o \
	objs/dsound.o \
	objs/dsvideo.o \
	objs/stdfile.o \
	objs/image.o \
	objs/glyph.o \
	objs/wave.o \
	objs/cpuid.o \
	objs/avx2.o \
	objs/avx.o \
	objs/sse42.o \
	objs/sse4.o \
	objs/sse3.o \
	objs/sse2.o \
	objs/sse.o \
	objs/scalar.o

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

all: fuelcore-x64.exe

fuelcore-x64.exe: $(OBJS_LANG) $(OBJS_PLATFORM) $(OBJS_ENGINE) $(OBJS_TOP)
	@$(CXX) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	@$(STRIP) --strip-all $@

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

objs/jit-x86_64.o: ../../src/lang/jit-x86_64.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

#
# src/platform
#

objs/winmain.o: ../../src/platform/winmain.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/d3drender.o: ../../src/platform/d3drender.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/d3d12render.o: ../../src/platform/d3d12render.cc dx12headers
	@mkdir -p objs
	$(CXX) -c -o $@ $(CPPFLAGS) -I./dx12headers/include/directx -I./dx12headers/include/dxguids -DWINAPI_PARTITION_GAMES $(CFLAGS) $(CXXFLAGS) $<

objs/d3d11render.o: ../../src/platform/d3d11render.cc
	@mkdir -p objs
	$(CXX) -c -o $@ $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) $<

objs/d3d9render.o: ../../src/platform/d3d9render.cc
	@mkdir -p objs
	$(CXX) -c -o $@ $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) $<

objs/gdirender.o: ../../src/platform/gdirender.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/dsound.o: ../../src/platform/dsound.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/dsvideo.o: ../../src/platform/dsvideo.cc
	@mkdir -p objs
	$(CXX) -c -o $@ $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) $<

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

objs/cpuid.o: ../../src/platform/cpuid.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/avx2.o: ../../src/platform/avx2.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) -mavx2 $(CFLAGS) $<

objs/avx.o: ../../src/platform/avx.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) -mavx $(CFLAGS) $<

objs/sse42.o: ../../src/platform/sse42.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) -msse4.2 $(CFLAGS) $<

objs/sse4.o: ../../src/platform/sse4.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) -msse4 $(CFLAGS) $<

objs/sse3.o: ../../src/platform/sse3.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) -msse3 $(CFLAGS) $<

objs/sse2.o: ../../src/platform/sse2.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) -msse2 $(CFLAGS) $<

objs/sse.o: ../../src/platform/sse.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) -msse $(CFLAGS) $<

objs/scalar.o: ../../src/platform/scalar.c
	@mkdir -p objs
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

objs/resource.o: ../win32/res/resource.rc
	@mkdir -p objs
	$(WINDRES) $< $@

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
	@../../lib/build-libs.sh "" $(CC) "-O3 -g0 -s -fno-stack-protector -fomit-frame-pointer -ffast-math -ftree-vectorize -ffunction-sections -fdata-sections" $(AR)

#
# DirectX 12 Headers
#

dx12headers:
	git clone https://github.com/microsoft/DirectX-Headers.git dx12headers

#
# Phony
#

setup:
	sudo apt-get install mingw-w64

clean:
	rm -rf objs fuelcore-x64.exe dx12headers libroot
