CC=cc
MINGWGCC=i686-w64-mingw32-gcc
CPPFLAGS=
CFLAGS=\
	-O2 \
	-g0 \
	-I../../src

all: fuel

fuel: ../../src/cli/climain.c
	$(CC) -o fuel $(CPPFLAGS) $(CFLAGS) ../../src/cli/climain.c

fuel.exe: ../../src/cli/climain.c
	$(MINGWGCC) -o fuel.exe $(CPPFLAGS) $(CFLAGS) ../../src/cli/climain.c

clean:
	rm -rf fuel fuel.exe
