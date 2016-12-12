
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
// #### Fonctions de BASTON ####
// #############################


#include <stdio.h>
#include <string.h>

#include "baston.h"
#include "defines.h"
#include "moteur_graphique.h"
#include "menus.h"
#include "aevilia.h"
#include "utilitaires.h"


unsigned int numFormationBataille	= (unsigned int)-1;
PosPixel posCameraVert_overworld;
PosPixel posCameraHoriz_overworld;

#define NB_TEXTURES_CHARGEES_SIMULTANEMENT	64
unsigned char nbInstancesChargees[NB_TEXTURES_CHARGEES_SIMULTANEMENT] = {[0 ... NB_TEXTURES_CHARGEES_SIMULTANEMENT - 1] = 0};
char nomsFichiersInfosTextures[NB_TEXTURES_CHARGEES_SIMULTANEMENT][FILENAME_MAX];
RessourceTextureCombat* __restrict__ ressourcesTexturesCombat[NB_TEXTURES_CHARGEES_SIMULTANEMENT];


Protagoniste* chargerProtagoniste(const char* nomFichierProtagoniste) {
	LOGGER("Chargement d'une instance de ")
	fprintf(fichierLog, nomFichierProtagoniste);
	
	// On commence par allouer la RAM pour le Protagoniste.
	Protagoniste* protagoniste = malloc(sizeof(Protagoniste));
	if(!protagoniste) {
		ERROR("Impossible d'allouer les ")
		fprintf(fichierLog, "%lu octets pour un Protagoniste.", sizeof(Protagoniste));
		
		return NULL;
	}
	
	FILE* fichierProtagoniste = chargerFichier("combat", nomFichierProtagoniste, "r");
	if(!fichierProtagoniste) {
		free(protagoniste);
		return NULL;
	}
	
	// On va charger les textures nécessaires.
	unsigned int i = 0;
	unsigned int echec = 0;
	char nomFichierTexture[FILENAME_MAX];
	for( ; fgets(nomFichierTexture, FILENAME_MAX, fichierProtagoniste) && i < NB_TEXTURES_PAR_PROTAGONISTE && !echec; i++) {
		protagoniste->textures[i] = chargerTextureCombat(nomFichierTexture);
		if(!protagoniste->textures[i]) {
			echec = 1;
		}
	}
	
	if(echec) {
		ERROR("Le chargement a échoué.")
		// On décharge toutes les textures chargées.
		while(i != 0) {
			dechargerTextureCombat(protagoniste->textures[i]);
		}
		// On libère la RAM du protagoniste.
		free(protagoniste);
		// Et on retourne... rien.
		return NULL;
	}
	
	return protagoniste;
}

void dechargerProtagoniste(Protagoniste* __restrict__ protagoniste) {
	unsigned int i = 0;
	while(protagoniste->textures[i] && i < NB_TEXTURES_PAR_PROTAGONISTE) {
		dechargerTextureCombat(protagoniste->textures[i]);
	}
	
	free(protagoniste);
}


