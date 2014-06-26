
src = $(wildcard src/*.cpp)
	
snaaake: $(src)
	em++ -std=c++11 -O2 -o build/snaaake.html $(src) -I libs/geometry/ -s FULL_ES2=1
	cp src/index.html build

.PHONY : clean
clean:
	rm build/*

.PHONE : install
install:
	cp build/*.* /Users/codemonkey_uk/Sites/thad.frogley.info/snaaake/