CC=c++
CCFLAGS= -std=c++20 *.cxx -I../../CoreAnimation -I../../ -I../../CoreGraphics \
	-I../../CoreFoundation/ -I../../CoreFoundation/Headers \
	../../CoreGraphics/*.cxx ../../CoreAnimation/*.cxx ../../CoreFoundation/Sources/Linux/*.cxx \
	-lcairo

.PHONY:
all: GenerateQR
	@echo "=> OK."

.PHONY: GenerateQR
GenerateQR:
	$(CC) $(CCFLAGS) ../../CoreFoundation/Sources/*.cxx -o GenerateQR
