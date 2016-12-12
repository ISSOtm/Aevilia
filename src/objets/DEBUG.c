
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
// ##### Objet #0 - DEBUG ######
// #############################


#include "DEBUG.h"


wchar_t chainesOnOff[2][LONG_NOM_OPTIONS]			= {L"Activer", L"Désactiver"};

#ifndef PRODUCTION

	Commande desactiverDebugChangements				= CMD_OCTET(&__DEBUG__debuggerChangements, 0, OCTET_CHAR, NULL);
	Commande activerDebugChangements				= CMD_OCTET(&__DEBUG__debuggerChangements, 1, OCTET_CHAR, NULL);
	Commande* choixDebugChangements[]				= {&activerDebugChangements, &desactiverDebugChangements};
	Commande choisirDebugChangements				= CMD_OPTIONS(choixDebugChangements, chainesOnOff, 2, NULL);
	Menu menuDebuggerChangements					= MENU(0, 11 * LARGEUR_TILE, 2, 13, &choisirDebugChangements);
	Commande ajouterMenuDebuggerChangements			= CMD_AJOUTER_MENU(&menuDebuggerChangements, MENU_CONSERVER, NULL);

	Commande desactiverDebugWarps					= CMD_OCTET(&__DEBUG__debuggerWarps, 0, OCTET_CHAR, NULL);
	Commande activerDebugWarps						= CMD_OCTET(&__DEBUG__debuggerWarps, 1, OCTET_CHAR, NULL);
	Commande* choixDebugWarps[]						= {&activerDebugWarps, &desactiverDebugWarps};
	Commande choisirDebugWarps						= CMD_OPTIONS(choixDebugWarps, chainesOnOff, 2, NULL);
	Menu menuDebuggerWarps							= MENU(0, 11 * LARGEUR_TILE, 2, 13, &choisirDebugWarps);
	Commande ajouterMenuDebuggerWarps				= CMD_AJOUTER_MENU(&menuDebuggerWarps, MENU_CONSERVER, NULL);

	Commande desactiverDebugSprites					= CMD_OCTET(&__DEBUG__debuggerSprites, 0, OCTET_CHAR, NULL);
	Commande activerDebugSprites					= CMD_OCTET(&__DEBUG__debuggerSprites, 1, OCTET_CHAR, NULL);
	Commande* choixDebugSprites[]					= {&activerDebugSprites, &desactiverDebugSprites};
	Commande choisirDebugSprites					= CMD_OPTIONS(choixDebugSprites, chainesOnOff, 2, NULL);
	Menu menuDebuggerSprites						= MENU(0, 11 * LARGEUR_TILE, 2, 13, &choisirDebugSprites);
	Commande ajouterMenuDebuggerSprites				= CMD_AJOUTER_MENU(&menuDebuggerSprites, MENU_CONSERVER, NULL);

	void _eteindreCouche(Commande* commande) {
		__DEBUG__couches[dernierChoixMenu] = NULL;
		commande->compteur = 0;
	}
	Commande eteindreCouche							= CMD_FONCTION(_eteindreCouche, NULL);
	Commande* eteindreCouches5[6]					= {&eteindreCouche, &eteindreCouche, &eteindreCouche, &eteindreCouche, &eteindreCouche, &eteindreCouche};
	wchar_t numCouches[6][LONG_NOM_OPTIONS]			= {L"0", L"1", L"2", L"3", L"4", L"5"};
	extern Commande rebouclerEteindre;
	Commande eteindreCouches						= CMD_OPTIONS(eteindreCouches5, numCouches, 6, &rebouclerEteindre);
	Menu menuEteindreCouches						= MENU(HAUTEUR_TILE, 12 * LARGEUR_TILE, 5, 12, &eteindreCouches);
	Commande ajouterMenuEteindreCouches				= CMD_AJOUTER_MENU(&menuEteindreCouches, MENU_CONSERVER, NULL);
	unsigned int rebouclerEteindreCouches(void) {
		return eteindreCouches.pointeur2 == NULL;
	}
	Commande rebouclerEteindre						= CMD_SAUTER_COND(rebouclerEteindreCouches, NULL, &eteindreCouches);
	void allumerDebugMap(Commande* commande) {
		commande->compteur = 0;
		__DEBUG__debuggerCouches = 1;
		unsigned int i = 0;
		for( ; i < NB_COUCHES_MAX; i++) {
			__DEBUG__couches[i] = &couchesMapCourante[i];
		}
		eteindreCouches.compteur = enTeteMapCourante.nbCouches;
	}
	Commande desactiverDebugMap						= CMD_OCTET(&__DEBUG__debuggerCouches, 0, OCTET_CHAR, NULL);
	Commande activerDebugMap						= CMD_FONCTION(allumerDebugMap, &ajouterMenuEteindreCouches);
	Commande* choixDebugMap[]						= {&activerDebugMap, &desactiverDebugMap};
	Commande choisirDebugMap						= CMD_OPTIONS(choixDebugMap, chainesOnOff, 2, NULL);
	Menu menuDebuggerMap							= MENU(0, 11 * LARGEUR_TILE, 2, 13, &choisirDebugMap);
	Commande ajouterMenuDebuggerMap					= CMD_AJOUTER_MENU(&menuDebuggerMap, MENU_CONSERVER, NULL);
	
