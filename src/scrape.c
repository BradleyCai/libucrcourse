/*
 * scraper.c
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#include <stdlib.h>

#include "scraper.h"
#include "ucrcourse.h"

struct course_results *scrape_html(const char *html)
{
	struct course_results *results;
	size_t i;

	results = malloc(sizeof(struct course_results));
	if (!results) {
		return NULL;
	}

	for (i = 0; html[i]; i++) {
	}

	results->courses = NULL;
	results->length = 0;

	return results;
}

