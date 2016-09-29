/*
 * blob.c
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#include <stdlib.h>
#include <stdio.h>

#include "blob.h"

char *get_blob(const char *filename)
{
	FILE *fh;
	long fsize;
	char *blob;
	int ret;

	fh = fopen(filename, "r");
	if (!fh) {
		return NULL;
	}

	ret = fseek(fh, 0, SEEK_END);
	if (ret) {
		return NULL;
	}

	fsize = ftell(fh);
	if (fsize < 0) {
		return NULL;
	}

	blob = malloc(fsize + 1);
	if (!blob) {
		return NULL;
	}

	rewind(fh);
	if (!fread(blob, fsize, 1, fh)) {
		free(blob);
		return NULL;
	}

	fclose(fh);
	blob[fsize] = '\0';
	return blob;
}

int set_blob(const char *filename, const char *blob, size_t length)
{
	FILE *fh;
	int ret;

	fh = fopen(filename, "w");
	if (!fh) {
		return -1;
	}

	ret = fwrite(blob, length, 1, fh);
	if (!ret) {
		fclose(fh);
		return -1;
	}

	fclose(fh);
	return 0;
}

