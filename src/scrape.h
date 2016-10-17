/*
 * scrape.h
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#ifndef __SCRAPE_H
#define __SCRAPE_H

#include "ucrcourse.h"

struct course_results *scrape_html(const char *html);

#endif /* __SCRAPE_H */

