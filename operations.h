#ifndef<operations.h>
#define<operations.h>
#include<stdio.h>
#include<stdlib.h>
#include<structures.h>
//taxe de facilite
void calcul_taxe(double montant,char cat){
	if (cat==privilege)
		return montant*faciliteCaisse;
}

//vérifier si solde suffisant pour debit
void solde_suffisant(compte*c,double montant){
	//compte epargne 
	if(c->type==epargne){
		return (c->solde-montant)>=solde_min_epargne;//sauf fermeture
	}
	//compte courant
	return (c->solde-montant)<= -(c->faciliteCaisse);
}

//créditer un compte
void crediter_compte(Compte comptes[],int nb,int numero,double montant){
	
	if(montant<=0){
		printf("impossible de débiter ce montant.");
	}
	Compte*c = rechercher_compte(comptes,nb,numero);
	if(!c){
		printf("Compte n°%d introuvalble.\n",numero);
	} elseif(c->bloque){
		printf("compte bloqué. Operation impossible.\n");
	
	}else{
		c->solde+=montant
		printf("crédit de %.2f FCFA effectue.Nouveau solde:%.2f FCFA\n",montant,c->solde);
	}
	
}

//fonction pour débiter un compte
void debiter_compte(Compte comptes[],int nb,int numero,double montant){
	double taxe=0.0;
	double dispo=c->solde+c->faciliteCaisse;
	double depassement=montant-c>solde;
	
	if(montant<=0){
		printf("impossible de débiter ce montant.");
	}
	Compte*c = rechercher_compte(comptes,nb,numero);
	if(!c){
		printf("Compte n°%d introuvalble.\n",numero);
	} 
	if(c->bloque){
		printf("compte bloqué. Operation impossible.\n");
	
	}
	//verifier disponibilite
	if(!solde_suffisant(c,montant)){
		
		printf("solde insuffisant.Disponible %.2f FCFA\n",dispo);
	}
	//calcul taxe
	if(c->type==courant && c->categorie==privilege){
		if (depassement>0){
			taxe=calcul_taxe(depassement,c->categorie);
		}
	}
	c->solde-=(montant+taxe);
	printf("taxe facilite appliquee:%.2f FCFA\n",taxe);
	printf("debit de %.2f FCFA effectue.Nouveau solde:%.2f FCFA\n",montant,c->solde);
	
}

