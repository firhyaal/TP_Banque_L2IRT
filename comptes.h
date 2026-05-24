#ifndef COMPTES_H
#define COMPTES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "gestion_clients.h"
#include <time.h>
#define MAX_COMPTES 500

Compte comptes[MAX_COMPTES];
extern Client clients[];
extern int nbClients;

int n = 0;
int dernierNumero = 1000;

void chargerComptes() {

    FILE *f = fopen("comptes.txt", "r");

    if (f == NULL) {
        return ;
    }

    while (fscanf(f,"%d %u %f %f %s %s %s %s %d/%d/%d",
        &comptes[n].numero,
        &comptes[n].idClient,
        &comptes[n].solde,
        &comptes[n].faciliteCaisse,
        comptes[n].type,
        comptes[n].categorie,
        comptes[n].etat,
        comptes[n].codePin,
        &comptes[n].dateCreation.jour,
        &comptes[n].dateCreation.mois,
        &comptes[n].dateCreation.annee
    ) ==11 ) {
        // mettre à jour dernierNumero au fur et à mesure
        if (comptes[n].numero > dernierNumero)
            dernierNumero = comptes[n].numero;
        n++;
    }

    fclose(f);

}

void sauvegarderComptes() {

    FILE *f = fopen("comptes.txt", "w");

    if (f == NULL) {
        printf("Erreur ouverture fichier.\n");
        return;
    }

    for (int i = 0; i < n; i++) {

        fprintf(
            f,
            "%d %u %.0f %.0f %s %s %s %s %d/%d/%d\n",
            comptes[i].numero,
            comptes[i].idClient,
            comptes[i].solde,
            comptes[i].faciliteCaisse,
            comptes[i].type,
            comptes[i].categorie,
            comptes[i].etat,
            comptes[i].codePin,
            comptes[i].dateCreation.jour,
            comptes[i].dateCreation.mois,
            comptes[i].dateCreation.annee
        );
    }

    fclose(f);
}

void creerCompte() {
    int choix;
    unsigned int idClient = 0;

    // pour identifier le client , si c'est un nouveau ou ancien client
    do {
        printf("S'agit-il d'un nouveau client ?\n");
        printf("1. Oui\n");
        printf("2. Non\n");
        printf("Veuillez saisir le numero correspondant a votre reponse : ");
        scanf("%d", &choix);
        if (choix != 1 && choix != 2)
            printf("Choix invalide, reessayez.\n");
    } while (choix != 1 && choix != 2);

    if (choix == 1) {
        enregistrer_client(clients, &nbClients);
        idClient = clients[nbClients - 1].id;

    } else {
        do {
            printf("Connaissez-vous son ID ?\n");
            printf("1. Oui\n");
            printf("2. Non\n");
            printf("Veuillez saisir le numero correspondant a votre reponse : ");
            scanf("%d", &choix);
            if (choix != 1 && choix != 2)
                printf("Choix invalide, reessayez.\n");
        } while (choix != 1 && choix != 2);

        if (choix == 1) {
            unsigned int id;
            printf("ID client : ");
            scanf("%u", &id);
            int index = rechercher_client_par_id(clients, nbClients, id);
            if (index == -1) {
                printf("Client introuvable.\n");
                return;
            }
            idClient = clients[index].id;

        } else {
            char nom[50];
            int trouve ;

            do {
                printf("Nom du client : ");
                scanf("%s", nom);
                trouve = 0;
                for (int i = 0; i < nbClients; i++) {
                    if (strcmp(clients[i].nom, nom) == 0) {
                        trouve = 1;
                    }
                }
                if (!trouve)
                    printf("Aucun client avec ce nom enregistre dans la base , reessayez.\n");
            } while (!trouve);

            rechercher_par_nom(clients, nbClients, nom);
            int index = -1;
            do{
               printf("Entrez l'ID du bon client : ");
               scanf("%u", &idClient);
               index = rechercher_client_par_id(clients, nbClients, idClient);
               if (index == -1) {
                  printf("ID invalide, reessayez.\n");
                } else if (strcmp(clients[index].nom, nom) != 0) {
                  printf("Cet ID ne correspond pas au nom %s, reessayez.\n", nom);
                  index = -1;  
                  }
            } while (index == -1);
            
        }
    }

    // pour identifier le type de compte
    do {
        printf("Type de compte :\n");
        printf("1. Epargne\n");
        printf("2. Courant\n");
        printf("Veuillez saisir le numero correspondant a votre reponse : ");
        scanf("%d", &choix);
        if (choix != 1 && choix != 2)
            printf("Choix invalide, reessayez.\n");
    } while (choix != 1 && choix != 2);

    Compte c;
    c.idClient = idClient;
    c.numero = ++dernierNumero;

    if (choix == 1)
        strcpy(c.type, "epargne");
    else
        strcpy(c.type, "courant");

    // ... la catégorie
    do {
        printf("Categorie :\n");
        printf("1. Simple\n");
        printf("2. Privilege\n");
        printf("Veuillez saisir le numero correspondant a votre reponse : ");
        scanf("%d", &choix);
        if (choix != 1 && choix != 2)
            printf("Choix invalide, reessayez.\n");
    } while (choix != 1 && choix != 2);

    if (choix == 1) {
        strcpy(c.categorie, "simple");
        c.faciliteCaisse = 0;
    } else {
        strcpy(c.categorie, "privilege");
        c.faciliteCaisse = 200000;
    }

    // règles métier solde
    if (strcmp(c.type, "epargne") == 0)
        c.solde = 10000;
    else
        c.solde = 0;

    strcpy(c.etat, "actif");

    // code PIN 
    printf(" Saisissez votre Code PIN : ");
    scanf("%s", c.codePin);
    
    // récuperer la date du jour
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    c.dateCreation.jour  = tm_info->tm_mday;
    c.dateCreation.mois  = tm_info->tm_mon + 1;
    c.dateCreation.annee = tm_info->tm_year + 1900;

    comptes[n++] = c;
    sauvegarderComptes();

    printf("Compte numero %d cree avec succes.\n", c.numero);
}
#endif