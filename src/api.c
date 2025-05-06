/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

/*
 * API: The implementation of the engine API.
 */

#include "engine.h"

/* Forward declarations. */
static bool get_int_param(struct rt_env *rt, const char *name, int *ret);
#if 0
static bool get_float_param(struct rt_env *rt, const char *name, float *ret);
#endif
static bool get_string_param(struct rt_env *rt, const char *name, const char **ret);

/* debug() */
static bool debug(struct rt_env *rt)
{
	struct rt_value param;
	int type;
	bool succeeded;

	type = 0;
	succeeded = false;
	do {
		if (!rt_get_arg(rt, 0, &param))
			break;

		if (!rt_get_value_type(rt, &param, &type))
			break;

		succeeded = true;
	} while (0);
	if (!succeeded) {
		log_error(_("%s:%d: error: %s\n"),
			  rt_get_error_file(rt),
			  rt_get_error_line(rt),
			  rt_get_error_message(rt));
		return false;
	}

	switch (type) {
	case RT_VALUE_INT:
	{
		int d;
		rt_get_int(rt, &param, &d);
		printf("%d\n", d);
		break;
	}
	case RT_VALUE_FLOAT:
	{
		float f;
		rt_get_float(rt, &param, &f);
		printf("%f\n", f);
		break;
	}
	case RT_VALUE_STRING:
	{
		const char *s;
		rt_get_string(rt, &param, &s);
		printf("%s\n", s);
		break;
	}
	default:
		printf("[object]\n");
		break;
	}

	return true;
}

/* API.moveToTagFile() */
static bool API_moveToTagFile(struct rt_env *rt)
{
	const char *file;

	if (!get_string_param(rt, "file", &file))
		return false;

	if (!move_to_tag_file(file))
		return false;

	return true;
}

/* API.moveToNextTag() */
static bool API_moveToNextTag(struct rt_env *rt)
{
	UNUSED_PARAMETER(rt);

	move_to_next_tag();

	return true;
}

/* API.callTagFunction() */
static bool API_callTagFunction(struct rt_env *rt)
{
	UNUSED_PARAMETER(rt);

	if (!call_vm_tag_function())
		return false;

	return true;
}

/* API.loadTexture() */
static bool API_loadTexture(struct rt_env *rt)
{
	const char *file;
	int tex_id;
	struct rt_value ret;

	if (!get_string_param(rt, "file", &file))
		return false;

	if (!load_texture(file, &tex_id))
		return false;

	rt_make_int(&ret, tex_id);
	if (!rt_set_return(rt, &ret))
		return false;

	return true;
}

/* API.renderTexture() */
static bool API_renderTexture(struct rt_env *rt)
{
	int dst_left;
	int dst_top;
	int dst_width;
	int dst_height;
	int tex_id;
	int src_left;
	int src_top;
	int src_width;
	int src_height;
	int alpha;

	if (!get_int_param(rt, "dstLeft", &dst_left))
		return false;
	if (!get_int_param(rt, "dstTop", &dst_top))
		return false;
	if (!get_int_param(rt, "dstWidth", &dst_width))
		return false;
	if (!get_int_param(rt, "dstHeight", &dst_height))
		return false;
	if (!get_int_param(rt, "texId", &tex_id))
		return false;
	if (!get_int_param(rt, "srcLeft", &src_left))
		return false;
	if (!get_int_param(rt, "srcTop", &src_top))
		return false;
	if (!get_int_param(rt, "srcWidth", &src_width))
		return false;
	if (!get_int_param(rt, "srcHeight", &src_height))
		return false;
	if (!get_int_param(rt, "alpha", &alpha))
		return false;

	render_texture(dst_left,
		       dst_top,
		       dst_width,
		       dst_height,
		       tex_id,
		       src_left,
		       src_top,
		       src_width,
		       src_height,
		       alpha);

	return true;
}

/*
 * Helpers
 */

/* Get an integer parameter. */
static bool get_int_param(struct rt_env *rt, const char *name, int *ret)
{
	struct rt_value param, elem;

	if (!rt_get_arg(rt, 0, &param))
		return false;

	if (!rt_get_dict_elem(rt, &param, name, &elem))
		return false;

	switch (elem.type) {
	case RT_VALUE_INT:
		*ret = elem.val.i;
		break;
	case RT_VALUE_FLOAT:
		*ret = (int)elem.val.f;
		break;
	case RT_VALUE_STRING:
		*ret = atoi(elem.val.str->s);
		break;
	default:
		rt_error(rt, "Unexpected parameter value for %s.", name);
		return false;
	}

	return true;
}

#if 0
/* Get a float parameter. */
static bool get_float_param(struct rt_env *rt, const char *name, float *ret)
{
	struct rt_value param, elem;

	if (!rt_get_arg(rt, 0, &param))
		return false;

	if (!rt_get_dict_elem(rt, &param, name, &elem))
		return false;

	switch (elem.type) {
	case RT_VALUE_INT:
		*ret = (float)elem.val.i;
		break;
	case RT_VALUE_FLOAT:
		*ret = elem.val.f;
		break;
	case RT_VALUE_STRING:
		*ret = (float)atof(elem.val.str->s);
		break;
	default:
		rt_error(rt, "Unexpected parameter value for %s.", name);
		return false;
	}

	return true;
}
#endif

/* Get a string parameter. */
static bool get_string_param(struct rt_env *rt, const char *name, const char **ret)
{
	struct rt_value param, elem;
	static char buf[128];

	if (!rt_get_arg(rt, 0, &param))
		return false;

	if (!rt_get_dict_elem(rt, &param, name, &elem))
		return false;

	switch (elem.type) {
	case RT_VALUE_INT:
		snprintf(buf, sizeof(buf), "%d", elem.val.i);
		*ret = buf;
		break;
	case RT_VALUE_FLOAT:
		snprintf(buf, sizeof(buf), "%f", elem.val.f);
		*ret = buf;
		break;
	case RT_VALUE_STRING:
		*ret = elem.val.str->s;
		break;
	default:
		rt_error(rt, "Unexpected parameter value for %s.", name);
		return false;
	}

	return true;
}

/*
 * API Installation
 */

/*
 * Install API functions to a runtime.
 */
bool install_api(struct rt_env *rt)
{
	const char *params[] = {"param"};
	struct func {
		bool (*func)(struct rt_env *);
		const char *field;
		const char *name;
	} funcs[] = {
#define RTFUNC(name) {API_##name, #name, "api_" # name}
		{debug, NULL, "debug"},
		RTFUNC(moveToTagFile),
		RTFUNC(moveToNextTag),
		RTFUNC(callTagFunction),
		RTFUNC(loadTexture),
		RTFUNC(renderTexture),
	};
	const int tbl_size = sizeof(funcs) / sizeof(struct func);
	struct rt_value dict;
	int i;

	/* Make a global variable "API". */
	if (!rt_make_empty_dict(rt, &dict))
		return false;
	if (!rt_set_global(rt, "API", &dict))
		return false;

	/* Register functions. */
	for (i = 0; i < tbl_size; i++) {
		struct rt_value funcval;

		/* Register a cfunc. */
		if (!rt_register_cfunc(rt, funcs[i].name, 1, params, funcs[i].func))
			return false;

		/* Add to the API dictionary. */
		if (funcs[i].field != NULL) {
			/* Get a function value. */
			if (!rt_get_global(rt, funcs[i].name, &funcval))
				return false;

			/* Make a dictionary element. */
			if (!rt_set_dict_elem(rt, &dict, funcs[i].field, &funcval))
				return false;
		}
	}

	return true;
}
