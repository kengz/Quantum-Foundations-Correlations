CC = g++ -std=c++11
CFLAGS = -c -Wall
LDFLAGS =
RM = rm -f

EXECUTABLE = canon
SOURCES = bitadder.cpp blockcode.cpp canon.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE) clean

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	./$(EXECUTABLE)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) *.o