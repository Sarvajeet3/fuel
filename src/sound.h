/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

#ifndef APP_SOUND_H
#define APP_SOUND_H

#include "compat.h"

bool play_sound_stream(int stream, const char *file);
bool stop_sound_stream(int stream);

#endif
