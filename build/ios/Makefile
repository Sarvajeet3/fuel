all: src

src:
	@./build-libs.sh
	@rm -rf ios-src
	@mkdir ios-src
	@mkdir ios-src/ios
	@cp -R ios/Assets.xcassets ios-src/ios/
	@cp -R ios/Base.lproj ios-src/ios/
	@cp ios/Main.storyboard ios-src/ios/
	@cp ios/ios.entitlements ios-src/ios/
	@cp ios/entry.c ios-src/ios/
	@cp ios/libfuel-device.a ios-src/ios/
	@cp ios/libfuel-sim.a ios-src/ios/
	@cp ios/GameShaders.metal ios-src/ios/
	@cp ios/GameShaderTypes.h ios-src/ios/
	@mkdir ios-src/Resources/
	@mkdir ios-src/Resources/video
	@mkdir ios-src/ios.xcodeproj
	@cp ios.xcodeproj/project.pbxproj ios-src/ios.xcodeproj/

clean:
	@rm -rf build libroot* objs ios-src fuel.dmg ios-src/libfuel.a ios-src/libfuel-device.a ios-src/libfuel-sim.a ios.xcodeproj/project.xcworkspace/xcuserdata
