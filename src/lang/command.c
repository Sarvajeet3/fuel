/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

/*
 * CLI Main
 */

#include "runtime.h"
#include "ast.h"
#include "hir.h"
#include "lir.h"
#include "cback.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <locale.h>
#include <unistd.h>
#include <stdbool.h>

#if defined(TARGET_WINDOWS)
#include <windows.h>
#endif

/* Version string. */
const char version[] = "0.0.1";

/* Index of the first file argument. */
int opt_index;

/*
 * Option Flags
 */

/* Ouput file. */
const char *opt_output;

/* Is compilation? */
bool opt_compile;

/* Is compilation to .lsc bytecode file? */
bool opt_compile_to_lsc;

/* Is compilation to app .c file? */
bool opt_compile_to_app;

/* Is compilation to DLL .c file? */
bool opt_compile_to_dll;

/*
 * Config (extern)
 */

extern bool conf_use_jit;
extern int conf_optimize;

/*
 * Temporary
 */

/* Source file data. */
static char source_data[1 * 1024 * 1024];

/* Source file size. */
static int source_size;

/*
 * Translation
 */

static char *lang_code;

/*
 * Forward Declaration
 */

static void init_locale(void);
static void parse_options(int argc, char *argv[]);
static bool run_interpreter(int argc, char *argv[]);
static bool run_source_compiler(int argc, char *argv[]);
static bool run_binary_compiler(int argc, char *argv[]);
static bool load_file(char *fname);
static void print_error(struct rt_env *rt);
static bool register_ffi(struct rt_env *rt);
static int wide_printf(const char *format, ...);

/*
 * Main
 */
int main(int argc, char *argv[])
{
	int ret;

	/* Get a language code. (for translation) */
	init_locale();

	/* Parse command line options. */
	parse_options(argc, argv);

	/* Run. */
	ret = 0;
	if (opt_compile_to_dll || opt_compile_to_app) {
		/* Translate to a C source file. */
		if (!run_source_compiler(argc, argv))
			return 1;
	} else if (opt_compile_to_lsc) {
		/* Translate to a bytecode file. */
		if (!run_binary_compiler(argc, argv))
			return 1;
	} else {
		/* Run by the interpreter. */
		if (!run_interpreter(argc, argv))
			return 1;
	}

	return ret;
}

/* Initialize the locale. */
static void init_locale(void)
{
	const char *locale;

	locale = setlocale(LC_ALL, "");
	setlocale(LC_ALL, "C");

	if (locale == NULL || locale[0] == '\0' || locale[1] == '\0')
		lang_code = "en";
	else if (strncmp(locale, "en", 2) == 0)
		lang_code = "en";
	else if (strncmp(locale, "fr", 2) == 0)
		lang_code = "fr";
	else if (strncmp(locale, "de", 2) == 0)
		lang_code = "de";
	else if (strncmp(locale, "it", 2) == 0)
		lang_code = "it";
	else if (strncmp(locale, "es", 2) == 0)
		lang_code = "es";
	else if (strncmp(locale, "el", 2) == 0)
		lang_code = "el";
	else if (strncmp(locale, "ru", 2) == 0)
		lang_code = "ru";
	else if (strncmp(locale, "zh_CN", 5) == 0)
		lang_code = "zh";
	else if (strncmp(locale, "zh_TW", 5) == 0)
		lang_code = "tw";
	else if (strncmp(locale, "ja", 2) == 0)
		lang_code = "ja";
	else
		lang_code = "en";
}

