/*
 * ucrcourse.h
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#ifndef __UCR_COURSE_H
#define __UCR_COURSE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdbool.h>
#include <stddef.h>

#define UCRCOURSE_ERR_OK		0
#define UCRCOURSE_ERR_INTERNAL		-100
#define UCRCOURSE_ERR_CURL		-101
#define UCRCOURSE_ERR_INVALID_ARG	-102
#define UCRCOURSE_ERR_CONNECT		-103
#define UCRCOURSE_ERR_SERVER		-104
#define UCRCOURSE_ERR_RESPONSE		-105

enum quarter {
	FALL_QUARTER,
	WINTER_QUARTER,
	SPRING_QUARTER,
	SUMMER_QUARTER
};

enum day {
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
};

enum course_status {
	STATUS_OPEN = 1,
	STATUS_CLOSED = 2,
	STATUS_CANCELLED = 3
};

enum subject_area {
	SUBJECT_ANTH,
	SUBJECT_ARBC,
	SUBJECT_ARLC,
	SUBJECT_ARC,
	SUBJECT_ART,
	SUBJECT_AHS,
	SUBJECT_AST,
	SUBJECT_BSWT,
	SUBJECT_BCH,
	SUBJECT_BIEN,
	SUBJECT_BIOL,
	SUBJECT_BMSC,
	SUBJECT_BPSC,
	SUBJECT_BUS,
	SUBJECT_CBNS,
	SUBJECT_CMDB,
	SUBJECT_CHFY,
	SUBJECT_CEE,
	SUBJECT_CHE,
	SUBJECT_CHEM,
	SUBJECT_CHN,
	SUBJECT_CLA,
	SUBJECT_CNAS,
	SUBJECT_CPAC,
	SUBJECT_CPLT,
	SUBJECT_CS,
	SUBJECT_CRWT,
	SUBJECT_CWPA,
	SUBJECT_DNCE,
	SUBJECT_ECON,
	SUBJECT_EDUC,
	SUBJECT_EE,
	SUBJECT_ENGR,
	SUBJECT_ENGL,
	SUBJECT_ENTM,
	SUBJECT_ENVE,
	SUBJECT_ENSC,
	SUBJECT_ENTX,
	SUBJECT_ETST,
	SUBJECT_EUR,
	SUBJECT_EEOB,
	SUBJECT_FIL,
	SUBJECT_FREN,
	SUBJECT_GDIV,
	SUBJECT_GSST,
	SUBJECT_GEN,
	SUBJECT_GEO,
	SUBJECT_GER,
	SUBJECT_GBST,
	SUBJECT_GRK,
	SUBJECT_HIST,
	SUBJECT_HISE,
	SUBJECT_HISA,
	SUBJECT_HNPG,
	SUBJECT_HASS,
	SUBJECT_ITAL,
	SUBJECT_JPN,
	SUBJECT_KOR,
	SUBJECT_LATN,
	SUBJECT_LNST,
	SUBJECT_LWSO,
	SUBJECT_LGBS,
	SUBJECT_LING,
	SUBJECT_MGT,
	SUBJECT_MSE,
	SUBJECT_MATH,
	SUBJECT_MDCL,
	SUBJECT_ME,
	SUBJECT_MCS,
	SUBJECT_MCBL,
	SUBJECT_MEIS,
	SUBJECT_MUS,
	SUBJECT_NASC,
	SUBJECT_NEM,
	SUBJECT_NRSC,
	SUBJECT_PCST,
	SUBJECT_PHIL,
	SUBJECT_PHYS,
	SUBJECT_PLPA,
	SUBJECT_POSC,
	SUBJECT_PSYC,
	SUBJECT_PBPL,
	SUBJECT_REC,
	SUBJECT_RLST,
	SUBJECT_RUSN,
	SUBJECT_SOC,
	SUBJECT_SWSC,
	SUBJECT_SEAS,
	SUBJECT_SPN,
	SUBJECT_STAT,
	SUBJECT_TFDP,
	SUBJECT_URST,
	SUBJECT_VNM,
	SUBJECT_NONE
};

enum class_type {
	CLASS_LEC,
	CLASS_DIS,
	CLASS_LAB,
	CLASS_LCA,
	CLASS_CLN,
	CLASS_COL,
	CLASS_CON,
	CLASS_FLD,
	CLASS_IND,
	CLASS_INT,
	CLASS_MCE,
	CLASS_PRC,
	CLASS_RES,
	CLASS_SCR,
	CLASS_SEM,
	CLASS_STU,
	CLASS_THE,
	CLASS_TPA,
	CLASS_TUT,
	CLASS_WRK,
	CLASS_ACT,
	CLASS_DEM,
	CLASS_ODL,
	CLASS_W_S,
	CLASS_NONE
};

enum course_location {
	BUILDING_ANDHL,
	BUILDING_BOYHL,
	BUILDING_ARTS,
	BUILDING_ATH,
	BUILDING_BATCH,
	BUILDING_HOUSE,
	BUILDING_BRNHL,
	BUILDING_SURGE,
	BUILDING_INTN,
	BUILDING_INTS,
	BUILDING_CHEM,
	BUILDING_ENTOM,
	BUILDING_ENTMU,
	BUILDING_GENOM,
	BUILDING_GEOL,
	BUILDING_WAT,
	BUILDING_CHPHL,
	BUILDING_HUMN,
	BUILDING_HMNSS,
	BUILDING_LFSC,
	BUILDING_MSE,
	BUILDING_OLMH,
	BUILDING_ONLNE,
	BUILDING_PHY,
	BUILDING_PRCE,
	BUILDING_PSYCH,
	BUILDING_SCLAB,
	BUILDING_SPTH,
	BUILDING_SPR,
	BUILDING_BARN,
	BUILDING_TBA,
	BUILDING_ULB,
	BUILDING_UNLH,
	BUILDING_UV,
	BUILDING_CHUNG,
	BUILDING_NONE
};

enum course_range {
	RANGE_LOWER_DIVISION,
	RANGE_UPPER_DIVISION,
	RANGE_GRADUATE,
	RANGE_POST_DOC,
	RANGE_NONE
};

enum breadth_course {
	BREADTH_E_S_EC,
	BREADTH_E_S_AN,
	BREADTH_E_S_ADD,
	BREADTH_E_N_PS,
	BREADTH_E_N_BS,
	BREADTH_E_N_ADD,
	BREADTH_E_H_WH,
	BREADTH_E_H_FA,
	BREADTH_E_H_ADD,
	BREADTH_E_ETH,
	BREADTH_E_ENGL,
	BREADTH_N_S_ADD,
	BREADTH_N_S,
	BREADTH_N_N_PS,
	BREADTH_N_N_MA,
	BREADTH_N_N_BS,
	BREADTH_N_N_ADD,
	BREADTH_N_WH,
	BREADTH_N_H_RS,
	BREADTH_N_H_PH,
	BREADTH_N_H_FA,
	BREADTH_N_H_ADD,
	BREADTH_N_ETH,
	BREADTH_N_ENGL,
	BREADTH_N_H_WH,
	BREADTH_N_H_LT,
	BREADTH_H_S_EC,
	BREADTH_H_S_AN,
	BREADTH_H_S_ADD,
	BREADTH_H_H_WH,
	BREADTH_H_H_LT,
	BREADTH_H_H_FA,
	BREADTH_H_H_ADD,
	BREADTH_H_N_PS,
	BREADTH_H_N_MA,
	BREADTH_H_N_BS,
	BREADTH_H_N_ADD,
	BREADTH_H_ETH,
	BREADTH_H_ENGL,
	BREADTH_NONE
};

struct course_query {
	/* Term */
	enum quarter quarter;
	unsigned short year;

	/* Subject area */
	enum subject_area subject_area;

	/* Course title */
	const char *course_title;

	/* Instructor */
	const char *instructor;

	/* Course number */
	const char *course_number;

	/* Start time */
	unsigned short start_hour;

	/* Course status */
	enum course_status course_status;

	/* Course range */
	enum course_range course_range;

	/* Class type */
	enum class_type class_type;

	/* Course location */
	enum course_location course_location;

	/* Breadth requirements */
	enum breadth_course breadth;

	/* Graduate quantitative method */
	bool graduate_quantitative;

	/* Days of the week */
	bool days[6];
};

