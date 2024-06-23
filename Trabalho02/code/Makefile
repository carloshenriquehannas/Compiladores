all: compile
	
compile:
	gcc -c ./src/*.c
	gcc -o parser *.o  -O3
	rm *.o

clear:
	rm parser a.out output.txt

debug:
	gcc -g ./src/*.c