/* Parse command line options. */
static void parse_options(int argc, char *argv[])
{
	int index;

	index = 1;
	while (index < argc) {
		/* --help */
		if (strcmp(argv[index], "--help") == 0) {
			wide_printf(_("Usage: %s <source file>\n"), argv[0]);
			exit(0);
		}

		/* --version */
		if (strcmp(argv[index], "--version") == 0) {
			wide_printf(_("%s version %s\n"), argv[0], version);
			exit(0);
		}

		/* --disable-jit */
		if (strcmp(argv[index], "--disable-jit") == 0) {
			conf_use_jit = false;
			index++;
			continue;
		}

		/* -O */
		if (strcmp(argv[index], "-O") == 0) {
			conf_optimize = 1;
			index++;
			continue;
		}

		/* -b */
		if (strcmp(argv[index], "-b") == 0) {
			opt_compile = true;
			opt_compile_to_lsc = true;
			index++;
			continue;
		}

		/* -c */
		if (strcmp(argv[index], "-c") == 0) {
			opt_compile = true;
			opt_compile_to_dll = true;
			index++;
			continue;
		}

		/* -o */
		if (strcmp(argv[index], "-o") == 0) {
			if (index + 1 >= argc) {
				wide_printf(_("Usage: %s <source file>\n"), argv[0]);
				exit(1);
			}
			opt_output = argv[index + 1];
			index += 2;
			continue;
		}

		break;
	}

	if (index >= argc) {
		wide_printf(_("Usage: %s <source file>\n"), argv[0]);
		exit(1);
	}

	opt_index  = index;
}

/*
 * Interpreter Mode (incl. JIT)
 */

/* Run as an interpreter. */
static bool run_interpreter(int argc, char *argv[])
{
	struct rt_env *rt;
	struct rt_value ret;
	int i;

	/* Create a runtime. */
	if (!rt_create(&rt))
		return false;

	/* Register FFI functions. */
	if (!register_ffi(rt))
		return false;

	/* Load argument files. */
	for (i = opt_index; i < argc; i++) {
		/* Load an argument file. */
		if (!load_file(argv[i]))
			return false;

		/* Check an file extension. */
		if (strstr(argv[i], ".lsc") != NULL) {
			/* .lsc: Load a bytecode file. */
			if (!rt_register_bytecode(rt, (uint32_t)source_size, (uint8_t *)source_data)) {
				print_error(rt);
				return false;
			}
		} else {
			/* Other: Compile a source code. */
			if (!rt_register_source(rt, argv[i], source_data)) {
				print_error(rt);
				return false;
			}
		}
	}

	/* Run the "main()" function. */
	if (!rt_call_with_name(rt, "main", NULL, 0, NULL, &ret)) {
		print_error(rt);
		return false;
	}

	/* Destroy a runtime. */
	if (!rt_destroy(rt))
		return false;

	/* Return a result value. */
	return true;
}

/*
 * Source-To-Bytecode Compilation
 */

/* Run as a source-to-bytecode compiler. */
static bool run_binary_compiler(int argc, char *argv[])
{
	char lsc_fname[1024];
	char *dot;
	FILE *fp;
	int i, j, k;

	/* For each argument file. */
	for (i = opt_index; i < argc; i++) {
		int func_count;

		/* Load an argument source file. */
		if (!load_file(argv[i]))
			return false;

		/* Do parse, build AST. */
		if (!ast_build(argv[i], source_data)) {
			wide_printf(_("Error: %s: %d: %s\n"),
				    ast_get_file_name(),
				    ast_get_error_line(),
				    ast_get_error_message());
			return false;
		}

		/* Transform AST to HIR. */
		if (!hir_build()) {
			wide_printf(_("Error: %s: %d: %s\n"),
				    hir_get_file_name(),
				    hir_get_error_line(),
				    hir_get_error_message());
			return false;
		}

		/* Make an output file name. (*.lsc) */
		strcpy(lsc_fname, argv[i]);
		dot = strstr(lsc_fname, ".");
		if (dot != NULL)
			strcpy(dot, ".lsc");
		else
			strcat(lsc_fname, ".lsc");

		/* Open an output .lsc bytecode file. */
		fp = fopen(lsc_fname, "wb");
		if (fp == NULL) {
			wide_printf(_("Cannot open file \"%s\".\n"), lsc_fname);
			exit(1);
		}

		/* Put a file header. */
		func_count = hir_get_function_count();
		fprintf(fp, "CScript Bytecode\n");
		fprintf(fp, "Source\n");
		fprintf(fp, "%s\n", argv[i]);
		fprintf(fp, "Number Of Functions\n");
		fprintf(fp, "%d\n", func_count);

		/* For each HIR function. */
		for (j = 0; j < func_count; j++) {
			struct hir_block *hfunc;
			struct lir_func *lfunc;

			/* Transform HIR to LIR (bytecode). */
			hfunc = hir_get_function(j);
			if (!lir_build(hfunc, &lfunc)) {
				wide_printf(_("Error: %s: %d: %s\n"),
					     lir_get_file_name(),
					     lir_get_error_line(),
					     lir_get_error_message());
				return false;;
			}

			/* Put a bytcode. */
			fprintf(fp, "Begin Function\n");
			fprintf(fp, "Name\n");
			fprintf(fp, "%s\n", lfunc->func_name);
			fprintf(fp, "Parameters\n");
			fprintf(fp, "%d\n", lfunc->param_count);
			for (k = 0; k < lfunc->param_count; k++)
				fprintf(fp, "%s\n", lfunc->param_name[k]);
			fprintf(fp, "Local Size\n");
			fprintf(fp, "%d\n", lfunc->tmpvar_size);
			fprintf(fp, "Bytecode Size\n");
			fprintf(fp, "%d\n", lfunc->bytecode_size);
			fwrite(lfunc->bytecode, (size_t)lfunc->bytecode_size, 1, fp);
			fprintf(fp, "\nEnd Function\n");

			/* Free a single LIR. */
			lir_free(lfunc);
		}

		fclose(fp);

		/* Free entire HIR. */
		hir_free();
	}

	return true;
}

