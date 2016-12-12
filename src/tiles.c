
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
// ### Définitions des tiles ###
// #############################


// Ce fichier n'est destiné qu'à être inclus dans aevilia.c, afin de séparer tout ce qui est tiles du reste.
	
	LOGGER("Création des transparences...")
	
Transparence renduTransparent						= {TRANSPARENT, {}};
Transparence renduOpaque							= {OPAQUE, {}};

unsigned int masqueJoueurVert0[HAUTEUR_TILE]		= {0x0000, 0x0000, 0x0280, 0x0440, 0x0000, 0x03c0, 0x07e0, 0x0ff0, 0x1ff8, 0x1ff8, 0x1ff8, 0x1ff8, 0x0ff0, 0x07e0, 0x03c0, 0x0000};
unsigned int masqueJoueurVert1[HAUTEUR_TILE]		= {0x0280, 0x0440, 0x0000, 0x03c0, 0x07e0, 0x0ff0, 0x1ff8, 0x1ff8, 0x1ff8, 0x1ff8, 0x0ff0, 0x07e0, 0x03c0, 0x0000, 0x0000, 0x0000};
Transparence renduJoueurVert						= {MASQUE, {&masqueJoueurVert0, &masqueJoueurVert1}};

unsigned int masqueJoueurGauche0[HAUTEUR_TILE]		= {0x0000, 0x0000, 0x0400, 0x0200, 0x0000, 0x03c0, 0x07e0, 0x0ff0, 0x1ff8, 0x1ff8, 0x1ff8, 0x1ff8, 0x0ff0, 0x07e0, 0x03c0, 0x0000};
unsigned int masqueJoueurGauche1[HAUTEUR_TILE]		= {0x0400, 0x0200, 0x0000, 0x03c0, 0x07e0, 0x0ff0, 0x1ff8, 0x1ff8, 0x1ff8, 0x1ff8, 0x07f0, 0x07e0, 0x03c0, 0x0000, 0x0000, 0x0000};
Transparence renduJoueurGauche						= {MASQUE, {&masqueJoueurGauche0, &masqueJoueurGauche1}};

unsigned int masqueJoueurDroite0[HAUTEUR_TILE]		= {0x0000, 0x0000, 0x0020, 0x0040, 0x0000, 0x03c0, 0x07e0, 0x0ff0, 0x1ff8, 0x1ff8, 0x1ff8, 0x1ff8, 0x0ff0, 0x07e0, 0x03c0, 0x0000};
unsigned int masqueJoueurDroite1[HAUTEUR_TILE]		= {0x0020, 0x0040, 0x0000, 0x03c0, 0x07e0, 0x0ff0, 0x1ff8, 0x1ff8, 0x1ff8, 0x1ff8, 0x0fe0, 0x07e0, 0x03c0, 0x0000, 0x0000, 0x0000};
Transparence renduJoueurDroite						= {MASQUE, {&masqueJoueurDroite0, &masqueJoueurDroite1}};

unsigned int masqueFlecheHaut0[HAUTEUR_TILE]		= {0x0000, 0x0000, 0x0000, 0x0000, 0x0180, 0x03c0, 0x07e0, 0x0ff0, 0x1ff8, 0x3ffc, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000};
unsigned int masqueFlecheHaut1[HAUTEUR_TILE]		= {0x0000, 0x0000, 0x0000, 0x0180, 0x03c0, 0x07e0, 0x0ff0, 0x1ff8, 0x3ffc, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000};
Transparence renduFlecheHaut						= {MASQUE, {&masqueFlecheHaut0, &masqueFlecheHaut1}};

unsigned int masqueFlecheBas0[HAUTEUR_TILE]			= {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3ffc, 0x1ff8, 0x0ff0, 0x07e0, 0x03c0, 0x0180, 0x0000, 0x0000, 0x0000, 0x0000};
unsigned int masqueFlecheBas1[HAUTEUR_TILE]			= {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3ffc, 0x1ff8, 0x0ff0, 0x07e0, 0x03c0, 0x0180, 0x0000, 0x0000, 0x0000};
Transparence renduFlecheBas							= {MASQUE, {&masqueFlecheBas0, &masqueFlecheBas1}};

unsigned int masqueToitGauche[HAUTEUR_TILE]			= {0x000f, 0x003f, 0x00ff, 0x01ff, 0x03ff, 0x07ff, 0x0fff, 0x1fff, 0x3fff, 0x3fff, 0x7fff, 0x7fff, 0x7fff, 0xffff, 0xffff, 0xffff};
Transparence renduToitGauche						= {MASQUE, {&masqueToitGauche}};

unsigned int masqueToitDroite[HAUTEUR_TILE]			= {0xf000, 0xfc00, 0xff00, 0xff80, 0xffc0, 0xffe0, 0xfff0, 0xfff8, 0xfffc, 0xfffc, 0xfffe, 0xfffe, 0xfffe, 0xffff, 0xffff, 0xffff};
Transparence renduToitDroite						= {MASQUE, {&masqueToitDroite}};

unsigned int masqueHautGaucheArbre[HAUTEUR_TILE]	= {0x00ff, 0x03ff, 0x07ff, 0x07ff, 0x0fff, 0x1fff, 0x1fff, 0x1fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x3fff};
Transparence renduHautGaucheArbre					= {MOITIE_DROITE, {&masqueHautGaucheArbre}};

unsigned int masqueMilieuGaucheArbre[HAUTEUR_TILE]	= {0x3fff, 0x3fff, 0x3fff, 0x7fff, 0x7fff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x7fff, 0x7fff, 0x3fff, 0x3fff, 0x0fff, 0x0fff};
Transparence renduMilieuGaucheArbre					= {MOITIE_DROITE, {&masqueMilieuGaucheArbre}};

unsigned int masqueBasGaucheArbre[HAUTEUR_TILE]		= {0x03ff, 0x01f0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001};
Transparence renduBasGaucheArbre					= {MASQUE, {&masqueBasGaucheArbre}};

unsigned int masqueBasMilieuArbre[HAUTEUR_TILE]		= {0xffff, 0x7fff, 0x1f3f, 0x0f0f, 0x0f00, 0x0f00, 0x0f00, 0x0f00, 0x0f00, 0x0f00, 0x0f00, 0x0f80, 0x1f80, 0x3f80, 0x7fc0, 0xffe0};
Transparence renduBasMilieuArbre					= {MASQUE, {&masqueBasMilieuArbre}};

