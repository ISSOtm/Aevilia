
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
// #### Centrale à typedefs ####
// #############################


#pragma once


#include <SDL2/SDL.h>


// Décommenter cette ligne pour les passages en prod.
//	#define PRODUCTION


// Constantes de version
#define MAJEUR						0
#define MINEUR						4
#define BUGFIX						0


// Constantes de rendu.
#define RATIO						16/9
#define NB_TILES_HAUT				27 // Doit être un multiple de 9. Merci. -- La Direction
#define NB_TILES_LARG				(NB_TILES_HAUT * RATIO)
#define HAUTEUR_TILE				16 // C'est un choix. Ne doit néanmoins pas excéder 32 !
#define LARGEUR_TILE				16
#define HAUTEUR_FENETRE				(NB_TILES_HAUT * HAUTEUR_TILE)
#define LARGEUR_FENETRE				(NB_TILES_LARG * LARGEUR_TILE)

#define NB_TILES_BARRE_ETAT			4
#define HAUTEUR_RENDU				(FLAG(AFFICHER_BARRE_ETAT) ? HAUTEUR_FENETRE - NB_TILES_BARRE_ETAT * HAUTEUR_TILE : HAUTEUR_FENETRE)

#define NB_ANIMATIONS				5 // Nombre d'animations programmées.
#define FRAME_MAX					8 // Plus grande FRAME_MAX qui existe. Penser à modifier si nécessaire.

#define FPS_MAX						60 // FPS maximaux.
#define INTERVALLE					1000 / FPS_MAX // Intervalle entre deux frames.


#define LONG_TEXTE_MENU				(NB_TILES_HAUT - 2) * (NB_TILES_LARG - 2) + 4

#define LONG_NOM_OPTIONS			17

// Permet d'afficher tout le texte du menu instantanément.
#define AFFICHAGE_INSTANTANE(menu)	(menu)->nbCharsArendre = LONG_TEXTE_MENU

#define LARGEUR_CLAVIER				27
#define HAUTEUR_CLAVIER				10
#define MENU_CLAVIER(vert, horiz, cmd)	{vert, horiz, HAUTEUR_CLAVIER, LARGEUR_CLAVIER, cmd}


#define NB_SAUVEGARDES				3
#define LONG_NOM_JOUEUR				10
#define FLAGS_DEFAUT				{0b00000010, 0b00000000, 0b0}


#define NB_TILES_MAX				NB_TILES_LARG * NB_TILES_HAUT * 3 * 3 // = 11664. Peut faire jusqu'à 3x3 écrans complets.
#define NB_COUCHES_MAX				4 // Nombre maximal de couches par map. 4.1 Ko max ?
#define NB_SPRITES_MAX				255 // Nombre maximal de sprites par map.
#define NB_WARPS_MAX				4 // Nombre maximal de warps par map.
#define NB_CHANGEMENTS_MAX			32
#define NB_CINEMATIQUES_MAX			5


#define LONG_NOM_OBJET				LONG_NOM_OPTIONS - 4 // Longueur maximale du nom d'un objet + 1 (pour le '\0').
#define LONG_DESCR_OBJET			256 // Longueur maximale de la description d'un objet + 1 (pour le '\0').


#define VITESSE_CAMERA				4


#define NB_ENNEMIS_MAX				5


#define PROBABLE(condition)			__builtin_expect(!!(condition), 1)
#define IMPROBABLE(condition)		__builtin_expect(!!(condition), 0)

#define PREFETCH_READONLY			0
#define PREFETCH_READWRITE			1



// Types utilisés en interne.

typedef enum {
	CONTROLE_JOUEUR, // Défaut		0
	COLLISION_ACTIVE, // Défaut		1
	CAMERA_FIXE, // Défaut			0
	AFFICHER_BARRE_ETAT, // Défaut	0
	IGNORER_SPRINT, // Défaut		0
	PLEIN_ECRAN_ACTIF, // Défaut	0
	DOUBLER_TAILLE_PIX, // Défaut	0
	DEBRIDER_FRAMES, // Défaut		0
	
	FORCER_DEFIL_TEXTE, // Défaut	0
	TEXTE_PASSE, // Défaut			0
	CHUCK_NORRIS_MODE, // Défaut	0
	MODE_ASTLEY, // Défaut			0
	MODE_KAIZO, // Défaut			0
	DESSINER_BOITE, // Défaut		0
	DETACH_SPRITE_JOUEUR, // Défaut 0
	DESACTIVER_ACCEL_GPU, // Défaut	0
	
	ACTIVER_DEBUG, // Défaut		0
	
	NB_FLAGS
} IDflag;


