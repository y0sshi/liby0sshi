#include <y0sshi/pspl.hpp>

namespace y0sshi {
	pspl::pspl() {
		printf("openning /dev/uio0...\n");
		open_device("/dev/uio0");
		map_address();
		printf("done !!\n");
	}

	pspl::pspl(const char *dev) {
		printf("openning %s...\n", dev);
		open_device(dev);
		map_address();
		printf("done !!\n");
	}

	pspl::pspl(std::string dev) {
		printf("openning %s...\n", dev.c_str());
		open_device(dev.c_str());
		map_address();
		printf("done !!\n");
	}

	pspl::~pspl() {
		printf("free device...\n");
		free_device();
		printf("done !!\n");
	}

	bool pspl::open_device(const char *dev) {
		if ((uiofd = open(dev, O_RDWR | O_SYNC)) < 0) {
			perror("open");
			return false;
		}
		return true;
	}

	bool pspl::map_address() {
		reg = (unsigned int *)mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, uiofd, 0);
		if (reg == MAP_FAILED) {
			perror("cannot mmap");
			close(uiofd);
			return false;
		}
		return true;
	}

	void pspl::free_device() {
		munmap((void*)reg, 0x1000);
		close(uiofd);
	}

	unsigned int pspl::read_reg(int addr) {
		return reg[addr];
	}

	void pspl::write_reg(int addr, int value) {
		reg[addr] = value;
	}

	unsigned int pspl::read(int addr) {
		write_reg(READ_ADDR, addr);
		return read_reg(3);
	}

	void pspl::write(int addr, int value) {
		write_reg(WRITE_ADDR  , addr);  // set addr
		write_reg(WRITE_ENABLE, 0x1);   // enable
		write_reg(WRITE_VALUE , value); // write value to register
		write_reg(WRITE_ENABLE, 0x0);   // enable
	}
};
