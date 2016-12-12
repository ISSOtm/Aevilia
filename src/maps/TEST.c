
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
// ####### Map #0 - TEST #######
// #############################


Warp warp_TEST0					= {32, 64, 0, HAUT, NULL, animation_SMB3, NULL, 1, 0};
Warp warp_TEST1					= {34, 272, 0, BAS, NULL, sortir, afficherJoueur, 2, 0};

Cinematique ouverturePorte1		= {46, 272, &ouvrirPorteExt0};
Cinematique fermeturePorte1		= {34, 272, &fermerPorteExt0};

unsigned int __attribute__ ((pure)) possedeDEBUG(void) {
	return quantitesObjets[OBJ_DEBUG];
};
wchar_t chaineTest5[]			= L"Tu as perdu mon cadeau ?\1Désolé, je n'en ai pas d'autre...\1Mais est-il unique ? Qui sait...";
Commande parler21				= CMD_CHAINE(chaineTest5, &attendreEtTerminer);
wchar_t chaineTest4[]			= L"Mon cadeau te sert-il ?\1J'imagine bien que oui ^^\1Amuse-toi bien !";
Commande parler20				= CMD_CHAINE(chaineTest4, &attendreEtTerminer);
Commande sauter20				= CMD_SAUTER_COND(possedeDEBUG, &parler20, &parler21);
Interaction interaction2		= INTERACTION(&sauter20, NULL);

wchar_t chaineTest3[]			= L"Cet objet, \"DEBUG\"... j'en ai perdu le mode\1d'emploi, mais il me semble très puissant.\1Fais-en bon usage.";
Commande parler10				= CMD_CHAINE(chaineTest3, &attendreEtTerminer);
Interaction interaction1		= INTERACTION(&parler10, &interaction2);

Commande donnerDEBUG			= CMD_OBJET(OBJ_DEBUG, 1, NULL);
Commande attendre02				= CMD_ATTENDRE(&donnerDEBUG);
wchar_t chaineTest2[]			= L"Oh, j'y pense ! Prends ceci.";
Commande parler02				= CMD_CHAINE(chaineTest2, &attendre02);
Commande effacer00				= CMD_EFFACER(&parler02);
Commande attendre01				= CMD_ATTENDRE(&effacer00);
wchar_t chaineTest1[]			= L"\1Première à avoir jamais été créée.\1Ça en jette, hein ?";
Commande parler01				= CMD_CHAINE(chaineTest1, &attendre01);
Commande attendre00				= CMD_ATTENDRE(&parler01);
wchar_t chaineTest0[]			= L"Bonjour.\1Je suis TEST0.";
Commande parler00				= CMD_CHAINE(chaineTest0, &attendre00);
Interaction interaction0		= INTERACTION(&parler00, &interaction1);

wchar_t chaineTest6[]			= L"Chut ! Je l'espionne...\1Je suis TEST1, l'agent secret !";
Commande parler1				= CMD_CHAINE(chaineTest6, &attendreEtTerminer);
Interaction interaction3		= INTERACTION(&parler1, NULL);

wchar_t chaineSauvTEST[]		= L"Cet endroit respire la tranquilité.\1";
Commande sauv_TEST				= CMD_CHAINE(chaineSauvTEST, &voulezVousSauvegarder);
Interaction sauv__TEST			= INTERACTION(&sauv_TEST, NULL);

wchar_t chaineTestPanneau[]		= L"Pont sur l'étang Kwaï.\1                        \1... Vous vous attendiez à quoi ?";
Commande texteTestPanneau		= CMD_CHAINE(chaineTestPanneau, &attendreEtTerminer);
Interaction testPanneau			= INTERACTION(&texteTestPanneau, NULL);

