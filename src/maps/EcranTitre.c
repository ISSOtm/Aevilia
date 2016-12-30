
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
// #### Map 1 - Écran Titre ####
// #############################


unsigned char quitterEcranTitre;
unsigned char sauvegardeAcharger;


extern Menu selectionJeu;
extern Menu selectContEcranTitre;
unsigned int chargerSauv(Commande* commande) {
	commande->compteur = 0;
	
	if(memcmp(sauvegardes[dernierChoixMenu].version, version, sizeof(version)) != 0 || calculerChecksum(dernierChoixMenu) != sauvegardes[dernierChoixMenu].checksum) {
		return 0; // Échec du chargement.
	}
	
	sauvegardeAcharger = dernierChoixMenu;
	
/*	if(dernierChoixMenu != 3) {
		retirerMenu(&selectContEcranTitre);
	}*/
	selectionJeu.prochaineCommande = NULL;
	
	quitterEcranTitre = 1;
	
	return 1; // Succès du chargement.
}

wchar_t chaineMauvaiseSauv[]						= L"Le chargement     de la\1 sauvegarde a    échoué.";
Commande mauvaiseSauv1								= CMD_CHAINE(chaineMauvaiseSauv, &attendreEtTerminer);
Commande mauvaiseSauv0								= CMD_EFFACER(&mauvaiseSauv1);

Commande chargerSauvEcranTitre						= CMD_SAUTER_COND(chargerSauv, NULL, &mauvaiseSauv0);

Commande* nullsEcranTitre[4]						= {&chargerSauvEcranTitre, &chargerSauvEcranTitre, &chargerSauvEcranTitre, NULL};
Commande continuerEcranTitre						= CMD_OPTIONS(nullsEcranTitre, sauvs, 4, NULL);
Menu selectContEcranTitre							= MENU(240, (NB_TILES_LARG - 16) * LARGEUR_TILE / 2, 4, 14, &continuerEcranTitre);
Commande selectEcranTitre							= CMD_AJOUTER_MENU(&selectContEcranTitre, 0, NULL);

Commande nouvelleEcranTitre							= CMD_OCTET(&dernierChoixMenu, NB_SAUVEGARDES, OCTET_INT, &chargerSauvEcranTitre);

Commande* commandesEcranTitre[2]					= {&selectEcranTitre, &nouvelleEcranTitre};
wchar_t optionsEcranTitre[2][LONG_NOM_OPTIONS]		= {L"  CONTINUER\1", L"NOUVELLE PARTIE"};
Commande commandeEcranTitre0						= CMD_OPTIONS(commandesEcranTitre, optionsEcranTitre, 2, &commandeEcranTitre0);
Menu selectionJeu									= MENU(208, (NB_TILES_LARG - 20) * LARGEUR_TILE / 2, 3, 18, &commandeEcranTitre0);

Warp warpRetourEcranTitre							= {HAUTEUR_FENETRE, LARGEUR_FENETRE, 0, 0, NULL, coin, NULL, -1, -1};

void chargement_EcranTitre(void) {
	ajouterMenu(&selectionJeu);
	ETEINDRE_FLAG(AFFICHER_BARRE_ETAT);
	positionVertCamera = 0;
	positionHorizCamera = 0;
	ALLUMER_FLAG(CAMERA_FIXE);
	couchesMapCourante[0].tilemap[NB_TILES_HAUT * NB_TILES_LARG - 5] += MAJEUR;
	couchesMapCourante[0].tilemap[NB_TILES_HAUT * NB_TILES_LARG - 3] += MINEUR;
	couchesMapCourante[0].tilemap[NB_TILES_HAUT * NB_TILES_LARG - 1] += BUGFIX;
	
	quitterEcranTitre = 0;
}

void script_EcranTitre(void) {
	if(quitterEcranTitre && selectionJeu.tailleHorizCourante == 0) {
		decompresserSauvegarde(sauvegardeAcharger);
		ALLUMER_FLAG(CONTROLE_JOUEUR);
		
		animation_SMB3();
		chargerMap(numMapCourante);
	}
}

Map enTete_EcranTitre =				{.fichiersCouches = {"EcranTitre_0.layr"},
									 .nbCouches = 1,
									 .warps = {&warpRetourEcranTitre},
									 .nbWarps = 1,
									 .fichierSprites = "./sprites/EcranTitre.spr",
									 .scriptChargement = chargement_EcranTitre,
									 .script = script_EcranTitre};

void enregistrerEcranTitre(void) {
	enTetes[ECRAN_TITRE] = &enTete_EcranTitre;
}

