/* -*- tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

/*
 * CLI Main
 */

#include "compat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define BUF_SIZE	(1024)

#if defined(TARGET_WINDOWS)
#define SEP "\\"
#else
#define SEP "/"
#endif

const char main_fuel_text[] =
	"func setup() {\n"
        "    // This function is called before creating a window.\n"
	"    return {\n"
	"        title: \"My Game\",\n"
	"        width: 640,\n"
	"        height: 480\n"
	"    };\n"
	"}\n"
	"\n"
	"func start() {\n"
	"    // This function is called before starting a game.\n"
	"}\n"
	"\n"
	"func frame() {\n"
	"    // This function is called every frame.\n"
	"}\n";	

int command_help(int argc, char *argv[]);
int command_create(int argc, char *argv[]);
int command_run(int argc, char *argv[]);
int command_export(int argc, char *argv[]);
int export_windows(char *argv0, char *outdir);
int export_macos(char *argv0, char *outdir);
int export_linux(char *argv0, char *outdir);
int export_ios(char *argv0, char *outdir);
int export_android(char *argv0, char *outdir);
int export_web(char *argv0, char *outdir);
int export_unity(char *argv0, char *outdir);
bool read_line(char *buf, size_t size);
bool read_yes_no(bool is_default_yes, bool is_default_no);
bool check_file_exist(const char *file);
bool check_dir_exist(const char *dir);
bool create_dir(const char *dir);
bool create_file(const char *file, const char *text);
bool copy_file(const char *src, const char *dst);
bool copy_dir(const char *src, const char *dst);
bool get_bin_dir(const char *argv0, char *buf, size_t size);
bool get_inst_dir(const char *argv0, char *buf, size_t size);

int main(int argc, char *argv[])
{
	char *cmd;

	if (argc == 1)
		return command_help(argc, argv);

	cmd = argv[1];
	if (strcmp(cmd, "create") == 0)
		return command_create(argc, argv);
	else if (strcmp(cmd, "run") == 0)
		return command_run(argc, argv);
	else if (strcmp(cmd, "export") == 0)
		return command_export(argc, argv);

	printf("Unknown command.\n");

	return 1;
}

int command_help(int argc, char *argv[])
{
	char buf[BUF_SIZE];

	printf("Fuel Engine CLI\n");
	printf("\n");
	printf("Specify a command.\n");
	printf("  create ... create a project.\n");
	printf("  run    ... run a game in the current directory.\n");
	printf("  export ... export a game for a specified platform.\n");
	printf("\n");

	return 1;
}

int command_create(int argc, char *argv[])
{
	char proj[BUF_SIZE];
	char sub[BUF_SIZE];
	int len;

	/* Read a project name. */
	printf("Enter a new project name: ");
	if (!read_line(proj, BUF_SIZE))
		return 1;

	/* Confirm. */
	printf("Are you sure you want to create a directory named %s? <Y/n> ", proj);
	if (!read_yes_no(true, false))
		return 1;

	/* Check for an existing directory. */
	if (check_dir_exist(proj)) {
		printf("Directory already exists.\n");
		return 1;
	}

	/* Create a project directory. */
	if (!create_dir(proj)) {
		printf("Cannot create a directory.\n");
		return 1;
	}

	/* Create an images directory. */
	strncpy(sub, proj, BUF_SIZE - 1);
	strncat(sub, "/images", BUF_SIZE - 1);
	if (!create_dir(sub)) {
		printf("Cannot create a directory.\n");
		return 1;
	}

	/* Create an sounds directory. */
	strncpy(sub, proj, BUF_SIZE - 1);
	strncat(sub, "/sounds", BUF_SIZE - 1);
	if (!create_dir(sub)) {
		printf("Cannot create a directory.\n");
		return 1;
	}

	/* Create a fonts directory. */
	strncpy(sub, proj, BUF_SIZE - 1);
	strncat(sub, "/fonts", BUF_SIZE - 1);
	if (!create_dir(sub)) {
		printf("Cannot create a directory.\n");
		return 1;
	}

	/* Create a scripts directory. */
	strncpy(sub, proj, BUF_SIZE - 1);
	strncat(sub, "/scripts", BUF_SIZE - 1);
	if (!create_dir(sub)) {
		printf("Cannot create a directory.\n");
		return 1;
	}

	/* Create a main.fuel file. */
	strncpy(sub, proj, BUF_SIZE - 1);
	strncat(sub, "/main.fuel", BUF_SIZE - 1);
	if (!create_file(sub, main_fuel_text)) {
		printf("Cannot create a file.\n");
		return 1;
	}

	printf("Succeeded.\n");

	return 0;
}

