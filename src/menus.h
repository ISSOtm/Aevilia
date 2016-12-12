
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
// ####### Header - Menus ######
// #############################


#pragma once


#include "defines.h"


extern wchar_t chainesOuiNon[2][LONG_NOM_OPTIONS];
extern Commande attendreEtTerminer;


// Petite discussion sur l'intérêt de ajouterMenu() et ajouterMenuRapide().
// Au début, il n'y avait que ajouterMenu(), qui était sensiblement identique à ce que vous obtiendriez si vous inlinez ajouterMenuRapide() dans cette fonction ; néanmoins, il m'est apparu que le code suivant :
/*	Menu* menu1 = MENU(...);
 *	Menu* menu2 = MENU(...);
 * 	
 *	ajouterMenu(menu1);
 *	ajouterMenu(menu2);
 */
// calculait inutilement. Pourquoi ? Simplement, supposons que ce code puisse être appelé quelque soit l'état de la chaîne de menus.
// À l'exécution du premier ajouterMenu(), le bout de la chaîne est inconnu, donc il est nécessaire de calculer le bout de la chaîne.
// Mais ceci n'est pas vrai pour le second ajouterMenu() ! Le bout de la chaîne - et je suppose qu'aucun autre thread ne peut modifier la chaîne - est menu1 ! La preuve, on vient de l'ajouter.
// Pour le seocnd appel, le calcul du bout de la chaîne est donc redondant ! On pourrait économiser du calcul simplement en donnant à ajouterMenu() la localisation du bout de la chaîne !
// De là est née l'idée d'ajouterMenuRapide().
// On peut objecter qu'il suffit de simplement modifier menu1->prochainMenu, et le tour est joué !
// Minute, papillon ! C'est pas aussi simple que ça :P
// Simplement, ajouter un menu est plus compliqué que ça. Il faut aussi retirer le contrôle au joueur si aucun menu n'était présent, faire en sorte qu'un seul menu soit ajouté à la fois, lancer l'animation, et surtout, logger son ajout !
// Le logging n'importe pas, mais pour le debug, je peux vous garantir que c'est une plaie que d'avoir des ajouts de menus qui se baladent dans le code. Centraliser dans une fonction rend le debugging viable.

// Bref, voici un tl;dr en forme de FAQ. Je déteste ça, mais tant pis !
// Q : Quand utiliser ajouterMenu() ?
// R : Quand vous ne pouvez pas être certain du dernier maillon de la chaîne de menus. Par défaut, utilisez celle-là.

// Q : Quand utiliser ajouterMenuRapide() ?
// R : Quand vous êtes certain de qui est le dernier de la chaîne de menus. En supposant que l'appelant dit vrai, elle ne calcule pas le pointeur vers le dernier menu du la chaîne.
//     Elle procède quand même à une simple vérification : "menuDajout->prochainMenu" (sous-entendu "!= NULL"). Autrement dit, si la chaîne ne continue pas après menuDajout.
//     Cette vérification est simplement un garde-fou, et ne doit pas être utilisée à outrance pour la raison décrite trois paragraphes plus loin.
//     Le cas attendu est que la vérification échoue (donc menuDajout->prochainMenu == NULL). Cette vérification est considérée comme "IMPROBABLE()", c'est-à-dire plus rapide si la condition n'est pas vérifiée. Recherchez la documentation sur __builtin_expect pour savoir ce que c'est.
//     Si cette vérification réussit, ajouterMenuRapide() se comporte comme ajouterMenu() ; en bref, elle remplace la valeur fournie par l'utilisateur pour menuDajout par celle retournée par dernierMenu(). Ce faisant, elle émet un avertissement sur le logging.
//     À noter que dans le cas où dernierMenu() est recalculée, ajouterMenuRapide() devient *plus lente* que ajouterMenu(), puisqu'on appelle à nouveau ajouterMenu().

// Q : J'ai rien suivi à ce que tu viens de dire.
// R : Tant pis. Retiens au moins ça :
//         1. Utiliser ajouterMenuRapide() quand tu as la certitude du menu précédent sur la pile. Le code donné en introduction est un bon exemple ; c'est avec ce genre de code en tête que j'ai créé ajouterMenuRapide().
//         2. Si tu n'as pas cette certitude, abstiens-toi et utilise ajouterMenu().
//         3. Si tu es quasi-certain de ton coup, tu peux abuser du garde-fou. Exemple :
/*  Menu inventaire = MENU(...);
 *  
 *  void ajouterInventaire() {
 *      ajouterMenuRapide(&inventaire, menuArendre);
 *      
 *      (...) // Setup de plein de trucs.
 *  }
 */
