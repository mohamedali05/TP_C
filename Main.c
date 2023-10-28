#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include "TP3.h"

 

int main(int argc, char** argv)
{
    char* source = "Bonjour";
    char destination[20];  
    strcpy(destination, source);

    printf("Source : %s\n", source);
    printf("Destination : %s\n", destination);

    T_Transaction* a = ajouterTransaction(1 , 12.5 , "ahv",NULL) ;
    ajouterTransaction(1 , 23, "Baguette",a) ; 
    ajouterTransaction(1 , 23, "Baguette",a) ;
    afficherTransaction(a) ; 

   printf("abc \n") ; 

   

    return 0;
}
