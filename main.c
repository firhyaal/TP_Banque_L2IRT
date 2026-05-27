#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
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
int dernier_num = 1000;
	

/*void afficher_titre_encadre(char titre[]) {
    int longueur = strlen(titre);
    int i;

// 1. Ligne supérieure (+ suivi de tirets adaptés, puis +)
    printf("\n+");
    for (i = 0; i < longueur + 2; i++) { // +2 pour couvrir les 2 espaces autour du texte
        printf("-");
    }
    printf("+\n");

    // 2. Ligne du milieu (| un espace, le texte, un espace, |)
    printf("| %s |\n", titre);

    // 3. Ligne inférieure (+ suivi de tirets adaptés, puis +)
    printf("+");
    for (i = 0; i < longueur + 2; i++) {
        printf("-");
    }
    printf("+\n\n");
	}*/
//initialisation des fichiers
// Permet de positionner le curseur de souris sur l'écran à l'endroit
// de coordonnées x,y
void gotoxy(int x, int y) 
{ 
    HANDLE hConsoleOutput; 
    COORD dwCursorPosition; 
    fflush(stdout); 
    dwCursorPosition.X = x; 
    dwCursorPosition.Y = y; 
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition); 
} 

// Pour effacer l'écran 
void clrscr()
{ 
  system("cls"); 
} 


// Fonction pour dessiner un rectangle
void rectangle(int x, int y, int lon, int haut)
{
     int i;
     gotoxy(x,y); printf("%c",218);
     gotoxy(x+lon,y); printf("%c",191);
     gotoxy(x, y+haut); printf("%c",192);
     gotoxy(x+lon, y+haut); printf("%c",217);     
     for (i=1; i<lon;i++)
     {
         gotoxy(x+i,y); printf("%c",196); 
         gotoxy(x+i,y+haut); printf("%c",196);
     }
     for (i=1; i<haut;i++)
     {
         gotoxy(x,y+i); printf("%c",179); 
         gotoxy(x+lon,y+i); printf("%c",179);
     }
}

//Pour définir une couleur de texte et une couleur de fond du texte.
void Color(int t,int f)
{
	HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(H,f*16+t);
}
void afficher_titre_encadre(char titre[]){
	//automatiser la largeur
	int longueur = strlen(titre);
	int largeur_cadre=longueur+8;
	int debut_x=(70-largeur_cadre);
	clrscr();
	Color(15,0);
	rectangle(debut_x,2,largeur_cadre,5);
	gotoxy(debut_x+4,4);
	printf("%s",titre);
	//Color(7,0);
	gotoxy(2,12);
	
}

void init_data(){
	charger_clients(clients);
	chargerComptes(comptes,&nbComptes,&dernier_num);
	
}
//sauvegarde des donn�es

void sauvegarde_globale(){
	sauvegarder_clients(clients,nbClients);
	sauvegarderComptes(comptes,nbComptes);
	
}
void menu_creer_compte(){
	afficher_titre_encadre("CREER UN COMPTE");
	nbClients=charger_clients(clients);
	creerCompte(comptes,&nbComptes,clients,&nbClients);
		sauvegarde_globale();
}
void menu_consulter(){
	afficher_titre_encadre("CONSULTER MON COMPTE");
	consulterCompte(comptes,nbComptes);

}
//fonction pour le menu d�biter
void menu_debiter(){
	float montant_d;
	double solde_avant=0;
	int num;
	
	char pinc[10];
	afficher_titre_encadre("DEBITER UN COMPTE");
	chargerComptes(comptes,&nbComptes,&dernier_num);
	printf("Numero de compte:");
	scanf(" %d",&num);
	while(getchar() != '\n');
	/*printf("Code pin:");
	scanf("%s",pinc);*/
	printf("Montant a debiter:");
	scanf(" %f",&montant_d);
	
	debiter_compte(comptes,nbComptes,num,montant_d,pinc);
	enregistrer_journal(num,"DEBIT",montant_d,comptes[indexCompte].solde);
	
}
void menu_crediter(){
	int index;
	float montant_c;
	int numeroc;
	
	afficher_titre_encadre("CREDITER UN COMPTE");
	
	chargerComptes(comptes,&nbComptes,&dernier_num);
	
	printf("Num�ro de compte:");
	
	scanf(" %d",&numeroc);
	//while(getchar() != '\n');
	printf("Montant a crediter:");
	
	scanf(" %f",&montant_c);
	crediter_compte(comptes,nbComptes,numeroc,montant_c);
	enregistrer_journal(numeroc,"CREDIT",montant_c,comptes[index].solde);
	
}
void menu_rechercher_client(){
	int choice;
	char nom[15];
	int numCompte;
	afficher_titre_encadre("RECHERCHER UN CLIENT");
	printf("1-Par nom de famille\n2-par num�ro de compte\nchoix:");
	scanf(" %d",&choice);
	while(getchar() != '\n');
	if(choice==1){
		nbClients=charger_clients(clients);
		printf("Veuillez entrer votre nom:");
		scanf(" %s",nom);
		rechercher_par_nom(clients,nbClients,nom);
		
	}else if(choice==2){
		chargerComptes(comptes,&nbComptes,&dernier_num);
		printf("Veuillez entrer votre numero de compte:");
		scanf(" %s",&numCompte);
		rechercherParNumeroCompte(comptes,nbComptes,clients,nbClients);
	} else{
		printf("erreur choisissez le bon chiffre");
	}
	
}
void menu_historique_compte(){
	char nom[15];
	int numeCompte;
	nbClients=charger_clients(clients);
	printf("Veuillez entrer votre nom:");
	scanf(" %s",nom);
	//while(getchar() != '\n');
	chargerComptes(comptes,&nbComptes,&dernier_num);
	printf("Veuillez entrer votre numero de compte:");
	scanf(" %d",&numeCompte);
	afficher_historique(numeCompte,comptes,nbComptes,clients,nbClients);
}
void afficherMenu() {
    afficher_titre_encadre("BANQUE-MENU PRINCIPAL");
    //printf("0-s'enregistrer\n");
    printf("1. Creer un nouveau compte bancaire\n");
    printf("2. Crediter un compte (Versement)\n");
    printf("3. Debiter un compte (Retrait)\n");
    printf("4. Consulter le solde d'un compte\n");
    printf("5. Rechercher un client\n");
    printf("6. Afficher l'historique des operations (Journal)\n");
    printf("7. Quitter l'application\n");

    
}

int main() {
	init_data();

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
        while(getchar()!= '\n');
        // Sécurité anti-plantage si quelqu'un saisit une lettre
        if ( choix<0) {
            printf("\n[Erreur] Saisie invalide ! Veuillez entrer un chiffre entre 1 et 7.\n");
            
        } 
            

        

        switch (choix) {
        	/*case 0:
        		enregistrer_client(clients,&nbClients);
        		break;*/
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












