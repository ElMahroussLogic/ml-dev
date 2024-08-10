FLAGS=-I../ -fPIC -I./Private -shared -LWin32 -lWin32Foundation -Wl,--subsystem=17
CC=x86_64-w64-mingw32-g++.exe
OUT=cordll.dll

.PHONY: build-lib
build-lib:
	$(CC) $(wildcard *.cxx) $(FLAGS) -o $(OUT)
	@echo "[cordll.dll] => OK."
