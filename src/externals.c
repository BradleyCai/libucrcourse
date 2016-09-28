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
#include "request.h"

char *get_raw_ucr_courses_request(const struct course_query *query)
{
	struct query_params params;
	char *param_str;
	if (query_to_params(&params, query)) {
		return NULL;
	}

	param_str = params_to_string(&params);
	if (!param_str) {
		return NULL;
	}

	return do_request(param_str);
}

char *get_raw_ucr_courses_html(const struct course_query *query)
{
	char *response, *html;

	response = get_raw_ucr_courses_request(query);
	if (!response) {
		return NULL;
	}

	html = extract_html(response);
	free(response);
	return html;
}

struct course_results *get_ucr_courses(const struct course_query *query)
{
	struct course_results *results;
	char *html;

	html = get_raw_ucr_courses_html(query);
	if (!html) {
		return NULL;
	}

	results = scrape_html(html);
	free(html);
	return results;
}

void destroy_course_result(struct course_results *results)
{
	size_t i;

	if (!results) {
		return;
	}

	for (i = 0; i < results->length; i++) {
		free((void *)results->courses[i].course_number);
		free((void *)results->courses[i].course_title);
		free((void *)results->courses[i].instructor);
		free((void *)results->courses[i].pre_requisites);
		free((void *)results->courses[i].co_requisites);
		free((void *)results->courses[i].pre_requisites);
		free((void *)results->courses[i].schedule_notes);
		free((void *)results->courses[i].schedule_notes);
		free((void *)results->courses[i].grade_type);
		free((void *)results->courses[i].catalog_description);
	}

	free(results);
}

