.PHONY: clean all whisper

all: whisper

whisper: whisper-server whisper-client

whisper-client: client.o

whisper-server: server.o

whisper-client whisper-server: common.o
	g++ -s -Wall -ansi -pedantic $^ -o $@

%.o: %.cpp common.hpp
	g++ -s -Wall -ansi -pedantic -c $< -o $@

clean:
	rm -f whisper-server whisper-client *.o