#endif


Commande desactiverAjustSpr							= CMD_FLAG(DETACH_SPRITE_JOUEUR, 0, NULL);
Commande activerAjustSpr							= CMD_FLAG(DETACH_SPRITE_JOUEUR, 1, NULL);
Commande* choixAjustSpr[]							= {&activerAjustSpr, &desactiverAjustSpr};
Commande choisirAjustSpr							= CMD_OPTIONS(choixAjustSpr, chainesOnOff, 2, NULL);
Menu menuAjustSpr									= MENU(0, 11 * LARGEUR_TILE, 2, 13, &choisirAjustSpr);
Commande ajouterMenuAjustSpr						= CMD_AJOUTER_MENU(&menuAjustSpr, MENU_CONSERVER, NULL);

Commande desactiverBoite							= CMD_FLAG(DESSINER_BOITE, 1, NULL);
Commande activerBoite								= CMD_FLAG(DESSINER_BOITE, 0, NULL);
Commande* choixBoite[]								= {&activerBoite, &desactiverBoite};
Commande choisirBoite								= CMD_OPTIONS(choixBoite, chainesOnOff, 2, NULL);
Menu menuBoite										= MENU(0, 11 * LARGEUR_TILE, 2, 13, &choisirBoite);
Commande ajouterMenuBoite							= CMD_AJOUTER_MENU(&menuBoite, MENU_CONSERVER, NULL);

Commande desactiverDebridage						= CMD_FLAG(DEBRIDER_FRAMES, 0, NULL);
Commande activerDebridage							= CMD_FLAG(DEBRIDER_FRAMES, 1, NULL);
Commande* choixDebridage[]							= {&activerDebridage, &desactiverDebridage};
Commande choisirDebridage							= CMD_OPTIONS(choixDebridage, chainesOnOff, 2, NULL);
Menu menuDebridage									= MENU(0, 11 * LARGEUR_TILE, 2, 13, &choisirDebridage);
Commande ajouterMenuDebridage						= CMD_AJOUTER_MENU(&menuDebridage, MENU_CONSERVER, NULL);

Commande desactiverCollision						= CMD_FLAG(COLLISION_ACTIVE, 0, NULL);
Commande activerCollision							= CMD_FLAG(COLLISION_ACTIVE, 1, NULL);
Commande* choixCollision[]							= {&activerCollision, &desactiverCollision};
Commande choisirCollision							= CMD_OPTIONS(choixCollision, chainesOnOff, 2, NULL);
Menu menuCollision									= MENU(0, 11 * LARGEUR_TILE, 2, 13, &choisirCollision);
Commande ajouterMenuCollision						= CMD_AJOUTER_MENU(&menuCollision, MENU_CONSERVER, NULL);

Commande desactiverBarreStatut						= CMD_FLAG(AFFICHER_BARRE_ETAT, 0, NULL);
Commande activerBarreStatut							= CMD_FLAG(AFFICHER_BARRE_ETAT, 1, NULL);
Commande* choixBarreStatut[]						= {&activerBarreStatut, &desactiverBarreStatut};
Commande choisirBarreStatut							= CMD_OPTIONS(choixBarreStatut, chainesOnOff, 2, NULL);
Menu menuBarreStatut								= MENU(0, 11 * LARGEUR_TILE, 2, 13, &choisirBarreStatut);
Commande ajouterMenuBarreStatut						= CMD_AJOUTER_MENU(&menuBarreStatut, MENU_CONSERVER, NULL);

