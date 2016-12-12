
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
// ###### Moteur graphique #####
// #############################


#include <SDL2/SDL.h>
#include <string.h>
#ifndef PRODUCTION
#include <time.h>
#endif

#include "moteur_graphique.h"
#include "defines.h"
#include "utilitaires.h"
#include "menus.h"



Image				imgTiles;

// NE JAMAIS EXÉCUTER DE CMD_EFFACER SUR CE MENU !!!
Menu barreEtat =	{.positionVert = HAUTEUR_FENETRE - NB_TILES_BARRE_ETAT * HAUTEUR_TILE,
					 .positionHoriz = 0,
					 .tailleVert = NB_TILES_BARRE_ETAT - 2,
					 .tailleHoriz = NB_TILES_LARG - 2,
					 .tailleHorizCourante = NB_TILES_LARG - 2,
					 .texte = L"   NOMJOUEUR \1   Niv 00 000/000 PV",
					 .nbCharsArendre = LONG_TEXTE_MENU - 1}; // On rend le texte instantané.
					 

void initialiserGraphismes(void) {
	
	// On initialise la SDL
	LOGGER("Initialisation de la SDL...")
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER)) {
		ERROR("La SDL n'a pas pu s'initialiser !")
		FATALERROR(SDL_GetError(), ERREUR_INIT_SDL)
	}
	
	LOGGER("Initialisation terminée.")
	
	// On crée la fenêtre
	LOGGER("Création de la fenêtre...")
	pFenetre = SDL_CreateWindow("Aevilia version 0.4.0", SDL_WINDOWPOS_UNDEFINED,
														 SDL_WINDOWPOS_UNDEFINED,
														 LARGEUR_FENETRE,
														 HAUTEUR_FENETRE,
														 SDL_WINDOW_SHOWN);
	// NULL signifie une erreur. On va ptêtre éviter la segfault :)
	if(pFenetre == NULL) {
		ERROR("La fenêtre n'a pas pu être ouverte !")
		FATALERROR(SDL_GetError(), ERREUR_CREATION_FENETRE)
	}
	
	LOGGER("Création du rendu...")
	// On tente de créer le SDL_Renderer
	pRendu = SDL_CreateRenderer(pFenetre, -1, FLAG(DESACTIVER_ACCEL_GPU) ? SDL_RENDERER_SOFTWARE : SDL_RENDERER_ACCELERATED);
	// NULL signifie une erreur. On va ptêtre éviter la redite :)
	if(pRendu == NULL) {
		// Pour les cas où l'accélération matérielle n'est pas supportée.
		pRendu = SDL_CreateRenderer(pFenetre, -1, SDL_RENDERER_SOFTWARE);
		if(pRendu == NULL) {
			ERROR("Le rendu n'a pas pu être créé !")
			FATALERROR(SDL_GetError(), ERREUR_CREATION_RENDU)
		} else {
			WARN("L'accélération matérielle n'est pas supportée. Un rendu logiciel est utilisé.")
			fprintf(fichierLog, SDL_GetError());
		}
	}
	LOGGER("Rendu créé.")
#ifndef PRODUCTION
	#define COULEUR_FOND	255, 0, 0
#else
	#define COULEUR_FOND	0, 0, 0
#endif
	if(SDL_SetRenderDrawColor(pRendu, COULEUR_FOND, 255)) { // Retourne 0 si tout va bien.
		WARN("Le nettoyage de l'écran ne peut pas s'effectuer !")
		DIRE("Le jeu va quand même tenter de s'exécuter, mais des bugs graphiques sont possibles.")
	} else {
		LOGGER("Nettoyage de l'écran prédéfini.")
	}
	
	LOGGER("Chargement du fichier de tiles...")
	if(chargerImage("tiles.bmp", &imgTiles) != SUCCES) {
		FATALERROR("Échec du chargement d'une ressource critique. Arrêt.", ERREUR_CHARGEMENT_IMAGE)
	}
	LOGGER("Chargement terminé.")
	
	pousserScript(PLEIN_ECRAN, pleinEcran);
	
	LOGGER("Le chargement des graphismes est terminé.")
}

