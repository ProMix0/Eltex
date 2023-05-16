SOURCES=main.c f1.c f2.c
OBJECTS=$(SOURCES:.c=.o)

compile: f1.o f2.o main.o

.c.o:
	gcc -fPIC -c $< -o $@

static: clean $(OBJECTS)
	ar rc libf.a f1.o f2.o
	ranlib libf.a
	gcc main.o -L. -lf -o main
	./main

dynamic: clean $(OBJECTS)
	gcc -shared -o libf.so f1.o f2.o
	gcc main.o -L. -lf -o main
	LD_LIBRARY_PATH=`pwd` ./main

clean:
	rm -f *.o *.a *.so main

