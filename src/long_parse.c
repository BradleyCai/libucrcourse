/*
 * long_parse.c
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#include <stddef.h>
#include <string.h>

#include "long_parse.h"

static const char *const subject_areas[] = {
	"ANTH",
	"ARBC",
	"ARLC",
	"ARC",
	"ART",
	"AHS",
	"AST",
	"BSWT",
	"BCH",
	"BIEN",
	"BIOL",
	"BMSC",
	"BPSC",
	"BUS",
	"CBNS",
	"CMDB",
	"CHFY",
	"CEE",
	"CHE",
	"CHEM",
	"CHN",
	"CLA",
	"CNAS",
	"CPAC",
	"CPLT",
	"CS",
	"CRWT",
	"CWPA",
	"DNCE",
	"ECON",
	"EDUC",
	"EE",
	"ENGR",
	"ENGL",
	"ENTM",
	"ENVE",
	"ENSC",
	"ENTX",
	"ETST",
	"EUR",
	"EEOB",
	"FIL",
	"FREN",
	"GDIV",
	"GSST",
	"GEN",
	"GEO",
	"GER",
	"GBST",
	"GRK",
	"HIST",
	"HISE",
	"HISA",
	"HNPG",
	"HASS",
	"ITAL",
	"JPN",
	"KOR",
	"LATN",
	"LNST",
	"LWSO",
	"LGBS",
	"LING",
	"MGT",
	"MSE",
	"MATH",
	"MDCL",
	"ME",
	"MCS",
	"MCBL",
	"MEIS",
	"MUS",
	"NASC",
	"NEM",
	"NRSC",
	"PCST",
	"PHIL",
	"PHYS",
	"PLPA",
	"POSC",
	"PSYC",
	"PBPL",
	"REC",
	"RLST",
	"RUSN",
	"SOC",
	"SWSC",
	"SEAS",
	"SPN",
	"STAT",
	"TFDP",
	"URST",
	"VNM",
	NULL
};

static const char *const class_types[] = {
	"LEC",
	"DIS",
	"LAB",
	"LCA",
	"CLN",
	"COL",
	"CON",
	"FLD",
	"IND",
	"INT",
	"MCE",
	"PRC",
	"RES",
	"SCR",
	"SEM",
	"STU",
	"THE",
	"TPA",
	"TUT",
	"WRK",
	"ACT",
	"DEM",
	"ODL",
	"W_S",
	NULL
};

enum subject_area parse_subject_area(const char *str)
{
	enum subject_area result = SUBJECT_ANTH;
	size_t i;

	for (i = 0; subject_areas[i]; i++, result++) {
		if (!strcmp(str, subject_areas[i])) {
			return result;
		}
	}

	return SUBJECT_NONE;
}

enum class_type parse_class_type(const char *str)
{
	enum class_type result = CLASS_LEC;
	size_t i;

	for (i = 0; class_types[i]; i++, result++) {
		if (!strcmp(str, class_types[i])) {
			return result;
		}
	}

	return CLASS_NONE;
}

int parse_course_status(enum course_status *status, const char *str)
{
	if (!strncmp(str, "OPEN", 4)) {
		*status = STATUS_OPEN;
	} else if (!strncmp(str, "CLOSE", 5)) {
		*status = STATUS_CLOSED;
	} else if (!strncmp(str, "CANCEL", 6)) {
		*status = STATUS_CANCELLED;
	} else {
		return -1;
	}

	return 0;
}

