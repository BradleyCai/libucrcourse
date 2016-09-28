/*
 * query.h
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#ifndef __QUERY_H
#define __QUERY_H

#include "ucrcourse.h"

struct query_params {
	/* Same names as actual parameters */
	const char drp_term[4];
	const char *drp_subjectArea;
	const char *txtbx_courseTitle;
	const char *txt_instructor;
	const char *txtbx_courseNumber;
	const char drp_startTime[6];
	const char drp_fullOpenClasses[2];
	const char *drp_courseRange;
	const char *drp_location;
	const char *drp_breadth;
	bool cbGraduateQuant;
};

int query_to_params(struct query_params *params, const struct course_query *query);
char *params_to_string(const struct query_params *params);

#endif /* __QUERY_H */

