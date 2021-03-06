#ifndef _PSPL_H_
#define _PSPL_H_

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdint.h>

#include <string>

namespace y0sshi {
	class pspl {
		private:
			uint32_t *reg_;
			int uiofd_;
			bool open_flag_;
			bool mtx_w_;
			bool mtx_r_;
			void lock(bool&);
			void unlock(bool&);
		protected:
		public:
			pspl();
			pspl(const char *);
			pspl(std::string);
			~pspl();
			void init();
			bool open_device(const char *);
			bool close_device();
			uint32_t read(uint32_t);
			void write(uint32_t, uint32_t);
	};
};

#endif
