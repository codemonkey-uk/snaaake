
src = $(wildcard src/*.cpp)
	
snaaake: $(src)
	EMCC_FAST_COMPILER=0 em++ -std=c++11 -O2 -o build/snaaake.js $(src) -I libs/geometry/ -s FULL_ES2=1
	cp src/index.html build
	cp res/* build
	
osx: $(src)
	g++ -std=c++11 -O2 -o build/SNAAAKE $(src) -I libs/geometry/\
	 -I /usr/local/Cellar/SDL/1.2.15/include/SDL/\
	 -L /usr/local/Cellar/SDL/1.2.15/lib/\
	 -lSDLmain -lSDL -framework OpenGL -framework Cocoa
	
.PHONY : clean
clean:
	rm build/*

.PHONY : install
install:
	cp build/*.* /Users/codemonkey_uk/Sites/thad.frogley.info/snaaake/