int command_run(int argc, char *argv[])
{
	char dir[BUF_SIZE];
	char cmd[BUF_SIZE];

	if (!check_file_exist("main.fuel")) {
		printf("Cannot find main.fuel file.\n");
		return 1;
	}

	if (!get_bin_dir(argv[0], dir, BUF_SIZE))
		strncpy(dir, "", BUF_SIZE - 1);

#if defined(TARGET_MACOS) && !defined(TARGET_POSIX)
	/* For macOS. */
	if (!check_dir_exist(".FuelCore.app")) {
		strncpy(cmd, "hdiutil attach ", BUF_SIZE);
		strncat(cmd, dir, BUF_SIZE);
		strncat(cmd, "/fuelcore.dmg", BUF_SIZE);
		printf("%s\n", cmd);
		if (system(cmd) != 0) {
			printf("Mount failed.\n");
			return 1;
		}
		printf("cp -Rav /Volumes/FuelCore/FuelCore.app .FuelCore.app\n");
		if (system("cp -Rav /Volumes/FuelCore/FuelCore.app .FuelCore.app") != 0) {
			printf("Copy failed.\n");
			return 1;
		}
		printf("hdiutil detach /Volumes/FuelCore\n");
		if (system("hdiutil detach /Volumes/FuelCore") != 0) {
			printf("Unmount failed.\n");
			return 1;
		}
	}

	system("open .FuelCore.app");
#elif defined(TARGET_WINDOWS)
	/* For Windows. */
	char fuelcore_path[BUF_SIZE];
	strncpy(fuelcore_path, dir, BUF_SIZE - 1);
	strncat(fuelcore_path, "\\fuelcore.exe", BUF_SIZE - 1);
	printf("%s\n", fuelcore_path);
	if (check_file_exist(fuelcore_path))
		system(fuelcore_path);
	else
		system("fuelcore");
#else
	/* For POSIX. */
	char fuelcore_path[BUF_SIZE];
	strncpy(fuelcore_path, dir, BUF_SIZE - 1);
	strncat(fuelcore_path, "/fuelcore", BUF_SIZE - 1);
	if (check_file_exist(fuelcore_path))
		system(fuelcore_path);
	else
		system("fuelcore");
#endif

	return 0;
}

int command_export(int argc, char *argv[])
{
	char buf[BUF_SIZE];

#if defined (USE_BINDIST)
	if (argc < 3) {
		printf("Specify a platform.\n");
		printf("  windows\n");
		printf("  macos\n");
		printf("  linux\n");
		printf("  ios\n");
		printf("  android\n");
		printf("  web\n");
		printf("  unity\n");
		return 1;
	}
	if (argc < 4) {
		printf("Specify a output directory.\n");
		return 1;
	}

	if (strcmp(argv[2], "windows") == 0)
		return export_windows(argv[0], argv[3]);
	else if (strcmp(argv[2], "macos") == 0)
		return export_macos(argv[0], argv[3]);
	else if (strcmp(argv[2], "linux") == 0)
		return export_linux(argv[0], argv[3]);
	else if (strcmp(argv[2], "ios") == 0)
		return export_ios(argv[0], argv[3]);
	else if (strcmp(argv[2], "android") == 0)
		return export_android(argv[0], argv[3]);
	else if (strcmp(argv[2], "web") == 0)
		return export_web(argv[0], argv[3]);
	else if (strcmp(argv[2], "unity") == 0)
		return export_unity(argv[0], argv[3]);

	printf("Unknown target.\n");
	return 1;
#else
	printf("Export is not supported in this compile configuration.\n");
	return 0;
#endif
}

