CC=cc
CPPFLAGS=
CFLAGS=

CFLAGS=\
	-O2 \
	-g0 \
	-I../../src

all: fuelpack

fuelpack: ../../src/platform/package.c
	$(CC) -o fuelpack $(CPPFLAGS) $(CFLAGS) ../../src/platform/package.c

fuelpack.exe: ../../src/platform/package.c
	$(CC) -o fuelpack.exe $(CPPFLAGS) $(CFLAGS) ../../src/platform/package.c

clean:
	rm -rf fuelpack fuelpack.exe
