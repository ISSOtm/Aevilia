
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
// #### Header -- Sauvegarde ###
// #############################


#pragma once


#include <stdio.h>

#include "aevilia.h"

// Écrit les sauvegardes dans le fichier.
extern void sauvegarder(void);
// Charge les sauvegardes depuis le ficher.
extern CodeRetour charger(void);
// Rassemble les éléments du jeu dans la sauvegarde concernée.
extern void mettreAjourSauvegarde(unsigned int numSauvegarde);
// Charge les éléments de la sauvegarde concernée dans le jeu.
extern CodeRetour decompresserSauvegarde(unsigned int numSauvegarde);

// Calcule la checksum d'une sauvegarde.
extern unsigned char calculerChecksum(unsigned int numSauvegarde);

