CC=g++
IFILES=-I./inc
DFLAGS=-lSDL2 -lSDL2_image
CFLAGS=-Wall -Wextra -g 
BINARY=build/debug/output

CFILES=$(foreach D,./src,$(wildcard $(D)/*.cpp))
HFILES=$(foreach D,./inc,$(wildcard $(D)/*.hpp))
OFILES=build/object/*.o

$(BINARY):  $(OFILES) $(CFILES) $(HFILES) 
	$(CC)  -o $(BINARY) $(CFLAGS) $(IFILES)  $(OFILES) $(DFLAGS)
		
build/object/%.o:src/%.cpp
	$(CC) $(CFLAGS) -c $^ $(DFLAGS)
	mv *.o build/object/

src/%.cpp:


run:
	./build/debug/output

clean: 
	rm build/object/*.o build/debug/output

new:
	mkdir src inc res build build/debug build/object

new_run:


debug:
	gdb ./build/debug/output


