CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

LDFLAGS = -lm

SRC = $(wildcard src/*.c)

TARGET = raytracer

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
