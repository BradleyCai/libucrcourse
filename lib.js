/*
 * libucrcourse - The UCR Course library
 * An open source library to utilize the UCR schedule of classes.
 *
 * Available under the MIT license. See the LICENSE file for more details.
 */

// Have NodeJS load jQuery
if (typeof 'window' === undefined) {
    $ = require('jquery');
}

///////////////
// Constants //
///////////////

const Quarter = Object.freeze({
    SUMMER: 0,
    SPRING: 1,
    WINTER: 2,
    FALL: 3,
});

const SubjectArea = Object.freeze({
    ANTH: ['ANTH', 'Anthropology'],
    ARBC: ['ARBC', 'Arabic'],
    ARLC: ['ARLC', 'Arabic Literature and Cultures'],
    ARC: ['ARC ', 'ARC'],
    ART: ['ART ', 'Art'],
    AHS: ['AHS ', 'Art History'],
    AST: ['AST ', 'Asian Studies'],
    BSWT: ['BSWT', 'Basic Writing'],
    BCH: ['BCH ', 'Biochemistry'],
    BIEN: ['BIEN', 'Bioengineering'],
    BIOL: ['BIOL', 'Biology'],
    BMSC: ['BMSC', 'Biomedical Sciences'],
    BPSC: ['BPSC', 'Botany/Plant Science'],
    BUS: ['BUS ', 'Business'],
    CBNS: ['CBNS', 'Cell Biology and Neuroscience'],
    CMDB: ['CMDB', 'Cell, Molecular, and Developmental Biology'],
    CHFY: ['CHFY', 'CHASS First Year Experience'],
    CEE: ['CEE ', 'Chemical and Environmental Engineering'],
    CHE: ['CHE ', 'Chemical Engineering'],
    CHEM: ['CHEM', 'Chemistry'],
    CHN: ['CHN ', 'Chinese'],
    CLA: ['CLA ', 'Classical Studies'],
    CNAS: ['CNAS', 'College of Natural & Ag Sci'],
    CPAC: ['CPAC', 'Comparative Ancient Civilizations'],
    CPLT: ['CPLT', 'Comparative Literature'],
    CS: ['CS  ', 'Computer Science'],
    CRWT: ['CRWT', 'Creative Writing'],
    CWPA: ['CWPA', 'Creative Writing & Writing for the Performing Arts'],
    DNCE: ['DNCE', 'Dance'],
    ECON: ['ECON', 'Economics'],
    EDUC: ['EDUC', 'Education'],
    EE: ['EE  ', 'Electrical Engineering'],
    ENGR: ['ENGR', 'Engineering'],
    ENGL: ['ENGL', 'English'],
    ENTM: ['ENTM', 'Entomology'],
    ENVE: ['ENVE', 'Environmental Engineering'],
    ENSC: ['ENSC', 'Environmental Sciences'],
    ENTX: ['ENTX', 'Environmental Toxicology'],
    ETST: ['ETST', 'Ethnic Studies'],
    EUR: ['EUR ', 'European Culture'],
    EEOB: ['EEOB', 'Evolution, Ecology, & Organismal Biology'],
    FIL: ['FIL ', 'Filipino'],
    FREN: ['FREN', 'French'],
    GDIV: ['GDIV', 'GDIV'],
    GSST: ['GSST', 'Gender and Sexuality Studies'],
    GEN: ['GEN ', 'Genetics'],
    GEO: ['GEO ', 'Geosciences'],
    GER: ['GER ', 'German'],
    GBST: ['GBST', 'Global Studies'],
    GRK: ['GRK ', 'Greek'],
    HIST: ['HIST', 'History'],
    HISE: ['HISE', 'History of Europe'],
    HISA: ['HISA', 'History of the Americas'],
    HNPG: ['HNPG', 'Honors'],
    HASS: ['HASS', 'Humanities, Arts, and Social Sciences'],
    ITAL: ['ITAL', 'Italian'],
    JPN: ['JPN ', 'Japanese'],
    KOR: ['KOR ', 'Korean'],
    LATN: ['LATN', 'Latin'],
    LNST: ['LNST', 'Latin American Studies'],
    LWSO: ['LWSO', 'Law and Society'],
    LGBS: ['LGBS', 'Lesbian, Gay, Bisexual Studies'],
    LING: ['LING', 'Linguistics'],
    MGT: ['MGT ', 'Management'],
    MSE: ['MSE ', 'Materials Science and Engineering'],
    MATH: ['MATH', 'Mathematics'],
    MDCL: ['MDCL', 'MDCL'],
    ME: ['ME  ', 'Mechanical Engineering'],
    MCS: ['MCS ', 'Media and Cultural Studies '],
    MCBL: ['MCBL', 'Microbiology'],
    MEIS: ['MEIS', 'Middle East & Islamic Studies '],
    MUS: ['MUS ', 'Music'],
    NASC: ['NASC', 'Natural and Agricultural Sciences'],
    NEM: ['NEM ', 'Nematology'],
    NRSC: ['NRSC', 'Neuroscience'],
    PCST: ['PCST', 'Peace & Conflict Studies'],
    PHIL: ['PHIL', 'Philosophy'],
    PHYS: ['PHYS', 'Physics & Astronomy'],
    PLPA: ['PLPA', 'Plant Pathology & Microbiology'],
    POSC: ['POSC', 'Political Science'],
    PSYC: ['PSYC', 'Psychology'],
    PBPL: ['PBPL', 'Public Policy'],
    REC: ['REC ', 'Recreation'],
    RLST: ['RLST', 'Religious Studies'],
    RUSN: ['RUSN', 'Russian Studies'],
    SOC: ['SOC ', 'Sociology'],
    SWSC: ['SWSC', 'Soil and Water Science'],
    SEAS: ['SEAS', 'Southeast Asian Studies'],
    SPN: ['SPN ', 'Spanish'],
    STAT: ['STAT', 'Statistics'],
    TFDP: ['TFDP', 'Theater, Film & Digital Production'],
    URST: ['URST', 'Urban Studies'],
    VNM: ['VNM ', 'Vietnamese'],
});

