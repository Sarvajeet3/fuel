SRCS=\
    ../../src/lang/lexer.yy.c \
    ../../src/lang/parser.tab.c \
    ../../src/lang/ast.c \
    ../../src/lang/hir.c \
    ../../src/lang/lir.c \
    ../../src/lang/runtime.c \
    ../../src/lang/interpreter.c \
    ../../src/lang/intrinsics.c \
    ../../src/lang/jit-common.c \
    ../../src/platform/ndkfile.c \
    ../../src/platform/image.c \
    ../../src/platform/slsound.c \
    ../../src/platform/glyph.c \
    ../../src/platform/wave.c \
    ../../src/platform/ndkmain.c \
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

src: libfuel-aarch64.so libfuel-armv7a.so libfuel-x86_64.so libfuel-i686.so
	@rm -rf app/build app/.cxx app/src/main/cpp app/src/main/java app/src/main/assets android-src
	@mkdir -p android-src
	@mkdir -p android-src/app/src/main/cpp
	@mkdir -p android-src/app/src/main/assets
	@
	@cp -R app android-src/
	@cp -R gradle.properties android-src/
	@cp -R build.gradle android-src/
	@cp -R gradlew android-src/
	@cp -R settings.gradle android-src/
	@cp -R gradlew.bat android-src/
	@cp -R gradle android-src/
	@
	@cp -R build.bat android-src/
	@
	@mkdir -p android-src/app/src/main/java/team/fuel/engineandroid
	@cp ../../src/platform/MainActivity.java android-src/app/src/main/java/team/fuel/engineandroid/
	@
	@mkdir -p android-src/app/src/main/jniLibs/arm64-v8a
	@cp libfuel-aarch64.so android-src/app/src/main/jniLibs/arm64-v8a/libfuel.so
	@mkdir -p android-src/app/src/main/jniLibs/armeabi-v7a
	@cp libfuel-armv7a.so android-src/app/src/main/jniLibs/armeabi-v7a/libfuel.so
	@mkdir -p android-src/app/src/main/jniLibs/x86_64
	@cp libfuel-x86_64.so android-src/app/src/main/jniLibs/x86_64/libfuel.so
	@mkdir -p android-src/app/src/main/jniLibs/x86
	@cp libfuel-i686.so android-src/app/src/main/jniLibs/x86/libfuel.so

libfuel-aarch64.so: ndk
	@echo 'Building aarch64 library...'
	@../../lib/build-libs.sh aarch64 `pwd`/ndk/bin/clang-18 "--target=aarch64-linux-android21 -O2 -g0 -fPIC" `pwd`/ndk/bin/llvm-ar
	@`pwd`/ndk/bin/clang-18 \
		--target=aarch64-linux-android21 \
		-O2 \
		-shared \
		-fPIC \
		-o libfuel-aarch64.so \
		-DUSE_DLL \
		-I../../src \
		-I./libroot-aarch64/include \
		-I./libroot-aarch64/include/png \
		-I./libroot-aarch64/include/freetype2 \
		$(SRCS) \
		-lm \
		-lGLESv3 \
		-lOpenSLES \
		-llog \
		-L./libroot-aarch64/lib \
		-lfreetype \
		-lwebp \
		-lpng \
		-ljpeg \
		-lbrotlidec \
		-lbrotlicommon \
		-lvorbisfile \
		-lvorbis \
		-logg \
		-lbz2 \
		-lz

libfuel-armv7a.so: ndk
	@echo 'Building armv7a library...'
	@../../lib/build-libs.sh armv7a `pwd`/ndk/bin/clang-18 "--target=armv7a-linux-androideabi21 -O2 -g0 -fPIC" `pwd`/ndk/bin/llvm-ar
	@`pwd`/ndk/bin/clang-18 \
		--target=armv7a-linux-android21 \
		-O2 \
		-shared \
		-fPIC \
		-o libfuel-armv7a.so \
		-DUSE_DLL \
		-I../../src \
		-I./libroot-armv7a/include \
		-I./libroot-armv7a/include/png \
		-I./libroot-armv7a/include/freetype2 \
		$(SRCS) \
		-lm \
		-lGLESv3 \
		-lOpenSLES \
		-llog \
		-L./libroot-armv7a/lib \
		-lfreetype \
		-lwebp \
		-lpng \
		-ljpeg \
		-lbrotlidec \
		-lbrotlicommon \
		-lvorbisfile \
		-lvorbis \
		-logg \
		-lbz2 \
		-lz

