/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

#include "engine.h"

/* The runtime. */
struct rt_env *rt;

/* Forward Declaration */
static bool setup_variables(void);
static bool load_main_file(void);
static bool call_setup(char **title, int *width, int *height);

/*
 * Create a VM.
 */
bool create_vm(char **title, int *width, int *height)
{
	/* Create a language runtime. */
	if (!rt_create(&rt))
		return false;

	/* Setup variables. */
	if (!setup_variables())
		return false;

	/* Load the "main.fuel" file. */
	if (!load_main_file())
		return false;

	/* Call "setup()" and get a title and window size. */
	if (!call_setup(title, width, height)) {
		log_error(_("%s:%d: error: %s\n"),
			  rt_get_error_file(rt),
			  rt_get_error_line(rt),
			  rt_get_error_message(rt));
		return false;
	}

	/* Install the API to the runtime. */
	if (!install_api(rt))
		return false;

	return true;
}

/* Setup global variables. */
static bool setup_variables(void)
{
	struct rt_value dict;
	bool succeeded;

	/* Try: */
	succeeded = false;
	do {
		/* Add a global variable "App". */
		if (!rt_make_empty_dict(rt, &dict))
			break;
		if (!rt_set_global(rt, "App", &dict))
			break;

		succeeded = true;
	} while (0);

	if (!succeeded) {
		log_error(_("error: %s\n"), rt_get_error_message(rt));
		return false;
	}

	return true;
}

/* Load "main.fuel". */
static bool load_main_file(void)
{
	char *buf;

	/* Load a file content, i.e., a script text. */
	if (!load_file("main.fuel", &buf, NULL))
		return false;

	/* Register the script text to the language runtime. */
	if (!rt_register_source(rt, "main.fuel", buf)) {
		log_error(_("%s:%d: error: %s"),
			  rt_get_error_file(rt),
			  rt_get_error_line(rt),
			  rt_get_error_message(rt));
		return false;
	}

	free(buf);

	return true;
}

/* Call "setup()" function to determin a title, width, and height. */
static bool call_setup(char **title, int *width, int *height)
{
	struct rt_value ret;
	struct rt_value title_val;
	struct rt_value width_val;
	struct rt_value height_val;
	const char *title_s;
	bool succeeded;

	succeeded = false;
	do {
		/* Call setup() and get a return dictionary. */
		if (!rt_call_with_name(rt, "setup", NULL, 0, NULL, &ret))
			break;

		/* Get the "title" element from the dictionary. */
		if (title != NULL) {
			if (!rt_get_dict_elem(rt, &ret, "title", &title_val))
				break;
			if (!rt_get_string(rt, &title_val, &title_s))
				break;
			*title = strdup(title_s);
		}

		/* Get the "width" element from the dictionary. */
		if (width != NULL) {
			if (!rt_get_dict_elem(rt, &ret, "width", &width_val))
				break;
			if (!rt_get_int(rt, &width_val, width))
				break;
		}

		/* Get the "height" element from the dictionary. */
		if (height != NULL) {
			if (!rt_get_dict_elem(rt, &ret, "height", &height_val))
				break;
			if (!rt_get_int(rt, &height_val, height))
				break;
		}

		succeeded = true;
	} while (0);
	if (!succeeded) {
		log_error(_("%s:%d: error: %s\n"),
			  rt_get_error_file(rt),
			  rt_get_error_line(rt),
			  rt_get_error_message(rt));
	}
	
	return true;
}

/*
 * Call a VM function.
 */
bool call_vm_raw_function(const char *func_name)
{
	struct rt_value ret;

	/* Call a function. */
	if (!rt_call_with_name(rt, func_name, NULL, 0, NULL, &ret)) {
		log_error(_("%s:%d: error: %s\n"),
			  rt_get_error_file(rt),
			  rt_get_error_line(rt),
			  rt_get_error_message(rt));
		return false;
	}

	return true;
}

/*
 * Call a tag function.
 */
bool call_vm_tag_function(void)
{
	struct tag *t;
	struct rt_value dict;
	int i;
	char func_name[256];
	struct rt_value func_val;
	struct rt_func *func;
	struct rt_value ret;

	/* Get a current command. */
	t = get_current_tag();
	if (t == NULL) {
		/* Reached to the end. Finish the game loop. */
		return false;
	}

	/* Make a parameter dictionary. */
	if (!rt_make_empty_dict(rt, &dict)) {
		log_error(_("In scenario %s:%d: runtime error.\n"),
			  get_tag_file_name(),
			  get_tag_line());
		return false;
	}

	/* Setup properties as dictionary items. */
	for (i = 0; i < t->prop_count; i++) {
		struct rt_value str;
		if (!rt_make_string(rt, &str, t->prop_value[i])) {
			log_error(_("In scenario %s:%d: runtime error.\n"),
				  get_tag_file_name(),
				  get_tag_line());
			return false;
		}
		if (!rt_set_dict_elem(rt, &dict, t->prop_name[i], &str)) {
			log_error(_("In scenario %s:%d: runtime error.\n"),
				  get_tag_file_name(),
				  get_tag_line());
			return false;
		}
	}

	/* Make a tag function name. */
	strlcpy(func_name, "tag_", sizeof(func_name));
	strlcat(func_name, t->tag_name, sizeof(func_name));

	/* Get a corresponding function.  */
	if (!rt_get_global(rt, func_name, &func_val)) {
		log_error(_("%s:%d: Tag \"%s\" not found.\n"),
			  get_tag_file_name(),
			  get_tag_line(),
			  t->tag_name);
		return false;
	}
	if (!rt_get_func(rt, &func_val, &func)) {
		log_error(_("%s:%d: \"tag_%s\" is not a function.\n"),
			  get_tag_file_name(),
			  get_tag_line(),
			  t->tag_name);
		return false;
	}

	/* Call the function. */
	if (!rt_call_with_name(rt, func_name, NULL, 1, &dict, &ret)) {
		log_error(_("In scenario %s:%d: Tag \"%s\" execution error.\n"),
			  get_tag_file_name(),
			  get_tag_line(),
			  t->tag_name);
		log_error(_("%s:%d: %s"),
			  rt_get_error_file(rt),
			  rt_get_error_line(rt),
			  rt_get_error_message(rt));
		return false;
	}

	return true;
}

/*
 * Set a VM integer.
 */
bool set_vm_int(const char *prop_name, int val)
{
	struct rt_value api, prop_val;

	if (!rt_get_global(rt, "API", &api))
		return false;
	rt_make_int(&prop_val, val);
	if (!rt_set_dict_elem(rt, &api, prop_name, &prop_val))
		return false;

	return true;
}
