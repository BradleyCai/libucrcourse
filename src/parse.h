/*
 * parse.h
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#ifndef __PARSE_H
#define __PARSE_H

#include "ucrcourse.h"

struct course_strings {
	char *course_name;
	char *co_requisites;
	char *instructor;
	char *units;
	char *max_enroll;
	char *pre_requisites;
	char *final_exam;
	char *class_type;
	char *days;
	char *times;
	char *available_seats;
	char *course_status;
	char *course_id;
	char *section_number;
	char *call_number;
};

int create_course(struct course *course, const struct course_strings *data);

#endif /* __PARSE_H */