Commande warper										= CMD_FONCTION(_warper, NULL);

Commande* choixIDwarp[NB_WARPS_MAX]					= {[0 ... NB_WARPS_MAX - 1] = &warper};
wchar_t nomsWarps[NB_WARPS_MAX][LONG_NOM_OPTIONS]	= {L"0", L"1", L"2", L"3"};
Commande choisirIDwarp								= CMD_OPTIONS(choixIDwarp, nomsWarps, 0, NULL);
Menu choixWarp										= MENU(HAUTEUR_TILE, LARGEUR_TILE * 12, 6, 10, &choisirIDwarp);

Commande ajouterChoixWarp							= CMD_AJOUTER_MENU(&choixWarp, MENU_CONSERVER, NULL);
Commande determinerNbWarps							= CMD_FONCTION(_determinerNbWarps, &ajouterChoixWarp);

Commande* selectionMap[NB_MAPS]						= {[0 ... NB_MAPS - 1] = &determinerNbWarps};
wchar_t nomsMaps[NB_MAPS][LONG_NOM_OPTIONS]			= {L"TEST", L"Écran titre", L"Maison TEST", L"Intro", L"Écran crash"};
Commande selectionnerMap							= CMD_OPTIONS(selectionMap, nomsMaps, NB_MAPS, NULL);

Menu warps											= MENU(0, 11 * LARGEUR_TILE, NB_MAPS, LONG_NOM_OPTIONS + 2, &selectionnerMap);
Commande demarrerWarps								= CMD_AJOUTER_MENU(&warps, MENU_CONSERVER, NULL);

void _warper(Commande* commande) {
	commande->compteur = 0;
	
	WARPER(selectionnerMap.compteur3 + selectionnerMap.compteur4, dernierChoixMenu);
}

void _determinerNbWarps(Commande* commande) {
	commande->compteur = 0;
	choisirIDwarp.compteur = enTetes[dernierChoixMenu]->nbWarps;
}



unsigned char IDobjetGestion						= 0;
unsigned char vraiIDobjetGestion					= 0;

Commande realiserOperation							= CMD_FONCTION(gestionObjetsValiderQte, NULL);
extern Commande modifierQteChoisie;
Commande qteChoisie									= CMD_SAUTER_COND(validerEnfonce, &realiserOperation, &modifierQteChoisie);
wchar_t choixQte[]									= L"Vous avez   00\1OBJETS       \1Combien ?\1   ";
Commande gererQtes									= CMD_CHAINE(choixQte, &qteChoisie);
Commande effacerChoixQte							= CMD_EFFACER(&gererQtes);
Commande modifierQteChoisie							= CMD_FONCTION(retracerChoixQte, &effacerChoixQte);
extern Commande attendreValiderRelachee;
Commande attendreValiderRelachee					= CMD_SAUTER_COND(validerEnfonce, &attendreValiderRelachee, &modifierQteChoisie);

extern Commande modifierIDchoisi;
Commande objetChoisi								= CMD_SAUTER_COND(validerEnfonce, &attendreValiderRelachee, &modifierIDchoisi);
wchar_t choixObjet[]								= L"Choisissez votre objet\1 00\1OBJETS";
Commande gererObjets								= CMD_CHAINE(choixObjet, &objetChoisi);
Commande effacerChoixObjet							= CMD_EFFACER(&gererObjets);
Commande modifierIDchoisi							= CMD_FONCTION(retracerChoix, &effacerChoixObjet);
Commande scriptsGestion								= CMD_FONCTION(pousserScriptsChoix, &modifierIDchoisi);
Menu gestionObjets									= MENU(11 * LARGEUR_TILE, 0, 6, 11, &scriptsGestion);
Commande demarrerGestionObjets						= CMD_AJOUTER_MENU(&gestionObjets, MENU_FERMER, NULL);