const ClassType = Object.freeze([
    ['LEC', 'Lecture'],
    ['DIS', 'Discussion'],
    ['LAB', 'Laboratory'],
    ['LCA', 'Additional lecture'],
    ['CLN', 'Clinic'],
    ['COL', 'Colloquium'],
    ['CON', 'Consultation'],
    ['FLD', 'Field'],
    ['IND', 'Individualized STUDY'],
    ['INT', 'Internship'],
    ['MCE', 'Multiple course entry'],
    ['PRC', 'Practicum'],
    ['RES', 'Research'],
    ['SCR', 'Screening'],
    ['SEM', 'Seminar'],
    ['STU', 'Studio'],
    ['THE', 'Thesis'],
    ['TPA', 'Term paper'],
    ['TUT', 'Tutorial'],
    ['WRK', 'Workshop'],
    ['ACT', 'Activity'],
    ['DEM', 'Demonstration'],
    ['ODL', 'Online dis and listening'],
    ['W&S', 'Workshop & screening'],
]);

const CourseLocation = Object.freeze({
    ANDHL: ['ANDHL', 'A. Gary Anderson Hall (ANDHL)'],
    BOYHL: ['BOYHL', 'Alfred M. Boyce Hall (BOYHL)'],
    ARTS: ['ARTS', 'Arts Building (ARTS)'],
    ATH: ['ATH', 'Athletics and Dance Building (ATH)'],
    BATCH: ['BATCH', 'Batchelor Hall (BATCH)'],
    HOUSE: ['HOUSE', 'Botany Headhouses(greenhouses) (HOUSE)'],
    BRNHL: ['BRNHL', 'Bourns Hall (BRNHL)'],
    SURGE: ['SURGE', 'Campus Surge (SURGE)'],
    INTN: ['INTN', 'CHASS Interdisciplinary Bldg-North (INTN)'],
    INTS: ['INTS', 'CHASS Interdisciplinary Bldg-South (INTS)'],
    CHEM: ['CHEM', 'Chemical Sciences (CHEM)'],
    ENTOM: ['ENTOM', 'Entomology (ENTOM)'],
    ENTMU: ['ENTMU', 'Entomology Research Museum (ENTMU)'],
    GENOM: ['GENOM', 'Genomics Building (GENOM)'],
    GEOL: ['GEOL', 'Geology Building (GEOL)'],
    WAT: ['WAT', 'Gordan Watkins Hall (WAT)'],
    CHPHL: ['CHPHL', 'Homer D. Chapman Hall (CHPHL)'],
    HUMN: ['HUMN', 'Humanities (HUMN)'],
    HMNSS: ['HMNSS', 'Humanities and Social Sciences (HMNSS)'],
    LFSC: ['LFSC', 'Life Sciences Building (LFSC)'],
    MSE: ['MSE', 'Materials Science and Engineering (MSE)'],
    OLMH: ['OLMH', 'Olmsted Hall (OLMH)'],
    ONLNE: ['ONLNE', 'Online (ONLNE)'],
    PHY: ['PHY', 'Physics (PHY)'],
    PRCE: ['PRCE', 'Pierce Hall (PRCE)'],
    PSYCH: ['PSYCH', 'Psychology (PSYCH)'],
    SCLAB: ['SCLAB', 'Science Laboratories 1 (SCLAB)'],
    SPTH: ['SPTH', 'Spieth Hall (SPTH)'],
    SPR: ['SPR', 'Sproul Hall (SPR)'],
    BARN: ['BARN', 'The Barn (BARN)'],
    TBA: ['TBA', 'To Be Announced (TBA)'],
    ULB: ['ULB', 'University Laboratory Building (ULB)'],
    UNLH: ['UNLH', 'University Lecture Hall (UNLH)'],
    UV: ['UV', 'University Village (UV)'],
    CHUNG: ['CHUNG', 'Winston Chung Hall (CHUNG)'],
});

// The equivalent code value is the stringified value of the integer
const CourseStatus = Object.freeze({
    OPEN: 1,
    CLOSED: 2,
    CANCELLED: 3,
});

const CourseRange = Object.freeze({
    LOWER_DIVISION: ['LGraduate', 'Lower Division', [0, 99]],
    UPPER_DIVISION: ['UGraduate', 'Upper Division', [100, 199]],
    GRADUATE:       ['Graduate', 'Graduate', [200, 299]],
    POST_DOCTORATE: ['PostDoc', 'Professional/Teaching', [300, 999]]
});

const DayOfWeek = Object.freeze({
    MONDAY: 0,
    TUESDAY: 1,
    WEDNESDAY: 2,
    THURSDAY: 3,
    FRIDAY: 4,
    SATURDAY: 5,
});

const BreadthCourse = Object.freeze([
    ['E-S-EC', ['COE', 'Social Sciences - Econ, Poli Sci']],
    ['E-S-AN', ['COE', 'Social Sciences - Anth, Psyc, Soc']],
    ['E-S-ADD', ['COE', 'Social Sciences - Additional']],
    ['E-N-PS', ['COE', 'Nat Sci & Math - Phys Sci']],
    ['E-N-BS', ['COE', 'Nat Sci & Math - Biol Sci']],
    ['E-N-ADD', ['COE', 'Nat Sci & Math - Additional']],
    ['E-H-WH', ['COE', 'Humanities - World History']],
    ['E-H-FA', ['COE', 'Humanities - Fine Arts, Lit, Phil, Rel Studies']],
    ['E-H-ADD', ['COE', 'Humanities - Additional']],
    ['E-ETH', ['COE', 'Ethnicity']],
    ['E-ENGL', ['COE', 'English Composition']],
    ['N-S-ADD', ['CNAS', 'Social Sciences - Additional']],
    ['N-S', ['CNAS', 'Social Sciences']],
    ['N-N-PS', ['CNAS', 'Nat Sci & Math - Phys Sci']],
    ['N-N-MA', ['CNAS', 'Nat Sci & Math - Math, Stat, Comp Sci']],
    ['N-N-BS', ['CNAS', 'Nat Sci & Math - Biological Sci']],
    ['N-N-ADD', ['CNAS', 'Nat Sci & Math - Additional']],
    ['N-WH', ['CNAS', 'Humanities - World History']],
    ['N-H-RS', ['CNAS', 'Humanities - Religious Studies']],
    ['N-H-PH', ['CNAS', 'Humanities - Philosophy']],
    ['N-H-FA', ['CNAS', 'Humanities - Fine Arts']],
    ['N-H-ADD', ['CNAS', 'Humanities - Additional']],
    ['N-ETH', ['CNAS', 'Ethnicity']],
    ['N-ENGL', ['CNAS', 'English Composition']],
    ['N-H-WH', ['CNAS ', 'Humanities - World History']],
    ['N-H-LT', ['CNAS ', 'Humanities - Lit, Phil, Rel Studies']],
    ['H-S-EC', ['CHASS', 'Social Sciences - Econ, Poli Sci']],
    ['H-S-AN', ['CHASS', 'Social Sciences - Anth, Psyc, Soc']],
    ['H-S-ADD', ['CHASS', 'Social Sciences - Additional']],
    ['H-H-WH', ['CHASS', 'Humanities - World History']],
    ['H-H-LT', ['CHASS', 'Humanities - Lit, Phil, Rel Studies']],
    ['H-H-FA', ['CHASS', 'Humanities - Fine Arts']],
    ['H-H-ADD', ['CHASS','Humanities - Additional']],
    ['H-N-PS', ['CHASS', 'Nat Sci & Math - Phys Sci']],
    ['H-N-MA', ['CHASS', 'Nat Sci & Math - Math, Stat, Comp Sci']],
    ['H-N-BS', ['CHASS', 'Nat Sci & Math - Biol Sci']],
    ['H-N-ADD', ['CHASS', 'Nat Sci & Math - Additional']],
    ['H-ETH', ['CHASS', 'Ethnicity']],
    ['H-ENGL', ['CHASS', 'English Composition']],
]);