// Les codes de retour possibles.
typedef enum {
	SUCCES,
	ERREUR_OUVRIR_LOG,
	ERREUR_FERMER_LOG,
	ERREUR_ECRITURE_LOG,
	ERREUR_INIT_SDL,
	ERREUR_CREATION_FENETRE,
	ERREUR_CREATION_RENDU,
	ERREUR_CHARGEMENT_IMAGE,
	ERREUR_CREATION_TIMER_FRAME,
	ERREUR_SEGFAULT,
	ERREUR_ACCES_SAUVEGARDE,
	ERREUR_CHARGEMENT_SAUVEGARDES,
	ERREUR_CHARGEMENT_SPRITES,
	ERREUR_CHARGEMENT_COUCHES,
	ERREUR_OUVERTURE_FICHIER,
	
	ERREUR_INCONNUE = -1
} CodeRetour;


// Donne l'état d'une touche.
typedef enum {
	TOUCHE_RELACHEE,
	TOUCHE_ENFONCEE // DOIT valoir 1 !! Sinon, il FAUT modifier le script touches->déplacement !!
} EtatTouche;


// Utilisée pour permettre le cap à 60 fps.
typedef enum {
	FEU_ROUGE, FEU_VERT
} EtatFrame;

// Utilisée pour terminer les threads parallèles.
typedef enum {
	TERMINE, EN_COURS
} EtatJeu;



// Types graphiques.

// Simplement pour avoir une meilleure idée de ce qui est une position à l'écran.
typedef unsigned int PosPixel;


// Contient les informations sur une image qui va être rendue à l'écran.
typedef struct {
	char							cheminNom[FILENAME_MAX]; // Chemin + nom du fichier image.
	SDL_Texture*					texture; // Doit être à NULL si l'image n'est pas chargée.
} Image;


typedef enum {
	TRANSPARENT,
	OPAQUE,
	MOITIE_GAUCHE,
	MOITIE_DROITE,
	
	MASQUE // Par défaut.
} ModeRendu;

// Attributs d'une tile.
typedef struct {
	unsigned char					frame; // Numéro de la frame d'animation courante.
// N'est pas const pour que certains scripts (surout des cinématiques) puissent stopper des animations.
	/*const */unsigned char			frameMax; // Numéro de la dernière frame d'animation.
	const unsigned int				freqAnim; // Plus ce nombre est élevé, moins la tile est animée rapidement. Je recommande des puissances de deux, mais whatevs.
	const unsigned char				collision; // Les 4 derniers bits donnent la collision de la tile. A voir ce qu'on fait des 4 autres. NB : le unsigned sert à éviter des différences d'implémentation.
} AttribTile;
#define ATTRIB(frames, freq, coll)	{0, frames, freq, coll}

typedef struct {
	const ModeRendu					modeRendu; // Le mode de rendu utilisé.
	unsigned int					(*transparence[FRAME_MAX])[HAUTEUR_TILE]; // Masque de transparence.
} Transparence;