unsigned int masqueHautDroiteArbre[HAUTEUR_TILE]	= {0xff80, 0xffe0, 0xfff0, 0xfff8, 0xfffc, 0xfffc, 0xfffc, 0xfffc, 0xfffe, 0xfffe, 0xfffe, 0xfffe, 0xfffe, 0xfffc, 0xfffc, 0xfffc};
Transparence renduHautDroiteArbre					= {MOITIE_GAUCHE, {&masqueHautDroiteArbre}};

unsigned int masqueMilieuDroiteArbre[HAUTEUR_TILE]	= {0xfffe, 0xfffe, 0xfffe, 0xfffe, 0xfffe, 0xfffe, 0xfffe, 0xfffe, 0xfffc, 0xfffc, 0xfff8, 0xffe0, 0xffe0, 0xffe0, 0xffe0, 0xffc0};
Transparence renduMilieuDroiteArbre					= {MOITIE_GAUCHE, {&masqueMilieuDroiteArbre}};

unsigned int masqueBasDroiteArbre[HAUTEUR_TILE]		= {0xffc0, 0xff80, 0xff00, 0xfe00, 0x3c00, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000};
Transparence renduBasDroiteArbre					= {MASQUE, {&masqueBasDroiteArbre}};

unsigned int masqueTable0[HAUTEUR_TILE]		= {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0007, 0x001f, 0x00ff, 0x01ff, 0x01ff, 0x03ff, 0x01ff, 0x01ff, 0x00ff};
Transparence renduTable0							= {MASQUE, {&masqueTable0}};

/* J'ai retiré la transparence de TABLE_HAUT_1 et TABLE_HAUT_4 après leur avoir retiré leur collision.
Si la collision est à nouveau retirée, décommenter ces masques et modifier les entrées plus bas.

unsigned int masqueTable1[HAUTEUR_TILE]		= {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x00ff, 0x3fff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff};
Transparence renduTable1							= {MASQUE, {&masqueTable1}};

unsigned int masqueTable4[HAUTEUR_TILE]		= {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xff00, 0xfffc, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff};
Transparence renduTable4							= {MASQUE, {&masqueTable4}};*/

unsigned int masqueTable5[HAUTEUR_TILE]		= {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xc000, 0xf800, 0xfe00, 0xff00, 0xff80, 0xffc0, 0xff80, 0xff00, 0xfe00};
Transparence renduTable5							= {MASQUE, {&masqueTable5}};

unsigned int masquePointSauvegarde0[HAUTEUR_TILE]	= {0x1000, 0x3800, 0x7c00, 0xfe00, 0x7c20, 0x3870, 0x10f8, 0x01fc, 0x00f8, 0x0470, 0x0e00, 0x1f00, 0x3f80, 0x1f00, 0x0e00, 0x0400};
unsigned int masquePointSauvegarde1[HAUTEUR_TILE]	= {0x7c00, 0xfe00, 0x7c20, 0x3870, 0x10f8, 0x01fc, 0x00f8, 0x0470, 0x0e20, 0x1f00, 0x3f80, 0x1f00, 0x0e00, 0x0400, 0x1000, 0x3800};
unsigned int masquePointSauvegarde2[HAUTEUR_TILE]	= {0x7c20, 0x3870, 0x10f8, 0x01fc, 0x00f8, 0x0470, 0x0e20, 0x1f00, 0x3f80, 0x1f00, 0x0e00, 0x0400, 0x1000, 0x3800, 0x7c00, 0xfe00};
unsigned int masquePointSauvegarde3[HAUTEUR_TILE]	= {0x10f8, 0x01fc, 0x00f8, 0x0470, 0x0e20, 0x1f00, 0x3f80, 0x1f00, 0x0e00, 0x0400, 0x1000, 0x3800, 0x7c00, 0xfe00, 0x7c20, 0x3870};
unsigned int masquePointSauvegarde4[HAUTEUR_TILE]	= {0x00f8, 0x0470, 0x0e20, 0x1f00, 0x3f80, 0x1f00, 0x0e00, 0x0400, 0x1000, 0x3800, 0x7c00, 0xfe00, 0x7c20, 0x3870, 0x10f8, 0x01fc};
unsigned int masquePointSauvegarde5[HAUTEUR_TILE]	= {0x0e20, 0x1f00, 0x3f80, 0x1f00, 0x0e00, 0x0400, 0x1000, 0x3800, 0x7c00, 0xfe00, 0x7c20, 0x3870, 0x10f8, 0x01fc, 0x00f8, 0x0470};
unsigned int masquePointSauvegarde6[HAUTEUR_TILE]	= {0x3f80, 0x1f00, 0x0e00, 0x0400, 0x1000, 0x3800, 0x7c00, 0xfe00, 0x7c20, 0x3870, 0x10f8, 0x01fc, 0x00f8, 0x0470, 0x0e20, 0x1f00};
unsigned int masquePointSauvegarde7[HAUTEUR_TILE]	= {0x0e00, 0x0400, 0x1000, 0x3800, 0x7c00, 0xfe00, 0x7c20, 0x3870, 0x10f8, 0x01fc, 0x00f8, 0x0470, 0x0e20, 0x1f00, 0x3f80, 0x1f00};
Transparence renduPointSauvegarde					= {MASQUE, {&masquePointSauvegarde0, &masquePointSauvegarde1, &masquePointSauvegarde2, &masquePointSauvegarde3, &masquePointSauvegarde4, &masquePointSauvegarde5, &masquePointSauvegarde6, &masquePointSauvegarde7}};

unsigned int masquePlanchesHoriz[HAUTEUR_TILE]		= {0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x1010, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x1010};
Transparence renduPlanchesHoriz						= {MASQUE, {&masquePlanchesHoriz}};

unsigned int masquePlanchesVert[HAUTEUR_TILE]		= {0xfefe, 0xfefe, 0xfefe, 0xffff, 0xfefe, 0xfefe, 0xfefe, 0xfefe, 0xfefe, 0xfefe, 0xfefe, 0xffff, 0xfefe, 0xfefe, 0xfefe, 0xfefe};
Transparence renduPlanchesVert						= {MASQUE, {&masquePlanchesVert}};

unsigned int masqueTasseCafe0[HAUTEUR_TILE]			= {0x0000, 0x0000, 0x0000, 0x0040, 0x0000, 0x0020, 0x0080, 0x0080, 0x0000, 0x00e0, 0x01f0, 0x01f8, 0x01fc, 0x01f8, 0x01f0, 0x00e0};
unsigned int masqueTasseCafe1[HAUTEUR_TILE]			= {0x0000, 0x0000, 0x0040, 0x0000, 0x0080, 0x0000, 0x0000, 0x0020, 0x0000, 0x00e0, 0x01f0, 0x01f8, 0x01fc, 0x01f8, 0x01f0, 0x00e0};
Transparence renduTasseCafe							= {MASQUE, {&masqueTasseCafe0, &masqueTasseCafe1}};

