
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
// ##### Fonctions d'objets ####
// #############################


#include <stdio.h>
#include <string.h>

#include "objets.h"
#include "defines.h"
#include "utilitaires.h"
#include "menus.h"

#include "objets/DEBUG.c"
#include "objets/ZapJouet.c"


#define TERMINATEUR_OBJET								(unsigned int)-1
AttribObjet* attributsObjets[NB_OBJETS]					= {&obj__DEBUG, &obj__ZapJouet};


wchar_t chaineObjetNonJetable[]							= L"Je ne m'en séparerai pas !";
Commande commandeJeterObjet8							= CMD_CHAINE(chaineObjetNonJetable, &attendreEtTerminer);
Commande commandeJeterObjet7							= CMD_FONCTION(jeterObjetJoueur, NULL);
wchar_t ouiNonJeterObjet[2][LONG_NOM_OPTIONS]			= {L"Oui\1", L"Non"};
Commande* confirmationsJeterObjet[2]					= {&commandeJeterObjet7, NULL};
Commande commandeJeterObjet6							= CMD_OPTIONS(confirmationsJeterObjet, ouiNonJeterObjet, 2, NULL);
Menu menuConfirmationJeterObjet							= MENU(HAUTEUR_FENETRE - 5 * HAUTEUR_TILE, LARGEUR_FENETRE - LARGEUR_TILE * 8, 3, 6, &commandeJeterObjet6);
Commande commandeJeterObjet5							= CMD_AJOUTER_MENU(&menuConfirmationJeterObjet, MENU_CONSERVER, NULL);
wchar_t chaineConfirmerJeterObjet[]						= L"\1Vous êtes sûr ?";
Commande commandeJeterObjet4							= CMD_CHAINE_INSTANT(chaineConfirmerJeterObjet, &commandeJeterObjet5);
Commande commandeJeterObjet3							= CMD_DEMANDER_ENTIER(HAUTEUR_FENETRE - 4 * HAUTEUR_TILE, LARGEUR_TILE * 26, 1, &commandeJeterObjet4);
wchar_t chaineJeterObjet[]								= L"Jeter combien d'objets ?";
Commande commandeJeterObjet2							= CMD_CHAINE_INSTANT(chaineJeterObjet, &commandeJeterObjet3);
Commande commandeJeterObjet1							= CMD_SAUTER_COND(verifierObjetJetable, &commandeJeterObjet2, &commandeJeterObjet8);
Menu menuJeterObjet										= TEXTBOX(&commandeJeterObjet1);
Commande commandeJeterObjet0							= CMD_AJOUTER_MENU(&menuJeterObjet, MENU_FERMER, NULL);


Commande commandeUtiliserObjet							= CMD_FONCTION(utiliserObjetJoueur, NULL);


// Les actions possibles sur l'objet.
Commande* utilisations[]								= {&commandeUtiliserObjet, &commandeJeterObjet0, NULL};
wchar_t nomsUtilisations[3][LONG_NOM_OPTIONS]			= {L"UTILISER", L"JETER", L"ANNULER"};
Commande selectionnerUtilisation						= CMD_OPTIONS(utilisations, nomsUtilisations, 3, NULL);
Menu utilisation										= MENU(0, (NB_TILES_LARG - LONG_NOM_OPTIONS - 14) * LARGEUR_TILE, 3, 11, &selectionnerUtilisation);

// Choisir l'action à effectuer sur l'objet en question.
Commande choisirActionObjet								= CMD_AJOUTER_MENU(&utilisation, MENU_FERMER, NULL);


// Retirer le script de fermeture de l'inventaire.
Commande retirerFermetureInventaire						= CMD_FONCTION(retirerScriptInventaire, NULL);
Commande rebouclerInventaire							= CMD_SAUTER_COND(rebouclerOuNon, &retirerFermetureInventaire, NULL);

// Choisir l'objet à utiliser.
Commande* actionsObjets[NB_OBJETS + 1]					= {[0 ... NB_OBJETS] = NULL};
wchar_t nomsObjets[NB_OBJETS+1][LONG_NOM_OPTIONS]		= {[0] = L"Annuler", [1 ... NB_OBJETS] = L""};
Commande selectionnerObjet								= CMD_OPTIONS(actionsObjets, nomsObjets, 0, &rebouclerInventaire);
// Générer la liste des objets dans l'inventaire.
Commande genererInventaire								= CMD_FONCTION(arrangerInventaire, &selectionnerObjet);

