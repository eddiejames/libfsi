#include <boost/asio/io_context.hpp>
#include <boost/asio/posix/stream_descriptor.hpp>

#include "fsi.h"

int main(int argc, char **argv)
{
	boost::asio::io_context io;
	boost::asio::posix::stream_descriptor desc(io);
	int fd = open("/dev/scom1", O_RDWR);
	uint32_t status;

	if (fd < 0)
		return -1;

	if (fsi_configure_scom_interrupt(fd, 0, 0x80007000)) {
		fprintf(stderr, "configure error\n");
		close(fd);
		return -1;
	}

	desc.assign(fd);
	desc.async_wait(boost::asio::posix::stream_descriptor::wait_read,
			[](const boost::system::error_code& ec) {
		if (ec)
			fprintf(stderr, "wait error: %s\n", ec.message().c_str());
		else
			fprintf(stdout, "got interrupt\n");
	});

	io.run();

	if (!fsi_get_scom_interrupt_status(fd, &status))
		fprintf(stdout, "status: %08x\n", status);
	else
		fprintf(stdout, "read error\n");

	close(fd);
	return 0;
}
