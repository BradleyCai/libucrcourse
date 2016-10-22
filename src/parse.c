/*
 * parse.c
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "long_parse.h"
#include "parse.h"
#include "ucrcourse.h"

static int parse_int(int *dest, const char *str)
{
	char *ptr;
	errno = 0;
	*dest = strtol(str, &ptr, 10);
	if (errno || !*ptr) {
		return -1;
	}

	return 0;
}

static int parse_final_exam(struct course *course, const char *str)
{
	char start_merid, end_merid;
	int ret = sscanf(
			str,
			" %2hhu/%2hhu/%4hu %2hhu:%2hhu%1c.M. - %2hhu:%2hhu:%2hhu%1c.M. ",
			&course->final_exam_date.month,
			&course->final_exam_date.day,
			&course->final_exam_date.year,
			&course->final_exam_date.start_hour,
			&course->final_exam_date.start_minute,
			&start_merid,
			&course->final_exam_date.end_hour,
			&course->final_exam_date.end_minute,
			&end_merid);

	if (ret == EOF) {
		return -1;
	}

	if (start_merid == 'P' || start_merid == 'p') {
		course->final_exam_date.start_hour += 12;
	}
	if (end_merid == 'P' || end_merid == 'p') {
		course->final_exam_date.end_hour += 12;
	}

	return 0;
}

static int parse_days(bool *days, const char *str)
{
	size_t i;

	days[MONDAY] = false;
	days[TUESDAY] = false;
	days[WEDNESDAY] = false;
	days[THURSDAY] = false;
	days[FRIDAY] = false;
	days[SATURDAY] = false;

	for (i = 0; str[i]; i++) {
		switch (str[i]) {
		case 'M':
			days[MONDAY] = true;
			break;
		case 'T':
			days[TUESDAY] = true;
			break;
		case 'W':
			days[WEDNESDAY] = true;
			break;
		case 'R':
			days[THURSDAY] = true;
			break;
		case 'F':
			days[FRIDAY] = true;
			break;
		case 'S':
			days[SATURDAY] = true;
			break;
		default:
			if (!isspace(str[i])) {
				return -1;
			}
		}
	}

	return 0;
}

static int parse_course_id(
	enum subject_area *subject_area, const char **course_number, const char *str)
{
	char *sa_buf, *cn_buf;
	size_t i, j, len;
	int ret;

	sa_buf = malloc(len);
	if (!sa_buf) {
		return -1;
	}

	for (i = 0; isspace(str[i]); i++);
	if (!str[i]) {
		free(sa_buf);
		return -1;
	}

	/* Copy subject area */
	for (j = 0; str[i]; i++) {
		if (!isalnum(str[i])) {
			break;
		}

		sa_buf[j++] = str[i];
	}
	if (!str[i]) {
		free(sa_buf);
		return -1;
	}

	for (; isspace(str[i]); i++);
	if (!str[i]) {
		free(sa_buf);
		return -1;
	}

	cn_buf = malloc(len - 1);
	if (!cn_buf) {
		free(sa_buf);
		return -1;
	}

	/* Copy course number */
	for (j = 0; str[i]; i++) {
		if (!isalnum(str[i])) {
			break;
		}

		cn_buf[j++] = str[i];
	}

	*subject_area = parse_subject_area(sa_buf);
	*course_number = cn_buf;
	free(sa_buf);
	return 0;
}

int parse_times(struct course *course, const char *str)
{
	char start_merid, end_merid;
	int ret = sscanf(str,
			" %2hhu:%2hhu %1c.m. - %2hhu:%2hhu %1c.m. ",
			&course->times.start_hour,
			&course->times.start_minute,
			&start_merid,
			&course->times.end_hour,
			&course->times.end_minute,
			&end_merid);
	if (ret) {
		return -1;
	}

	if (start_merid == 'p' || start_merid == 'P') {
		course->times.start_hour += 12;
	}
	if (end_merid == 'p' || end_merid == 'P') {
		course->times.end_hour += 12;
	}

	return 0;
}

int create_course(struct course *course, const struct course_strings *data)
{
	int val, ret;

	course->course_name = data->course_name;
	course->co_requisites = data->co_requisites;
	course->instructor = data->instructor;
	course->pre_requisites = data->pre_requisites;
	course->course_id = data->course_id;

	ret = parse_int(&val, data->units);
	if (ret) return -1;
	course->units = val;

	ret = parse_int(&val, data->max_enroll);
	if (ret) return -1;
	course->max_enrollment = val;

	ret = parse_final_exam(course, data->final_exam);
	if (ret) return -1;

	ret = parse_course_id(&course->subject_area, &course->course_number, data->course_id);
	if (ret) return -1;

	course->class_type = parse_class_type(data->class_type);

	ret = parse_days(course->days, data->days);
	if (ret) return -1;

	ret = parse_times(course, data->times);
	if (ret) return -1;

	ret = parse_int(&val, data->available_seats);
	if (ret) return -1;
	course->available_seats = val;

	ret = parse_course_status(&course->status, data->course_status);
	if (ret) return -1;

	ret = parse_int(&val, data->section_number);
	if (ret) return -1;
	course->section = val;

	ret = parse_int(&val, data->call_number);
	if (ret) return -1;
	course->call_number = val;

	return 0;
}

