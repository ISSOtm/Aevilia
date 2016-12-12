
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
// ###### Header principal #####
// #############################


#pragma once


#include <SDL2/SDL.h>

#include "defines.h"


SDL_TimerID							IDtimerFrame; // ID du timer d'activation des frames.
unsigned int						IDframePrec; // Utilisé pour compter les fps.
SDL_TimerID							IDtimerFPS; // ID du timer de comptage des FPS.
unsigned int						fps; // FPS comptés. Idéalement, 62.

extern Sprite						spriteJoueur;

SDL_Event							evenement; // Évènement traité par le programme. Envoyé à SDL_PollEvent().


// Initialise le jeu (librairies, rendu, etc)
extern void initialiser(int argc, char* argv[]) __attribute__ ((__constructor__));
// Code principal.
extern int main();
// Wrapper pour exit() ; cette fonction effectue en plus l'inverse de initialiser()
extern void terminer(CodeRetour statut) __attribute__ ((__noreturn__));
// Effectue l'animation de fin, et termine le jeu avec le staut SUCCES.
extern void quitterJeu(void) __attribute__ ((__noreturn__, cold));
// Termine le jeu avec la valeur de CodeRetour.
extern void terminerJeu(void) __attribute__ ((__noreturn__, cold));
// Charge la map de crash.
extern void crash(CodeRetour code) __attribute__ ((cold));
// Handler du signal SIGSEGV.
extern void segfault(int arg) __attribute__ ((__noreturn__));

// Exécute une frame de jeu, et arme la temporisation de la suivante.
extern Uint32 frame(Uint32 delai, void* param_UNUSED);

extern Uint32 compterFPS(Uint32 delai, void* param_UNUSED);

// Traite les évènements de la SDL.
extern void traiterEvenements(void) __attribute__ ((hot));
// Enregistre l'appui sur une touche.
extern void presserTouche(SDL_Scancode codeTouche);
// Enregistre le relâchement d'une touche.
extern void relacherTouche(SDL_Scancode codeTouche);

// Donne la possibilité au personnage d'avancer... ou non.
extern unsigned char collision(unsigned int vert, unsigned int horiz, unsigned char numCouche, Direction direction) __attribute__ ((pure, warn_unused_result));
// Fait aller le personnage vers le haut.
extern void haut(void);
// Fait aller le personnage vers le bas.
extern void bas(void);
// Fait aller le personnage vers la gauche.
extern void gauche(void);
// Fait aller le personnage vers la droite.
extern void droite(void);
// Fait avancer le personnage en fonction de sa direction.
extern void avancer(void);
// Exécute l'interaction dont le script est donné.
extern void interaction(unsigned int IDinteraction);
// Fait interagir le personnage avec son environnement.
extern void interagir(void);

#define WARPER(IDmap, IDwarp)	mapDestination = IDmap; \
								warpDestination = IDwarp;
// Charge la map dont l'index est donné.
extern void chargerMap(unsigned int IDmap);
// Charge la map dont l'index est donné, et place le joueur au warp donné.
extern void warperVersMap(unsigned int IDmap, unsigned int IDwarp);
// Ajuste la position du joueur à l'écran en fonction de la position du joueur et la position de la caméra.
extern void ajusterJoueur(void) __attribute__ ((hot));

