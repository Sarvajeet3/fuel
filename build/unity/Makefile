CONSOLE_LLVM_CC=clang
CONSOLE_LLVM_AR=ar

#
# Make a source tree
#
src: libfuel.dll
	@echo 'Making Unity source tree.'
	@rm -rf unity-src
	@mkdir unity-src
	@mkdir unity-src/Assets
	@mkdir unity-src/Assets/StreamingAssets
	@mkdir unity-src/Assets/Resources
	@cp -v ./MainScene.unity unity-src/Assets/
	@cp -v ../../src/platform/FuelScript.cs unity-src/Assets/
	@cp -v ../../src/platform/NormalShader.shader unity-src/Assets/Resources/
	@cp -v ../../src/platform/AddShader.shader unity-src/Assets/Resources/
	@cp -v ../../src/platform/DimShader.shader unity-src/Assets/Resources/
	@cp -v ../../src/platform/RuleShader.shader unity-src/Assets/Resources/
	@cp -v ../../src/platform/MeltShader.shader unity-src/Assets/Resources/
	@cp libfuel.dll unity-src/Assets/libfuel.dll
	@cp README.md unity-src/
	@echo 'Done making Unity source tree.'
	@echo ''

#
# Unity Native Plugin for Windows x86_64
#
libfuel.dll: $(SRCS)
	@echo 'Building libfuel.dll ...'
	@if [ ! -d libroot ]; then ../../lib/build-libs.sh "" x86_64-w64-mingw32-gcc "-O2 -g0 -fPIC" x86_64-w64-mingw32-ar; fi
	x86_64-w64-mingw32-gcc \
		-shared \
		-fPIC \
		-o libfuel.dll \
		-O2 \
		-DUSE_UNITY \
		-DUSE_CSHARP \
		-DUSE_DLL \
		-I../../src \
		-I./libroot/include \
		-I./libroot/include/png \
		-I./libroot/include/freetype2 \
		../../src/lang/lexer.yy.c \
		../../src/lang/parser.tab.c \
		../../src/lang/ast.c \
		../../src/lang/hir.c \
		../../src/lang/lir.c \
		../../src/lang/runtime.c \
		../../src/lang/interpreter.c \
		../../src/lang/intrinsics.c \
		../../src/lang/jit-common.c \
		../../src/lang/jit-x86_64.c \
		../../src/platform/halwrap.c \
		../../src/platform/image.c \
		../../src/platform/glyph.c \
		../../src/platform/wave.c \
		../../src/api.c \
		../../src/common.c \
		../../src/tag.c \
		../../src/vm.c \
		../../src/render.c \
		../../src/sound.c \
		../../src/font.c \
		../../src/main.c \
		./libroot/lib/libfreetype.a \
		./libroot/lib/libpng.a \
		./libroot/lib/libjpeg.a \
		./libroot/lib/libwebp.a \
		./libroot/lib/libbrotlidec.a \
		./libroot/lib/libbrotlicommon.a \
		./libroot/lib/libvorbisfile.a \
		./libroot/lib/libvorbis.a \
		./libroot/lib/libogg.a \
		./libroot/lib/libbz2.a \
		./libroot/lib/libz.a
	@rm -rf libroot
	@echo 'Done building libfuel.dll.'
	@echo ''

