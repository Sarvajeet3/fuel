/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

/*
 * common.h: Common routines.
 */

#include "engine.h"

bool load_file(const char *file, char **buf, size_t *size)
{
	struct rfile *f;
	size_t file_size, read_size;

	assert(buf != NULL);

	if (!open_rfile(file, &f)) {
		log_error(_("Cannot open file \"%s\"."), file);
		return false;
	}

	if (!get_rfile_size(f, &file_size)) {
		log_error(_("Cannot get the size of file \"%s\"."), file);
		return false;
	}

	if (buf != NULL) {
		*buf = malloc(file_size + 1);
		if (*buf == NULL) {
			log_out_of_memory();
			return false;
		}

		if (!read_rfile(f, *buf, file_size, &read_size)) {
			log_error("Cannot read file \"%s\".", file);
			free(buf);
			return false;
		}

		(*buf)[file_size] = '\0';
	}

	close_rfile(f);

	if (size != NULL)
		*size = file_size;

	return true;
}
