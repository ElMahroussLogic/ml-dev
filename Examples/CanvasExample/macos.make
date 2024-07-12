CC=c++
CCFLAGS= -std=c++20 *.cxx -I../../CoreAnimation -I../../ -I../../CoreGraphics \
	-I../../CoreFoundation/ -I/opt/homebrew/Cellar/cairo/1.18.0/include -I../../CoreFoundation/Headers \
	../../CoreGraphics/*.cxx ../../CoreAnimation/*.cxx ../../CoreFoundation/Sources/MacOS/*.mm \
	-framework Cocoa -framework AppKit -L/opt/homebrew/Cellar/cairo/1.18.0/lib \
	-lcairo

.PHONY:
all: CanvasExample
	@echo "=> OK."

.PHONY: CanvasExample
CanvasExample:
	$(CC) $(CCFLAGS) ../../CoreFoundation/Sources/*.cxx -o CanvasExample
