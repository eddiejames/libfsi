#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "fsi.h"

int main(int argc, char **argv)
{
	const char *opts = "m:rw:h";
	struct option lopts[] = {
		{ "rmw", 1, 0, 'm' },
		{ "read", 1, 0, 'd' },
		{ "write", 1, 0, 's' },
		{ "help", 0, 0, 'h' },
		{ 0, 0, 0, 0 }
	};
	uint32_t reg;
	int fd;
	int rc;
	int i;

	if (argc < 2)
		return -1;

	fd = open(argv[1], O_RDWR);
	if (fd < 0)
		return -1;

	for (i = 0; i < 4; ++i) {
		rc = fsi_mbox_reg_read(fd, i, &reg);
		if (rc) {
			fprintf(stderr, "read error\n");
			goto out;
		}

		fprintf(stdout, "reg%d: %08x\n", i, reg);
	}

out:
	close(fd);
	return rc;
}
