/*
 * params.c
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "blob.h"
#include "constants.h"
#include "params.h"
#include "string_buffer.h"

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

	if (hour == HOUR_NONE) {
		buf[0] = '\0';
		return;
	}

	if (hour > 12) {
		meridian = 'p';
	} else {
		meridian = 'a';
	}

	sprintf(buf, "%02u%c.m", hour % 12, meridian);
}

void set_default_term(struct course_query *query)
{
	time_t now = time(NULL);
	struct tm *tm = localtime(&now);

	query->year = tm->tm_year;
	switch (tm->tm_mon) {
	case 6:
	case 7:
	case 8:
		/* Summer - June to August */
		query->quarter = SUMMER_QUARTER;
		break;
	case 9:
	case 10:
	case 11:
		/* Fall - September to November */
		query->quarter = FALL_QUARTER;
		break;
	case 12:
	case 1:
	case 2:
		/* Winter - December to February */
		query->quarter = WINTER_QUARTER;
		break;
	case 3:
	case 4:
	case 5:
		/* Spring - March to May */
		query->quarter = SPRING_QUARTER;
	}
}

static void add_param(struct string_buffer *string, const char *key, const char *value)
{
	if (string->length > 0) {
		strbuf_append_char(string, '&');
	}

	strbuf_append(string, key);
	strbuf_append_char(string, '=');
	strbuf_append(string, value);
}

char *query_to_string(const struct course_query *query)
{
	struct string_buffer strbuf;
	char *blob;
	char buf[6];

	if (strbuf_init(&strbuf, 1024)) {
		return NULL;
	}

	/*
	blob = get_blob("blob/viewstate.dat");
	if (!blob) return NULL;
	add_param(&strbuf, "__VIEWSTATE", blob);
	free(blob);

	blob = get_blob("blob/eventvalidation.dat");
	if (!blob) return NULL;
	add_param(&strbuf, "__EVENTVALIDATION", blob);
	free(blob);
	*/

	add_param(&strbuf, "__EVENTTARGET", "");
	add_param(&strbuf, "__EVENTARGUMENT", "");
	add_param(&strbuf, "__LASTFOCUS", "");
	add_param(&strbuf, "__SCROLLPOSITIONX", "0");
	add_param(&strbuf, "__SCROLLPOSITIONY", "0");
	add_param(&strbuf, "__ASYNCPOST", "true");
	add_param(&strbuf, "btn_search", " Search >>");

	set_term_code(buf, query->quarter, query->year);
	add_param(&strbuf, "drp_term", buf);
	add_param(&strbuf, "drp_subjectArea", SUBJECT_AREAS[query->subject_area]);
	add_param(&strbuf, "txtbx_courseTitle", query->course_title);
	add_param(&strbuf, "txt_instructor", query->instructor);
	add_param(&strbuf, "txtbx_courseNumber", query->course_number);
	set_start_time(buf, query->start_hour);
	add_param(&strbuf, "drp_startTime", buf);
	set_course_status(buf, query->course_status);
	add_param(&strbuf, "drp_fullOpenClasses", buf);
	add_param(&strbuf, "drp_courseRange", COURSE_RANGES[query->course_range]);
	add_param(&strbuf, "drp_location", COURSE_LOCATIONS[query->course_location]);
	add_param(&strbuf, "drp_breadth", BREADTH_COURSES[query->breadth]);

	if (query->graduate_quantitative) add_param(&strbuf, "cbGraduateQuant", "on");
	if (query->days[MONDAY]) add_param(&strbuf, "chkbx_mon", "on");
	if (query->days[TUESDAY]) add_param(&strbuf, "chkbx_tue", "on");
	if (query->days[WEDNESDAY]) add_param(&strbuf, "chkbx_wed", "on");
	if (query->days[THURSDAY]) add_param(&strbuf, "chkbx_thur", "on");
	if (query->days[FRIDAY]) add_param(&strbuf, "chkbx_fri", "on");
	if (query->days[SATURDAY]) add_param(&strbuf, "chkbx_sat", "on");

	strbuf_append_char(&strbuf, '\0');
	return strbuf.data;
}

