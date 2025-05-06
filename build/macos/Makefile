all: fuelcore.dmg

fuelcore.dmg: libroot/lib/libfuel.a
	@echo "Building FuelCore.app"
	@rm -rf build
	@echo 'Archiving...'
	@xcodebuild \
		-quiet \
		-scheme Fuel \
		-project macos.xcodeproj \
		-configuration Release \
		-archivePath `pwd`/build/Release/FuelCore.xcarchive \
		archive
	@echo 'Exporting...'
	@xcodebuild \
		-quiet \
		-exportArchive \
		-archivePath `pwd`/build/Release/FuelCore.xcarchive \
		-exportOptionsPlist ExportOptions.plist
	@echo 'Notarizing...'
	@until \
		xcodebuild \
			-quiet \
			-exportNotarizedApp \
			-archivePath `pwd`/build/Release/FuelCore.xcarchive \
			-exportPath `pwd`/build/Release; \
	do \
		echo \"Waiting 10 seconds for notarization...\"; \
		sleep 10; \
	done
	@echo "Successfully notarized."
	@rm -f fuelcore.dmg
	@rm -rf tmp
	@mkdir -p tmp
	@cp -Rv build/Release/FuelCore.app tmp/FuelCore.app
	@hdiutil create -fs HFS+ -format UDBZ -srcfolder tmp -volname FuelCore fuelcore.dmg
	@codesign --sign 'Developer ID Application' fuelcore.dmg
	@rm -rf tmp

src: libroot/lib/libfuel.a
	@mkdir -p macos-src/lib
	@mkdir -p macos-src/Resources/
	@touch macos-src/Resources/COPY_ASSETS_HERE
	@cp libroot/lib/* macos-src/macos/
	@cp libroot/lib/libbrotlicommon.a macos-src/macos/
	@cp libroot/lib/libfreetype.a macos-src/macos/
	@cp libroot/lib/libogg.a macos-src/macos/
	@cp libroot/lib/libvorbisfile.a macos-src/macos/
	@cp libroot/lib/libbrotlidec.a macos-src/macos/
	@cp libroot/lib/libfuel.a macos-src/macos/
	@cp libroot/lib/libpng.a macos-src/macos/
	@cp libroot/lib/libwebp.a macos-src/macos/
	@cp libroot/lib/libbz2.a macos-src/macos/
	@cp libroot/lib/libjpeg.a macos-src/macos/
	@cp libroot/lib/libvorbis.a macos-src/macos/
	@cp libroot/lib/libz.a macos-src/macos/
	@cp ../../src/platform/GameShaders.metal macos-src/macos/
	@cp ../../src/platform/GameShaderTypes.h macos-src/macos/

libroot/lib/libfuel.a:
	@./build-libs.sh

clean:
	@rm -rf build libroot* objs fuelcore.dmg macos/libfuel.a macos.xcodeproj/project.xcworkspace/xcuserdata
