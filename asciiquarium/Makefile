CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
TARGET = ASCIIQuarium
 
SOURCES = $(wildcard src/*.c src/animation_object_types/*.c)
OBJECTS = $(SOURCES:src/%.c=obj/%.o)
 
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)
 
obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
 
clean:
	rm -rf obj $(TARGET)
 