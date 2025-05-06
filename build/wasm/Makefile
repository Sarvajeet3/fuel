SRCS = \
    ../../src/lang/lexer.yy.c \
    ../../src/lang/parser.tab.c \
    ../../src/lang/ast.c \
    ../../src/lang/hir.c \
    ../../src/lang/lir.c \
    ../../src/lang/runtime.c \
    ../../src/lang/interpreter.c \
    ../../src/lang/intrinsics.c \
    ../../src/lang/jit-common.c \
    ../../src/platform/stdfile.c \
    ../../src/platform/image.c \
    ../../src/platform/glyph.c \
    ../../src/platform/wave.c \
    ../../src/platform/emmain.c \
    ../../src/platform/alsound.c \
    ../../src/platform/glrender.c \
    ../../src/api.c \
    ../../src/main.c \
    ../../src/tag.c \
    ../../src/vm.c \
    ../../src/common.c \
    ../../src/render.c \
    ../../src/sound.c \
    ../../src/font.c \
    ../../src/translation.c

all: index.html

index.html: $(SRCS)
	@tar xzf ../../lib/archive/libwebp-1.3.2.tar.gz
	@rm -f html/index.*
	@emcc \
		-O2 \
		-o index.html \
		-I../../src \
		-I./libwebp-1.3.2 \
		-I./libwebp-1.3.2/src \
		$(SRCS) \
		libwebp-1.3.2/src/**/*.c \
		-s USE_ZLIB=1 \
		-s USE_LIBPNG=1 \
		-s USE_OGG=1 \
		-s USE_VORBIS=1 \
		-s USE_FREETYPE=1 \
		-s USE_LIBJPEG=1 \
		-s TOTAL_MEMORY=536870912 \
		-s NO_EXIT_RUNTIME=1 \
		-s EXPORTED_RUNTIME_METHODS=["ccall","UTF8ToString"] \
		-lz \
		-lpng \
		-logg \
		-lvorbis \
		-lfreetype \
		-lopenal \
		-lidbfs.js \
		--shell-file shell.html \
		--pre-js pre.js \
		--use-preload-plugins

clean:
	@rm -rf index.html index.js index.wasm libwebp-1.3.2
