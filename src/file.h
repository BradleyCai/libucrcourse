/*
 * file.h
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#ifndef __FILE_H
#define __FILE_H

#include <stddef.h>

char *get_file(const char *filename);
int save_file(const char *filename, const char *blob, size_t length);

#endif /* __FILE_H */