// Liste des noms de tiles.
typedef enum {
	TRANSPARENT_MARCHE,
	TRANSPARENT_BLOQUE,
	BARRE_DEFILANTE,
	TEST_T,
	TEST_E,
	TEST_S,
	TEST_T_ROUGE,
	COIN_HAUT_GAUCHE,
	COIN_HAUT_DROITE,
	COIN_BAS_GAUCHE,
	COIN_BAS_DROITE, // 10
	BORD_HAUT,
	BORD_BAS,
	BORD_GAUCHE,
	BORD_DROIT,
	NOIR,
	CURSEUR,
	HERBE,
	JOUEUR_HAUT,
	JOUEUR_BAS,
	JOUEUR_GAUCHE, // 20
	JOUEUR_DROITE,
	PORTE,
	MAISON_BAS_GAUCHE,
	MAISON_BAS_DROITE,
	MAISON_BAS,
	FLECHE_HAUT,
	FLECHE_BAS,
	TOIT_GAUCHE,
	TOIT,
	TOIT_DROITE, // 30
	MAISON,
	ESPACE,
	EXCLAMATION,
	GUILLEMET,
	DIESE,
	DOLLAR,
	POURCENT,
	ESPERLUETTE,
	APOSTROPHE,
	PARENTHESE_GAUCHE, // 40
	PARENTHESE_DROITE,
	ASTERISQUE,
	PLUS,
	VIRGULE,
	TIRET,
	POINT,
	SLASH,
	ZERO,
	UN,
	DEUX, // 50
	TROIS,
	QUATRE,
	CINQ,
	SIX,
	SEPT,
	HUIT,
	NEUF,
	DEUX_POINTS,
	POINT_VIRGULE,
	CHEVRON_GAUCHE, // 60
	EGAL,
	CHEVRON_DROITE,
	INTERROGATION,
	AROBASE,
	A,
	B,
	C,
	D,
	E,
	F, // 70
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P, // 80
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z, // 90
	CROCHET_GAUCHE,
	ANTISLASH,
	CROCHET_DROIT,
	CIRCONFLEXE,
	UNDERSCORE,
	CURSEUR_VIDE,
	AMIN,
	BMIN,
	CMIN,
	DMIN, // 100
	EMIN,
	FMIN,
	GMIN,
	HMIN,
	IMIN,
	JMIN,
	KMIN,
	LMIN,
	MMIN,
	NMIN, // 110
	OMIN,
	PMIN,
	QMIN,
	RMIN,
	SMIN,
	TMIN,
	UMIN,
	VMIN,
	WMIN,
	XMIN, // 120
	YMIN,
	ZMIN,
	ACCOLADE_GAUCHE,
	TRAIT_VERTICAL,
	ACCOLADE_DROITE,
	ARBRE_HAUT_GAUCHE,
	ARBRE_MILIEU_GAUCHE,
	ARBRE_BAS_GAUCHE,
	ARBRE_HAUT_MILIEU,
	ARBRE_MILIEU_MILIEU, // 130
	ARBRE_BAS_MILIEU,
	ARBRE_HAUT_DROITE,
	ARBRE_MILIEU_DROITE,
	ARBRE_BAS_DROITE,
	TERRE,
	TABLE_HAUT_0,
	TABLE_HAUT_1,
	TABLE_HAUT_2,
	TABLE_HAUT_3,
	TABLE_HAUT_4, // 140
	TABLE_HAUT_5,
	TABLE_BAS_0,
	TABLE_BAS_1,
	TABLE_BAS_2,
	TABLE_BAS_3,
	TABLE_BAS_4,
	TABLE_BAS_5,
	FENETRE,
	MAISON_GAUCHE,
	MAISON_DROITE, // 150
	POINT_SAUVEGARDE,
	EAU_CALME,
	PLANCHES_HORIZ,
	PLANCHES_VERT,
	TRANSPARENT_NORD,
	TRANSPARENT_SUD,
	TRANSPARENT_OUEST,
	TRANSPARENT_EST,
	CHEMINEE_ALLUMEE_HAUT_GAUCHE,
	CHEMINEE_ALLUMEE_HAUT_DROITE, // 160
	CHEMINEE_ALLUMEE_BAS_GAUCHE,
	CHEMINEE_ALLUMEE_BAS_DROITE,
	PORTE_OUVERTE,
	TASSE_CAFE,
	DEMON_MAL_FAIT,
	PLANCHES_HORIZ_BAS,
	PLANCHES_VERT_DROITE,
	PANNEAU,
	TEST_JOUEUR_COMBAT_HG,
	TEST_JOUEUR_COMBAT_HD, // 170
	TEST_JOUEUR_COMBAT_BG,
	TEST_JOUEUR_COMBAT_BD,
	TEST_ZAPPER_COMBAT,
	ETOILE_SUCCES,
	HERBE_ANIMEE,
	ENCADREMENT_PORTE,
	VIDE_177,
	VIDE_178,
	VIDE_179,
	VIDE_180, // 180
	VIDE_181,
	VIDE_182,
	VIDE_183,
	VIDE_184,
	VIDE_185,
	VIDE_186,
	VIDE_187,
	VIDE_188,
	VIDE_189,
	VIDE_190, // 190
	VIDE_191,
	A_GRAVE,
	VIDE_193,
	A_CIRCONFLEXE,
	VIDE_195,
	A_TREMA,
	VIDE_197,
	VIDE_198,
	C_CEDILLE,
	E_GRAVE, // 200
	E_AIGU,
	E_CIRCONFLEXE,
	E_TREMA,
	VIDE_204,
	VIDE_205,
	I_CIRCONFLEXE,
	I_TREMA,
	VIDE_208,
	VIDE_209,
	VIDE_210, // 201
	VIDE_211,
	O_CIRCONFLEXE,
	VIDE_213,
	O_TREMA,
	MULT, // ×
	VIDE_216,
	VIDE_217,
	VIDE_218,
	U_CIRCONFLEXE,
	U_TREMA, // 220
	VIDE_221,
	VIDE_222,
	VIDE_223,
	A_GRAVE_MIN,
	VIDE_225,
	A_CIRCONFLEXE_MIN,
	VIDE_227,
	A_TREMA_MIN,
	VIDE_229,
	VIDE_230, // 230
	C_CEDILLE_MIN,
	E_GRAVE_MIN,
	E_AIGU_MIN,
	E_CIRCONFLEXE_MIN,
	E_TREMA_MIN,
	VIDE_236,
	VIDE_237,
	I_CIRCONFLEXE_MIN,
	I_TREMA_MIN,
	VIDE_240, // 240
	VIDE_241,
	VIDE_242,
	VIDE_243,
	O_CIRCONFLEXE_MIN,
	VIDE_245,
	O_TREMA_MIN,
	VIDE_247,
	VIDE_248,
	U_GRAVE_MIN,
	VIDE_250, // 250
	U_CIRCONFLEXE_MIN,
	U_TREMA_MIN,
	
	NB_TILES // 253
} IDTile;


