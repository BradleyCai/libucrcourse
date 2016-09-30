/*
 * request.c
 *
 * Copyright (C) 2016 Ammon Smith and Bradley Cai
 * Available for use under the terms of the MIT License.
 */

#include <errno.h>
#include <stdlib.h>

#include <curl/curl.h>

#include "blob.h"
#include "params.h"
#include "request.h"
#include "string_buffer.h"
#include "ucrcourse.h"

#define POST_URL		"http://student08.ucr.edu/em/classes/ScheduleNew/Index.aspx"
#define DEFAULT_CAPACITY	4096
#define TRUE			1L

static size_t read_data(void *ptr, size_t size, size_t nmemb, void *arg)
{
	struct string_buffer *strbuf = arg;
	strbuf_append_data(strbuf, ptr, size * nmemb);
	return size * nmemb;
}

char *do_request(const struct course_query *query)
{
	CURL *curlh;
	CURLcode res;
	struct string_buffer strbuf;
	int ret;
	char *params;

	ret = strbuf_init(&strbuf, DEFAULT_CAPACITY);
	if (ret) {
		return NULL;
	}

	curlh = curl_easy_init();
	if (!curlh) {
		errno = UCRCOURSE_ERR_CURL;
		return NULL;
	}

	params = query_to_string(curlh, query);
	if (!params) {
		int errsave = errno;
		curl_easy_cleanup(curlh);
		errno = errsave;
		return NULL;
	}

	curl_easy_setopt(curlh, CURLOPT_URL, POST_URL);
	curl_easy_setopt(curlh, CURLOPT_WRITEFUNCTION, read_data);
	curl_easy_setopt(curlh, CURLOPT_WRITEDATA, (void *)&strbuf);
	curl_easy_setopt(curlh, CURLOPT_POST, TRUE);
	curl_easy_setopt(curlh, CURLOPT_POSTFIELDS, params);
	curl_easy_setopt(curlh, CURLOPT_USERAGENT, "Mozilla/5.0 libucrcourse-client");
	curl_easy_setopt(curlh, CURLOPT_ENCODING, "gzip");
	curl_easy_setopt(curlh, CURLOPT_FAILONERROR, TRUE);
#ifndef NDEBUG
	curl_easy_setopt(curlh, CURLOPT_VERBOSE, TRUE);
#endif /* NDEBUG */

	res = curl_easy_perform(curlh);
	free(params);
	curl_easy_cleanup(curlh);
	if (res != CURLE_OK) {
		switch (res) {
		case CURLE_COULDNT_RESOLVE_PROXY:
		case CURLE_COULDNT_RESOLVE_HOST:
		case CURLE_COULDNT_CONNECT:
		case CURLE_REMOTE_ACCESS_DENIED:
		case CURLE_OPERATION_TIMEDOUT:
		case CURLE_SEND_ERROR:
		case CURLE_RECV_ERROR:
			errno = UCRCOURSE_ERR_CONNECT;
			break;
		case CURLE_HTTP_RETURNED_ERROR:
			errno = UCRCOURSE_ERR_SERVER;
			break;
		default:
			errno = UCRCOURSE_ERR_CURL;
		}

		return NULL;
	}

	strbuf_append_char(&strbuf, '\0');
	return strbuf.data;
}

