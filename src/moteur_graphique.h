
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
// ###### Header du moteur #####
// #############################


#pragma once


#include <SDL2/SDL.h>

#include "maps.h"


// Charge les librairies de rendu et les images principales et crée la fenêtre de jeu.
extern void initialiserGraphismes(void);
// Effectue l'inverse de la précédente.
extern void nettoyerGraphismes(void);

// Charge une image dont le nom (extension comprise !) est donné. Le fichier doit être au format BMP.
// Termine Aevilia si l'image échoue à charger.
extern CodeRetour chargerImage(const char nom[], Image* img);
// Effectue l'inverse de la fonction précédente. Si l'image a déjà été déchargée, ne fait rien.
extern void dechargerImage(Image* img);

#define TILE(x, y)		{x, y, LARGEUR_TILE, HAUTEUR_TILE}
#define RECT_TILE		TILE(0, 0)
// Renvoie le numéro de la tuile aux positions indiquées dans la couche fournie.
extern wchar_t obtenirNumeroTile(unsigned int positionVert, unsigned int positionHoriz, const Couche* couche) __attribute__ ((pure));
// Modifie la tuile aux positions indiquées dans la couche fournie.
extern void modifierNumeroTile(unsigned int positionVert, unsigned int positionHoriz, Couche* couche, wchar_t tile);
// Modifie rectangle.x et rectangle.y pour correspondre à la frame actuelle de la tile donnée.
extern void ciblerTile(wchar_t numero, SDL_Rect* rectangle);
// Effectue un SDL_RenderCopy() avec les deux rectangles fournis, en tenant compte du fullscreen.
extern void rendreCopie(const SDL_Rect* rectSource, const SDL_Rect* rectDest);
// Effectue un RenderPresent()... et dessine la boîte !!
extern void rendrePresent(void) __attribute__ ((hot));
// Affiche le rectangle donné aux coordonnées indiquées.
extern void afficherRect(const SDL_Rect* rectSource, unsigned int positionVert, unsigned int positionHoriz) __attribute__ ((hot));
// Affiche la tile donnée à la position donnée.
extern void afficherTile(wchar_t numero, unsigned int positionVert, unsigned int positionHoriz) __attribute__ ((hot));
// Rend la tilemap de numéro indiqué.
extern void rendreBackground(unsigned int positionVert, unsigned int positionHoriz, const Couche* couche);
// Rend le sprite fourni.
extern void rendreSprite(const Sprite* sprite);
// Avance toutes les tiles d'une frame.
extern void animer(void);
// Rend toutes les couches de la map fournie (background et sprites).
extern void rendreMap(unsigned int positionVert, unsigned int positionHoriz);
// Affiche le nombre de FPS à l'écran.
extern void afficherInfosDebug(void);
// Déplace la caméra pour qu'elle suive le sprite spécifié.
extern void attacherCameraSprite(unsigned int IDsprite);
// Affiche la barre d'état en bas de l'écran.
extern void afficherBarreEtat(void);

// Met la fenêtre en plein écran.
extern void pleinEcran(void);

// Animations.
extern void animation_SMB3(void);
extern void gaucheDroite(void);
extern void coin(void);
extern void rentrer(void);
extern void sortir(void);
extern void snake(void);

extern void transitionAttaqueWobble(void);