struct course {
	/* Course number */
	const char *course_number;

	/* Section */
	unsigned short section;

	/* Call number */
	unsigned short call_number;

	/* Course title */
	const char *course_title;

	/* Instructor */
	const char *instructor;

	/* Class type */
	enum class_type class_type;

	/* Days */
	bool days[6];

	/* Time */
	unsigned char start_hour, start_minute;
	unsigned char end_hour, end_minute;

	/* Available seats */
	unsigned short available_seats, max_enrollment;

	/* Waitlist */
	unsigned short on_wait_list, max_wait_list;

	/* Course status */
	enum course_status status;

	/* Other information */
	struct {
		unsigned char month, day;
		unsigned short year;

		unsigned char start_hour, start_minute;
		unsigned char end_hour, end_minute;
	} final_exam_date;

	const char *co_requisites, *pre_requisites;
	const char *schedule_notes, *grade_type;
	const char *catalog_description;
};

struct course_results {
	struct course *courses;
	size_t length;
};

struct course_html_parts {
	char *listings;
	char *details;
};

int ucrcourse_init(void);
void ucrcourse_cleanup(void);
const char *ucrcourse_strerror(int error);

void ucrcourse_query_init(struct course_query *query);
void ucrcourse_results_destroy(struct course_results *results);
char *ucrcourse_get_raw(const struct course_query *query);
struct course_html_parts ucrcourse_get_html(const struct course_query *query);
struct course_results *ucrcourse_get_courses(const struct course_query *query);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __UCR_COURSE_H */

