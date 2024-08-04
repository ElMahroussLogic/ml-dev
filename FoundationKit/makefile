.PHONY: build-lib
build-lib:
	g++ $(wildcard *.cxx) -I../ -fPIC -I./Private -shared -o libFoundation.lib -LLinux/ -lLinuxFoundation
	@echo "=> OK."