#
# Console (using Clang)
#
libfuel.a:
	@echo 'Building libfuel.a ...'
	@rm -rf libroot
	@../../lib/build-libs.sh "" $(CROSS_CC) "-O2 -g0" $(CROSS_AR)
	@rm -rf objs
	@mkdir objs
	@$(CONSOLE_LLVM_CC) -c -O2 -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 ../../src/lang/lexer.yy.c -o objs/lexer.yy.o
	@$(CONSOLE_LLVM_CC) -c -O2 -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 ../../src/lang/parser.tab.c -o objs/parser.tab.o
	@$(CONSOLE_LLVM_CC) -c -O2 -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 ../../src/lang/ast.c -o objs/ast.o
	@$(CONSOLE_LLVM_CC) -c -O2 -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 ../../src/lang/hir.c -o objs/hir.o
	@$(CONSOLE_LLVM_CC) -c -O2 -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 ../../src/lang/lir.c -o objs/lir.o
	@$(CONSOLE_LLVM_CC) -c -O2 -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 ../../src/lang/runtime.c -o objs/runtime.o
	@$(CONSOLE_LLVM_CC) -c -O2 -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 ../../src/lang/interpreter.c -o objs/interpreter.o
	@$(CONSOLE_LLVM_CC) -c -O2 -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 ../../src/lang/intrinsics.c -o objs/intrinsics.o
	@$(CONSOLE_LLVM_CC) -c -O2 -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 ../../src/lang/jit-common.c -o objs/jit-common.o
	@$(CONSOLE_LLVM_CC) -c -O2 -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 ../../src/lang/jit-x86_64.c -o objs/jit-x86_64.o
	@$(CONSOLE_LLVM_CC) -c -O2 -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 ../../src/lang/jit-arm64.c -o objs/jit-arm64.o
	@$(CONSOLE_LLVM_CC) -c -O2 -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 ../../src/platform/halwrap.c -o objs/halwrap.o
	@$(CONSOLE_LLVM_CC) -c -O2 -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 ../../src/platform/image.c -o objs/image.o
	@$(CONSOLE_LLVM_CC) -c -O2 -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 ../../src/platform/glyph.c -o objs/glyph.o
	@$(CONSOLE_LLVM_CC) -c -O2 -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 ../../src/platform/wave.c -o objs/wave.o
	@$(CONSOLE_LLVM_CC) -c -O2 -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 ../../src/api.c -o objs/api.o
	@$(CONSOLE_LLVM_CC) -c -O2 -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 ../../src/common.c -o objs/common.o
	@$(CONSOLE_LLVM_CC) -c -O2 -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 ../../src/tag.c -o objs/tag.o
	@$(CONSOLE_LLVM_CC) -c -O2 -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 ../../src/vm.c -o objs/vm.o
	@$(CONSOLE_LLVM_CC) -c -O2 -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 ../../src/render.c -o objs/render.o
	@$(CONSOLE_LLVM_CC) -c -O2 -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../src -I./libroot/include -I./libroot/include/png -I./libroot/include/freetype2 ../../src/main.c -o objs/main.o
	@cd objs && $(CONSOLE_LLVM_AR) x ../libroot/lib/libfreetype.a
	@cd objs && $(CONSOLE_LLVM_AR) x ../libroot/lib/libpng.a
	@cd objs && $(CONSOLE_LLVM_AR) x ../libroot/lib/libjpeg.a
	@cd objs && $(CONSOLE_LLVM_AR) x ../libroot/lib/libwebp.a
	@cd objs && $(CONSOLE_LLVM_AR) x ../libroot/lib/libbrotlidec.a
	@cd objs && $(CONSOLE_LLVM_AR) x ../libroot/lib/libbrotlicommon.a
	@cd objs && $(CONSOLE_LLVM_AR) x ../libroot/lib/libvorbisfile.a
	@cd objs && $(CONSOLE_LLVM_AR) x ../libroot/lib/libvorbis.a
	@cd objs && $(CONSOLE_LLVM_AR) x ../libroot/lib/libogg.a
	@cd objs && $(CONSOLE_LLVM_AR) x ../libroot/lib/libbz2.a
	@cd objs && $(CONSOLE_LLVM_AR) x ../libroot/lib/libz.a
	@$(CONSOLE_LLVM_AR) rcs libfuel.a objs/*.o
	@echo 'Done building libfuel.a.'
	@echo ''

#
# Cleanup
#
clean:
	@rm -rf unity-src libfuel.dll libroot tmp
