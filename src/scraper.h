/*
 * scraper.h
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#ifndef __SCRAPER_H
#define __SCRAPER_H

#include "ucrcourse.h"

struct course_results *scrape_html(const char *html);

#endif /* __SCRAPER_H */

