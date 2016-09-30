/*
 * blob.h
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#ifndef __BLOB_H
#define __BLOB_H

#include <stddef.h>

char *get_blob(const char *filename);
int save_blob(const char *filename, const char *blob, size_t length);

#endif /* __BLOB_H */

