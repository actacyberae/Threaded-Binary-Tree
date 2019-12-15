all: main

main-valgrind: main.o lib.o TBT.o
	$(CC) main.o lib.o TBT.o -o main
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./main
	rm -rf *.o
	
main: main.o lib.o TBT.o
	$(CC) main.o lib.o TBT.o -lm -o main
	rm -rf *.o
	
lib.o: ./libs/lib.c
	$(CC) ./libs/lib.c -c ./libs/lib.c
	
TBT.o: ./libs/TBT.c
	$(CC) ./libs/TBT.c -c ./libs/TBT.c
	
insertion_main.o: main.c
	$(CC) main.c -c main.c
	
clean:
	rm -rf *.o main
