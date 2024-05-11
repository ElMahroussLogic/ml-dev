.PHONY: TestApp
TestApp:
	c++ -std=c++20 *.cxx -I../CoreAnimation -I../CoreGraphics \
	-I../meta/appcore/ -I/opt/homebrew/Cellar/cairo/1.18.0/include -I../meta/appcore/Headers \
	../CoreGraphics/*.cxx ../CoreAnimation/*.cxx ../meta/appcore/Sources/MacOS/*.mm \
	-framework Cocoa -framework AppKit \
	../meta/appcore/Sources/*.cxx -o CanvasExample -L/opt/homebrew/Cellar/cairo/1.18.0/lib \
	-lcairo