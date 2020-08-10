#ifndef _PSPL_H_
#define _PSPL_H_

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>

#define WRITE_ADDR   0
#define WRITE_VALUE  1
#define WRITE_ENABLE 2
#define READ_ADDR    3

namespace y0sshi {
	class pspl {
		private:
			unsigned int *reg;
			int uiofd;
			unsigned int read_reg(int addr);
			void write_reg(int addr, int value);
		protected:
		public:
			pspl();
			~pspl();
			bool open_device();
			bool map_address();
			void free_device();
			unsigned int read(int addr);
			void write(int addr, int value);
	};
};

#endif
