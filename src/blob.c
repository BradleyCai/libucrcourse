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

	fh = fopen(filename, "r");
	if (!fh) {
		return NULL;
	}

	if (fseek(fh, 0, SEEK_END)) {
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

