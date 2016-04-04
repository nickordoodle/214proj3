COMPILER = gcc
CFLAGS = -Wall -g
CFLAGS2 = -g

all: indexer 
.PHONY: all
.PHONY: clean

binary-search-tree.o: binary-search-tree.c binary-search-tree.h
	$(COMPILER) $(CFLAGS) -c binary-search-tree.c

tokenizer.o: tokenizer.c tokenizer.h
	$(COMPILER) $(CFLAGS) -c tokenizer.c

indexer.o: indexer.c indexer.h
	$(COMPILER) $(CFLAGS) -c indexer.c

indexer: indexer.o tokenizer.o binary-search-tree.o
	$(COMPILER) $(CFLAGS) -o indexer tokenizer.o indexer.o binary-search-tree.o

clean: 
	rm -f *.o indexer 
