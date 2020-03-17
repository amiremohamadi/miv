miv: miv.cc editor.hh defines.hh config.hh
	g++ `pkg-config --libs ncursesw` *\.cc -o miv
clean:
	rm miv
install:
	$(miv)
	cp miv /usr/bin/miv
