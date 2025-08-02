CC = g++
CFLAGS = -std=c++17 -Wall
TARGET = programa
HEADERS = all_headers.h
SOURCES = all_src.cc

$(TARGET): $(SOURCES:.cc=.o)
		$(CC) $(CFLAGS) $^ -o $@

%.o: %.cc $(HEADERS)
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f *.o $(TARGET)