COMPILER = gcc
CFLAGS = -Wall -g
CFLAGS2 = -g

all: indexer 
.PHONY: all
.PHONY: clean

hashTable.o: hashTable.c hashTable.h
	$(COMPILER) $(CFLAGS) -c hashTable.c

indexer.o: indexer.c indexer.h
	$(COMPILER) $(CFLAGS) -c indexer.c

indexer: indexer.o hashTable.o
	$(COMPILER) $(CFLAGS) -o indexer indexer.o hashTable.o

clean: 
	rm -f *.o indexer 