///////////
// Blobs //
///////////

const VIEWSTATE = '/wEPDwUJNzU4ODU5NDI3D2QWAgIDD2QWFgILDw8WAh4LTmF2aWdhdGVVcmwFL2h0dHA6Ly9yZWdpc3RyYXIudWNyLmVkdS9yZWdpc3RyYXIvZGVmYXVsdC5hc3B4ZGQCDQ8PFgIfAAVDaHR0cDovL3JlZ2lzdHJhci51Y3IuZWR1L1JlZ2lzdHJhci9TY2hlZHVsZS1vZi1DbGFzc2VzL0RlZmF1bHQuYXNweGRkAhEPDxYCHwAFR2h0dHA6Ly9yZWdpc3RyYXIudWNyLmVkdS9yZWdpc3RyYXIvcmVnaXN0ZXJpbmctZm9yLWNsYXNzZXMvZGVmYXVsdC5hc3B4ZGQCEw8PFgIfAAVAaHR0cDovL3JlZ2lzdHJhci51Y3IuZWR1L3JlZ2lzdHJhci90dWl0aW9uLWFuZC1mZWVzL2RlZmF1bHQuYXNweGRkAhUPDxYCHwAFTWh0dHA6Ly9yZWdpc3RyYXIudWNyLmVkdS9yZWdpc3RyYXIvYWNhZGVtaWMtY2FsZW5kYXIvZmluYWwtZXhhbS1zY2hlZHVsZS5hc3B4ZGQCFw8PFgIfAAVIaHR0cDovL3JlZ2lzdHJhci51Y3IuZWR1L3JlZ2lzdHJhci9ndWlkZS10by1ncmFkdWF0aW9uL2RlZ3JlZS1hdWRpdC5hc3B4ZGQCGw9kFgJmD2QWBgIBDw8WAh4EVGV4dGVkZAIDD2QWFAIDD2QWAmYPDxYCHghJbWFnZVVybAURfi9pbWFnZXMvcGx1cy5QTkdkZAIFD2QWDAIBDxAPFgYeDURhdGFUZXh0RmllbGQFBERlc2MeDkRhdGFWYWx1ZUZpZWxkBQRUZXJtHgtfIURhdGFCb3VuZGdkEBU8BzE2IEZBTEwJMTYgU1VNTUVSCTE2IFNQUklORwkxNiBXSU5URVIHMTUgRkFMTAkxNSBTVU1NRVIJMTUgU1BSSU5HCTE1IFdJTlRFUgcxNCBGQUxMCTE0IFNVTU1FUgkxNCBTUFJJTkcJMTQgV0lOVEVSBzEzIEZBTEwJMTMgU1BSSU5HCTEzIFNVTU1FUgkxMyBXSU5URVIHMTIgRkFMTAkxMiBTUFJJTkcJMTIgU1VNTUVSCTEyIFdJTlRFUgcxMSBGQUxMCTExIFNQUklORwkxMSBTVU1NRVIJMTEgV0lOVEVSBzEwIEZBTEwJMTAgU1VNTUVSCTEwIFNQUklORwkxMCBXSU5URVIHMDkgRkFMTAkwOSBTUFJJTkcJMDkgV0lOVEVSCTA5IFNVTU1FUgcwOCBGQUxMCTA4IFNQUklORwkwOCBXSU5URVIHMDcgRkFMTAkwNyBTUFJJTkcJMDcgV0lOVEVSBzA2IEZBTEwJMDYgU1BSSU5HCTA2IFdJTlRFUgcwNSBGQUxMCTA1IFNQUklORwkwNSBXSU5URVIHMDQgRkFMTAkwNCBTUFJJTkcJMDQgV0lOVEVSBzAzIEZBTEwJMDMgU1BSSU5HCTAzIFdJTlRFUgcwMiBGQUxMCTAyIFNQUklORwkwMiBXSU5URVIHMDEgRkFMTAkwMSBTUFJJTkcJMDEgV0lOVEVSBzAwIEZBTEwJMDAgU1BSSU5HCTAwIFdJTlRFUgc5OSBGQUxMFTwDMTZGAzE2VQMxNlMDMTZXAzE1RgMxNVUDMTVTAzE1VwMxNEYDMTRVAzE0UwMxNFcDMTNGAzEzUwMxM1UDMTNXAzEyRgMxMlMDMTJVAzEyVwMxMUYDMTFTAzExVQMxMVcDMTBGAzEwVQMxMFMDMTBXAzA5RgMwOVMDMDlXAzA5VQMwOEYDMDhTAzA4VwMwN0YDMDdTAzA3VwMwNkYDMDZTAzA2VwMwNUYDMDVTAzA1VwMwNEYDMDRTAzA0VwMwM0YDMDNTAzAzVwMwMkYDMDJTAzAyVwMwMUYDMDFTAzAxVwMwMEYDMDBTAzAwVwM5OUYUKwM8Z2dnZ2dnZ2dnZ2dnZ2dnZ2dnZ2dnZ2dnZ2dnZ2dnZ2dnZ2dnZ2dnZ2dnZ2dnZ2dnZ2dnZ2dnZ2dnZ2dnFgFmZAIDDxAPFgYfAwUERGVzYx8EBQdTdWJqZWN0HwVnZA8WXQIBAgICAwIEAgUCBgIHAggCCQIKAgsCDAINAg4CDwIQAhECEgITAhQCFQIWAhcCGAIZAhoCGwIcAh0CHgIfAiACIQIiAiMCJAIlAiYCJwIoAikCKgIrAiwCLQIuAi8CMAIxAjICMwI0AjUCNgI3AjgCOQI6AjsCPAI9Aj4CPwJAAkECQgJDAkQCRQJGAkcCSAJJAkoCSwJMAk0CTgJPAlACUQJSAlMCVAJVAlYCVwJYAlkCWgJbAlwCXRZdEAUMQW50aHJvcG9sb2d5BQRBTlRIZxAFB0FyYWJpYyAFBEFSQkNnEAUfQXJhYmljIExpdGVyYXR1cmUgYW5kIEN1bHR1cmVzIAUEQVJMQ2cQBQRBUkMgBQRBUkMgZxAFA0FydAUEQVJUIGcQBQtBcnQgSGlzdG9yeQUEQUhTIGcQBQ1Bc2lhbiBTdHVkaWVzBQRBU1QgZxAFDUJhc2ljIFdyaXRpbmcFBEJTV1RnEAUMQmlvY2hlbWlzdHJ5BQRCQ0ggZxAFDkJpb2VuZ2luZWVyaW5nBQRCSUVOZxAFB0Jpb2xvZ3kFBEJJT0xnEAUTQmlvbWVkaWNhbCBTY2llbmNlcwUEQk1TQ2cQBRRCb3RhbnkvUGxhbnQgU2NpZW5jZQUEQlBTQ2cQBQhCdXNpbmVzcwUEQlVTIGcQBR1DZWxsIEJpb2xvZ3kgYW5kIE5ldXJvc2NpZW5jZQUEQ0JOU2cQBSpDZWxsLCBNb2xlY3VsYXIsIGFuZCBEZXZlbG9wbWVudGFsIEJpb2xvZ3kFBENNREJnEAUbQ0hBU1MgRmlyc3QgWWVhciBFeHBlcmllbmNlBQRDSEZZZxAFJkNoZW1pY2FsIGFuZCBFbnZpcm9ubWVudGFsIEVuZ2luZWVyaW5nBQRDRUUgZxAFFENoZW1pY2FsIEVuZ2luZWVyaW5nBQRDSEUgZxAFCUNoZW1pc3RyeQUEQ0hFTWcQBQdDaGluZXNlBQRDSE4gZxAFEUNsYXNzaWNhbCBTdHVkaWVzBQRDTEEgZxAFG0NvbGxlZ2Ugb2YgTmF0dXJhbCAmIEFnIFNjaQUEQ05BU2cQBSFDb21wYXJhdGl2ZSBBbmNpZW50IENpdmlsaXphdGlvbnMFBENQQUNnEAUWQ29tcGFyYXRpdmUgTGl0ZXJhdHVyZQUEQ1BMVGcQBRBDb21wdXRlciBTY2llbmNlBQRDUyAgZxAFEENyZWF0aXZlIFdyaXRpbmcFBENSV1RnEAUyQ3JlYXRpdmUgV3JpdGluZyAmIFdyaXRpbmcgZm9yIHRoZSBQZXJmb3JtaW5nIEFydHMFBENXUEFnEAUFRGFuY2UFBEROQ0VnEAUJRWNvbm9taWNzBQRFQ09OZxAFCUVkdWNhdGlvbgUERURVQ2cQBRZFbGVjdHJpY2FsIEVuZ2luZWVyaW5nBQRFRSAgZxAFC0VuZ2luZWVyaW5nBQRFTkdSZxAFB0VuZ2xpc2gFBEVOR0xnEAUKRW50b21vbG9neQUERU5UTWcQBRlFbnZpcm9ubWVudGFsIEVuZ2luZWVyaW5nBQRFTlZFZxAFFkVudmlyb25tZW50YWwgU2NpZW5jZXMFBEVOU0NnEAUYRW52aXJvbm1lbnRhbCBUb3hpY29sb2d5BQRFTlRYZxAFDkV0aG5pYyBTdHVkaWVzBQRFVFNUZxAFEEV1cm9wZWFuIEN1bHR1cmUFBEVVUiBnEAUoRXZvbHV0aW9uLCBFY29sb2d5LCAmIE9yZ2FuaXNtYWwgQmlvbG9neQUERUVPQmcQBQhGaWxpcGlubwUERklMIGcQBQZGcmVuY2gFBEZSRU5nEAUER0RJVgUER0RJVmcQBRxHZW5kZXIgYW5kIFNleHVhbGl0eSBTdHVkaWVzBQRHU1NUZxAFCEdlbmV0aWNzBQRHRU4gZxAFC0dlb3NjaWVuY2VzBQRHRU8gZxAFBkdlcm1hbgUER0VSIGcQBQ5HbG9iYWwgU3R1ZGllcwUER0JTVGcQBQVHcmVlawUER1JLIGcQBQdIaXN0b3J5BQRISVNUZxAFEUhpc3Rvcnkgb2YgRXVyb3BlBQRISVNFZxAFF0hpc3Rvcnkgb2YgdGhlIEFtZXJpY2FzBQRISVNBZxAFBkhvbm9ycwUESE5QR2cQBSVIdW1hbml0aWVzLCBBcnRzLCBhbmQgU29jaWFsIFNjaWVuY2VzBQRIQVNTZxAFB0l0YWxpYW4FBElUQUxnEAUISmFwYW5lc2UFBEpQTiBnEAUGS29yZWFuBQRLT1IgZxAFBUxhdGluBQRMQVROZxAFFkxhdGluIEFtZXJpY2FuIFN0dWRpZXMFBExOU1RnEAUPTGF3IGFuZCBTb2NpZXR5BQRMV1NPZxAFHkxlc2JpYW4sIEdheSwgQmlzZXh1YWwgU3R1ZGllcwUETEdCU2cQBQtMaW5ndWlzdGljcwUETElOR2cQBQpNYW5hZ2VtZW50BQRNR1QgZxAFIU1hdGVyaWFscyBTY2llbmNlIGFuZCBFbmdpbmVlcmluZwUETVNFIGcQBQtNYXRoZW1hdGljcwUETUFUSGcQBQRNRENMBQRNRENMZxAFFk1lY2hhbmljYWwgRW5naW5lZXJpbmcFBE1FICBnEAUbTWVkaWEgYW5kIEN1bHR1cmFsIFN0dWRpZXMgBQRNQ1MgZxAFDE1pY3JvYmlvbG9neQUETUNCTGcQBR5NaWRkbGUgRWFzdCAmIElzbGFtaWMgU3R1ZGllcyAFBE1FSVNnEAUFTXVzaWMFBE1VUyBnEAUhTmF0dXJhbCBhbmQgQWdyaWN1bHR1cmFsIFNjaWVuY2VzBQROQVNDZxAFCk5lbWF0b2xvZ3kFBE5FTSBnEAUMTmV1cm9zY2llbmNlBQROUlNDZxAFGFBlYWNlICYgQ29uZmxpY3QgU3R1ZGllcwUEUENTVGcQBQpQaGlsb3NvcGh5BQRQSElMZxAFE1BoeXNpY3MgJiBBc3Ryb25vbXkFBFBIWVNnEAUeUGxhbnQgUGF0aG9sb2d5ICYgTWljcm9iaW9sb2d5BQRQTFBBZxAFEVBvbGl0aWNhbCBTY2llbmNlBQRQT1NDZxAFClBzeWNob2xvZ3kFBFBTWUNnEAUNUHVibGljIFBvbGljeQUEUEJQTGcQBQpSZWNyZWF0aW9uBQRSRUMgZxAFEVJlbGlnaW91cyBTdHVkaWVzBQRSTFNUZxAFD1J1c3NpYW4gU3R1ZGllcwUEUlVTTmcQBQlTb2Npb2xvZ3kFBFNPQyBnEAUWU29pbCBhbmQgV2F0ZXIgU2NpZW5jZQUEU1dTQ2cQBRdTb3V0aGVhc3QgQXNpYW4gU3R1ZGllcwUEU0VBU2cQBQdTcGFuaXNoBQRTUE4gZxAFClN0YXRpc3RpY3MFBFNUQVRnEAUiVGhlYXRlciwgRmlsbSAmIERpZ2l0YWwgUHJvZHVjdGlvbgUEVEZEUGcQBQ1VcmJhbiBTdHVkaWVzBQRVUlNUZxAFClZpZXRuYW1lc2UFBFZOTSBnZGQCBw8QDxYGHwMFCEFjdGl2aXR5HwQFA0FDVB8FZ2QPFhgCAQICAgMCBAIFAgYCBwIIAgkCCgILAgwCDQIOAg8CEAIRAhICEwIUAhUCFgIXAhgWGBAFB0xFQ1RVUkUFA0xFQ2cQBQpESVNDVVNTSU9OBQNESVNnEAUKTEFCT1JBVE9SWQUDTEFCZxAFEkFERElUSU9OQUwgTEVDVFVSRQUDTENBZxAFBkNMSU5JQwUDQ0xOZxAFCkNPTExPUVVJVU0FA0NPTGcQBQxDT05TVUxUQVRJT04FA0NPTmcQBQVGSUVMRAUDRkxEZxAFFElORElWSURVQUxJWkVEIFNUVURZBQNJTkRnEAUKSU5URVJOU0hJUAUDSU5UZxAFFU1VTFRJUExFIENPVVJTRSBFTlRSWQUDTUNFZxAFCVBSQUNUSUNVTQUDUFJDZxAFCFJFU0VBUkNIBQNSRVNnEAUJU0NSRUVOSU5HBQNTQ1JnEAUHU0VNSU5BUgUDU0VNZxAFBlNUVURJTwUDU1RVZxAFBlRIRVNJUwUDVEhFZxAFClRFUk0gUEFQRVIFA1RQQWcQBQhUVVRPUklBTAUDVFVUZxAFCFdPUktTSE9QBQNXUktnEAUIQUNUSVZJVFkFA0FDVGcQBQ1ERU1PTlNUUkFUSU9OBQNERU1nEAUYT05MSU5FIERJUyBBTkQgTElTVEVOSU5HBQNPRExnEAUUV09SS1NIT1AgJiBTQ1JFRU5JTkcFA1cmU2dkZAIfDxAPFgYfAwUITG9jYXRpb24fBAUETmFtZR8FZ2QPFiMCAQICAgMCBAIFAgYCBwIIAgkCCgILAgwCDQIOAg8CEAIRAhICEwIUAhUCFgIXAhgCGQIaAhsCHAIdAh4CHwIgAiECIgIjFiMQBR1BLiBHYXJ5IEFuZGVyc29uIEhhbGwgKEFOREhMKQUFQU5ESExnEAUcQWxmcmVkIE0uIEJveWNlIEhhbGwgKEJPWUhMKQUFQk9ZSExnEAUUQXJ0cyBCdWlsZGluZyAoQVJUUykFBEFSVFNnEAUiQXRobGV0aWNzIGFuZCBEYW5jZSBCdWlsZGluZyAoQVRIKQUDQVRIZxAFFkJhdGNoZWxvciBIYWxsIChCQVRDSCkFBUJBVENIZxAFJkJvdGFueSBIZWFkaG91c2VzKGdyZWVuaG91c2VzKSAoSE9VU0UpBQVIT1VTRWcQBRNCb3VybnMgSGFsbCAoQlJOSEwpBQVCUk5ITGcQBRRDYW1wdXMgU3VyZ2UgKFNVUkdFKQUFU1VSR0VnEAUpQ0hBU1MgSW50ZXJkaXNjaXBsaW5hcnkgQmxkZy1Ob3J0aCAoSU5UTikFBElOVE5nEAUpQ0hBU1MgSW50ZXJkaXNjaXBsaW5hcnkgQmxkZy1Tb3V0aCAoSU5UUykFBElOVFNnEAUYQ2hlbWljYWwgU2NpZW5jZXMgKENIRU0pBQRDSEVNZxAFEkVudG9tb2xvZ3kgKEVOVE9NKQUFRU5UT01nEAUiRW50b21vbG9neSBSZXNlYXJjaCBNdXNldW0gKEVOVE1VKQUFRU5UTVVnEAUZR2Vub21pY3MgQnVpbGRpbmcgKEdFTk9NKQUFR0VOT01nEAUXR2VvbG9neSBCdWlsZGluZyAoR0VPTCkFBEdFT0xnEAUZR29yZGFuIFdhdGtpbnMgSGFsbCAoV0FUKQUDV0FUZxAFHUhvbWVyIEQuIENoYXBtYW4gSGFsbCAoQ0hQSEwpBQVDSFBITGcQBRFIdW1hbml0aWVzIChIVU1OKQUESFVNTmcQBSZIdW1hbml0aWVzIGFuZCBTb2NpYWwgU2NpZW5jZXMgKEhNTlNTKQUFSE1OU1NnEAUdTGlmZSBTY2llbmNlcyBCdWlsZGluZyAoTEZTQykFBExGU0NnEAUnTWF0ZXJpYWxzIFNjaWVuY2UgYW5kIEVuZ2luZWVyaW5nIChNU0UpBQNNU0VnEAUTT2xtc3RlZCBIYWxsIChPTE1IKQUET0xNSGcQBQ5PbmxpbmUgKE9OTE5FKQUFT05MTkVnEAUNUGh5c2ljcyAoUEhZKQUDUEhZZxAFElBpZXJjZSBIYWxsIChQUkNFKQUEUFJDRWcQBRJQc3ljaG9sb2d5IChQU1lDSCkFBVBTWUNIZxAFHlNjaWVuY2UgTGFib3JhdG9yaWVzIDEgKFNDTEFCKQUFU0NMQUJnEAUSU3BpZXRoIEhhbGwgKFNQVEgpBQRTUFRIZxAFEVNwcm91bCBIYWxsIChTUFIpBQNTUFJnEAUPVGhlIEJhcm4gKEJBUk4pBQRCQVJOZxAFFVRvIEJlIEFubm91bmNlZCAoVEJBKQUDVEJBZxAFJFVuaXZlcnNpdHkgTGFib3JhdG9yeSBCdWlsZGluZyAoVUxCKQUDVUxCZxAFHlVuaXZlcnNpdHkgTGVjdHVyZSBIYWxsIChVTkxIKQUEVU5MSGcQBRdVbml2ZXJzaXR5IFZpbGxhZ2UgKFVWKQUCVVZnEAUaV2luc3RvbiBDaHVuZyBIYWxsIChDSFVORykFBUNIVU5HZ2RkAiEPEA8WBh8DBQREZXNjHwQFBUNvZGVzHwVnZA8WJwIBAgICAwIEAgUCBgIHAggCCQIKAgsCDAINAg4CDwIQAhECEgITAhQCFQIWAhcCGAIZAhoCGwIcAh0CHgIfAiACIQIiAiMCJAIlAiYCJxYnEAUlQ09FLSBTb2NpYWwgU2NpZW5jZXMgLSBFY29uLCBQb2xpIFNjaQUGRS1TLUVDZxAFJkNPRS0gU29jaWFsIFNjaWVuY2VzIC0gQW50aCwgUHN5YywgU29jBQZFLVMtQU5nEAUhQ09FLSBTb2NpYWwgU2NpZW5jZXMgLSBBZGRpdGlvbmFsBQdFLVMtQUREZxAFHkNPRS0gTmF0IFNjaSAmIE1hdGggLSBQaHlzIFNjaQUGRS1OLVBTZxAFHkNPRS0gTmF0IFNjaSAmIE1hdGggLSBCaW9sIFNjaQUGRS1OLUJTZxAFIENPRS0gTmF0IFNjaSAmIE1hdGggLSBBZGRpdGlvbmFsBQdFLU4tQUREZxAFH0NPRS0gSHVtYW5pdGllcyAtIFdvcmxkIEhpc3RvcnkFBkUtSC1XSGcQBTNDT0UtIEh1bWFuaXRpZXMgLSBGaW5lIEFydHMsIExpdCwgUGhpbCwgUmVsIFN0dWRpZXMFBkUtSC1GQWcQBRxDT0UtIEh1bWFuaXRpZXMgLSBBZGRpdGlvbmFsBQdFLUgtQUREZxAFDkNPRS0gRXRobmljaXR5BQVFLUVUSGcQBRhDT0UtIEVuZ2xpc2ggQ29tcG9zaXRpb24FBkUtRU5HTGcQBSJDTkFTLSBTb2NpYWwgU2NpZW5jZXMgLSBBZGRpdGlvbmFsBQdOLVMtQUREZxAFFUNOQVMtIFNvY2lhbCBTY2llbmNlcwUDTi1TZxAFH0NOQVMtIE5hdCBTY2kgJiBNYXRoIC0gUGh5cyBTY2kFBk4tTi1QU2cQBStDTkFTLSBOYXQgU2NpICYgTWF0aCAtIE1hdGgsIFN0YXQsIENvbXAgU2NpBQZOLU4tTUFnEAUlQ05BUy0gTmF0IFNjaSAmIE1hdGggLSBCaW9sb2dpY2FsIFNjaQUGTi1OLUJTZxAFIUNOQVMtIE5hdCBTY2kgJiBNYXRoIC0gQWRkaXRpb25hbAUHTi1OLUFERGcQBSBDTkFTLSBIdW1hbml0aWVzIC0gV29ybGQgSGlzdG9yeQUETi1XSGcQBSRDTkFTLSBIdW1hbml0aWVzIC0gUmVsaWdpb3VzIFN0dWRpZXMFBk4tSC1SU2cQBR1DTkFTLSBIdW1hbml0aWVzIC0gUGhpbG9zb3BoeQUGTi1ILVBIZxAFHENOQVMtIEh1bWFuaXRpZXMgLSBGaW5lIEFydHMFBk4tSC1GQWcQBR1DTkFTLSBIdW1hbml0aWVzIC0gQWRkaXRpb25hbAUHTi1ILUFERGcQBQ9DTkFTLSBFdGhuaWNpdHkFBU4tRVRIZxAFGUNOQVMtIEVuZ2xpc2ggQ29tcG9zaXRpb24FBk4tRU5HTGcQBSFDTkFTIC0gSHVtYW5pdGllcyAtIFdvcmxkIEhpc3RvcnkFBk4tSC1XSGcQBSpDTkFTIC0gSHVtYW5pdGllcyAtIExpdCwgUGhpbCwgUmVsIFN0dWRpZXMFBk4tSC1MVGcQBSZDSEFTUy1Tb2NpYWwgU2NpZW5jZXMgLSBFY29uLCBQb2xpIFNjaQUGSC1TLUVDZxAFJ0NIQVNTLVNvY2lhbCBTY2llbmNlcyAtIEFudGgsIFBzeWMsIFNvYwUGSC1TLUFOZxAFIkNIQVNTLVNvY2lhbCBTY2llbmNlcyAtIEFkZGl0aW9uYWwFB0gtUy1BRERnEAUgQ0hBU1MtSHVtYW5pdGllcyAtIFdvcmxkIEhpc3RvcnkFBkgtSC1XSGcQBSlDSEFTUy1IdW1hbml0aWVzIC0gTGl0LCBQaGlsLCBSZWwgU3R1ZGllcwUGSC1ILUxUZxAFHENIQVNTLUh1bWFuaXRpZXMgLSBGaW5lIEFydHMFBkgtSC1GQWcQBR1DSEFTUy1IdW1hbml0aWVzIC0gQWRkaXRpb25hbAUHSC1ILUFERGcQBSBDSEFTUy0gTmF0IFNjaSAmIE1hdGggLSBQaHlzIFNjaQUGSC1OLVBTZxAFLENIQVNTLSBOYXQgU2NpICYgTWF0aCAtIE1hdGgsIFN0YXQsIENvbXAgU2NpBQZILU4tTUFnEAUgQ0hBU1MtIE5hdCBTY2kgJiBNYXRoIC0gQmlvbCBTY2kFBkgtTi1CU2cQBSJDSEFTUy0gTmF0IFNjaSAmIE1hdGggLSBBZGRpdGlvbmFsBQdILU4tQUREZxAFEENIQVNTLSBFdGhuaWNpdHkFBUgtRVRIZxAFGkNIQVNTLSBFbmdsaXNoIENvbXBvc2l0aW9uBQZILUVOR0xnZGQCKQ8PFgIeB1Zpc2libGVoZBYOAgEPDxYCHwZoZBYCAgEPEGRkFgFmZAIDDw8WAh8GaGQWAgIBDxBkZBYBZmQCBQ8PFgIfBmhkFgICAQ8QZGQWAWZkAgcPZBYCAgEPEGRkFgFmZAIJDxBkZBYBZmQCCw8QZGQWAWZkAg0PEGRkFgFmZAIJD2QWAgIFD2QWAmYPDxYCHwIFEn4vaW1hZ2VzL21pbnVzLlBOR2RkAgsPDxYCHwZoZBYCAgUPEGRkFgFmZAIPD2QWAmYPDxYCHwIFEn4vaW1hZ2VzL21pbnVzLlBOR2RkAhMPDxYCHwZoZGQCFA8QDxYCHwZoZGQWAWZkAhYPDxYCHwZoZBYEAgEPPCsADQBkAgMPDxYCHwEFNjxoNCBpZD0nbGJsMScgY2xhc3M9J2ZhZGUnPk5vIHJlY29yZChzKSBmb3VuZCEhISE8L2g0PmRkAhoPZBYCZg8PFgIfAgUSfi9pbWFnZXMvbWludXMuUE5HZGQCHA8PFgIfBmhkFgICAQ9kFgICBw8PFgIfBmhkZAIFDw8WAh8GaGQWBgIDD2QWAmYPDxYCHwIFG34vaW1hZ2VzL3BsdXMtbmV3LXdoaXRlLlBOR2RkAgUPZBYCAgEPPCsACwBkAgkPZBYCZg8PFgIfAgUbfi9pbWFnZXMvcGx1cy1uZXctd2hpdGUuUE5HZGQCHQ8PFgIfAQUiTGFzdCBVcGRhdGUgOiA5LzIyLzIwMTYgOTo0MDoyMyBBTWRkAh8PDxYCHwEFI0N1cnJlbnQgRGF0ZSA6IDkvMjIvMjAxNiA5OjQ1OjMxIEFNZGQCIw9kFgJmD2QWCmYPDw8WBB4LQm9yZGVyV2lkdGgbAAAAAAAA8D8BAAAAHgRfIVNCAiBkFgQeB1RvcExlZnQFN2ltYWdlcy90bF8wRTU3QzAsdHJhbnNwYXJlbnRfMTV4MTVfMXB4LHNvbGlkLDBFNTdDMC5wbmceBE1vZGULKYABQm9yQmVyLldlYkNvbnRyb2xzLlJvdW5kZWRJbWFnZXMrSW1hZ2VNb2RlLCBCb3JCZXIuV2ViQ29udHJvbHMuUm91bmRlZEJveCwgVmVyc2lvbj0xLjAuMC4wLCBDdWx0dXJlPW5ldXRyYWwsIFB1YmxpY0tleVRva2VuPW51bGwDFgICAw8PFgQfAQUFTG9naW4eB1Rvb2xUaXAFKkxvZ2luIHNvIHlvdSBjYW4gdGFrZSBhZHZhbnRhZ2Ugb2YgdGhlIFNPQ2RkAgEPZBYEAgEPDxYCHwEFgwFUbyBzYXZlIGFuZCBwcmludCB5b3VyIHNlYXJjaCByZXN1bHRzLCB5b3XigJlsbCBuZWVkIHRvIGxvZy1pbi4gICBUaGlzIHdpbGwgaGVscCB3aGVuIHlvdSByZWdpc3RlciBmb3IgY2xhc3NlcyBvbiBHUk9XTC48L2I+PC9mb250PmRkAgMPDxYEHwEFYDxicj48Zm9udCBjb2xvcj0nI0Y3QTUwMCc+PGI+TG9naW4gYWNjZXNzIGlzIG5vdCBhdmFpbGFibGUgZm9yIFZpc2l0aW5nIFN0dWRlbnRzLjwvYj48L2ZvbnQ+PGJyPh8GaGRkAgIPZBYMAgMPZBYCZg8PFgIfAgUcfi9pbWFnZXMvbWludXMtbmV3LXdoaXRlLlBOR2RkAgUPDxYCHwZoZGQCCw9kFgJmDw8WAh8CBRt+L2ltYWdlcy9wbHVzLW5ldy13aGl0ZS5QTkdkZAIND2QWBAIBDzwrAA0AZAIFDw8WAh8GaGRkAhEPZBYCZg8PFgIfAgURfi9pbWFnZXMvcGx1cy5QTkdkZAITD2QWAgIBDzwrAA0AZAIEDw8WBB4JRm9yZUNvbG9yCRGUx/8fCAIEZGQCBQ9kFgJmDw8WAh8CBRF+L2ltYWdlcy9wbHVzLlBOR2RkAiUPZBYCZg9kFgICCw8PFgIfBmhkZBgEBR5fX0NvbnRyb2xzUmVxdWlyZVBvc3RCYWNrS2V5X18WBwUJY2hrYnhfbW9uBQpjaGtieF90dWVzBQljaGtieF93ZWQFCmNoa2J4X3RodXIFCWNoa2J4X2ZyaQUJY2hrYnhfc2F0BQ9jYkdyYWR1YXRlUXVhbnQFDWdyaWRfTXlTZWFyY2gPZ2QFDmdyaWRfTXlDb3Vyc2VzD2dkBQ1ncmlkX3N0dWRlbnRzD2dkdi81gI+e4tJ9c5yoJ+xagqlazdI=';

