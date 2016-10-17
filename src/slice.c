/*
 * slice.c
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#include <stdlib.h>
#include <string.h>

#include "slice.h"

char *copy_slice(const char *str, const struct slice *slice)
{
	char *buf = malloc(slice->length + 1);
	if (!buf) {
		return NULL;
	}

	memcpy(buf, str + slice->start, slice->length);
	buf[slice->length] = '\0';
	return buf;
}

