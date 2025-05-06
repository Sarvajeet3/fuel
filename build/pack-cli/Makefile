CC=cc
CPPFLAGS=
CFLAGS=
MINGWCC=i686-w64-mingw32-gcc

CFLAGS=\
	-O2 \
	-g0 \
	-I../../src

all: fuelpack

fuelpack: ../../src/platform/package.c
	$(CC) -o fuelpack $(CPPFLAGS) $(CFLAGS) ../../src/platform/package.c

fuelpack.exe: ../../src/platform/package.c
	$(MINGWCC) -o fuelpack.exe $(CPPFLAGS) $(CFLAGS) ../../src/platform/package.c

clean:
	rm -rf fuelpack fuelpack.exe
