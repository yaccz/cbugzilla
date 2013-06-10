#include <libcbugzilla/string.h>

void cb_string_init(cb_string_t *cgbs) {
	cgbs->mem = NULL;
	cgbs->size = 0;
	cgbs->len  = 0;
}

int cb_string_realloc(cb_string_t *s, int len) {
	int oldlen = s->len;
	s->len = len;
	if(oldlen == 0)
		s->len += 1; // count the NULL byte only firt time
	s->size = sizeof(char) * (s->len);
	s->mem = realloc(s->mem, s->size);
	if(s->mem == NULL) {
		perror("realloc");
		return EXIT_FAILURE;
	}
	if(oldlen == 0)
		memset(s->mem, 0, s->size);

	return EXIT_SUCCESS;
}

void cb_string_free(cb_string_t *s) {
	s->len = 0;
	s->size = 0;
	if(s->mem != NULL)
		free(s->mem);
	s->mem = NULL;
}

int cb_string_dup(cb_string_t *s, const char *cs) {
	cb_string_free(s);
	s->mem = strdup(cs);
	if(s->mem == NULL)
		{ perror("strdup"); return EXIT_FAILURE; }
	s->len = strlen(cs);
	s->size = s->len * sizeof(char);
	return EXIT_SUCCESS;
}