TextureCombat* chargerTextureCombat(const char* nomFichierTexture) {
	LOGGER("Chargement d'une texture ")
	fprintf(fichierLog, nomFichierTexture);
	
	// On commence par allouer la texture.
	TextureCombat* __restrict__ texture = malloc(sizeof(TextureCombat));
	if(IMPROBABLE(!texture)) {
		ERROR("Échec de l'allocation de la texture ")
		fprintf(fichierLog, "%s. Taille : %lu octets.", nomFichierTexture, sizeof(TextureCombat));
		
		return NULL;
	}
	
	unsigned int IDtexture = -1;
	unsigned int IDtextureLibre = -1;
	// On va voir si la texture n'a pas déjà été chargée...
	unsigned int i = 0;
	for( ; i < NB_TEXTURES_CHARGEES_SIMULTANEMENT && IDtexture == (unsigned int)-1; i++) {
		if(nbInstancesChargees[i]) {
			// Déjà une instance chargée, le nom de fichier stocké a donc un sens.
			if(!(strcmp(nomFichierTexture, nomsFichiersInfosTextures[i]))) {
				// On a trouvé notre texture !
				IDtexture = i;
			}
		} else if(IDtextureLibre == (unsigned int)-1) {
			// Premier emplacement libre.
			IDtextureLibre = i;
		}
	}
	
	// La texture n'a jamais encore été chargée ?
	if(IDtexture == (unsigned int)-1) {
		LOGGER("Chargement de la première instance...")
		
		// A-t-on modifié IDtextureLibre ? (ie, a-t-on trouvé un slot libre ?)
		if(IDtextureLibre == (unsigned int)-1) {
			ERROR("Tous les emplacements de textures sont occupés !")
			
			free(texture);
			
			return NULL;
		}
#ifndef PRODUCTION
		if(NB_TEXTURES_CHARGEES_SIMULTANEMENT - IDtextureLibre < 5) {
			WARN("Occupation des textures dangereusement haute ! ")
			fprintf(fichierLog, "%d slots occupés sur %d.", IDtextureLibre, NB_TEXTURES_CHARGEES_SIMULTANEMENT);
		}
#endif
		// On a une place libre pour charger.
		LOGGER("Chargement dans le slot ")
		fprintf(fichierLog, "%d.", IDtextureLibre);
		
		// On se l'attribue, et on y place notre nom.
		IDtexture = IDtextureLibre;
		strncpy(nomsFichiersInfosTextures[IDtexture], nomFichierTexture, FILENAME_MAX - 1);
		
		
		// Fichier de métadonnées.
		FILE* fichierDonneesTexture = chargerFichier("combat", nomFichierTexture, "r");
		
		LOGGER("Chargement du fichier combat/")
		fprintf(fichierLog, nomFichierTexture);
		
		// On ouvre le fichier d'infos.
		if(!fichierDonneesTexture) {
			ERROR("Impossible d'ouvrir le fichier ")
			fprintf(fichierLog, "%s.", nomFichierTexture);
			
			return NULL;
		}
		
		
		// Variables que nous allons remplir.
		RessourceTextureCombat* ressource;
		unsigned int longueurNomFichierImage;
		unsigned int maxElements[LONG_NB_ELEMS] = {NB_MASQUES_DIFFERENTS_PAR_TEXTURE, NB_PARAMS_DIFFERENTS_PAR_TEXTURE, NB_ELEMS_ANIM_PAR_TEXTURE, NB_ANIMATIONS_PAR_TEXTURE};
		char nomFichierImage[FILENAME_MAX+1] = "";
		
		// Indique quels éléments ont été chargés. Mettre à jour à chaque fois qu'une action nécessitant d'être annulée (malloc, fopen, etc) est terminée.
		enum {
			FICHIER,
			RESSOURCE,
			IMAGE,
			MASQUES,
			ELEMENTS_ANIMATIONS,
			ANIMATIONS_TEXTURE
		} progressionChargement = FICHIER;
		
		// A appeler pour tout annuler, en fonction de progressionChargement.
		TextureCombat* echec(void) {
			unsigned int i = 0;
			
			switch(progressionChargement) {
				case ANIMATIONS_TEXTURE:
					for( ; i < ressource->nbElems[NB_ANIMATIONS]; i++) {
						free(ressource->animations[i]);
					}
				case ELEMENTS_ANIMATIONS:
					free(ressource->elemsAnimation);
				case MASQUES:
					if(ressource->nbElems[NB_MASQUES]) {
						for(i = 0; i < ressource->nbElems[NB_MASQUES]; i++) {
							free((*ressource->masques)[i]);
						}
						free(ressource->masques);
					}
				case IMAGE:
					dechargerImage(&ressource->image);
				case RESSOURCE:
					free(ressource);
				case FICHIER:
					fclose(fichierDonneesTexture);
				break;
			}
			
			return NULL;
		}
		
		
		// On tente d'allouer la RessourceTextureCombat.
		ressource = malloc(sizeof(RessourceTextureCombat));
		if(!ressource) {
			ERROR("Impossible d'allouer la RessourceTextureCombat ! Taille : ")
			fprintf(fichierLog, "%lu octets.", sizeof(RessourceTextureCombat));
			
			return echec();
		}
		
		// Surtout pour les animations, on initialise la mémoire à zéro.
		memset(ressource, 0, sizeof(RessourceTextureCombat));
		
		progressionChargement++; // RESSOURCE
		
		
		if(!fread(&longueurNomFichierImage, sizeof(unsigned int), 1, fichierDonneesTexture)) {
			if(feof(fichierDonneesTexture)) {
				ERROR("Pas assez de données dans le fichier !")
			} else {
				ERROR("Erreur de lecture du fichier !")
			}
			
			return echec();
		}
		
		if(longueurNomFichierImage >= FILENAME_MAX) {
			ERROR("Nom de fichier image trop long ! ")
			fprintf(fichierLog, "%d octets demandés, %d disponibles.", longueurNomFichierImage, FILENAME_MAX);
			
			return echec();
		}
		
		if(fread(ressource->nbElems, sizeof(unsigned int), LONG_NB_ELEMS, fichierDonneesTexture) < LONG_NB_ELEMS) {
			if(feof(fichierDonneesTexture)) {
				ERROR("Pas assez de données dans le fichier !")
			} else {
				ERROR("Erreur de lecture du fichier !")
			}
			
			return echec();
		}
		
		unsigned int i = 0;
		for( ; i < LONG_NB_ELEMS; i++) {
			if(ressource->nbElems[i] >= maxElements[i]) {
				ERROR("Capacité demandée trop grande ! ")
				fprintf(fichierLog, "Attribut %d : %u demandé > %u possible.", i, ressource->nbElems[i], maxElements[i]);
				
				return echec();
			}
		}
		
		
		if(fread(nomFichierImage, sizeof(char), longueurNomFichierImage, fichierDonneesTexture) < longueurNomFichierImage) {
			if(feof(fichierDonneesTexture)) {
				ERROR("Pas assez de données dans le fichier !")
			} else {
				ERROR("Erreur de lectuer du fichier !")
			}
			
			return echec();
		}
		nomFichierImage[longueurNomFichierImage] = 0; // On force la terminaison de la chaîne.
		
		if(chargerImage(nomFichierImage, &ressource->image)) {
			// chargerImage() imprime son message d'erreur.
			ERROR("Erreur de chargement de l'image.")
			
			return echec();
		}
		
		progressionChargement++; // IMAGE
		
		if(ressource->nbElems[NB_MASQUES]) {
			size_t taille_collec_masques = sizeof(unsigned int (*[ressource->nbElems[NB_MASQUES]])[32]);
			ressource->masques = malloc(taille_collec_masques);
			if(!ressource->masques) {
				ERROR("Impossible d'allouer la collection de masques ! ")
				fprintf(fichierLog, "Taille : %lu", taille_collec_masques);
				
				return echec();
			}
			
			// Ce qui est important, c'est de désallouer les masques en cas d'échec. Le code préparant l'échec se charge d'empêcher que de la mémoire non initialsée ne soit lue. De plus, masques ne valant pas NULL, on n'aura pas de segfault.
			progressionChargement++; // MASQUES
			
			unsigned int (*masque)[32];
			for(i = 0; i < ressource->nbElems[NB_MASQUES]; i++) {
				masque = malloc(sizeof(unsigned int[32]));
				(*ressource->masques)[i] = masque; // Peut être NULL en cas d'échec ; lire les commentaires juste avant l'appel à echec() pour de plus amples informations.
				
				if(!masque) {
					ERROR("Erreur d'allocation du masque n°")
					fprintf(fichierLog, "%d (%lu octets)", i, sizeof(unsigned int[32]));
					
					ressource->nbElems[NB_MASQUES] = i+1; // Comme la mémoire de masques n'a pas été initialisée, il ne faut pas que echec() ne lise plus loin que ce masque-ci.
					// Mettre i est une faute, car si on échoue à allouer le premier masque, free(masques) ne sera pas exécuté !
					// On va juste exécuter un free(NULL) de plus que nécessaire. Bah.
					
					return echec();
				}
				
				// On remplit.
				if(fread(masque, sizeof(unsigned int), 32, fichierDonneesTexture) < 32) {
					if(feof(fichierDonneesTexture)) {
						ERROR("Pas assez de données dans le fichier !")
					} else {
						ERROR("Erreur lors de la lecture du fichier.")
					}
					
					ressource->nbElems[NB_MASQUES] = i+1;
					
					return echec();
				}
				// Il n'y a plus rien à faire (le dernier truc était le fread() dans le if)
			}
		} else {
			// S'il n'y a pas de masques, on ne va pas en allouer.
			ressource->masques = NULL;
			
			progressionChargement++; // MASQUES
		}
		
		
		if(ressource->nbElems[NB_PARAMS_RENDU]) {
			RessourceParamTextureCombat ressourcesParams[ressource->nbElems[NB_PARAMS_RENDU]];
			
			if(fread(ressourcesParams, sizeof(RessourceTextureCombat), ressource->nbElems[NB_PARAMS_RENDU], fichierDonneesTexture) < ressource->nbElems[NB_PARAMS_RENDU]) {
				if(feof(fichierDonneesTexture)) {
					ERROR("Pas assez de données dans le fichier !")
				} else {
					ERROR("Erreur lors de la lecture du fichier.")
				}
				
				return echec();
			}
			
			for(i = 0; i < ressource->nbElems[NB_PARAMS_RENDU]; i++) {
				ressource->paramsSource[i].rectSource = ressourcesParams[i].rectSource;
				ressource->paramsSource[i].modeRendu = ressourcesParams[i].modeRendu;
				
				ModeRendu modeRendu = ressourcesParams[i].modeRendu;
				if(modeRendu == MASQUE || modeRendu == MOITIE_GAUCHE || modeRendu == MOITIE_DROITE) {
					if(ressourcesParams[i].IDmasque >= ressource->nbElems[NB_MASQUES]) {
						ERROR("Paramètre de rendu ")
						fprintf(fichierLog, "%d : ID de masque invalide ! Maximum possible : %d, demandé : %d", i, ressource->nbElems[NB_MASQUES] - 1, ressourcesParams[i].IDmasque);
						
						return echec();
					}
					
					ressource->paramsSource[i].masque = (*ressource->masques)[ressourcesParams[i].IDmasque];
				}
			}
		}
		
		progressionChargement++; // ELEMENTS_ANIMATIONS
		
		if(ressource->nbElems[NB_ELEMS_ANIM]) {
			size_t size = sizeof(ElemAnimTexture[ressource->nbElems[NB_ELEMS_ANIM]]);
			ElemAnimTexture (*elems)[ressource->nbElems[NB_ELEMS_ANIM]] = malloc(size);
			if(!elems) {
				ERROR("Impossible d'allouer la collection d'éléments d'animation ! ")
				fprintf(fichierLog, "Taille : %lu", size);
				
				return echec();
			}
			
			ressource->elemsAnimation = elems;
			
			if(fread(elems, sizeof(ElemAnimTexture), ressource->nbElems[NB_ELEMS_ANIM], fichierDonneesTexture) < ressource->nbElems[NB_ELEMS_ANIM]) {
				if(feof(fichierDonneesTexture)) {
					ERROR("Le fichier ne contient pas assez de données !")
				} else {
					ERROR("Erreur lors de la lecture du fichier.")
				}
				
				return echec();
			}
		} else {
			ressource->elemsAnimation = NULL;
		}
		
		progressionChargement++; // ANIMATIONS
		
		if(ressource->nbElems[NB_ANIMS]) {	
			RessourceAnimation ressourceAnimation;
			
			for(i = 0; i < ressource->nbElems[NB_ANIMS]; i++) {
				Animation* animation = malloc(sizeof(Animation));
				if(!animation) {
					ERROR("Impossible d'allouer les animations !")
					fprintf(fichierLog, "%d déjà allouées, taille %lu", i, sizeof(Animation));
					
					// Ici, le tableau n'est pas à désallouer, donc on n'a pas à forcer le nombre à être non nul.
					ressource->nbElems[NB_ELEMS_ANIM] = i;
					
					return echec();
				}
				
				if(!fread(&ressourceAnimation, sizeof(RessourceAnimation), 1, fichierDonneesTexture)) {
					if(feof(fichierDonneesTexture)) {
						ERROR("Pas assez de données dans le fichier !")
					} else {
						ERROR("Erreur lors de la lecture du fichier.")
					}
					
					ressource->nbElems[NB_ELEMS_ANIM] = i;
					
					return echec();
				}
				
				ressource->animations[i] = animation;
				animation->nbElementsAnim = ressourceAnimation.nbElementsAnim;
				
				unsigned int j = 0;
				for(j = 0; j < ressourceAnimation.nbElementsAnim; j++) {
					if(ressourceAnimation.elementsAnimations[j] >= ressource->nbElems[NB_ELEMS_ANIM]) {
						ERROR("Animation ")
						fprintf(fichierLog, "%d : ID d'élément invalide ! Maximum possible : %d, demandé : %d", j, ressource->nbElems[NB_ELEMS_ANIM] - 1, ressourceAnimation.elementsAnimations[j]);
						
						ressource->nbElems[NB_ELEMS_ANIM] = i;
						
						return echec();
					}
					
					animation->elementsAnimation[j] = &(*ressource->elemsAnimation)[ressourceAnimation.elementsAnimations[j]];
				}
			}
		}
		
		
		fclose(fichierDonneesTexture);
		ressourcesTexturesCombat[IDtexture] = ressource;
	}
	
	LOGGER("Remplissage de l'instance...")
	texture->IDtexture = IDtexture;
	texture->img = &ressourcesTexturesCombat[IDtexture]->image;
	texture->numParamActif = 0;
	texture->paramsSource = ressourcesTexturesCombat[IDtexture]->paramsSource;
	texture->rectDest.x = 0;
	texture->rectDest.y = 0;
	texture->rectDest.w = 0;
	texture->rectDest.h = 0;
	texture->angle = 0;
	texture->centre.x = 0;
	texture->centre.y = 0;
	texture->animationEnCours = NULL;
	texture->IDanimEnCours = 0;
	texture->timerAnim = 0;
	
	nbInstancesChargees[IDtexture]++;
	return texture;
}

