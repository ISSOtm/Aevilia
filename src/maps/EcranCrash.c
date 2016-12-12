
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
// #### Map 4 - Écran crash ####
// #############################


wchar_t excusesDev0[]				= L"Hey, euh... Bonjour !\1Je suis le développeur.";
wchar_t excusesDev1[]				= L"J'ai une mauvaise nouvelle...\1Apparemment, le jeu vient de crasher.";
wchar_t excusesDev2[]				= L"\1Je me sens un peu coupable, tu vois ?\1Du coup j'aimerais éviter que ça se\1reproduise.";
wchar_t excusesDev3[]				= L"\1Donc, heu, si tu pouvais me contacter,\1ça serait super cool.";
wchar_t excusesDev4[]				= L"\1Genre, euh, comme ça je pourrai essayer\1de corriger le problème !";
wchar_t excusesDev5[]				= L"\1... C'est dur à corriger sans savoir que\1ça existe.";
wchar_t excusesDev6[]				= L"\1Désolé, je digresse.\1Mais du coup, euh, si tu me contacte...\1Faudrait que j'en sache un peu plus.";
wchar_t excusesDev7[]				= L"\1Je vais pas te demander de raconter ta vie,\1hein, juste, euh, de m'envoyer un mail.";
wchar_t excusesDev8[]				= L"\1Bon, après... dans le mail,\1j'aurais besoin de trois trucs.";
wchar_t excusesDev9[]				= L"\1Le premier, c'est que tu mette, en objet,\1\"Crash d'Aevilia\", un truc comme ça.";
wchar_t excusesDev10[]				= L"\1Le second, c'est que tu décrives \1ce que tu étais en train de faire.";
wchar_t excusesDev11[]				= L"\1Genre, euh, \"j'étais en train de parler à\1un gars dans tel bâtiment, et ça a crashé.\",\1tu vois ?";
wchar_t excusesDev12[]				= L"\1Le dernier truc, c'est que tu mette une pièce jointe.";
wchar_t excusesDev13[]				= L"\1Tu vois, dans le même dossier que le jeu,\1il doit y avoir un fichier qui s'appelle\1\"aevilia.log\".";
wchar_t excusesDev14[]				= L"\1Bah voilà. Si tu pouvais le joindre au mail,\1ça serait cool.";
wchar_t excusesDev15[]				= L"\1Mais alors, attends, parce qu'il faut avoir\1fermé le jeu avant de joindre le fichier.\1D'acc ?";
wchar_t excusesDev16[]				= L"\1J'aimerais aussi savoir quelle version du jeu tu utilise. Ça m'aide beaucoup.";
wchar_t excusesDev17[]				= L"\1Voilà, donc, euh... c'est tout, j'imagine ?";
wchar_t excusesDev18[]				= L"\1... ah, mais jsuis con, moi.";
wchar_t excusesDev19[]				= L"\1'te faut peut-être mon adresse.\1eldredhabert0@gmail.com";
wchar_t excusesDev20[]				= L"\1Bon, bah, maintenant... j'ai plus grand-chose\1à faire ici, moi.";
wchar_t excusesDev21[]				= L"\1Donc, bah, je vais y aller.\1J'espère que je ne te reverrai pas.";
wchar_t excusesDev22[]				= L"\1Sinon ça veut dire que le jeu aura\1encore crashé !\1Ça serait con, quand même.";
extern Commande commandeExcusesDev0;
extern Commande commandeExcusesDev1;
extern Commande commandeExcusesDev2;
extern Commande commandeExcusesDev3;
extern Commande commandeExcusesDev4;
extern Commande commandeExcusesDev5;
extern Commande commandeExcusesDev6;
extern Commande commandeExcusesDev7;
extern Commande commandeExcusesDev8;
extern Commande commandeExcusesDev9;
extern Commande commandeExcusesDev10;
extern Commande commandeExcusesDev11;
extern Commande commandeExcusesDev12;
extern Commande commandeExcusesDev13;
extern Commande commandeExcusesDev14;
extern Commande commandeExcusesDev15;
extern Commande commandeExcusesDev16;
extern Commande commandeExcusesDev17;
extern Commande commandeExcusesDev18;
extern Commande commandeExcusesDev19;
extern Commande commandeExcusesDev20;
extern Commande commandeExcusesDev21;
extern Commande commandeExcusesDev22;
extern Commande commandeExcusesDev23;
extern Commande commandeExcusesDev24;
extern Commande commandeExcusesDev25;
extern Commande commandeExcusesDev26;
extern Commande commandeExcusesDev27;
extern Commande commandeExcusesDev28;
extern Commande commandeExcusesDev29;
extern Commande commandeExcusesDev30;
extern Commande commandeExcusesDev31;
extern Commande commandeExcusesDev32;
extern Commande commandeExcusesDev33;
extern Commande commandeExcusesDev34;
extern Commande commandeExcusesDev35;
extern Commande commandeExcusesDev36;
extern Commande commandeExcusesDev37;
extern Commande commandeExcusesDev38;
extern Commande commandeExcusesDev39;
extern Commande commandeExcusesDev40;
extern Commande commandeExcusesDev41;
extern Commande commandeExcusesDev42;
extern Commande commandeExcusesDev43;
extern Commande commandeExcusesDev44;
extern Commande commandeExcusesDev45;
extern Commande commandeExcusesDev46;
extern Commande commandeExcusesDev47;