#if defined (USE_BINDIST)
int export_windows(char *argv0, char *outdir)
{
	char src[BUF_SIZE];
	char dest[BUF_SIZE];
	char pack[BUF_SIZE];

	/* Make a directory. */
	if (!create_dir(outdir)) {
		printf("Failed to create a directory.\n");
		return 1;
	}

	/* Copy fuelcore.exe file. */
	get_inst_dir(argv0, src, BUF_SIZE); /*  */
	strncat(src, SEP, BUF_SIZE - 1);
	strncat(src, "windows", BUF_SIZE - 1);
	strncat(src, SEP, BUF_SIZE - 1);
	strncat(src, "fuelcore.exe", BUF_SIZE - 1);
	strncpy(dest, outdir, BUF_SIZE - 1);
	strncat(dest, SEP, BUF_SIZE - 1);
	strncat(dest, "fuelcore.exe", BUF_SIZE - 1);
	if (!copy_file(src, dest)) {
		printf("Cannot copy files.\n");
		return 1;
	}

	/* Do pack. */
	get_bin_dir(argv0, pack, BUF_SIZE);
	strncat(pack, SEP, BUF_SIZE - 1);
	strncat(pack, "fuelpack ", BUF_SIZE - 1);
	strncat(pack, outdir, BUF_SIZE - 1);
	strncat(pack, SEP, BUF_SIZE - 1);
	strncat(pack, "fuel.tank main.fuel images sounds fonts scripts", BUF_SIZE - 1);
	printf("%s\n", pack);
	if (system(pack) != 0) {
		printf("Failed.\n");
		return 1;
	}

	printf("Succeeded.\n");

	return 0;
}
#endif

#if defined (USE_BINDIST)
int export_macos(char *argv0, char *outdir)
{
	char vsdir[BUF_SIZE];
	char pack[BUF_SIZE];

	printf("Copying assets.\n");

	/* Copy a template directory. */
	get_inst_dir(argv0, vsdir, BUF_SIZE);
	strncat(vsdir, "/projects/macos", BUF_SIZE - 1);
	if (!copy_dir(vsdir, outdir)) {
		printf("Cannot copy files.\n");
		return 1;
	}

	/* Do pack. */
	get_inst_dir(argv0, pack, BUF_SIZE);
	strncat(pack, "/fuelpack ", BUF_SIZE - 1);
	strncat(pack, outdir, BUF_SIZE - 1);
	strncat(pack, " main.fuel images sounds fonts scripts", BUF_SIZE - 1);
	system(pack);

	printf("Succeeded.\n");

	return 0;
}
#endif

#if defined (USE_BINDIST)
int export_linux(char *argv0, char *outdir)
{
	char src[BUF_SIZE];
	char dest[BUF_SIZE];
	char pack[BUF_SIZE];

	/* Make a directory. */
	if (!create_dir(outdir)) {
		printf("Failed to create a directory.\n");
		return 1;
	}

	/* Copy linux-x86_64/fuelcore file. */
	get_inst_dir(argv0, src, BUF_SIZE); /*  */
	strncat(src, "/linux-x86_64/fuelcore", BUF_SIZE - 1);
	strncpy(dest, outdir, BUF_SIZE - 1);
	strncat(dest, "/", BUF_SIZE - 1);
	if (!copy_file(src, dest)) {
		printf("Cannot copy files.\n");
		return 1;
	}

	/* Copy linux-x86_64/fuelcore file. */
	get_inst_dir(argv0, src, BUF_SIZE); /*  */
	strncat(src, "/linux-arm64/fuelcore", BUF_SIZE - 1);
	strncpy(dest, outdir, BUF_SIZE - 1);
	strncat(dest, "/", BUF_SIZE - 1);
	if (!copy_file(src, dest)) {
		printf("Cannot copy files.\n");
		return 1;
	}

	/* Do pack. */
	get_bin_dir(argv0, pack, BUF_SIZE);
	strncat(pack, "/fuelpack ", BUF_SIZE - 1);
	strncat(pack, outdir, BUF_SIZE - 1);
	strncat(pack, "/fuel.tank main.fuel images sounds fonts scripts", BUF_SIZE - 1);
	printf("%s\n", pack);
	system(pack);

	printf("Succeeded.\n");

	return 0;
}
#endif

