CC = gcc

SOURCE = crawler.c bag.c curl.c hashtable.c pagedir.c url.c webpage.c
OBJ = crawler.o bag.o curl.o hashtable.o pagedir.o url.o webpage.o
HEADER = crawler.h bag.h curl.h hashtable.h pagedir.h url.h webpage.h

crawler: ${OBJ} ${HEADER}
	$(CC) $(OBJ) -Wall -Wextra -Wpedantic -o crawler -lcurl

%.o: %.c $(HEADER)
	$(CC) $< -c -lcurl

clean:
	rm -rf crawler
	rm -rf *.o
