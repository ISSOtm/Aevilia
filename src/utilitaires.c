
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
// ### Fonctions utilitaires ###
// #############################


#include <time.h>
#include <stdio.h>

#include "utilitaires.h"
#include "defines.h"


CodeRetour demarrerLogging(void) {
	char nomLog[] = "aevilia.log";
	
	remove(nomLog);
	// C'est un log, on va donc faire des append, rien d'autre. De plus on doit créer le fichier.
	fichierLog = fopen(nomLog, "a");
	return (fichierLog) ? SUCCES : ERREUR_OUVRIR_LOG;
}

CodeRetour arreterLogging(void) {
	// fclose renvoie 0 si tout s'est bien passé. Je ne vois pas sous quelles circonstances ça peut rater, donc je ne peux pas faire de handler...
	return (fclose(fichierLog)) ? ERREUR_FERMER_LOG : SUCCES;
}

CodeRetour logger(const char type[]) {
	// Récupération de l'heure
	time_t secondes = time(NULL);
	struct tm moment = *localtime(&secondes);
	
	// Logging
	return (fprintf(fichierLog, "\n[%.2d:%.2d:%.2d] %s: ", moment.tm_hour, moment.tm_min, moment.tm_sec, type) == EOF) ? ERREUR_ECRITURE_LOG : SUCCES;
}



// Taille physique de la pile.
#define TAILLE_PILE_DE_SCRIPTS		16
// Stack qui pousse vers le haut.
void (*pileDeScripts[NB_TOUCHES][TAILLE_PILE_DE_SCRIPTS])(void);
// Taille logique de la pile de scripts. Peut excéder 16, mais ne 
unsigned int taillePileDeScripts[NB_TOUCHES];

void pousserScript(Touche touche, void (*fonction)(void)) {
	// Si on est dans les limites de la pile...
	if(taillePileDeScripts[touche] < TAILLE_PILE_DE_SCRIPTS) {
		// On pousse.
		pileDeScripts[touche][taillePileDeScripts[touche]] = scripts[touche];
		scripts[touche] = fonction;
	}
	
	// On augmente la taille logique.
	taillePileDeScripts[touche]++;
}

void popperScript(Touche touche) {
	// Si la pile est vide, ça compte pour du NULL.
	if(taillePileDeScripts[touche] == 0) {
		scripts[touche] = NULL;
		return;
	}
	
	// Comme c'est non nul, pas d'overflow !
	taillePileDeScripts[touche]--;
	
	// Maintenant, on vérifie si la stack n'est pas trop large.
	// Sinon on poppe.
	if(taillePileDeScripts[touche] < TAILLE_PILE_DE_SCRIPTS) {
		scripts[touche] = pileDeScripts[touche][taillePileDeScripts[touche]];
		pileDeScripts[touche][taillePileDeScripts[touche]] = NULL;
	}
}


void ecrireNombre(unsigned int nombre, wchar_t* dest) {
	if(nombre > 99) {
		dest--;
		*dest = nombre / 100 + L'0';
		dest++;
		*dest = (nombre % 100) / 10 + L'0';
		dest++;
		*dest = nombre % 10 + L'0';
	} else {
		*dest = (nombre > 9) ? nombre / 10 + L'0' : L' ';
		dest++;
		*dest = nombre % 10 + L'0';
	}
}


EtatTouche etatTouche(Touche touche) {
	return scripts[touche] == NULL && etatTouches[touche] == TOUCHE_ENFONCEE;
}


unsigned int min(unsigned int a, unsigned int b) {
	return a < b ? a : b;
}


FILE* chargerFichier(const char* dossier, const char* nomFichier, const char* mode) {
	char cheminComplet[FILENAME_MAX];
	char* cheminFichier = strrchr(nomFichier, '/');
	
	strncpy(cheminComplet, dossier, FILENAME_MAX - 2);
	strcat(cheminComplet, "/");
	strncat(cheminComplet, cheminFichier ? cheminFichier : nomFichier, FILENAME_MAX - 2 - strlen(cheminComplet));
	
	return fopen(cheminComplet, mode);
}


void queryTextureInfo(SDL_Texture* texture) {
	Uint32 format;
	int access;
	int w;
	int h;
	
	SDL_QueryTexture(texture, &format, &access, &w, &h);
	LOGGER("Texture ")
	fprintf(fichierLog, "%p %u %d %d %d", texture, format, access, w, h);
}

