#include "../src/bugzilla.c"
#include "../src/bugzilla_parser.c"
#include "../src/htmltidy.c"
#include "../src/curl.c"
#include "../src/string.c"

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#define EXIT_TESTFAIL 2

int test_recordsCount() {
	long unsigned count;
	int fd;
	void *response;
	struct stat sb;
	char file[] = "./test/response/namedcmd.html";

	fd = open(file, O_RDONLY);
	if (fd == -1)
		{ perror("open"); return EXIT_FAILURE; }

	if (fstat(fd, &sb) == -1)
		{ perror("fstat"); return EXIT_FAILURE; }

	response = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if(response == MAP_FAILED)
		{ perror("mmap"); return EXIT_FAILURE; }

	TidyDoc tdoc;
	if(0 != cb_tidy_loadBuf(&tdoc, response, sb.st_size))
		return EXIT_FAILURE;

	if(0 != cb_parse_recordsCount(tdoc, tidyGetBody(tdoc), &count))
		return EXIT_FAILURE;

	if(count != 420)
		return EXIT_TESTFAIL;

	return EXIT_SUCCESS;
}

int main(void) {
	int rc;
	switch(rc = test_recordsCount()) {
		case EXIT_FAILURE:
			printf("recordsCount INTERFAILED\n");
			break;
		case EXIT_TESTFAIL:
			printf("recordsCount FAILED\n");
			break;
		case EXIT_SUCCESS:
			printf("recordsCount OK\n");
			break;
		default:
			printf("recordsCount UNDEFINED\n");
	}
	return rc;
}
