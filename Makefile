#options
INCLUDE := -I $(HOME)/include
LDFLAGS := -L $(HOME)/lib -lpthread -lm
CFLAGS := -W -Wall -g

#targets
all: server

server: main.o
	gcc -o server main.o $(LDFLAGS)

main.o: main.c
	gcc $(CFLAGS) -c main.c -I $(INCLUDE)

run:
	if [-f server]; then \
		./server; \
	else \
		echo "Error: server executable not found. Run 'make' first."; \
	fi

debug:
	gdb server

clean:
	rm -f *.o .main.c.swp server
