
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
// ######### Sauvegarde ########
// #############################


#include <stdio.h>

#include "sauvegarde.h"
#include "utilitaires.h"


char nomSauvegarde[] = "aevilia.sav";
Sauvegarde sauvegardes[NB_SAUVEGARDES + 1] = {[NB_SAUVEGARDES] = {.version = {MAJEUR, MINEUR, BUGFIX},
																	.map = INTRO,
																	.posVertJoueur = HAUTEUR_FENETRE,
																	.posHorizJoueur = LARGEUR_FENETRE,
																	.couche = 0,
																	.posVertCamera = 0,
																	.posHorizCamera = 0,
																	.direction = BAS,
																	.ordreObj = {(unsigned int)-1},
																	.qtesObj = {0},
																	.flags = FLAGS_DEFAUT,
																	.interactions = {0},
																	.vitesseTexte = 3,
																	.PVjoueur = 20,
																	.PVmaxJoueur = 20,
																	.sexeJoueur = 0,
																	.nomJoueur = L"Ness"}};

void sauvegarder(void) {
	remove(nomSauvegarde);
	FILE* fichierSauvegarde = fopen(nomSauvegarde, "a");
	
	fwrite(sauvegardes, sizeof(Sauvegarde), NB_SAUVEGARDES, fichierSauvegarde);
	
	fclose(fichierSauvegarde);
}

CodeRetour charger(void) {
	FILE* fichierSauvegarde = fopen(nomSauvegarde, "r");
	if(!fichierSauvegarde) {
		return ERREUR_CHARGEMENT_SAUVEGARDES;
	}
	
	fread(sauvegardes, sizeof(Sauvegarde), NB_SAUVEGARDES, fichierSauvegarde);
	
	fclose(fichierSauvegarde);
	return SUCCES;
}

void mettreAjourSauvegarde(unsigned int numSauvegarde) {
	DIRE("Écriture sur la sauvegarde n°")
	fprintf(fichierLog, "%u", numSauvegarde);
	
	if(numSauvegarde < NB_SAUVEGARDES) {
		unsigned int i = 0;
#define SAUV(nomAttr, nomVar)	sauvegardes[numSauvegarde].nomAttr = nomVar;
		SAUV(version[0], version[0])
		SAUV(version[1], version[1])
		SAUV(version[2], version[2])
		SAUV(map, numMapCourante)
		SAUV(posVertJoueur, positionVertJoueur)
		SAUV(posHorizJoueur, positionHorizJoueur)
		SAUV(couche, coucheJoueur)
		SAUV(posVertCamera, positionVertCamera)
		SAUV(posHorizCamera, positionHorizCamera)
		SAUV(direction, direction)
		memcpy(sauvegardes[numSauvegarde].ordreObj, ordreObjets, (NB_OBJETS + 1) * sizeof(unsigned int));
		memcpy(sauvegardes[numSauvegarde].qtesObj, quantitesObjets, NB_OBJETS * sizeof(unsigned int));
		memcpy(sauvegardes[numSauvegarde].flags, flags, (NB_FLAGS / 8) * sizeof(unsigned char));
		for( ; i < NB_INTERACTIONS_SAUV; i++) {
			SAUV(interactions[i], interactionsAsauvegarder[i]->interagie)
		}
		SAUV(vitesseTexte, vitesseTexte)
		SAUV(PVjoueur, PVjoueur)
		SAUV(PVmaxJoueur, PVmaxJoueur)
		SAUV(niveauJoueur, niveauJoueur)
		SAUV(sexeJoueur, sexeJoueur)
		wmemcpy(sauvegardes[numSauvegarde].nomJoueur, nomJoueur, LONG_NOM_JOUEUR);
		SAUV(checksum, calculerChecksum(numSauvegarde))
		DIRE("Checksum : 0x")
		fprintf(fichierLog, "%hhx", sauvegardes[numSauvegarde].checksum);
	} else {
		ERROR("Impossible de charger la sauvegarde ")
		fprintf(fichierLog, "%u", numSauvegarde);
	}
}

