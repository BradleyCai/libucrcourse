/*
 * scrape.c
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parse.h"
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
		if (slice.start && html[*i] == end) {
			slice.length = *i - slice.start - 1;
		} else if (html[*i] == start) {
			slice.start = *i + len + 1;
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
#define INSTRUCTOR_END				'<'

#define UNITS_TRIGGER				"<b>Units:"
#define UNITS_LENGTH				8
#define UNITS_START				'>'
#define UNITS_END				'<'

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

#define CLASS_TYPE_TRIGGER			"<td"
#define CLASS_TYPE_LENGTH			3
#define CLASS_TYPE_START			'>'
#define CLASS_TYPE_END				'<'

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

#define COURSE_ID_TRIGGER			"<td"
#define COURSE_ID_LENGTH			3
#define COURSE_ID_START				'>'
#define COURSE_ID_END				'<'

#define SECTION_NUMBER_TRIGGER			"<td"
#define SECTION_NUMBER_LENGTH			3
#define SECTION_NUMBER_START			'>'
#define SECTION_NUMBER_END			'<'

#define CALL_NUMBER_TRIGGER			"<td"
#define CALL_NUMBER_LENGTH			3
#define CALL_NUMBER_START			'>'
#define CALL_NUMBER_END				'<'

static int read_course_data(struct course_strings *data, const char *html, size_t *i)
{
	data->course_name = find_next(
			html, i, COURSE_NAME_TRIGGER, COURSE_NAME_LENGTH,
			COURSE_NAME_START, COURSE_NAME_END);
	if (!data->course_name) {
		return -1;
	}

	/* TODO add signup requirement */

	data->instructor = find_next(
			html, i, INSTRUCTOR_TRIGGER, INSTRUCTOR_LENGTH,
			INSTRUCTOR_START, INSTRUCTOR_END);
	if (!data->instructor) {
		free(data->course_name);
		/* free(data->signup_requirement); */
		return -1;
	}

	data->units = find_next(
			html, i, UNITS_TRIGGER, UNITS_LENGTH,
			UNITS_START, UNITS_END);
	if (!data->units) {
		free(data->course_name);
		/* free(data->signup_requirement); */
		free(data->instructor);
		return -1;
	}

	data->max_enroll = find_next(
			html, i, MAX_ENROLL_TRIGGER, MAX_ENROLL_LENGTH,
			MAX_ENROLL_START, MAX_ENROLL_END);
	if (!data->max_enroll) {
		free(data->course_name);
		/* free(data->signup_requirement); */
		free(data->instructor);
		free(data->units);
		return -1;
	}

	data->pre_requisites = find_next(
			html, i, PREREQUISITES_TRIGGER, PREREQUISITES_LENGTH,
			PREREQUISITES_START, PREREQUISITES_END);
	if (!data->pre_requisites) {
		free(data->course_name);
		/* free(data->signup_requirement); */
		free(data->instructor);
		free(data->units);
		free(data->max_enroll);
		return -1;
	}

	data->final_exam = find_next(
			html, i, FINAL_EXAM_TRIGGER, FINAL_EXAM_LENGTH,
			FINAL_EXAM_START, FINAL_EXAM_END);
	if (!data->final_exam) {
		free(data->course_name);
		/* free(data->signup_requirement); */
		free(data->instructor);
		free(data->units);
		free(data->max_enroll);
		free(data->pre_requisites);
		return -1;
	}

	data->class_type = find_next(
			html, i, CLASS_TYPE_TRIGGER, CLASS_TYPE_LENGTH,
			CLASS_TYPE_START, CLASS_TYPE_END);
	if (!data->class_type) {
		free(data->course_name);
		/* free(data->signup_requirement); */
		free(data->instructor);
		free(data->units);
		free(data->max_enroll);
		free(data->pre_requisites);
		free(data->final_exam);
		return -1;
	}

	data->days = find_next(
			html, i, DAYS_TRIGGER, DAYS_LENGTH,
			DAYS_START, DAYS_END);
	if (!data->days) {
		free(data->course_name);
		/* free(data->signup_requirement); */
		free(data->instructor);
		free(data->units);
		free(data->max_enroll);
		free(data->pre_requisites);
		free(data->final_exam);
		free(data->class_type);
		return -1;
	}

	data->times = find_next(
			html, i, TIMES_TRIGGER, TIMES_LENGTH,
			TIMES_START, TIMES_END);
	if (!data->times) {
		free(data->course_name);
		/* free(data->signup_requirement); */
		free(data->instructor);
		free(data->units);
		free(data->max_enroll);
		free(data->pre_requisites);
		free(data->final_exam);
		free(data->class_type);
		free(data->days);
		return -1;
	}

	data->available_seats = find_next(
			html, i, AVAILABLE_SEATS_TRIGGER, AVAILABLE_SEATS_LENGTH,
			AVAILABLE_SEATS_START, AVAILABLE_SEATS_END);
	if (!data->available_seats) {
		free(data->course_name);
		/* free(data->signup_requirement); */
		free(data->instructor);
		free(data->units);
		free(data->max_enroll);
		free(data->pre_requisites);
		free(data->final_exam);
		free(data->class_type);
		free(data->days);
		free(data->times);
		return -1;
	}

	data->course_status = find_next(
			html, i, COURSE_STATUS_TRIGGER, COURSE_STATUS_LENGTH,
			COURSE_STATUS_START, COURSE_STATUS_END);
	if (!data->course_status) {
		free(data->course_name);
		/* free(data->signup_requirement); */
		free(data->instructor);
		free(data->units);
		free(data->max_enroll);
		free(data->pre_requisites);
		free(data->final_exam);
		free(data->class_type);
		free(data->days);
		free(data->available_seats);
		return -1;
	}

	data->course_id = find_next(
			html, i, COURSE_ID_TRIGGER, COURSE_ID_LENGTH,
			COURSE_ID_START, COURSE_ID_END);
	if (!data->course_id) {
		free(data->course_name);
		/* free(data->signup_requirement); */
		free(data->instructor);
		free(data->units);
		free(data->max_enroll);
		free(data->pre_requisites);
		free(data->final_exam);
		free(data->class_type);
		free(data->days);
		free(data->available_seats);
		free(data->course_status);
		return -1;
	}

	data->section_number = find_next(
			html, i, SECTION_NUMBER_TRIGGER, SECTION_NUMBER_LENGTH,
			SECTION_NUMBER_START, SECTION_NUMBER_END);
	if (!data->section_number) {
		free(data->course_name);
		/* free(data->signup_requirement); */
		free(data->instructor);
		free(data->units);
		free(data->max_enroll);
		free(data->pre_requisites);
		free(data->final_exam);
		free(data->class_type);
		free(data->days);
		free(data->available_seats);
		free(data->course_status);
		free(data->course_id);
		return -1;
	}

	data->call_number = find_next(
			html, i, CALL_NUMBER_TRIGGER, CALL_NUMBER_LENGTH,
			CALL_NUMBER_START, CALL_NUMBER_END);
	if (!data->call_number) {
		free(data->course_name);
		/* free(data->signup_requirement); */
		free(data->instructor);
		free(data->units);
		free(data->max_enroll);
		free(data->pre_requisites);
		free(data->final_exam);
		free(data->class_type);
		free(data->days);
		free(data->available_seats);
		free(data->course_status);
		free(data->course_id);
		free(data->section_number);
		return -1;
	}

	return 0;
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
		struct course_strings course_data;
		struct course *course;

		if (results->length + 1 >= capacity) {
			resize_course_results(results, &capacity);
		}

		ret = read_course_data(&course_data, html, &i);
		if (ret) {
			destroy_course_results(results);
			return NULL;
		}

		course = (struct course *)(&results->courses[results->length]);
		ret = create_course(course, &course_data);
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