Menu inventaire											= MENU(0, (NB_TILES_LARG - LONG_NOM_OPTIONS - 2) * LARGEUR_TILE, NB_TILES_HAUT - 6, LONG_NOM_OPTIONS, &genererInventaire);


Menu description										= TEXTBOX(NULL);

unsigned int decalageInventaire							= 0;


void (*scriptFrameSauvInventaire)(void);

void retirerScriptInventaire(Commande* commande) {
	commande->compteur = 0;
	
	popperScript(INVENTAIRE);
	scriptFrame = scriptFrameSauvInventaire;
}

unsigned int rebouclerOuNon(void) {
	description.texte[0] = 0;
	
	return selectionnerObjet.pointeur2 == NULL;
}

void arrangerInventaire(Commande* commande) {
	rebouclerInventaire.pointeur2 = inventaire.commande;
	
	unsigned int i = 0;
	while(ordreObjets[i] != (unsigned int)-1 && i < NB_OBJETS + 1) {
		wcsncpy(nomsObjets[i], obtenirNomObjet(ordreObjets[i]), LONG_NOM_OBJET);
		size_t item_name_len = wcslen(nomsObjets[i]);
		wmemset(nomsObjets[i] + item_name_len, L' ', LONG_NOM_OBJET - item_name_len);
		
		wmemcpy(&nomsObjets[i][LONG_NOM_OBJET-2], L"x  ", 4);
		ecrireNombre(quantitesObjets[ordreObjets[i]], &nomsObjets[i][LONG_NOM_OBJET-1]);
		nomsObjets[i][LONG_NOM_OBJET+1] = 0;
		actionsObjets[i] = &choisirActionObjet;
		i++;
	}
	wmemcpy(nomsObjets[i], L"ANNULER", 8);
	actionsObjets[i] = NULL;
	selectionnerObjet.compteur = i+1;
	
	commande->compteur = 0;
}

void fermerInventaire(void) {
	// Ne rien effectuer en dehors de ce if !
	if(dernierMenu() == &inventaire && selectionnerObjet.compteur2 > PHASE_OPTION_SETUP) {
		selectionnerObjet.pointeur = NULL;
		selectionnerObjet.pointeur2 = NULL;
		selectionnerObjet.compteur2 = PHASE_OPTION_FIN;
	}
}

void ouvrirInventaire(void) {
	if(FLAG(CONTROLE_JOUEUR) && actionEnCours == NULL && positionVertJoueur % HAUTEUR_TILE == 0 && positionHorizJoueur % LARGEUR_TILE == 0) {
		description.texte[0] = 0;
		ajouterMenu(&description);
		ajouterMenu(&inventaire);
	
		pousserScript(INVENTAIRE, fermerInventaire);
		
		scriptFrameSauvInventaire = scriptFrame;
		scriptFrame = &afficherDescription;
	}
}

wchar_t MissingItem[LONG_NOM_OBJET]	= L"MISSINGITEM.";
wchar_t descrMissingItem[] = L"Euh... aucune idée de ce que c'est !\1Par contre, ça a l'air très volatil.";
wchar_t descrAnnuler[] = L"Ferme l'inventaire.";
void afficherDescription(void) {
	if(description.tailleHoriz != description.tailleHorizCourante || inventaire.tailleHoriz != inventaire.tailleHorizCourante) {
		description.texte[0] = 0;
		
		return;
	}
	
	if(selectionnerObjet.compteur3 + selectionnerObjet.compteur4 == (signed int)selectionnerObjet.compteur - 1) {
		wcscpy(description.texte, descrAnnuler);
	} else {
		unsigned int IDobjet = ordreObjets[selectionnerObjet.compteur3 + selectionnerObjet.compteur4];
		if(IDobjet >= NB_OBJETS) {
			wcscpy(description.texte, descrMissingItem);
		} else {
			wcsncpy(description.texte, attributsObjets[IDobjet]->descr, LONG_TEXTE_MENU - 1);
		}
	}
	AFFICHAGE_INSTANTANE(&description);
}

wchar_t* obtenirNomObjet(unsigned int indexObjet) {
	return (indexObjet < NB_OBJETS) ? attributsObjets[indexObjet]->nom : MissingItem;
}

