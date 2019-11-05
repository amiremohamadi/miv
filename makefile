miv: miv.cc editor.hh defines.hh config.hh
	g++ -lncurses miv.cc editor.cc file.cc -o miv

clean:
	rm miv