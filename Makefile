DESTDIR=/usr/local
BUILDDIR=build/linux
TARGET_POSTFIX=
CC=cc
CXX=c++
AR=ar
STRIP=strip
WINDRES=windres

build-all:
	@cd build/lang-cli && make "fuellang$(TARGET_POSTFIX)" CC=$(CC) CXX=$(CXX) AR=$(AR) STRIP=$(STRIP) WINDRES=$(WINDRES)
	@cd build/pack-cli && make "fuelpack$(TARGET_POSTFIX)" CC=$(CC) CXX=$(CXX) AR=$(AR) STRIP=$(STRIP) WINDRES=$(WINDRES)
	@cd build/fuel-cli && make "fuel$(TARGET_POSTFIX)" CC=$(CC) CXX=$(CXX) AR=$(AR) STRIP=$(STRIP) WINDRES=$(WINDRES) CPPFLAGS="-DTARGET_POSIX -I../../src"
	@cd $(BUILDDIR) && make "fuelcore$(TARGET_POSTFIX)" CC=$(CC) CXX=$(CXX) AR=$(AR) STRIP=$(STRIP) WINDRES=$(WINDRES)

install:
	@install -v -d $(DESTDIR)/bin
	@install -m 755 -v build/lang-cli/fuellang$(TARGET_POSTFIX) $(DESTDIR)/bin/fuellang$(TARGET_POSTFIX)
	@install -m 755 -v build/pack-cli/fuelpack$(TARGET_POSTFIX) $(DESTDIR)/bin/fuelpack$(TARGET_POSTFIX)
	@install -m 755 -v build/fuel-cli/fuel$(TARGET_POSTFIX) $(DESTDIR)/bin/fuel$(TARGET_POSTFIX)
	@install -m 755 -v $(BUILDDIR)/fuelcore$(TARGET_POSTFIX) $(DESTDIR)/bin/fuelcore$(TARGET_POSTFIX)
	@install -d "$(DESTDIR)/share/man/man1"
	@install -m 644 -v man/fuellang.1 "$(DESTDIR)/share/man/fuellang.1"
	@install -m 644 -v man/fuelpack.1 "$(DESTDIR)/share/man/fuelpack.1"
	@install -m 644 -v man/fuel.1 "$(DESTDIR)/share/man/fuel.1"
	@install -m 644 -v man/fuelcore.1 "$(DESTDIR)/share/man/fuelcore.1"

doc:
	mkdocs build

clean:
	@cd build/lang-cli && make clean
	@cd build/pack-cli && make clean
	@cd build/fuel-cli && make clean
	@cd $(BUILDDIR) && make clean
	@rm -rf site
