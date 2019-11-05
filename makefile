miv: miv.cc editor.hh defines.hh config.hh
	g++ -lncurses miv.cc editor.cc -o miv

clean: miv
	rm miv