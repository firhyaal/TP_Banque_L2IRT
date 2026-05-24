#ifndef STRUCTURES_H
#define STRUCTURES_H
//structure pour la date
typedef struct Date Date;
struct Date{
    int jour;
    int mois;
    int annee;
};
//structure pour le client
typedef struct Client Client;
struct Client {
    unsigned int id;
    char nom[50];
    char prenom[50];
    char sexe;
    Date dateNaissance;
    char telephone[15];
};
//structure pour le compte
typedef struct Compte Compte;
struct Compte {
    int numero;
    Date dateCreation;
    char type[15];
    char categorie[15];
    float solde;
    float faciliteCaisse;
    char etat[15];
    char codePin[10];
    unsigned int idClient;
};
#endif 