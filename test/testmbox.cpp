#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "fsi.h"

int main(int argc, char **argv)
{
	int fd = open("/dev/mbox-cfam-s1", O_RDWR);
	uint32_t reg;
	int rc;

	if (fd < 0)
		return -1;

	rc = fsi_mbox_reg_write(fd, 0, 0xabcdef12);
	if (rc) {
		fprintf(stderr, "write error\n");
		goto out;
	}

	rc = fsi_mbox_reg_rmw(fd, 0, 0x00000080, 0x00000080);
	if (rc) {
		fprintf(stderr, "rmw error\n");
		goto out;
	}

	rc = fsi_mbox_reg_read(fd, 0, &reg);
	if (rc) {
		fprintf(stderr, "read error\n");
		goto out;
	}

	fprintf(stdout, "success: %08x\n", reg);

out:
	close(fd);
	return rc;
}
