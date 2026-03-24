CC = gcc
CFLAGS = -Wall -Wextra -Iincludes

SRC = src/main.c src/mp3_header.c src/mp3_frames.c src/utils.c

OUT = mp3_reader

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)