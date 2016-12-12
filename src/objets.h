
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
// ###### Header -- Objets #####
// #############################


#pragma once


#include "defines.h"

#include "objets/DEBUG.h"


// Écrit la description dans le champ de texte prévu à cet effet.
extern void afficherDescription(void);
// Retire le script de fermeture de l'inventaire.
extern void retirerScriptInventaire(Commande* commande);
// Détermine si on doit retourner dans l'inventaire ou non.
extern unsigned int rebouclerOuNon(void);
// Génère la liste d'objets dans l'inventaire.
extern void arrangerInventaire(Commande* commande);
// Ouvre l'inventaire.
extern void ouvrirInventaire(void);
// Renvoie le nom de l'objet demandé.
extern wchar_t* obtenirNomObjet(unsigned int indexObjet) __attribute__ ((returns_nonnull, pure));
// Utilise l'objet d'index passé en paramètre. Renvoie la quantité d'objets après utilisation.
extern unsigned int utiliserObjet(unsigned int indexObjet) __attribute__ ((warn_unused_result));
// Utilise l'objet d'index passé en paramètre, et modifie l'inventaire du joueur en conséquence.
extern void utiliserObjetJoueur(Commande* commande);

// Donne au joueur des exemplaires d'un objet.
extern void obtenirObjet(unsigned int IDobjet, unsigned int qteObjet);
// Affiche la textbox indiquant l'obtention des objets.
extern void afficherObjetObtenu(unsigned int IDobjet, unsigned int qteObjet);

// Vérifie si le joueur a le droit de jeter cet objet, et agit en conséquence.
extern unsigned int verifierObjetJetable(void) __attribute__ ((pure));
// Jette des objets.
extern void jeterObjetJoueur(Commande* commande);