// Veuillez (sauf si le contraire est requis) nettoyer dans l'ordre inverse du chargement !
void nettoyerGraphismes(void) {
	dechargerImage(&imgTiles);
	
	if(pRendu) {
		SDL_DestroyRenderer(pRendu);
	}
	
	if(pFenetre) {
		SDL_DestroyWindow(pFenetre);
	}
	
	SDL_Quit();
}


CodeRetour chargerImage(const char nom[], Image* img) {
	SDL_Surface* tempSurface = NULL;
	LOGGER("Chargement du fichier img/")
	fprintf(fichierLog, nom);
	
	strcpy(img->cheminNom, "img/");
	strncpy(img->cheminNom + 4 * sizeof(char), nom, FILENAME_MAX - 4 * sizeof(char) - 1);
	
	tempSurface = SDL_LoadBMP(img->cheminNom);
	if(!tempSurface) {
		ERROR("Erreur de création de la surface. Fichier :")
		fprintf(fichierLog, nom);
		ERROR(SDL_GetError())
		return ERREUR_CHARGEMENT_IMAGE;
	}
	
	img->texture = SDL_CreateTextureFromSurface(pRendu, tempSurface);
	if(!img->texture) {
		ERROR("Erreur de création de la texture. Fichier :")
		fprintf(fichierLog, nom);
		ERROR(SDL_GetError())
		return ERREUR_CHARGEMENT_IMAGE;
	}
	
	SDL_FreeSurface(tempSurface);
	
	return SUCCES;
}

void dechargerImage(Image* img) {
	if(img->texture) {
		LOGGER("Déchargement du fichier ")
		fprintf(fichierLog, img->cheminNom);
		
		SDL_DestroyTexture(img->texture);
		
		// On évite le use-after-free ?
		img->texture = NULL;
	}
}


wchar_t obtenirNumeroTile(unsigned int positionVert, unsigned int positionHoriz, const Couche* couche) {
	// Émule un tableau 2D avec un tableau 1D ; comme ça, on peut moduler les tailles maximales et optimiser l'utilsation mémoire.
	__builtin_prefetch(&couche->largeur, 1);
	if(positionVert >= couche->hauteur || positionHoriz >= couche->largeur) {
		return TRANSPARENT_BLOQUE;
	}
	return couche->tilemap[positionVert * couche->largeur + positionHoriz];
}

void modifierNumeroTile(unsigned int positionVert, unsigned int positionHoriz, Couche* couche, wchar_t tile) {
	if(positionHoriz < couche->largeur && positionVert < couche->hauteur) {
		couche->tilemap[positionVert * couche->largeur + positionHoriz] = tile;
	}
}

void ciblerTile(wchar_t numero, SDL_Rect* rectangle) {
	// tiles.bmp est organisé comme suit :
	// Une ligne correspond à une tile et comprend ses frames successives, alignées horizontalement.
	rectangle->y = numero * HAUTEUR_TILE; // On recherche la ligne (c'est simple)...
	rectangle->x = attributsTiles[numero]->frame * LARGEUR_TILE; // ...et on recherche la colonne (dépend de la frame).
}

void rendreCopie(const SDL_Rect* rectSource, const SDL_Rect* rectDest) {
	SDL_Rect rDest	= {rectDest->x * taillePixel, rectDest->y * taillePixel, rectDest->w * taillePixel, rectDest->h * taillePixel};
	SDL_Rect rSrc	= {rectSource->x, rectSource->y, rectSource->w, rectSource->h};
	
	if(rDest.y < 0) {
		if(rDest.y + rDest.h <= 0) {
			return;
		}
		
		rSrc.h += rectDest->y;
		rSrc.y -= rectDest->y;
		
		rDest.h += rDest.y; // rDest.y < 0 !
		rDest.y = 0;
	}
	
	if(rDest.x < 0) {
		if(rDest.x + rDest.w <= 0) {
			return;
		}
		
		rSrc.w += rectDest->x;
		rSrc.x -= rectDest->x;
		
		rDest.w += rDest.x; // rDest.x < 0 !
		rDest.x = 0;
	}
	
	if(FLAG(PLEIN_ECRAN_ACTIF)) {
		rDest.x += boiteHoriz;
		rDest.y += boiteVert;
	}
	
	SDL_RenderCopy(pRendu, imgTiles.texture, &rSrc, &rDest);
}

