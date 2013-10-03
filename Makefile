steg: steg.cpp steg.hpp
	g++ -g -Wall -ansi -pedantic $< -lpthread -lX11 -o $@
