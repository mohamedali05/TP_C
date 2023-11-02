#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "TP3_amen.h"


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


void print_Transc(T_Transaction* trans){
    if (trans == NULL)
        return;

    printf("id_Etu : %d \n" ,  trans->idEtu) ;
    printf("montant : %f \n" ,  trans->montant) ;
    printf("description : %s \n \n" ,  trans->description) ;

    while (trans->suivant != NULL){
        trans = trans->suivant ;
        printf("id_Etu : %d \n" ,  trans->idEtu) ;
        printf("montant : %f \n" ,  trans->montant) ;
        printf("description : %s \n \n" ,  trans->description) ;

    }
}


void print_premier_bloc(BlockChain bc)
{
    if (bc == NULL)
        return;

    T_Block* premier_bloc = bc;

    printf("id_premier_bloc : %d \n" , premier_bloc->idBlock) ;
    printf("date_premier_bloc : %s \n" , premier_bloc->dateBlock) ;
    print_Transc(premier_bloc->listeTransactions);
}

void print_bloc(T_Block* bloc)
{
    if (bloc ==  NULL)
        return;

    printf("id_bloc : %d \n" , bloc->idBlock) ;
    printf("date_bloc : %s \n" , bloc->dateBlock);
    printf("Voici la liste de transactions du bloc: \n");
    print_Transc(bloc->listeTransactions);
}

