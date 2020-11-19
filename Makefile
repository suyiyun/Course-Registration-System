main : dlist.o student.o menu.o main.o
		gcc	-o $@ $^
		rm *.o -rf
%.o	: %.c
		gcc -c *.c -Wall

