CC=gcc
CFLAGS= -Wall -Wextra -Werror -std=c99 -pedantic
FILES = httpServer.c common.c

make: $(FILES)
	$(CC) $(CFLAGS) -o httpServer $(FILES)
