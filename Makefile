COMPILER = gcc
CFLAGS = -Wall -g
CFLAGS2 = -g

all: indexer 
.PHONY: all
.PHONY: clean


indexer.o: indexer.c indexer.h
	$(COMPILER) $(CFLAGS) -c indexer.c

indexer: indexer.o 
	$(COMPILER) $(CFLAGS) -o indexer indexer.o

clean: 
	rm -f *.o indexer 