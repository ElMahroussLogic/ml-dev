FLAGS=-I../ -fPIC -I./Private -shared -LWin32 -lWin32Foundation
CC=x86_64-w64-mingw32-g++.exe
OUT=libFoundation.dll

.PHONY: build-lib
build-lib:
	$(CC) $(wildcard *.cxx) $(FLAGS) -o $(OUT)
	@echo "=> OK."
