/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

#include "engine.h"

#include <locale.h>

struct image *img;

int pos_x;
int pos_y;

/* Forward declaration. */

/*
 * This function is called when the app is going to be initialized.
 */
bool on_event_boot(char **title, int *width, int *height)
{
	/* Create a VM and call setup(). */
	if (!create_vm(title, width, height))
		return false;

	return true;
}

/*
 * This function is called right before the game loop.
 */
bool on_event_start(void)
{
	set_vm_int("mousePosX", 0);
	set_vm_int("mousePosY", 0);

	call_vm_raw_function("start");

	return true;
}

/*
 * This function is called every frame periodically.
 */
bool on_event_frame(void)
{
	call_vm_raw_function("frame");

	set_vm_int("isMouseLeftPressed", 0);
	set_vm_int("isMouseRightPressed", 0);

	/* Continue the game loop. */
	return true;
}

void on_event_stop(void)
{
}

void on_event_key_press(int key)
{
	UNUSED_PARAMETER(key);
}

void on_event_key_release(int key)
{
	UNUSED_PARAMETER(key);
}

void on_event_mouse_press(int button, int x, int y)
{
	set_vm_int("mousePosX", x);
	set_vm_int("mousePosY", y);

	if (button == MOUSE_LEFT)
		set_vm_int("isMouseLeftPressed", 1);
	else
		set_vm_int("isMouseRightPressed", 1);
}

void on_event_mouse_release(int button, int x, int y)
{
	set_vm_int("mousePosX", x);
	set_vm_int("mousePosY", y);

	if (button == MOUSE_LEFT)
		set_vm_int("isMouseLeftPressed", 0);
	else
		set_vm_int("isMouseRightPressed", 0);
}

void on_event_mouse_move(int x, int y)
{
	set_vm_int("mousePosX", x);
	set_vm_int("mousePosY", y);
}

void on_event_touch_cancel(void)
{
}

void on_event_swipe_down(void)
{
}

void on_event_swipe_up(void)
{
}