void dechargerTextureCombat(TextureCombat* __restrict__ texture) {
	if(!--nbInstancesChargees[texture->IDtexture]) {
		RessourceTextureCombat* ressource = ressourcesTexturesCombat[texture->IDtexture];
		unsigned int i = 0;
		
		for( ; i < ressource->nbElems[NB_ANIMS]; i++) {
			free(ressource->animations[i]);
		}
		
		// Peut être NULL. D'après le  standard, free(NULL) ne fait rien, donc c'est bon.
		free(ressource->elemsAnimation);
		
		// ressource->masques peut valoir NULL, mais c'est si et seulement si ressource->nbElems[NB_MASQUES] == 0. Donc no problemo !
		for(i = 0; i < ressource->nbElems[NB_MASQUES]; i++) {
			free((*ressource->masques)[i]);
		}
		// Peut aussi être NULL.
		free(ressource->masques);
		
		dechargerImage(&ressource->image);
		
		free(ressource);
	}
	free(texture);
}


void rendreCopieEx(SDL_Texture* texture, const SDL_Rect* rectSource, const SDL_Rect* rectDest, const double angle, const SDL_Point* centre, const SDL_RendererFlip flip) {
	SDL_Rect rDest = {rectDest->x * taillePixel, rectDest->y * taillePixel, rectDest->w * taillePixel, rectDest->h * taillePixel};
	if(FLAG(PLEIN_ECRAN_ACTIF)) {
		rDest.x += boiteHoriz;
		rDest.y += boiteVert;
	}
	
	SDL_Point pointRotation = {centre->x * taillePixel, centre->y * taillePixel};
	
	SDL_RenderCopyEx(pRendu, texture, rectSource, &rDest, angle, &pointRotation, flip);
}

