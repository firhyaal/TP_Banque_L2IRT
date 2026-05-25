#ifndef<operations.h>
#define<operations.h>
#include<stdio.h>
#include<stdlib.h>
#include<structures.h>
//taxe de facilite
void calcul_taxe(double montant,char cat){
	if (cat==PRIVILEGE)
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
	Compte*c = rechercher_compte(comptes,nb,numero)
}