/*
 * Source-To-Source Compilation
 */

/* Run as source-to-source compiler. */
static bool run_source_compiler(int argc, char *argv[])
{
	int i, j;

	/* Initialize the C backend. */
	if (!cback_init(opt_output))
		return false;

	/* For each input file. */
	for (i = opt_index; i < argc; i++) {
		int func_count;

		/* Load an argument file. */
		if (!load_file(argv[i]))
			return false;

		/* Do parse, build AST. */
		if (!ast_build(argv[i], source_data)) {
			wide_printf(_("Error: %s: %d: %s\n"),
				     ast_get_file_name(),
				     ast_get_error_line(),
				     ast_get_error_message());
			return false;
		}

		/* Transform AST to HIR. */
		if (!hir_build()) {
			wide_printf(_("Error: %s: %d: %s\n"),
				     hir_get_file_name(),
				     hir_get_error_line(),
				     hir_get_error_message());
			return false;
		}

		/* For each HIR function. */
		func_count = hir_get_function_count();
		for (j = 0; j < func_count; j++) {
			struct hir_block *hfunc;
			struct lir_func *lfunc;

			/* Transform HIR to LIR (bytecode). */
			hfunc = hir_get_function(j);
			if (!lir_build(hfunc, &lfunc)) {
				wide_printf(_("Error: %s: %d: %s\n"),
					     lir_get_file_name(),
					     lir_get_error_line(),
					     lir_get_error_message());
				return false;;
			}

			/* Put a C function. */
			if (!cback_translate_func(lfunc))
				return false;

			/* Free a single LIR. */
			lir_free(lfunc);
		}

		/* Free entire HIR. */
		hir_free();
	}

	/* Put a epilogue code. */
	if (opt_compile_to_dll) {
		if (!cback_finalize_dll())
			return false;
	} else if (opt_compile_to_app) {
		if (!cback_finalize_standalone())
			return false;
	}

	return true;
}

/*
 * Helpers
 */

/* Load a file content. */
static bool load_file(char *fname)
{
	FILE *fp;
	size_t len;

	fp = fopen(fname, "rb");
	if (fp == NULL) {
		wide_printf(_("Cannot open file \"%s\".\n"), fname);
		return false;
	}

	len = fread(source_data, 1, sizeof(source_data) - 1, fp);
	if (len == 0) {
		wide_printf(_("Cannot read file \"%s\".\n"), fname);
		return false;
	}
	source_size = (int)len;

	/* Terminate the string. */
	source_data[len] = '\0';

	fclose(fp);

	return true;
}

/* Print a runtime error. */
static void print_error(struct rt_env *rt)
{
	wide_printf(_("%s:%d: error: %s\n"),
		     rt_get_error_file(rt),
		     rt_get_error_line(rt),
		     rt_get_error_message(rt));
}

/* Print to console. (supports wide characters) */
static int wide_printf(const char *format, ...)
{
	static char buf[4096];
	va_list ap;

	va_start(ap, format);
	vsnprintf(buf, sizeof(buf), format, ap);
	va_end(ap);

#if defined(TARGET_WINDOWS)
	/* Use wprintf() and wide-string. (Otherwise, we'll see garbages.) */
	static wchar_t wbuf[4096];
	MultiByteToWideChar(CP_UTF8, 0, buf, -1, wbuf, sizeof(wbuf));
	return wprintf(L"%ls", wbuf);
#else
	return printf("%s", buf);
#endif
}