#ifndef PRODUCTION
Commande* commandes0[]								= {&demarrerGestionObjets, &demarrerWarps, &ajouterMenuBarreStatut, &ajouterMenuCollision, &ajouterMenuDebridage, &ajouterMenuBoite, &ajouterMenuDebuggerMap, &ajouterMenuDebuggerSprites, &ajouterMenuDebuggerWarps, &ajouterMenuDebuggerChangements, NULL};
wchar_t noms0[][LONG_NOM_OPTIONS]					= {L"OBJETS", L"WARPER", L"BARRE ETAT", L"COLLISION", L"DEBRIDER", L"BOITE", L"DEBUG MAP", L"DEBUG SPR", L"DEBUG WARPS", L"DEBUG CHGMT", L"ANNULER"};
Commande commandeDebug								= CMD_OPTIONS(commandes0, noms0, 11, NULL);
#else
Commande* commandes0[]								= {&demarrerGestionObjets, &demarrerWarps, &ajouterMenuBarreStatut, &ajouterMenuCollision, &ajouterMenuDebridage, &ajouterMenuBoite, NULL};
wchar_t noms0[][LONG_NOM_OPTIONS]					= {L"OBJETS", L"WARPER", L"BARRE ETAT", L"COLLISION", L"DEBRIDER", L"BOITE", L"ANNULER"};
Commande commandeDebug								= CMD_OPTIONS(commandes0, noms0, 5, NULL);
#endif
Menu menuDebug0 									= VERTICAL(0, 14, &commandeDebug);

Menu* menusDebug[]									= {&menuDebug0};



void gestionObjetsValiderQte(Commande* commande) {
	commande->compteur = 0;
	obtenirObjet((unsigned int)vraiIDobjetGestion, IDobjetGestion - quantitesObjets[(unsigned int)vraiIDobjetGestion]);
	popperScript(HAUT);
	popperScript(BAS);
	popperScript(GAUCHE);
	popperScript(DROITE);
}
void retracerChoixQte(Commande* commande) {
	commande->compteur = 0;
	commande->suivante = &effacerChoixQte;
	
	choixQte[11] = L' ';
	ecrireNombre(quantitesObjets[(unsigned int)vraiIDobjetGestion], &choixQte[12]);
	wmemset(&choixQte[15], L' ', LONG_NOM_OBJET);
	wcscpy(&choixQte[15], obtenirNomObjet(vraiIDobjetGestion));
	*(&choixQte[15] + wcslen(&choixQte[15])) = L' ';
	choixQte[39] = L' ';
	ecrireNombre(IDobjetGestion, &choixQte[40]);
	
	if(vraiIDobjetGestion >= NB_OBJETS) {
		popperScript(HAUT);
		popperScript(BAS);
		popperScript(GAUCHE);
		popperScript(DROITE);
		commande->suivante = NULL;
	}
}
unsigned int validerEnfonce(void) {
	if(etatTouches[VALIDER] == TOUCHE_ENFONCEE) {
		return 1;
	} else {
		return 0;
	}
}
void retracerChoix(Commande* commande) {
	commande->compteur = 0;
	
	vraiIDobjetGestion = IDobjetGestion;
	choixObjet[23] = ' ';
	ecrireNombre(IDobjetGestion, &choixObjet[24]);
	wmemset(&choixObjet[27], L' ', LONG_NOM_OBJET);
	wcscpy(&choixObjet[27], obtenirNomObjet(IDobjetGestion));
}

void decrementerIDchoix10(void) {
	IDobjetGestion -= 10;
}
void incrementerIDchoix10(void) {
	IDobjetGestion += 10;
}
void decrementerIDchoix(void) {
	IDobjetGestion--;
}
void incrementerIDchoix(void) {
	IDobjetGestion++;
}
void pousserScriptsChoix(Commande* commande) {
	commande->compteur = 0;
	
	pousserScript(HAUT, decrementerIDchoix10);
	pousserScript(BAS,  incrementerIDchoix10);
	pousserScript(GAUCHE, decrementerIDchoix);
	pousserScript(DROITE, incrementerIDchoix);
	
	IDobjetGestion = 0;
}


unsigned int menuDebug(unsigned int indexMenu) {
	ajouterMenu(menusDebug[indexMenu]);
#ifndef PRODUCTION
	return 1;
#else
	return 0;
#endif
}


#ifndef PRODUCTION
AttribObjet obj__DEBUG = {L"DEBUG", L"Ceci est votre outil. Il est à vous.\1Seulement à vous. Précieuuuuux...\1(Ne devenez pas mégalo non plus)", menuDebug, 0, NON_JETABLE, 0};
#else
AttribObjet obj__DEBUG = {L"DEBUG", L"À cause d'un bug, cet objet est à usage\1unique... dommage pour vous !", menuDebug, 9001, JETABLE, 0};
#endif

