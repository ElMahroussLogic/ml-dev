FLAGS=-I../ -fPIC -I./Private -shared
CC=g++
OUT=libGraphics.dll

.PHONY: build-lib
build-lib:
	$(CC) $(FLAGS) $(wildcard *.cxx) -o $(OUT)
	@echo "=> OK."
