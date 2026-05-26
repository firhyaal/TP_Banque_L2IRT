#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "gestion_clients.h"

int rechercher_client_par_id(Client clients[], int nbClients, int id) {
    for (int i = 0; i < nbClients; i++) {
        if (clients[i].id == id) return i;
    }
    return -1;
}

Date date_courante(void){
    time_t t = time(NULL);
    struct tm *timeInfo = localtime(&t);
    Date today;
    today.jour = timeInfo->tm_mday;
    today.mois = timeInfo->tm_mon + 1; // tm_mon est de 0 à 11
    today.annee = timeInfo->tm_year + 1900; // tm_year est depuis 1900
    return today;
}

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


void sauvegarder_clients (Client clients[], int nbClients){
    FILE * f = fopen("clients.txt", "w");
    if (f == NULL)
        return;
    for (int i = 0; i < nbClients; i++){
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

/*fonction pour rechercher un client par son nom
retourne tous les clients portant le nom et les affiche*/
void rechercher_par_nom(Client clients[], int nbClients, char nom[]) {
    int trouve = 0;
    for (int i = 0; i < nbClients; i++) {
        if (strcmp(clients[i].nom, nom) == 0) {
            printf("ID: %d | %s %s | %c | %s\n",
                   clients[i].id, clients[i].prenom, clients[i].nom,
                   clients[i].sexe, clients[i].telephone);
            trouve = 1;
        }
    }
    if (!trouve) printf("Aucun client avec le nom %s\n", nom);
}
