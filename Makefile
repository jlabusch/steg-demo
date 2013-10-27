.PHONY: clean all whisper steg torrent

TORRENT=libtorrent-rasterbar-0.16.12

all: whisper steg torrent

whisper steg:
	make -C $@ all

torrent:
	test -d $(TORRENT) || tar -zxf $(TORRENT).tar.gz
	grep -q sstream $(TORRENT)/src/peer_connection.cpp || patch -p0 < libtorrent.patch
	cd $(TORRENT) && ./configure && make && cd examples && make simple_client
	ln -sf $(TORRENT)/examples/simple_client .

clean:
	make -C whisper clean
	make -C steg clean
	rm -f simple_client
	rm -fr $(TORRENT)

