#ifndef __INCLUDE_FICHIER_H__
#define __INCLUDE_FICHIER_H__

#include <time.h>  // Pour gérer la date
#include <stdlib.h> // Pour utiliser malloc
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

// Structure pour représenter une Transaction
typedef struct T_Transaction {
    int etudiant_id;    // Identifiant de l'étudiant
    float montant;      // Montant en EATCoin payé ou reçu
    char description[50];  // Description de la Transaction
    struct T_Transaction* Proc_trans;
} T_Transaction;

// Structure pour représenter un bloc
typedef struct T_Block {
    int bloc_id;             // Identifiant unique du bloc
    char date[9];            // Date du bloc au format AAAAMMJJ
    T_Transaction* Prem_Trans;
    struct T_Block* bloc_suivant; // Pointeur vers le bloc suivant
} T_Block;

// Structure pour représenter la BlockChain
typedef struct T_BlockChain {
    T_Block* Prem_bloc;
} T_BlockChain;

T_Transaction* ajouterTransaction(int idEtu, float montant, char* descr, T_Transaction* listeTransaction);
T_BlockChain ajouterBlock(T_BlockChain bc) ; 
float totalTransactionEtudiantBlock(int idEtu, T_Block b)  ; 

void afficherTransaction( T_Transaction* listeTransaction) ; 

#endif /* __INCLUDE_FICHIER_H__ */


