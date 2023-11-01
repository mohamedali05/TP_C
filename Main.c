#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include "TP3_amen.h"


int main(int argc, char** argv)
{
    int choix;

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
                int idetu;
                float montant;
                char descr[20];


                printf("\nVeuillez entrer l'id de l'etudiant: ");
                scanf("%d", &idetu);
                printf("\nVeuillez entrer le montant de la transaction: ");
                scanf("%f", &montant);
                printf("\nVeuillez entrer la description correspondant a la transaction: ");
                scanf("%s", &descr);
                ajouterTransaction(idetu, montant, &descr, transactions);
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
            printf("Vous avez choisi l'option 2, qui croorespond a l'ajout d'un bloc en tete de la BlockChain.\n");
            ajouterBlock(blockchain, &date_du_jour);
            break;

        case 3:
            int idEtu;
            char date_recherchee[9];
            float total_transactions;

            printf("Vous avez choisi l'option 3, qui correspond au calcul de la somme des EATCoin credites et depenses par un etudiant sur une journee. \n");
            printf("\nVeuillez entrer l'id de l'etudiant en question: ");
            scanf("%d", &idEtu);
            printf("\nVeuillez entrer la date de la journee recherchee (en respectant le format de date AAAAMMJJ): ");
            scanf("%s", &date_recherchee);
            T_Block *bloc_recherche = rechercherBlocParDate(blockchain, &date_recherchee);
            if (bloc_recherche != NULL) {
                // On a trouvé le bloc correspondant à la date de recherche.
                total_transactions = totalTransactionEtudiantBlock(idEtu, bloc_recherche);
                printf("La somme des EATCoin credites et depenses par l'etudiant d'id %d sur la journee %s est de %f EATCoin.\n", idEtu, date_recherchee, total_transactions);
            }
            else {
                printf("Ooops! Aucun bloc avec la date recherchee n'a ete trouve.\n");
                printf("Reessayez! Nous vous redirigeons vers le menu.\n");
                continue;
            }
            break;

        case 4:
            int idEtu;
            float solde;
            printf("Vous avez choisi l'option 4, qui correspond au calcul du solde total d'un etudiant. \n");
            printf("Veuillez enter l'id de l'etudiant en question: ");
            scanf("%d", &idEtu);
            solde = soldeEtudiant(idEtu, blockchain);
            printf("\nLe solde total de cet etudiant d'id %d est de %f EATCoin.\n", idEtu, solde);
            break;

        case 5:
            int idEtu, verif;
            float montant;
            char descr[20];
            printf("Vous avez choisi l'option 5, qui correspond au rechargement du compte d'un etudiant. \n");
            printf("Veuillez entrer l'id de l'etudiant en question: ");
            scanf("%d", &idEtu);
            printf("\nVeuillez entrer le montant du rechargement: ");
            scanf("%f", &montant);
            printf("\nVeuillez entrer la description correspondant au rechargement (ici considere comme une transaction): ");
            scanf("%s", &descr);
            crediter(idEtu, montant, &descr, &date_du_jour ,blockchain);
            break;

        case 6:
            int idEtu, verif = 1;
            float montant;
            char descr[20];

            printf("Vous avez choisi l'option 6, qui correspond au paiement d'un repas. \n");
            printf("Veuillez entrer l'id de l'etudiant en question: ");
            scanf("%d", &idEtu);
            printf("\nVeuillez entrer le montant du paiement: ");
            scanf("%f", &montant);
            printf("\nVeuillez entrer la description correspondant au paiement: ");
            scanf("%s", &descr);

            verif = payer(idEtu, montant, &descr, &date_du_jour, blockchain);
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
            int idEtu;
            printf("Vous avez choisi l'option 7, qui correspond a l'affichage de l'historique d'un etudiant. \n");
            printf("Veuillez entrer l'id de l'etudiant en question: ");
            scanf("%d", &idEtu);

            consulter(idEtu, blockchain);
            break;

        case 8:
            int idEtu_source, idEtu_destination, verif;
            float montant;
            char descr[20];
            printf("Vous avez choisi l'option 8, qui correspond au transfert de EATCoins entre deux etudiants. \n");
            printf("Veuillez entrer l'id de l'etudiant qui souhaite effectuer le transfert: ");
            scanf("%d", &idEtu_source);
            printf("\nVeuillez entrer l'id de l'etudiant qui souhaite recevoir le transfert: ");
            scanf("%d", &idEtu_destination);
            printf("\nVeuillez entrer le montant du transfert: ");
            scanf("%f", &montant);
            printf("\nVeuillez entrer la description correspondant au transfert: ");
            scanf("%s", &descr);
            verif = transfert(idEtu_source, idEtu_destination, montant, &descr, &date_du_jour, blockchain);
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