void rendrePresent(void) {
	if(!FLAG(DESSINER_BOITE)) {
		if(boiteVert != 0) {
			SDL_Rect rectSource = TILE(0, NOIR * HAUTEUR_TILE);
			SDL_Rect rectDest   = {0, 0, affichage.w * taillePixel, boiteVert};
			SDL_RenderCopy(pRendu, imgTiles.texture, &rectSource, &rectDest);
			rectDest.y += HAUTEUR_FENETRE * taillePixel + rectDest.h;
			SDL_RenderCopy(pRendu, imgTiles.texture, &rectSource, &rectDest);
		}
		if(boiteHoriz != 0) {
			SDL_Rect rectSource = TILE(0, NOIR * HAUTEUR_TILE);
			SDL_Rect rectDest   = {0, 0, boiteHoriz, affichage.h * taillePixel};
			SDL_RenderCopy(pRendu, imgTiles.texture, &rectSource, &rectDest);
			rectDest.x += LARGEUR_FENETRE * taillePixel + rectDest.w;
			SDL_RenderCopy(pRendu, imgTiles.texture, &rectSource, &rectDest);
		}
	}
	SDL_RenderPresent(pRendu);
}

void afficherRect(const SDL_Rect* rectSource, unsigned int positionVert, unsigned int positionHoriz) {
	SDL_Rect rectDest = TILE(positionHoriz, positionVert);	
	
	rendreCopie(rectSource, &rectDest);
}

