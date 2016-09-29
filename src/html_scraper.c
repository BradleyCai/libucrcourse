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

#define ERROR_KEY_NAME			"error"
#define ERROR_KEY_LENGTH		5

#define HTML_KEY_NAME			"UpdatePanel3"
#define HTML_KEY_LENGTH			12

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

	memcpy(buf, str + slice.start + 1, slice.length - 1);
	buf[slice.length] = '\0';
	return buf;
}

char *extract_html(const char *response)
{
	struct slice html;
	size_t i;

	html.start = 0;
	html.length = 0;

	for (i = 0; response[i]; i++) {
		if (response[i] == '|') {
			if (html.start == 0) {
				i++;
				if (!strncmp(response + i, ERROR_KEY_NAME, ERROR_KEY_LENGTH)) {
					errno = UCRCOURSE_ERR_SERVER;
					return NULL;
				} else if (!strncmp(response + i, HTML_KEY_NAME, HTML_KEY_LENGTH)) {
					i += HTML_KEY_LENGTH;
					html.start = i;
				}
			} else {
				html.length = i - html.start;
				break;
			}
		}
	}

	if (html.length == 0) {
		errno = UCRCOURSE_ERR_RESPONSE;
		return NULL;
	}

	return copy_slice(response, html);
}

struct course_results *scrape_html(const char *html)
{
	struct course_results *results = malloc(sizeof(struct course_results));
	if (!results) {
		return NULL;
	}

	/* TODO */
	results->courses = NULL;
	results->length = 0;

	return results;
}

