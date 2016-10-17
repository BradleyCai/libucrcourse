/*
 * scrape.c
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "scrape.h"
#include "slice.h"
#include "string_buffer.h"
#include "ucrcourse.h"

#define DEFAULT_RESULT_CAPACITY			5

static struct course_results *init_course_results(
	size_t *capacity)
{
	struct course_results *results;

	results = malloc(sizeof(struct course_results));
	if (!results) {
		return NULL;
	}

	results->length = 0;
	*capacity = DEFAULT_RESULT_CAPACITY;
	results->courses = malloc(sizeof(struct course) * DEFAULT_RESULT_CAPACITY);
	if (!results->courses) {
		int errsave = errno;
		free(results);
		errno = errsave;
		return NULL;
	}

	return results;
}

static void destroy_course_results(struct course_results *results)
{
	free((void *)results->courses);
	free(results);
}

static int resize_course_results(struct course_results *results, size_t *capacity)
{
	struct course *new_array;
	size_t new_capacity;

	new_capacity = (*capacity) * 2;
	new_array = realloc((void *)results->courses, sizeof(struct course) * new_capacity);
	if (!new_array) {
		return -1;
	}

	results->courses = new_array;
	*capacity = new_capacity;
	return 0;
}

static char *find_next(
	const char *html, size_t *i, const char *trigger, size_t len,
	char start, char end)
{
	struct slice slice;

	for (; html[*i]; (*i)++) {
		if (!strncmp(html + *i, trigger, len)) {
			break;
		}
	}

	slice.start = 0;
	slice.length = 0;

	for (; html[*i]; (*i)++) {
		if (html[*i] == start) {
			slice.start = *i + len;
		} else if (html[*i] == end) {
			slice.length = *i - slice.start;
		}
	}

	if (slice.start && slice.length) {
		return copy_slice(html, &slice);
	}

	return NULL;
}

#define COURSE_NAME_TRIGGER			"_lnkbtn_courseTitle"
#define COURSE_NAME_LENGTH			18
#define COURSE_NAME_START			'>'
#define COURSE_NAME_END				'<'

/* FIXME */
#define SIGNUP_REQUIREMENT_TRIGGER		"**"
#define SIGNUP_REQUIREMENT_LENGTH		2

#define INSTRUCTOR_TRIGGER			"<b>Instructor:"
#define INSTRUCTOR_LENGTH			13
#define INSTRUCTOR_START			'>'
#define INSTURCTOR_END				'<'

#define UNITS_TRIGGER				"<b>Units:"
#define UNITS_LENGTH				8
#define UNITS_START				'>'
#define UNITS_ENDS				'<'

#define MAX_ENROLL_TRIGGER			"<b>Max Enroll</b>"
#define MAX_ENROLL_LENGTH			16
#define MAX_ENROLL_START			':'
#define MAX_ENROLL_END				'<'

#define PREREQUISITES_TRIGGER			"<b>Prerequisities:"
#define PREREQUISITES_LENGTH			17
#define PREREQUISITES_START			'>'
#define PREREQUISITES_END			'<'

#define FINAL_EXAM_TRIGGER			"<b>Final Exam:"
#define FINAL_EXAM_LENGTH			13
#define FINAL_EXAM_START			'>'
#define FINAL_EXAM_END				'\n'

#define COURSE_TYPE_TRIGGER			"<td"
#define COURSE_TYPE_LENGTH			3
#define COURSE_TYPE_START			'>'
#define COURSE_TYPE_END				'<'

#define DAYS_TRIGGER				"<td"
#define DAYS_LENGTH				3
#define DAYS_START				'>'
#define DAYS_END				'<'

#define TIMES_TRIGGER				"<td"
#define TIMES_LENGTH				3
#define TIMES_START				'<'
#define TIMES_END				'>'

#define AVAILABLE_SEATS_TRIGGER			"_lbl_seeDetails"
#define AVAILABLE_SEATS_LENGTH			14
#define AVAILABLE_SEATS_START			'>'
#define AVAILABLE_SEATS_END			'<'

#define COURSE_STATUS_TRIGGER			"<font size=1"
#define COURSE_STATUS_LENGTH			11
#define COURSE_STATUS_START			'>'
#define COURSE_STATUS_END			'<'

#define COURSE_TITLE_TRIGGER			"<td"
#define COURSE_TITLE_LENGTH			3
#define COURSE_TITLE_START			'>'
#define COURSE_TITLE_END			'<'

#define SECTION_NUMBER_TRIGGER			"<td"
#define SECTION_NUMBER_LENGTH			3
#define SECTION_NUMBER_START			'>'
#define SECTION_NUMBER_END			'<'

#define CALL_NUMBER_TRIGGER			"<td"
#define CALL_NUMBER_LENGTH			3
#define CALL_NUMBER_START			'>'
#define CALL_NUMBER_END				'<'

static int read_course(struct course *course, const char *html, size_t *i)
{
	;
}

struct course_results *scrape_html(const char *html)
{
	struct course_results *results;
	size_t capacity;
	size_t i;
	int ret;

	results = init_course_results(&capacity);
	if (!results) {
		return NULL;
	}

	i = 0;
	while (html[i]) {
		struct course *course;

		if (results->length + 1 >= capacity) {
			resize_course_results(results, &capacity);
		}

		course = (struct course *)(&results->courses[results->length]);
		ret = read_course(course, html, &i);
		if (ret) {
			destroy_course_results(results);
			return NULL;
		}
	}

	/* TEMP */
	results->courses = NULL;
	results->length = 0;

	return results;
}

