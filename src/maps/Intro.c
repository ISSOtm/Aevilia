
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
// ### Map #3 - Introduction ###
// #############################


wchar_t chaineIntro[]			= L"...";
wchar_t chaineIntro0[]			= L"Lui : Ça y est !";
wchar_t chaineIntro1[]			= L"\1L'accouchement est terminé.";
wchar_t chaineIntro2[]			= L"\1Beau bébé, hein ?";
wchar_t chaineIntro3[]			= L"Elle : Alors ? C'est un garçon ?";
wchar_t chaineIntroOui1[]		= L"Heureuse pour toi.";
wchar_t chaineIntroOui2[]		= L"Lui : Je l'élèverai comme mon fils !";
wchar_t chaineIntroNon1[]		= L"Elle : Je suis désolée...";
wchar_t chaineIntroNon2[]		= L"Lui : Ce n'est pas grave.\1Je l'élèverai comme ma fille !";
wchar_t chaineIntro4[]			= L"Elle : Aussi...\1Tu as réussi à te décider sur son nom ?";
wchar_t chaineIntro5[]			= L"Lui : Ha ha ! Toujours pas !";
wchar_t chaineIntro6[]			= L"Elle : Alors je peux te faire une suggestion ?";
wchar_t chaineIntro7[]			= L"\1\4.";
wchar_t chaineIntro8[]			= L"\1Tu aimes ?\1";
wchar_t chaineIntro9_Oui[]		= L"Lui : Oui ! Ça me plaît.";
wchar_t chaineIntro9_Non0[]		= L"Lui : Hmm... ça m'a donné une autre idée...\1";
wchar_t chaineIntro9_Non1[]		= L".\1Qu'en penses-tu ?";
wchar_t chaineIntro9_Non2[]		= L"Elle : J'aime bien.";
wchar_t chaineIntro9_Non3[]		= L"Elle : C'est exactement ce que j'avais\1proposé ! Enfin, chéri...";
wchar_t chaineIntro9_Non4[]		= L"Lui : Je m'amuse avec toi, ma belle !";
wchar_t chaineIntro10[]			= L"Lui : Aujourd'hui est le jour de la naissance\1de m\2 petit\3 \4 !";
wchar_t chaineIntro11[]			= L"\1On se doit de fêter ça, mon amour...";
wchar_t chaineIntro12[]			= L"... et voilà.";
wchar_t chaineIntro13[]			= L"\1Voilà ce que sont mes parents pour moi.";
wchar_t chaineIntro14[]			= L"\1Deux souvenirs. Deux voix.";
wchar_t chaineIntro15[]			= L"\1Et un nom.";
wchar_t chaineIntro16[]			= L"\1\4.";
wchar_t chaineIntro17[]			= L"\1Je trouve ça plutôt triste, que l'une\1des rares choses auxquelles je me rattache...";
wchar_t chaineIntro18[]			= L"\1soit absente.";
wchar_t chaineIntro19[]			= L"Mais bon, ce n'est pas sur un passé pareil\1que j'ai bâti ma vie.";

Commande commandeIntro58		= CMD_PAUSE(300, NULL);
Commande commandeIntro57		= CMD_CHAINE(chaineIntro, &commandeIntro58);
Commande commandeIntro56		= CMD_EFFACER(&commandeIntro57);
Menu suspensionIntro			= TEXTBOX(&commandeIntro56);

