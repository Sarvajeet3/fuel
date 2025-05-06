/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

/*
 * API: The implementation of the engine API.
 */

#ifndef APP_API_H
#define APP_API_H

#include "compat.h"
#include "lang/lang.h"

/* Install API functions to a runtime. */
bool install_api(struct rt_env *rt);

#endif
