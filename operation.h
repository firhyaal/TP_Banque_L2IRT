#ifndef operation.h
#define operation.h

#include "structures.h"

double calcul_taxe(Compte *c, double depassement);
void solde_suffisant(Compte *c, double montant);
void crediter_compte(Compte comptes[], int nb, int numero, double montant);
void debiter_compte(Compte comptes[], int nb, int numero, double montant);
Compte* rechercher_compte(Compte comptes[], int nb, int numero);


#endif


