#ifndef STRUCTURES_H
#define STRUCTURES_H
#define PRIVILEGE 'P'
#define depassement
#define solde_init_epargne 10000.0
#define solde_init_courant 0.0
#define solde_min_epargne 5000.0
#define facilite_privilege 200000.0
#define taxe_facilite 0.05
#define pinLen 10


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