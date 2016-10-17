/*
 * slice.h
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#ifndef __SLICE_H
#define __SLICE_H

#include <stddef.h>

struct slice {
	size_t start;
	size_t length;
};

char *copy_slice(const char *str, const struct slice *slice);

#endif /* __SLICE_H */