Commande commandeIntro78		= CMD_CHAINE(chaineIntro19, &attendreEtTerminer);
Commande commandeIntro77		= CMD_EFFACER(&commandeIntro78);
Commande commandeIntro76		= CMD_ATTENDRE(&commandeIntro77);
Commande commandeIntro75		= CMD_CHAINE(chaineIntro18, &commandeIntro76);
Commande commandeIntro74		= CMD_PAUSE(120, &commandeIntro75);
Commande commandeIntro73		= CMD_CHAINE(chaineIntro17, &commandeIntro74);
Commande commandeIntro72		= CMD_ATTENDRE(&commandeIntro73);
Commande commandeIntro71		= CMD_CHAINE(chaineIntro16, &commandeIntro72);
Commande commandeIntro70		= CMD_PAUSE(30, &commandeIntro71);
Commande commandeIntro69		= CMD_CHAINE(chaineIntro15, &commandeIntro70);
Commande commandeIntro68		= CMD_ATTENDRE(&commandeIntro69);
Commande commandeIntro67		= CMD_CHAINE(chaineIntro14, &commandeIntro68);
Commande commandeIntro66		= CMD_ATTENDRE(&commandeIntro67);
Commande commandeIntro65		= CMD_CHAINE(chaineIntro13, &commandeIntro66);
Commande commandeIntro64		= CMD_ATTENDRE(&commandeIntro65);
Commande commandeIntro63		= CMD_CHAINE(chaineIntro12, &commandeIntro64);
Commande commandeIntro62		= CMD_PAUSE(150, &commandeIntro63);
Commande commandeIntro61		= CMD_EFFACER(&commandeIntro62);
Commande commandeIntro60		= CMD_ATTENDRE(&commandeIntro61);
Commande commandeIntro59		= CMD_CHAINE(chaineIntro11, &commandeIntro60);
Commande commandeIntro55		= CMD_ATTENDRE(&commandeIntro59);
Commande commandeIntro54		= CMD_CHAINE(chaineIntro10, &commandeIntro55);
Commande commandeIntro53		= CMD_EFFACER(&commandeIntro54);
Commande commandeIntro52		= CMD_ATTENDRE(&commandeIntro53);
Commande commandeIntro51		= CMD_CHAINE(chaineIntro9_Non2, &commandeIntro52);
Commande commandeIntro50		= CMD_CHAINE(chaineIntro9_Non4, &commandeIntro52);
Commande commandeIntro49		= CMD_EFFACER(&commandeIntro50);
Commande commandeIntro48		= CMD_ATTENDRE(&commandeIntro49);
Commande commandeIntro47		= CMD_CHAINE(chaineIntro9_Non3, &commandeIntro48);
unsigned int comparerNoms(void) {
	wchar_t nomChuckMode[]		= L"Norris\0";
	wchar_t nomModeAstley[]		= L"Astley\0";
	wchar_t nomModeKaizo[]		= L"Kaizo\0";
	
	if(wcscmp(entreeUtilisateur, nomChuckMode) == 0) {
		ALLUMER_FLAG(CHUCK_NORRIS_MODE); // Mieux que le God Mode.
	} else if(wcscmp(entreeUtilisateur, nomModeAstley) == 0) {
		ALLUMER_FLAG(MODE_ASTLEY); // Met le texte random :P
	} else if(wcscmp(entreeUtilisateur, nomModeKaizo) == 0) {
		ALLUMER_FLAG(MODE_KAIZO); // Met le joueur à 1 PV perma :D
	} else if (wcscmp(nomJoueur, entreeUtilisateur) == 0) {
		return 0; // Même nom que celui qu'elle avait proposé. Go vers le script spécial !
	}
	wcscpy(nomJoueur, entreeUtilisateur);
	return 1;
}
Commande commandeIntro46		= CMD_SAUTER_COND(comparerNoms, &commandeIntro51, &commandeIntro47);
Commande commandeIntro45		= CMD_EFFACER(&commandeIntro46);
Commande commandeIntro44		= CMD_ATTENDRE(&commandeIntro45);
Commande commandeIntro43		= CMD_CHAINE(chaineIntro9_Non1, &commandeIntro44);
Commande commandeIntro42		= CMD_CHAINE(entreeUtilisateur, &commandeIntro43);
Commande commandeIntro41		= CMD_EFFACER(&commandeIntro42);
Commande commandeEntrerNom		= CMD_ENTREE(LONG_NOM_JOUEUR - 1, NULL);
Menu entrerNom					= CLAVIER(4, 4, &commandeEntrerNom);
Commande commandeIntro40		= CMD_AJOUTER_MENU(&entrerNom, 0, &commandeIntro41);
Commande commandeIntro39		= CMD_ATTENDRE(&commandeIntro40);
Commande commandeIntro38		= CMD_CHAINE(chaineIntro9_Non0, &commandeIntro39);
Commande commandeIntro37		= CMD_EFFACER(&commandeIntro38);
Commande commandeIntro36		= CMD_CHAINE(chaineIntro9_Oui, &commandeIntro52);
Commande commandeIntro35		= CMD_EFFACER(&commandeIntro36);
unsigned int __attribute__ ((pure)) sexeChoisi(void) {
	return dernierChoixMenu;
}
Commande commandeIntro34		= CMD_SAUTER_COND(sexeChoisi, &commandeIntro37, &commandeIntro35);
Commande* choixSexe[2]			= {NULL, NULL};
Commande commandeAccepterNom	= CMD_OPTIONS(choixSexe, chainesOuiNon, 2, NULL);
Menu accepterNom				= MENU(HAUTEUR_FENETRE - 8 * HAUTEUR_TILE, 0, 2, 6, &commandeAccepterNom);
Commande commandeIntro33		= CMD_AJOUTER_MENU(&accepterNom, 0, &commandeIntro34);
Commande commandeIntro32		= CMD_CHAINE(chaineIntro8, &commandeIntro33);
Commande commandeIntro31		= CMD_ATTENDRE(&commandeIntro32);
Commande commandeIntro30		= CMD_CHAINE(chaineIntro7, &commandeIntro31);
Commande commandeIntro29		= CMD_ATTENDRE(&commandeIntro30);
Commande commandeIntro28		= CMD_CHAINE(chaineIntro6, &commandeIntro29);
Commande commandeIntro27		= CMD_EFFACER(&commandeIntro28);
Commande commandeIntro26		= CMD_ATTENDRE(&commandeIntro27);
Commande commandeIntro25		= CMD_CHAINE(chaineIntro5, &commandeIntro26);
Commande commandeIntro24		= CMD_EFFACER(&commandeIntro25);
Commande commandeIntro23		= CMD_ATTENDRE(&commandeIntro24);
Commande commandeIntro22		= CMD_CHAINE(chaineIntro4, &commandeIntro23);
Commande commandeIntro21		= CMD_EFFACER(&commandeIntro22);
Commande commandeIntro20		= CMD_ATTENDRE(&commandeIntro21);
Commande commandeIntro19		= CMD_CHAINE(chaineIntroNon2, &commandeIntro20);
Commande commandeIntro18		= CMD_EFFACER(&commandeIntro19);
Commande commandeIntro17		= CMD_ATTENDRE(&commandeIntro18);
Commande commandeIntro16		= CMD_CHAINE(chaineIntroNon1, &commandeIntro17);
Commande commandeIntro15		= CMD_CHAINE(chaineIntroOui2, &commandeIntro20);
Commande commandeIntro14		= CMD_EFFACER(&commandeIntro15);
Commande commandeIntro13		= CMD_ATTENDRE(&commandeIntro14);
Commande commandeIntro12		= CMD_CHAINE(chaineIntroOui1, &commandeIntro13);
Commande commandeIntro11		= CMD_SAUTER_COND(sexeChoisi, &commandeIntro16, &commandeIntro12);
Commande commandeIntro10		= CMD_EFFACER(&commandeIntro11);
wchar_t nomsDefaut[2][LONG_NOM_JOUEUR] = {L"Ness", L"Paula"};
void enregistrerSexe(Commande* commande) {
	commande->compteur = 0;
	sexeJoueur = dernierChoixMenu;
	wcscpy(nomJoueur, nomsDefaut[dernierChoixMenu]);
}
Commande enregistrerSexeIntro	= CMD_FONCTION(enregistrerSexe, NULL);
Commande commandeSexe			= CMD_OPTIONS(choixSexe, chainesOuiNon, 2, &enregistrerSexeIntro);
Menu choisirSexeIntro			= MENU(HAUTEUR_FENETRE - 8 * HAUTEUR_TILE, 0, 2, 6, &commandeSexe);
Commande commandeIntro9			= CMD_AJOUTER_MENU(&choisirSexeIntro, 0, &commandeIntro10);
Commande commandeIntro8			= CMD_CHAINE(chaineIntro3, &commandeIntro9);
Commande commandeIntro7			= CMD_EFFACER(&commandeIntro8);
Commande commandeIntro6			= CMD_ATTENDRE(&commandeIntro7);
Commande commandeIntro5			= CMD_CHAINE(chaineIntro2, &commandeIntro6);
Commande commandeIntro4			= CMD_ATTENDRE(&commandeIntro5);
Commande commandeIntro3			= CMD_CHAINE(chaineIntro1, &commandeIntro4);
Commande commandeIntro2			= CMD_ATTENDRE(&commandeIntro3);
Commande commandeIntro1			= CMD_CHAINE(chaineIntro0, &commandeIntro2);
Commande commandeIntro0			= CMD_EFFACER(&commandeIntro1);
Menu dialogueIntro				= TEXTBOX(&commandeIntro0);

