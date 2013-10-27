.PHONY: clean all

all: steg

steg: steg.cpp steg.hpp
	g++ -s -Wall -ansi -pedantic $< -o $@ -lm -lpthread -lX11

clean:
	rm -f steg *.o

