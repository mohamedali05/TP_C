

# si on tape "make" sans préciser de cible, make va chercher à
# construire la *première* cible du Makefile.
default: all

all: main 

##########################################
# compilation des programmes

Main: Main.c
	gcc -g -Wall -Werror -o rebours   Main.c 



clean:
	rm -f *.o  main
