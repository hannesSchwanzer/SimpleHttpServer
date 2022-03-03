CC=gcc
CFLAGS= -Wall -Wextra -Werror -std=c99 -pedantic
FILES = httpServer.c util/common.c httpFunctions/httpRequest.c httpFunctions/httpParser.c Data_Structures/Dictionary/dictionary.c Data_Structures/LinkedList/linkedList.c util/strfunc.c

make: $(FILES)
	$(CC) $(CFLAGS) -o httpServer $(FILES)
