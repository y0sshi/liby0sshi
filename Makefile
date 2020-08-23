################################ Set env ################################
PREFIX       = /usr
PY_BOOST     = -lboost_python38 -I/usr/include/python3.8/
PY_TARGET    = y0sshi.so
PY_SO        = $(PREFIX)/lib/python3.8/$(PY_TARGET)
LIB          = $(PREFIX)/lib/y0sshi
INCLUDE      = $(PREFIX)/include/y0sshi
LDCONF       = /etc/ld.so.conf.d/y0sshi.conf
PKGCONF      = $(PREFIX)/lib/arm-linux-gnueabihf/pkgconfig/y0sshi.pc
CFLAGS       = -I`pwd`/include
SHARED_FLAGS = -shared -fPIC $(CFLAGS)
PY_FLAGS     = $(SHARED_FLAGS) $(PY_BOOST) -DPYTHON
INSTALL_ALL  = $(LIB)/liby0sshi_pspl.so $(INCLUDE)/pspl.hpp \
	$(PY_SO) $(LDCONF) $(PKGCONF) $(PREFIX)/include/y0sshi.hpp
#########################################################################


default: all


################################# Build #################################
all: lib/liby0sshi_pspl.so lib/$(PY_TARGET)

lib/$(PY_TARGET): src/pyy0sshi.cpp lib/pspl.o
	g++ src/pyy0sshi.cpp lib/pspl.o -o lib/$(PY_TARGET) $(PY_FLAGS)

lib/pspl.o: src/pspl.cpp
	mkdir -p lib
	g++ -c src/pspl.cpp -o lib/pspl.o $(CFLAGS)

lib/liby0sshi_pspl.so: src/pspl.cpp
	mkdir -p lib
	g++ $(SHARED_FLAGS) src/pspl.cpp -o lib/liby0sshi_pspl.so

#########################################################################


################################ Install ################################
install: $(INSTALL_ALL)

uninstall:
	rm -f $(INSTALL_ALL)
	ldconfig

$(PY_SO): lib/$(PY_TARGET)
	mkdir -p $(PREFIX)/lib/python3.8
	cp lib/$(PY_TARGET) $(PY_SO)

$(LIB)/liby0sshi_pspl.so: lib/liby0sshi_pspl.so
	mkdir -p $(LIB)
	cp lib/liby0sshi_pspl.so $(LIB)/liby0sshi_pspl.so

$(PREFIX)/include/y0sshi.hpp:
	cp include/y0sshi.hpp $(PREFIX)/include/y0sshi.hpp

$(INCLUDE)/pspl.hpp: include/y0sshi/pspl.hpp
	mkdir -p $(PREFIX)/include/y0sshi
	cp include/y0sshi/pspl.hpp $(INCLUDE)/pspl.hpp

$(LDCONF): config/y0sshi.conf
	mkdir -p /etc/ld.so.conf.d/
	cp config/y0sshi.conf $(LDCONF)
	ldconfig

$(PKGCONF): config/y0sshi.pc
	mkdir -p $(PREFIX)/lib/arm-linux-gnueabihf/pkgconfig/
	cp config/y0sshi.pc $(PKGCONF)
#########################################################################


################################# Clean #################################
clean:
	rm -rf lib sample/main

#########################################################################
