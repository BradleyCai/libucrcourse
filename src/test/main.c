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

#include "blob.h"

int main()
{
	struct course_query query;
	struct course_html_parts html;
	struct course_results *results;
	int ret;

	ret = ucrcourse_init();
	if (ret) {
		return -1;
	}

	ucrcourse_query_init(&query);

	query.subject_area = SUBJECT_CS;
	query.course_number = "14";

	puts("Extracted:");
	html = ucrcourse_get_html(&query);
	if (html.listings) {
		save_blob("/tmp/ammon/html.txt", html.listings, 0);
		free(html.listings);
	} else {
		printf("error: %s\n", ucrcourse_strerror(errno));
	}
	puts("***");

	/*
	results = ucrcourse_get_courses(&query);
	printf("Results:\n");
	for (i = 0; i < results->length; i++) {
		struct course *course = &results->courses[i];
		printf("%s %s - %s\n",
			course->course_title, course->course_number, course->instructor);
	}

	ucrcourse_results_destroy(results);
	*/
	ucrcourse_cleanup();

	return 0;
}

