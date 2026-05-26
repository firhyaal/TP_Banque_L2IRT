#ifndef JOURNAL_H
#define JOURNAL_H
#include "structures.h"

void sauvegarderComptes(Compte comptes[], int n);
void crypterPin(const char *pin, char *pinCrypte);
void enregistrer_journal(int numeroCompte, const char *typeOp, float montant, float nouveauSolde);
void afficher_historique(int numeroCompte, Compte comptes[], int nComptes, Client clients[], int nClients);

#endif





