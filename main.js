#!/usr/bin/env node

const ucrCourses = require('./lib.js');
const prompt = require('prompt');

prompt.start();

const promptProperties = Object.freeze([
    {
        name: 'quarter',
        validator: /(fall|summer|spring|winter)/i,
        warning: "Quarter must be one of 'fall', 'summer', 'spring' or 'winter.",
    },
    {
        name: 'year',
        validator: /[0-9]{4}/,
        warning: "Year must be a 4-digit number.",
    },
    {
        name: 'subject area',
    },
    {
        name: 'course number',
        validator: /[0-9]{2,}/,
        warning: "Course number must be a positive integer.",
    },
    {
        name: 'class type',
    },
    {
        name: 'days of the week',
        validator: /[MTWRFS]{1,6}/i,
        warning: "Days list should be M, T, W, R, F or S characters only.",
    },
    {
        name: 'start time',
        validator: /[0-9]{2}/,
        warning: "Start time should be an 2-digit hour specification in military time.",
    },
]);

prompt.get(promptProperties, function(err, result) {
    if (err) {
        console.log(err);
        return 1;
    }

    ucrCourses.getCourses(result.quarter, result.year, result.subject_area,
        result.course_number, result.class_type, result.days_of_the_week,
        result.start_time);
});

