CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

TARGET = ASCIIQuarium

SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:src/%.c=%.o)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)