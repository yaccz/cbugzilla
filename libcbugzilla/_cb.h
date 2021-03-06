#ifndef CB__CB_H
#define CB__CB_H

#include <libcbugzilla/string.h>

#define CB_USED __attribute__ ((used))

struct cb_s {
	cb_string_t url;
	cb_string_t http_log_f;
	cb_string_t cookiejar_f;
	cb_string_t auth_user;
	cb_string_t auth_pass;
	int verify_peer;
	int verify_host;

	/* *** */

	cb_string_t response;
	CURL *curl;
	int curl_verbose;
	FILE *http_log;
	CURLcode res;
	int (*log_response)(cb_t cb, char *name);
	int (*curl_perform)(cb_t cb);

	double total_time;

	int (*destroy)(cb_t cgb);
	int (*get_records_count)(cb_t cb, const char *namedcmd, int *count);
};

#endif /* CB__CB_H */
