CFLAGS=-W -Wall -g
OBJECTS=reverse.o stringlist.o

reverse: $(OBJECTS)
	gcc -o reverse $(OBJECTS)

reverse.o: reverse.c

stringlist.o: stringlist.c

clean: 
	rm -f reverse $(OBJECTS)
