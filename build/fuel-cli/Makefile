CC=cc
CPPFLAGS=\
	-I../../src
CFLAGS=\
	-O2 \
	-g0 \

all: fuel

fuel: ../../src/cli/climain.c
	$(CC) -o fuel $(CPPFLAGS) $(CFLAGS) ../../src/cli/climain.c

fuel.exe: ../../src/cli/climain.c
	$(CC) -o fuel.exe $(CPPFLAGS) $(CFLAGS) ../../src/cli/climain.c

clean:
	rm -rf fuel fuel.exe
