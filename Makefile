src   = src/main.cc src/render.cc src/fs.cc src/util.cc
hdr   = src/level.hh src/render.hh src/fs.hh src/util.hh
out   = bin/coingame
flags = -s -lSDL2 -lSDL2_image -lSDL2_ttf -lstdc++ -o

build: $(src) $(hdr)
	mkdir -p bin
	$(CC) $(src) $(flags) $(out)

windows: $(src) $(hdr)
	mkdir -p bin
	x86_64-w64-mingw32-g++ -s $(src) -o $(out) -I./mingw/include -L./mingw/lib -mwindows mingw/bin/*.dll
