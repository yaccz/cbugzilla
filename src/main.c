#include "bugzilla.c"

int main(void)
{
	CGB_t *cgb;
	cgb = CGB_new();
	BO(CGB_init(cgb))
	BO(CGBString_dup(&cgb->url, "https://bugs.gentoo.org"))
	BO(CGBString_dup(&cgb->cookiejar, "./cookiejar"))
	BO(CGB_init_curl(cgb))

	BO(CGB_bz_login(cgb))
	CGB_log_response(cgb, "bz_login");

	int records;
	BO(CGB_bz_RecordsCount_get(cgb, "python-herd", &records))
	CGB_log_response(cgb, "rec: python-herd");

	printf("Records for python-herd: %d\n", records);

	CGB_cleanup(cgb);
	return EXIT_SUCCESS;
}