#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TP3_amen.h"

int main(){
    int tmp, var = 0;
    BlockChain bc;
    T_Block b;
    char* date;
    while(var!=8){
        printf("1. Afficher la liste des blocs de la BlockChain\n");
        printf("2. Afficher toutes les transactions d’un bloc\n");
        printf("3. Afficher toutes les transactions du jour pour un étudiant\n");
        printf("4. Afficher l’historique pour un étudiant\n");
        printf("5. Créditer un compte\n");
        printf("6. Payer un repas\n");
        printf("7. Transférer des EATCoins entre deux étudiants\n");
        printf("8. quitter \n");
        scanf("%d", var);
        //choix 1
        if(var==1){
            printf("la blockchain contient les blocs suivants:");
            while(bc!=NULL){
                printf(" %d ", bc->idBlock);
                bc = bc->suivant;     
            }
        }
        //choix 2
        if(var==2){
            printf("donner l'id du bloc: ");
            scanf("%d", tmp);
            while(bc!=NULL){
                if(bc->idBlock==tmp){
                    T_Transaction* list = bc->listeTransactions;
                    while(list!=NULL){
                        printf("idEtu: %d    montant: %f   description:%s \n", list->idEtu, list->montant, list->description);
                        list = list->suivant;
                    }
                    break;
                }
                else bc = bc->suivant;
            }
            if(bc==NULL) printf("un bloc avec ce id n'existe pas");
            
        }

    }
}