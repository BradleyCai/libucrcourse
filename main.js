#!/usr/bin/env node

const ucrCourses = require('./lib.js');
const prompt = require('prompt');

prompt.start();

const promptProperties = Object.freeze([
    {
        name: 'quarter',
        validator: /(fall|summer|spring|winter)?/i,
        warning: "Quarter must be one of 'fall', 'summer', 'spring' or 'winter.",
    },
    {
        name: 'year',
        validator: /[0-9]{4}?/,
        warning: "Year must be a 4-digit number.",
    },
    {
        name: 'subject area',
    },
    {
        name: 'course number',
        validator: /[0-9]{2,}?/,
        warning: "Course number must be a positive integer.",
    },
    {
        name: 'days of the week',
        validator: /[MTWRFS]{1,6}?/i,
        warning: "Days list should be M, T, W, R, F or S characters only.",
    },
    {
        name: 'start time',
        validator: /[0-9]{2}?/,
        warning: "Start time should be an 2-digit hour specification in military time.",
    },
]);

prompt.get(promptProperties, function(err, result) {
    if (err) {
        console.log(err);
        return 1;
    }

    var quarter;
    switch (result.quarter.toLowerCase()) {
        case 'fall':
            quarter = ucrCourses.Quarter.FALL;
            break;
        case 'summer':
            quarter = ucrCourses.Quarter.SUMMER;
            break;
        case 'spring':
            quarter = ucrCourses.Quarter.SPRING;
            break;
        case 'winter':
            quarter = ucrCourses.Quarter.WINTER;
            break;
        default:
            quater = null;
    }

    var query = new ucrCourses.CourseQuery();
    if (quarter !== '' && result.year !== '') {
        query.setTerm(quarter, parseInt(result.year));
    }
    if (result.subject_area !== '') {
        query.setSubjectArea(ucrCourses.SubjectArea[result.subject_area]);
    }
    if (result.course_number !== '') {
        query.setCourseNumber(result.course_number);
    }
    if (result.days_of_the_week !== '') {
        query.setDaysOfTheWeek(result.days_of_the_week);
    }
    if (result.start_time !== '') {
        query.setStartTime(result.start_time);
    }

    ucrCourses.getCourses(query, function(courses) {
        console.log(courses);
    });
});

