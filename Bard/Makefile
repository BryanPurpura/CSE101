
bard: bard_main.o bard_functs.o
	gcc bard_main.o bard_functs.o -o bard

bard_main.o: bard_main.c
	gcc -c bard_main.c

bard_functs.o: bard_functs.c bard.h
	gcc -c bard_functs.c

clean:
	rm *.o bard


