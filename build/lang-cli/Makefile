CC=cc
CPPFLAGS=
CFLAGS=
LEX=flex
YACC=bison

CPPFLAGS=\
	-I../../src \
	-DUSE_JIT \
	-DUSE_TRANSLATION

CFLAGS=\
	-O0 \
	-g3 \
	-std=gnu11 \
	-Wall \
	-Werror \
	-Wextra \
	-Wundef \
	-Wconversion \
	-Wno-multichar \
	-Wno-strict-aliasing

LDFLAGS=\
	-lm

OBJS=\
	objs/lexer.yy.o \
	objs/parser.tab.o \
	objs/ast.o \
	objs/hir.o \
	objs/lir.o \
	objs/runtime.o \
	objs/interpreter.o \
	objs/intrinsics.o \
	objs/jit-common.o \
	objs/jit-arm64.o \
	objs/jit-arm32.o \
	objs/jit-x86_64.o \
	objs/jit-x86.o \
	objs/jit-ppc64.o \
	objs/jit-ppc32.o \
	objs/jit-mips64.o \
	objs/jit-mips32.o \
	objs/command.o \
	objs/cback.o \
	objs/translation.o

all: fuellang

fuellang: $(OBJS)
	$(CC) -o fuellang $(CPPFLAGS) $(CFLAGS) $(OBJS) $(LDFLAGS)

fuellang.exe: $(OBJS)
	$(CC) -o fuellang.exe $(CPPFLAGS) $(CFLAGS) $(OBJS) $(LDFLAGS)

objs/lexer.yy.o: ../../src/lang/lexer.yy.c
	@mkdir -p objs
	$(CC) -c -o objs/lexer.yy.o $(CPPFLAGS) $(CFLAGS) -Wno-sign-conversion -Wno-sign-compare -Wno-conversion ../../src/lang/lexer.yy.c

objs/parser.tab.o: ../../src/lang/parser.tab.c
	@mkdir -p objs
	$(CC) -c -o objs/parser.tab.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/parser.tab.c

objs/ast.o: ../../src/lang/ast.c
	@mkdir -p objs
	$(CC) -c -o objs/ast.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/ast.c

objs/hir.o: ../../src/lang/hir.c
	@mkdir -p objs
	$(CC) -c -o objs/hir.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/hir.c

objs/lir.o: ../../src/lang/lir.c
	@mkdir -p objs
	$(CC) -c -o objs/lir.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/lir.c

objs/runtime.o: ../../src/lang/runtime.c
	@mkdir -p objs
	$(CC) -c -o objs/runtime.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/runtime.c

objs/interpreter.o: ../../src/lang/interpreter.c
	@mkdir -p objs
	$(CC) -c -o objs/interpreter.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/interpreter.c

objs/intrinsics.o: ../../src/lang/intrinsics.c
	@mkdir -p objs
	$(CC) -c -o objs/intrinsics.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/intrinsics.c

objs/jit-common.o: ../../src/lang/jit-common.c
	@mkdir -p objs
	$(CC) -c -o objs/jit-common.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/jit-common.c

objs/jit-arm64.o: ../../src/lang/jit-arm64.c
	@mkdir -p objs
	$(CC) -c -o objs/jit-arm64.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/jit-arm64.c

objs/jit-arm32.o: ../../src/lang/jit-arm32.c
	@mkdir -p objs
	$(CC) -c -o objs/jit-arm32.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/jit-arm32.c

objs/jit-x86_64.o: ../../src/lang/jit-x86_64.c
	@mkdir -p objs
	$(CC) -c -o objs/jit-x86_64.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/jit-x86_64.c

objs/jit-x86.o: ../../src/lang/jit-x86.c
	@mkdir -p objs
	$(CC) -c -o objs/jit-x86.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/jit-x86.c

objs/jit-ppc64.o: ../../src/lang/jit-ppc64.c
	@mkdir -p objs
	$(CC) -c -o objs/jit-ppc64.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/jit-ppc64.c

objs/jit-ppc32.o: ../../src/lang/jit-ppc32.c
	@mkdir -p objs
	$(CC) -c -o objs/jit-ppc32.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/jit-ppc32.c

objs/jit-mips64.o: ../../src/lang/jit-mips64.c
	@mkdir -p objs
	$(CC) -c -o objs/jit-mips64.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/jit-mips64.c

objs/jit-mips32.o: ../../src/lang/jit-mips32.c
	@mkdir -p objs
	$(CC) -c -o objs/jit-mips32.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/jit-mips32.c

objs/command.o: ../../src/lang/command.c
	@mkdir -p objs
	$(CC) -c -o objs/command.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/command.c

objs/cback.o: ../../src/lang/cback.c
	@mkdir -p objs
	$(CC) -c -o objs/cback.o $(CPPFLAGS) $(CFLAGS) ../../src/lang/cback.c

objs/translation.o: ../../src/translation.c
	@mkdir -p objs
	$(CC) -c -o objs/translation.o $(CPPFLAGS) $(CFLAGS) ../../src/translation.c

#../../src/lang/lexer.yy.c: ../../src/lang/lexer.l
#	$(LEX) -o ../../src/lang/lexer.yy.c --prefix=ast_yy ../../src/lang/lexer.l
#
#../../src/lang/parser.tab.c: ../../src/lang/parser.y
#	$(YACC) -Wcounterexamples -d -p ast_yy -o ../../src/lang/parser.tab.c ../../src/lang/parser.y

clean:
	rm -rf objs fuellang fuellang.exe
