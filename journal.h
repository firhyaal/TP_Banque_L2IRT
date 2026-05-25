#ifndef JOURNAL_H
#define JOURNAL_H
#include "structures.h"
#include "comptes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CLE_XOR 0x5A

#define max_essai_pin 3

/* Gestion de l'authentification PIN
    - D'abord faire une recherche du compte par N°
    - Authentifier en passant par la fonction 
        . L'objectif est de vérifier si le pin enter 
          est égale à celle enregistré au début: 
           verifierPin()
*/

int rechercherCompteParNumero(int numero) {
    int i;
    for (i = 0; i < MAX_COMPTES; i++) {
        if (comptes[i].numero == numero) return i;
    }
    return -1;
}

void crypterPin(const char *pin, char *pinCrypte) {
    int i;
    for (i = 0; pin[i] != '\0'; i++)
        pinCrypte[i] = (char)(pin[i] ^ CLE_XOR);
    pinCrypte[i] = '\0';
}
 
int verifierPin(const char *saisie, const char *stocke) {
    char temp[pinLen];
    crypterPin(saisie, temp);
    return (strcmp(temp, stocke) == 0);
}

int authentification(int index) {
    char saisie[pinLen];
    int  essai;
 
    for (essai = 0; essai < max_essai_pin; essai++) {
        printf("Entrer votre PIN: ");
        scanf("%s",saisie);
        if (verifierPin(saisie, comptes[index].codePin)) {
            return 1;
        }
        printf("Code PIN incorrect. Essai %d/%d.\n", essai + 1, max_essai_pin);
    }
    /* Blocage du compte */
    strcpy(comptes[index].etat, "bloque");
    sauvegarderComptes();
    printf("Compte bloqué après %d essais incorrects.\n", max_essai_pin);
    return 0;
}






#endif