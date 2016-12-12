
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
// ### Header -- Utilitaires ###
// #############################


#pragma once


#include <stdio.h>

#include "aevilia.h"


#define PREFIX(type)				if(logger(type) == ERREUR_ECRITURE_LOG) { \
										terminer(ERREUR_ECRITURE_LOG); \
									}
#define LOGGER(message) 			if(logger(LOG) == ERREUR_ECRITURE_LOG) { \
										terminer(ERREUR_ECRITURE_LOG); \
									} \
									fprintf(fichierLog, message);
#define DIRE(message)   			if(logger(MESSAGE) == ERREUR_ECRITURE_LOG) { \
										terminer(ERREUR_ECRITURE_LOG); \
									} \
									fprintf(fichierLog, message);
#define WARN(message)   			if(logger(ATTENTION) == ERREUR_ECRITURE_LOG) { \
										terminer(ERREUR_ECRITURE_LOG); \
									} \
									fprintf(fichierLog, message);
#define ERROR(message)  			if(logger(ERREUR) == ERREUR_ECRITURE_LOG) { \
										terminer(ERREUR_ECRITURE_LOG); \
									} \
									fprintf(fichierLog, message);
#define FATALERROR(message,statut)  if(logger(ERREUR) == ERREUR_ECRITURE_LOG) { \
										terminer(ERREUR_ECRITURE_LOG); \
									} \
									fprintf(fichierLog, message); \
									logger("FATAL"); \
									fprintf(fichierLog, "Arrêt d'Aevilia avec le statut %d.", statut); \
									terminer(statut);
#define LOG			"Log"
#define MESSAGE		"Message"
#define ATTENTION	"Attention"
#define ERREUR		"ERREUR"
#define FATAL		"FATAL"

FILE*         						fichierLog; // Pointeur pour logging.


// Démarre le logging et met le pointeur du fichier dans fichierLog.
extern CodeRetour demarrerLogging(void);
// Fait l'inverse.
extern CodeRetour arreterLogging(void);
// Prépare l'affichage d'une ligne du log. Effectuer un fprintf après.
extern CodeRetour logger(const char type[]);

// Donne l'index du haut du stack.
// Non programmée. extern unsigned int obtenirHautStack(void (*fonctions[])(void));
// Ajoute un script sur la touche indiquée, et sauvegarde le précédent sur la pile.
extern void pousserScript(Touche touche, void (*fonction)(void));
// Retire le premier script de la pile vers le script correspondant.
extern void popperScript(Touche touche);

// Écrit le nombre à l'endroit pointé.
extern void ecrireNombre(unsigned int nombre, wchar_t* dest);

// Retourne l'état d'une touche. Renvoie TOUCHE_RELACHEE si un script est présent.
extern EtatTouche etatTouche(Touche touche) __attribute__ ((pure));

// Obvious.
extern unsigned int min(unsigned int a, unsigned int b);

// Charge un fichier dans le répertoire spécifié.
extern FILE* chargerFichier(const char* dossier, const char* nomFichier, const char* mode);

