/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

/*
 * Sound
 */

#include "engine.h"

/* Wave table. */
static struct wave *wave_tbl[SOUND_TRACKS];

bool play_sound_stream(int stream, const char *file)
{
	if (stream < 0 || stream >= SOUND_TRACKS) {
		log_error("Invalid stream index.");
		return false;
	}

	wave_tbl[stream] = create_wave_from_file(file, false);
	if (wave_tbl[stream] == NULL)
		return false;

	if (!play_sound(stream, wave_tbl[stream]))
		return false;

	return true;
}

bool stop_sound_stream(int stream)
{
	if (stream < 0 || stream >= SOUND_TRACKS) {
		log_error("Invalid stream index.");
		return false;
	}

	stop_sound(stream);

	destroy_wave(wave_tbl[stream]);
	wave_tbl[stream] = NULL;

	return true;
}
