/*
 * html_scraper.h
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#ifndef __HTML_SCRAPER_H
#define __HTML_SCRAPER_H

#include "ucrcourse.h"

void extract_html(const char *response, char **listing_html, char **detail_html);
struct course_results *scrape_html(const char *html);

#endif /* __HTML_SCRAPER_H */

