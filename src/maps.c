
// #############################
// #                           #
// #    AEVILIA SOURCE CODE    #
// #       Version 0.4.0       #
// #                           #
// #   Version expérimentale,  #
// #  seulement à des fins de  #
// #     test. Probablement    #
// #  instable, utilisez-la à  #
// #   vos risques et périls.  #
// #                           #
// #############################
// ##                         ##
// #### Maps - Headers, etc. ###
// #############################


#include "maps.h"
#include "defines.h"
#include "aevilia.h"
#include "sauvegarde.h"
#include "moteur_graphique.h"
#include "utilitaires.h"
#include "menus.h"
#include "baston.h"


// Partie commune à tous les scripts de sauvegarde.

void resetRetourEcranTitre(Commande* commande) {
	commande->compteur = 0;
	
	menuArendre = NULL;
	mapDestination = ECRAN_TITRE;
	warpDestination = 0;
}
Commande resetMenusRetourEcranTitre	= CMD_FONCTION(resetRetourEcranTitre, NULL);
Commande* cmdsRetourEcranTitre[2]	= {&resetMenusRetourEcranTitre, NULL};
Commande demanderRetourEcranTitre	= CMD_OPTIONS(cmdsRetourEcranTitre, chainesOuiNon, 2, NULL);
Menu menuRetourEcranTitre			= MENU(HAUTEUR_FENETRE - 8 * HAUTEUR_TILE, 0, 2, 6, &demanderRetourEcranTitre);

Commande ajouterRetourEcranTitre	= CMD_AJOUTER_MENU(&menuRetourEcranTitre, MENU_CONSERVER, NULL);
wchar_t chaineRetourEcranTitre[]	= L"Retourner à l'écran titre ?";
Commande afficherChaineRetourEcranT	= CMD_CHAINE(chaineRetourEcranTitre, &ajouterRetourEcranTitre);
Commande effacerChaineRetourEcranT	= CMD_EFFACER(&afficherChaineRetourEcranT);
Commande attendreRetourEcranT		= CMD_ATTENDRE(&effacerChaineRetourEcranT);
wchar_t sauvTerminee[]				= L"Partie sauvegardée !";
Commande afficherSauvTerminee		= CMD_CHAINE(sauvTerminee, &attendreRetourEcranT);
Commande effacerChaineSauv			= CMD_EFFACER(&afficherChaineRetourEcranT);
void sauvegarderParCommande(Commande* commande) {
	commande->compteur = 0;
	mettreAjourSauvegarde(dernierChoixMenu);
	effacerChaineSauv.suivante = &afficherSauvTerminee;
}
Commande effectuerSauvegarde		= CMD_FONCTION(sauvegarderParCommande, NULL);
Commande* choixSauvs[]				= {&effectuerSauvegarde, &effectuerSauvegarde, &effectuerSauvegarde, NULL};
wchar_t sauvs[4][LONG_NOM_OPTIONS]	= {L"Sauv. 1", L"Sauv. 2", L"Sauv. 3", L"Annuler"};
Commande choisirSauv				= CMD_OPTIONS(choixSauvs, sauvs, 4, NULL);
void defautEffacerChaineSauv(Commande* commande) {
	commande->compteur = 0;
	effacerChaineSauv.suivante = &effacerChaineRetourEcranT;
}
Commande defautEffacer				= CMD_FONCTION(defautEffacerChaineSauv, &choisirSauv);
Menu choixSauvegarde				= MENU(HAUTEUR_FENETRE - 10 * HAUTEUR_TILE, 0, 4, 11, &defautEffacer);

Commande ajouterChoixSauv			= CMD_AJOUTER_MENU(&choixSauvegarde, MENU_FERMER, &effacerChaineSauv);
wchar_t voulezVousSauv[]			= L"Voulez-vous sauvegarder ?";
Commande voulezVousSauvegarder		= CMD_CHAINE(voulezVousSauv, &ajouterChoixSauv);


