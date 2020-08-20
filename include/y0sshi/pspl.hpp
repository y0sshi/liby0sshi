#ifndef _PSPL_H_
#define _PSPL_H_

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>

#include <string>

#define WRITE_ADDR   0
#define WRITE_VALUE  1
#define WRITE_ENABLE 2
#define READ_ADDR    3

namespace y0sshi {
	class pspl {
		private:
			unsigned int *reg;
			int uiofd;
			unsigned int read_reg(int);
			void write_reg(int, int);
			bool open_flag;
		protected:
		public:
			pspl();
			pspl(const char *);
			pspl(std::string);
			~pspl();
			bool open_device(const char *);
			bool close_device();
			unsigned int read(int);
			void write(int, int);
	};
};

#endif
