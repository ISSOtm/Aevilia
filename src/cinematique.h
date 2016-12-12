
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
// ### Header -- Cinématique ###
// #############################


#pragma once


#include "defines.h"


// Ajoute une cinématique à la file.
extern void ajouterCinematique(ElemCinematique* action);
// Retire la première cinématique de la file.
extern void terminerCinematique(void);

// Déplace le joueur (pas son sprite !)
extern unsigned int bouger(ElemCinematique* action);
// Attend que la touche fournie soit pressée.
extern unsigned int attendreTouche(ElemCinematique* action);
// Attend que VALIDER ou ANNULER soit pressé.
extern unsigned int valider(ElemCinematique* action);
// Ajouter un menu.
extern unsigned int actionMenu(ElemCinematique* action);
// Attendre que tous les menus soient fermés.
extern unsigned int attendreMenu(void);
// Déplace le sprite pointé dans la direction fournie.
extern unsigned int deplacerSpr(ElemCinematique* action);
// Attend le nombre de frames spécifié.
extern unsigned int attendreFrames(ElemCinematique* action);
// Modifie la tile du sprite pointé.
extern unsigned int tileSprite(ElemCinematique* action);
// Écrit un octet en mémoire.
extern unsigned int ecrireOctet(ElemCinematique* action);
// Sert de boucle for.
extern unsigned int djnz(ElemCinematique* action);
// Modifie un flag.
extern unsigned int flag(ElemCinematique* action);
// Exécute une fonction.
extern unsigned int execFonction(ElemCinematique* action);
// Modifie une tile de la couche pointée.
extern unsigned int modifTile(ElemCinematique* action);

// Effectue une frame de la cinématique en cours.
extern void cinematique(void);

