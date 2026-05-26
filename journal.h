#ifndef JOURNAL_H
#define JOURNAL_H
#include "structures.h"
 //#include "comptes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CLE_XOR 0x5A
#define max_essai_pin 3
#define pinLen 10
/* Gestion de l'authentification PIN
    - D'abord faire une recherche du compte par N°
    - Authentifier en passant par la fonction 
        . L'objectif est de vérifier si le pin enter 
          est égale à celle enregistré au début: 
           verifierPin()
*/

void sauvegarderComptes(Compte comptes[], int n);
int rechercherCompte(Compte comptes[], int n, int numero);
Date date_courante(void);

// Fonction de cryptage XOR:
void crypterPin(const char *pin, char *pinCrypte) {
    int i;
    for (i = 0; pin[i] != '\0'; i++)
        pinCrypte[i] = (char)(pin[i] ^ CLE_XOR);
    pinCrypte[i] = '\0';
}
//Fonction de vérification du Pin
int verifierPin(const char *saisie, const char *stocke) {
    char temp[pinLen];
    crypterPin(saisie, temp);
    return (strcmp(temp, stocke) == 0);
}

int authentification(Compte comptes[],int index, int nbComptes) {
    char saisie[pinLen];
    int  essai;
 
    for (essai = 0; essai < max_essai_pin; essai++) {
        printf("Entrer votre PIN: ");
        scanf("%s",saisie);
        if (verifierPin(saisie, comptes[index].codePin)) {
            return 1;
        }
        printf("Code PIN incorrect. Essai %d/%d.\n", essai + 1, max_essai_pin);
    }
    /* Blocage du compte */
    strcpy(comptes[index].etat, "bloque");
    sauvegarderComptes(comptes,nbComptes);
    printf("Compte bloque apres %d essais incorrects.\n", max_essai_pin);
    return 0;
}
// on enregistre dans le journal l'opération faite
void enregistrer_journal(int numeroCompte, const char *typeOp, float montant, float nouveauSolde) {
    FILE *f = fopen("journal.txt", "a");
    if (f == NULL) return;

    Date d = date_courante();

    fprintf(f, "%d/%d/%d | %d | %s | %.2f | %.2f\n",
        d.jour,
        d.mois,
        d.annee,
        numeroCompte,
        typeOp,
        montant,
        nouveauSolde
    );

    fclose(f);
}

// affichage de l'historique du compte 
void afficher_historique(int numeroCompte, Compte comptes[], int nComptes, Client clients[], int nClients) {

    // Trouver le compte
    int index = rechercherCompte(comptes, nComptes, numeroCompte);
    if (index == -1) {
        printf("Compte introuvable.\n");
        return;
    }

    // Trouver client
    unsigned int idClient = comptes[index].idClient;
    int i;
    for (i = 0; i < nClients; i++) {
        if (clients[i].id == idClient)
            break;
    }

    printf("\n========== HISTORIQUE COMPTE ==========\n");

    if (i < nClients) {
        printf("Compte N°: %d\n", numeroCompte);
        printf("Proprietaire: %s %s\n\n",
            clients[i].prenom,
            clients[i].nom
        );
    }

    FILE *f = fopen("journal.txt", "r");
    if (f == NULL) {
        printf("Aucun historique disponible.\n");
        return;
    }

    Date d;
    int num;
    char type[15];
    float montant, solde;

    while (fscanf(f, "%d/%d/%d | %d | %s | %f | %f",
        &d.jour,
        &d.mois,
        &d.annee,
        &num,
        type,
        &montant,
        &solde) == 7) {

        if (num == numeroCompte) {
            printf("%02d/%02d/%04d | %s | %.2f | Solde: %.2f\n",
                d.jour, d.mois, d.annee,
                type,
                montant,
                solde
            );
        }
    }

    fclose(f);
}


#endif