void afficherTile(wchar_t numero, unsigned int positionVert, unsigned int positionHoriz) {
	ModeRendu modeRendu		= transparences[numero]->modeRendu;
	
	// S'il n'y a pas de transparence à appliquer, on rend la tile entière direct.
#ifndef PRODUCTION
	if(modeRendu == OPAQUE || (__DEBUG__debuggerCouches != 0 && numero == TRANSPARENT_BLOQUE)) {
#else
	if(modeRendu == OPAQUE) {
#endif
		SDL_Rect rectSource = {0, 0, LARGEUR_TILE, HAUTEUR_TILE};
		ciblerTile(numero, &rectSource);
		
		afficherRect(&rectSource, positionVert, positionHoriz);
		return;
#ifndef PRODUCTION
	} else if(modeRendu == TRANSPARENT) { // Pour aligner les accolades pour la coloration de gedit.
#else
	} else if(modeRendu == TRANSPARENT) {
#endif
		return;
	}
	
	// Tableau de masques de rendu. Supportent du 32 pixels de large au max.
	unsigned int* masques	= *transparences[numero]->transparence[attributsTiles[numero]->frame];
	unsigned int masque;
	
	unsigned int ligne		= 0;
	unsigned int colonne;
	
	SDL_Rect rectDest		= {positionHoriz, positionVert, 0, 1};
	SDL_Rect rectSource		= {0, 0, 0, 1};
	ciblerTile(numero, &rectSource);
	unsigned int vert		= rectSource.x;
	
	if(modeRendu == MOITIE_GAUCHE) {
		rectSource.w = LARGEUR_TILE / 2;
		rectSource.h = HAUTEUR_TILE;
		rectDest.w = LARGEUR_TILE / 2;
		rectDest.h = HAUTEUR_TILE;
		
		rendreCopie(&rectSource, &rectDest);
		
		rectSource.w = 1;
		rectSource.h = 1;
		rectDest.w = 0;
		rectDest.h = 1;
	} else if(modeRendu == MOITIE_DROITE) {
		rectSource.x += LARGEUR_TILE / 2;
		rectSource.w = LARGEUR_TILE / 2;
		rectSource.h = HAUTEUR_TILE;
		rectDest.x = positionHoriz + LARGEUR_TILE / 2;
		rectDest.w = LARGEUR_TILE / 2;
		rectDest.h = HAUTEUR_TILE;
		
		rendreCopie(&rectSource, &rectDest);
		
		rectSource.x -= LARGEUR_TILE / 2;
		rectSource.w = 1;
		rectSource.h = 1;
		rectDest.w = 0;
		rectDest.h = 1;
	}
	
	// On va afficher chaque ligne avec son masque, pixel à pixel.
	for( ; ligne < HAUTEUR_TILE && rectDest.y < HAUTEUR_FENETRE; ligne++) {
		masque = masques[ligne];
		
		if(masque != 0x0000 && rectDest.y >= 0) {
			rectDest.x = positionHoriz;
			rectSource.x = vert;
			
			if(modeRendu == MOITIE_GAUCHE) {
				masque <<= 8;
				rectSource.x += LARGEUR_TILE / 2;
				rectDest.x += LARGEUR_TILE / 2;
			}
		
			for(colonne = 0; colonne < ((modeRendu == MOITIE_GAUCHE || modeRendu == MOITIE_DROITE) ? LARGEUR_TILE / 2 : LARGEUR_TILE) ; colonne++) {
				// Si le pixel n'est pas transparent,
				if(masque & 0x8000 && rectDest.x >= 0) {
					rectDest.w++;
					rectSource.w++;
				} else {
					if(rectDest.w) {
						rendreCopie(&rectSource, &rectDest);
						rectDest.x += rectDest.w;
						rectSource.x += rectDest.w;
						rectDest.w = 0;
						rectSource.w = 0;
					}
					rectDest.x++;
					rectSource.x++;
				}
		
				masque <<= 1;
			}
			
			if(rectDest.w) {
				rendreCopie(&rectSource, &rectDest);
				rectDest.w = 0;
				rectSource.w = 0;
			}
		}
		
		rectDest.y++;
		rectSource.y++;
	}
}

// Attention : les positions sont en pixels...
void rendreBackground(unsigned int positionVert, unsigned int positionHoriz, const Couche* couche) {
	unsigned int positionVertLecture0	= positionVert / HAUTEUR_TILE;
	unsigned int positionHorizLecture0	= positionHoriz / LARGEUR_TILE;
	
	unsigned int nbPixelsDecalageVert	= positionVert % HAUTEUR_TILE;
	unsigned int nbPixelsDecalageHoriz	= positionHoriz % LARGEUR_TILE;
	
	unsigned int curseurVert = 0;
	unsigned int curseurHoriz;
	
	for( ; curseurVert <= (FLAG(AFFICHER_BARRE_ETAT) ? NB_TILES_HAUT - NB_TILES_BARRE_ETAT : NB_TILES_HAUT); curseurVert++) {
		for(curseurHoriz = 0; curseurHoriz <= NB_TILES_LARG; curseurHoriz++) {
			wchar_t numeroTile = obtenirNumeroTile(positionVertLecture0 + curseurVert, positionHorizLecture0 + curseurHoriz, couche);
			
			afficherTile(numeroTile, curseurVert * HAUTEUR_TILE - nbPixelsDecalageVert, curseurHoriz * LARGEUR_TILE - nbPixelsDecalageHoriz);
		}
	}
}

void rendreSprite(const Sprite* sprite) {
#ifndef PRODUCTION
	if(__DEBUG__debuggerSprites != 0) {
		SDL_Rect rectSource	= TILE(LARGEUR_TILE, HAUTEUR_TILE);
		SDL_Rect rectDest	= TILE(sprite->positionHoriz - positionHorizCamera, sprite->positionVert - positionVertCamera);
		rendreCopie(&rectSource, &rectDest);
		return;
	}
#endif
	if(positionVertCamera + 1 <= sprite->positionVert + HAUTEUR_TILE && positionHorizCamera + 1 <= sprite->positionHoriz + LARGEUR_TILE && sprite->tile > TRANSPARENT_MARCHE) {
		afficherTile(sprite->tile + ((sprite->direction < VALIDER) ? sprite->direction : 0), sprite->positionVert - positionVertCamera, sprite->positionHoriz - positionHorizCamera);
	}
}

void rendreMap(unsigned int positionVert, unsigned int positionHoriz) {
	unsigned int numCouche = 0;
	unsigned int numSprite;
	
	SDL_RenderClear(pRendu);
	for( ; numCouche < enTeteMapCourante.nbCouches && numCouche < NB_COUCHES_MAX; numCouche++) {
#ifndef PRODUCTION
		if((__DEBUG__debuggerCouches == 0 || __DEBUG__couches[numCouche] != NULL)) {
			rendreBackground(positionVert, positionHoriz, &couchesMapCourante[numCouche]);
			for(numSprite = 0; numSprite <= enTeteMapCourante.nbSprites && numSprite < NB_SPRITES_MAX + 1; numSprite++) {
				Sprite* sprite = &spritesMapCourante[numSprite];
				if(sprite->couche == numCouche) {
					rendreSprite(sprite);
				}
			}
		}
#else
		rendreBackground(positionVert, positionHoriz, &couchesMapCourante[numCouche]);
		for(numSprite = 0; numSprite <= enTeteMapCourante->nbSprites && numSprite < NB_SPRITES_MAX; numSprite++) {
			Sprite* sprite = spritesMapCourante[numSprite];
			if(sprite->couche == numCouche) {
				rendreSprite(sprite);
			}
		}
#endif
	}
}

void animer(void) {
	int numAnim;
	AttribTile* attr;
	
	for(numAnim = 0; numAnim < NB_ANIMATIONS; numAnim++) {
		attr = animations[numAnim];
		if(IDframe % attr->freqAnim == 0) {
			if(attr->frame == attr->frameMax) {
				attr->frame = 0;
			} else if(attr->frame < attr->frameMax) {
				attr->frame++;
			}
		}
	}
}

#ifndef PRODUCTION
void afficherInfosDebug(void) {
	if(!FLAG(ACTIVER_DEBUG)) {
		return;
	}
	
#define AFFTILE(nb, vert, horiz)	afficherTile(nb, vert * HAUTEUR_TILE, LARGEUR_FENETRE - horiz * LARGEUR_TILE);
	AFFTILE(' ', 0, 8)
	AFFTILE((fps < 100) ? ' ' : (fps / 100 + '0'), 0, 7)
	AFFTILE(fps % 100 / 10 + '0', 0, 6)
	AFFTILE(fps % 10 + '0', 0, 5)
	AFFTILE(' ', 0, 4)
	AFFTILE('F', 0, 3)
	AFFTILE('P', 0, 2)
	AFFTILE('S', 0, 1)
	
	AFFTILE('L', 1, 8)
	AFFTILE('A', 1, 7)
	AFFTILE('Y', 1, 6)
	AFFTILE('E', 1, 5)
	AFFTILE('R', 1, 4)
	AFFTILE(' ', 1, 3)
	AFFTILE(coucheJoueur / 10 + '0', 1, 2)
	AFFTILE(coucheJoueur % 10 + '0', 1, 1)
	
	AFFTILE('X', 2, 8)
	AFFTILE('P', 2, 7)
	AFFTILE('L', 2, 6)
	AFFTILE('A', 2, 5)
	AFFTILE('Y', 2, 4)
	AFFTILE(positionHorizJoueur / 100 + '0', 2, 3)
	AFFTILE(positionHorizJoueur % 100 / 10 + '0', 2, 2)
	AFFTILE(positionHorizJoueur % 10 + '0', 2, 1)
	
	AFFTILE('Y', 3, 8)
	AFFTILE('P', 3, 7)
	AFFTILE('L', 3, 6)
	AFFTILE('A', 3, 5)
	AFFTILE('Y', 3, 4)
	AFFTILE(positionVertJoueur / 100 + '0', 3, 3)
	AFFTILE(positionVertJoueur % 100 / 10 + '0', 3, 2)
	AFFTILE(positionVertJoueur % 10 + '0', 3, 1)
	
	AFFTILE('X', 4, 8)
	AFFTILE('C', 4, 7)
	AFFTILE('A', 4, 6)
	AFFTILE('M', 4, 5)
	AFFTILE(' ', 4, 4)
	AFFTILE(positionHorizCamera / 100 + '0', 4, 3)
	AFFTILE(positionHorizCamera % 100 / 10 + '0', 4, 2)
	AFFTILE(positionHorizCamera % 10 + '0', 4, 1)
	
	AFFTILE('Y', 5, 8)
	AFFTILE('C', 5, 7)
	AFFTILE('A', 5, 6)
	AFFTILE('M', 5, 5)
	AFFTILE(' ', 5, 4)
	AFFTILE(positionVertCamera / 100 + '0', 5, 3)
	AFFTILE(positionVertCamera % 100 / 10 + '0', 5, 2)
	AFFTILE(positionVertCamera % 10 + '0', 5, 1)
	
	AFFTILE('D', 6, 8)
	AFFTILE('I', 6, 7)
	AFFTILE('R', 6, 6)
	AFFTILE('P', 6, 5)
	AFFTILE('L', 6, 4)
	AFFTILE('A', 6, 3)
	AFFTILE('Y', 6, 2)
	AFFTILE(direction + '0', 6, 1)
	
	AFFTILE('M', 7, 8)
	AFFTILE('A', 7, 7)
	AFFTILE('P', 7, 6)
	AFFTILE('I', 7, 5)
	AFFTILE('D', 7, 4)
	AFFTILE(numMapCourante / 100 + '0', 7, 3)
	AFFTILE(numMapCourante % 100 / 10 + '0', 7, 2)
	AFFTILE(numMapCourante % 10 + '0', 7, 1)
	
	SDL_Rect infosTempsProcSrc  = {32, 16, 1, 1};
	SDL_Rect infosTempsProcDest = {0, 0, 1, 4};
	unsigned int i = 0;
	char chronos[NB_CHRONOS][21] = {"Chargement map", "Évènements", "Joueur / Cinématique", "Rendu graphique", "Menus"};
	for( ; i < NB_CHRONOS; i++) {
		infosTempsProcDest.w = tempsProcesseur[i] / 20;
		if((signed int)tempsProcesseur[i] > (signed int)precedentsTempsProc[i] * 3 / 2 + 200) {
			WARN("Lag spike détecté ! ")
			fprintf(fichierLog, "%s @ frame %u : %u cycles (comparés à %u).", chronos[i], IDframe, tempsProcesseur[i], precedentsTempsProc[i]);
			WARN("Ça peut être un faux positif, faites attention.")
		}
		precedentsTempsProc[i] = tempsProcesseur[i];
		rendreCopie(&infosTempsProcSrc, &infosTempsProcDest);
		
		infosTempsProcSrc.y++;
		infosTempsProcDest.y += 4;
	}
}
#endif

void attacherCameraSprite(unsigned int IDsprite) {
	Sprite* sprite = &spritesMapCourante[IDsprite];
	
	if(FLAG(CAMERA_FIXE) == 0) {
		int deplacementVert = sprite->positionVert - (positionVertCamera + (HAUTEUR_RENDU - HAUTEUR_TILE) / 2);
		int deplacementHoriz = sprite->positionHoriz - (positionHorizCamera + (LARGEUR_FENETRE - LARGEUR_TILE) / 2);
		
		if(deplacementVert == 0 && deplacementHoriz == 0) {
			return;
		}
		
		if(deplacementVert > VITESSE_CAMERA) {
			deplacementVert = VITESSE_CAMERA;
		} else if(deplacementVert < -VITESSE_CAMERA) {
			deplacementVert = -VITESSE_CAMERA;
		}
		if(deplacementHoriz > VITESSE_CAMERA) {
			deplacementHoriz = VITESSE_CAMERA;
		} else if(deplacementHoriz < -VITESSE_CAMERA) {
			deplacementHoriz = -VITESSE_CAMERA;
		}
		
		positionVertCamera += deplacementVert;
		if(positionVertCamera + HAUTEUR_RENDU > couchesMapCourante[(unsigned int)sprite->couche].hauteur * HAUTEUR_TILE) {
			positionVertCamera = couchesMapCourante[(unsigned int)sprite->couche].hauteur * HAUTEUR_TILE - HAUTEUR_RENDU;
		}
		if((signed int)positionVertCamera < 0) {
			positionVertCamera = 0;
		}
		
		positionHorizCamera += deplacementHoriz;
		if(positionHorizCamera + LARGEUR_FENETRE > couchesMapCourante[(unsigned int)sprite->couche].largeur * LARGEUR_TILE) {
			positionHorizCamera = couchesMapCourante[(unsigned int)sprite->couche].largeur * LARGEUR_TILE - LARGEUR_FENETRE;
		}
		if((signed int)positionHorizCamera < 0) {
			positionHorizCamera = 0;
		}
	}
}

void afficherBarreEtat(void) {
	if(FLAG(AFFICHER_BARRE_ETAT)) {
		wmemset(&barreEtat.texte[3], L' ', LONG_NOM_JOUEUR - 1);
		*wcpcpy(&barreEtat.texte[3], nomJoueur) = ' ';
		ecrireNombre(niveauJoueur, &barreEtat.texte[20]);
		barreEtat.texte[24] = L' ';
		ecrireNombre(PVjoueur, &barreEtat.texte[25]);
		barreEtat.texte[28] = L' ';
		ecrireNombre(PVmaxJoueur, &barreEtat.texte[29]);
		rendreMenu(&barreEtat);
		
		SDL_Rect rectSource = {0, JOUEUR_BAS * HAUTEUR_TILE, LARGEUR_TILE, HAUTEUR_TILE};
		SDL_Rect rectDest = {LARGEUR_TILE, (NB_TILES_HAUT - NB_TILES_BARRE_ETAT + 1) * HAUTEUR_TILE, LARGEUR_TILE * 2, HAUTEUR_TILE * 2};
		rendreCopie(&rectSource, &rectDest);
	}
}


void pleinEcran(void) {
	if(FLAG(PLEIN_ECRAN_ACTIF)) {
		ETEINDRE_FLAG(PLEIN_ECRAN_ACTIF);
		taillePixel = 1;
		SDL_SetWindowFullscreen(pFenetre, 0);
		boiteVert = 0;
		boiteHoriz = 0;
	} else {
		ALLUMER_FLAG(PLEIN_ECRAN_ACTIF);
		SDL_SetWindowFullscreen(pFenetre, SDL_WINDOW_FULLSCREEN_DESKTOP);
		
		if(SDL_GetWindowDisplayMode(pFenetre, &affichage) == 0) {
			taillePixel = min(affichage.h / HAUTEUR_FENETRE, affichage.w / LARGEUR_FENETRE);
			boiteVert = (affichage.h - HAUTEUR_FENETRE * taillePixel) / 2;
			boiteHoriz = (affichage.w - LARGEUR_FENETRE * taillePixel) / 2;
			
			DIRE("Taille de l'affichage : ")
			fprintf(fichierLog, "%d pix de haut, %d pix de large.", affichage.h, affichage.w);
			DIRE("Taille de la boîte : ")
			fprintf(fichierLog, "%d pix de haut, %d pix de large.", boiteVert, boiteHoriz);
		} else {
			ERROR("Impossible de passer en plein écran.");
			fprintf(fichierLog, "%s", SDL_GetError());
			
			// On repasse en fenêtré.
			pleinEcran();
		}
	}
}



// ANIMATIONS

void animation_SMB3(void) {
	unsigned int coordVert = 0;
	unsigned int coordHoriz = -1;
	SDL_Rect rectSource = TILE(0, HAUTEUR_TILE);
	
	void placerTile(void) {
		afficherRect(&rectSource, coordVert * HAUTEUR_TILE, coordHoriz * LARGEUR_TILE);
		rendrePresent();
		SDL_Delay(1);
	}
	int taille_V = NB_TILES_HAUT;
	int taille_H = NB_TILES_LARG;
	int compteur;
	while(taille_V > 0) {
		// Exécuter une spirale.
		for(compteur = 0; compteur < taille_H; compteur++) {
			coordHoriz++;
			placerTile();
		}
		taille_V--;
		for(compteur = 0; compteur < taille_V; compteur++) {
			coordVert++;
			placerTile();
		}
		taille_H--;
		for(compteur = 0; compteur < taille_H; compteur++) {
			coordHoriz--;
			placerTile();
		}
		taille_V--;
		for(compteur = 0; compteur < taille_V; compteur++) {
			coordVert--;
			placerTile();
		}
		taille_H--;
	}
}

void gaucheDroite(void) {
#define NB_HAUT		(NB_TILES_HAUT + 1) / 2
	int decalage[NB_HAUT];
	SDL_Rect rectSource = TILE(0, HAUTEUR_TILE);
	SDL_Rect rectDest = {0, 0, LARGEUR_TILE, HAUTEUR_TILE * 2};
	unsigned char termines = NB_HAUT;
	
	while(termines != 0) {
		termines--;
		decalage[termines] = rand() % 24 - 23;
	}
	// termines = 0 !
	while(termines != NB_HAUT) {
		unsigned char curseur = 0;
		while(curseur < NB_HAUT) {
			if(decalage[curseur] >= 0) {
				rectDest.y = curseur * HAUTEUR_TILE * 2;
				rectDest.x = decalage[curseur] * LARGEUR_TILE;
				rendreCopie(&rectSource, &rectDest);
			}
			if(decalage[curseur] == NB_TILES_LARG) {
				termines++;
			}
			decalage[curseur]++;
			curseur++;
		}
		rendrePresent();
		SDL_Delay(10);
	}
}

void coin(void) {
	int coordVert;
	unsigned int coordHoriz;
	unsigned int etape = 0;
	SDL_Rect rectSource = TILE(0, HAUTEUR_TILE);
	SDL_Rect rectDest = {0, 0, LARGEUR_TILE * 2, HAUTEUR_TILE * 2};
	while(etape * 2 < NB_TILES_HAUT + NB_TILES_LARG) {
		coordHoriz = 0;
		coordVert = etape;
		while(coordVert >= 0) {
			rectDest.x = coordHoriz * LARGEUR_TILE * 2;
			rectDest.y = coordVert * HAUTEUR_TILE * 2;
			rendreCopie(&rectSource, &rectDest);
			coordHoriz++;
			coordVert--;
			SDL_Delay(3);
		}
		etape++;
		rendrePresent();
	}
}

void rentrer(void) {
	unsigned int etape = 0;
	SDL_Rect rectSource = TILE(0, HAUTEUR_TILE);
	SDL_Rect rectDest = {0, 0, LARGEUR_TILE / 4, HAUTEUR_FENETRE};
	while(etape <= NB_TILES_LARG * 2) {
		rectDest.x = etape * LARGEUR_TILE / 4;
		rendreCopie(&rectSource, &rectDest);
		rectDest.x = (NB_TILES_LARG * 4 - etape) * LARGEUR_TILE / 4;
		rendreCopie(&rectSource, &rectDest);
		etape++;
		rendrePresent();
		SDL_Delay(4);
	}
	SDL_Delay(100);
}

void sortir(void) {
	int etape = NB_TILES_LARG * 2;
	SDL_Rect rectSource = RECT_TILE;
	SDL_Rect rectDest = {0, 0, LARGEUR_TILE / 4, HAUTEUR_FENETRE};
	while(etape >= 0) {
		rectDest.x = etape * LARGEUR_TILE / 4;
		rendreCopie(&rectSource, &rectDest);
		rectDest.x = (NB_TILES_LARG * 4 - etape) * LARGEUR_TILE / 4;
		rendreCopie(&rectSource, &rectDest);
		etape--;
		rendrePresent();
		SDL_Delay(4);
	}
	SDL_Delay(100);
}

void snake(void) {
	unsigned int etape = 0;
	unsigned int etapeDest = 0;
	unsigned int nbEtapes = 0;
	SDL_Rect rectSource = TILE(0, NOIR * HAUTEUR_TILE);
	
	while(etape < NB_TILES_HAUT * NB_TILES_LARG) {
		nbEtapes++;
		etapeDest += nbEtapes;
		while(etape < etapeDest && etape < NB_TILES_HAUT * NB_TILES_LARG) {
			unsigned int _etape = etape % (NB_TILES_LARG * 2);
			afficherRect(&rectSource, (etape / NB_TILES_LARG) * HAUTEUR_TILE, ((_etape < NB_TILES_LARG) ? _etape : NB_TILES_LARG * 2 - _etape - 1) * LARGEUR_TILE);
			rendrePresent();
			etape++;
		}
		SDL_Delay(20);
	}
	
	SDL_Delay(100);
}


void transitionAttaqueWobble(void) {
	SDL_Rect rectSource = TILE(0, NOIR * HAUTEUR_TILE);
	SDL_Rect rectDest = {HAUTEUR_FENETRE / 2, HAUTEUR_FENETRE / 2, LARGEUR_FENETRE - HAUTEUR_FENETRE, 2};
	unsigned int i = 2;
	
	for( ; i != (unsigned int)-1; i--) {
		while((unsigned int)rectDest.x != i * 70) {
			rectDest.x -= 1;
			rectDest.y -= 1;
			rectDest.w += 2;
			rectDest.h += 2;
			rendreCopie(&rectSource, &rectDest);
			rendrePresent();
			SDL_Delay(1);
		}
		rectDest.x = HAUTEUR_FENETRE / 2;
		rectDest.y = HAUTEUR_FENETRE / 2;
		rectDest.w = LARGEUR_FENETRE - HAUTEUR_FENETRE;
		rectDest.h = 2;
		ciblerTile((i % 2) ? NOIR : ' ', &rectSource);
		SDL_Delay(i * 100 + 1);
	}
	SDL_Delay(300);
}

