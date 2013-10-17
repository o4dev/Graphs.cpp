# Makefile
UNAME := $(shell uname)

# All should be first rule.
all: rebuild run

clean:
	rm -fr bin
	rm -fr obj

fix:
	mkdir bin
	mkdir obj
	cp lib/*.dll bin/

# Windows builds
graphs.exe:
	g++ src/*.cpp -o bin/graphs.exe -I include/ -L lib/ -lmingw32 -lSDLmain -lSDL -static-libstdc++ -static-libgcc -static-libg++
rebuild-win: clean fix graphs.exe
all-win: rebuild-win

# All other builds. For Linux, OSX, Unix and any other POSIX OS.
graphs:
	g++ src/**.cpp -o bin/graphs -Iinclude/ -L lib/ -lSDLmain -lSDL
rebuild: clean fix graphs
run:
	./bin/graphs

