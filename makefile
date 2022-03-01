CC=gcc
CFLAGS= -Wall -Wextra -Werror -std=c99 -pedantic
FILES = httpServer.c common.c httpRequest.c httpParser.c Data_Structures/Dictionary/dictionary.c Data_Structures/LinkedList/linkedList.c

make: $(FILES)
	$(CC) $(CFLAGS) -o httpServer $(FILES)
