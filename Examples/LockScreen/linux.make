CC=c++
CCFLAGS= -std=c++20 *.cxx -I../../ -I../../CoreAnimation -I../../CoreGraphics \
	-I../../CoreFoundation/ -I../../CoreFoundation/CoreFoundation \
	../../CoreGraphics/*.cxx ../../CoreAnimation/*.cxx ../../CoreFoundation/Sources/Linux/*.cxx \
	-I/usr/include/gtk-3.0/ -I/usr/include/glib-2.0/ -I/usr/include/glib-2.0/glib

.PHONY:
all: LockScreen
	@echo "=> OK."

.PHONY: LockScreen
LockScreen:
	$(CC) $(CCFLAGS) ../../CoreFoundation/Sources/*.cxx -o LockScreen `pkg-config --cflags --libs gtk+-3.0 cairo glib-2.0`
