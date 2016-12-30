
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
// ##### Centrale à defines ####
// #############################


#pragma once


#include <SDL2/SDL.h>
#include <stdio.h>
#include <wchar.h>
#include <stdbool.h>

#include "typedefs.h"


EtatFrame							rendreFrame; // Donne ou non le feu vert à la prochaine frame.
EtatJeu								jeuEnCours; // Indique si le jeu est en train de tourner ou s'il doit être terminé.
CodeRetour							codeRetour; // Indique le code retour de la fonction frame().



// Variables liées à la map courante.

unsigned int						numMapCourante; // Numéro de la map courante.
Map									enTeteMapCourante; // Copie temporaire de l'en-tête de la map courante.
Couche								couchesMapCourante[NB_COUCHES_MAX];
extern Sprite						spritesMapCourante[NB_SPRITES_MAX];

// ATTENTION : dès que cette variable a une valeur différente de -1, déclenche le warp.
// Si les deux variables doivent être mises à jour séparément, modifier D'ABORD mapDestination !
unsigned int						warpDestination;
unsigned int						mapDestination;

void								(*scriptFrame)(void); // Script exécuté à chaque frame.


ElemCinematique*					actionEnCours;
Interaction*						tableInteractions[NB_INTERACTIONS];
Interaction*						interactionsAsauvegarder[NB_INTERACTIONS_SAUV];

Map*								enTetes[NB_MAPS]; // En-têtes de chaque map du jeu.


extern Sauvegarde					sauvegardes[NB_SAUVEGARDES + 1];

unsigned int						ordreObjets[NB_OBJETS + 1]; // Ordre des objets dans l'inventaire du joueur.
unsigned int						quantitesObjets[NB_OBJETS]; // Quantité possédée par le joueur de chaque objet.
extern AttribObjet*					attributsObjets[NB_OBJETS];

SDL_Window*   						pFenetre; // Fenêtre de jeu.
SDL_Renderer* 						pRendu; // Rendu de la fenêtre du jeu.
SDL_Texture*						framebuffer; // Texture servant de frame buffer.
extern Image    					imgTiles; // Image des tiles.
SDL_DisplayMode						affichage; // Contient des informations sur l'affichage plein écran.
unsigned char						taillePixel; // Taille d'un pixel logique.
unsigned int						boiteVert; // Nombre de pixels "vides" (taille verticale)
unsigned int						boiteHoriz; // Nombre de pixels "vides" (taille horizontale).

AttribTile*							attributsTiles[NB_TILES]; // Attributs des tiles.
Transparence*						transparences[NB_TILES]; // Masques de transparence des tiles.
AttribTile*							animations[NB_ANIMATIONS]; // Attributs à animer.

int									dernierChoixMenu; // Contient le dernier choix fait dans une CMD_OPTIONS.
unsigned int						vitesseTexte; // Modulo auquel des caractères sont affichés.
wchar_t								entreeUtilisateur[15];

Menu*								menuArendre; // Premier menu rendu par le jeu. Il est donc rendu tout en bas.
unsigned int						entreeEntier;
unsigned char						positionCurseurEntree;



// Variables globales

unsigned int						IDframe; // Compteur de frames, utilisé pour timer les évènements temporels.

#define SDL_SCANCODE_BOUTON_SOURIS	3
SDL_Scancode						codesTouches[NB_TOUCHES]; // Table de correspondance entre les touches et leur position logique dans le jeu.
EtatTouche							etatTouches[NB_TOUCHES]; // Indique si les touches sont enfoncées ou non.
void								(*scripts[NB_TOUCHES])(void);
EtatTouche							touchesPressees[NB_TOUCHES]; // Indique les touches qui ont été pressées à cette frame.
bool								mouvementEnCours;
unsigned int						positionSourisVert;
unsigned int						positionSourisHoriz;

unsigned char						flags[(NB_FLAGS + 7) / 8];
#define FLAG(numero_flag)			((flags[numero_flag / 8] >> (numero_flag % 8)) & 1)
#define ALLUMER_FLAG(numero_flag)	flags[numero_flag / 8] |= 1 << (numero_flag % 8)
#define ETEINDRE_FLAG(numero_flag)	flags[numero_flag / 8] &= ~(1 << (numero_flag % 8)) 

extern unsigned char				version[3];


// Variables liées au joueur

PosPixel							positionVertJoueur; // Position verticale du joueur.
PosPixel							positionHorizJoueur; // Position horizontale du joueur.
unsigned char						coucheJoueur; // Numéro de la couche où se trouve le joueur.
PosPixel							positionVertCamera; // Position verticale de la caméra.
PosPixel							positionHorizCamera; // Position horizontale de la caméra.
unsigned int						numSpriteCamera; // Numéro du sprite auquel la caméra est attachée.
Direction							direction; // Direction du joueur.
unsigned int						PVjoueur;
unsigned int						PVmaxJoueur;
unsigned char						niveauJoueur;
unsigned char						sexeJoueur;
wchar_t								nomJoueur[LONG_NOM_JOUEUR];


#ifndef PRODUCTION
unsigned char						__DEBUG__debuggerCouches;
Couche*								__DEBUG__couches[NB_COUCHES_MAX];
unsigned char						__DEBUG__debuggerSprites;
unsigned char						__DEBUG__debuggerWarps;
unsigned char						__DEBUG__debuggerChangements;

enum {
	CHARGEMENT_MAP,
	EVENEMENTS,
	JOUEUR_CINEMATIQUE,
	TEMPS_RENDU,
	MENUS,
	
	NB_CHRONOS
};
unsigned int						tempsProcesseur[NB_CHRONOS];
#endif
unsigned int						precedentsTempsProc[NB_CHRONOS];

