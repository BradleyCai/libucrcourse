$.getScript("constants.js");

function getQuarterCode(year, quarter) {
    var quarterLetter;
    switch (quarter) {
        case Quarter.SUMMER:
            quarterLetter = 'U';
            break;
        case Quarter.SPRING:
            quarterLetter = 'S';
            break;
        case Quarter.WINTER:
            quarterLetter = 'W';
            break;
        case Quarter.FALL:
            quarterLetter = 'F';
            break;
        default:
            throw 'Invalid value in quarter enum: ' + quarter;
    }

    if (year % 100 < 10) {
        return '0' + (year % 10);
    } else {
        return year % 100;
    }
}

function getTimeCode(hour, isAM) {
    if (hour < 10) {
        hour = '0' + (hour % 10);
    }

    if (isAM) {
        return hour + 'a.m';
    } else {
        return hour + 'p.m';
    }
}

