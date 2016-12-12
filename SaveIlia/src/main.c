
// #############################
// #                           #
// #    AEVILIA - GFX EDIT     #
// #       Version 0.0.1       #
// #                           #
// #     Contient des gros     #
// #   copier-coller du code   #
// #   d'Aevilia. Pourquoi ?   #
// #   La flemme ! \_(^.^)_/   #
// #                           #
// #############################
// ##                         ##
// ##### Fichier principal #####
// #############################


#include <stdio.h>
#include <stdlib.h>

#include "../../src/typedefs.h"
#include "../../src/defines.h"
#include "../../src/utilitaires.h"
#include "../../src/sauvegarde.h"



unsigned char version[3]	= {MAJEUR, MINEUR, BUGFIX};

int main(int argc, char* argv[]) {
	printf("\n");
	if(argc != 3 || strlen(argv[1]) != 2 || argv[1][0] != '-' || (argv[1][1] != 'i' && argv[1][1] != 'o')) {
		printf("Syntaxe incorrecte !\nSyntaxe : SaveIlia -i sauvegarde.txt pour convertir un .sav en .txt\n        : SaveIlia -o sauvegarde.txt pour convertir un .txt en .sav\n\n");
		return 1;
	}
	
	if(demarrerLogging()) {
		perror("Erreur de démarrage du logging ! ");
		printf("\n");
		return 1;
	}
	FILE* fichierTxt;
	char nomSauvegarde[] = "aevilia.sav";
	
	char formatFichierTxt0[]	= "version = %u.%u.%u\nmap = %u\nposVertJoueur = %u\nposHorizJoueur = %u\ncouche = %u\nposVertCamera = %u\nposHorizCamera = %u\ndirection = %u\n";
	char formatFichierTxt1[]	= "vitesseTexte = %u\nPVjoueur = %u\nPVmaxJoueur = %u\nniveauJoueur = %u\nsexeJoueur = %u\n";
	
	Interaction dummy;
	unsigned int i = 0;
	for( ; i < NB_INTERACTIONS_SAUV; i++) {
		interactionsAsauvegarder[i] = &dummy;
	}
	char nomJoueur_char[LONG_NOM_JOUEUR * MB_CUR_MAX];
	
	if(argv[1][1] == 'o') {
		// OUTPUT
		
		fichierTxt = fopen(argv[2], "r");
		if(!fichierTxt) {
			printf("Erreur fatale !\n");
			perror(argv[2]);
			printf("\n");
			return 1;
		}
		printf("Fichier %s ouvert !\n", argv[2]);
		remove(nomSauvegarde);
		
		unsigned int IDsave = 0;
		for( ; IDsave < NB_SAUVEGARDES; IDsave++) {
			fscanf(fichierTxt, formatFichierTxt0, &version[0], &version[1], &version[2], &numMapCourante, &positionVertJoueur, &positionHorizJoueur, &coucheJoueur, &positionVertCamera, &positionHorizCamera, &direction);
			
			unsigned int tmpvar;
			for(i = 0 ; i < NB_OBJETS + 1; i++) {
				fscanf(fichierTxt, "ordreObjets[%*u] = %u\n", &ordreObjets[i]);
			}
			for(i = 0; i < NB_OBJETS; i++) {
				fscanf(fichierTxt, "qtesObjets[%*u] = %u\n", &quantitesObjets[i]);
			}
			for(i = 0; i < (NB_FLAGS + 7) / 8; i++) {
				fscanf(fichierTxt, "flags[%*u] = 0x%02x\n", &tmpvar);
				flags[i] = (unsigned char)tmpvar;
			}
			for(i = 0; i < NB_INTERACTIONS_SAUV; i++) {
				fscanf(fichierTxt, "interactionsSauv[%*u] = %u\n", &tmpvar);
				interactionsAsauvegarder[i]->interagie = (unsigned char)tmpvar;
			}
			fscanf(fichierTxt, formatFichierTxt1, &vitesseTexte, &PVjoueur, &PVmaxJoueur, &niveauJoueur, &sexeJoueur);
			if(!fscanf(fichierTxt, "nomJoueur = %s\n\n", nomJoueur_char)) {
				nomJoueur[0] = 0;
			} else {
				mbstowcs(nomJoueur, nomJoueur_char, LONG_NOM_JOUEUR);
			}
			
			sauvegardes[IDsave].checksum = calculerChecksum(IDsave);
			mettreAjourSauvegarde(IDsave);
		}
		
		printf("Compression terminée. Écriture dans le fichier...\n");
		sauvegarder();
		
	} else {
		// INPUT
		
		remove(argv[2]);
		fichierTxt = fopen(argv[2], "a");
		if(!fichierTxt) {
			printf("Erreur fatale !\n");
			perror(argv[2]);
			printf("\n");
			return 1;
		}
	
		printf("Fichier %s ouvert !\n", argv[2]);
		
		if(charger()) {
			printf("Erreur de chargement du fichier de sauvegardes !\n");
			perror(nomSauvegarde);
			printf("\n");
			return 1;
		}
		printf("Fichier de sauvegardes lu. Décompression...\n");
		
		unsigned int IDsave = 0;
		for( ; IDsave < NB_SAUVEGARDES; IDsave++) {
			unsigned int vraieVersion[3] = {sauvegardes[IDsave].version[0], sauvegardes[IDsave].version[1], sauvegardes[IDsave].version[2]};
			sauvegardes[IDsave].version[0] = version[0];
			sauvegardes[IDsave].version[1] = version[1];
			sauvegardes[IDsave].version[2] = version[2];
			sauvegardes[IDsave].checksum = calculerChecksum(IDsave);
			decompresserSauvegarde(IDsave);
			
			fprintf(fichierTxt, formatFichierTxt0, (unsigned int)vraieVersion[0], (unsigned int)vraieVersion[1], (unsigned int)vraieVersion[2], numMapCourante, positionVertJoueur, positionHorizJoueur, coucheJoueur, positionVertCamera, positionHorizCamera, direction);
		
			for(i = 0 ; i < NB_OBJETS + 1; i++) {
				fprintf(fichierTxt, "ordreObjets[%u] = %u\n", i, ordreObjets[i]);
			}
			for(i = 0; i < NB_OBJETS; i++) {
				fprintf(fichierTxt, "qtesObjets[%u] = %u\n", i, quantitesObjets[i]);
			}
			for(i = 0; i < (NB_FLAGS + 7) / 8; i++) {
				fprintf(fichierTxt, "flags[%u] = 0x%02x\n", i, flags[i]);
			}
			for(i = 0; i < NB_INTERACTIONS_SAUV; i++) {
				fprintf(fichierTxt, "interactionsSauv[%u] = %u\n", i, interactionsAsauvegarder[i]->interagie);
			}
			fprintf(fichierTxt, formatFichierTxt1, vitesseTexte, PVjoueur, PVmaxJoueur, niveauJoueur, sexeJoueur);
			wcstombs(nomJoueur_char, nomJoueur, LONG_NOM_JOUEUR * MB_CUR_MAX);
			fprintf(fichierTxt, "nomJoueur = %s\n\n", nomJoueur_char);
		}
	}
	
	fclose(fichierTxt);
	arreterLogging();
	printf("Terminé.\n\n");
	return 0;
}

void terminer(CodeRetour statut) {
	exit(statut);
}