enum {
	GARCON,
	FILLE
} Sexe;



// Les ressources pour un ParamTextureCombat.
typedef struct {
	SDL_Rect						rectSource;
	ModeRendu						modeRendu;
	unsigned char					IDmasque;
} RessourceParamTextureCombat;

// Un paramètre de rendu de texture.
typedef struct {
	SDL_Rect						rectSource;
	ModeRendu						modeRendu;
	unsigned int					(*masque)[32];
} ParamTextureCombat;


// Liste des actions pouvant être effectuées durant une animation.
typedef enum {
	TERMINER,
	PAUSE_ANIMATION,
	SAUTER_ANIMATION,
	MODIFIER_ID_ANIM_EN_COURS,
	MODIF_PARAM_ACTIF,
	DEPLACER_TEXTURE,
	MODIFIER_TAILLE_TEXTURE,
	MODIFIER_ANGLE,
	MODIFIER_CENTRE_ROTATION,
	MODIFIER_FLIP,
	
	NB_ACTIONS_ANIMATION
} IDactionAnimation;

// Une action élémentaire d'une animation.
typedef struct {
	IDactionAnimation				IDaction;
	unsigned int					argument1;
	unsigned int					argument2;
} ElemAnimTexture;

typedef struct {
#define NB_ELEM_PAR_ANIM			32
	ElemAnimTexture*				elementsAnimation[NB_ELEM_PAR_ANIM];
	unsigned int					nbElementsAnim;
	unsigned int					IDelementEnCours;
	unsigned int					timerAnim;
} Animation;

typedef struct {
	unsigned int					elementsAnimations[NB_ELEM_PAR_ANIM];
	const unsigned int				nbElementsAnim;
} RessourceAnimation;


enum {
	NB_MASQUES,
	NB_PARAMS_RENDU,
	NB_ELEMS_ANIM,
	NB_ANIMS,
	
	LONG_NB_ELEMS
};
// Les ressources communes aux TextureCombat d'un même type.
typedef struct {
	unsigned int					nbElems[LONG_NB_ELEMS];
	Image							image;
	
#define NB_MASQUES_DIFFERENTS_PAR_TEXTURE 16
	unsigned int					(*(*masques)[/*NB_MASQUES_DIFFERENTS_PAR_TEXTURE*/])[32];
#define NB_PARAMS_DIFFERENTS_PAR_TEXTURE 16
	ParamTextureCombat				paramsSource[NB_PARAMS_DIFFERENTS_PAR_TEXTURE];
	
#define NB_ELEMS_ANIM_PAR_TEXTURE	256
	ElemAnimTexture					(*elemsAnimation)[];
#define NB_ANIMATIONS_PAR_TEXTURE	16
	Animation*						animations[NB_ANIMATIONS_PAR_TEXTURE];
} RessourceTextureCombat;

// Une texture d'un protagoniste en combat.
typedef struct {
	unsigned int					IDtexture;
	Image*							img;
	unsigned int					numParamActif;
	ParamTextureCombat*				paramsSource;
	SDL_Rect						rectDest;
	double							angle;
	SDL_Point						centre;
	Animation*						animationEnCours;
	unsigned int					IDanimEnCours;
	unsigned int					timerAnim;
} TextureCombat;


