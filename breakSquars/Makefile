build/debug/output: build/object/main.o build/object/Brick.o build/object/gWindow.o build/object/circle.o 
	g++ -I inc/ build/object/*.o -o build/debug/output  -lSDL2 -lSDL2_image

build/object/main.o: src/main.cpp 
	g++ -c -Wall -Wextra -g src/main.cpp -I inc/
	mv main.o build/object

build/object/Brick.o: src/Brick.cpp inc/Brick.hpp inc/line.hpp
	g++ -c -Wall -Wextra -g src/Brick.cpp -I inc/ 
	mv Brick.o build/object

build/object/gWindow.o: src/gWindow.cpp inc/gWindow.hpp
	g++ -c -Wall -Wextra -g src/gWindow.cpp -I inc/
	mv gWindow.o build/object

run:
	pwd
	./build/debug/output

clean: 
	rm build/object/*.o build/debug/output

new:
	mkdir src inc res build build/debug build/object
	code src/main.cpp


debug:
	gdb ./build/debug/output


