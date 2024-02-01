build/debug/output: build/object/main.o 
	g++  build/object/main.o -I inc -o build/debug/output  -lSDL2 -lSDL2_image

build/object/main.o: src/main.cpp
	g++ -std=c++20 -c -Wall -Wextra -g -L/sharedDrive/Project/Snakev2/inc src/main.cpp 
	mv main.o build/object

build/object/linked_list.o: src/linked_list.cpp inc/linked_list.hpp
	g++ -std=c++20 -c -Wall -Wextra -g src/linked_list.cpp -L/sharedDrive/Project/Snakev2/inc
	mv linked_list.o build/object


run:
	pwd
	./build/debug/output

clean: 
	rm build/object/*.o build/debug/output

new:
	mkdir src inc res build build/debug build/object


debug:
	gdb ./build/debug/output


