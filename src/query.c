/*
 * query.c
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "constants.h"
#include "query.h"

static void set_term_code(char *buf, enum quarter quarter, unsigned short year)
{
	char quarter_letter;

	switch (quarter) {
	case FALL_QUARTER:
		quarter_letter = 'F';
		break;
	case WINTER_QUARTER:
		quarter_letter = 'W';
		break;
	case SPRING_QUARTER:
		quarter_letter = 'S';
		break;
	case SUMMER_QUARTER:
		quarter_letter = 'U';
		break;
	default:
		assert(0);
	}

	sprintf(buf, "%02u%c", year % 100u, quarter_letter);
}

static void set_course_status(char *buf, unsigned int value)
{
	buf[0] = '0' + value;
	buf[1] = '\0';
}

static void set_start_time(char *buf, unsigned int hour)
{
	char meridian;

	if (hour > 12) {
		meridian = 'p';
	} else {
		meridian = 'a';
	}

	sprintf(buf, "%02u%c.m", hour % 12, meridian);
}

int query_to_params(struct query_params *params, const struct course_query *query)
{
	set_term_code((char *)params->drp_term, query->quarter, query->year);
	params->drp_subjectArea = SUBJECT_AREAS[query->subject_area];
	params->txtbx_courseTitle = query->course_title;
	params->txt_instructor = query->instructor;
	params->txtbx_courseNumber = query->course_number;
	set_start_time((char *)params->drp_startTime, query->start_hour);
	set_course_status((char *)params->drp_fullOpenClasses, query->course_status);
	params->drp_courseRange = COURSE_RANGES[query->course_range];
	params->drp_location = COURSE_LOCATIONS[query->course_location];
	params->drp_breadth = BREADTH_COURSES[query->breadth];
	params->cbGraduateQuant = query->graduate_quantitative;

	return 0;
}

char *params_to_string(const struct query_params *params)
{
	/* TODO string buffer */
	return NULL;
}

