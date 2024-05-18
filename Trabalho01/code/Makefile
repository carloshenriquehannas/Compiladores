all: compile
	
compile:
	gcc -c ./src/*.c
	gcc -o tokenizer *.o  -O3
	rm *.o

clear:
	rm tokenizer a.out tokenOutput.txt

debug:
	gcc -g ./src/*.c
