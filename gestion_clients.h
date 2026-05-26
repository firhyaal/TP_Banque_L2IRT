#ifndef GESTION_CLIENTS_H
#define GESTION_CLIENTS_H

#include "structures.h"

Date date_courante(void);
int date_ant(Date d1, Date d2);
void sauvegarder_clients (Client clients[], int nbClients);


void enregistrer_client (Client clients[], int *nbClients);
int rechercher_client_par_id(Client clients[], int nbClients, int id);

void rechercher_par_nom(Client clients[], int nbClients, char nom[]);
Compte* rechercher_compte(Compte comptes[],int nb, int numero);
   
#endif 