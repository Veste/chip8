CPP=g++
RM=rm -f

CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(patsubst src/%.cpp,obj/%.o,$(CPP_FILES))
LD_FLAGS := 
CC_FLAGS := -Wall -O2

default: all

all: obj bin bin/chip8

debug: CC_FLAGS += -D DEBUG
debug: all

bin:
	mkdir bin

bin/chip8: $(OBJ_FILES)
	$(CPP) -o $@ $^ $(LD_FLAGS)

obj:
	mkdir obj

obj/%.o: src/%.cpp
	$(CPP) $(CC_FLAGS) -c -o $@ $<

clean:
	$(RM) bin/chip8 obj/*.o

