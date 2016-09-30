/*
 * params.c
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#include <assert.h>
#include <errno.h>
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

static int add_param(struct string_buffer *string, CURL *curlh, const char *key, const char *value)
{
	char *escaped;

	if (string->length > 0) {
		strbuf_append_char(string, '&');
	}

	escaped = curl_easy_escape(curlh, key, 0);
	if (strbuf_append(string, escaped)) {
		int errsave = errno;
		curl_free(escaped);
		errno = errsave;
		return -1;
	}
	curl_free(escaped);

	if (strbuf_append_char(string, '=')) {
		return -1;
	}

	escaped = curl_easy_escape(curlh, value, 0);
	if (strbuf_append(string, escaped)) {
		int errsave = errno;
		curl_free(escaped);
		errno = errsave;
		return -1;
	}
	curl_free(escaped);

	return 0;

}

#define ADD_PARAM(strbuf, curlh, key, val)					\
	do {									\
		int ret = add_param((strbuf), (curlh), (key), (val));		\
		if (ret) {							\
			int errsave = errno;					\
			strbuf_destroy(strbuf);					\
			errno = errsave;					\
			return NULL;						\
		}								\
	} while(0)

char *query_to_string(CURL *curlh, const struct course_query *query)
{
	struct string_buffer strbuf;
	char *blob;
	char buf[6];

	if (strbuf_init(&strbuf, 1024)) {
		return NULL;
	}

	ADD_PARAM(&strbuf, curlh, "ScriptManager1", "UpdatePanel1|btn_search");
	ADD_PARAM(&strbuf, curlh, "__ASYNCPOST", "true");
	ADD_PARAM(&strbuf, curlh, "__EVENTTARGET", "");
	ADD_PARAM(&strbuf, curlh, "__EVENTARGUMENT", "");

	blob = get_blob("blob/eventvalidation.dat");
	if (!blob) return NULL;
	if (add_param(&strbuf, curlh, "__EVENTVALIDATION", blob)) {
		int errsave = errno;
		strbuf_destroy(&strbuf);
		free(blob);
		errno = errsave;
		return NULL;
	}
	free(blob);

	ADD_PARAM(&strbuf, curlh, "__LASTFOCUS", "");
	ADD_PARAM(&strbuf, curlh, "__SCROLLPOSITIONX", "0");
	ADD_PARAM(&strbuf, curlh, "__SCROLLPOSITIONY", "0");

	blob = get_blob("blob/viewstate.dat");
	if (!blob) return NULL;
	if (add_param(&strbuf, curlh, "__VIEWSTATE", blob)) {
		int errsave = errno;
		strbuf_destroy(&strbuf);
		free(blob);
		errno = errsave;
		return NULL;
	}
	free(blob);

	ADD_PARAM(&strbuf, curlh, "btn_search", "\xc2\xa0Search >>\n");

	set_term_code(buf, query->quarter, query->year);
	ADD_PARAM(&strbuf, curlh, "drp_term", buf);
	ADD_PARAM(&strbuf, curlh, "drp_subjectArea", SUBJECT_AREAS[query->subject_area]);
	ADD_PARAM(&strbuf, curlh, "txtbx_courseTitle", query->course_title);
	ADD_PARAM(&strbuf, curlh, "txt_instructor", query->instructor);
	ADD_PARAM(&strbuf, curlh, "txtbx_courseNumber", query->course_number);
	set_start_time(buf, query->start_hour);
	ADD_PARAM(&strbuf, curlh, "drp_startTime", buf);
	set_course_status(buf, query->course_status);
	ADD_PARAM(&strbuf, curlh, "drp_fullOpenClasses", buf);
	ADD_PARAM(&strbuf, curlh, "drp_courseRange", COURSE_RANGES[query->course_range]);
	ADD_PARAM(&strbuf, curlh, "drp_location", COURSE_LOCATIONS[query->course_location]);
	ADD_PARAM(&strbuf, curlh, "drp_breadth", BREADTH_COURSES[query->breadth]);

	if (query->graduate_quantitative) ADD_PARAM(&strbuf, curlh, "cbGraduateQuant", "on");
	if (query->days[MONDAY]) ADD_PARAM(&strbuf, curlh, "chkbx_mon", "on");
	if (query->days[TUESDAY]) ADD_PARAM(&strbuf, curlh, "chkbx_tue", "on");
	if (query->days[WEDNESDAY]) ADD_PARAM(&strbuf, curlh, "chkbx_wed", "on");
	if (query->days[THURSDAY]) ADD_PARAM(&strbuf, curlh, "chkbx_thur", "on");
	if (query->days[FRIDAY]) ADD_PARAM(&strbuf, curlh, "chkbx_fri", "on");
	if (query->days[SATURDAY]) ADD_PARAM(&strbuf, curlh, "chkbx_sat", "on");

	strbuf_append_char(&strbuf, '\0');
	return strbuf.data;
}