CodeRetour decompresserSauvegarde(unsigned int numSauvegarde) {
	DIRE("Décompression de la sauvegarde n°")
	fprintf(fichierLog, "%u", numSauvegarde);
	
	if(numSauvegarde <= NB_SAUVEGARDES) {
		if(memcmp(sauvegardes[numSauvegarde].version, version, sizeof(version)) == 0 && calculerChecksum(numSauvegarde) == sauvegardes[numSauvegarde].checksum) {
			unsigned int i = 0;
#define CHARG(nomAttr, nomVar)	nomVar = sauvegardes[numSauvegarde].nomAttr;
			CHARG(map, numMapCourante)
			CHARG(posVertJoueur, positionVertJoueur)
			CHARG(posHorizJoueur, positionHorizJoueur)
			CHARG(couche, coucheJoueur)
			CHARG(posVertCamera, positionVertCamera)
			CHARG(posHorizCamera, positionHorizCamera)
			CHARG(direction, direction)
			memcpy(ordreObjets, sauvegardes[numSauvegarde].ordreObj, (NB_OBJETS + 1) * sizeof(unsigned int));
			memcpy(quantitesObjets, sauvegardes[numSauvegarde].qtesObj, NB_OBJETS * sizeof(unsigned int));
			
			// On va décompresser les flags. On doit donc sauvegarder les flags de plein écran, etc. puis les restaurer.
			if(FLAG(PLEIN_ECRAN_ACTIF)) {
				i = 1;
			}
			if(FLAG(DOUBLER_TAILLE_PIX)) {
				i += 2;
			}
			memcpy(flags, sauvegardes[numSauvegarde].flags, (NB_FLAGS / 8) * sizeof(unsigned char));
			if(i % 2 == 1) {
				ALLUMER_FLAG(PLEIN_ECRAN_ACTIF);
				i--;
			} else {
				ETEINDRE_FLAG(PLEIN_ECRAN_ACTIF);
			}
			if(i % 4 == 2) {
				ALLUMER_FLAG(DOUBLER_TAILLE_PIX);
				i -= 2;
			} else {
				ETEINDRE_FLAG(DOUBLER_TAILLE_PIX);
			}
			for( ; i < NB_INTERACTIONS_SAUV; i++) {
				CHARG(interactions[i], interactionsAsauvegarder[i]->interagie)
			}
			sauvegardes[NB_SAUVEGARDES].vitesseTexte = vitesseTexte;
			CHARG(vitesseTexte, vitesseTexte)
			CHARG(PVjoueur, PVjoueur)
			CHARG(PVmaxJoueur, PVmaxJoueur)
			CHARG(niveauJoueur, niveauJoueur)
			CHARG(sexeJoueur, sexeJoueur)
			wmemcpy(nomJoueur, sauvegardes[numSauvegarde].nomJoueur, LONG_NOM_JOUEUR);
			return SUCCES;
		} else {
			ERROR("Impossible de charger la sauvegarde ")
			fprintf(fichierLog, "%u", numSauvegarde);
			ERROR("Version d'Aevilia : ")
			fprintf(fichierLog, "%u.%u.%u", version[0], version[1], version[2]);
			ERROR("Version de la sauvegarde : ")
			fprintf(fichierLog, "%u.%u.%u", sauvegardes[numSauvegarde].version[0], sauvegardes[numSauvegarde].version[1], sauvegardes[numSauvegarde].version[2]);
			unsigned char chk = calculerChecksum(numSauvegarde);
			ERROR("Checksum calculée : 0x")
			fprintf(fichierLog, "%hhx", chk);
			ERROR("Checksum trouvée : 0x")
			fprintf(fichierLog, "%hhx", sauvegardes[numSauvegarde].checksum);
			return ERREUR_ACCES_SAUVEGARDE;
		}
	} else {
		ERROR("Impossible de charger la sauvegarde ")
		fprintf(fichierLog, "%u", numSauvegarde);
		ERROR("Sauvegarde inexistante.")
		return ERREUR_ACCES_SAUVEGARDE;
	}
}


unsigned char calculerChecksum(unsigned int numSauvegarde) {
	unsigned char* pointeur		= (unsigned char*)&sauvegardes[numSauvegarde];
	unsigned char* pointeurDest	= &sauvegardes[numSauvegarde].checksum;
	unsigned char checksum		= 0;
	
	while(pointeur < pointeurDest) {
		checksum += *pointeur;
		pointeur++;
	}
	
	return checksum;
}

