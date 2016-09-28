## libucrcourse - The UCR Course library
An open source library to utilize the [UCR schedule of classes](http://student08.ucr.edu/em/classes/ScheduleNew/Index.aspx?browse=Browse0). It mimics the calls that the website uses to ask for course data and returns it in a simple, uniform API.

This is a C library that fetches results from the website using [cURL](https://curl.haxx.se) and returns the result of a query. It is designed to be simple, portable, and efficient.

Available under the [MIT License](LICENSE.md).

### Compilation
This project uses CMake as its build system. In the top level of the repository, do:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```
Compiled library artifacts should now be available for use in your applications.

### API
(TODO)

### Limitations
This library does not support fetching records from before 1999.

