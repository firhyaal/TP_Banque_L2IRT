#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "gestion_clients.h"
#include "operations.h"
#include "comptes.h"
#include "journal.h"

void afficherMenu(void);
void afficher_titre_encadre(char titre[]);

int main() {
    int choix = 0;
    int idRecherche;
    Client tabClients[100];
    int nbClients=0;
    int numeroSaisi;
    double montantSaisi;
    Compte tabCompte[100];
    int nbComptes=0;
    int dernierNumero = 1000;
    //Compte mesComptes[100];

    nbClients = charger_clients(tabClients);
   chargerComptes(tabCompte, &nbComptes,&dernierNumero);

    do {
        afficherMenu();
        
        printf("Votre choix : ");
        
        // Sécurité anti-plantage si quelqu'un saisit une lettre
        if (scanf("%d", &choix) != 1) {
            printf("\n[Erreur] Saisie invalide ! Veuillez entrer un chiffre entre 1 et 7.\n");
            while (getchar() != '\n'); 
            choix=-1;
        }

        int index ;
        int num;
        

        switch (choix) {
            case 1:
                printf("\n--- [Option 1] Ouverture de compte bancaire ---\n");
                system("pause");
                // Connexion avec le travail de Falonne et Christia
                //ouvrir_compte(); 

                creerCompte(tabCompte,&nbComptes,&dernierNumero,tabClients,&nbClients);
                break;
                
            case 2:
                printf("\n--- [Option 2] Credit (Depot / Versement d'argent) ---\n");
                printf("Numero du compte : ");
                scanf("%d", &numeroSaisi);
                printf("Montant a crediter : ");
                scanf("%lf", &montantSaisi);     

                // Connexion avec le travail de Firhyaal
                //effectuer_versement();
                crediter_compte(tabCompte, nbComptes, numeroSaisi, montantSaisi);

                 system("pause");   
                break;
                
            case 3:
                printf("\n--- [Option 3] Debit (Retrait d'argent) ---\n");
                 // 1. Demander le numéro de compte
                printf("Entrez le numero de compte : ");
                scanf("%d", &numeroSaisi);
    
                // 2. Demander le montant
                printf("Entrez le montant a debiter : ");
                scanf("%lf", &montantSaisi); // %lf pour un double
    
                // 3. Appel de la fonction avec les variables remplies
                // Assure-toi que 'tabComptes' et 'nbComptes' sont bien définis dans ton main
                debiter_compte(tabCompte, nbComptes,numeroSaisi,montantSaisi);
                system("pause");

                // Connexion avec le travail de Firhyaal
                //effectuer_retrait();

                break;
                
            case 4:
              printf("\nEntrez le numero de compte a rechercher : ");
              debiter_compte(tabCompte, nbComptes, numeroSaisi, montantSaisi);
              scanf("%d", &num);

             // Appeler la fonction avec les arguments nécessaires
               index = rechercherCompte(tabCompte, nbComptes, numeroSaisi);

             if (index != -1) {
             printf("Compte trouve ! Solde : %.2f\n", tabCompte[index].solde);
             } else {
             printf("Erreur : Compte introuvable.\n");
             }
                printf("\n--- [Option 4] Consultation de compte ---\n");
                system("pause");
                // Connexion avec le travail de Falonne ou Jeff
                //  index =rechercherCompte(tabCompte, nbComptes, numeroSaisi);
                break;
                
            case 5:
                printf("\n--- [Option 5] Recherche d'un client ---\n");
            
                printf("Entrez l'ID du client a rechercher : ");
                scanf("%d", &idRecherche);

                index = rechercher_client_par_id(tabClients, nbClients, idRecherche);

                // 3. Afficher le résultat
               if (index != -1) {
              printf("Client trouve a l'index %d.\n", index);
              // Tu peux ajouter ici l'affichage des détails du client si tu veux
              } else {
              printf("Client introuvable.\n");
               system("pause");
              }
             break;
                
            case 6:
                printf("\n--- [Option 6] Affichage de l'historique (Journal) ---\n");
                printf("Entrez le numero de compte : ");
            
                scanf("%d", &num);

                 // 1. Recherche du compte pour vérifier qu'il existe
                 int index = rechercherCompte(tabCompte, nbComptes, num);

                if (index != -1) {
                // 2. Appel de la fonction d'affichage (supposée exister dans ton projet)
                //afficher_historique(c); 

                afficherCompte(tabCompte,index);

                } else {
                printf("Erreur : Compte introuvable.\n");
                }
    
                system("pause");
                break;
                
            case 7:
                printf("\n===================================================\n");
                printf(" Fermeture du systeme bancaire. Au revoir !\n");
                printf("===================================================\n");
                break;
                
            default:
                printf("\n[Attention] Option inconnue ! Choisis un chiffre entre 1 et 7.\n\n");
        }
    } while (choix != 7);

    return 0;
}


// Fonction d'affichage du menu principal
void afficherMenu() {
    afficher_titre_encadre("SYSTEME DE GESTION BANCAIRE L2-IRT");
    printf("1. Creer un nouveau compte bancaire\n");
    printf("2. Crediter un compte (Versement)\n");
    printf("3. Debiter un compte (Retrait)\n");
    printf("4. Consulter le solde d'un compte\n");
    printf("5. Rechercher un client\n");
    printf("6. Afficher l'historique des operations (Journal)\n");
    printf("7. Quitter l'application\n");

    
}




void afficher_titre_encadre(char titre[]) {
    int longueur = strlen(titre);
    int i;

// 1. Ligne supérieure (+ suivi de tirets adaptés, puis +)
    printf("\n+");
    for (i = 0; i < longueur + 2; i++) { // +2 pour couvrir les 2 espaces autour du texte
        printf("-");
    }
    printf("+\n");

    // 2. Ligne du milieu (| un espace, le texte, un espace, |)
    printf("| %s |\n", titre);

    // 3. Ligne inférieure (+ suivi de tirets adaptés, puis +)
    printf("+");
    for (i = 0; i < longueur + 2; i++) {
        printf("-");
    }
    printf("+\n\n");
}