// Un protagoniste du combat.
typedef struct {
#define NB_TEXTURES_PAR_PROTAGONISTE 16
	TextureCombat*					textures[NB_TEXTURES_PAR_PROTAGONISTE];
} Protagoniste;


typedef struct {
	const PosPixel					posVertCam;
	const PosPixel					posHorizCam;
	const PosPixel					posVertJoueur;
	const PosPixel					posHorizJoueur;
	
	const unsigned int				nbEnnemis;
	const Protagoniste*				ennemis[NB_ENNEMIS_MAX];
	const PosPixel					spawnsEnnemis[2][NB_ENNEMIS_MAX];
	
	const char						nomFichierCoucheArriere[FILENAME_MAX];
	const char						nomFichierCoucheMilieu[FILENAME_MAX];
	const char						nomFichierCoucheAvant[FILENAME_MAX];
	
	void							(*scriptFrame)(void);
} FormationBataille;



// Clés des commandes du moteur de menus.
typedef enum {
#define ENTREE										1
#define MON_MA										2
#define E_SEXE										3
#define NOM_JOUEUR									4
#define IL_ELLE										5

#define CMD_CHAINE(chaine, suiv)					{.commande = CHAINE, .pointeur = chaine, .compteur = 0, .suivante = suiv}
#define CMD_CHAINE_INSTANT(chaine, suiv)			{.commande = CHAINE, .pointeur = chaine, .compteur = 1, .suivante = suiv}
	CHAINE, // Afficher une chaîne.
	
#define CMD_PAUSE(attente, suiv)					{.commande = PAUSE, .compteur = attente, .suivante = suiv}
	PAUSE, // Attendre un certain nombre de frames.
	
#define CMD_FONCTION(fct, suiv)						{.commande = FONCTION, .fonction2 = fct, .suivante = suiv}
	FONCTION, // Écrire un octet en mémoire.
	
#define CMD_SAUTER_COND(condition, branche, suiv)	{.commande = SAUTER, .pointeur = branche, .pointeur2 = suiv, .fonction = condition}
#define CMD_SAUTER(branche)							CMD_SAUTER_COND(NULL, branche, NULL)
	SAUTER, // Continuer la lecture autre part.
	
#define CMD_APPELER_COND(condition, branche, suiv)	{.commande = APPELER, .pointeur = branche, .pointeur2 = branche, .fonction = condition, .suivante = suiv}
#define CMD_APPELER(branche, suiv)					CMD_APPELER_COND(NULL, branche, suiv)
	APPELER, // Appeler d'autres commandes (comme le fait SAUTER) puis revenir ici.
	
#define MENU_CONSERVER								0
#define MENU_FERMER									1
#define CMD_AJOUTER_MENU(menu, conserver, suiv)		{.commande = AJOUTER_MENU, .compteur = conserver, .phase = conserver, .pointeur = menu, .suivante = suiv}
	AJOUTER_MENU, // Ajouter un autre menu par-dessus celui-ci.
	
#define CMD_ATTENDRE(suiv)							{.commande = ATTENDRE, .compteur = TOUCHE_RELACHEE, .suivante = suiv}
	ATTENDRE, // Attend un appui sur VALIDER.
	
#define CMD_EFFACER(suiv)							{.commande = EFFACER, .suivante = suiv}
	EFFACER, // Efface toute la chaîne de caractères. (En fait, écrit juste un '\0' :P
	
	// ATTENTION : Les noms doivent être des chaînes de caractères de 16 de long !!
#define CMD_OPTIONS(options, noms, nbOptions, suiv)	{.commande = OPTIONS, .pointeur3 = options, .pointeur4 = noms, .compteur = nbOptions, .suivante = suiv}
	OPTIONS, // Un vrai menu, avec différents choix.
	
#define CMD_OBJET(IDobjet, quantite, suiv)			{.commande = OBJET, .compteur = IDobjet, .compteur2 = quantite, .suivante = suiv}
	OBJET, // Donner des objets.
	
#define CMD_WARPER(map, warp, suiv)					{.commande = WARPER, .compteur = map, .compteur2 = warp, .suivante = suiv}
	WARPER, // Warper. Meh.
	
#define OCTET_CHAR									0
#define OCTET_WCHAR									1
#define OCTET_INT									2
#define CMD_OCTET(ptr, valeur, type, suiv)			{.commande = OCTET, .pointeur = ptr, .compteur = valeur, .compteur2 = type, .suivante = suiv}
	OCTET, // Écrire un octet en mémoire.
	
#define CMD_FLAG(IDflag, valeur, suiv)				{.commande = EDITION_FLAG, .compteur = IDflag, .compteur2 = valeur, .suivante = suiv}
	EDITION_FLAG,
	
#define CMD_ENTREE(nbChars, suiv)					{.commande = ENTRER_TEXTE, .pointeur = chaineEntree, .compteur = nbChars, .suivante = suiv}
	ENTRER_TEXTE,
	
#define CMD_DEMANDER_ENTIER(y, x, maxNum, suiv)		{.commande = DEMANDER_ENTIER, .compteur = y, .compteur2 = x, .compteur3 = maxNum, .suivante = suiv}
	DEMANDER_ENTIER,
	
	NB_CMD
} IDCommande;

