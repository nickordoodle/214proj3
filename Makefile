COMPILER = gcc
CFLAGS = -Wall -g
CFLAGS2 = -g

all: indexer 
.PHONY: all
.PHONY: clean


fileManager.o: fileManager.c fileManager.h
	$(COMPILER) $(CFLAGS) -c fileManager.c

hashTable.o: hashTable.c hashTable.h
	$(COMPILER) $(CFLAGS) -c hashTable.c

tokenizer.o: tokenizer.c tokenizer.h
	$(COMPILER) $(CFLAGS) -c tokenizer.c

indexer.o: indexer.c indexer.h
	$(COMPILER) $(CFLAGS) -c indexer.c

indexer: indexer.o hashTable.o fileManager.o tokenizer.o
	$(COMPILER) $(CFLAGS) -o indexer tokenizer.o indexer.o hashTable.o fileManager.o 

clean: 
	rm -f *.o indexer 