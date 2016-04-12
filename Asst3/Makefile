COMPILER = gcc
CFLAGS = -Wall -g
CFLAGS2 = -g

all: index 
.PHONY: all
.PHONY: clean

sorted-list.o: sorted-list.c sorted-list.h
	$(COMPILER) $(CFLAGS) -c sorted-list.c

tokenizer.o: tokenizer.c tokenizer.h
	$(COMPILER) $(CFLAGS) -c tokenizer.c

index.o: index.c index.h
	$(COMPILER) $(CFLAGS) -c index.c

index: index.o tokenizer.o sorted-list.o
	$(COMPILER) $(CFLAGS) -o index tokenizer.o index.o sorted-list.o

clean: 
	rm -f *.o file.txt index