const EVENTVALIDATION = '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';

///////////////
// Utilities //
///////////////

function combineObjects(first, second) {
    var combined = {};
    for (var attrname in first) {
        combined[attrname] = first[attrname];
    }
    for (var attrname in second) {
        combined[attrname] = second[attrname];
    }
    return combined;
}

// Turns a date into a quarter code
function getQuarterCodeFromDate(date) {
    var quarter;

    // getMonth() returns 0-11 inclusive
    switch (date.getMonth()) {
        case 5:
        case 6:
        case 7:
            // June to August is summer quarter
            quarter = Quarter.SUMMER;
            break;
        case 8:
        case 9:
        case 10:
            // September to November is fall quarter
            quarter = Quarter.FALL;
            break;
        case 11:
        case 0:
        case 1:
            // December to February is winter quarter
            quarter = Quarter.WINTER;
            break;
        case 2:
        case 3:
        case 4:
            // March to May is spring quarter
            quarter = Quarter.SPRING;
    }

    return getQuarterCode(quarter, date.getFullYear());
}

// Turn a year and a quarter enum into a quarter code for the form
function getQuarterCode(quarter, year) {
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
            throw 'Invalid value quarter enum value: ' + quarter;
    }

    if (year % 100 < 10) {
        return '0' + (year % 10);
    } else {
        return year % 100;
    }
}