unsigned int utiliserObjet(unsigned int indexObjet) {
	if(indexObjet < NB_OBJETS) {
		return attributsObjets[indexObjet]->utiliserObjet(indexObjet);
	} else {
		WARN("Objet invalide utilisé ! ID : ")
		fprintf(fichierLog, "%d", indexObjet);
		return 0;
	}
}

void utiliserObjetJoueur(Commande* commande) {
	commande->compteur = 0;
	
	unsigned int indexObjet = ordreObjets[selectionnerObjet.compteur3 + selectionnerObjet.compteur4];
	quantitesObjets[indexObjet] = utiliserObjet(indexObjet);
	
	// Il n'y a plus d'objets, on le retire donc de l'ordre de rendu.
	if(quantitesObjets[indexObjet] == 0) {
		unsigned int index = 0;
		// On recherche l'objet dans l'ordre de rendu.
		while(ordreObjets[index] != indexObjet && index < NB_OBJETS) {
			index++;
		}
		// On décale tout.
		while(index < NB_OBJETS + 1) {
			ordreObjets[index] = ordreObjets[index + 1];
			index++;
		}
		ordreObjets[index] = 0;
	}
}

void obtenirObjet(unsigned int IDobjet, unsigned int qteObjet) {
	unsigned int i;
	if(quantitesObjets[IDobjet] == 0) {
		i = 0;
		while(i < NB_OBJETS && ordreObjets[i] != (unsigned int)-1) {
			i++;
		}
		ordreObjets[i]   = IDobjet;
		ordreObjets[i+1] = (unsigned int)-1;
	}
	quantitesObjets[IDobjet] += qteObjet;
	if((signed int)quantitesObjets[IDobjet] <= 0) {
		i = 0;
		while(i < NB_OBJETS && ordreObjets[i] != IDobjet) {
			i++;
		}
		while(i < NB_OBJETS) {
			ordreObjets[i] = ordreObjets[i+1];
			i++;
		}
	}
}

wchar_t obtentionObjets[LONG_NOM_OBJET + 21 + 3]	= L"Vous avez obtenu ?? 012345";
wchar_t objetInvalide[]								= L"Vous avez obtenu...                           Attends, c'est quoi, ça ?                     ... bon, on va laisser tomber.";

unsigned int _preparerObtention(Commande* commande) {
	if(commande->compteur >= NB_OBJETS) {
		return 0;
	}
	obtentionObjets[17] = L' ';
	obtentionObjets[18] = L' ';
	ecrireNombre(commande->compteur2, &obtentionObjets[17]);
	wcsncpy(&obtentionObjets[20], attributsObjets[commande->compteur]->nom, LONG_NOM_OBJET);
	wchar_t* ptr = &obtentionObjets[20] + wcslen(&obtentionObjets[20]);
	*ptr = L' ';
	ptr++;
	*ptr = L'!';
	ptr++;
	*ptr = 0;
	
	return 1;
}

Commande attendreObtention	= CMD_ATTENDRE(NULL);
Commande invalideObtenu		= CMD_CHAINE(objetInvalide, &attendreObtention);
Commande objetsObtenus		= CMD_CHAINE(obtentionObjets, &attendreObtention);
Commande preparerObtention	= CMD_SAUTER_COND(_preparerObtention, &objetsObtenus, &invalideObtenu);
Menu objetObtenu			= TEXTBOX(&preparerObtention);

void afficherObjetObtenu(unsigned int IDobjet, unsigned int qteObjet) {
	preparerObtention.compteur  = IDobjet;
	preparerObtention.compteur2 = qteObjet;
	ajouterMenu(&objetObtenu);
	
	if(IDobjet < NB_OBJETS) {
		obtenirObjet(IDobjet, qteObjet);
	}
}

unsigned int verifierObjetJetable(void) {
	unsigned int IDobjet = ordreObjets[selectionnerObjet.compteur3 + selectionnerObjet.compteur4];
	
	return attributsObjets[IDobjet]->jetable;
}

void jeterObjetJoueur(Commande* commande) {
	commande->compteur = 0;
	
	/*unsigned int* ptr = &quantitesObjets[ordreObjets[selectionnerObjet.compteur3 + selectionnerObjet.compteur4]];
	*ptr -= entreeEntier;
	
	if((signed int)*ptr < 0) {
		*ptr = 0;
	}*/
	obtenirObjet(ordreObjets[selectionnerObjet.compteur3 + selectionnerObjet.compteur4], -entreeEntier);
}

