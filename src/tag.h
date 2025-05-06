/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

/*
 * tag.h: Tag Management
 */

#ifndef APP_TAG_H
#define APP_TAG_H

#include "compat.h"

/* Maximum properties in a tag. */
#define PROP_MAX	128

/* Command struct. */
struct tag {
	char *tag_name;
	int prop_count;
	char *prop_name[PROP_MAX];
	char *prop_value[PROP_MAX];
	int line;
};

bool init_tag(void);
void cleanup_tag(void);
const char *get_tag_file_name(void);
int get_tag_line(void);
struct tag *get_current_tag(void);
bool move_to_tag_file(const char *file);
void move_to_next_tag(void);

#endif
