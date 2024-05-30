CC=c++
CCFLAGS= -std=c++20 *.cxx -I../../CoreAnimation -I../../CoreGraphics \
	-I../../meta/appcore/ -I../../meta/appcore/Headers \
	../../CoreGraphics/*.cxx ../../CoreAnimation/*.cxx ../../meta/appcore/Sources/Linux/*.cxx \
	-lcairo

.PHONY:
all: CanvasExample
	@echo "=> OK."

.PHONY: CanvasExample
CanvasExample:
	$(CC) $(CCFLAGS) ../../meta/appcore/Sources/*.cxx -o CanvasExample