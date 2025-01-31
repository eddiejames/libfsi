#include <errno.h>
#include <poll.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <time.h>

#include "fsi.h"
#include "uapi/fsi.h"

int fsi_configure_scom_interrupt(int fd, uint32_t comp_mask, uint32_t true_mask)
{
	struct scom_interrupt si;
	int rc;

	si.comp_mask = comp_mask;
	si.true_mask = true_mask;

	rc = ioctl(fd, FSI_SCOM_SET_INTERRUPT, &si);
	if (rc < 0)
		return -errno;

	return 0;
}

int fsi_get_scom_interrupt_status(int fd, uint32_t *status)
{
	int rc;

	rc = ioctl(fd, FSI_SCOM_GET_INTERRUPT, status);
	if (rc < 0)
		return -errno;

	return 0;
}

int fsi_mbox_reg_read(int fd, uint32_t reg, uint32_t *data)
{
	struct mbox_access ma;
	int rc;

	ma.reg = reg;
	rc = ioctl(fd, FSI_MBOX_READ, &ma);
	if (rc < 0)
		return -errno;

	*data = ma.data;
	return 0;
}

int fsi_mbox_reg_rmw(int fd, uint32_t reg, uint32_t data, uint32_t mask)
{
	struct mbox_access_rmw ma;
	int rc;

	ma.mask = mask;
	ma.access.reg = reg;
	ma.access.data = data;
	rc = ioctl(fd, FSI_MBOX_RMW, &ma);
	if (rc < 0)
		return -errno;

	return 0;
}

int fsi_mbox_reg_write(int fd, uint32_t reg, uint32_t data)
{
	struct mbox_access ma;
	int rc;

	ma.reg = reg;
	ma.data = data;
	rc = ioctl(fd, FSI_MBOX_WRITE, &ma);
	if (rc < 0)
		return -errno;

	return 0;
}

