build:main

main: main.o
main.o: main.c

run:
	./main
clean:
	rm -f *.o