void print_blockchain(BlockChain bc)
{
    if (bc == NULL)
        return;

    T_Block *bloc = bc;
    print_bloc(bloc);

    while (bloc->suivant != NULL)
    {
        bloc = bloc->suivant;
        print_bloc(bloc);
    }
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


T_Block *rechercherBlocParDate(BlockChain bc, char *dateRecherche) {
    T_Block *currentBlock = bc;
    while (currentBlock != NULL) {
        if (strcmp(currentBlock->dateBlock, dateRecherche) == 0) {
            // La date du bloc correspond à la date de recherche.
            printf("Bloc trouve\n");
            return currentBlock;
        }
        currentBlock = currentBlock->suivant;
    }

    // Le bloc avec la date recherchée n'a pas été trouvé.
    printf("Le bloc n'a pas été retrouvé");
    return NULL;
}

int estBissextile(int an) {
    return (an % 4 == 0 && (an % 100 != 0 || an % 400 == 0));
}
char* date_suivante(char* date){

    char date_courante[9];
    char sous_chaine_an[5], sous_chaine_mois[3], sous_chaine_jour[3];
    unsigned int an, mois, jour;
    unsigned int nouv_an, nouv_mois, nouv_jour;

    // Récupérer la valeur de date (string) contenue à l'adresse passée en paramètre
    strncpy(date_courante, date, 8);
    date_courante[8] = '\0';


    // Extraire l'an (4 premiers caractères)
    strncpy(sous_chaine_an, date_courante, 4);
    sous_chaine_an[4] = '\0';

    // Extraire le mois (2 caractères suivants)
    strncpy(sous_chaine_mois, date_courante + 4, 2);
    sous_chaine_mois[2] = '\0';

    // Extraire le jour (2 derniers caractères)
    strncpy(sous_chaine_jour, date_courante + 6, 2);
    sous_chaine_jour[2] = '\0';

    // Convertir les sous_chaînes en entiers
    an = atoi(sous_chaine_an);
    mois = atoi(sous_chaine_mois);
    jour = atoi(sous_chaine_jour);

    printf("An: %04d\nMois: %02d\nJour: %02d\n", an, mois, jour); // simple test

    int jours_par_mois[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Vérifier si  l'année est bissextile
    if (estBissextile(an))
        jours_par_mois[1] = 29; // si l'année est bissextile, février a 29 jours au lieu de 28 jours


    // Vérifier si le format de date est cohérent
    if (mois >= 1 && mois <= 12 && jour >= 1 && jour <= jours_par_mois[mois - 1])
    {
        // Incrémenter le jour seulement
        if (jour < jours_par_mois[mois - 1])
        {
            nouv_jour = jour + 1;
            nouv_mois = mois;
            nouv_an = an;
        }
        // Passer au mois suivant
        else if (mois < 12)
        {
            nouv_jour = 1;
            nouv_mois = mois + 1;
            nouv_an = an;
        }
        // Passer à l'année suivante si le jour courant est le 31 décembre
        else
        {
            nouv_jour = 1;
            nouv_mois = 1;
            nouv_an = an + 1;
        }

        // Convertir les entiers en chaînes de caractères et concaténer le tout pour obtenir la date suivante
        snprintf(date, 9, "%04d%02d%02d", nouv_an, nouv_mois, nouv_jour);

    }
    else
    {
        date[0] = '\0';
    }

    return date;
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
    // je pense qu'il suffit de donner la somme mais on peut, ken thib Amen (tests sur le signe de trans->montant)

    float coin = 0.0;
    T_Transaction* trans = b.listeTransactions; // on accède au bloc et pas à son pointeur pour récupérer la liste des transaction (voir type T_Block)

    while (trans != NULL) {
        if (trans->idEtu == idEtu) {
            coin += trans->montant;
        }
        trans = trans->suivant; // trans->suivant marche pour moi
    }

    return coin;
}

// 4/Calcul du solde total d'un étudiant:
float soldeEtudiant(int idEtu, BlockChain bc){
    float res = 0.0;
    T_Block* bloc = bc; // on initialise le bloc avec la tête de la blockchain (qui est un pointeur)

    while (bloc != NULL) {
        res += totalTransactionEtudiantBlock(idEtu, *bloc);
        bloc = bloc->suivant; // on passe au bloc suivant
    }

    return res;
}

// 5/Rechargement du compte d'un étudiant:
BlockChain crediter(int idEtu, float montant, char* descr, char* date, BlockChain bc){

    T_Block* b = bc;
    while(b != NULL){
        //si un bloc avec cette date existe déjà, on rajoute la transaction à la liste de ce block
        if(strcmp(b->dateBlock, date) == 0){
            b->listeTransactions = ajouterTransaction(idEtu, montant, descr, b->listeTransactions);
            return ; // sortir de la fonction après avoir ajouté la transaction
        }
        else b = b->suivant;
    }
    // si un bloc avec cette date n'existe pas, on crée un nouveau un bloc, on le lie à la blockchain et on ajoute la transaction à la liste de transactions de ce bloc
    bc = ajouterBlock(bc, date);

    bc->listeTransactions = ajouterTransaction(idEtu, montant, descr, bc->listeTransactions);
    return bc ;
}

// 6/Paiement d'un repas:
int payer(int idEtu, float montant, char* descr, char* date, BlockChain* bc){ //same thing, faut expliquer prq on a choisi de rajouter el variable date
    //le montant est-il négatif ou positif?
    if (montant < 0) // si l'utilisateur a saisi une valeur négative, on change le signe
        montant = -montant;
    float solde = soldeEtudiant(idEtu, *bc);
    if (solde < montant) // si l'etudiant n'a pas assez d'EATCoin pour payer
        return 0;
    else
    {
        if (montant > 0)
            montant = -montant;

        (*bc) = crediter(idEtu, montant, descr, date, *bc);
        return 1; // retourne 1 si le paiement a bien ete effectue avec succes
    }
}

// 7/Historique d'un étudiant:
void consulter(int idEtu, BlockChain bc){
    float solde = soldeEtudiant(idEtu, bc);
    printf("Le solde de l'etudiant est: %f\n", solde);
    printf("L'historique de l'etudiant:\n");
    int var = 0; // variable qui sera condition de fin de boucle quand c égal à 5
    T_Block* bloc = bc;

    while (bloc != NULL && var < 5) {
        T_Transaction* trans = bloc->listeTransactions;
        while (trans != NULL && var < 5) {
            if (trans->idEtu == idEtu) {
                var += 1;
                printf("\n\nTransaction numero %d\n", var);
                printf("Date: %s\n", bloc->dateBlock);
                printf("Description: %s\n", trans->description);
                printf("Montant: %f\n", trans->montant);
            }
            trans = trans->suivant;
        }
        bloc = bloc->suivant;
    }

    printf("Fin d'historique!\n");
}

// 8/Transfert de EATCoins entre deux étudiants:
int transfert(int idSource, int idDestination, float montant, char *descr, char* date,BlockChain bc){
    float solde_etudiantSource = soldeEtudiant(idSource, bc);
    if (solde_etudiantSource < montant)
        return 0;
    else
    {
        bc = crediter(idDestination, montant, descr, date, bc);
        float montant_neg = -montant;
        bc = crediter(idSource, montant_neg, descr, date, bc);
        return 1;
    }
}

// vider buffer
void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

void libererTransaction(T_Transaction* trans) {
    if (trans == NULL)
        return;

    // Libération de la mémoire pour la description
    free(trans->description);
    trans->description = NULL;

    // Libération de la mémoire pour la transaction elle-même
    free(trans);
}

void libererBloc(T_Block* bloc) {
    if (bloc == NULL)
        return;

    // Libération de la mémoire pour la date du bloc
    free(bloc->dateBlock);
    bloc->dateBlock = NULL;

    // Libération de la mémoire pour la liste de transactions (appel de la fonction de libération pour chaque transaction)
    T_Transaction* transactionCourante = bloc->listeTransactions;
    while (transactionCourante != NULL) {
        T_Transaction* transactionSuivante = transactionCourante->suivant;
        libererTransaction(transactionCourante);
        transactionCourante = transactionSuivante;
    }

    // Libération de la mémoire pour le bloc lui-même
    free(bloc);
}

void libererBlockchain (BlockChain bc)
{
    if (bc == NULL)
        return;
    T_Block* bloc = bc;
    while (bloc != NULL)
    {
        libererBloc(bloc);
        bloc = bloc->suivant;
    }
}
