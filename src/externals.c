/*
 * externals.c
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#include <stdlib.h>

#include "html_scraper.h"
#include "query.h"
#include "ucrcourse.h"

char *get_raw_ucr_courses_html(const struct course_query *query)
{
	/* TODO */
	return NULL;
}

struct course_result *get_ucr_courses(const struct course_query *query)
{
	struct course_result *results;
	char *html;

	html = get_raw_ucr_courses_html(query);
	if (!html) {
		return NULL;
	}

	results = parse_html(html);
	free(html);
	if (!results) {
		return NULL;
	}
	return results;
}

void destroy_course_result(struct course_result *results)
{
	if (!results) {
		return;
	}

	if (results->next) {
		destroy_course_result(results->next);
	}

	free((void *)results->course_number);
	free((void *)results->course_title);
	free((void *)results->instructor);
	free((void *)results->pre_requisites);
	free((void *)results->co_requisites);
	free((void *)results->pre_requisites);
	free((void *)results->schedule_notes);
	free((void *)results->schedule_notes);
	free((void *)results->grade_type);
	free((void *)results->catalog_description);

	free(results);
}