// Une commande envoyée au moteur textuel.
typedef struct Commande Commande;
struct Commande {
	const IDCommande				commande; // Indique quelle commande doit être exécutée, par sa clé.

// Arguments à la commande.
	void*							pointeur;
	void*							pointeur2;
	void*							pointeur3;
	void*							pointeur4;
	
	unsigned int					phase;
	
	unsigned int					compteur;
	unsigned int					compteur2;
	int								compteur3;
	int								compteur4;

	unsigned int					(*fonction)();
	void							(*fonction2)();

	Commande*						suivante; // Pointe vers la prochaine commande à exécuter. NULL signifie "fin".
};

// Un overlay, une boîte de dialogue, en somme.
typedef struct Menu Menu;
struct Menu {
	PosPixel						positionVert;
	PosPixel						positionHoriz;
	unsigned int					tailleVert;
	unsigned int					tailleHoriz;
	unsigned int					tailleHorizCourante;
	unsigned char					fermeture;
	wchar_t							texte[LONG_TEXTE_MENU];
	size_t							nbCharsAsauter; // Nombre de wchar_t à sauter avant de débuter le rendu.
	size_t							nbCharsArendre; // Nombre de wchar_t à rendre à l'écran.
	Commande*						commande; // Première commande à exécuter.
	Commande*						prochaineCommande; // Pour se souvenir de quelle est la commande actuelle.
	Menu*							prochainMenu; // Le prochain menu à rendre. Peut ne pas être initialisé à NULL.
};
#define MENU(y, x, h, w, commande)	{y, x, h, w, w, 0, L"\0", 0, 0, commande, commande, NULL}
// Un overlay qui convient à la commande ENTREE.
#define CLAVIER(y, x, commande)		MENU(y, x, 8, 27, commande)
// Un overlay qui prend l'entièreté du bas de l'écran, sur trois lignes.
#define TEXTBOX(commande)			MENU(HAUTEUR_FENETRE - 5 * HAUTEUR_TILE, 0, 3, NB_TILES_LARG - 2, commande)
// Un overlay qui prend tout la hauteur de l'écran.
#define VERTICAL(horiz, larg, suiv)	MENU(0, horiz, NB_TILES_HAUT - 2, larg, suiv)


// Les codes des actions des éléments de cinématiques.
typedef enum {
#define ACTION_BOUGER(direction, qte, suiv)	{BOUGER, direction, qte, NULL, NULL, suiv}
	BOUGER,
	
#define ACTION_TOUCHE(touche, suiv)			{ATTENDRE_TOUCHE, touche, 0, NULL, NULL, suiv}
	ATTENDRE_TOUCHE,
	
#define ACTION_SUIVANTE(suiv)				{SUIVANTE, 0, 0, NULL, NULL, suiv}
	SUIVANTE,
	
#define ACTION_MENU(ptrMenu, suiv)			{MENU, 0, 0, ptrMenu, NULL, suiv}
	MENU,
	
#define ACTION_ATTENDRE_MENU(suiv)			{ATTENDRE_MENU, 0, 0, NULL, NULL, suiv}
	ATTENDRE_MENU,
	
#define ACTION_DEPL_SPR(spr, dir, px, suiv)	{DEPLACER_SPR, dir, px, spr, NULL, suiv}
	DEPLACER_SPR,
	
#define ACTION_ATTENDRE(nbFrames, suiv)		{ATTENDRE_FRAMES, nbFrames, 0, NULL, NULL, suiv}
	ATTENDRE_FRAMES,
	
#define ACTION_TILE_SPR(spr, tileSpr, suiv)	{TILE_SPRITE, tileSpr, spr, NULL, NULL, suiv}
	TILE_SPRITE,
	
#define ACTION_OCTET(ptr, val, type, suiv)	{ECRIRE_OCTET, val, type, ptr, NULL, suiv}
	ECRIRE_OCTET,
	
#define ACTION_DJNZ(nbIters, boucle, suiv)	{DJNZ, nbIters, 0, boucle, suiv, NULL}
	DJNZ,
	
#define ACTION_FLAG(IDflag, valeur, suiv)	{EDITER_FLAG, IDflag, valeur, NULL, NULL, suiv}
	EDITER_FLAG,
	
#define ACTION_FONCTION(ptrFonction, suiv)	{EXEC_FONCTION, 0, 0, ptrFonction, NULL, suiv}
	EXEC_FONCTION,
	
#define ACTION_MODIF_TILE(p, t, ptr, suiv)	{MODIF_TILE, p, t, ptr, NULL, suiv}
	MODIF_TILE,
	
	
	NB_ACTIONS
} ActionCinematique;

