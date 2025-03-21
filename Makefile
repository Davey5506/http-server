#options
INCLUDE := -I ~/include
LDFLAGS := -L ~/lib -lpthread -lm
CFLAGS := -W -Wall -g

#targets
all: server

server: main.o
	gcc -o server main.o $(LDFLAGS)

main.o: main.c
	gcc $(CFLAGS) -c main.c -I ~/include

run:
	./server

debug:
	gdb server

clean:
	rm -f *.o .main.c.swp server