/*
 * FFI Functions
 */

/* FFI function implementation. */
static bool cfunc_print(struct rt_env *rt);
static bool cfunc_readline(struct rt_env *rt);
static bool cfunc_readint(struct rt_env *rt);
static bool cfunc_shell(struct rt_env *rt);

/* FFI table. */
struct ffi_item {
	const char *name;
	int param_count;
	const char *param[RT_ARG_MAX];
	bool (*cfunc)(struct rt_env *rt);
} ffi_items[] = {
	{"print", 1, {"msg"}, cfunc_print},
	{"readline", 0, {}, cfunc_readline},
	{"readint", 0, {}, cfunc_readint},
	{"shell", 1, {"cmd"}, cfunc_shell},
};

/* Register FFI functions. */
static bool
register_ffi(
	struct rt_env *rt)
{
	int i;

	for (i = 0; i < (int)(sizeof(ffi_items) / sizeof(struct ffi_item)); i++) {
		if (!rt_register_cfunc(rt,
				       ffi_items[i].name,
				       ffi_items[i].param_count,
				       ffi_items[i].param,
				       ffi_items[i].cfunc))
			return false;
	}

	return true;
}

/* Implementation of print() */
static bool
cfunc_print(
	struct rt_env *rt)
{
	struct rt_value msg;
	const char *s;
	float f;
	int i;
	int type;

	if (!rt_get_arg(rt, 0, &msg))
		return false;

	if (!rt_get_value_type(rt, &msg, &type))
		return false;

	switch (type) {
	case RT_VALUE_INT:
		if (!rt_get_int(rt, &msg, &i))
			return false;
		wide_printf("%i\n", i);
		break;
	case RT_VALUE_FLOAT:
		if (!rt_get_float(rt, &msg, &f))
			return false;
		wide_printf("%f\n", f);
		break;
	case RT_VALUE_STRING:
		if (!rt_get_string(rt, &msg, &s))
			return false;
		wide_printf("%s\n", s);
		break;
	default:
		wide_printf("[object]\n");
		break;
	}

	return true;
}

/* Implementation of readline() */
static bool
cfunc_readline(
	struct rt_env *rt)
{
	struct rt_value ret;
	char buf[1024];
	int len;

	memset(buf, 0, sizeof(buf));

	if (fgets(buf, sizeof(buf) - 1, stdin) == NULL)
		strcpy(buf, "");

	len = (int)strlen(buf);
	if (len > 0)
		buf[len - 1] = '\0';
	
	if (!rt_make_string(rt, &ret, buf))
		return false;
	if (!rt_set_return(rt, &ret))
		return false;

	return true;
}

/* Implementation of readint() */
static bool cfunc_readint(struct rt_env *rt)
{
	struct rt_value ret;
	char buf[1024];

	memset(buf, 0, sizeof(buf));

	if (fgets(buf, sizeof(buf) - 1, stdin) == NULL)
		strcpy(buf, "");
	
	rt_make_int(&ret, atoi(buf));
	if (!rt_set_return(rt, &ret))
		return false;

	return true;
}

/* Implementation of shell() */
static bool
cfunc_shell(
	struct rt_env *rt)
{
	struct rt_value cmd;
	struct rt_value ret;
	const char *s;
	int type;
	int cmd_ret;

	/* Get a "cmd" parameer. */
	if (!rt_get_arg(rt, 0, &cmd))
		return false;
	if (!rt_get_value_type(rt, &cmd, &type))
		return false;
	if (type != RT_VALUE_STRING) {
		wide_printf(_("shell(): Parameter not a string."));
		return false;
	}
	if (!rt_get_string(rt, &cmd, &s))
		return false;

	/* Run a command. */
	cmd_ret = system(s);

	/* Make a return value. */
	rt_make_int(&ret, cmd_ret);
	if (!rt_set_return(rt, &ret))
		return false;

	return true;
}

/* For translation. */
const char *get_system_language(void)
{
	return lang_code;
}