void chargerBatailleTest(Commande* commande) {
	commande->compteur = 0;
	
	numFormationBataille = 0;
}
wchar_t chaineTestBataille[]	= L"J'suis un démon vraiment mal fait.\1ET ÇA ME MET EN ROGNE !!\1Quoi ? Tu veux te battre ?";
extern Commande commandeTestBataille0;
extern Commande commandeTestBataille1;
extern Commande commandeTestBataille2;
extern Commande commandeTestBataille3;
Menu menuTestBatailleOuiNon		= MENU(HAUTEUR_FENETRE - 8 * HAUTEUR_TILE, 0, 2, 6, &commandeTestBataille2);
Commande commandeTestBataille0	= CMD_CHAINE(chaineTestBataille, &commandeTestBataille1);
Commande commandeTestBataille1	= CMD_AJOUTER_MENU(&menuTestBatailleOuiNon, 1, NULL);
Commande* commandesTestBataille[2]	= {&commandeTestBataille3, NULL};
Commande commandeTestBataille2	= CMD_OPTIONS(commandesTestBataille, chainesOuiNon, 2, NULL);
Commande commandeTestBataille3	= CMD_FONCTION(chargerBatailleTest, NULL);
Interaction testerBataille		= INTERACTION(&commandeTestBataille0, NULL);

void script_TEST(void) {
	if(IDframe % 4 == 0) {
		if(spritesMapCourante[1].positionVert != 0) {
			spritesMapCourante[1].positionVert--;
		} else {
			spritesMapCourante[1].positionVert = 36;
		}
	}
}

ChangementCouche changemtPont0	= { 80,  66, DROITE, 2};
ChangementCouche changemtPont1	= { 80,  66, GAUCHE, 0};
ChangementCouche changemtPont2	= { 80, 334, GAUCHE, 2};
ChangementCouche changemtPont3	= { 80, 334, DROITE, 0};
ChangementCouche changemtPont12	= { 96,  66, DROITE, 2};
ChangementCouche changemtPont13	= { 96,  66, GAUCHE, 0};
ChangementCouche changemtPont14	= { 96, 334, GAUCHE, 2};
ChangementCouche changemtPont15	= { 96, 334, DROITE, 0};

ChangementCouche changemtPont4	= {144, 400, BAS, 2};
ChangementCouche changemtPont16 = {144, 416, BAS, 2};
ChangementCouche changemtPont5	= {142, 400, HAUT, 0};
ChangementCouche changemtPont17 = {142, 416, HAUT, 0};
ChangementCouche changemtPont6	= {144, 398, GAUCHE, 0};
ChangementCouche changemtPont7	= {144, 418, DROITE, 0};
ChangementCouche changemtPont8	= {256, 400, HAUT, 2};
ChangementCouche changemtPont18 = {256, 416, HAUT, 2};
ChangementCouche changemtPont10	= {258, 400, BAS, 0};
ChangementCouche changemtPont19 = {258, 416, BAS, 0};
ChangementCouche changemtPont9	= {256, 398, GAUCHE, 0};
ChangementCouche changemtPont11	= {256, 418, DROITE, 0};


Map enTete_TEST =  {.fichiersCouches = {"TEST_0.layr", "TEST_1.layr", "TEST_2.layr"},
					.nbCouches = 3,
					.fichierSprites = "./sprites/TEST.spr",
					.nbSprites = 10,
					.warps = {&warp_TEST0, &warp_TEST1},
					.nbWarps = 2,
					.changementsCouches =  {&changemtPont0,
											&changemtPont1,
											&changemtPont2,
											&changemtPont3,
											&changemtPont4,
											&changemtPont5,
											&changemtPont6,
											&changemtPont7,
											&changemtPont8,
											&changemtPont9,
											&changemtPont10,
											&changemtPont11,
											&changemtPont12,
											&changemtPont13,
											&changemtPont14,
											&changemtPont15,
											&changemtPont16,
											&changemtPont17,
											&changemtPont18,
											&changemtPont19},
					.nbChangements = 20,
					.cinematiques		=  {&ouverturePorte1,
											&fermeturePorte1},
					.nbCinematiques = 2,
					.script = &script_TEST};

void enregistrerTEST(void) {
	enTetes[TEST]						= &enTete_TEST;
	
	tableInteractions[TEST0]			= &interaction0;
	interactionsAsauvegarder[TEST0_0]	= &interaction0;
	interactionsAsauvegarder[TEST0_1]	= &interaction1;
	
	tableInteractions[TEST1]			= &interaction3;
	
	tableInteractions[SAUV_TEST]		= &sauv__TEST;
	
	tableInteractions[TEST_PANNEAU]		= &testPanneau;
	
	tableInteractions[TESTER_BATAILLE]	= &testerBataille;
}