unsigned int masquePlanchesHorizDroite[HAUTEUR_TILE]= {0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x1010, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000};
Transparence renduPlanchesHorizDroite				= {MASQUE, {&masquePlanchesHorizDroite}};

unsigned int masquePlanchesVertBas[HAUTEUR_TILE]	= {0xfefe, 0xfefe, 0xfefe, 0xfffe, 0xfefe, 0xfefe, 0xfefe, 0xfefe, 0xfefe, 0xfefe, 0xfefe, 0xfffe, 0xfefe, 0xfefe, 0xfefe, 0xfefe};
Transparence renduPlanchesVertBas					= {MASQUE, {&masquePlanchesVertBas}};

unsigned int masqueDemonMalFait[HAUTEUR_TILE]		= {0x0000, 0x0000, 0x0000, 0x1008, 0x1818, 0x1ff8, 0x0ff0, 0x0ff0, 0x1ff8, 0x1ff8, 0x1ff8, 0x1ff8, 0x0ff0, 0x07e0, 0x03c0, 0x0000};
Transparence renduDemonMalFait						= {MASQUE, {&masqueDemonMalFait}};

unsigned int masquePanneau[HAUTEUR_TILE]			= {0x7ffe, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x7ffe, 0x03c0, 0x03c0, 0x03c0, 0x03c0, 0x0180};
Transparence renduPanneau							= {MASQUE, {&masquePanneau}};

unsigned int masqueTestJoueurCombatHG[HAUTEUR_TILE]	= {0x0000, 0x000f, 0x000f, 0x001f, 0x001f, 0x001f, 0x001f, 0x001f, 0x0007, 0x0003, 0x001f, 0x0062, 0x0182, 0x0202, 0x0402, 0x0002};
Transparence renduTestJoueurCombatHG				= {MASQUE, {&masqueTestJoueurCombatHG}};

unsigned int masqueTestJoueurCombatHD[HAUTEUR_TILE]	= {0x0000, 0x0000, 0xe000, 0xe000, 0xe000, 0xe000, 0xe000, 0xe200, 0xe200, 0xc200, 0x8400, 0x7c00, 0x0000, 0x0000, 0x0000, 0x0000};
Transparence renduTestJoueurCombatHD				= {MASQUE, {&masqueTestJoueurCombatHD}};

unsigned int masqueTestJoueurCombatBG[HAUTEUR_TILE]	= {0x0002, 0x0002, 0x0003, 0x000c, 0x0010, 0x0020, 0x0040, 0x0080, 0x0300, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000};
Transparence renduTestJoueurCombatBG				= {MASQUE, {&masqueTestJoueurCombatBG}};

unsigned int masqueTestJoueurCombatBD[HAUTEUR_TILE]	= {0x0000, 0x0000, 0xf000, 0x0800, 0x0800, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000};
Transparence renduTestJoueurCombatBD				= {MASQUE, {&masqueTestJoueurCombatBD}};

unsigned int masqueEtoileSucces[HAUTEUR_TILE]		= {0x0000, 0x0100, 0x0100, 0x0380, 0x0380, 0x37c0, 0x7ffc, 0x3ff8, 0x1ff0, 0x0fe0, 0x0fe0, 0x1ff0, 0x1ef0, 0x3838, 0x3018, 0x0000};
Transparence renduEtoileSucces						= {MASQUE, {&masqueEtoileSucces}};

