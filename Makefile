.PHONY: clean all whisper steg torrent

all: whisper steg torrent

whisper steg:
	make -C $@ all

torrent:
	tar -zxf libtorrent-rasterbar-0.16.12.tar.gz
	patch -p0 < libtorrent.patch
	cd libtorrent-rasterbar-0.16.12 && ./configure && make && cd examples && make simple_client

clean:
	make -C whisper clean
	make -C steg clean
	rm -fr libtorrent-rasterbar-0.16.12

