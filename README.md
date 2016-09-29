## libucrcourse - The UCR Course library
An open source library to utilize the [UCR schedule of classes](http://student08.ucr.edu/em/classes/ScheduleNew/Index.aspx?browse=Browse0). It mimics the calls that the website uses to ask for course data and returns it in a simple, uniform API.

This is a C library that fetches results from the website using [cURL](https://curl.haxx.se) and returns the result of a query. Since libcurl is thread-safe and IPv6-compatible this library is as well. It is designed to be simple, portable, and efficient.

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
The APIs are located in the header file `ucrcourse.h`, which contains all the necessary symbols needed for using the library. The following functions are defined:
```c
int ucrcourse_init(void)
```
This must be called before any of the other library functions are called. Returns zero on success.

```c
void ucrcourse_cleanup(void)
```
This must be called after you have run `ucrcourse_init` but before you exit.

```c
const char *ucrcourse_strerror(int error)
```
Turns an error code into a human-readable string. The return value should not be modified. If the error is
not a library error, then `strerror` is called instead.

```c
void ucrcourse_query_init(struct course_query *query)
```
The header file provides a definition for `struct course_query`. This function should be called before using
the structure in order to populate default fields.

```c
void ucrcourse_results_destroy(struct course_results *results)
```
Upon a successful query, a `struct course_results` object is returned. You should call this function on the 
object when you are done to free any dynamically allocated memory inside.

```c
struct course_results *ucrcourse_get_courses(const struct course_query *query)
```
Takes the given query object and sends it to the server. If the query succeeds, then a `struct course_results`
object is returned. This object must be disposed of using `ucrcourse_results_destroy`.
If an error occurred, `NULL` is returned and `errno` is set to indicate the error.

```c
char *ucrcourse_get_raw(const struct course_query *query)
```
This takes a query and performs a lookup. No output interpretation or scraping is performed, and the raw
response is returned to the user. The string was created using `malloc` and can be freely modified.
If an error occurred, `NULL` is returned and `errno` is set to indicate the error.

```c
char *ucrcourse_get_html(const struct course_query *query)
```
This is similar to `ucrcourse_get_raw`, except that it extracts the HTML from the raw response. The string
is also created using `malloc` and must be freed when it is no longer in use.
If an error occurred, `NULL` is returned and `errno` is set to indicate the error.

### API Errors
When an error occurs, then the special value `errno` is set. If the error that resulted is not part of the C
standard library then a library error value is returned instead. The values are defined in `ucrcourse.h`. Each name and its meaning is listed here:
* `UCRCOURSE_ERR_OK` - (not really an error) means the operation succeeded
* `UCRCOURSE_ERR_INTERNAL` - a generic error that is returned if there is no better error to return
* `UCRCOURSE_ERR_CURL` - a generic error that is returned when libcurl encounters an issue
* `UCRCOURSE_ERR_INVALID_ARG` - an argument provided to the library is invalid
* `UCRCOURSE_ERR_CONNECT` - a connection could not be established
* `UCRCOURSE_ERR_SERVER` - the remote server was not able to respond to the query
* `UCRCOURSE_ERR_RESPONSE` - the remote server responded, but the data was malformed

### Limitations
This library does not support fetching records from before 1999. Since records are scraped from a remote sight,
if the server changes its output or goes down, this library will be nonfunctional.

