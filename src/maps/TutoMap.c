
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
// ##### Map #5 - Tutorial #####
// #############################


extern Commande commandeTuto0;
extern Commande commandeTuto1;
extern Commande commandeTuto2;
extern Commande commandeTuto3;
extern Commande commandeTuto4;
extern Commande commandeTuto5;
extern Commande commandeTuto6;
extern Commande commandeTuto7;
extern Commande commandeTuto8;
extern Commande commandeTuto9;

wchar_t chaineTuto0[]	= L"Voici \"Toi\".";
wchar_t chaineTuto1[]	= L"Tu t'appelles \4.\1Compris ?";
wchar_t chaineTuto2[]	= L"Bien.\1Utilise les flèches du clavier pour te déplacer.";
wchar_t chaineTuto3[]	= L"Super ! Maintenant, utilise Z pour interagir.";

Commande commandeTuto0	= CMD_CHAINE(chaineTuto0, &commandeTuto1);
Commande commandeTuto1	= CMD_PAUSE(60, &commandeTuto2);
Commande commandeTuto2	= CMD_CHAINE(chaineTuto1, &commandeTuto3);
Commande commandeTuto3	= CMD_ATTENDRE(&commandeTuto4);
Commande commandeTuto4	= CMD_CHAINE(chaineTuto2, &commandeTuto5);
Commande commandeTuto5	= CMD_FLAG(CONTROLE_JOUEUR, 0, &commandeTuto6);
unsigned int rebouclerTuto6(Commande* commande) {
	return positionVertJoueur == HAUTEUR_TILE;
}
Commande commandeTuto6	= CMD_SAUTER_COND(rebouclerTuto6, &commandeTuto7, &commandeTuto6);
Commande commandeTuto7	= CMD_EFFACER(&commandeTuto8);
Commande commandeTuto8	= CMD_CHAINE(chaineTuto3, &attendreEtTerminer);

Menu boiteTexteTuto		= MENU(100, 100, 3, 20, &commandeTuto0);


Map enTete_MapTuto		= { .fichiersCouches = {"MapTuto_0.layr"},
							.nbCouches = 1};