void rendreTextureCombat(TextureCombat* texture) {
	ModeRendu modeRendu		= texture->paramsSource[texture->numParamActif].modeRendu;
	
	// S'il n'y a pas de transparence à appliquer, on rend la tile entière direct.
	if(modeRendu == OPAQUE) {
		SDL_Rect rectDest = {texture->rectDest.x - positionHorizCamera, texture->rectDest.y - positionVertCamera, texture->rectDest.w, texture->rectDest.h};
		
		rendreCopieEx(texture->img->texture, &texture->paramsSource[texture->numParamActif].rectSource, &rectDest, texture->angle, &texture->centre, 0);
		return;
	} else if(modeRendu == TRANSPARENT) {
		return;
	}
	
	// Tableau de masques de rendu. Supportent du 32 pixels de large au max.
	unsigned int* masques	= *texture->paramsSource[texture->numParamActif].masque;
	unsigned int masque;
	
	unsigned int ligne		= 0;
	unsigned int colonne;
	
	unsigned int nbColonnes	= texture->paramsSource[texture->numParamActif].rectSource.w;
	unsigned int nbLignes	= texture->paramsSource[texture->numParamActif].rectSource.h;
	
	unsigned int rectSourceX = texture->paramsSource[texture->numParamActif].rectSource.x;
	SDL_Rect rectSource		= {0, texture->paramsSource[texture->numParamActif].rectSource.y, 0, 1};
	SDL_Rect rectDest		= {texture->rectDest.x - positionHorizCamera, texture->rectDest.y - positionVertCamera, 0, 0};
	
	double vert = rectDest.y;
	double horiz;
	double pasVert = (double)texture->rectDest.h / (double)nbLignes;
	double pasHoriz = (double)texture->rectDest.w / (double)nbColonnes;
	unsigned int epaisseurHoriz;
	
	unsigned int bitDeRendu = 1 << (nbColonnes - 1);
	
	SDL_Point pointRotation = {texture->centre.x, texture->centre.y};
	
	if(modeRendu == MOITIE_GAUCHE) {
		vert += nbColonnes / 2;
		
		rectSource.w = nbColonnes / 2;
		rectSource.h = nbLignes;
		rectDest.w = texture->rectDest.w / 2;
		rectDest.h = texture->rectDest.h;
		
		// colonne est ici utilisée comme compteur de lignes, mais bon. On économise du calcul...
		for(colonne = 0; colonne < nbLignes; colonne++) {
			masques[colonne] <<= (nbColonnes + 1) / 2;
		}
		
		nbColonnes = (nbColonnes + 1) / 2;
		
		rendreCopieEx(texture->img->texture, &rectSource, &rectDest, texture->angle, &texture->centre, 0);
		
		rectSource.x += rectSource.w;
		rectSource.w = 1;
		rectSource.h = 1;
		pointRotation.x += rectDest.w / 2;
		rectDest.x += rectDest.w;
		rectDest.w = 0;
		rectDest.h = 0;
	} else if(modeRendu == MOITIE_DROITE) {
		rectSource.x += nbColonnes / 2;
		rectSource.w = nbColonnes / 2;
		rectSource.h = nbLignes;
		rectDest.x += pasHoriz * (nbColonnes / 2);
		rectDest.w = texture->rectDest.w / 2;
		rectDest.h = texture->rectDest.h;
		
		nbColonnes = (nbColonnes + 1) / 2;
		
		rendreCopieEx(texture->img->texture, &rectSource, &rectDest, texture->angle, &texture->centre, 0);
		
		rectSource.x -= nbColonnes;
		rectSource.w = 1;
		rectSource.h = 1;
		pointRotation.x -= rectDest.w / 2;
		rectDest.x = texture->rectDest.x;
		rectDest.w = 0;
		rectDest.h = 0;
	}
	
	// On va afficher chaque ligne avec son masque, pixel à pixel.
	for( ; ligne < nbLignes && rectDest.y < HAUTEUR_RENDU; ligne++) {
		masque = masques[ligne];
		
		if(masque != 0x0000 && rectDest.y >= 0) {
			rectDest.x = texture->rectDest.x - positionHorizCamera;
			rectSource.x = rectSourceX;
			
			// On calcule la nouvelle épaisseur verticale.
			vert += pasVert;
			rectDest.h = vert - rectDest.y;
			
			// On réinitialise horiz.
			horiz = rectDest.x;
			pointRotation.x = texture->centre.x;
		
			for(colonne = 0; colonne < nbColonnes ; colonne++) {
				
				horiz += pasHoriz;
				epaisseurHoriz = horiz - rectDest.x - rectDest.w;
				
				// Si le pixel n'est pas transparent,
				if(masque & bitDeRendu) {
					rectDest.w += epaisseurHoriz;
					rectSource.w++;
				} else {
					if(rectDest.w) {
						pointRotation.x = texture->centre.x - rectDest.x + texture->rectDest.x - positionHorizCamera;
						rendreCopieEx(texture->img->texture, &rectSource, &rectDest, texture->angle, &pointRotation, 0);
						rectDest.x += rectDest.w;
						rectSource.x += rectDest.w;
						rectDest.w = 0;
						rectSource.w = 0;
					}
					rectDest.x += epaisseurHoriz;
					rectSource.x++;
				}
		
				masque <<= 1;
			}
			
			if(rectDest.w) {
				pointRotation.x = texture->centre.x + rectDest.x - texture->rectDest.x - positionHorizCamera;
				rendreCopieEx(texture->img->texture, &rectSource, &rectDest, texture->angle, &pointRotation, 0);
				rectDest.w = 0;
				rectSource.w = 0;
			}
		}
		
		rectDest.y += rectDest.h;
		rectSource.y++;
		pointRotation.y -= rectDest.h;
	}
}

