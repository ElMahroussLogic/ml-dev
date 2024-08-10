FLAGS=-I../ -fPIC -I./Private -shared -L../FoundationKit -lFoundation -Wl,--subsystem=17
CC=x86_64-w64-mingw32-g++.exe
OUT=animdll.dll

.PHONY: all
all:
	$(CC) $(wildcard *.cxx) $(FLAGS) -o $(OUT)
	@echo "[animdll.dll] => OK."
