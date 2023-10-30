#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TP3_amen.h"
//TODO: À la fin du programme, les blocs de mémoire dynamiquement alloués doivent être proprement libérés.

//création et initialisation du bloc
T_Block* creerBloc(int id, char* date){
    T_Block *nouveauBloc = malloc(sizeof(T_Block));
    if (nouveauBloc != NULL) {
        // l'allocation mémoire s'est bien passée
        nouveauBloc->dateBlock = malloc(strlen(date) + 1);
        strcpy(nouveauBloc->dateBlock,date);
        nouveauBloc->idBlock = id;
        nouveauBloc->listeTransactions = NULL;
        nouveauBloc->suivant = NULL;
    }

    return nouveauBloc;
}

//création et initialisation du transaction
T_Transaction* creerTransaction(int id, float montant, char* descr) {
    T_Transaction *nouvelleTransaction = malloc(sizeof(T_Transaction));
    if (nouvelleTransaction != NULL) {
        // l'allocation mémoire s'est bien passée
        nouvelleTransaction->description = malloc(strlen(descr) + 1); // Important : malloc permet d'avoir l'espace mémoire dédié pour notre champ de structure
        strcpy(nouvelleTransaction->description,descr);
        nouvelleTransaction->idEtu = id;
        nouvelleTransaction->montant = montant;
        nouvelleTransaction->suivant = NULL;
    }

    return nouvelleTransaction;
}

// 1/ajout d'une transaction à la tete de la liste
T_Transaction* ajouterTransaction(int idEtu, float montant, char* descr, T_Transaction* listeTransaction){
    T_Transaction* trans = creerTransaction(idEtu, montant, descr);
    trans->suivant = listeTransaction;
    return trans;
}

char* date_suivante(char* date){ 
    //TODO
    //on peut simplifier en comptant 30 jours par mois
}

// 2/ajout d'un bloc en tete de blockchain 
//TODO: rajouter dans le rapport prq on a rajouté le variable date
BlockChain ajouterBlock(BlockChain bc, char* date){
    int idBlock_res; 
    //blockchain vide--> id= 0
    if(bc == NULL)idBlock_res = 0;
    //blockchain non vide-->id= bc->idBlock +1 , date 
    else idBlock_res = bc->idBlock + 1;
    T_Block* res = creerBloc(idBlock_res, date);

    //on relie le nouveau block créé au reste de la chaine(suivant=NULL si block vide, sinon, suivant= ancienne tete de la chaine)
    res->suivant = bc;
    return res;
}

// 3/Calcul de la somme des EATCoin crédités et dépenses par un étudiant sur une journée:
float totalTransactionEtudiantBlock(int idEtu, T_Block b){
    //faut-il pas séparer le montant dépensé et le montant crédité????? 
    float coin=0;
    while(b.listeTransactions != NULL){
        T_Transaction trans = *b.listeTransactions; 
        if(trans.idEtu == idEtu)coin += trans.montant;
        trans = *trans.suivant; // trans->suivant ne marche pas et je sais pas prq
    }
    return coin;
}

// 4/Calcul du solde total d'un étudiant:
float soldeEtudiant(int idEtu, BlockChain bc){
    float res = 0;
    T_Block b = *bc;
    while(bc != NULL){
        res += totalTransactionEtudiantBlock(idEtu, b);
        b = *b.suivant; // b->suivant ne marche pas et je sais pas prq
    }
    return res;
}

// 5/Rechargement du compte d'un étudiant:
void crediter(int idEtu, float montant, char* descr, char* date ,BlockChain bc){
    T_Block b = *bc;
    while(bc != NULL){
        //si, un bloc avec cette date existe déjà, on rajoute la transaction à la liste de ce block
        if(b.dateBlock == date) ajouterTransaction(idEtu, montant, descr, b.listeTransactions);
        else b = *b.suivant;
    }
    // si un bloc avec cette date n'existe pas, on crée un nouveau un bloc, on le lie à la blockchain et on ajoute la transaction à la liste de transactions de ce bloc
    BlockChain res = ajouterBlock(bc, date);
    res->listeTransactions = ajouterTransaction(idEtu, montant, descr, NULL);

}

// 6/Paiement d'un repas:
int payer(int idEtu, float montant, char* descr, char* date ,BlockChain bc){ //same thing, faut expliquer prq on a choisi de rajouter el variable date
    //le montant est-il négatif ou positif?
    if(montant>0) montant = -montant;
    float solde = soldeEtudiant(idEtu, bc);
    if(solde<montant) return 0;
    else{
        crediter(idEtu, montant, descr, date, bc);
        return 1;
    }
}

// 7/Historique d'un étudiant:
void consulter(int idEtu, BlockChain bc){
    float solde = soldeEtudiant(idEtu, bc);
    printf("le solde de l'étudiant est: %f \n", solde);
    printf("l'historique de l'étudiant:");
    int var=0; //variable qui sera condition de fin de boucle quand c égal à 5
    T_Block bloc = *bc;
        while(bc!=NULL && var<5){ //on parcourt les différents blocs à partir du dernier(soit le plus récent)
            while(bloc.listeTransactions != NULL && var<5){ //on parcourt les différents transactions associées à ce bloc à partir du dernier(soit le plus récent)
                T_Transaction trans = *bloc.listeTransactions; 
                if(trans.idEtu == idEtu){
                    var+=1;
                    printf("\n\ntransaction numéro %d \n", var);
                    printf("date: %s \n", bc->dateBlock);
                    printf("description: %s \n", trans.description);
                    printf("montant: %f \n", trans.montant);
                }
                trans = *trans.suivant; // trans->suivant ne marche pas et je sais pas prq
            }
            bc = bc->suivant;
        }
    printf("fin d'historique!");
}

// 8/Transfert de EATCoins entre deux étudiants:
int transfert(int idSource, int idDestination, float montant, char *descr, char* date,BlockChain bc){
    crediter(idDestination, montant, descr, date, bc);
    float montant_neg = -montant;
    crediter(idSource, montant_neg, descr, date, bc);
    return 1; //if it works else return 0
}

// vider buffer
void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