#if defined (USE_BINDIST)
int export_ios(char *argv0, char *outdir)
{
	char proj[BUF_SIZE];
	char dest[BUF_SIZE];
	char transpile[BUF_SIZE];

	/* Copy a template directory. */
	get_inst_dir(argv0, proj, BUF_SIZE);
	strncat(proj, "/projects/ios", BUF_SIZE - 1);
	if (!copy_dir(proj, outdir)) {
		printf("Cannot copy files.\n");
		return 1;
	}

	/* Copy assets. */
	strncpy(dest, outdir, BUF_SIZE - 1);
	strncat(dest, "/", BUF_SIZE - 1);
	if (!copy_dir("./images", dest)) {
		printf("Cannot copy images/ directory.\n");
		return 1;
	}
	if (!copy_dir("./sounds", dest)) {
		printf("Cannot copy images/ directory.\n");
		return 1;
	}
	if (!copy_dir("./fonts", dest)) {
		printf("Cannot copy images/ directory.\n");
		return 1;
	}
	if (!copy_dir("./scripts", dest)) {
		printf("Cannot copy images/ directory.\n");
		return 1;
	}

	/* Transpile. */
	if (!get_bin_dir(argv0, transpile, BUF_SIZE)) {
		printf("Could not get path.\n");
		return 1;
	}
	strncat(transpile, "/fuellang -c -o ", BUF_SIZE - 1);
	strncat(transpile, outdir, BUF_SIZE - 1);
	strncat(transpile, "/ios/transpile.c main.fuel", BUF_SIZE - 1);
	printf("Compiling scripts to C.\n");
	printf("%s\n", transpile);
	if (system(transpile) != 0) {
		printf("Cannot compile the code.\n");
		return 1;
	}

	printf("Succeeded.\n");

	return 0;
}
#endif

#if defined (USE_BINDIST)
int export_android(char *argv0, char *outdir)
{
	char proj[BUF_SIZE];
	char dest[BUF_SIZE];
	char transpile[BUF_SIZE];

	/* Copy a template directory. */
	get_inst_dir(argv0, proj, BUF_SIZE);
	strncat(proj, "/projects/android", BUF_SIZE - 1);
	if (!copy_dir(proj, outdir)) {
		printf("Cannot copy files.\n");
		return 1;
	}

	/* Copy assets. */
	strncpy(dest, outdir, BUF_SIZE - 1);
	strncat(dest, "/app/src/main/assets/", BUF_SIZE - 1);
	if (!copy_dir("./images", dest)) {
		printf("Cannot copy images/ directory.\n");
		return 1;
	}
	if (!copy_dir("./sounds", dest)) {
		printf("Cannot copy images/ directory.\n");
		return 1;
	}
	if (!copy_dir("./fonts", dest)) {
		printf("Cannot copy images/ directory.\n");
		return 1;
	}
	if (!copy_dir("./scripts", dest)) {
		printf("Cannot copy images/ directory.\n");
		return 1;
	}

	/* Transpile. */
	if (!get_bin_dir(argv0, transpile, BUF_SIZE)) {
		printf("Could not get path.\n");
		return 1;
	}
	strncat(transpile, "/fuellang -j -o ", BUF_SIZE - 1);
	strncat(transpile, outdir, BUF_SIZE - 1);
	strncat(transpile, "/app/src/main/java/FuelLang.java main.fuel", BUF_SIZE - 1);
	printf("Compiling scripts to Java.\n");
	printf("%s\n", transpile);
	if (system(transpile) != 0) {
		printf("Cannot compile the code.\n");
		return 1;
	}

	printf("Succeeded.\n");

	return 0;
}
#endif
	
