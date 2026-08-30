CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -Wno-format-zero-length

TARGET = ASCIIQuarium

OBJS = ASCIIQuarium.o terminal.o text_chunk.o animation.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

ASCIIQuarium.o: ASCIIQuarium.c
	$(CC) $(CFLAGS) -c ASCIIQuarium.c -o ASCIIQuarium.o

terminal.o: terminal.c
	$(CC) $(CFLAGS) -c terminal.c -o terminal.o

text_chunk.o: text_chunk.c
	$(CC) $(CFLAGS) -c text_chunk.c -o text_chunk.o

animation.o: animation.c
	$(CC) $(CFLAGS) -c animation.c -o animation.o

clean:
	rm -f $(OBJS) $(TARGET)