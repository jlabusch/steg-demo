.PHONY: clean all whisper steg torrent

TORRENT=libtorrent-rasterbar-0.16.12

all: whisper steg torrent

whisper steg:
	make -C $@ all

torrent:
	test -d $(TORRENT) || tar -zxf $(TORRENT).tar.gz
	cd $(TORRENT) && ./configure --enable-logging=verbose --enable-examples && make
	ln -sf $(TORRENT)/examples/simple_client .

clean:
	make -C whisper clean
	make -C steg clean
	rm -f simple_client
	rm -fr $(TORRENT) lsd.log libtorrent_logs*

