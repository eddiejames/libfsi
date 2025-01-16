#ifndef _LIBFSI_FSI_H_
#define _LIBFSI_FSI_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int fsi_configure_scom_interrupt(int fd, uint32_t comp_mask, uint32_t true_mask);

int fsi_get_scom_interrupt_status(int fd, uint32_t *status);

int fsi_mbox_reg_read(int fd, uint32_t reg, uint32_t *data);

int fsi_mbox_reg_rmw(int fd, uint32_t reg, uint32_t data, uint32_t mask);

int fsi_mbox_reg_write(int fd, uint32_t reg, uint32_t data);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _LIBFSI_FSI_H_ */