unsigned int masqueEncadrementPorte[HAUTEUR_TILE]	= {0x3ffc, [1 ... HAUTEUR_TILE - 1] = 0x0000};
Transparence renduEncadrementPorte					= {MASQUE, {&masqueEncadrementPorte}};
	
	transparences[TRANSPARENT_MARCHE]			= &renduTransparent;
	transparences[TRANSPARENT_BLOQUE]			= &renduTransparent;
	transparences[BARRE_DEFILANTE]				= &renduOpaque;
	transparences[TEST_T]						= &renduOpaque;
	transparences[TEST_E]						= &renduOpaque;
	transparences[TEST_S]						= &renduOpaque;
	transparences[TEST_T_ROUGE]					= &renduOpaque;
	transparences[COIN_HAUT_GAUCHE]				= &renduOpaque;
	transparences[COIN_HAUT_DROITE]				= &renduOpaque;
	transparences[COIN_BAS_GAUCHE]				= &renduOpaque;
	transparences[COIN_BAS_DROITE]				= &renduOpaque;
	transparences[BORD_HAUT]					= &renduOpaque;
	transparences[BORD_BAS]						= &renduOpaque;
	transparences[BORD_GAUCHE]					= &renduOpaque;
	transparences[BORD_DROIT]					= &renduOpaque;
	transparences[NOIR]							= &renduOpaque;
	transparences[CURSEUR]						= &renduOpaque;
	transparences[HERBE]						= &renduOpaque;
	transparences[JOUEUR_HAUT]					= &renduJoueurVert;
	transparences[JOUEUR_BAS]					= &renduJoueurVert;
	transparences[JOUEUR_GAUCHE]				= &renduJoueurGauche;
	transparences[JOUEUR_DROITE]				= &renduJoueurDroite;
	transparences[PORTE]						= &renduOpaque;
	transparences[MAISON_BAS_GAUCHE]			= &renduOpaque;
	transparences[MAISON_BAS_DROITE]			= &renduOpaque;
	transparences[MAISON_BAS]					= &renduOpaque;
	transparences[FLECHE_HAUT]					= &renduFlecheHaut;
	transparences[FLECHE_BAS]					= &renduFlecheBas;
	transparences[TOIT_GAUCHE]					= &renduToitGauche;
	transparences[TOIT]							= &renduOpaque;
	transparences[TOIT_DROITE]					= &renduToitDroite;
	transparences[MAISON]						= &renduOpaque;
	transparences[ESPACE]						= &renduOpaque;
	transparences[EXCLAMATION]					= &renduOpaque;
	transparences[GUILLEMET]					= &renduOpaque;
	transparences[DIESE]						= &renduOpaque;
	transparences[DOLLAR]						= &renduOpaque;
	transparences[POURCENT]						= &renduOpaque;
	transparences[ESPERLUETTE]					= &renduOpaque;
	transparences[APOSTROPHE]					= &renduOpaque;
	transparences[PARENTHESE_GAUCHE]			= &renduOpaque;
	transparences[PARENTHESE_DROITE]			= &renduOpaque;
	transparences[ASTERISQUE]					= &renduOpaque;
	transparences[PLUS]							= &renduOpaque;
	transparences[VIRGULE]						= &renduOpaque;
	transparences[TIRET]						= &renduOpaque;
	transparences[POINT]						= &renduOpaque;
	transparences[SLASH]						= &renduOpaque;
	transparences[ZERO]							= &renduOpaque;
	transparences[UN]							= &renduOpaque;
	transparences[DEUX]							= &renduOpaque;
	transparences[TROIS]						= &renduOpaque;
	transparences[QUATRE]						= &renduOpaque;
	transparences[CINQ]							= &renduOpaque;
	transparences[SIX]							= &renduOpaque;
	transparences[SEPT]							= &renduOpaque;
	transparences[HUIT]							= &renduOpaque;
	transparences[NEUF]							= &renduOpaque;
	transparences[DEUX_POINTS]					= &renduOpaque;
	transparences[POINT_VIRGULE]				= &renduOpaque;
	transparences[CHEVRON_GAUCHE]				= &renduOpaque;
	transparences[EGAL]							= &renduOpaque;
	transparences[CHEVRON_DROITE]				= &renduOpaque;
	transparences[INTERROGATION]				= &renduOpaque;
	transparences[AROBASE]						= &renduOpaque;
	transparences[A]							= &renduOpaque;
	transparences[B]							= &renduOpaque;
	transparences[C]							= &renduOpaque;
	transparences[D]							= &renduOpaque;
	transparences[E]							= &renduOpaque;
	transparences[F]							= &renduOpaque;
	transparences[G]							= &renduOpaque;
	transparences[H]							= &renduOpaque;
	transparences[I]							= &renduOpaque;
	transparences[J]							= &renduOpaque;
	transparences[K]							= &renduOpaque;
	transparences[L]							= &renduOpaque;
	transparences[M]							= &renduOpaque;
	transparences[N]							= &renduOpaque;
	transparences[O]							= &renduOpaque;
	transparences[P]							= &renduOpaque;
	transparences[Q]							= &renduOpaque;
	transparences[R]							= &renduOpaque;
	transparences[S]							= &renduOpaque;
	transparences[T]							= &renduOpaque;
	transparences[U]							= &renduOpaque;
	transparences[V]							= &renduOpaque;
	transparences[W]							= &renduOpaque;
	transparences[X]							= &renduOpaque;
	transparences[Y]							= &renduOpaque;
	transparences[Z]							= &renduOpaque;
	transparences[CROCHET_GAUCHE]				= &renduOpaque;
	transparences[ANTISLASH]					= &renduOpaque;
	transparences[CROCHET_DROIT]				= &renduOpaque;
	transparences[CIRCONFLEXE]					= &renduOpaque;
	transparences[UNDERSCORE]					= &renduOpaque;
	transparences[CURSEUR_VIDE]					= &renduOpaque;
	transparences[AMIN]							= &renduOpaque;
	transparences[BMIN]							= &renduOpaque;
	transparences[CMIN]							= &renduOpaque;
	transparences[DMIN]							= &renduOpaque;
	transparences[EMIN]							= &renduOpaque;
	transparences[FMIN]							= &renduOpaque;
	transparences[GMIN]							= &renduOpaque;
	transparences[HMIN]							= &renduOpaque;
	transparences[IMIN]							= &renduOpaque;
	transparences[JMIN]							= &renduOpaque;
	transparences[KMIN]							= &renduOpaque;
	transparences[LMIN]							= &renduOpaque;
	transparences[MMIN]							= &renduOpaque;
	transparences[NMIN]							= &renduOpaque;
	transparences[OMIN]							= &renduOpaque;
	transparences[PMIN]							= &renduOpaque;
	transparences[QMIN]							= &renduOpaque;
	transparences[RMIN]							= &renduOpaque;
	transparences[SMIN]							= &renduOpaque;
	transparences[TMIN]							= &renduOpaque;
	transparences[UMIN]							= &renduOpaque;
	transparences[VMIN]							= &renduOpaque;
	transparences[WMIN]							= &renduOpaque;
	transparences[XMIN]							= &renduOpaque;
	transparences[YMIN]							= &renduOpaque;
	transparences[ZMIN]							= &renduOpaque;
	transparences[ACCOLADE_GAUCHE]				= &renduOpaque;
	transparences[TRAIT_VERTICAL]				= &renduOpaque;
	transparences[ACCOLADE_DROITE]				= &renduOpaque;
	transparences[ARBRE_HAUT_GAUCHE]			= &renduHautGaucheArbre;
	transparences[ARBRE_MILIEU_GAUCHE]			= &renduMilieuGaucheArbre;
	transparences[ARBRE_BAS_GAUCHE]				= &renduBasGaucheArbre;
	transparences[ARBRE_HAUT_MILIEU]			= &renduOpaque;
	transparences[ARBRE_MILIEU_MILIEU]			= &renduOpaque;
	transparences[ARBRE_BAS_MILIEU]				= &renduBasMilieuArbre;
	transparences[ARBRE_HAUT_DROITE]			= &renduHautDroiteArbre;
	transparences[ARBRE_MILIEU_DROITE]			= &renduMilieuDroiteArbre;
	transparences[ARBRE_BAS_DROITE]				= &renduBasDroiteArbre;
	transparences[TERRE]						= &renduOpaque;
	transparences[TABLE_HAUT_0]					= &renduTable0;
	transparences[TABLE_HAUT_1]					= &renduOpaque;//Table1;
	transparences[TABLE_HAUT_2]					= &renduOpaque;
	transparences[TABLE_HAUT_3]					= &renduOpaque;
	transparences[TABLE_HAUT_4]					= &renduOpaque;//Table4;
	transparences[TABLE_HAUT_5]					= &renduTable5;
	transparences[TABLE_BAS_0]					= &renduOpaque;
	transparences[TABLE_BAS_1]					= &renduOpaque;
	transparences[TABLE_BAS_2]					= &renduOpaque;
	transparences[TABLE_BAS_3]					= &renduOpaque;
	transparences[TABLE_BAS_4]					= &renduOpaque;
	transparences[TABLE_BAS_5]					= &renduOpaque;
	transparences[FENETRE]						= &renduOpaque;
	transparences[MAISON_GAUCHE]				= &renduOpaque;
	transparences[MAISON_DROITE]				= &renduOpaque;
	transparences[POINT_SAUVEGARDE]				= &renduPointSauvegarde;
	transparences[EAU_CALME]					= &renduOpaque;
	transparences[PLANCHES_HORIZ]				= &renduPlanchesHoriz;
	transparences[PLANCHES_VERT]				= &renduPlanchesVert;
	transparences[TRANSPARENT_NORD]				= &renduTransparent;
	transparences[TRANSPARENT_SUD]				= &renduTransparent;
	transparences[TRANSPARENT_OUEST]			= &renduTransparent;
	transparences[TRANSPARENT_EST]				= &renduTransparent;
	transparences[CHEMINEE_ALLUMEE_HAUT_GAUCHE]	= &renduOpaque;
	transparences[CHEMINEE_ALLUMEE_HAUT_DROITE]	= &renduOpaque;
	transparences[CHEMINEE_ALLUMEE_BAS_GAUCHE]	= &renduOpaque;
	transparences[CHEMINEE_ALLUMEE_BAS_DROITE]	= &renduOpaque;
	transparences[PORTE_OUVERTE]				= &renduOpaque;
	transparences[TASSE_CAFE]					= &renduTasseCafe;
	transparences[DEMON_MAL_FAIT]				= &renduDemonMalFait;
	transparences[PLANCHES_HORIZ_BAS]			= &renduPlanchesHorizDroite;
	transparences[PLANCHES_VERT_DROITE]			= &renduPlanchesVertBas;
	transparences[PANNEAU]						= &renduPanneau;
	transparences[TEST_JOUEUR_COMBAT_HG]		= &renduTestJoueurCombatHG;
	transparences[TEST_JOUEUR_COMBAT_HD]		= &renduTestJoueurCombatHD;
	transparences[TEST_JOUEUR_COMBAT_BG]		= &renduTestJoueurCombatBG;
	transparences[TEST_JOUEUR_COMBAT_BD]		= &renduTestJoueurCombatBD;
	transparences[TEST_ZAPPER_COMBAT]			= &renduOpaque;
	transparences[ETOILE_SUCCES]				= &renduEtoileSucces;
	transparences[HERBE_ANIMEE]					= &renduOpaque;
	transparences[ENCADREMENT_PORTE]			= &renduEncadrementPorte;
	transparences[VIDE_177]						= &renduOpaque;
	transparences[VIDE_178]						= &renduOpaque;
	transparences[VIDE_179]						= &renduOpaque;
	transparences[VIDE_180]						= &renduOpaque;
	transparences[VIDE_181]						= &renduOpaque;
	transparences[VIDE_182]						= &renduOpaque;
	transparences[VIDE_183]						= &renduOpaque;
	transparences[VIDE_184]						= &renduOpaque;
	transparences[VIDE_185]						= &renduOpaque;
	transparences[VIDE_186]						= &renduOpaque;
	transparences[VIDE_187]						= &renduOpaque;
	transparences[VIDE_188]						= &renduOpaque;
	transparences[VIDE_189]						= &renduOpaque;
	transparences[VIDE_190]						= &renduOpaque;
	transparences[VIDE_191]						= &renduOpaque;
	transparences[A_GRAVE]						= &renduOpaque;
	transparences[VIDE_193]						= &renduOpaque;
	transparences[A_CIRCONFLEXE]				= &renduOpaque;
	transparences[VIDE_195]						= &renduOpaque;
	transparences[A_TREMA]						= &renduOpaque;
	transparences[VIDE_197]						= &renduOpaque;
	transparences[VIDE_198]						= &renduOpaque;
	transparences[C_CEDILLE]					= &renduOpaque;
	transparences[E_GRAVE]						= &renduOpaque;
	transparences[E_AIGU]						= &renduOpaque;
	transparences[E_CIRCONFLEXE]				= &renduOpaque;
	transparences[E_TREMA]						= &renduOpaque;
	transparences[VIDE_204]						= &renduOpaque;
	transparences[VIDE_205]						= &renduOpaque;
	transparences[I_CIRCONFLEXE]				= &renduOpaque;
	transparences[I_TREMA]						= &renduOpaque;
	transparences[VIDE_208]						= &renduOpaque;
	transparences[VIDE_209]						= &renduOpaque;
	transparences[VIDE_210]						= &renduOpaque;
	transparences[VIDE_211]						= &renduOpaque;
	transparences[O_CIRCONFLEXE]				= &renduOpaque;
	transparences[VIDE_213]						= &renduOpaque;
	transparences[O_TREMA]						= &renduOpaque;
	transparences[MULT]							= &renduOpaque;
	transparences[VIDE_216]						= &renduOpaque;
	transparences[VIDE_217]						= &renduOpaque;
	transparences[VIDE_218]						= &renduOpaque;
	transparences[U_CIRCONFLEXE]				= &renduOpaque;
	transparences[U_TREMA]						= &renduOpaque;
	transparences[VIDE_221]						= &renduOpaque;
	transparences[VIDE_222]						= &renduOpaque;
	transparences[VIDE_223]						= &renduOpaque;
	transparences[A_GRAVE_MIN]					= &renduOpaque;
	transparences[VIDE_225]						= &renduOpaque;
	transparences[A_CIRCONFLEXE_MIN]			= &renduOpaque;
	transparences[VIDE_227]						= &renduOpaque;
	transparences[A_TREMA_MIN]					= &renduOpaque;
	transparences[VIDE_229]						= &renduOpaque;
	transparences[VIDE_230]						= &renduOpaque;
	transparences[C_CEDILLE_MIN]				= &renduOpaque;
	transparences[E_GRAVE_MIN]					= &renduOpaque;
	transparences[E_AIGU_MIN]					= &renduOpaque;
	transparences[E_CIRCONFLEXE_MIN]			= &renduOpaque;
	transparences[E_TREMA_MIN]					= &renduOpaque;
	transparences[VIDE_236]						= &renduOpaque;
	transparences[VIDE_237]						= &renduOpaque;
	transparences[I_CIRCONFLEXE_MIN]			= &renduOpaque;
	transparences[I_TREMA_MIN]					= &renduOpaque;
	transparences[VIDE_240]						= &renduOpaque;
	transparences[VIDE_241]						= &renduOpaque;
	transparences[VIDE_242]						= &renduOpaque;
	transparences[VIDE_243]						= &renduOpaque;
	transparences[O_CIRCONFLEXE_MIN]			= &renduOpaque;
	transparences[VIDE_245]						= &renduOpaque;
	transparences[O_TREMA_MIN]					= &renduOpaque;
	transparences[VIDE_247]						= &renduOpaque;
	transparences[VIDE_248]						= &renduOpaque;
	transparences[U_GRAVE_MIN]					= &renduOpaque;
	transparences[VIDE_250]						= &renduOpaque;
	transparences[U_CIRCONFLEXE_MIN]			= &renduOpaque;
	transparences[U_TREMA_MIN]					= &renduOpaque;
		
	LOGGER("Transparences enregistrées.")
	
	
	LOGGER("Génération de la liste des attributs de tiles...")
	
