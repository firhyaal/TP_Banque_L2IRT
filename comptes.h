#ifndef COMPTES_H
#define COMPTES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "gestion_clients.h"
#include <time.h>
//#include "journal.h"

// Charger depuis comptes.txt dans le tableau de compte

void chargerComptes(Compte comptes[], int *n, int *dernierNumero) {

    FILE *f = fopen("comptes.txt", "r");

    if (f == NULL) return;

    while (fscanf(f, "%d|%u|%f|%f|%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d\n",
        &comptes[*n].numero,
        &comptes[*n].idClient,
        &comptes[*n].solde,
        &comptes[*n].faciliteCaisse,
        comptes[*n].type,
        comptes[*n].categorie,
        comptes[*n].etat,
        comptes[*n].codePin,
        &comptes[*n].dateCreation.jour,
        &comptes[*n].dateCreation.mois,
        &comptes[*n].dateCreation.annee) == 11) {

        if (comptes[*n].numero > *dernierNumero)
            *dernierNumero = comptes[*n].numero;

        (*n)++;
    }
    fclose(f);
}

// Sauvegarder dans comptes.txt

void sauvegarderComptes(Compte comptes[], int n) {

    FILE *f = fopen("comptes.txt", "w");

    if (f == NULL) return;

    for (int i = 0; i < n; i++) {
        fprintf(f, "%d|%u|%.0f|%.0f|%s|%s|%s|%s|%d/%d/%d\n",
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
            comptes[i].dateCreation.annee);
    }
    fclose(f);
}

// initialiser l'etat et la date de creation du compte

void initialiserCompte(Compte *c) {
    strcpy(c->etat, "actif");
    time_t t = time(NULL); // récupere le temps actuel du systeme
    struct tm *tm_info = localtime(&t); // transforme ça en j.m.a
    c->dateCreation.jour  = tm_info->tm_mday;
    c->dateCreation.mois  = tm_info->tm_mon + 1;
    c->dateCreation.annee = tm_info->tm_year + 1900;
}

// Creation d'un compte

void creerCompte(Compte comptes[], int *n, int *dernierNumero, Client clients[], int *nbClients) {

    int choix;
    unsigned int idClient ;

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
        int nouv_client ;
        int client_prec ;
        do{ //  passer par là car enreg_client ne retourne rien
            client_prec = *nbClients;
            enregistrer_client(clients, nbClients);

            if (*nbClients == client_prec) {
                printf("Echec de la creation du client.\n");
                nouv_client = 0; //return;
            }else 
            nouv_client = 1;
        }while (nouv_client ==0);

        idClient = clients[*nbClients - 1].id;

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
            int index;
            do{
                printf("ID client : ");
                scanf("%u", &id);
                index = rechercher_client_par_id(clients, *nbClients, id);
                if (index == -1) {
                    printf("Client introuvable.Veuillez saisir le bon ID\n");
                
                }
            }while (index ==-1);

        idClient = clients[index].id;

        } 
        else {
            char nom[50];
            int trouve;

            do { // mm probleme que pour enreg_client par id
                printf("Nom du client : ");
                scanf("%s", nom);
                trouve = 0;
                for (int i = 0; i < *nbClients; i++) {
                    if (strcmp(clients[i].nom, nom) == 0)
                        trouve = 1;
                }
                if (!trouve)
                    printf("Aucun client avec ce nom enregistre dans la base, reessayez.\n");
            } while (!trouve);

            rechercher_par_nom(clients, *nbClients, nom);

            int index = -1;
            do {
                printf("Entrez l'ID du bon client : ");
                scanf("%u", &idClient);
                index = rechercher_client_par_id(clients, *nbClients, idClient);
                if (index == -1)
                    printf("ID invalide, reessayez.\n");
                else if (strcmp(clients[index].nom, nom) != 0) {
                    printf("Cet ID ne correspond pas au nom %s, reessayez.\n", nom);
                    index = -1;
                }
            } while (index == -1);
        }
    }

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
    c.numero = ++(*dernierNumero);

    if (choix == 1)
        strcpy(c.type, "epargne");
    else
        strcpy(c.type, "courant");

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

    if (strcmp(c.type, "epargne") == 0)
        c.solde = 10000;
    else
        c.solde = 0;

    initialiserCompte(&c);

    char pinBrut[10];
    printf("Saisissez votre Code PIN : ");
    scanf("%s", pinBrut);
    crypterPin(pinBrut, c.codePin); 

    
    comptes[(*n)++] = c;
    sauvegarderComptes(comptes, *n);

    printf("Compte numero %d cree avec succes.\n", c.numero);
}


// Rechercher un compte par son num de compte

int rechercherCompte(Compte comptes[], int n, int numero) {

    for (int i = 0; i < n; i++) {
        if (comptes[i].numero == numero)
            return i;
    }
    return -1;
}

// Afficher les infos relatives à un compte

void afficherCompte(Compte comptes[], int index) {
    printf("\n INFORMATIONS DU COMPTE \n");
    printf("Numero  : %d\n", comptes[index].numero);
    printf("ID client : %u\n", comptes[index].idClient);
    printf("Type : %s\n", comptes[index].type);
    printf("Categorie : %s\n", comptes[index].categorie);
    printf("Solde : %.0f FCFA\n", comptes[index].solde);
    printf("Facilite : %.0f FCFA\n", comptes[index].faciliteCaisse);
    printf("Etat : %s\n", comptes[index].etat);
    printf("Date creation: %d/%d/%d\n",comptes[index].dateCreation.jour,comptes[index].dateCreation.mois,comptes[index].dateCreation.annee);       
}


// Consulter un compte

void consulterCompte(Compte comptes[], int n) {
    int numero;
    int index;
    do{ 
        printf("Numero du compte : ");
        scanf("%d", &numero);

        index = rechercherCompte(comptes, n, numero);
        if (index == -1) {
            printf("Ce compte est introuvable.\n");
        
        } 
    }while (index == -1);

    if (!authentification(comptes,index, n )) return;

    afficherCompte(comptes, index);
}

// Rechercher client par son num de compte & afficher ses infos personnelles

void rechercherClientParNumeroCompte(Compte comptes[], int n, Client clients[], int nbClients) {
    int numero;
    int index ;
    do{
        printf("Numero du compte : ");
        scanf("%d", &numero);

        index = rechercherCompte(comptes, n, numero);
        if (index == -1) {
        printf("Compte introuvable.\n");
        
        }
    } while (index == -1);

    unsigned int idClient = comptes[index].idClient;
    int trouve = 0;
    for (int i = 0; i < nbClients; i++) {
        if (clients[i].id == idClient) {
            printf("\nINFORMATIONS PERSONNELLES DU CLIENT ASSOCIE AU COMPTE %d\n", numero);
            printf("ID : %u\n", clients[i].id);
            printf("Nom : %s\n", clients[i].nom);
            printf("Prenom : %s\n", clients[i].prenom);
            printf("Sexe : %c\n", clients[i].sexe);
            printf("Date de naissance: %d/%d/%d\n",clients[i].dateNaissance.jour,clients[i].dateNaissance.mois,clients[i].dateNaissance.annee);
            printf("Telephone: %s\n", clients[i].telephone);
            trouve = 1;
            break;
        }
    }
    if (!trouve)
        printf("Aucun client associe a ce compte.\n");
}

#endif