FLAGS=-I../ -fPIC -I./Private -shared
CC=x86_64-w64-mingw32-g++.exe
OUT=libGraphics.dll

.PHONY: build-lib
build-lib:
	$(CC) $(FLAGS) $(wildcard *.cxx) -o $(OUT)
	@echo "=> OK."