// Turns a 24-hour time into a time code for the form
function getTimeCode24Hour(hour) {
    return getTimeCode(hour / 24, hour % 24);
}

// Turns an AM/PM hour into a time code for the form
function getTimeCode(hour, isPM) {
    if (hour < 10) {
        hour = '0' + (hour % 10);
    }

    if (isPM) {
        return hour + 'p.m';
    } else {
        return hour + 'a.m';
    }
}

// Turns a string like 'MWF' into their corresponding fields
function getDaysOfTheWeek(daysOfWeek, params) {
    for (var day in daysOfWeek) {
        switch (day) {
            case 'M':
            case 'm':
                params.chkbx_mon = 'on';
                break;
            case 'T':
            case 't':
                params.chkbx_tues = 'on';
                break;
            case 'W':
            case 'w':
                params.chkbx_wed = 'on';
                break;
            case 'R':
            case 'r':
                params.chkbx_thur = 'on';
                break;
            case 'F':
            case 'f':
                params.chkbx_fri = 'on';
                break;
            case 'S':
            case 's':
                params.chkbx_sat = 'on';
                break;
            default:
                throw 'Invalid day: ' + day;
        }
    }
}

/////////////////////
// Form submission //
/////////////////////

const defaultPostUrl = 'http://student08.ucr.edu/em/classes/ScheduleNew/Index.aspx?browse=Browse';
const defaultPostPath = '/em/classes/ScheduleNew/Index.aspx?browse=Browse';
const defaultPostFields = Object.freeze({
    '__LASTFOCUS': '',
    '__EVENTTARGET': '',
    '__EVENTARGUMENT': '',
    '__VIEWSTATE': VIEWSTATE,
    '__SCROLLPOSITIONX': '0',
    '__SCROLLPOSITIONY': '0',
    '__EVENTVALIDATION': EVENTVALIDATION,
    '__ASYNCPOST': 'true',
    'btn_search': ' Search >>',
});

