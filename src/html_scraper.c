/*
 * html_scraper.c
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "html_scraper.h"
#include "ucrcourse.h"

#define ERROR_NAME			"error"
#define ERROR_LENGTH			5

#define LISTINGS_NAME			"UpdatePanel1|"
#define LISTINGS_LENGTH			13

#define DETAILS_NAME			"UpdatePanel3|"
#define DETAILS_LENGTH			13

struct slice {
	size_t start;
	size_t length;
};

static char *copy_slice(const char *str, struct slice slice)
{
	char *buf = malloc(slice.length + 1);
	if (!buf) {
		return NULL;
	}

	memcpy(buf, str + slice.start, slice.length);
	buf[slice.length] = '\0';
	return buf;
}

void extract_html(const char *response, char **listing_html, char **detail_html)
{
	struct slice listings, details;
	size_t i;

	listings.start = 0;
	listings.length = 0;

	details.start = 0;
	details.length = 0;

	*listing_html = NULL;
	*detail_html = NULL;

	for (i = 1; response[i]; i++) {
		if (response[i - 1] == '|') {
			if (!strncmp(response + i, ERROR_NAME, ERROR_LENGTH)) {
				errno = UCRCOURSE_ERR_SERVER;
				return;
			} else if (!strncmp(response + i, LISTINGS_NAME, LISTINGS_LENGTH)) {
				listings.start = i + LISTINGS_LENGTH;
			} else if (!strncmp(response + i, DETAILS_NAME, DETAILS_LENGTH)) {
				details.start = i + DETAILS_LENGTH;
			} else if (listings.start && !listings.length) {
				listings.length = i - listings.start;
			} else if (details.start && !details.length) {
				details.length = i - details.start;
			}
		}
	}

	if (listings.length == 0 || details.length == 0) {
		errno = UCRCOURSE_ERR_RESPONSE;
		return;
	}

	*listing_html = copy_slice(response, listings);
	*detail_html = copy_slice(response, details);
}

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

