/*
 * main.c
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include <ucrcourse.h>

#include "file.h"

int main()
{
	struct course_query query;
	struct course_results *results;
	size_t i;
	int ret;

	ret = ucrcourse_init();
	if (ret) {
		return -1;
	}

	ucrcourse_query_init(&query);

	query.subject_area = SUBJECT_CS;
	query.course_number = "14";

	results = ucrcourse_get_courses(&query);
	if (!results) {
		ucrcourse_perror("Query failed");
		return -1;
	}

	printf("Results:\n");
	for (i = 0; i < results->length; i++) {
		const struct course *course = &results->courses[i];
		printf("%s - %s\n",
			course->course_id, course->instructor);
	}

	ucrcourse_results_destroy(results);
	ucrcourse_cleanup();

	return 0;
}

