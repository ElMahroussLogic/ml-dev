CC=c++
CCFLAGS= -std=c++20 *.cxx -I../../CoreAnimation -I../../CoreGraphics \
	-I../../CoreFoundation/ -I../../CoreFoundation/Headers \
	../../CoreGraphics/*.cxx ../../CoreAnimation/*.cxx ../../CoreFoundation/Sources/Linux/*.cxx \
	-lcairo

.PHONY:
all: CanvasExample
	@echo "=> OK."

.PHONY: CanvasExample
CanvasExample:
	$(CC) $(CCFLAGS) ../../CoreFoundation/Sources/*.cxx -o CanvasExample