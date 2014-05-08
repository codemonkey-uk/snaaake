
src = $(wildcard src/*.cpp)
	
trees: $(src)
	em++ -std=c++11 -O2 -o trees.html $(src) -I libs/geometry/ -s FULL_ES2=1

.PHONY : clean
clean:
	rm trees.*

.PHONE : install
install:
	cp trees.* /Users/codemonkey_uk/Sites/thad.frogley.info/lols