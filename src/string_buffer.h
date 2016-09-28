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

#endif /* __STRING_BUFFER_H */

