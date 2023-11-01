#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
//#include "TP3_amen.h"
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
            return currentBlock;
        }
        currentBlock = currentBlock->suivant;
    }

    // Le bloc avec la date recherchée n'a pas été trouvé.
    return NULL;
}

int estBissextile(int an) {
    return (an % 4 == 0 && (an % 100 != 0 || an % 400 == 0));
}
char* date_suivante(char* date){

    char* p_result = NULL;
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
        strcpy(p_result, date);
    }
    else
        date[0] = '\0';
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
    float res = 0.0;
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


int main(int argc, char** argv)
{
    T_Transaction* trans  = creerTransaction(1 , 3.2 ,"bonjour" )  ;
    trans->suivant =  creerTransaction(2, 3.2 ,"Je suis un char*" )  ;
    print_Transc(trans)  ;

    /*int choix;
    float montant ;
    float solde;
    float total_transactions;
    int idEtu_source, idEtu_destination, verif;
    char descr[20];
    char date_recherchee[9];
    int idetu;
    char date_du_jour[9] = "20231107";
    BlockChain blockchain = NULL;


    while (1){
        // Affichage du menu
        printf("Menu:\n");

        printf("\t1. Ajout d'une transaction en tete d'une liste de transactions \n");
        printf("\t2. Ajout d'un bloc en tete de la BlockChain \n");
        printf("\t3. Calcul de la somme des EATCoin credites et depenses par un etudiant sur une journee \n");
        printf("\t4. Calcul du solde total d'un etudiant \n");
        printf("\t5. Rechargement du compte d'un etudiant \n");
        printf("\t6. Paiement d'un repas \n");
        printf("\t7. Historique d'un etudiant \n");
        printf("\t8. Transfert de EATCoins entre deux etudiants \n");
        printf("\t9. Quitter \n");
        // Saisie utilisateur
        printf("Veuillez selectionner une option, qui est designee par un numero (1,2,3,4,5,6,7,8 ou 9).\n") ;
        scanf("%d",&choix);

        printf("CHOIX ; %d \n",choix);
        // Traitement de la saisie
        switch(choix){
        case 1:
            printf("Vous avez choisi l'option 1, qui correspond a l'ajout d'une transaction en tete d'une liste de transactions.\n");
            T_Block *premier_bloc = blockchain;
            if (premier_bloc != NULL)
            {
                T_Transaction *transactions = premier_bloc->listeTransactions;
                printf("\nVeuillez entrer l'id de l'etudiant: ");
                scanf("%d", &idetu);
                printf("\nVeuillez entrer le montant de la transaction: ");
                scanf("%f", &montant);
                printf("\nVeuillez entrer la description correspondant a la transaction: ");
                scanf("%s", descr);
                ajouterTransaction(idetu, montant, descr, transactions);
            }
            else
            {
                printf("Ooops! La blockchain est vide. Impossible d'effectuer l'ajout de transaction.\n");
                printf("Pour cela, il vous faudra d'abord ajouter un premier bloc en tete de la blockchain, en choisissant l'option 2.\n");
                printf("Nous vous redirigeons vers le menu.\n");
                continue;
            }
            break;

        case 2:
            printf("Vous avez choisi l'option 2, qui correspond a l'ajout d'un bloc en tete de la BlockChain.\n");
            ajouterBlock(blockchain, date_du_jour);
            break;

        case 3:


           printf("Vous avez choisi l'option 3, qui correspond au calcul de la somme des EATCoin credites et depenses par un etudiant sur une journee. \n");
            printf("\nVeuillez entrer l'id de l'etudiant en question: ");
            scanf("%d", &idetu);
            printf("\nVeuillez entrer la date de la journee recherchee (en respectant le format de date AAAAMMJJ): ");
            scanf("%s", date_recherchee);
            T_Block *bloc_recherche = rechercherBlocParDate(blockchain, date_recherchee);
            if (bloc_recherche != NULL) {
                // On a trouvé le bloc correspondant à la date de recherche.
                total_transactions = totalTransactionEtudiantBlock(idetu, *bloc_recherche);
                printf("La somme des EATCoin credites et depenses par l'etudiant d'id %d sur la journee %s est de %f EATCoin.\n", idetu, date_recherchee, total_transactions);
            }
            else {
                printf("Ooops! Aucun bloc avec la date recherchee n'a ete trouve.\n");
                printf("Reessayez! Nous vous redirigeons vers le menu.\n");
                continue;
            }
            break;


        case 4:

            printf("Vous avez choisi l'option 4, qui correspond au calcul du solde total d'un etudiant. \n");
            printf("Veuillez enter l'id de l'etudiant en question: ");
            scanf("%d", &idetu);
            solde = soldeEtudiant(idetu, blockchain);
            printf("\nLe solde total de cet etudiant d'id %d est de %f EATCoin.\n", idetu, solde);
            break;

        case 5:
            printf("Vous avez choisi l'option 5, qui correspond au rechargement du compte d'un etudiant. \n");
            printf("Veuillez entrer l'id de l'etudiant en question: ");
            scanf("%d", &idetu);
            printf("\nVeuillez entrer le montant du rechargement: ");
            scanf("%f", &montant);
            printf("\nVeuillez entrer la description correspondant au rechargement (ici considere comme une transaction): ");
            scanf("%s", descr);
            crediter(idetu, montant, descr, date_du_jour ,blockchain);
            break;

        case 6:
            verif = 1;
            printf("Vous avez choisi l'option 6, qui correspond au paiement d'un repas. \n");
            printf("Veuillez entrer l'id de l'etudiant en question: ");
            scanf("%d", &idetu);
            printf("\nVeuillez entrer le montant du paiement: ");
            scanf("%f", &montant);
            printf("\nVeuillez entrer la description correspondant au paiement: ");
            scanf("%s", descr);

            verif = payer(idetu, montant, descr, date_du_jour, blockchain);
            if (verif)
            {
                printf("Oops! L'operation a echoue... Reessayez! Nous vous redirigeons vers le menu.\n");
                continue;
            }
            else
            {
                printf("Le paiement a bien ete effectue avec succes!\n");
            }
            break;

        case 7:
            printf("Vous avez choisi l'option 7, qui correspond a l'affichage de l'historique d'un etudiant. \n");
            printf("Veuillez entrer l'id de l'etudiant en question: ");
            scanf("%d", &idetu);

            consulter(idetu, blockchain);
            break;

        case 8:

            printf("Vous avez choisi l'option 8, qui correspond au transfert de EATCoins entre deux etudiants. \n");
            printf("Veuillez entrer l'id de l'etudiant qui souhaite effectuer le transfert: ");
            scanf("%d", &idEtu_source);
            printf("\nVeuillez entrer l'id de l'etudiant qui souhaite recevoir le transfert: ");
            scanf("%d", &idEtu_destination);
            printf("\nVeuillez entrer le montant du transfert: ");
            scanf("%f", &montant);
            printf("\nVeuillez entrer la description correspondant au transfert: ");
            scanf("%s", descr);
            verif = transfert(idEtu_source, idEtu_destination, montant, descr, date_du_jour, blockchain);
            if (verif)
            {
                printf("Oops! L'operation de transfert a echoue. \n");
                printf("Ressayer! Nous vous redirigeons vers le menu.\n");
                continue;
            }
            else
                printf("Le transfert a ete effectue avec succes!\n");
            break;

        case 9:
            printf("Au revoir!");
            exit(0); // Quitter le programme

        default:
            printf("Vous avez entre un numero invalide. Recommencez!\n");
            // Puis, on réaffiche le menu et on redemande la sélection d'une option en cas de choix invalide
        }
    }

    /*char* source = "Bonjour";
    char destination[20];
    strcpy(destination, source);

    printf("Source : %s\n", source);
    printf("Destination : %s\n", destination);

    T_Transaction* a = ajouterTransaction(1 , 12.5 , "ahv",NULL) ;
    ajouterTransaction(1 , 23, "Baguette",a) ;
    ajouterTransaction(1 , 23, "Baguette",a) ;
    afficherTransaction(a) ;

   printf("abc \n") ; */



    return 0;
}
