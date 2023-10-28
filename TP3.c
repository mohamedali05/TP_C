
#include <string.h> 
#include "TP3.h"

T_Transaction* ajouterTransaction(int idEtu, float montant, char *descr, T_Transaction *listeTransaction){
    T_Transaction* nouv_Trans = malloc(sizeof(T_Transaction)) ;
    nouv_Trans->etudiant_id =  idEtu ; 
    nouv_Trans->montant =  montant ; 
    strcpy(nouv_Trans->description, descr) ; 
    if (listeTransaction == NULL){
        return nouv_Trans ; 
    }

    T_Transaction* buffer = listeTransaction ; 
    while (buffer->Proc_trans !=NULL){
        buffer = buffer->Proc_trans ; 
    }
    buffer->Proc_trans = malloc(sizeof(T_Transaction)) ;
    buffer->Proc_trans  = nouv_Trans ; 
    return listeTransaction ; 
    
}

void afficherTransaction( T_Transaction* listeTransaction){
    while(listeTransaction != NULL){
        printf("id : %d , montant %f , description %s \n",listeTransaction->etudiant_id ,listeTransaction->montant, listeTransaction->description ) ;
         listeTransaction = listeTransaction->Proc_trans ; 
    }
}

void ajouterBlock(T_BlockChain bc){
    int id = 0 ; 
    if (bc.Prem_bloc == NULL){
        bc.Prem_bloc = malloc(sizeof(T_Block)) ; 
        bc.Prem_bloc->bloc_id = id  ; 
         
    }
    id++ ; 
    T_Block* buffer = bc.Prem_bloc  ; 
    while (buffer->bloc_suivant !=NULL){
        buffer = buffer->bloc_suivant ; 
        id++ ; 
    }
    buffer->bloc_suivant = malloc(sizeof(T_Block)) ; 
    buffer->bloc_suivant->bloc_id = id ;   
}

float totalTransactionEtudiantBlock(int idEtu, T_Block b){
    T_Transaction* buffer = b.Prem_Trans ; 
    float total = 0 ; 
    while (buffer != NULL){
        if (buffer->etudiant_id ==  idEtu){
            total = total+ buffer->montant; 
        }
        buffer = buffer->Proc_trans ; 
    }
    return total ; 
}

 
