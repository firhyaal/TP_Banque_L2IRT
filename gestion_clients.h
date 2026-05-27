#ifndef GESTION_CLIENTS_H
#define GESTION_CLIENTS_H

#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//retourne la date courante(date du jour)
Date date_courante(void){
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    Date today;
    today.jour = tm->tm_mday;
    today.mois = tm->tm_mon + 1; // tm_mon est de 0 à 11
    today.annee = tm->tm_year + 1900; // tm_year est depuis 1900
    return today;
}

//fonction pour comparer deux dates(retourne 1 si d1 strictement antérieure à d2, sinon 0)
int date_ant(Date d1, Date d2) {
    if (d1.annee < d2.annee) return 1;
    if (d1.annee > d2.annee) return 0;
    if (d1.mois < d2.mois) return 1;
    if (d1.mois > d2.mois) return 0;
    return d1.jour < d2.jour;
}

//fonction pour sauvegarder un client(sauvegarde tous les clients dans clients.txt)
void sauvegarder_clients (Client clients[], int nbClients){
	int i;
    FILE * f = fopen("clients.txt", "w+");
    if (f == NULL)
        return;
    for ( i = 0; i < nbClients; i++){
        fprintf(f,"%d| %s| %s| %c| %d/%d/%d| %s\n",
        clients[i].id,
        clients[i].nom,
        clients[i].prenom,
        clients[i].sexe,
        clients[i].dateNaissance.jour,
        clients[i].dateNaissance.mois,
        clients[i].dateNaissance.annee,
        clients[i].telephone);
    }
    fclose(f);
}

/*fonction pour charger les clients depuis le fichier
Charge les clients depuis le fichier clients.txt et retourne le nombre de clients chargés*/
int charger_clients(Client clients[]) {
	
    FILE *f = fopen("clients.txt", "r");
    if (f == NULL) return 0;  // fichier inexistant → 0 client

    int nbClients = 0;
    while (fscanf(f, "%d| %[^|]| %[^|]| %c| %d/%d/%d| %s\n",
                  &clients[nbClients].id,
                  clients[nbClients].nom,
                  clients[nbClients].prenom,
                  &clients[nbClients].sexe,
                  &clients[nbClients].dateNaissance.jour,
                  &clients[nbClients].dateNaissance.mois,
                  &clients[nbClients].dateNaissance.annee,
                  clients[nbClients].telephone) == 8) {
        nbClients++;
    }
    fclose(f);
    return nbClients;   // retourne le nombre de clients lus
}
	
//fonction pour rechercher un client par son id(recherche par id et retourne l'indice ou -1)
int rechercher_client_par_id (Client clients[], int nbClients, unsigned int id){
	int i;
    for (i=0; i < nbClients; i++){
        if (clients[i].id == id)
            return i;
    }
    return -1;
}

//fonction pour enregistrer un client(ajoute un client et le sauvegarde)
void enregistrer_client (Client clients[], int *nbClients){
    Client nouveauClient;
    Date today = date_courante();
    int idExiste;
    printf("ID du client:");
    scanf("%d",&nouveauClient.id); 
    //Verifier que l'ID n'existe pas déjà
    idExiste = rechercher_client_par_id(clients, *nbClients, nouveauClient.id);
    if (idExiste != -1) {
        printf("Erreur : Un client avec l'ID %d existe deja.\n", nouveauClient.id);
        return;
    }
    printf("Nom :");
    scanf("%s",&nouveauClient.nom);
    printf("Prenom :");
    scanf("%s",&nouveauClient.prenom);
    printf("Sexe(M/F) :");
    scanf(" %c",&nouveauClient.sexe);
    do {
        printf("Date de naissance (jour mois annee) :");
        scanf("%d %d %d",&nouveauClient.dateNaissance.jour,&nouveauClient.dateNaissance.mois,&nouveauClient.dateNaissance.annee);
        if (!date_ant(nouveauClient.dateNaissance,today)){
            printf("La date de naissance doit etre avant la date du jour.Reessayez\n");
        }
    } while (!date_ant(nouveauClient.dateNaissance,today));
    printf("Telephone :");
    scanf("%s",nouveauClient.telephone);
    clients[*nbClients] = nouveauClient;
    (*nbClients)++;
    sauvegarder_clients(clients, *nbClients);
    printf("Enregistrement reussi\n");
}

/*fonction pour rechercher un client par son nom
retourne tous les clients portant le nom et les affiche*/
void rechercher_par_nom(Client clients[], int nbClients, char nom[]) {
	int i;
    int trouve = 0;
    for (i = 0; i < nbClients; i++) {
        if (strcmp(clients[i].nom, nom) == 0) {
            printf("ID: %d | %s %s | %c | %s\n",
                   clients[i].id, clients[i].prenom, clients[i].nom,
                   clients[i].sexe, clients[i].telephone);
            trouve = 1;
        }
    }
    if (!trouve) printf("Aucun client avec le nom %s\n", nom);
}
#endif 
