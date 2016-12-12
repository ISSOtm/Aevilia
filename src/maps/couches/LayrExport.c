
// #############################
// #                           #
// #    AEVILIA SOURCE CODE    #
// #       Version 0.4.0       #
// #                           #
// #  LayrExport Version 0.1   #
// #                           #
// #############################
// ##                         ##
// ##### Fichier principal #####
// #############################


#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "../../typedefs.h"


int main(int argc, char* argv[]) {
	unsigned int verbeux = 0;
	if(argc == 4 && !(strcmp(argv[1], "-v"))) {
		verbeux = 1;
		argv[1] = argv[2];
		argv[2] = argv[3];
		argc = 3;
	}
	
	if(verbeux) {
		printf("\n#################\n#               #\n# LAYER  EXPORT #\n# Version 0.1.0 #\n#   By ISSOtm   #\n#               #\n#################\n\nConvient pour Aevilia version 0.4.0\n\n\n");
	}
	
	if(argc != 3) {
		printf("Syntaxe invalide !\nSyntaxe valide : LayrExport chemin/vers/fichierEntree.layr chemin/vers/fichierSortie.layr\nExemple : LayrExport src/maps/TEST_0.layr bin/couches/TEST_0.layr\n");
		return 1; 
	}
	
	Couche couche;
#define LONG_NOM_TILE 40
	char chaines[NB_TILES][LONG_NOM_TILE] = {
	"TRANSPARENT_MARCHE",
	"TRANSPARENT_BLOQUE",
	"BARRE_DEFILANTE",
	"TEST_T",
	"TEST_E",
	"TEST_S",
	"TEST_T_ROUGE",
	"COIN_HAUT_GAUCHE",
	"COIN_HAUT_DROITE",
	"COIN_BAS_GAUCHE",
	"COIN_BAS_DROITE",
	"BORD_HAUT",
	"BORD_BAS",
	"BORD_GAUCHE",
	"BORD_DROIT",
	"NOIR",
	"CURSEUR",
	"HERBE",
	"JOUEUR_HAUT",
	"JOUEUR_BAS",
	"JOUEUR_GAUCHE",
	"JOUEUR_DROITE",
	"PORTE",
	"MAISON_BAS_GAUCHE",
	"MAISON_BAS_DROITE",
	"MAISON_BAS",
	"FLECHE_HAUT",
	"FLECHE_BAS",
	"TOIT_GAUCHE",
	"TOIT",
	"TOIT_DROITE",
	"MAISON",
	"ESPACE",
	"EXCLAMATION",
	"GUILLEMET",
	"DIESE",
	"DOLLAR",
	"POURCENT",
	"ESPERLUETTE",
	"APOSTROPHE",
	"PARENTHESE_GAUCHE",
	"PARENTHESE_DROITE",
	"ASTERISQUE",
	"PLUS",
	"VIRGULE",
	"TIRET",
	"POINT",
	"SLASH",
	"ZERO",
	"UN",
	"DEUX",
	"TROIS",
	"QUATRE",
	"CINQ",
	"SIX",
	"SEPT",
	"HUIT",
	"NEUF",
	"DEUX_POINTS",
	"POINT_VIRGULE",
	"CHEVRON_GAUCHE",
	"EGAL",
	"CHEVRON_DROITE",
	"INTERROGATION",
	"AROBASE",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"CROCHET_GAUCHE",
	"ANTISLASH",
	"CROCHET_DROIT",
	"CIRCONFLEXE",
	"UNDERSCORE",
	"CURSEUR_VIDE",
	"AMIN",
	"BMIN",
	"CMIN",
	"DMIN",
	"EMIN",
	"FMIN",
	"GMIN",
	"HMIN",
	"IMIN",
	"JMIN",
	"KMIN",
	"LMIN",
	"MMIN",
	"NMIN",
	"OMIN",
	"PMIN",
	"QMIN",
	"RMIN",
	"SMIN",
	"TMIN",
	"UMIN",
	"VMIN",
	"WMIN",
	"XMIN",
	"YMIN",
	"ZMIN",
	"ACCOLADE_GAUCHE",
	"TRAIT_VERTICAL",
	"ACCOLADE_DROITE",
	"ARBRE_HAUT_GAUCHE",
	"ARBRE_MILIEU_GAUCHE",
	"ARBRE_BAS_GAUCHE",
	"ARBRE_HAUT_MILIEU",
	"ARBRE_MILIEU_MILIEU",
	"ARBRE_BAS_MILIEU",
	"ARBRE_HAUT_DROITE",
	"ARBRE_MILIEU_DROITE",
	"ARBRE_BAS_DROITE",
	"TERRE",
	"TABLE_HAUT_0",
	"TABLE_HAUT_1",
	"TABLE_HAUT_2",
	"TABLE_HAUT_3",
	"TABLE_HAUT_4",
	"TABLE_HAUT_5",
	"TABLE_BAS_0",
	"TABLE_BAS_1",
	"TABLE_BAS_2",
	"TABLE_BAS_3",
	"TABLE_BAS_4",
	"TABLE_BAS_5",
	"FENETRE",
	"MAISON_GAUCHE",
	"MAISON_DROITE",
	"POINT_SAUVEGARDE",
	"EAU_CALME",
	"PLANCHES_HORIZ",
	"PLANCHES_VERT",
	"TRANSPARENT_NORD",
	"TRANSPARENT_SUD",
	"TRANSPARENT_OUEST",
	"TRANSPARENT_EST",
	"CHEMINEE_ALLUMEE_HAUT_GAUCHE",
	"CHEMINEE_ALLUMEE_HAUT_DROITE",
	"CHEMINEE_ALLUMEE_BAS_GAUCHE",
	"CHEMINEE_ALLUMEE_BAS_DROITE",
	"PORTE_OUVERTE",
	"TASSE_CAFE",
	"DEMON_MAL_FAIT",
	"PLANCHES_HORIZ_BAS",
	"PLANCHES_VERT_DROITE",
	"PANNEAU",
	"TEST_JOUEUR_COMBAT_HG",
	"TEST_JOUEUR_COMBAT_HD",
	"TEST_JOUEUR_COMBAT_BG",
	"TEST_JOUEUR_COMBAT_BD",
	"TEST_ZAPPER_COMBAT",
	"ETOILE_SUCCES",
	"HERBE_ANIMEE",
	"ENCADREMENT_PORTE",
	"VIDE_177",
	"VIDE_178",
	"VIDE_179",
	"VIDE_180",
	"VIDE_181",
	"VIDE_182",
	"VIDE_183",
	"VIDE_184",
	"VIDE_185",
	"VIDE_186",
	"VIDE_187",
	"VIDE_188",
	"VIDE_189",
	"VIDE_190",
	"VIDE_191",
	"A_GRAVE",
	"VIDE_193",
	"A_CIRCONFLEXE",
	"VIDE_195",
	"A_TREMA",
	"VIDE_197",
	"VIDE_198",
	"C_CEDILLE",
	"E_GRAVE",
	"E_AIGU",
	"E_CIRCONFLEXE",
	"E_TREMA",
	"VIDE_204",
	"VIDE_205",
	"I_CIRCONFLEXE",
	"I_TREMA",
	"VIDE_208",
	"VIDE_209",
	"VIDE_210",
	"VIDE_211",
	"O_CIRCONFLEXE",
	"VIDE_213",
	"O_TREMA",
	"MULT",
	"VIDE_216",
	"VIDE_217",
	"VIDE_218",
	"U_CIRCONFLEXE",
	"U_TREMA",
	"VIDE_221",
	"VIDE_222",
	"VIDE_223",
	"A_GRAVE_MIN",
	"VIDE_225",
	"A_CIRCONFLEXE_MIN",
	"VIDE_227",
	"A_TREMA_MIN",
	"VIDE_229",
	"VIDE_230",
	"C_CEDILLE_MIN",
	"E_GRAVE_MIN",
	"E_AIGU_MIN",
	"E_CIRCONFLEXE_MIN",
	"E_TREMA_MIN",
	"VIDE_236",
	"VIDE_237",
	"I_CIRCONFLEXE_MIN",
	"I_TREMA_MIN",
	"VIDE_240",
	"VIDE_241",
	"VIDE_242",
	"VIDE_243",
	"O_CIRCONFLEXE_MIN",
	"VIDE_245",
	"O_TREMA_MIN",
	"VIDE_247",
	"VIDE_248",
	"U_GRAVE_MIN",
	"VIDE_250",
	"U_CIRCONFLEXE_MIN",
	"U_TREMA_MIN"};
	FILE* fichier;
	FILE* fichierSortie;
	
	if(verbeux) {
		printf("Ouverture du fichier d'entrée  %s\n", argv[1]);
	}
	fichier = fopen(argv[1], "r");
	
	if(!fichier) {
		perror(argv[1]);
		printf("\n");
		return 1;
	}
	
	if(verbeux) {
		printf("Ouverture du fichier de sortie %s...\n", argv[2]);
	}
	remove(argv[2]);
	fichierSortie = fopen(argv[2], "ab");
	
	if(!fichierSortie) {
		perror(argv[2]);
		printf("\n");
		return 1;
	}
	
	
	if(!fscanf(fichier, "hauteur = %u", &couche.hauteur)) {
		printf("La hauteur est mal formatée ! Arrêt.\n");
		return 1;
	}
	
	if(!fscanf(fichier, "\nlargeur = %u", &couche.largeur)) {
		printf("La largeur est mal formatée ! Arrêt.\n");
		return 1;
	}
	if(verbeux) {
		printf("Hauteur : %u\nLargeur : %u\n", couche.hauteur, couche.largeur);
	}
	
	
	char nomTile[LONG_NOM_TILE] = "TRANSPARENT_MARCHE";
	wchar_t tileDefaut = 0;
	
	wchar_t* pointerCoords(unsigned int vert, unsigned int horiz) {
		return &couche.tilemap[vert * couche.largeur + horiz];
	}
	
	wchar_t obtenirIDtile(char* nom) {
		wchar_t IDtile = 0;
		
		for( ; IDtile < NB_TILES; IDtile++) {
			if(!strcmp(chaines[IDtile], nom)) {
				return IDtile;
			}
		}
		printf("Valeur invalide (%s) fournie !\n", nom);
		exit(1);
	}
	
	if(!fscanf(fichier, "\ndefaut = %s", nomTile)) {
		printf("La tile par défaut n'est pas spécifiée !\n");
		return 1;
	}
	tileDefaut = obtenirIDtile(nomTile);
	if(verbeux) {
		printf("Tile par défaut : %s (%u)\n\n", nomTile, tileDefaut);
	}
	wmemset(couche.tilemap, tileDefaut, couche.hauteur * couche.largeur);
	
	unsigned int nbEcritures = 0;
	char indexTile[100] = "";
	unsigned int coordVert;
	unsigned int coordHoriz;
	unsigned int coordVertFin;
	unsigned int coordHorizFin;
	
	while(fscanf(fichier, "\n[%s = %s", indexTile, nomTile) != EOF) {
		switch(sscanf(indexTile, "%u][%u]...[%u][%u]", &coordVert, &coordHoriz, &coordVertFin, &coordHorizFin)) {
			case 2:
				// N'a trouvé que les deux premiers nombres.
				if(verbeux) {
					printf("Coords (%u, %u) : tile %s (%u)\n\n", coordVert, coordHoriz, nomTile, obtenirIDtile(nomTile));
				}
				*pointerCoords(coordVert, coordHoriz) = obtenirIDtile(nomTile);
			break;
			
			case 4:
				// A trouvé les deux paires de coordonnées.
				if(verbeux) {
					printf("Des coords (%u, %u) aux coords (%u, %u) : tile %s\n\n", coordVert, coordHoriz, coordVertFin, coordHorizFin, nomTile);
				}
				wmemset(pointerCoords(coordVert, coordHoriz), obtenirIDtile(nomTile), (coordVertFin - coordVert) * couche.largeur + (coordHorizFin - coordHoriz) + 1);
			break;
			
			default:
				printf("Ligne formatée incorrectement !\n[%s] = %s\n", indexTile, nomTile);
				
				fclose(fichierSortie);
				fclose(fichier);
				return 1;
		}
		
		nbEcritures++;
	}
	
	
	if(verbeux) {
		printf("\nÉcriture de la couche terminée.\n(%u écritures réalisées)\nÉcriture du fichier %s...\n", nbEcritures, argv[2]);
	}
	fwrite(&couche, sizeof(Couche), 1, fichierSortie);
	
	if(verbeux) {
		printf("Fermeture des fichiers...\n");
	}
	fclose(fichierSortie);
	fclose(fichier);
	
	printf("LayrExport a terminé.\n");
	return 0;
}