#if defined (USE_BINDIST)
int export_web(char *argv0, char *outdir)
{
	char proj[BUF_SIZE];
	char src[BUF_SIZE];
	char dest[BUF_SIZE];
	char pack[BUF_SIZE];

	/* Copy a template directory. */
	get_inst_dir(argv0, proj, BUF_SIZE);
	strncat(proj, "/projects/wasm", BUF_SIZE - 1);
	if (!copy_dir(proj, outdir)) {
		printf("Cannot copy files.\n");
		return 1;
	}

	/* Do pack. */
	get_bin_dir(argv0, pack, BUF_SIZE);
	strncat(pack, "/fuelpack ", BUF_SIZE - 1);
	strncat(pack, outdir, BUF_SIZE - 1);
	strncat(pack, "/fuel.tank main.fuel images sounds fonts scripts", BUF_SIZE - 1);
	printf("%s\n", pack);
	system(pack);

	printf("Succeeded.\n");

	return 0;
}
#endif

#if defined (USE_BINDIST)
int export_unity(char *argv0, char *outdir)
{
	printf("Not implemented.\n");
	return 1;
}
#endif

bool read_line(char *buf, size_t size)
{
	size_t len;

	if (size < 3)
		return false;
	
	if (fgets(buf, size, stdin) == NULL)
		return false;
	if (strcmp(buf, "") == 0 || strcmp(buf, "\n") == 0)
		return false;

	len = strlen(buf);
	if (len < 2)
		return false;

	buf[len - 1] = '\0';

	return true;
}

bool read_yes_no(bool is_default_yes, bool is_default_no)
{
	char buf[BUF_SIZE];

	while (1) {
		if (fgets(buf, BUF_SIZE - 2, stdin) == NULL)
			return false;
		if (strcmp(buf, "") == 0)
			continue;
		if (strlen(buf) < 1)
			continue;
		if (buf[0] == '\n') {
			if (is_default_yes)
				return true;
			if (is_default_no)
				return true;
		}
		if (buf[0] == 'Y' || buf[0] == 'y')
			return true;
		if (buf[0] == 'N' || buf[0] == 'n')
			return true;
	}

	/* Never come here. */
	return true;
}

#ifdef TARGET_WINDOWS

/*
 * Windows Part
 */

#include <windows.h>

bool check_file_exist(const char *file)
{
	DWORD dwAttrib;

	dwAttrib = GetFileAttributesA(file);
	if (dwAttrib == INVALID_FILE_ATTRIBUTES)
		return false;
	if (dwAttrib & FILE_ATTRIBUTE_DIRECTORY)
		return false;

	return true;
}

bool check_dir_exist(const char *dir)
{
	DWORD dwAttrib;

	dwAttrib = GetFileAttributesA(dir);
	if (dwAttrib == INVALID_FILE_ATTRIBUTES)
		return false;
	if (!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
		return false;

	return true;
}

bool create_dir(const char *dir)
{
	if (!CreateDirectoryA(dir, NULL))
		return false;

	return true;
}

bool get_bin_dir(const char *argv0, char *buf, size_t size)
{
	DWORD dwLength;
	int i;

	dwLength = GetModuleFileNameA(NULL, buf, size);
	if (dwLength == 0 || dwLength == MAX_PATH)
		return false;

	for (i = (int)dwLength - 1; i >= 0; i--)
	{
		if (buf[i] == '\\')
		{
			buf[i] = '\0';
			break;
		}
	}

	return true;
}

bool get_inst_dir(const char *argv0, char *buf, size_t size)
{
	int i;

	if (!get_bin_dir(argv0, buf, size))
		return false;

	for (i = strlen(buf) - 1; i >= 0; i--)
	{
		if (buf[i] == '\\')
		{
			buf[i] = '\0';
			break;
		}
	}

	return true;
}

bool copy_file(const char *src, const char *dst)
{
	char cmd[BUF_SIZE];

	if (!CopyFileA(src, dst, FALSE))
	{
		printf("Failed to copy %s to %s\n", src, dst);
		return false;
	}

	return true;
}

bool copy_dir(const char *src, const char *dst)
{
	char buf[BUF_SIZE];
	WIN32_FIND_DATA fd;
	HANDLE hFind;

	if (!CreateDirectoryA(dst, NULL))
	{
		printf("Failed to create directory %s\n", dst);
		return false;
	}

	strncpy(buf, src, BUF_SIZE - 1);
	strncat(buf, "\\*", BUF_SIZE - 1);
	hFind = FindFirstFileA(buf, &fd);

	do
	{
		char src2[BUF_SIZE];
		char dst2[BUF_SIZE];

		strncpy(src2, src, BUF_SIZE - 1);
		strncat(src2, "\\", BUF_SIZE - 1);
		strncat(src2, fd.cFileName, BUF_SIZE - 1);

		strncpy(dst2, dst, BUF_SIZE - 1);
		strncat(dst2, "\\", BUF_SIZE - 1);
		strncat(dst2, fd.cFileName, BUF_SIZE - 1);

		if (strcmp(fd.cFileName, ".") == 0)
			continue;
		if (strcmp(fd.cFileName, "..") == 0)
			continue;
		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (!copy_dir(src2, dst2))
				return false;
		}
		else
		{
			if (!CopyFileA(src2, dst2, FALSE))
			{
				printf("Failed to copy %s to %s\n", src, dst);
				return false;
			}
		}
	}
	while (FindNextFileA(hFind, &fd));
	FindClose(hFind);

	return true;
}