unsigned int warperFinIntro(void) {
	WARPER(TEST, 0);
	return 0;
}
ElemCinematique elemIntro7		= ACTION_FONCTION(warperFinIntro, NULL);
ElemCinematique elemIntro6		= ACTION_ATTENDRE(16, &elemIntro7);
ElemCinematique elemIntro5		= ACTION_ATTENDRE_MENU(&elemIntro6);
ElemCinematique elemIntro4		= ACTION_MENU(&dialogueIntro, &elemIntro5);
ElemCinematique elemIntro3		= ACTION_ATTENDRE(75, &elemIntro4);
ElemCinematique elemIntro2		= ACTION_ATTENDRE_MENU(&elemIntro3);
ElemCinematique elemIntro1		= ACTION_MENU(&suspensionIntro, &elemIntro2);

void chargement_Intro(void) {
	ETEINDRE_FLAG(AFFICHER_BARRE_ETAT);
	actionEnCours = &elemIntro1;
}

Map enTete_Intro =  {.fichiersCouches = {"Intro_0.layr"},
					 .nbCouches = 1,
					 .fichierSprites = "./sprites/Intro.spr",
					 .scriptChargement = chargement_Intro};

void enregistrerIntro(void) {
	enTetes[INTRO] = &enTete_Intro;
}

