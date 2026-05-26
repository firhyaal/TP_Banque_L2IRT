#include <stdio.h>
#include <string.h>
#include "structures.h"
#include "operation.h"

// 1. Calcul de taxe : renvoie un montant calculé
double calcul_taxe(Compte *c, double montant) {
    if (strcmp(c->categorie, "PRIVILEGE") == 0) {
        return montant * 0.05;
    }
    return 0.0;
}

// 2. Vérification solde : renvoie 1 (Vrai) ou 0 (Faux)
int solde_suffisant(Compte *c, double montant) {
    if (c == NULL) return 0;

    if (strcmp(c->type, "epargne") == 0) {
        if ((c->solde - montant) >= solde_min_epargne) return 1;
    }
    else if (strcmp(c->type, "courant") == 0) {
        if ((c->solde - montant) >= -(c->faciliteCaisse)) return 1;
    }
    return 0;
}
void debiter_compte(Compte comptes[], int nb, int numero, double montant) {
    if (montant <= 0) {
        printf("Erreur : Montant invalide.\n");
        return;
    }

    // 1. Recherche obligatoire AVANT toute utilisation de 'c'
    Compte *c = rechercher_compte(comptes, nb, numero);

    // 2. Vérification de sécurité
    if (c == NULL) {
        printf("Erreur : Compte n°%d introuvable.\n", numero);
        return;
    }

    // 3. Vérification de l'état
    if (strcmp(c->etat, "bloqué") == 0) {
        printf("Erreur : Compte bloqué.\n");
        return;
    }

    // 4. Calculs sécurisés
    double depassement = montant - c->solde;
    double taxe = 0.0;

    if (depassement > 0) {
        taxe = calcul_taxe(c, depassement, c->categorie);
    }

    c->solde -= (montant + taxe);
    printf("Débit effectué. Nouveau solde: %.2f\n", c->solde);
}

// Implémentation d'un test de solde
int solde_suffisant(Compte *c, double montant) {
    if (c == NULL) return 0;
    
    // Comparaison avec strcmp
    if (strcmp(c->type, "epargne") == 0) {
        return (c->solde >= montant);
    }
    return 1; // Autorisation par défaut pour les autres types

}





