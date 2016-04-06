COMPILER = gcc
CFLAGS = -Wall -g
CFLAGS2 = -g

all: indexer 
.PHONY: all
.PHONY: clean

testFile.o: testFile.c
	$(COMPILER) $(CFLAGS) -c testFile.c

testFile: testFile.o
	$(COMPILER) $(CFLAGS) -o testFile testFile.o

sorted-list.o: sorted-list.c sorted-list.h
	$(COMPILER) $(CFLAGS) -c sorted-list.c

tokenizer.o: tokenizer.c tokenizer.h
	$(COMPILER) $(CFLAGS) -c tokenizer.c

indexer.o: indexer.c indexer.h
	$(COMPILER) $(CFLAGS) -c indexer.c

indexer: indexer.o tokenizer.o sorted-list.o
	$(COMPILER) $(CFLAGS) -o indexer tokenizer.o indexer.o sorted-list.o

clean: 
	rm -f *.o indexer 
