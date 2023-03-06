.PHONY: clean make build

build:
	g++ -Wall main.cpp -o run
run: build
	xboard -fcp "./run"
clean:
	rm -f run
