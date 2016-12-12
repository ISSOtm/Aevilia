
// #############################
// #                           #
// #    AEVILIA SOURCE CODE    #
// #       Version 0.4.0       #
// #                           #
// #  ParamsExport Version 0.1 #
// #                           #
// #############################
// ##                         ##
// ##### Fichier principal #####
// #############################


#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "../typedefs.h"


int main(int argc, char* argv[]) {
	printf("\n#################\n#               #\n# PARAMS EXPORT #\n# Version 0.1.0 #\n#   By ISSOtm   #\n#               #\n#################\n\nConvient pour Aevilia version 0.4.0\n\n\n");
	
	if(argc != 3) {
		printf("Syntaxe invalide !\nSyntaxe valide : ParamsExport chemin/vers/fichierEntree.ptc chemin/vers/fichierSortie.ptc\nExemple : LayrExport src/maps/TEST_0.ptc bin/sprites/TEST_0.ptc\n");
		return 1; 
	}
	
	
	FILE* fichier;
	FILE* fichierSortie;
	
	printf("Ouverture du fichier d'entrée  %s\n", argv[1]);
	fichier = fopen(argv[1], "r");
	
	if(!fichier) {
		perror(argv[1]);
		printf("\n");
		return 1;
	}
	
	printf("Ouverture du fichier de sortie %s...\n", argv[2]);
	remove(argv[2]);
	fichierSortie = fopen(argv[2], "a");
	
	if(!fichierSortie) {
		perror(argv[2]);
		printf("\n");
		fclose(fichier);
		return 1;
	}
	
	char uneLigne[9001];
	enum {
		IMAGE,
		PARAMS,
		ANIMS_ELEMS,
		ANIMS,
		
		AUCUN
	} mode = AUCUN;
	char nomsModes[AUCUN][12] = {"image", "params", "anims_elems", "anims"};
	
	char nomFichierImage[FILENAME_MAX] = "\0";
	unsigned int longueurNomImage = 0;
	
	unsigned int nbMasques = 0;
	unsigned int numLigneMasque = 0;
	unsigned int masques[256][32];
	unsigned int nbParamsRendu = 0;
	RessourceParamTextureCombat paramsRendu[NB_PARAMS_DIFFERENTS_PAR_TEXTURE];
	char nomsModesRendu[MASQUE+1][14] = {"TRANSPARENT", "OPAQUE", "MOITIE_GAUCHE", "MOITIE_DROITE", "MASQUE"};
	
	unsigned int i;
	unsigned int numLigne = 0;
	
	enum {
		ELEM_RECT,
		ELEM_MODE,
		ELEM_MASQUE
	} elemParam = ELEM_RECT;
	
	while(fgets(uneLigne, 9002, fichier)) {
		numLigne++;
		
		unsigned int lgt = strlen(uneLigne);
		if(lgt && uneLigne[lgt - 1] == '\n') {
			uneLigne[--lgt] = '\0';
		}
		
		if(lgt && uneLigne[0] != '#' && uneLigne[0] != '\n') {
			// On n'a pas un commentaire.
			
			if(uneLigne[0] == '[') {
				if(mode != AUCUN) {
					printf("Ligne %d : Mode %d non terminé, impossible d'en démarrer un nouveau !\n  %s\n", numLigne, mode, uneLigne);
					
					fclose(fichierSortie);
					fclose(fichier);
					return 1;
				}
				
				if(!lgt || uneLigne[lgt-1] != ']') {
					printf("Ligne %d : Aucun mode entré !\n  %s\n", numLigne, uneLigne);
					
					fclose(fichierSortie);
					fclose(fichier);
					return 1;
				}
				
				// On retire le ']'.
				uneLigne[lgt-1] = '\0';
				
				for(i = 0; i < AUCUN; i++) {
					if(!strncmp(nomsModes[i], &uneLigne[1], 12)) {
						mode = i;
					}
				}
				
				if(mode == AUCUN) {
					printf("Ligne %d : Mode %s inconnu !\n", numLigne, &uneLigne[1]);
					
					fclose(fichierSortie);
					fclose(fichier);
					return 1;
				}
			} else if(mode != AUCUN) {
				switch(mode) {
					case IMAGE:
						if(strlen(nomFichierImage)) {
							printf("Ligne %d : Image définie deux fois !\n", numLigne);
						
							fclose(fichierSortie);
							fclose(fichier);
							return 1;
						}
					
						longueurNomImage = strlen(uneLigne);
						if(longueurNomImage >= FILENAME_MAX) {
							printf("Ligne %d : Nom de fichier d'image trop long !\n  %s\n", numLigne, uneLigne);
						
							fclose(fichierSortie);
							fclose(fichier);
							return 1;
						}
					
						strcpy(nomFichierImage, uneLigne);
					
						mode = AUCUN;
					break;
					case PARAMS:
						if(!strcmp(uneLigne, "fin_params")) {
							if(elemParam != ELEM_RECT) {
								printf("Ligne %d : Impossible de terminer l'entrée des params : paramètre non complet !\n", numLigne);
								
								fclose(fichierSortie);
								fclose(fichier);
								return 1;
							}
							
							mode = AUCUN;	
						} else {
							switch(elemParam) {
								case ELEM_RECT:
									// S'occupe aussi d'écrire les valeurs là où elles le doivent.
									if(sscanf(uneLigne, "{y = %d, x = %d, dy = %d, dx = %d}", &paramsRendu[nbParamsRendu].rectSource.y, &paramsRendu[nbParamsRendu].rectSource.x, &paramsRendu[nbParamsRendu].rectSource.h, &paramsRendu[nbParamsRendu].rectSource.w) != 4) {
										printf("Ligne %d : Rectangle mal formé ! (Attendu : {y = %%d, x = %%d, dy = %%d, dx = %%d})\n%s\n", numLigne, uneLigne);
										
										fclose(fichierSortie);
										fclose(fichier);
										return 1;
									}
									
									elemParam = ELEM_MODE;
								break;
								case ELEM_MODE:
									paramsRendu[nbParamsRendu].modeRendu = -1;
									
									for(i = 0; i <= MASQUE; i++) {
										if(!strcmp(nomsModesRendu[i], uneLigne)) {
											paramsRendu[nbParamsRendu].modeRendu = i;
										}
									}
									
									if(paramsRendu[nbParamsRendu].modeRendu == (unsigned int)-1) {
										printf("Ligne %d : Mode de rendu inconnu !\n%s\n", numLigne, uneLigne);
										
										fclose(fichierSortie);
										fclose(fichier);
										return 1;
									}
									
									switch(paramsRendu[nbParamsRendu].modeRendu) {
										case TRANSPARENT:
										case OPAQUE:
											elemParam = ELEM_RECT;
											nbParamsRendu++;
										break;
										
										case MOITIE_GAUCHE:
										case MOITIE_DROITE:
										case MASQUE:
											elemParam = ELEM_MASQUE;
										break;
									}
								break;
								case ELEM_MASQUE:
									if(!strcmp(uneLigne, "fin_masque")) {
										numLigneMasque = 0;
										elemParam = ELEM_RECT;
										
										nbMasques++;
										nbParamsRendu++;
									} else {
										sscanf(uneLigne, "%x", &masques[nbMasques][numLigneMasque]);
									}
								break;
								
								default:
									printf("Ligne %d : Élément inconnu pour les paramètres (%d) !\n", numLigne, elemParam);
									
									fclose(fichierSortie);
									fclose(fichier);
									return 1;
							}
						}
					break;
					case ANIMS_ELEMS:
						
					break;
					case ANIMS:
						
					break;
					
					default:
						printf("Ligne %u : Mode inconnu ! %d\n", numLigne-1, mode);
						
						fclose(fichierSortie);
						fclose(fichier);
						return 1;
				}
			}
		}
	}
	
	if(mode != AUCUN) {
		printf("Fin du fichier rencontrée, mais mode %d toujours actif !\n", mode);
		
		fclose(fichier);
		fclose(fichierSortie);
		return 1;
	}
	
	
	printf("\n%d ligne(s) lue(s).\nÉcriture des données de texture terminée.\nÉcriture du fichier %s...\n", numLigne, argv[2]);
	fwrite(&longueurNomImage, sizeof(unsigned int), 1, fichierSortie);
	fwrite(nomFichierImage, sizeof(char), longueurNomImage, fichierSortie);
	
	printf("Fermeture des fichiers...\n");
	fclose(fichierSortie);
	fclose(fichier);
	
	printf("ParamsExport a terminé.\n");
	return 0;
}

