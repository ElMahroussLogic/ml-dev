FLAGS=-I../ -fPIC -I./Private -shared -Wl,--subsystem=17
CC=x86_64-w64-mingw32-g++.exe
OUT=2gxdll.dll

.PHONY: build-lib
build-lib:
	$(CC) $(FLAGS) $(wildcard *.cxx) -o $(OUT)
	@echo "[2gxdll.dll] => OK."
