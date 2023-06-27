
all: main.o deck.o
	gcc $^ -o main

%.o: %.c
	gcc -c $^

clean:
	rm *.o main