// Un élément de cinématique.
typedef struct ElemCinematique ElemCinematique;
struct ElemCinematique {
	ActionCinematique				action;
	unsigned int					argumentUint;
	int								argumentSint;
	void*							argumentPtr1;
	void*							argumentPtr2;
	
	ElemCinematique*				elemSuivant;
};

typedef struct {
	PosPixel						positionVert;
	PosPixel						positionHoriz;
	ElemCinematique*				premierElement;
} Cinematique;


typedef enum {
	DEPLACER_SPRITE,
	CHARGER_SPRITE,
	
	TYPE_MAX
} TypeScene;
typedef struct {
	TypeScene	typeScene;
} Scene;

typedef struct {
	Image	img;
	Scene*	scenes[];
} Film;


// Noms des maps.
typedef enum {
	TEST,
	ECRAN_TITRE,
	MAISON_TEST,
	INTRO,
	ECRAN_CRASH,

	NB_MAPS // Nombre de maps programmées dans le jeu.
} NomsMaps;

// Une interaction avec un PNJ.
typedef struct Interaction Interaction;
struct Interaction {
	unsigned char					interagie;
	Commande*						commande;
	Interaction*					interactionSuivante; // NULL signifie qu'on a atteint la fin.
};
#define INTERACTION(commande, suiv) {0, commande, suiv}

typedef enum {
	TEST0,
	TEST1,
	SAUV_MAISONTEST,
	SAUV_TEST,
	TASSE_MAISONTEST,
	TEST_PANNEAU,
	TESTER_BATAILLE,
	
	NB_INTERACTIONS,
	
	
	NON_INTERACTIBLE = (unsigned int)-1
} LabelInteractions;

typedef enum {
	TEST0_0,
	TEST0_1,
	
	NB_INTERACTIONS_SAUV
} LabelInteractionsSauv;


// Définit une couche de tiles.
typedef struct {
	wchar_t							tilemap[NB_TILES_MAX]; // Tableau de numéros de tiles. Les lignes sont virtuelles.
	unsigned int					largeur; // Largeur d'une ligne.
	unsigned int					hauteur; // Nombre de lignes.
} Couche;

// Les index logiques des touches.
typedef enum {
	HAUT,
	BAS,
	GAUCHE,
	DROITE,
	// Les directions DOIVENT être les 4 premières entrées ici !!!
	VALIDER,
	ANNULER,
	INVENTAIRE,
#ifndef PRODUCTION
	TOUCHE_DEBUG,
#endif
	SPRINT,
	PLEIN_ECRAN,
#ifndef PRODUCTION
	ACTIVER_FRAME_ADV,
	AVANCER_FRAME,
#endif
	QUITTER_JEU,
	
	NB_TOUCHES
} Touche;
typedef Touche Direction; // Partagent HAUT, BAS, GAUCHE et DROITE. En plus, en cas de modification des Touches, ça reste bon.

// Définit un sprite, son rendu et son interaction.
#define SPRITE_FIXE(v, h, t, i, c)	{v, h, t, VALIDER, i, c} // Sprite qui ne se tourne pas.
typedef struct {
	PosPixel						positionVert; // Position verticale du sprite à l'écran (en pixels).
	PosPixel						positionHoriz; // Position horizontale du sprite à l'écran (en pixels).
	wchar_t							tile; // Tile du sprite.
	Direction						direction; // Direction du sprite. Mettre plus haut que DROITE empêche le sprite de se tourner.
	unsigned int					IDtableInteractions; // Numéro de la table d'Interactions associés à ce sprite.
	unsigned char					couche; // Couche de rendu du sprite.
} Sprite;

