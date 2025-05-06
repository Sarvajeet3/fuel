/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

#ifndef APP_RENDER_H
#define APP_RENDER_H

#include "compat.h"

bool load_texture(const char *fname, int *ret);
void render_texture(int dst_left, int dst_top, int dst_width, int dst_height,
		    int tex_id, int src_x, int src_y, int src_width,
		    int src_height, int alpha);

#endif
