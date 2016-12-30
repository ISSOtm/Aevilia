
// #############################
// #                           #
// #    AEVILIA SOURCE CODE    #
// #       Version 0.3.0       #
// #                           #
// #   Version expérimentale,  #
// #  seulement à des fins de  #
// #     test. Probablement    #
// #  instable, utilisez-la à  #
// #   vos risques et périls.  #
// #                           #
// #############################
// ##                         ##
// ### Objet #2 - PadOptions ###
// #############################


#pragma once

#include <SDL2/SDL.h>


extern AttribObjet obj__PadOptions;

unsigned int detecterManettes(Commande* commande);

void ecrireVitesseTexte(Commande* commande);

unsigned int ouvrirMenuOptions(unsigned int IDmenu);


