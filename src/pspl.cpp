#include <y0sshi/pspl.hpp>

namespace y0sshi {
	pspl::pspl() {
		init();
	}

	pspl::pspl(const char *dev) {
		init();
		if (!open_flag_) {
			printf("openning %s...\n", dev);
			open_device(dev);
			printf("done !!\n");
		}
	}

	pspl::pspl(std::string dev) {
		init();
		if (!open_flag_) {
			printf("openning %s...\n", dev.c_str());
			open_device(dev.c_str());
			printf("done !!\n");
		}
	}

	pspl::~pspl() {
		if (open_flag_) {
			printf("close device...\n");
			close_device();
			printf("done !!\n");
		}
	}

	void pspl::init() {
		open_flag_ = false;
		mtx_w_     = false;
		mtx_r_     = false;
	}

	bool pspl::open_device(const char *dev) {
		/* open device */
		if ((uiofd_ = open(dev, O_RDWR | O_SYNC)) < 0) {
			perror("open");
			return false;
		}

		/* mmap register */
		reg_ = (unsigned int *)mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, uiofd_, 0);
		if (reg_ == MAP_FAILED) {
			perror("cannot mmap");
			close(uiofd_);
			return false;
		}

		/* change flag */
		open_flag_ = true;

		return true;
	}

	bool pspl::close_device() {
		munmap((void*)reg_, 0x1000);
		close(uiofd_);
		open_flag_ = false;

		return true;
	}

	void pspl::lock(bool& mutex) {
		while (mutex);
		mutex = true;
	}

	void pspl::unlock(bool& mutex) {
		mutex = false;
	}

	uint32_t pspl::read(uint32_t addr) {
		uint32_t value;
		lock(mtx_r_);
		value = reg_[addr];
		unlock(mtx_r_);

		return value;
	}

	void pspl::write(uint32_t addr, uint32_t value) {
		lock(mtx_w_);
		reg_[addr] = value;
		unlock(mtx_w_);

		return;
	}

};
