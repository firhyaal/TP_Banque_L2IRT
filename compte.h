#ifndef COMPTES_H
#define COMPTES_H

#include "structures.h"

void chargerComptes(Compte comptes[], int *n, int *dernierNumero);
void sauvegarderComptes(Compte comptes[], int n);
void initialiserCompte(Compte *c);
void creerCompte(Compte comptes[], int *n, int *dernierNumero, Client clients[], int *nbClients);
int rechercherCompte(Compte comptes[], int n, int numero);
void afficherCompte(Compte comptes[], int index) ;
void consulterCompte(Compte comptes[], int n)
void rechercherClientParNumeroCompte(Compte comptes[], int n, Client clients[], int nbClients);



#endif