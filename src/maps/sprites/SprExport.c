
// #############################
// #                           #
// #    AEVILIA SOURCE CODE    #
// #       Version 0.4.0       #
// #                           #
// #  SprExport Version 0.1.0  #
// #                           #
// #############################
// ##                         ##
// ##### Fichier principal #####
// #############################


#include <stdio.h>
#include <stdlib.h>

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
		printf("\n#################\n#               #\n# SPRITE EXPORT #\n# Version 0.2.0 #\n#   By ISSOtm   #\n#               #\n#################\n\nConvient pour Aevilia version 0.4.0\n\n\n");
	}
	
	if(argc != 3) {
		printf("Syntaxe invalide !\nSyntaxe valide : SprExport chemin/vers/fichierEntree.spr chemin/vers/fichierSortie.spr\nExemple : SprExport src/maps/TEST.spr bin/sprites/TEST.spr\n");
		return 1; 
	}
	
	Sprite sprites[NB_SPRITES_MAX] = {[0 ... NB_SPRITES_MAX - 1] = {0, 0, 0, 0, 0, 0}};
	unsigned int IDsprite = 0;
	FILE* fichier;
	FILE* fichierSortie;
	
	char nomSprite[30];
	unsigned int positionVert;
	unsigned int positionHoriz;
	unsigned int tile;
	unsigned int direction;
	unsigned int IDinteraction;
	unsigned int couche;
	
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
	
	while(fscanf(fichier, "[%s\npositionVert = %u\npositionHoriz = %u\ntile = %u\ndirection = %u\nIDinteraction = %u\ncouche = %u\n\n", nomSprite, &positionVert, &positionHoriz, &tile, &direction, &IDinteraction, &couche) == 7) {
		nomSprite[strlen(nomSprite) - 1] = 0;
		
		if(verbeux) {
			printf("\nSprite %s = {%u %u %u %u %u %u}\n", nomSprite, positionVert, positionHoriz, tile, direction, IDinteraction, couche);
		}
		
		sprites[IDsprite].positionVert = positionVert;
		sprites[IDsprite].positionHoriz = positionHoriz;
		sprites[IDsprite].tile = tile;
		sprites[IDsprite].direction = direction;
		sprites[IDsprite].IDtableInteractions = IDinteraction;
		sprites[IDsprite].couche = (unsigned char)couche;
		
		IDsprite++;
	}
	
	if(verbeux) {
		printf("\nÉcriture de %u sprites terminée. Écriture du fichier %s...\n", IDsprite, argv[2]);
	}
	fwrite(&sprites, sizeof(Sprite), NB_SPRITES_MAX, fichierSortie);
	
	if(verbeux) {
		printf("Fermeture des fichiers...\n");
	}
	fclose(fichierSortie);
	fclose(fichier);
	
	printf("SprExport a terminé.\n");
	return 0;
}

