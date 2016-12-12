
// #############################
// #                           #
// #    AEVILIA SOURCE CODE    #
// #       Version 0.4.0       #
// #                           #
// #  AnimExport Version 0.1   #
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
	printf("\n#################\n#               #\n#  ANIM EXPORT  #\n# Version 0.1.0 #\n#   By ISSOtm   #\n#               #\n#################\n\nConvient pour Aevilia version 0.4.0\n\n\n");
	
	if(argc != 3) {
		printf("Syntaxe invalide !\nSyntaxe valide : AnimExport chemin/vers/fichierEntree.anic chemin/vers/fichierSortie.anic\nExemple : LayrExport src/maps/TEST_0.anic bin/sprites/TEST_0.anic\n");
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
	fichierSortie = fopen(argv[2], "ab");
	
	if(!fichierSortie) {
		perror(argv[2]);
		printf("\n");
		fclose(fichier);
		return 1;
	}
	
	
	char actions[NB_ACTIONS_ANIMATION+1][16] = {"terminer",
											    "attendre",
											    "sauter",
											    "autre_anim",
											    "changer_param",
											    "deplacer",
											    "redimensionner",
											    "modif_angle",
											    "modif_centre",
											    "modif_flip",
											    "fin"};
	char argumentsAttendre[2][16] = {"frames",
									 "timer"};
	char argumentsDeplacer[4][16] = {"haut",
									 "bas",
									 "gauche",
									 "droite"};
	char argumentsAbsRel[2][16] = {"absolu",
								   "relatif"};
	char argumentsFlip[4][16] = {"aucun",
								 "horizontal",
								 "vertical",
								 "double"};
	
	__attribute__ ((pure)) unsigned int indexOf(char* str, char array[][16], unsigned int len) {
		unsigned int i = 0;
		for( ; i < len; i++) {
			if(!(strcmp(array[i], str))) {
				return i;
			}
		}
		return -1;
	}
	
	char action[99];
	unsigned int IDaction;
	unsigned int argument1;
	unsigned int argument2;
	
	unsigned int numLigne = 0;
	
	unsigned int IDinsertionElem = 0; // Index d'insertion des éléments.
	ElemAnimTexture elemsAnimation[NB_ELEMS_ANIM_PAR_TEXTURE];
	unsigned int IDanimationEnCours = 0; // Index de l'animation à modifier.
	unsigned int IDelemEnCoursDajout = 0; // Index de l'élément (de l'animation à modifier) à modifier.
	RessourceAnimation ressourcesAnimations[NB_ANIMATIONS_PAR_TEXTURE];
	printf("Lecture des éléments...\n");
	while(fscanf(fichier, "%s", action) != EOF) {
		numLigne++;
		
		if(IDanimationEnCours == NB_ANIMATIONS_PAR_TEXTURE) {
			printf("Ligne %u : Capacité d'animations (%u) dépassée !\n", numLigne, NB_ANIMATIONS_PAR_TEXTURE);
			fclose(fichier);
			fclose(fichierSortie);
			return 2;
		}
		
		IDaction = indexOf(action, actions, NB_ACTIONS_ANIMATION+1);
		
		if(IDaction == (unsigned int)-1) {
			printf("Ligne %u : Action inconnue \"%s\".\n", numLigne, action);
			fclose(fichier);
			fclose(fichierSortie);
			return 1;
		}
		
		switch(IDaction) {
			case TERMINER:
				argument1 = 0;
				argument2 = 0;
			break;
			case PAUSE_ANIMATION:
				if(fscanf(fichier, "%u %s", &argument2, action) != 2) {
					printf("Ligne %u : Pas assez d'arguments à \"attendre\".\n", numLigne);
					fclose(fichier);
					fclose(fichierSortie);
					return 1;
				}
				
				argument1 = indexOf(action, argumentsAttendre, 2);
				if(argument1 == (unsigned int)-1) {
					printf("Ligne %u : Argument 1 invalide (%s obtenu).\n", numLigne, action);
					fclose(fichier);
					fclose(fichierSortie);
					return 1;
				}
			break;
			case SAUTER_ANIMATION:
				if(fscanf(fichier, "%u %s", &argument2, action) != 2) {
					printf("Ligne %u : Pas assez d'arguments à \"sauter\".\n", numLigne);
					fclose(fichier);
					fclose(fichierSortie);
					return 1;
				}
				
				argument1 = indexOf(action, argumentsAbsRel, 2);
				if(argument1 == (unsigned int)-1) {
					printf("Ligne %u : Argument 1 invalide (%s obtenu).\n", numLigne, action);
					fclose(fichier);
					fclose(fichierSortie);
					return 1;
				}
			break;
			case MODIFIER_ID_ANIM_EN_COURS:
				if(fscanf(fichier, "%u %s", &argument2, action) != 2) {
					printf("Ligne %u : Pas assez d'arguments à \"autre_anim\".\n", numLigne);
					fclose(fichier);
					fclose(fichierSortie);
					return 1;
				}
				
				argument1 = indexOf(action, argumentsAbsRel, 2);
				if(argument1 == (unsigned int)-1) {
					printf("Ligne %u : Argument 1 invalide (%s obtenu).\n", numLigne, action);
					fclose(fichier);
					fclose(fichierSortie);
					return 1;
				}
			break;
			case MODIF_PARAM_ACTIF:
				if(fscanf(fichier, "%u %s", &argument2, action) != 2) {
					printf("Ligne %u : Pas assez d'arguments à \"changer_param\".\n", numLigne);
					fclose(fichier);
					fclose(fichierSortie);
					return 1;
				}
				
				argument1 = indexOf(action, argumentsAbsRel, 2);
				if(argument1 == (unsigned int)-1) {
					printf("Ligne %u : Argument 1 invalide (%s obtenu).\n", numLigne, action);
					fclose(fichier);
					fclose(fichierSortie);
					return 1;
				}
			break;
			case DEPLACER_TEXTURE:
				if(fscanf(fichier, "%u %s", &argument2, action) != 2) {
					printf("Ligne %u : Pas assez d'arguments à \"deplacer\".\n", numLigne);
					fclose(fichier);
					fclose(fichierSortie);
					return 1;
				}
				
				argument1 = indexOf(action, argumentsDeplacer, 4);
				if(argument1 == (unsigned int)-1) {
					printf("Ligne %u : Argument 1 invalide (%s obtenu).\n", numLigne, action);
					fclose(fichier);
					fclose(fichierSortie);
					return 1;
				}
			break;
			case MODIFIER_TAILLE_TEXTURE:
				if(fscanf(fichier, "%ux%u", &argument1, &argument2) != 2) {
					printf("Ligne %u : Pas assez d'arguments à \"redimensionner\".\n", numLigne);
					fclose(fichier);
					fclose(fichierSortie);
					return 1;
				}
			break;
			case MODIFIER_ANGLE:
				if(fscanf(fichier, "%u %s", &argument2, action) != 2) {
					printf("Ligne %u : Pas assez d'arguments à \"modif_angle\".\n", numLigne);
					fclose(fichier);
					fclose(fichierSortie);
					return 1;
				}
				
				argument1 = indexOf(action, argumentsAbsRel, 2);
				if(argument1 == (unsigned int)-1) {
					printf("Ligne %u : Argument 1 invalide (%s obtenu).\n", numLigne, action);
					fclose(fichier);
					fclose(fichierSortie);
					return 1;
				}
			break;
			case MODIFIER_CENTRE_ROTATION:
				if(fscanf(fichier, "(%u,%u)", &argument1, &argument2) != 2) {
					printf("Ligne %u : Pas assez d'arguments à \"modif_centre\".\n", numLigne);
					fclose(fichier);
					fclose(fichierSortie);
					return 1;
				}
			break;
			case MODIFIER_FLIP:
				if(fscanf(fichier, "%s", action) != 1) {
					printf("Ligne %u : Pas assez d'arguments à \"modif_flip\".\n", numLigne);
					fclose(fichier);
					fclose(fichierSortie);
					return 1;
				}
				
				argument1 = indexOf(action, argumentsFlip, 2);
				if(argument1 == (unsigned int)-1) {
					printf("Ligne %u : Argument 1 invalide (%s obtenu).\n", numLigne, action);
					fclose(fichier);
					fclose(fichierSortie);
					return 1;
				}
				
				argument2 = 0;
			break;
			
			// Correspond à "fin".
			case NB_ACTIONS_ANIMATION:
				// On recommence les ajouts à partir de 0.
				IDelemEnCoursDajout = 0;
				// On avance d'une animation.
				IDanimationEnCours++;
				
				// Saute le reste de la boucle, ie l'ajout d'un élément à l'animation en cours.
				// Puisqu'il n'y a rien à ajouter.
				continue;
			break;
			
			default:
				printf("Ligne %u : Action inconnue ??? %s -> %u\n", numLigne, action, IDaction);
					fclose(fichier);
					fclose(fichierSortie);
				return 1;
		}
		
		// On cherche un élément identique.
		unsigned int i = 0;
		for( ; i < IDinsertionElem; i++) {
			// On regarde si l'élément qu'on veut ajouter existe déjà.
			if(elemsAnimation[i].IDaction == IDaction && elemsAnimation[i].argument1 == argument1 && elemsAnimation[i].argument2 == argument2) {
				// On a trouvé un autre élément qui convient.
				ressourcesAnimations[IDanimationEnCours].elementsAnimations[IDelemEnCoursDajout] = i;
				
				// On quitte la boucle (et i != IDinsertionElem, sinon on ne serait pas ici)
				break;
			}
		}
		if(i == IDinsertionElem) {
			if(i == NB_ELEMS_ANIM_PAR_TEXTURE) {
				printf("Ligne %u : Capacité d'éléments d'animation (%u) dépassée !\n", numLigne, NB_ELEMS_ANIM_PAR_TEXTURE);
				fclose(fichier);
				fclose(fichierSortie);
				return 2;
			}
			
			// On doit en rajouter un nouveau.
			ressourcesAnimations[IDanimationEnCours].elementsAnimations[IDelemEnCoursDajout] = i;
			elemsAnimation[i].IDaction = IDaction;
			elemsAnimation[i].argument1 = argument1;
			elemsAnimation[i].argument2 = argument2;
			
			// On en a rajouté un.
			IDinsertionElem++;
		}
	}
	
	
	printf("\nÉcriture des éléments terminée.\n(%u écritures réalisées)\n\nÉcriture des animations terminée.\n(%u écritures réalisées)\n\nÉcriture du fichier %s...\n", IDinsertionElem, IDanimationEnCours, argv[2]);
	fwrite(&IDinsertionElem, sizeof(unsigned int), 1, fichierSortie);
	fwrite(&IDanimationEnCours, sizeof(unsigned int), 1, fichierSortie);
	fwrite(elemsAnimation, sizeof(ElemAnimTexture), IDinsertionElem, fichierSortie);
	fwrite(ressourcesAnimations, sizeof(RessourceAnimation), IDanimationEnCours, fichierSortie);
	
	printf("Fermeture des fichiers...\n");
	fclose(fichierSortie);
	fclose(fichier);
	
	printf("AnimExport a terminé.\n");
	return 0;
}