function submitRequest(params, callback) {
    params = combineObjects(defaultPostFields, params);
    $.ajax({
        type: 'POST',
        url: defaultPostUrl,
        crossDomain: true,
        data: params,
        // dataType: null,
        success: function(responseData, textStatus, jqXHR) {
            callback(responseData);
        },
        error: function(responseData, textStatus, errorThrown) {
            console.log('POST failed: ' + errorThrown);
        },
    });
}

///////////////
// Externals //
///////////////

// Builder class for creating a query
function CourseQuery() {
    this.params = combineObjects(defaultPostFields, {
        'drp_term': getQuarterCodeFromDate(new Date()),
        'drp_subjectArea': '',
        'txtbx_courseTitle': '',
        'txt_instructor': '',
        'txtbx_courseNumber': '',
        'drp_startTime': '',
        'drp_fullOpenClasses': '',
        'drp_courseRange': '',
        'drp_location': '',
        'drp_breadth': '',
        'cbGraduateQuant': false,
    });

    this.setTerm = function(quarter, year) {
        this.params['drp_term'] = getQuarterCode(quarter, year);
    };

    this.setSubjectArea = function(subjectArea) {
        this.params['drp_subjectArea'] = subjectArea[0];
    };

    this.setCourseTitle = function(courseTitle) {
        this.params['txtbx_courseTitle'] = courseTitle;
    };

    this.setInstructor = function(instructor) {
        this.params['txt_instructor'] = instructor;
    };

    this.setCourseNumber = function(courseNumber) {
        this.params['txtbx_courseNumber'] = courseNumber + '';
    };

    this.setStartTime = function(startHour) {
        this.params['drp_startTime'] = getTimeCode24Hour(startHour);
    };

    this.setCourseStatus = function(courseStatus) {
        this.params['drp_fullOpenClasses'] = courseStatus + '';
    };

    this.setCourseRange = function(courseRange) {
        this.params['drp_courseRange'] = courseRange[0];
    };

    this.setLocation = function(locationEnum) {
        this.params['drp_location'] = locationEnum[0];
    };

    this.setBreadth = function(breadthCourse) {
        this.params['drp_breadth'] = breadthCourse;
    };

    this.setGraduateQuantitativeMethod = function(value) {
        this.params['cbGraduateQuant'] = Boolean(value);
    };

    this.setDaysOfTheWeek = function(daysOfWeek) {
        getDaysOfTheWeek(daysOfWeek, this.params);
    };
}

// Class to describe one course result
function Course() {
    // TODO

    this.toString = function() {
    };
}

function getRawCourseHTML(query, callback) {
    submitRequest(query.params, callback);
}

function getCourses(query, callback) {
    getRawCourseHTML(query, function(data) {
        var courses = [];
        // TODO parse html

        callback(courses);
    });
}

if (typeof exports !== 'undefined') {
    // Enums
    exports.Quarter = Quarter;
    exports.SubjectArea = SubjectArea;
    exports.ClassType = ClassType;
    exports.CourseLocation = CourseLocation;
    exports.CourseStatus = CourseStatus;
    exports.CourseRange = CourseRange;
    exports.DayOfWeek = DayOfWeek;
    exports.BreadthCourse = BreadthCourse;

    // Objects
    exports.CourseQuery = CourseQuery;
    exports.Course = Course;

    // Functions
    exports.getRawCourseHTML = getRawCourseHTML;
    exports.getCourses = getCourses;
}

// vim: set nowrap:
