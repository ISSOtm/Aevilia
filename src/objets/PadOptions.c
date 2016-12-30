
// #############################
// #                           #
// #    AEVILIA SOURCE CODE    #
// #       Version 0.3.0       #
// #                           #
// #   Version expérimentale,  #
// #  seulement à des fins de  #
// #     test. Probablement    #
// #  instable, utilisez-la à  #
// #   vos risques et périls.  #
// #                           #
// #############################
// ##                         ##
// ### Objet #2 - PadOptions ###
// #############################


#include "PadOptions.h"


AttribObjet obj__PadOptions							= {L"Pad Options", L"Pour régler mes options.\1L'autonomie de la batterie est quasi-infinie.", ouvrirMenuOptions, 0, NON_JETABLE, 0};


Commande manetteNonTrouvee							= CMD_AJOUTER_MENU(NULL, 1, NULL);
Commande selectionnerManette						= CMD_FONCTION(NULL, NULL);
SDL_GameController** manettes						= NULL;
unsigned int detecterManettes(Commande* commande) {
	commande->compteur = 0;
	
	unsigned int nbManettesPotentielles = SDL_NumJoysticks();
	unsigned int nbManettes = 0;
	SDL_GameController* manette;
	LOGGER("Gestionnaire de manettes : ")
	fprintf(fichierLog, "%d manettes trouvées.", nbManettesPotentielles);
	
	if(!nbManettesPotentielles) {
		return 0;
	}
	
	manettes = calloc(sizeof(SDL_GameController*), nbManettesPotentielles);
	
	unsigned int i = 0;
	for( ; i < nbManettesPotentielles; i++) {
		if(SDL_IsGameController(i)) {
			LOGGER("Manette trouvée...")
			manette = SDL_GameControllerOpen(i);
			if(manette) {
				LOGGER("Compatible !")
				manettes[nbManettes] = manette;
				nbManettes++;
			} else {
				LOGGER("Non compatible.")
				ERROR(SDL_GetError())
			}
		}
	}
	
	return nbManettes;
}
Commande commandeDetecterManettes					= CMD_SAUTER_COND(detecterManettes, &selectionnerManette, &manetteNonTrouvee);

void ecrireVitesseTexte(Commande* commande) {
	commande->compteur = 0;
	
	if(dernierChoixMenu != 3) {
		vitesseTexte = dernierChoixMenu * 2 + 1;
	}
}
Commande modifierVitesseTexte						= CMD_FONCTION(ecrireVitesseTexte, NULL);
Commande* commandesVitesseTexte[4]					= {NULL, NULL, NULL, NULL};
wchar_t optionsVitesseTexte[4][LONG_NOM_OPTIONS]	= {L"Rapide", L"Moyen", L"Lent", L"Annuler"};
Commande choisirVitesseTexte						= CMD_OPTIONS(commandesVitesseTexte, optionsVitesseTexte, 4, &modifierVitesseTexte);
Menu menuVitesseTexte								= MENU(224, (NB_TILES_LARG - 12) * LARGEUR_TILE / 2, 4, 10, &choisirVitesseTexte);
Commande selectionnerVitesseTexte					= CMD_AJOUTER_MENU(&menuVitesseTexte, 0, NULL);
Commande* commandesOptionsModif[3]					= {&selectionnerVitesseTexte, &commandeDetecterManettes, NULL};
// J'avoue. J'ai fait exprès, pour le nom. :D
wchar_t optionsOptionsModif[3][LONG_NOM_OPTIONS]	= {L"Vitesse du texte", L"Réglages manettes", L"Annuler"};
Commande selectionOptionAmodifier					= CMD_OPTIONS(commandesOptionsModif, optionsOptionsModif, 3, NULL);
Menu menuOptions									= MENU(272, (NB_TILES_LARG - 22) * LARGEUR_TILE / 2, 2, 20, &selectionOptionAmodifier);
Commande ajouterMenuOptions							= CMD_AJOUTER_MENU(&menuOptions, 0, NULL);


unsigned int ouvrirMenuOptions(unsigned int IDmenu) {
	ajouterMenu(&menuOptions);
	return 1;
}

