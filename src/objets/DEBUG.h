
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
// ##### Objet #0 - DEBUG ######
// #############################


#pragma once

// Commandes auxiliaires.
void _warper(Commande* commande);
void _determinerNbWarps(Commande* commande);

void gestionObjetsValiderQte(Commande* commande);
void retracerChoixQte(Commande* commande);
unsigned int validerEnfonce(void);
void retracerChoix(Commande* commande);
void decrementerIDchoix10(void);
void incrementerIDchoix10(void);
void decrementerIDchoix(void);
void incrementerIDchoix(void);
void pousserScriptsChoix(Commande* commande);

// Affiche le menu de debug demandé.
unsigned int menuDebug(unsigned int indexMenu);

extern AttribObjet obj__DEBUG;

