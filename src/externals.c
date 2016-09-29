/*
 * externals.c
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>

#include "html_scraper.h"
#include "params.h"
#include "request.h"
#include "ucrcourse.h"

#define DEFAULT_INSTRUCTOR			"Instructor"
#define DEFAULT_COURSE_NUMBER			"Course%23"
#define DEFAULT_COURSE_TITLE			"Course%20Title"

int ucrcourse_init(void)
{
	CURLcode res = curl_global_init(CURL_GLOBAL_DEFAULT);
	if (res != CURLE_OK) {
		errno = UCRCOURSE_ERR_CURL;
		return -1;
	}

	return 0;
}

void ucrcourse_cleanup(void)
{
	curl_global_cleanup();
}

const char *ucrcourse_strerror(int error)
{
	switch (error) {
	case UCRCOURSE_ERR_INTERNAL:
		return "Internal library error";
	case UCRCOURSE_ERR_CURL:
		return "cURL returned an error";
	case UCRCOURSE_ERR_INVALID_ARG:
		return "Invalid argument(s)";
	case UCRCOURSE_ERR_CONNECT:
		return "Unable to connect to remote";
	case UCRCOURSE_ERR_SERVER:
		return "Remote server encountered an error";
	case UCRCOURSE_ERR_RESPONSE:
		return "Server response is malformed";
	default:
		return strerror(error);
	}
}

void ucrcourse_query_init(struct course_query *query)
{
	set_default_term(query);
	query->subject_area = SUBJECT_NONE;
	query->course_title = DEFAULT_COURSE_TITLE;
	query->instructor = DEFAULT_INSTRUCTOR;
	query->course_number = DEFAULT_COURSE_NUMBER;
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

char *ucrcourse_get_raw(const struct course_query *query)
{
	char *params = query_to_string(query);
	char *result = params ? do_request(params) : NULL;
	free(params);
	return result;
}

char *ucrcourse_get_html(const struct course_query *query)
{
	char *response, *html;

	response = ucrcourse_get_raw(query);
	if (!response) {
		return NULL;
	}

	html = extract_html(response);
	free(response);
	return html;
}

struct course_results *ucrcourse_get_courses(const struct course_query *query)
{
	struct course_results *results;
	char *html;

	html = ucrcourse_get_html(query);
	if (!html) {
		return NULL;
	}

	results = scrape_html(html);
	free(html);
	return results;
}

void ucrcourse_results_destroy(struct course_results *results)
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