#define NORD_OUVERT									0b0010 // Valeurs de collision.
#define SUD_OUVERT									0b0001
#define OUEST_OUVERT								0b1000
#define EST_OUVERT									0b0100
	AttribTile huitFrames							= ATTRIB(7,  4, 0b0000);
	AttribTile statiqueMarche						= ATTRIB(0, -1, 0b1111);
	AttribTile statiqueBloque						= ATTRIB(0, -1, 0b0000);
	AttribTile animJoueur__TEST						= ATTRIB(1, 16, 0b0000);
	AttribTile animCurseur							= ATTRIB(1, 32, 0b0000);
	AttribTile statiqueNordFerme					= ATTRIB(0, -1, 0b1101);
	AttribTile statiqueSudFerme						= ATTRIB(0, -1, 0b1110);
	AttribTile statiqueOuestFerme					= ATTRIB(0, -1, 0b0111);
	AttribTile statiqueEstFerme						= ATTRIB(0, -1, 0b1011);
	AttribTile statiquePorte						= ATTRIB(0, -1, 0b0011);
	AttribTile attribFlotte							= ATTRIB(3, 80, 0b0000);
	AttribTile attribHerbe							= ATTRIB(7, 32, 0b1111);
	
	// On n'enregistre pas les animations statiques.
	animations[0]									= &huitFrames;
	animations[1]									= &animJoueur__TEST;
	animations[2]									= &animCurseur;
	animations[3]									= &attribFlotte;
	animations[4]									= &attribHerbe;
	
	attributsTiles[TRANSPARENT_MARCHE]				= &statiqueMarche;
	attributsTiles[TRANSPARENT_BLOQUE]				= &statiqueBloque;
	attributsTiles[BARRE_DEFILANTE]					= &huitFrames;
	attributsTiles[TEST_T]							= &statiqueBloque;
	attributsTiles[TEST_E]							= &statiqueBloque;
	attributsTiles[TEST_S]							= &statiqueBloque;
	attributsTiles[TEST_T_ROUGE]					= &statiqueBloque;
	attributsTiles[COIN_HAUT_GAUCHE]				= &statiqueBloque;
	attributsTiles[COIN_HAUT_DROITE]				= &statiqueBloque;
	attributsTiles[COIN_BAS_GAUCHE]					= &statiqueBloque;
	attributsTiles[COIN_BAS_DROITE]					= &statiqueBloque;
	attributsTiles[BORD_HAUT]						= &statiqueBloque;
	attributsTiles[BORD_BAS]						= &statiqueBloque;
	attributsTiles[BORD_GAUCHE]						= &statiqueBloque;
	attributsTiles[BORD_DROIT]						= &statiqueBloque;
	attributsTiles[NOIR]							= &statiqueBloque;
	attributsTiles[CURSEUR]							= &animCurseur;
	attributsTiles[HERBE]							= &statiqueMarche;
	attributsTiles[JOUEUR_HAUT]						= &animJoueur__TEST;
	attributsTiles[JOUEUR_BAS]						= &animJoueur__TEST;
	attributsTiles[JOUEUR_GAUCHE]					= &animJoueur__TEST;
	attributsTiles[JOUEUR_DROITE]					= &animJoueur__TEST;
	attributsTiles[PORTE]							= &statiqueMarche;
	attributsTiles[MAISON_BAS_GAUCHE]				= &statiqueBloque;
	attributsTiles[MAISON_BAS_DROITE]				= &statiqueBloque;
	attributsTiles[MAISON_BAS]						= &statiqueBloque;
	attributsTiles[FLECHE_HAUT]						= &animCurseur;
	attributsTiles[FLECHE_BAS]						= &animCurseur;
	attributsTiles[TOIT_GAUCHE]						= &statiqueMarche;
	attributsTiles[TOIT]							= &statiqueMarche;
	attributsTiles[TOIT_DROITE]						= &statiqueMarche;
	attributsTiles[MAISON]							= &statiqueBloque;
	attributsTiles[ESPACE]							= &statiqueMarche;
	attributsTiles[EXCLAMATION]						= &statiqueBloque;
	attributsTiles[GUILLEMET]						= &statiqueBloque;
	attributsTiles[DIESE]							= &statiqueBloque;
	attributsTiles[DOLLAR]							= &statiqueBloque;
	attributsTiles[POURCENT]						= &statiqueBloque;
	attributsTiles[ESPERLUETTE]						= &statiqueBloque;
	attributsTiles[APOSTROPHE]						= &statiqueBloque;
	attributsTiles[PARENTHESE_GAUCHE]				= &statiqueBloque;
	attributsTiles[PARENTHESE_DROITE]				= &statiqueBloque;
	attributsTiles[ASTERISQUE]						= &statiqueBloque;
	attributsTiles[PLUS]							= &statiqueBloque;
	attributsTiles[VIRGULE]							= &statiqueBloque;
	attributsTiles[TIRET]							= &statiqueBloque;
	attributsTiles[POINT]							= &statiqueBloque;
	attributsTiles[SLASH]							= &statiqueBloque;
	attributsTiles[ZERO]							= &statiqueBloque;
	attributsTiles[UN]								= &statiqueBloque;
	attributsTiles[DEUX]							= &statiqueBloque;
	attributsTiles[TROIS]							= &statiqueBloque;
	attributsTiles[QUATRE]							= &statiqueBloque;
	attributsTiles[CINQ]							= &statiqueBloque;
	attributsTiles[SIX]								= &statiqueBloque;
	attributsTiles[SEPT]							= &statiqueBloque;
	attributsTiles[HUIT]							= &statiqueBloque;
	attributsTiles[NEUF]							= &statiqueBloque;
	attributsTiles[DEUX_POINTS]						= &statiqueBloque;
	attributsTiles[POINT_VIRGULE]					= &statiqueBloque;
	attributsTiles[CHEVRON_GAUCHE]					= &statiqueBloque;
	attributsTiles[EGAL]							= &statiqueBloque;
	attributsTiles[CHEVRON_DROITE]					= &statiqueBloque;
	attributsTiles[INTERROGATION]					= &statiqueBloque;
	attributsTiles[AROBASE]							= &statiqueBloque;
	attributsTiles[A]								= &statiqueBloque;
	attributsTiles[B]								= &statiqueBloque;
	attributsTiles[C]								= &statiqueBloque;
	attributsTiles[D]								= &statiqueBloque;
	attributsTiles[E]								= &statiqueBloque;
	attributsTiles[F]								= &statiqueBloque;
	attributsTiles[G]								= &statiqueBloque;
	attributsTiles[H]								= &statiqueBloque;
	attributsTiles[I]								= &statiqueBloque;
	attributsTiles[J]								= &statiqueBloque;
	attributsTiles[K]								= &statiqueBloque;
	attributsTiles[L]								= &statiqueBloque;
	attributsTiles[M]								= &statiqueBloque;
	attributsTiles[N]								= &statiqueBloque;
	attributsTiles[O]								= &statiqueBloque;
	attributsTiles[P]								= &statiqueBloque;
	attributsTiles[Q]								= &statiqueBloque;
	attributsTiles[R]								= &statiqueBloque;
	attributsTiles[S]								= &statiqueBloque;
	attributsTiles[T]								= &statiqueBloque;
	attributsTiles[U]								= &statiqueBloque;
	attributsTiles[V]								= &statiqueBloque;
	attributsTiles[W]								= &statiqueBloque;
	attributsTiles[X]								= &statiqueBloque;
	attributsTiles[Y]								= &statiqueBloque;
	attributsTiles[Z]								= &statiqueBloque;
	attributsTiles[CROCHET_GAUCHE]					= &statiqueBloque;
	attributsTiles[ANTISLASH]						= &statiqueBloque;
	attributsTiles[CROCHET_DROIT]					= &statiqueBloque;
	attributsTiles[CIRCONFLEXE]						= &statiqueBloque;
	attributsTiles[UNDERSCORE]						= &statiqueBloque;
	attributsTiles[CURSEUR_VIDE]					= &statiqueBloque;
	attributsTiles[AMIN]							= &statiqueBloque;
	attributsTiles[BMIN]							= &statiqueBloque;
	attributsTiles[CMIN]							= &statiqueBloque;
	attributsTiles[DMIN]							= &statiqueBloque;
	attributsTiles[EMIN]							= &statiqueBloque;
	attributsTiles[FMIN]							= &statiqueBloque;
	attributsTiles[GMIN]							= &statiqueBloque;
	attributsTiles[HMIN]							= &statiqueBloque;
	attributsTiles[IMIN]							= &statiqueBloque;
	attributsTiles[JMIN]							= &statiqueBloque;
	attributsTiles[KMIN]							= &statiqueBloque;
	attributsTiles[LMIN]							= &statiqueBloque;
	attributsTiles[MMIN]							= &statiqueBloque;
	attributsTiles[NMIN]							= &statiqueBloque;
	attributsTiles[OMIN]							= &statiqueBloque;
	attributsTiles[PMIN]							= &statiqueBloque;
	attributsTiles[QMIN]							= &statiqueBloque;
	attributsTiles[RMIN]							= &statiqueBloque;
	attributsTiles[SMIN]							= &statiqueBloque;
	attributsTiles[TMIN]							= &statiqueBloque;
	attributsTiles[UMIN]							= &statiqueBloque;
	attributsTiles[VMIN]							= &statiqueBloque;
	attributsTiles[WMIN]							= &statiqueBloque;
	attributsTiles[XMIN]							= &statiqueBloque;
	attributsTiles[YMIN]							= &statiqueBloque;
	attributsTiles[ZMIN]							= &statiqueBloque;
	attributsTiles[ACCOLADE_GAUCHE]					= &statiqueBloque;
	attributsTiles[TRAIT_VERTICAL]					= &statiqueBloque;
	attributsTiles[ACCOLADE_DROITE]					= &statiqueBloque;
	attributsTiles[ARBRE_HAUT_GAUCHE]				= &statiqueMarche;
	attributsTiles[ARBRE_MILIEU_GAUCHE]				= &statiqueMarche;
	attributsTiles[ARBRE_BAS_GAUCHE]				= &statiqueMarche;
	attributsTiles[ARBRE_HAUT_MILIEU]				= &statiqueMarche;
	attributsTiles[ARBRE_MILIEU_MILIEU]				= &statiqueMarche;
	attributsTiles[ARBRE_BAS_MILIEU]				= &statiqueBloque;
	attributsTiles[ARBRE_HAUT_DROITE]				= &statiqueMarche;
	attributsTiles[ARBRE_MILIEU_DROITE]				= &statiqueMarche;
	attributsTiles[ARBRE_BAS_DROITE]				= &statiqueMarche;
	attributsTiles[TERRE]							= &statiqueMarche;
	attributsTiles[TABLE_HAUT_0]					= &statiqueSudFerme;
	attributsTiles[TABLE_HAUT_1]					= &statiqueBloque;
	attributsTiles[TABLE_HAUT_2]					= &statiqueBloque;
	attributsTiles[TABLE_HAUT_3]					= &statiqueBloque;
	attributsTiles[TABLE_HAUT_4]					= &statiqueBloque;
	attributsTiles[TABLE_HAUT_5]					= &statiqueSudFerme;
	attributsTiles[TABLE_BAS_0]						= &statiqueNordFerme;
	attributsTiles[TABLE_BAS_1]						= &statiqueNordFerme;
	attributsTiles[TABLE_BAS_2]						= &statiqueBloque;
	attributsTiles[TABLE_BAS_3]						= &statiqueBloque;
	attributsTiles[TABLE_BAS_4]						= &statiqueNordFerme;
	attributsTiles[TABLE_BAS_5]						= &statiqueNordFerme;
	attributsTiles[FENETRE]							= &statiqueBloque;
	attributsTiles[MAISON_GAUCHE]					= &statiqueBloque;
	attributsTiles[MAISON_DROITE]					= &statiqueBloque;
	attributsTiles[POINT_SAUVEGARDE]				= &huitFrames;
	attributsTiles[EAU_CALME]						= &attribFlotte;
	attributsTiles[PLANCHES_HORIZ]					= &statiqueMarche;
	attributsTiles[PLANCHES_VERT]					= &statiqueMarche;
	attributsTiles[TRANSPARENT_NORD]				= &statiqueNordFerme;
	attributsTiles[TRANSPARENT_SUD]					= &statiqueSudFerme;
	attributsTiles[TRANSPARENT_OUEST]				= &statiqueOuestFerme;
	attributsTiles[TRANSPARENT_EST]					= &statiqueEstFerme;
	attributsTiles[CHEMINEE_ALLUMEE_HAUT_GAUCHE]	= &animCurseur;
	attributsTiles[CHEMINEE_ALLUMEE_HAUT_DROITE]	= &animCurseur;
	attributsTiles[CHEMINEE_ALLUMEE_BAS_GAUCHE]		= &animCurseur;
	attributsTiles[CHEMINEE_ALLUMEE_BAS_DROITE]		= &animCurseur;
	attributsTiles[PORTE_OUVERTE]					= &statiquePorte;
	attributsTiles[TASSE_CAFE]						= &animCurseur;
	attributsTiles[DEMON_MAL_FAIT]					= &statiqueBloque;
	attributsTiles[PLANCHES_HORIZ_BAS]				= &statiqueMarche;
	attributsTiles[PLANCHES_VERT_DROITE]			= &statiqueMarche;
	attributsTiles[PANNEAU]							= &statiqueBloque;
	attributsTiles[TEST_JOUEUR_COMBAT_HG]			= &statiqueBloque;
	attributsTiles[TEST_JOUEUR_COMBAT_HD]			= &statiqueBloque;
	attributsTiles[TEST_JOUEUR_COMBAT_BG]			= &statiqueBloque;
	attributsTiles[TEST_JOUEUR_COMBAT_BD]			= &statiqueBloque;
	attributsTiles[TEST_ZAPPER_COMBAT]				= &statiqueBloque;
	attributsTiles[ETOILE_SUCCES]					= &statiqueBloque;
	attributsTiles[HERBE_ANIMEE]					= &attribHerbe;
	attributsTiles[ENCADREMENT_PORTE]				= &statiqueMarche;
	attributsTiles[VIDE_177]						= &statiqueBloque;
	attributsTiles[VIDE_178]						= &statiqueBloque;
	attributsTiles[VIDE_179]						= &statiqueBloque;
	attributsTiles[VIDE_180]						= &statiqueBloque;
	attributsTiles[VIDE_181]						= &statiqueBloque;
	attributsTiles[VIDE_182]						= &statiqueBloque;
	attributsTiles[VIDE_183]						= &statiqueBloque;
	attributsTiles[VIDE_184]						= &statiqueBloque;
	attributsTiles[VIDE_185]						= &statiqueBloque;
	attributsTiles[VIDE_186]						= &statiqueBloque;
	attributsTiles[VIDE_187]						= &statiqueBloque;
	attributsTiles[VIDE_188]						= &statiqueBloque;
	attributsTiles[VIDE_189]						= &statiqueBloque;
	attributsTiles[VIDE_190]						= &statiqueBloque;
	attributsTiles[VIDE_191]						= &statiqueBloque;
	attributsTiles[A_GRAVE]							= &statiqueBloque;
	attributsTiles[VIDE_193]						= &statiqueBloque;
	attributsTiles[A_CIRCONFLEXE]					= &statiqueBloque;
	attributsTiles[VIDE_195]						= &statiqueBloque;
	attributsTiles[A_TREMA]							= &statiqueBloque;
	attributsTiles[VIDE_197]						= &statiqueBloque;
	attributsTiles[VIDE_198]						= &statiqueBloque;
	attributsTiles[C_CEDILLE]						= &statiqueBloque;
	attributsTiles[E_GRAVE]							= &statiqueBloque;
	attributsTiles[E_AIGU]							= &statiqueBloque;
	attributsTiles[E_CIRCONFLEXE]					= &statiqueBloque;
	attributsTiles[E_TREMA]							= &statiqueBloque;
	attributsTiles[VIDE_204]						= &statiqueBloque;
	attributsTiles[VIDE_205]						= &statiqueBloque;
	attributsTiles[I_CIRCONFLEXE]					= &statiqueBloque;
	attributsTiles[I_TREMA]							= &statiqueBloque;
	attributsTiles[VIDE_208]						= &statiqueBloque;
	attributsTiles[VIDE_209]						= &statiqueBloque;
	attributsTiles[VIDE_210]						= &statiqueBloque;
	attributsTiles[VIDE_211]						= &statiqueBloque;
	attributsTiles[O_CIRCONFLEXE]					= &statiqueBloque;
	attributsTiles[VIDE_213]						= &statiqueBloque;
	attributsTiles[O_TREMA]							= &statiqueBloque;
	attributsTiles[MULT]							= &statiqueBloque;
	attributsTiles[VIDE_216]						= &statiqueBloque;
	attributsTiles[VIDE_217]						= &statiqueBloque;
	attributsTiles[VIDE_218]						= &statiqueBloque;
	attributsTiles[U_CIRCONFLEXE]					= &statiqueBloque;
	attributsTiles[U_TREMA]							= &statiqueBloque;
	attributsTiles[VIDE_221]						= &statiqueBloque;
	attributsTiles[VIDE_222]						= &statiqueBloque;
	attributsTiles[VIDE_223]						= &statiqueBloque;
	attributsTiles[A_GRAVE_MIN]						= &statiqueBloque;
	attributsTiles[VIDE_225]						= &statiqueBloque;
	attributsTiles[A_CIRCONFLEXE_MIN]				= &statiqueBloque;
	attributsTiles[VIDE_227]						= &statiqueBloque;
	attributsTiles[A_TREMA_MIN]						= &statiqueBloque;
	attributsTiles[VIDE_229]						= &statiqueBloque;
	attributsTiles[VIDE_230]						= &statiqueBloque;
	attributsTiles[C_CEDILLE_MIN]					= &statiqueBloque;
	attributsTiles[E_GRAVE_MIN]						= &statiqueBloque;
	attributsTiles[E_AIGU_MIN]						= &statiqueBloque;
	attributsTiles[E_CIRCONFLEXE_MIN]				= &statiqueBloque;
	attributsTiles[E_TREMA_MIN]						= &statiqueBloque;
	attributsTiles[VIDE_236]						= &statiqueBloque;
	attributsTiles[VIDE_237]						= &statiqueBloque;
	attributsTiles[I_CIRCONFLEXE_MIN]				= &statiqueBloque;
	attributsTiles[I_TREMA_MIN]						= &statiqueBloque;
	attributsTiles[VIDE_240]						= &statiqueBloque;
	attributsTiles[VIDE_241]						= &statiqueBloque;
	attributsTiles[VIDE_242]						= &statiqueBloque;
	attributsTiles[VIDE_243]						= &statiqueBloque;
	attributsTiles[O_CIRCONFLEXE_MIN]				= &statiqueBloque;
	attributsTiles[VIDE_245]						= &statiqueBloque;
	attributsTiles[O_TREMA_MIN]						= &statiqueBloque;
	attributsTiles[VIDE_247]						= &statiqueBloque;
	attributsTiles[VIDE_248]						= &statiqueBloque;
	attributsTiles[U_GRAVE_MIN]						= &statiqueBloque;
	attributsTiles[VIDE_250]						= &statiqueBloque;
	attributsTiles[U_CIRCONFLEXE_MIN]				= &statiqueBloque;
	attributsTiles[U_TREMA_MIN]						= &statiqueBloque;
	LOGGER("Génération terminée.")

