/*
 * html_scraper.h
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#ifndef __HTML_SCRAPER_H
#define __HTML_SCRAPER_H

#include "ucrcourse.h"

struct course_result *parse_html(const char *html);

#endif /* __HTML_SCRAPER_H */

