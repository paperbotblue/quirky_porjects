build/debug/output: build/object/main.o build/object/gWindow.o build/object/gShapes.o
	g++ -I include/ build/object/*.o -o build/debug/output  -lSDL2 -lSDL2_image

build/object/main.o: src/main.cpp
	g++ -c -Wall -Wextra -g src/main.cpp -I include/ 
	mv main.o build/object

build/object/gWindow.o: src/gWindow.cpp include/gWindow.hpp
	g++ -c -Wall -Wextra -g src/gWindow.cpp -I include/ 
	mv gWindow.o build/object

build/object/gShapes.o: src/gShapes.cpp include/gShapes.hpp
	g++ -c -Wall -Wextra -g src/gShapes.cpp -I include/ 
	mv gShapes.o build/object

run:
	./build/debug/output

clean: 
	rm build/object/*.o build/debug/output

debug:
	gdb ./build/debug/output