Commande commandeExcusesDev0		= CMD_PAUSE(30, &commandeExcusesDev1);
Commande commandeExcusesDev1		= CMD_CHAINE(excusesDev0, &commandeExcusesDev2);
Commande commandeExcusesDev2		= CMD_ATTENDRE(&commandeExcusesDev3);
Commande commandeExcusesDev3		= CMD_EFFACER(&commandeExcusesDev4);
Commande commandeExcusesDev4		= CMD_CHAINE(excusesDev1, &commandeExcusesDev5);
Commande commandeExcusesDev5		= CMD_ATTENDRE(&commandeExcusesDev6);
Commande commandeExcusesDev6		= CMD_CHAINE(excusesDev2, &commandeExcusesDev7);
Commande commandeExcusesDev7		= CMD_ATTENDRE(&commandeExcusesDev8);
Commande commandeExcusesDev8		= CMD_CHAINE(excusesDev3, &commandeExcusesDev9);
Commande commandeExcusesDev9		= CMD_ATTENDRE(&commandeExcusesDev10);
Commande commandeExcusesDev10		= CMD_CHAINE(excusesDev4, &commandeExcusesDev11);
Commande commandeExcusesDev11		= CMD_ATTENDRE(&commandeExcusesDev12);
Commande commandeExcusesDev12		= CMD_CHAINE(excusesDev5, &commandeExcusesDev13);
Commande commandeExcusesDev13		= CMD_ATTENDRE(&commandeExcusesDev14);
Commande commandeExcusesDev14		= CMD_CHAINE(excusesDev6, &commandeExcusesDev15);
Commande commandeExcusesDev15		= CMD_ATTENDRE(&commandeExcusesDev16);
Commande commandeExcusesDev16		= CMD_CHAINE(excusesDev7, &commandeExcusesDev17);
Commande commandeExcusesDev17		= CMD_ATTENDRE(&commandeExcusesDev18);
Commande commandeExcusesDev18		= CMD_CHAINE(excusesDev8, &commandeExcusesDev19);
Commande commandeExcusesDev19		= CMD_ATTENDRE(&commandeExcusesDev20);
Commande commandeExcusesDev20		= CMD_CHAINE(excusesDev9, &commandeExcusesDev21);
Commande commandeExcusesDev21		= CMD_ATTENDRE(&commandeExcusesDev22);
Commande commandeExcusesDev22		= CMD_CHAINE(excusesDev10, &commandeExcusesDev23);
Commande commandeExcusesDev23		= CMD_ATTENDRE(&commandeExcusesDev24);
Commande commandeExcusesDev24		= CMD_CHAINE(excusesDev11, &commandeExcusesDev25);
Commande commandeExcusesDev25		= CMD_ATTENDRE(&commandeExcusesDev26);
Commande commandeExcusesDev26		= CMD_CHAINE(excusesDev12, &commandeExcusesDev27);
Commande commandeExcusesDev27		= CMD_ATTENDRE(&commandeExcusesDev28);
Commande commandeExcusesDev28		= CMD_CHAINE(excusesDev13, &commandeExcusesDev29);
Commande commandeExcusesDev29		= CMD_ATTENDRE(&commandeExcusesDev30);
Commande commandeExcusesDev30		= CMD_CHAINE(excusesDev14, &commandeExcusesDev31);
Commande commandeExcusesDev31		= CMD_ATTENDRE(&commandeExcusesDev32);
Commande commandeExcusesDev32		= CMD_CHAINE(excusesDev15, &commandeExcusesDev33);
Commande commandeExcusesDev33		= CMD_ATTENDRE(&commandeExcusesDev34);
Commande commandeExcusesDev34		= CMD_CHAINE(excusesDev16, &commandeExcusesDev35);
Commande commandeExcusesDev35		= CMD_ATTENDRE(&commandeExcusesDev36);
Commande commandeExcusesDev36		= CMD_CHAINE(excusesDev17, &commandeExcusesDev37);
Commande commandeExcusesDev37		= CMD_ATTENDRE(&commandeExcusesDev38);
Commande commandeExcusesDev38		= CMD_CHAINE(excusesDev18, &commandeExcusesDev39);
Commande commandeExcusesDev39		= CMD_ATTENDRE(&commandeExcusesDev40);
Commande commandeExcusesDev40		= CMD_CHAINE(excusesDev19, &commandeExcusesDev41);
Commande commandeExcusesDev41		= CMD_ATTENDRE(&commandeExcusesDev42);
Commande commandeExcusesDev42		= CMD_CHAINE(excusesDev20, &commandeExcusesDev43);
Commande commandeExcusesDev43		= CMD_ATTENDRE(&commandeExcusesDev44);
Commande commandeExcusesDev44		= CMD_CHAINE(excusesDev21, &commandeExcusesDev45);
Commande commandeExcusesDev45		= CMD_ATTENDRE(&commandeExcusesDev46);
Commande commandeExcusesDev46		= CMD_CHAINE(excusesDev22, &attendreEtTerminer);
Menu excusesCrash					= TEXTBOX(&commandeExcusesDev0);