void rendreProtagoniste(Protagoniste* protagoniste) {
	unsigned int i = 0;
	for( ; i < NB_TEXTURES_PAR_PROTAGONISTE; i++) {
		if(protagoniste->textures[i]) {
			rendreTextureCombat(protagoniste->textures[i]);
		}
	}
}


void demarrerBataille(unsigned int numFormation) {
	numFormationBataille = numFormation;
	posCameraVert_overworld = positionVertCamera;
	positionVertCamera = 0;
	posCameraHoriz_overworld = positionHorizCamera;
	positionHorizCamera = 0;
}

void terminerBataille(void) {
	positionVertCamera = posCameraVert_overworld;
	positionHorizCamera = posCameraHoriz_overworld;
}


void main__bataille(void) {
	Couche*			couchesBataille[3] /* Temporaire */ = {&couchesMapCourante[0], &couchesMapCourante[1], &couchesMapCourante[2]};
	
	unsigned int	masqueTeteJoueur[32]	= {0x003f00, 0x00ffc0, 0x03fff0, 0x07fff8, 0x0ffffc, 0x0ffffc, 0x1ffffe, 0x1ffffe, 0x3fffff, 0x3fffff, 0x3fffff, 0x3fffff, 0x3fffff, 0x3fffff, 0x1ffffe, 0x1ffffe, 0x0ffffc, 0x0ffffc, 0x07fff8, 0x03fff0, 0x00ffc0, 0x003f00};
	ParamTextureCombat paramsTeteJoueur[]	= {{.rectSource = {0, 0, 22, 22},
												.modeRendu = MASQUE,
												.masque = &masqueTeteJoueur}};
	
	Image									imgTeteJoueur;
	TextureCombat	textureTeteJoueur 		= { .img = &imgTeteJoueur,
												.numParamActif = 0,
												.paramsSource = paramsTeteJoueur,
												.rectDest = {200, 200, 22, 22},
												.angle = 0,
												.centre = {11, 11},
												.animationEnCours = NULL,
												.IDanimEnCours = 0,
												.timerAnim = 0};
	Protagoniste	joueurCombat = {.textures = {[0] = &textureTeteJoueur,
												 [1 ... NB_TEXTURES_PAR_PROTAGONISTE - 1] = NULL}};
	
	chargerImage("tete_test.bmp", &imgTeteJoueur);
	
	Protagoniste	ennemis[NB_ENNEMIS_MAX];
	
	while(1) {
		rendreFrame = FEU_ROUGE;
		
		if(enTeteMapCourante.scriptBataille != NULL) {
			enTeteMapCourante.scriptBataille();
		}
		
		traiterEvenements();
		
		// Effectuer le traitement de la frame ici.
		
		rendreBackground(positionVertCamera / 2, positionHorizCamera / 2, couchesBataille[0]);
		rendreBackground(positionVertCamera, positionHorizCamera, couchesBataille[1]);
		rendreProtagoniste(&joueurCombat);
		rendreBackground(positionVertCamera * 2, positionHorizCamera * 2, couchesBataille[2]);
		
		activerMenus();
		afficherBarreEtat();
		
		animer();
		
		if(etatTouches[INVENTAIRE]) {
			return;
		}
		
		IDframe++;
		while(rendreFrame != FEU_VERT) {
			SDL_Delay(1);
		}
		rendrePresent();
	}
	
	dechargerImage(&imgTeteJoueur);
}

