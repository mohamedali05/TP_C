#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include "TP3_amen.h"


int main()
{

    int choix;
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
                printf("\nVeuillez entrer l'id de l'etudiant: ");
                scanf("%d", &idetu);
                printf("\nVeuillez entrer le montant de la transaction: ");
                scanf("%f", &montant);
                printf("\nVeuillez entrer la description correspondant a la transaction: ");
                scanf("%s", descr);

                // Ajout de la transaction � ajouter en t�te du premier bloc
                premier_bloc->listeTransactions = ajouterTransaction(idetu, montant, descr, premier_bloc->listeTransactions);

                // Affichage du r�sultat
                printf("Le premier bloc devient alors: \n");
                print_bloc(premier_bloc);

                // Lib�ration de la m�moire pour la transaction
                //libererTransaction(trans_ajoutee);
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
            // Ajout d'un bloc avec un dateBlock correspondant � la date suivante et un idBlock en autoincr�ment
            blockchain = ajouterBlock(blockchain, date_suivante(date_du_jour));
            // Affichage de la blockchain apr�s ajout du bloc
            print_blockchain(blockchain);
            break;

        case 3:


           printf("Vous avez choisi l'option 3, qui correspond au calcul de la somme des EATCoin credites et depenses par un etudiant sur une journee. \n");
            printf("\nVeuillez entrer l'id de l'etudiant en question: ");
            scanf("%d", &idetu);
            printf("\nVeuillez entrer la date de la journee recherchee (en respectant le format de date AAAAMMJJ): ");
            scanf("%s", date_recherchee);

            printf("--------------\n") ;

            printf("La date recherchee est %s.\n", date_recherchee);
            printf("La blockchain est: \n");
            T_Block *bloc_recherche = rechercherBlocParDate(blockchain, date_recherchee);

            if (bloc_recherche != NULL) {
                // On a trouv� le bloc correspondant � la date de recherche.
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
            printf("Veuillez entrer l'id de l'etudiant en question: ");
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
            crediter(idetu, montant, descr, date_du_jour, blockchain);
            printf("\nrechargement réussi");
            break;

        case 6:

            printf("Vous avez choisi l'option 6, qui correspond au paiement d'un repas. \n");
            printf("Veuillez entrer l'id de l'etudiant en question: ");
            scanf("%d", &idetu);
            printf("\nVeuillez entrer le montant du paiement: ");
            scanf("%f", &montant);
            printf("\nVeuillez entrer la description correspondant au paiement: ");
            scanf("%s", descr);

            verif = payer(idetu, montant, descr, date_du_jour, blockchain);
            if (verif == 0)
            {
                printf("\n Ooops! Cet etudiant d'id %d n'a pas assez de EATCoin pour pouvoir effectuer le paiement.\n", idetu);
                printf("Vous devez d'abord recharger son compte, en choisissant l'option 5. Nous vous redirigeons vers le menu.\n");
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
            if (verif == 0)
            {
                printf("Oops! L'operation de transfert a echoue, car l'etudiant d'id %d, qui souhaite effectuer un transfert, n'a pas assez de EATCoin dans son compte. \n", idEtu_source);
                printf("Vous pouvez recharger son compte, en choisissant l'option 5. Nous vous redirigeons vers le menu.\n");
                continue;
            }else{
                printf("Le transfert a ete effectue avec succes!\n");
                print_blockchain(blockchain);
            }
            break;

        case 9:
            printf("Au revoir!");
            // Lib�rer la m�moire avant de sortir
            libererBlockchain(blockchain);
            exit(0); // Quitter le programme

        default:
            printf("Vous avez entre un numero invalide. Recommencez!\n");
            // Puis, on r�affiche le menu et on redemande la s�lection d'une option en cas de choix invalide
        }
    }
    viderBuffer(); // supprimer de l'entree standard le retour charriot et les eventuels caracteres supplementaires tapes par l'utilisateur

    // Lib�rer la m�moire
    libererBlockchain(blockchain);

    return 0;
}
