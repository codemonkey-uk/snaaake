
src = src/CApp.cpp src/CApp_OnCleanup.cpp src/CApp_OnEvent.cpp src/CApp_OnInit.cpp src/CApp_OnLoop.cpp src/CApp_OnRender.cpp
src += src/shape.cpp src/star.cpp src/colour.cpp
	
trees: $(src)
	emcc -o trees.html $(src) -I src/geometry/ -s FULL_ES2=1

.PHONY : clean
clean:
	rm trees.*