CC=g++
CC_FLAGS=-Wall -ansi
EXEC=rshell
SOURCES=$(wildcard ./src/*.cpp)
OBJECTS=$(SOURCES:./src/.cpp=.o)
MKDIR=mkdir bin

all: 
	$(MKDIR)
	$(CC) $(OBJECTS) -o bin/$(EXEC)

$(EXEC): $(OBJECTS)
	$(MKDIR)
	$(CC) $(OBJECTS) -o bin/$(EXEC)

%.o: %.cpp Object
	$(CC) -c $(CC_FLAGS) $< -o $@


clean:
	rm -f $(EXEC) $(OBJECTS)

