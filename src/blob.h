/*
 * blob.h
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#ifndef __BLOB_H
#define __BLOB_H

char *get_blob(const char *filename);
int set_blob(const char *filename, const char *blob, size_t length);

#endif /* __BLOB_H */

