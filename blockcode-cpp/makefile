# CC = clang++ -std=c++11 -stdlib=libc++
CC = g++ -std=c++11
CFLAGS = -c -Wall
LDFLAGS =
RM = rm -f

EXECUTABLE = parseFri
SOURCES = blockcode.cpp canon.cpp bitadder.cpp parseFri.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE) clean

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	./$(EXECUTABLE)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) *.o