/*
 * externals.c
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#include <stdlib.h>

#include "html_scraper.h"
#include "params.h"
#include "request.h"
#include "ucrcourse.h"

void course_query_init(struct course_query *query)
{
	set_default_term(query);
	query->subject_area = SUBJECT_NONE;
	query->course_title = "";
	query->instructor = "";
	query->course_number = "";
	query->start_hour = HOUR_NONE;
	query->course_status = STATUS_OPEN;
	query->course_range = RANGE_NONE;
	query->class_type = CLASS_NONE;
	query->course_location = BUILDING_NONE;
	query->breadth = BREADTH_NONE;
	query->graduate_quantitative = false;
	query->days[MONDAY] = false;
	query->days[TUESDAY] = false;
	query->days[WEDNESDAY] = false;
	query->days[THURSDAY] = false;
	query->days[FRIDAY] = false;
	query->days[SATURDAY] = false;
}

char *get_raw_ucr_courses_request(const struct course_query *query)
{
	char *params = query_to_string(query);
	return params ? do_request(params) : NULL;
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

