.PHONY: clean

whisper: whisper-server whisper-client

whisper-client: client.o

whisper-server: server.o

whisper-client whisper-server: common.o
	g++ -g -Wall -ansi -pedantic $^ -o $@

%.o: %.cpp common.hpp
	g++ -g -Wall -ansi -pedantic -c $< -o $@

clean:
	rm -f whisper-server whisper-client *.o

