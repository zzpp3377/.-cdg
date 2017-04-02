
test : list.o test.o
	gcc -o $@ $^
list.o : list.c list.h
	gcc -o $@ -c $<
test.o : test.c
	gcc -o $@ -c $<
clean :
	rm test test.o list.o


