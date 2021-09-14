
all: hello.o world.o main.o

	gcc -Wall -o main main.o world.o hello.o


hello.o: hello.c hello.h
	gcc -Wall -c -o hello.o hello.c

world.o: world.c world.h
	gcc -Wall -c -o world.o world.c

clean:
	rm -f *.o main
