
src = $(wildcard src/*.cpp)
	
snaaake: $(src)
	em++ -std=c++11 -O2 -o build/snaaake.html $(src) -I libs/geometry/ -s FULL_ES2=1

.PHONY : clean
clean:
	rm build/snaaake.*

.PHONE : install
install:
	cp build/snaaake.* /Users/codemonkey_uk/Sites/thad.frogley.info/snaaake/