// Désigne un point d'entrée d'une map.
// Attention : le script du warp est exécuté après le chargement de la map, donc après le script de chargement de celle-ci !
typedef struct {
	PosPixel						positionVert; // Position à laquelle le warp emmène.
	PosPixel						positionHoriz;
	unsigned char					couche; // Couche destination.
	Direction						direction;
	char							(*condition)(void); // Script exécuté avant de warper ; s'il retourne false, le warp est inactif. NULL signifie que le warp est systématiquement actif.
	void							(*animation)(void); // Script chargé d'effectuer l'animation du warp. NULL n'est jamais exécuté.
	void 							(*script)(void); // Script exécuté après avoir warpé. NULL n'est jamais exécuté.
	unsigned int					mapDest;
	unsigned int					warpDest;
} Warp;

// Désigne un point où le joueur change de couche.
typedef struct {
	PosPixel						positionVert;
	PosPixel						positionHoriz;
	Direction						direction;
//	unsigned char					coucheOrigine; N'a pas encore d'utilité, mais décommenter si ça se révèle nécessaire.
	unsigned char					coucheDestination;
} ChangementCouche;

// Relie tous les éléments qui composent une map. Ce qui n'est pas fait ici l'est généralement par le script de chargement.
typedef struct {
	char							fichiersCouches[NB_COUCHES_MAX][FILENAME_MAX];
// Obsolète, remplacé par fichiersCouches.
//	Couche*							couches[NB_COUCHES_MAX]; // Tableau de pointeurs vers les couches de la map.
	unsigned char					nbCouches; // Longeur du tableau précédent / sizeof(Couche*).
	char							fichierSprites[FILENAME_MAX];
// Obsolète, replacé par fichierSprites.
//	Sprite							sprites[NB_SPRITES_MAX]; // Tableau des sprites de la map.
	unsigned int					nbSprites; // Longueur du tableau précédent / sizeof(Sprite*).
	Warp*							warps[NB_WARPS_MAX]; // Tableau de pointeurs vers les warps de la map.
	unsigned int					nbWarps; // Longueur du tableau précédent.
	ChangementCouche*				changementsCouches[NB_CHANGEMENTS_MAX];
	unsigned int					nbChangements;
	Cinematique*					cinematiques[NB_CINEMATIQUES_MAX];
	unsigned int					nbCinematiques;
	void							(*script)(void); // Script s'exécutant à chaque frame. NULL n'est jamais exécuté.
	void							(*scriptChargement)(void); // Script s'exécutant au chargement de la map. NULL n'est jamais exécuté.
	void							(*scriptBataille)(void);
} Map;


// Liste des objets.
typedef enum {
	OBJ_DEBUG,
	ZAP_JOUET,
	
	NB_OBJETS // Nombre de types d'objets implémentés.
} IDobjet;

enum {
	NON_JETABLE, JETABLE
};

// Arrange les données inhérentes à un objet.
typedef struct {
	wchar_t							nom[LONG_NOM_OBJET]; // Nom de l'objet.
	wchar_t							descr[LONG_DESCR_OBJET]; // Description de l'objet.
	unsigned int					(*utiliserObjet)(unsigned int); // Fonction appelée à l'utilisation de l'objet. Doit renvoyer le nombre d'objets après utilisation.
	int								poids; // Poids d'un objet dans l'inventaire.
	unsigned char					jetable;
	unsigned int					IDchaineJeter;
} AttribObjet;


typedef struct {
	unsigned char	version[3];
	unsigned int	map;
	PosPixel		posVertJoueur;
	PosPixel		posHorizJoueur;
	unsigned char	couche;
	PosPixel		posVertCamera;
	PosPixel		posHorizCamera;
	Direction		direction;
	unsigned int	ordreObj[NB_OBJETS + 1];
	unsigned int	qtesObj[NB_OBJETS];
	
	unsigned char	flags[(NB_FLAGS + 7) / 8];
	unsigned char	interactions[NB_INTERACTIONS_SAUV];
	unsigned int	vitesseTexte;
	
	unsigned int	PVjoueur;
	unsigned int	PVmaxJoueur;
	unsigned char	niveauJoueur;
	unsigned char	sexeJoueur;
	wchar_t			nomJoueur[LONG_NOM_JOUEUR];
	
	unsigned char	checksum;
} Sauvegarde;


