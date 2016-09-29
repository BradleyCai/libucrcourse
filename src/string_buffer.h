/*
 * string_buffer.h
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#ifndef __STRING_BUFFER_H
#define __STRING_BUFFER_H

#include <stddef.h>

struct string_buffer {
    char *data;
    size_t length;
    size_t capacity;
};

int strbuf_init(struct string_buffer *strbuf, size_t capacity);
void strbuf_destroy(struct string_buffer *strbuf);
int strbuf_append(struct string_buffer *strbuf, const char *str);
int strbuf_append_char(struct string_buffer *strbuf, char ch);
int strbuf_append_data(struct string_buffer *strbuf, const char *data, size_t len);
int strbuf_resize(struct string_buffer *strbuf, size_t new_capacity);

#endif /* __STRING_BUFFER_H */

