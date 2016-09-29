/*
 * params.h
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#ifndef __PARAMS_H
#define __PARAMS_H

#include <curl/curl.h>

#include "ucrcourse.h"

#define HOUR_NONE	25

void set_default_term(struct course_query *query);
char *query_to_string(CURL *curlh, const struct course_query *query);

#endif /* __PARAMS_H */

