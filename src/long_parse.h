/*
 * long_parse.h
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#ifndef __LONG_PARSE_H
#define __LONG_PARSE_H

#include "ucrcourse.h"

enum subject_area parse_subject_area(const char *str);
enum class_type parse_class_type(const char *str);
int parse_course_status(enum course_status *status, const char *str);

#endif /* __LONG_PARSE_H */

