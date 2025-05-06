/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

/*
 * Renderer
 */

#include "engine.h"

#define TEXTURE_COUNT	(256)

struct texture_entry {
	bool is_used;
	struct image *img;
};

/* Texture table. */
static struct texture_entry tex_tbl[TEXTURE_COUNT];

/* Forward Declaration */
static int search_free_entry(void);

/*
 * Load a texture.
 */
bool load_texture(const char *fname, int *ret)
{
	int index;
	const char *ext;
	char *data;
	size_t size;

	/* Allocate a texture entry. */
	index = search_free_entry();
	if (index == -1) {
		log_error("Too many textures.");
		return false;
	}

	/* Get a file extension. */
	ext = strrchr(fname, '.');
	if (ext == NULL) {
		log_error("Cannot determine a file type for \"%s\".", fname);
		return false;
	}

	/* Load a file content. */
	if (!load_file(fname, &data, &size))
		return false;

	/* Load an image. */
	if (strcasecmp(ext, ".jpg") == 0 || strcasecmp(ext, ".jpeg") == 0) {
		if (!create_image_with_webp((const uint8_t *)data, size, &tex_tbl[index].img)) {
			log_error("Cannot load an image \"%s\".", fname);
			return false;
		}
	} else if (strcasecmp(ext, ".webp") == 0) {
		if (!create_image_with_webp((const uint8_t *)data, size, &tex_tbl[index].img)) {
			log_error("Cannot load an image \"%s\".", fname);
			return false;
		}
	} else {
		if (!create_image_with_png((const uint8_t *)data, size, &tex_tbl[index].img)) {
			log_error("Cannot load an image \"%s\".", fname);
			return false;
		}
	}
	free(data);

	/* Fill alpha channel. */
	fill_image_alpha(tex_tbl[index].img);
	notify_image_update(tex_tbl[index].img);

	/* Mark as used. */
	tex_tbl[index].is_used = true;

	/* Succeeded. */
	*ret = index;
	return true;
}

/* Search a free texture index. */
static int search_free_entry(void)
{
	int i;

	for (i = 0; i < TEXTURE_COUNT; i++) {
		if (!tex_tbl[i].is_used)
			return i;
	}
	return -1;
}

/*
 * Render a texture.
 */
void
render_texture(
	int dst_left,
	int dst_top,
	int dst_width,
	int dst_height,
	int tex_id,
	int src_left,
	int src_top,
	int src_width,
	int src_height,
	int alpha)
{
	struct texture_entry *t;

	assert(tex_id >= 0 &&  tex_id < TEXTURE_COUNT);

	t = &tex_tbl[tex_id];
	assert(t->is_used);
	assert(t->img != NULL);

	render_image_normal(dst_left,
			    dst_top,
			    dst_width,
			    dst_height,
			    t->img,
			    src_left,
			    src_top,
			    src_width,
			    src_height,
			    alpha);
}
