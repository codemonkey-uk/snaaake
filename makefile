
trees: src/main.cpp
	emcc -o trees.html src/main.cpp

.PHONY : clean
clean:
	rm trees.*