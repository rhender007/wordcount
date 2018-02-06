# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=gcc
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
CFLAGS=-c -Wall

all: wordstat
	
wordstat: wordstat.o tree.o
	$(CC) wordstat.o tree.o -o wordstat	
	
wordstat.o: wordstat.c
	$(CC) $(CFLAGS) wordstat.c

tree.o: tree.c
	$(CC) $(CFLAGS) tree.c

clean:
	rm -rf *o twordstat

