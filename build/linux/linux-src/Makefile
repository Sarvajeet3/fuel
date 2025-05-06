CC=cc
CPPFLAGS=
CFLAGS=

all: fuelcore

fuelcore: entry.c icon.c
	$(CC) -o fuelcore entry.c icon.c lib/libfuel.a lib/libpng.a lib/libjpeg.a lib/libwebp.a lib/libbrotlidec.a lib/libbrotlicommon.a lib/libvorbisfile.a lib/libvorbis.a lib/libogg.a lib/libfreetype.a lib/libbz2.a lib/libz.a