extern ElemCinematique laisserMijoter;
extern ElemCinematique deplacerDev;
extern ElemCinematique boucleDeplDev;
extern ElemCinematique reprendreSonSouffle;
extern ElemCinematique tournerDev;
extern ElemCinematique menuExcuses;
extern ElemCinematique attendreFinExcuses;
extern ElemCinematique legerDelai;
extern ElemCinematique fermerJeu;
ElemCinematique laisserMijoter		= ACTION_ATTENDRE(60, &deplacerDev);
ElemCinematique deplacerDev			= ACTION_DEPL_SPR(&spritesMapCourante[1], GAUCHE, 2, &boucleDeplDev);
ElemCinematique boucleDeplDev		= ACTION_DJNZ((LARGEUR_FENETRE - LARGEUR_TILE) / 4, &deplacerDev, &reprendreSonSouffle);
ElemCinematique reprendreSonSouffle	= ACTION_ATTENDRE(120, &tournerDev);
ElemCinematique tournerDev			= ACTION_DEPL_SPR(&spritesMapCourante[1], BAS, 0, &menuExcuses);
ElemCinematique menuExcuses			= ACTION_MENU(&excusesCrash, &attendreFinExcuses);
ElemCinematique attendreFinExcuses	= ACTION_ATTENDRE_MENU(&legerDelai);
ElemCinematique legerDelai			= ACTION_ATTENDRE(60, &fermerJeu);
ElemCinematique fermerJeu			= ACTION_FONCTION(terminerJeu, NULL);

Warp warp_EcranCrash				= {HAUTEUR_FENETRE, LARGEUR_FENETRE, 0, HAUT, NULL, NULL, NULL, 0, 1};

void chargement_EcranCrash(void) {
	menuArendre = NULL;
	actionEnCours = &deplacerDev;
	ETEINDRE_FLAG(AFFICHER_BARRE_ETAT);
	ETEINDRE_FLAG(CONTROLE_JOUEUR);
	ALLUMER_FLAG(CAMERA_FIXE);
	positionVertCamera = 0;
	positionHorizCamera = 0;
	spritesMapCourante[0].tile = TRANSPARENT_BLOQUE;
}

Map enTete_EcranCrash =				{.fichiersCouches = {"EcranCrash_0.layr"},
									 .nbCouches = 1,
									 .fichierSprites = "./sprites/EcranCrash.spr",
									 .nbSprites = 1,
									 .warps = {&warp_EcranCrash},
									 .nbWarps = 1,
									 .scriptChargement = chargement_EcranCrash};

void enregistrerEcranCrash(void) {
	enTetes[ECRAN_CRASH] = &enTete_EcranCrash;
}

