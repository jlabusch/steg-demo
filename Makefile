.PHONY: dep clean


dep: bitlet

clean:
	rm -f steg
	rm -fr bitlet

steg: steg.cpp steg.hpp
	g++ -g -Wall -ansi -pedantic $< -lpthread -lX11 -o $@

bitlet:
	git clone https://github.com/bitletorg/bitlet.git
