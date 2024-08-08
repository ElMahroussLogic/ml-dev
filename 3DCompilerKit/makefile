FLAGS=-I../ -fPIC -I./Private -shared -L../FoundationKit -lFoundation
CC=x86_64-w64-mingw32-g++.exe
OUT=lib3DCompiler.dll

.PHONY: build-lib
build-lib:
	$(CC) $(wildcard *.cxx) $(FLAGS) -o $(OUT)
	@echo "=> OK."