unsigned int timerAnimationPorte	= 0;
#define ANIM_JOUEUR(attr) attributsTiles[JOUEUR_HAUT]-> attr
void cacherJoueur(void) {
	spritesMapCourante[0].tile = 0;
}
void afficherJoueur(void) {
	spritesMapCourante[0].tile = JOUEUR_HAUT;
}
unsigned int ouvrirPorteExt(void) {
	ANIM_JOUEUR(frameMax) = 0;
	
	if(!timerAnimationPorte) {
		modifierNumeroTile(positionVertJoueur / HAUTEUR_TILE, positionHorizJoueur / LARGEUR_TILE, &couchesMapCourante[coucheJoueur], PORTE_OUVERTE);
		
		if(attributsTiles[PORTE_OUVERTE]->frame) {
			return 0;
		}
	} else if(timerAnimationPorte == 4) {
		attributsTiles[PORTE_OUVERTE]->frame = 1;
	} else if(timerAnimationPorte == 7) {
		timerAnimationPorte = 0;
		return 0;
	}
	
	return ++timerAnimationPorte;
}
unsigned int ouvrirPorteInt(void) {
	ANIM_JOUEUR(frameMax) = 0;
	
	if(!timerAnimationPorte) {
		modifierNumeroTile(positionVertJoueur / HAUTEUR_TILE + 1, positionHorizJoueur / LARGEUR_TILE, &couchesMapCourante[coucheJoueur], PORTE_OUVERTE);
		
		if(attributsTiles[PORTE_OUVERTE]->frame) {
			return 0;
		}
	} else if(timerAnimationPorte == 4) {
		attributsTiles[PORTE_OUVERTE]->frame = 1;
	} else if(timerAnimationPorte == 7) {
		timerAnimationPorte = 0;
		return 0;
	}
	
	return ++timerAnimationPorte;
}
unsigned int fermerPorteExt(void) {
	ANIM_JOUEUR(frameMax) = 1;
	
	if(!timerAnimationPorte) {
		timerAnimationPorte = 4;
		attributsTiles[PORTE_OUVERTE]->frame = 0;
	}
	if(timerAnimationPorte) {
		timerAnimationPorte--;
	}
	if(!timerAnimationPorte) {
		if(!attributsTiles[PORTE_OUVERTE]->frame) {
			modifierNumeroTile(positionVertJoueur / HAUTEUR_TILE, positionHorizJoueur / LARGEUR_TILE, &couchesMapCourante[coucheJoueur], PORTE);
		}
		
		ETEINDRE_FLAG(IGNORER_SPRINT);
		return 0;
	}
	
	return 1;
}
unsigned int fermerPorteInt(void) {
	ANIM_JOUEUR(frameMax) = 1;
	
	if(!timerAnimationPorte) {
		timerAnimationPorte = 4;
		attributsTiles[PORTE_OUVERTE]->frame = 0;
	}
	if(timerAnimationPorte) {
		timerAnimationPorte--;
	}
	if(!timerAnimationPorte) {
		if(!attributsTiles[PORTE_OUVERTE]->frame) {
			modifierNumeroTile(positionVertJoueur / HAUTEUR_TILE + 1, positionHorizJoueur / LARGEUR_TILE, &couchesMapCourante[coucheJoueur], PORTE);
		}
		
		ETEINDRE_FLAG(IGNORER_SPRINT);
		return 0;
	}
	
	return 1;
}

extern ElemCinematique ouvrirPorteExt0;
extern ElemCinematique ouvrirPorteExt1;
extern ElemCinematique ouvrirPorteExt2;
extern ElemCinematique ouvrirPorteExt3;
extern ElemCinematique ouvrirPorteExt4;
ElemCinematique ouvrirPorteExt0		= ACTION_FLAG(IGNORER_SPRINT, 1, &ouvrirPorteExt1);
ElemCinematique ouvrirPorteExt1		= ACTION_FONCTION(ouvrirPorteExt, &ouvrirPorteExt2);
ElemCinematique ouvrirPorteExt2		= ACTION_BOUGER(HAUT, 1, &ouvrirPorteExt3);
ElemCinematique ouvrirPorteExt3		= ACTION_DJNZ(11, &ouvrirPorteExt2, &ouvrirPorteExt4);
ElemCinematique ouvrirPorteExt4		= ACTION_TILE_SPR(0, TRANSPARENT_MARCHE, NULL);