//            Admettons qu'habituellement, ajouterInventaire() soit appelée avec menuArendre == NULL mais que UNE FOIS, lors d'un tutorial, le menu soit ajouté avec une boîte de texte déjà à l'écran.
//            Dans ce cas, on peut se le permettre. Mais "parce que c'est une seule fois". Mais il ne faut pas que ce soit "une seule fois par frame".


// Renvoie un pointeur vers le dernier menu de la chaîne. Si la chaîne est vide, retourne NULL.
extern Menu* dernierMenu(void) __attribute__ ((pure));
// Ajoute le menu passé en pointeur à la liste des menus actifs.
extern void ajouterMenu(Menu* menu) __nonnull ((1));
// Ajoute menuAajouter à la chaîne des menus actifs. Part de la supposition que le dernier menu de la chaîne est menuDajout, et modifie celui-ci.
extern void ajouterMenuRapide(Menu* menuAajouter, Menu** menuDajout) __nonnull ((1, 2));
// Retire le dernier menu de la liste. Ne fait rien si la liste est vide.
extern void retirerDernierMenu(void);
// Retire le menu spécifié de la liste. Ne fait rien s'il n'y est pas.
extern void retirerMenu(Menu* menu) __nonnull ((1));
// Rend à l'écran les menus de la chaîne, et exécute la dernière commande du dernier d'entre eux.
extern void activerMenus(void);
// Renvoie le nombre de caractères à rendre.
// Non programmée. extern unsigned int calculerLongChaineMenu(Menu* menu) __nonnull ((1));
// Rend à l'écran le menu pointé en paramètre.
extern void rendreMenu(Menu* menu) __nonnull ((1));


// Exécute la commande AFFICHER.
extern unsigned int afficherChaine(Commande* commande) __nonnull ((1));
// Exécute la commande PAUSE.
extern unsigned int pause(Commande* commande) __nonnull ((1));
// Exécute la commande FONCTION.
extern unsigned int fonction(Commande* commande) __nonnull ((1));
// Exécute la commande SAUTER.
extern unsigned int sauter(Commande* commande) __nonnull ((1));
// Exécute la commande APPELER.
extern unsigned int appeler(Commande* commande) __nonnull ((1));
// Exécute la commande AJOUTER_MENU.
extern unsigned int nouveauMenu(Commande* commande) __nonnull ((1));
// Exécute la commande ATTENDRE.
extern unsigned int attendre(void);
// Exécute la commande EFFACER.
extern unsigned int effacer(void);
// Efface le texte d'un menu.
extern unsigned int effacerMenu(Menu* menu) __nonnull ((1));
// Exécute la commande OPTIONS.
#define PHASE_OPTION_SETUP		0
#define PHASE_OPTION_DEPL		1
#define PHASE_OPTION_FIN		2
#define PHASE_OPTION_APPELS		3
// Doit ABSOLUMENT être la dernière de la liste !
#define PHASE_OPTION_TERMINER	4
extern unsigned int options(Commande* commande) __nonnull ((1));
// Exécute la commande OBJET.
#define PHASE_OBJETS_OBTENIR	0
#define PHASE_OBJETS_OBTENU		1
extern unsigned int objets(Commande* commande) __nonnull ((1));
// Exécute la commande WARPER.
extern unsigned int warp(Commande* commande) __nonnull ((1));
// Exécute la commande OCTET.
extern unsigned int octet(Commande* commande) __nonnull ((1));
// Exécute la commande EDITION_FLAG.
extern unsigned int editionFlag(Commande* commande) __nonnull ((1));
// Exécute la commande ENTRER_TEXTE
extern wchar_t					chaineEntree[217];
extern unsigned int entrerTexte(Commande* commande) __nonnull ((1));
// Exécute la commande DEMANDER_ENTIER
#define PHASE_ENTIER_SETUP		0
#define PHASE_ENTIER_DEMANDER	1
#define PHASE_ENTIER_TERMINER	2
extern unsigned int demanderEntier(Commande* commande) __nonnull ((1));

