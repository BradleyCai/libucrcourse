/*
 * string_buffer.c
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#include <stdlib.h>
#include <string.h>

#include "string_buffer.h"

#define MIN(x, y)	(((x) < (y)) ? (x) : (y))
#define MAX(x, y)	(((x) > (y)) ? (x) : (y))

int strbuf_init(struct string_buffer *strbuf, size_t capacity)
{
	strbuf->data = malloc(capacity);
	if (!strbuf->data) {
		return -1;
	}

	strbuf->length = 0;
	strbuf->capacity = capacity;
	return 0;
}

void strbuf_destroy(struct string_buffer *strbuf)
{
	free(strbuf->data);
}

int strbuf_append(struct string_buffer *strbuf, const char *str)
{
	return strbuf_append_data(strbuf, str, strlen(str));
}

int strbuf_append_data(struct string_buffer *strbuf, const char *data, size_t len)
{
	if (strbuf->length + len > strbuf->capacity) {
		if (strbuf_resize(strbuf, MAX(strbuf->capacity * 2, strbuf->length + len))) {
			return -1;
		}
	}

	memcpy(strbuf->data + strbuf->length, data, len);
	strbuf->length += len;
	return 0;
}

int strbuf_append_char(struct string_buffer *strbuf, char ch)
{
	if (strbuf->length + 1 > strbuf->capacity) {
		if (strbuf_resize(strbuf, strbuf->capacity + 10)) {
			return -1;
		}
	}

	strbuf->data[strbuf->length++] = ch;
	return 0;
}

int strbuf_resize(struct string_buffer *strbuf, size_t new_capacity)
{
	char *new_data = realloc(strbuf->data, new_capacity);
	if (!new_data) {
		return -1;
	}

	strbuf->data = new_data;
	strbuf->capacity = new_capacity;
	strbuf->length = MIN(strbuf->length, new_capacity);
	return 0;
}

