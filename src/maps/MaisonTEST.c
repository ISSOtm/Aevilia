
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
// #### Map #2 - Maison TEST ###
// #############################


Warp warp_MaisonTEST0			= {286, 480, 0, HAUT, NULL, rentrer, afficherJoueur, 0, 1};

Cinematique ouverturePorte0		= {274, 480, &ouvrirPorteInt0};
Cinematique fermeturePorte0		= {286, 480, &fermerPorteInt0};

wchar_t chaineSauvMaisonTEST[]	= L"L'endroit est calme et chaud.\1Vous êtes reposé.\1";
Commande sauv_MaisonTEST		= CMD_CHAINE(chaineSauvMaisonTEST, &voulezVousSauvegarder);
Interaction sauv__MaisonTEST	= INTERACTION(&sauv_MaisonTEST, NULL);

wchar_t chaineTasseMaisonTEST[]	= L"Une tasse de café apparemment délicieux.\1Attention, il a l'air chaud.";
Commande texteTasseMaisonTEST	= CMD_CHAINE(chaineTasseMaisonTEST, &attendreEtTerminer);
Interaction tasse_MaisonTEST	= INTERACTION(&texteTasseMaisonTEST, NULL);


void script_MaisonTEST(void) {
	ajusterJoueur();
}

Map enTete_MaisonTEST = {.fichiersCouches = {"MaisonTEST_0.layr", "MaisonTEST_1.layr", "MaisonTEST_2.layr"},
						 .nbCouches = 3,
						 .fichierSprites = "./sprites/MaisonTEST.spr",
						 .nbSprites = 2,
						 .warps = {&warp_MaisonTEST0},
						 .nbWarps = 1,
						 .cinematiques		=  {&ouverturePorte0,
						 						&fermeturePorte0},
						 .nbCinematiques = 2,
						 .script = script_MaisonTEST};

void enregistrerMaisonTEST(void) {
	enTetes[MAISON_TEST]				= &enTete_MaisonTEST;
	
	tableInteractions[SAUV_MAISONTEST]	= &sauv__MaisonTEST;
	tableInteractions[TASSE_MAISONTEST]	= &tasse_MaisonTEST;
}

