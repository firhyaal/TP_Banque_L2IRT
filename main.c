#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "gestion_clients.h"
#include "operations.h"
#include "comptes.h"
#include "journal.h"

Client clients[100];
Compte comptes[100];
int nbClients=0;
int nbComptes=0;
int nbJournal=0;
int indexCompte;
void afficher_titre_encadre(char titre[]) {
    int longueur = strlen(titre);
    int i;

// 1. Ligne sup√©rieure (+ suivi de tirets adapt√©s, puis +)
    printf("\n+");
    for (i = 0; i < longueur + 2; i++) { // +2 pour couvrir les 2 espaces autour du texte
        printf("-");
    }
    printf("+\n");

    // 2. Ligne du milieu (| un espace, le texte, un espace, |)
    printf("| %s |\n", titre);

    // 3. Ligne inf√©rieure (+ suivi de tirets adapt√©s, puis +)
    printf("+");
    for (i = 0; i < longueur + 2; i++) {
        printf("-");
    }
    printf("+\n\n");
	}
//initialisation des fichiers
void init_data(){
	charger_clients(clients);
	chargerComptes(comptes,&nbComptes);
	
}
//sauvegarde des donnÈes

void sauvegarde_globale(){
	sauvegarder_clients(clients,nbClients);
	sauvegarderComptes(comptes,nbComptes);
	
}
void menu_creer_compte(){
	afficher_titre_encadre("CREER UN COMPTE");
	creerCompte(comptes,&nbComptes,clients,&nbClients);
		sauvegarde_globale();
}
void menu_consulter(){
	afficher_titre_encadre("CONSULTER MON COMPTE");
	consulterCompte(comptes,nbComptes);

}
//fonction pour le menu dÈbiter
void menu_debiter(){
	
	float montant_d;
	double solde_avant=0;
	int num;
	char pinc[10];
	afficher_titre_encadre("DEBITER UN COMPTE");
	printf("NumÈro de compte:\n");
	scanf("%d",&num);
	printf("Code pin:\n");
	scanf("%s",&pinc);
	printf("Montant a debiter:\n");
	scanf("%.2f",&montant_d);
	debiter_compte(comptes,nbComptes,num,montant_d,pinc);
	enregistrer_journal(num,"DEBIT",montant_d,comptes[indexCompte].solde);
	
}
void menu_crediter(){
	
	float montant_c;
	int numeroc;
	char pinco[10];
	afficher_titre_encadre("CREDITER UN COMPTE");
	printf("NumÈro de compte:\n");
	scanf("%d",numeroc);
	printf("Montant a crediter:\n");
	scanf("%.2f",&montant_c);
	crediter_compte(comptes,nbComptes,numeroc,montant_c);
	enregistrer_journal(numeroc,"CREDIT",montant_c,comptes[indexCompte].solde);
	
}
void menu_rechercher_client(){
	int choice;
	char nom[15];
	int numCompte;
	afficher_titre_encadre("RECHERCHER UN CLIENT");
	printf("1-Par nom de famille\n2-par numÈro de compte\nchoix:");
	scanf("%d\n",&choice);
	if(choice==1){
		printf("Veuillez entrer votre nom:");
		scanf("%s\n",&nom);
		rechercher_par_nom(clients,nbClients,nom);
	}else if(choice==2){
		printf("Veuillez entrer votre numero de compte:");
		scanf("%s\n",&numCompte);
		rechercherParNumeroCompte(comptes,nbComptes,clients,nbClients);
	} else{
		printf("erreur choisissez le bon chiffre");
	}
	
}
void menu_historique_compte(){
	char nom[15];
	int numeCompte;
	printf("Veuillez entrer votre nom:");
	scanf("%s\n",&nom);
	printf("Veuillez entrer votre numero de compte:");
	scanf("%s\n",&numeCompte);
	afficher_historique(numeCompte,comptes,nbComptes,clients,nbClients);
}
void afficherMenu() {
    afficher_titre_encadre("BANQUE-MENU PRINCIPAL");
    printf("0-s'enregistrer\n");
    printf("1. Creer un nouveau compte bancaire\n");
    printf("2. Crediter un compte (Versement)\n");
    printf("3. Debiter un compte (Retrait)\n");
    printf("4. Consulter le solde d'un compte\n");
    printf("5. Rechercher un client\n");
    printf("6. Afficher l'historique des operations (Journal)\n");
    printf("7. Quitter l'application\n");

    
}

int main() {
	init_data;

    int choix;
    /*int idRecherche;
    Client tabClients[100];
    int *nbClients=0;
    int numeroSaisi;
    double montantSaisi;
    Compte tabCompte[100];
    int nbComptes=0;
    Compte mesComptes[100];*/
    do {
        afficherMenu();
        
        printf("Votre choix : ");
        scanf("%d", &choix);
        // S√©curit√© anti-plantage si quelqu'un saisit une lettre
        if ( choix<0) {
            printf("\n[Erreur] Saisie invalide ! Veuillez entrer un chiffre entre 1 et 7.\n");
            
        } 
            

        

        switch (choix) {
        	case 0:
        		enregistrer_client(clients,&nbClients);
        		break;
            case 1:
                
                menu_creer_compte();
                break;
            case 2:
                        

                // Connexion avec le travail de Firhyaal
                menu_crediter();
                break;
                
            case 3:
                
                menu_debiter();
                
                break;
                
            case 4:
              menu_consulter();
                break;
                
            case 5:
                menu_rechercher_client();
             break;
                
            case 6:
               menu_historique_compte();
                break;
                
            case 7:
                afficher_titre_encadre("fermeture du compte bancaire");
                break;
                
            default:
                printf("\n[Attention] Option inconnue ! Choisis un chiffre entre 1 et 7.\n\n");
        }
    } while (choix >= 0);

    return 0;
}