extern ElemCinematique ouvrirPorteInt0;
extern ElemCinematique ouvrirPorteInt1;
extern ElemCinematique ouvrirPorteInt2;
extern ElemCinematique ouvrirPorteInt3;
extern ElemCinematique ouvrirPorteInt4;
ElemCinematique ouvrirPorteInt0		= ACTION_FLAG(IGNORER_SPRINT, 1, &ouvrirPorteInt1);
ElemCinematique ouvrirPorteInt1		= ACTION_FONCTION(ouvrirPorteInt, &ouvrirPorteInt2);
ElemCinematique ouvrirPorteInt2		= ACTION_BOUGER(BAS, 1, &ouvrirPorteInt3);
ElemCinematique ouvrirPorteInt3		= ACTION_DJNZ(11, &ouvrirPorteInt2, &ouvrirPorteInt4);
ElemCinematique ouvrirPorteInt4		= ACTION_TILE_SPR(0, TRANSPARENT_MARCHE, NULL);

extern ElemCinematique fermerPorteExt0;
extern ElemCinematique fermerPorteExt1;
extern ElemCinematique fermerPorteExt2;
extern ElemCinematique fermerPorteExt3;
extern ElemCinematique fermerPorteExt4;
extern ElemCinematique fermerPorteExt5;
extern ElemCinematique fermerPorteExt6;
ElemCinematique fermerPorteExt0		= ACTION_FONCTION(ouvrirPorteExt, &fermerPorteExt1);
ElemCinematique fermerPorteExt1		= ACTION_FLAG(IGNORER_SPRINT, 1, &fermerPorteExt2);
ElemCinematique fermerPorteExt2		= ACTION_TILE_SPR(0, JOUEUR_HAUT, &fermerPorteExt3);
ElemCinematique fermerPorteExt3		= ACTION_BOUGER(BAS, 1, &fermerPorteExt4);
ElemCinematique fermerPorteExt4		= ACTION_DJNZ(12, &fermerPorteExt3, &fermerPorteExt5);
ElemCinematique fermerPorteExt5		= ACTION_FONCTION(fermerPorteExt, NULL);

extern ElemCinematique fermerPorteInt0;
extern ElemCinematique fermerPorteInt1;
extern ElemCinematique fermerPorteInt2;
extern ElemCinematique fermerPorteInt3;
extern ElemCinematique fermerPorteInt4;
extern ElemCinematique fermerPorteInt5;
ElemCinematique fermerPorteInt0		= ACTION_FONCTION(ouvrirPorteInt, &fermerPorteInt1);
ElemCinematique fermerPorteInt1		= ACTION_FLAG(IGNORER_SPRINT, 1, &fermerPorteInt2);
ElemCinematique fermerPorteInt2		= ACTION_TILE_SPR(0, JOUEUR_HAUT, &fermerPorteInt3);
ElemCinematique fermerPorteInt3		= ACTION_BOUGER(HAUT, 1, &fermerPorteInt4);
ElemCinematique fermerPorteInt4		= ACTION_DJNZ(12, &fermerPorteInt3, &fermerPorteInt5);
ElemCinematique fermerPorteInt5		= ACTION_FONCTION(fermerPorteInt, NULL);


#include "maps/TEST.c"
#include "maps/EcranTitre.c"
#include "maps/MaisonTEST.c"
#include "maps/Intro.c"
#include "maps/EcranCrash.c"


void enregistrerHeaders(void) {
	LOGGER("Génération de la liste des headers de maps...")
	
	enregistrerTEST();
	enregistrerEcranTitre();
	enregistrerMaisonTEST();
	enregistrerIntro();
	enregistrerEcranCrash();
	
	LOGGER("Génération terminée.")
}

