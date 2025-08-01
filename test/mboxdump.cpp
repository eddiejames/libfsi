#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "fsi.h"

int main(int argc, char **argv)
{
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
