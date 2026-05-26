#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "comptes.h"

#define SOLDE_MIN_EPARGNE 0

// prototype de rechercherCompte defini dans comptes.h
int rechercherCompte(Compte comptes[], int n, int numero);

// calculer la taxe de facilite de caisse
double calcul_taxe(double montant, Compte *c) {
    return montant * (c->faciliteCaisse / 100.0);
}

// verifier si le solde est suffisant pour debiter
int solde_suffisant(Compte *c, double montant) {
    if (strcmp(c->type, "epargne") == 0)
        return (c->solde - montant) >= SOLDE_MIN_EPARGNE;
    return (c->solde - montant) >= -(c->faciliteCaisse);
}

// crediter un compte
void crediter_compte(Compte comptes[], int nb, int numero, double montant) {
    if (montant <= 0) {
        printf("Montant invalide.\n");
        return;
    }

    int index = rechercherCompte(comptes, nb, numero);
    if (index == -1) {
        printf("Compte n%d introuvable.\n", numero);
        return;
    }

    if (strcmp(comptes[index].etat, "bloque") == 0) {
        printf("Compte bloque. Operation impossible.\n");
        return;
    }

    comptes[index].solde += montant;
    printf("Credit de %.2f FCFA effectue. Nouveau solde : %.2f FCFA\n",
        montant, comptes[index].solde);
}

// debiter un compte
void debiter_compte(Compte comptes[], int nb, int numero, double montant) {
    if (montant <= 0) {
        printf("Montant invalide.\n");
        return;
    }

    int index = rechercherCompte(comptes, nb, numero);
    if (index == -1) {
        printf("Compte n%d introuvable.\n", numero);
        return;
    }

    if (strcmp(comptes[index].etat, "bloque") == 0) {
        printf("Compte bloque. Operation impossible.\n");
        return;
    }

    if (!solde_suffisant(&comptes[index], montant)) {
        printf("Solde insuffisant. Disponible : %.2f FCFA\n",
            comptes[index].solde + comptes[index].faciliteCaisse);
        return;
    }

    double taxe = 0.0;
    double depassement = montant - comptes[index].solde;

    if (strcmp(comptes[index].type, "courant") == 0 &&
        strcmp(comptes[index].categorie, "privilege") == 0) {
        if (depassement > 0)
            taxe = calcul_taxe(depassement, &comptes[index]);
    }

    comptes[index].solde -= (montant + taxe);

    if (taxe > 0)
        printf("Taxe facilite appliquee : %.2f FCFA\n", taxe);
    printf("Debit de %.2f FCFA effectue. Nouveau solde : %.2f FCFA\n",
        montant, comptes[index].solde);
}

#endif