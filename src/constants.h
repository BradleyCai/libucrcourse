/*
 * constants.h
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#ifndef __CONSTANTS_H
#define __CONSTANTS_H

#ifndef __CONSTANTS_EXTERN
# define __CONSTANTS_EXTERN
# define EXTERN extern
#else
# define EXTERN
#endif /* __CONSTANTS_EXTERN */

EXTERN char *SUBJECT_AREAS[];
EXTERN char *CLASS_TYPES[];
EXTERN char *COURSE_LOCATIONS[];
EXTERN char *COURSE_RANGES[];
EXTERN char *BREADTH_COURSES[];

#endif /* __CONSTANTS_H */