libfuel-x86_64.so: ndk
	@echo 'Building x86_64 library...'
	@../../lib/build-libs.sh x86_64 `pwd`/ndk/bin/clang-18 "--target=x86_64-linux-android21 -O2 -g0 -fPIC" `pwd`/ndk/bin/llvm-ar
	@`pwd`/ndk/bin/clang-18 \
		--target=x86_64-linux-android21 \
		-O2 \
		-shared \
		-fPIC \
		-o libfuel-x86_64.so \
		-DUSE_DLL \
		-I../../src \
		-I./libroot-x86_64/include \
		-I./libroot-x86_64/include/png \
		-I./libroot-x86_64/include/freetype2 \
		$(SRCS) \
		-lm \
		-lGLESv3 \
		-lOpenSLES \
		-llog \
		-L./libroot-x86_64/lib \
		-lfreetype \
		-lwebp \
		-lpng \
		-ljpeg \
		-lbrotlidec \
		-lbrotlicommon \
		-lvorbisfile \
		-lvorbis \
		-logg \
		-lbz2 \
		-lz

libfuel-i686.so: ndk
	@echo 'Building i686 library...'
	@../../lib/build-libs.sh i686 `pwd`/ndk/bin/clang-18 "--target=i686-linux-android21 -O2 -g0 -fPIC" `pwd`/ndk/bin/llvm-ar
	@`pwd`/ndk/bin/clang-18 \
		--target=i686-linux-android21 \
		-O2 \
		-shared \
		-fPIC \
		-o libfuel-i686.so \
		-DUSE_DLL \
		-I../../src \
		-I./libroot-i686/include \
		-I./libroot-i686/include/png \
		-I./libroot-i686/include/freetype2 \
		$(SRCS) \
		-lm \
		-lGLESv3 \
		-lOpenSLES \
		-llog \
		-L./libroot-i686/lib \
		-lfreetype \
		-lwebp \
		-lpng \
		-ljpeg \
		-lbrotlidec \
		-lbrotlicommon \
		-lvorbisfile \
		-lvorbis \
		-logg \
		-lbz2 \
		-lz

ndk:
	@if [ "`uname -a | grep Linux`" != "" ]; then \
		curl -O https://dl.google.com/android/repository/android-ndk-r27-linux.zip; \
		unzip android-ndk-r27-linux.zip; \
		mv 'android-ndk-r27/toolchains/llvm/prebuilt/linux-x86_64' ndk; \
		chmod -R +x ./ndk/bin/*; \
		rm -rf 'android-ndk-r27' android-ndk-r27-linux.zip; \
	elif [ "`uname -a | grep Darwin`" != "" ]; then \
		curl -O https://dl.google.com/android/repository/android-ndk-r27-darwin.dmg; \
		7z x android-ndk-r27-darwin.dmg; \
		mv 'Android NDK r27/AndroidNDK12077973.app/Contents/NDK/toolchains/llvm/prebuilt/darwin-x86_64' ndk; \
		chmod -R +x ./ndk/bin/*; \
		rm ndk/bin/ld.lld; \
		ln -s lld ndk/bin/ld.lld; \
		rm -rf 'Android NDK r27'; \
	else \
		curl -O https://dl.google.com/android/repository/android-ndk-r27-windows.zip; \
		unzip android-ndk-r27-windows.zip; \
		mv 'android-ndk-r27/toolchains/llvm/prebuilt/windows-x86_64' ndk; \
		chmod -R +x ./ndk/bin/*; \
		rm -rf 'android-ndk-r27' android-ndk-r27-windows.zip; \
	fi

clean:
	@rm -rf android-src android-ndk-r27-darwin.dmg android-ndk-r27-linux.zip ndk libroot-* libfuel-*.so