#else

/*
 * POSIX Part
 */

#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <libgen.h>

bool check_file_exist(const char *file)
{
	struct stat st;

	if (stat(file, &st) != 0)
		return false;
	if (!S_ISREG(st.st_mode))
		return false;

	return true;
}

bool check_dir_exist(const char *dir)
{
	struct stat st;

	if (stat(dir, &st) != 0)
		return false;
	if (!S_ISDIR(st.st_mode))
		return false;

	return true;
}

bool create_dir(const char *dir)
{
	if (mkdir(dir, 0755) == -1)
		return false;

	return true;
}

bool get_bin_dir(const char *argv0, char *buf, size_t size)
{
#if defined(TARGET_LINUX)
	char resolved_path[BUF_SIZE];
	char dir_path[BUF_SIZE];
	char *dir;
	ssize_t len;

	len = readlink("/proc/self/exe", resolved_path, BUF_SIZE - 1);
	if (len == -1)
		return false;
	resolved_path[len] = '\0';

	strncpy(dir_path, resolved_path, BUF_SIZE - 1);
	dir = dirname(dir_path);

	strncpy(buf, dir, size - 1);
	dir_path[size - 1] = '\0';

	return true;
#else
	return false;
#endif
}

bool get_inst_dir(const char *argv0, char *buf, size_t size)
{
	char resolved_path[BUF_SIZE];
	char dir_path[BUF_SIZE];
	char *dir;

	if (realpath(argv0, resolved_path) == NULL)
		return false;
	strncpy(dir_path, resolved_path, BUF_SIZE - 1);
	dir = dirname(dir_path);
	dir = dirname(dir);
	strncpy(buf, dir, size - 1);
	dir_path[size - 1] = '\0';

	return true;
}

bool copy_file(const char *src, const char *dst)
{
	char cmd[BUF_SIZE];

	strncpy(cmd, "cp ", BUF_SIZE - 1);
	strncat(cmd, src, BUF_SIZE - 1);
	strncat(cmd, " ", BUF_SIZE - 1);
	strncat(cmd, dst, BUF_SIZE - 1);
	printf("%s\n", cmd);
	if (system(cmd) != 0)
		return false;

	return true;
}

bool copy_dir(const char *src, const char *dst)
{
	char cmd[BUF_SIZE];

	strncpy(cmd, "cp -R ", BUF_SIZE - 1);
	strncat(cmd, src, BUF_SIZE - 1);
	strncat(cmd, " ", BUF_SIZE - 1);
	strncat(cmd, dst, BUF_SIZE - 1);
	printf("%s\n", cmd);
	if (system(cmd) != 0)
		return false;

	return true;
}

#endif

bool create_file(const char *file, const char *text)
{
	FILE *fp;

	fp = fopen(file, "wb");
	if (fp == NULL)
		return false;

	if (fwrite(text, strlen(text), 1, fp) != 1) {
		fclose(fp);
		return false;
	}

	fclose(fp);

	return true;
}
