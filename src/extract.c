/*
 * extract.c
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "extract.h"
#include "slice.h"
#include "ucrcourse.h"

#define ERROR_TRIGGER			"error"
#define ERROR_LENGTH			5

#define LISTINGS_TRIGGER		"UpdatePanel1|"
#define LISTINGS_LENGTH			13

#define DETAILS_TRIGGER			"UpdatePanel3|"
#define DETAILS_LENGTH			13

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
			if (!strncmp(response + i, ERROR_TRIGGER, ERROR_LENGTH)) {
				errno = UCRCOURSE_ERR_SERVER;
				return;
			} else if (!strncmp(response + i, LISTINGS_TRIGGER, LISTINGS_LENGTH)) {
				listings.start = i + LISTINGS_LENGTH;
			} else if (!strncmp(response + i, DETAILS_TRIGGER, DETAILS_LENGTH)) {
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

	*listing_html = copy_slice(response, &listings);
	*detail_html = copy_slice(response, &details);
}

