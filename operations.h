#ifndef OPERATIONS_H
#define OPERATIONS_H
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "structures.h"
#include "journal.h"
#include "comptes.h"

//taxe de facilite
double calcul_taxe(float montant,char* cat){
	if (strcmp(cat,"privilege")==0)
		return montant * taxe_facilite;
}

//vérifier si solde suffisant pour debit
int solde_suffisant(Compte comptes[],int nb,int numero,float montant){
	int index;
	index = rechercherCompte(comptes,nb,numero);
	//compte epargne 
	if(strcmp(comptes[index].type,"epargne")==0){
		return (comptes[index].solde-montant)>=solde_min_epargne;//sauf fermeture
	}
	//compte courant
	return (comptes[index].solde-montant)<= -(facilite_privilege);
}
//créditer un compte
int crediter_compte(Compte comptes[],int nb,int numero,float montant){
	int index;
	index = rechercherCompte(comptes,nb,numero);

	
	//si le compte n'existe pas
	if(index ==-1){
		printf("Compte n°%d introuvalble.\n",numero);
		return 0;
	} 
	if(strcmp(comptes[index].etat,"bloque")==0){
		printf("compte bloqué. Operation impossible.\n");
		return 0;
	
	}
	//si le montant est négatif
		if(montant<=0){
		printf("impossible de crediter ce montant.");
		return 0;
	}else{
	comptes[index].solde+=montant;
	printf("crédit de %f FCFA effectue.Nouveau solde:%f FCFA\n",montant,comptes[index].solde);
	return 1;
	}
	
	}
	
	
	


//fonction pour débiter un compte
double debiter_compte(Compte comptes[],int nb,int numero,float montant,char*pin){
	double taxe=0.0;
	float dispo;
	float depassement;
	int index;
	
	
	/*printf("Numero de compte:");
	fflush(stdout);
	scanf("%d\n",&numero);
	while(getchar() != '\n');*/
	//rechercher le compte à debiter
	index=rechercherCompte(comptes,nb,numero);
	
	
		if(index==-1){
			printf("Compte n°%d introuvalble.\n",numero);
			return 0;
		} 
		if(strcmp(comptes[index].etat,"bloque")==0){
			printf("compte bloqué. Operation impossible.\n");
			return 0;
		
		}
		
		
	
	
		//verifier code pin
		/*printf("Code pin:");
		fflush(stdout);
		scanf("%s",pin);*/
		if(!authentification(comptes,index,nb))
		return 0;
		//verifier disponibilite
		dispo=(comptes[index].solde)+(facilite_privilege);
		if(!solde_suffisant(comptes,nb,numero,montant)){
			
			printf("solde insuffisant.Disponible %.2f FCFA\n",dispo);
			return 0; 
		}
		/*printf("Montant a debiter:");
		fflush(stdout);
		scanf("%.2f",&montant);*/
		if(montant<0){
		printf("impossible de débiter ce montant.");
		return 0;
		}
		
		//calcul taxe
		depassement=montant-(comptes[index].solde);
		if(strcmp(comptes[index].type,"courant")==0 &&strcmp(comptes[index].categorie,"privilege")==0){
			if (depassement>0){
				//vérifier si le découvert autoriseécouvre le depassement
				if(depassement<=facilite_privilege){
					taxe=calcul_taxe(depassement,comptes[index].categorie);
					comptes[index].solde-=(montant+taxe);
					printf("taxe facilite appliquee:%.2f FCFA\n",taxe);
					printf("debit de %.2f FCFA effectue.Nouveau solde:%.2f FCFA\n",montant,comptes[index].solde);
					return 1;
				} else{
					printf("solde insuffisant");
				}
				
			}else{
				comptes[index].solde-=montant;
				printf("debit de %f FCFA effectue.Nouveau solde:%f FCFA\n",montant,comptes[index].solde);
			}
			
		}
		else if(strcmp(comptes[index].type,"epargne")==0){
			if(montant>comptes[index].solde){
				printf("pas  sur un compte épargne");
				
			}else{
				comptes[index].solde-=montant;
				printf("debit de %.2f FCFA effectue.Nouveau solde:%.2f FCFA\n",montant,comptes[index].solde);
			
			}
		}
	
	
		
		
		//return 1;
	
	return 0;
}
#endif

