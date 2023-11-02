#include <stdio.h>
#include <stdlib.h>

#define MAX_descr 100
typedef struct Transaction{
    int idEtu;
    float montant;
    char* description;
    struct Transaction *suivant;
} T_Transaction;

typedef struct Block{
    int idBlock;
    char* dateBlock; //AAAAMMJJ
    T_Transaction* listeTransactions;
    struct Block* suivant ;
} T_Block;

typedef T_Block* BlockChain;

// Cr�ation et initialisation des structures
T_Transaction *creerTransaction(int id, float montant, char *descr);
T_Block *creerBloc(int id, char* date);



// 1.	Ajout d'une transaction en t�te d'une liste de transactions :
T_Transaction *ajouterTransaction(int idEtu, float montant, char *descr, T_Transaction *listeTransaction);

T_Block *rechercherBlocParDate(BlockChain bc, char *dateRecherche) ;

// 2.	Ajout d'un bloc en t�te de la BlockChain :
BlockChain ajouterBlock(BlockChain bc, char* date); //TODO: rajouter dans le rapport prq on a rajouté le variable date

// 3.	Calcul de la somme des EATCoin cr�dit�s et d�pens�s par un �tudiant sur une journ�e :
float totalTransactionEtudiantBlock(int idEtu, T_Block b);

// 4.	Calcul du solde total d'un �tudiant:
float soldeEtudiant(int idEtu, BlockChain bc);

// 5.	Rechargement du compte d�un �tudiant :
 BlockChain crediter(int idEtu, float montant, char *descr, char* date , BlockChain bc); //TODO: rajouter dans le rapport prq on a rajouté le variable date

// 6.	Paiement d�un repas :
int payer(int idEtu, float montant, char *descr, char* date ,BlockChain bc);//TODO: rajouter dans le rapport prq on a rajouté le variable date

// 7.	Historique d�un �tudiant :
void consulter(int idEtu, BlockChain bc);

// 8.	Transfert de EATCoins entre deux �tudiants :
int transfert(int idSource, int idDestination, float montant, char *descr, char* date, BlockChain bc);

int estBissextile(int an);
char* date_suivante(char* date);

// Fonctions d'affichage det de deboggage
void print_Transc(T_Transaction* trans);
void print_premier_bloc(BlockChain bc);
void print_bloc(T_Block* bloc);
void print_blockchain(BlockChain bc);

// Fonctions de libération de la mémoire
void libererTransaction(T_Transaction* trans);
void libererBloc(T_Block* bloc);



// UTILS
void viderBuffer() ;

