
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
// #  Je me répète : CE N'EST  #
// #  PAS UNE VERSION BETA !!  #
// #                           #
// #   Si vous n'êtes pas un   #
// #   testeur ou débugueur,   #
// #  bravo pour avoir obtenu  #
// #  cette build !  --ISSOtm  #
// #                           #
// #############################
// ##                         ##
// ##### Fichier principal #####
// #############################


#include <SDL2/SDL.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#include "aevilia.h"
#include "defines.h"
#include "baston.h"
#include "utilitaires.h"
#include "moteur_graphique.h"
#include "menus.h"
#include "objets.h"
#include "sauvegarde.h"
#include "cinematique.h"
#include "maps.h"



void (*deplacements[NB_TOUCHES])(void)		= {haut, bas, gauche, droite};

Sprite spritesMapCourante[NB_SPRITES_MAX]	= {{HAUTEUR_FENETRE, LARGEUR_FENETRE, JOUEUR_HAUT, 0, 0, 0}}; // Sprite correspondant au joueur. Toujours en première position de l'spritesMapCourante. Initialisé pour ne pas être visible à l'écran titre.

unsigned char version[3]					= {MAJEUR, MINEUR, BUGFIX};


void initialiser(int argc, char* argv[]) {
	// Initialisation des variables globales
	rendreFrame						= FEU_VERT;
	jeuEnCours						= EN_COURS;
	
	codeRetour						= ERREUR_INCONNUE; // Prions pour qu'il soit écrasé.
	
	memset(etatTouches, 0, NB_TOUCHES * sizeof(char));
	// Je ne fais pas de defines sur les Scancode, parce qu'ils ne sont censés apparaître qu'ici !
	codesTouches[HAUT]				= SDL_SCANCODE_UP;
	codesTouches[BAS]				= SDL_SCANCODE_DOWN;
	codesTouches[GAUCHE]			= SDL_SCANCODE_LEFT;
	codesTouches[DROITE] 			= SDL_SCANCODE_RIGHT;
	codesTouches[VALIDER]			= SDL_SCANCODE_W;
	codesTouches[ANNULER]			= SDL_SCANCODE_Z;
	codesTouches[INVENTAIRE]		= SDL_SCANCODE_E;
#ifndef PRODUCTION
	codesTouches[TOUCHE_DEBUG]		= SDL_SCANCODE_P;
#endif
	codesTouches[SPRINT]			= SDL_SCANCODE_LSHIFT;
	codesTouches[PLEIN_ECRAN]		= SDL_SCANCODE_F11;
#ifndef PRODUCTION
	codesTouches[ACTIVER_FRAME_ADV]	= SDL_SCANCODE_O;
	codesTouches[AVANCER_FRAME]		= SDL_SCANCODE_A;
#endif
	codesTouches[QUITTER_JEU]		= SDL_SCANCODE_ESCAPE;
	codesTouches[BOUTON_SOURIS]		= SDL_SCANCODE_BOUTON_SOURIS;
	
	taillePixel						= 1;
	
	vitesseTexte					= 3;
	
	ordreObjets[0]					= NB_OBJETS;
	
	mapDestination					= -1;
	warpDestination					= -1;
	
	positionVertJoueur				= HAUTEUR_FENETRE;
	positionHorizJoueur				= LARGEUR_FENETRE;
	
	unsigned int i = 0;
	for(i = 0; i < (NB_FLAGS + 7) / 8; i++) {
		flags[i] = 0;
	}
	ALLUMER_FLAG(COLLISION_ACTIVE);
	
	// On calcule la checksum n°3 (celle par défaut)
	sauvegardes[NB_SAUVEGARDES].checksum = calculerChecksum(NB_SAUVEGARDES);
	
	srand(time(NULL)); // J'hésite à seeder autrement. Bah.
	
	
#ifndef PRODUCTION
	// On va lire les arguments passés en ligne de commande.
	i = 1;
	while((signed int)i < argc) {
		if(argv[i][0] == '-') {
			switch(argv[i][1]) {
				case 'd':
					ALLUMER_FLAG(ACTIVER_DEBUG);
				break;
				case 'g':
					ALLUMER_FLAG(DESACTIVER_ACCEL_GPU);
				break;
			}
		}
		i++;
	}
#endif
	
	
	// On tente de démarrer le logging.
	demarrerLogging();
	if(!fichierLog) {
		// On n'utilise pas terminer() car elle appelle les fonctions de logging.
		printf("Échec du démarrage du logging.");
		exit(ERREUR_OUVRIR_LOG);
	}
	
	// Il est très important de ne RIEN rajouter qui puisse déclencher du logging au-dessus de cette marque !!
	// Si vous le faites, en cas d'erreur d'ouverture du logging, le nettoyage ne se fera pas.
	
	DIRE("Démarrage d'Aevilia !")
	LOGGER("Logging démarré avec succès.")
	
	signal(SIGSEGV, segfault);
	
	initialiserGraphismes();
	
	LOGGER("Graphismes initialisés.")
	
	enregistrerHeaders();
	
	LOGGER("Récupération des sauvegardes...")
	
	charger();
	
	LOGGER("Terminé.")
	
	// On démarre le timer des frames.
	LOGGER("Création du timer des frames...");
	IDtimerFrame = SDL_AddTimer(INTERVALLE, &frame, NULL);
	if(IDtimerFrame == 0) {
		ERROR("Le timer de frame n'a pas pu être créé !")
		FATALERROR(SDL_GetError(), ERREUR_CREATION_TIMER_FRAME)
	}
#ifndef PRODUCTION
	IDtimerFPS = SDL_AddTimer(1000, &compterFPS, NULL);
#endif
	LOGGER("Le timer a été créé.")
	
	SDL_WarpMouseInWindow(pFenetre, LARGEUR_FENETRE / 2, HAUTEUR_FENETRE / 2);
	ALLUMER_FLAG(COLLISION_ACTIVE);
	pousserScript(INVENTAIRE, ouvrirInventaire);
	pousserScript(QUITTER_JEU, quitterJeu);
	
	LOGGER("Initialisation terminée !\n")
}

int main(/*int argc, char* argv[]*/) {
	// Appel commenté car fonction définie comme "constructeur" dans aevilia.h
	// Si le compilateur ne reconnaît pas l'attribut, décommenter.
	
	// On initialise ce qui doit l'être.
	// initialiser();
	
	#include "tiles.c"
	
	LOGGER("Chargement écran titre...")
	
	mapDestination = 1;
	warpDestination = -1;
	
	LOGGER("Ecran titre chargé.")
	
	
	// Code principal
	while(1) {
		// Indique qu'une frame est en cours. 
		rendreFrame = FEU_ROUGE;
		
		// Le truc qui sert dans toutes les boucles.
		unsigned int i = 0;
		
		// Si le joueur est en Kaizo et qu'il a plus de 0 PV, on le met à 1.
		// Premier truc dont se charge le jeu. Touchant, non ?
		if(FLAG(MODE_KAIZO)) {
			PVjoueur = !!PVjoueur;
		}
		
		// BASTOOOON !!
		if(numFormationBataille != (unsigned int)-1) {
			demarrerBataille(numFormationBataille);
			main__bataille();
			terminerBataille();
			
			numFormationBataille = -1;
		}
		
#ifndef PRODUCTION
		// Parmet d'afficher les jolies barres colorées en haut de l'écran :D
		tempsProcesseur[CHARGEMENT_MAP] = clock();
#endif
		// Charger une map. Avec ou sans warp.
		// On n'autorise pas à warper avec une cinématique active.
		if(warpDestination != (unsigned int)-1 && actionEnCours == NULL) {
			warperVersMap(mapDestination, warpDestination);
			mapDestination = (unsigned int)-1;
			warpDestination = (unsigned int)-1;
		} else if(mapDestination != (unsigned int)-1) {
			chargerMap(mapDestination);
			mapDestination = (unsigned int)-1;
		}
#ifndef PRODUCTION
		tempsProcesseur[CHARGEMENT_MAP] = clock() - tempsProcesseur[CHARGEMENT_MAP];
#endif
		
		// On exécute le script de frame.
		if(scriptFrame != NULL) {
			scriptFrame();
		}
		
		// On ajoute les cinématiques s'il y a lieu.
		for(i = 0 ; i < enTeteMapCourante.nbCinematiques && i < NB_CINEMATIQUES_MAX ; i++) {
			Cinematique* cinematique = enTeteMapCourante.cinematiques[i];
			if(actionEnCours == NULL && cinematique->positionVert == positionVertJoueur && cinematique->positionHoriz == positionHorizJoueur) {
				ajouterCinematique(cinematique->premierElement);
			}
		}
		
#ifndef PRODUCTION
		tempsProcesseur[EVENEMENTS] = clock();
#endif
		traiterEvenements();
#ifndef PRODUCTION
		tempsProcesseur[EVENEMENTS] = clock() - tempsProcesseur[EVENEMENTS];
		
		tempsProcesseur[JOUEUR_CINEMATIQUE] = clock();
#endif
		if(actionEnCours != NULL) {
			cinematique();
		} else {
			// Si le joueur n'est pas aligné sur la grille, on le force à avancer.
			if(positionVertJoueur % HAUTEUR_TILE != 0 || positionHorizJoueur % LARGEUR_TILE != 0) {
				avancer();
			} else if(FLAG(CONTROLE_JOUEUR)) {
				if(etatTouches[HAUT] + etatTouches[BAS] + etatTouches[GAUCHE] + etatTouches[DROITE] == TOUCHE_ENFONCEE) {
					for(i = HAUT; i < VALIDER; i++) {
						if(etatTouche(i) == TOUCHE_ENFONCEE) {
							deplacements[i]();
						}
					}
				}
				if(touchesPressees[VALIDER] == TOUCHE_ENFONCEE) {
					interagir();
				}
			}
		}
#ifndef PRODUCTION
		tempsProcesseur[JOUEUR_CINEMATIQUE] = clock() - tempsProcesseur[JOUEUR_CINEMATIQUE];
#endif
		
		for(i = 0; i < enTeteMapCourante.nbChangements && i < NB_CHANGEMENTS_MAX; i++) {
			ChangementCouche* changement = enTeteMapCourante.changementsCouches[i];
#ifndef PRODUCTION
			SDL_Rect rectSource = TILE(0, HAUTEUR_TILE);
			SDL_Rect rectDest = TILE(changement->positionHoriz, changement->positionVert);
			rendreCopie(&rectSource, &rectDest);
#endif
			if(changement != NULL && changement->positionVert == positionVertJoueur && changement->positionHoriz == positionHorizJoueur && changement->direction == direction) {
				coucheJoueur = changement->coucheDestination;
				break;
			}
		}
		
		for(i = 0; i < NB_WARPS_MAX && i < enTeteMapCourante.nbWarps; i++) {
			Warp* warp = enTeteMapCourante.warps[i];
			if(menuArendre == NULL && actionEnCours == NULL && warp->mapDest != 1 && positionVertJoueur == warp->positionVert && positionHorizJoueur == warp->positionHoriz) {// && coucheJoueur == warp->couche) {
				mapDestination = warp->mapDest;
				warpDestination = warp->warpDest;
			}
		}
		
		if(!FLAG(DETACH_SPRITE_JOUEUR)) {
			ajusterJoueur();
		}
		attacherCameraSprite(numSpriteCamera);
		
#ifndef PRODUCTION
		tempsProcesseur[TEMPS_RENDU] = clock();
#endif
		rendreMap(positionVertCamera, positionHorizCamera);
#ifndef PRODUCTION
		tempsProcesseur[TEMPS_RENDU] = clock() - tempsProcesseur[TEMPS_RENDU];
		
		if(__DEBUG__debuggerChangements != 0) {
			for(i = 0; i < enTeteMapCourante.nbChangements && i < NB_CHANGEMENTS_MAX; i++) {
				ChangementCouche* changement = enTeteMapCourante.changementsCouches[i];
				SDL_Rect rectSource = TILE(LARGEUR_TILE, HAUTEUR_TILE);
				SDL_Rect rectDest = TILE(changement->positionHoriz - positionHorizCamera, changement->positionVert - positionVertCamera);
				rendreCopie(&rectSource, &rectDest);
			}
		}
		if(__DEBUG__debuggerWarps != 0) {
			for(i = 0; i < enTeteMapCourante.nbWarps && i < NB_WARPS_MAX; i++) {
				Warp* warp = enTeteMapCourante.warps[i];
				SDL_Rect rectSource = TILE(LARGEUR_TILE, HAUTEUR_TILE);
				SDL_Rect rectDest = TILE(warp->positionHoriz - positionHorizCamera, warp->positionVert - positionVertCamera);
				rendreCopie(&rectSource, &rectDest);
			}
		}
		
		tempsProcesseur[MENUS] = clock();
#endif
		afficherBarreEtat();
		activerMenus();
#ifndef PRODUCTION
		tempsProcesseur[MENUS] = clock() - tempsProcesseur[MENUS];
		
		if(etatTouches[TOUCHE_DEBUG] == TOUCHE_RELACHEE) {
			afficherInfosDebug();
		}
#endif
		
		animer();
		
		IDframe++;
		rendrePresent();
#ifndef PRODUCTION
		if(etatTouches[ACTIVER_FRAME_ADV] == TOUCHE_ENFONCEE) {
			while(!touchesPressees[AVANCER_FRAME]) {
				traiterEvenements();
			}
		}
#endif
		if(!FLAG(DEBRIDER_FRAMES)) {
			while(rendreFrame != FEU_VERT) {
				SDL_Delay(1);
			} // On attend le feu vert. Que voulez-vous que je vous dise de plus ? xD
		}
	}
}

// Nettoyage avant de terminer avec exit(). Le programme doit SYSTÉMATIQUEMENT être terminé avec cette fonction !
// La seul exception possible est le "exit(ERREUR_OUVRIR_LOG)" dans initialiser(). On peut se le permettre puisque NORMALEMENT rien n'a encore été initialisé.
void terminer(CodeRetour statut) {
	popperScript(INVENTAIRE);
	
	nettoyerGraphismes();
	
	sauvegarder();
	
// Ce code doit être supprimé pour rendre la terminaison de terminer() indépendante de l'ouverture du log.
// Néanmoins, il serait mieux qu'il existe. Je le commente en espérant qu'on pourra le modifier et le décommenter.
// Le problème est que, en cas d'échec, logger() appelle terminer(), qui appelle logger() qui va probablement à nouveau échouer, etc.
/*	DIRE("Aevilia s'est terminé.")
	DIRE("Code de retour ")
	fprintf(fichierLog, "%d", statut);
	if(statut != SUCCES) {
		WARN("Ce code signale une erreur !")
	} else {
		DIRE("Ce code signale que tout s'est bien passé.")
	}
*/
	
	// Il est très important de ne RIEN ajouter après cette marque. Normalement, si l'ordre de initialiser() est respecté, ça n'arrivera pas.
	
	printf("Code retour : %d\n", statut);
	
	if(arreterLogging() != SUCCES) {
		printf("Échec de l'extinction du logging.");
		exit(ERREUR_FERMER_LOG);
	}
	
	exit(statut);
}

void quitterJeu(void) {
	gaucheDroite();
	terminer(SUCCES);
}

void terminerJeu(void) {
	terminer(codeRetour);
}

void crash(CodeRetour code) {
	codeRetour = code;
	chargerMap(ECRAN_CRASH);
}

void segfault(int arg) {
	ERROR("SEGFAULT !")
	ERROR("Code donné : ")
	fprintf(fichierLog, "%d", arg);
	terminer(ERREUR_SEGFAULT);
}



Uint32 frame(Uint32 delai, void* param_UNUSED) {
	rendreFrame = FEU_VERT;
	if(jeuEnCours == TERMINE) {
		LOGGER("Extinction du timer des frames.")
		return 0;
	} else {
		return delai;
	}
}

Uint32 compterFPS(Uint32 delai, void* param_UNUSED) {
	fps = IDframe - IDframePrec;
	IDframePrec = IDframe;
	if(jeuEnCours == TERMINE) {
		return 0;
	} else {
		return delai;
	}
}


void traiterEvenements(void) {
	unsigned int i = 0;
	for( ; i < NB_TOUCHES; i++) {
		touchesPressees[i] = TOUCHE_RELACHEE;
	}
	mouvementEnCours = false;
	
	while(SDL_PollEvent(&evenement)) {
		switch(evenement.type) {
			case SDL_WINDOWEVENT:
				switch(evenement.window.event) {
					case SDL_WINDOWEVENT_CLOSE:
						DIRE("Zoink sur la croix. Arrêt.")
						terminer(SUCCES);
					break;
				}
			break;
			case SDL_KEYDOWN:
				presserTouche(evenement.key.keysym.scancode);
			break;
			case SDL_KEYUP:
				relacherTouche(evenement.key.keysym.scancode);
			break;
			case SDL_MOUSEMOTION:
				mouvementEnCours = true;
				positionSourisVert  = evenement.motion.y;
				positionSourisHoriz = evenement.motion.x;
			break;
			case SDL_MOUSEBUTTONDOWN:
				if(evenement.button.button == SDL_BUTTON_LEFT) {
					presserTouche(SDL_SCANCODE_BOUTON_SOURIS);
				}
			break;
			case SDL_MOUSEBUTTONUP:
				if(evenement.button.button == SDL_BUTTON_LEFT) {
					relacherTouche(SDL_SCANCODE_BOUTON_SOURIS);
				}
			break;
			case SDL_QUIT:
				// L'utilisateur demande la fermeture ? Okay !
				DIRE("Requête de fermeture du logiciel. Arrêt.")
				terminer(SUCCES);
			break;
		}
	}
}
void presserTouche(SDL_Scancode codeTouche) {
	int index;
	
	for(index = 0; index < NB_TOUCHES; index++) {
		if(codeTouche == codesTouches[index]) {
			if(etatTouches[index] != TOUCHE_ENFONCEE) {
				etatTouches[index] = TOUCHE_ENFONCEE;
				
				// Le script a la possibilité de modifier les deux précédentes variables.
				if(scripts[index] != NULL) {
					scripts[index]();
				} else {
					touchesPressees[index] = TOUCHE_ENFONCEE;
				}
			}
			return;
		}
	}
}

void relacherTouche(SDL_Scancode codeTouche) {
	int index;
	
	for(index = 0; index < NB_TOUCHES; index++) {
		if(codeTouche == codesTouches[index]) {
			etatTouches[index] = TOUCHE_RELACHEE;
			return;
		}
	}
}



// Fonctions de déplacement du joueur.
unsigned char collision(unsigned int vert, unsigned int horiz, unsigned char numCouche, Direction direction) {
	unsigned char collisionDirection(unsigned int IDcouche) {
		if(IDcouche >= enTeteMapCourante.nbCouches) {
			return TRANSPARENT_BLOQUE;
		}
		return (attributsTiles[obtenirNumeroTile(vert / HAUTEUR_TILE, horiz / LARGEUR_TILE, &couchesMapCourante[IDcouche])]->collision >> direction) & 1;
	}
	
	// Vérifications prioritaires.
	if(vert % HAUTEUR_TILE != 0 || horiz % LARGEUR_TILE != 0) {
		return 1; // Si on est pas aligné, on passe.
	}
	// On ne doit pas sortir du cadre.
	if(horiz < positionHorizCamera || horiz >= positionHorizCamera + LARGEUR_FENETRE || vert < positionVertCamera || vert >= positionVertCamera + HAUTEUR_FENETRE) {
		return 0;
	}
	if(!FLAG(COLLISION_ACTIVE)) {
		return 1; // Si la collision est désactivée, on passe.
	}
	
	// Collision standard.
	unsigned int i = 0;
	Sprite* sprite;
	for( ; i < enTeteMapCourante.nbSprites && i < NB_SPRITES_MAX; i++) {
		sprite = &spritesMapCourante[i+1];
		if(sprite->positionVert == vert && sprite->positionHoriz == horiz && sprite->couche == coucheJoueur && sprite->tile != TRANSPARENT_MARCHE) {
			return 0; // Si on bumpe dans un sprite.
		}
	}
	
	// On tente de passer sur la couche actuelle et la couche du dessus.
	return collisionDirection(numCouche) && collisionDirection(numCouche+1);
}

#define DEPLACER(axe, signe)	if(etatTouches[SPRINT] == TOUCHE_ENFONCEE && FLAG(IGNORER_SPRINT) == 0 && position##axe##Joueur % 2 == 0) { \
									position##axe##Joueur signe##= 2; \
								} else { \
									position##axe##Joueur signe##signe; \
								}
void haut(void) {
	direction = HAUT;
	if(collision(positionVertJoueur - HAUTEUR_TILE, positionHorizJoueur, coucheJoueur, direction)) {
		DEPLACER(Vert, -)
	}
}

void bas(void) {
	direction = BAS;
	if(collision(positionVertJoueur + HAUTEUR_TILE, positionHorizJoueur, coucheJoueur, direction)) {
		DEPLACER(Vert, +)
	}
}

void gauche(void) {
	direction = GAUCHE;
	if(collision(positionVertJoueur, positionHorizJoueur - LARGEUR_TILE, coucheJoueur, direction)) {
		DEPLACER(Horiz, -)
	}
}

void droite(void) {
	direction = DROITE;
	if(collision(positionVertJoueur, positionHorizJoueur + LARGEUR_TILE, coucheJoueur, direction)) {
		DEPLACER(Horiz, +)
	}
}

void avancer(void) {
	// On force la validité de la direction.
	if((unsigned int)direction > DROITE) {
		direction = HAUT;
	}
	deplacements[direction]();
}


Menu menu = TEXTBOX(NULL);
void interaction(unsigned int IDinteraction) {
	if(IDinteraction < NB_INTERACTIONS) { // Ne rien faire si l'ID est invalide.
		Interaction* interaction = tableInteractions[IDinteraction];
		while(interaction->interactionSuivante != NULL && interaction->interagie != 0) {
			interaction = interaction->interactionSuivante;
		}
		interaction->interagie = 1;
		menu.prochaineCommande = interaction->commande;
		ajouterMenu(&menu);
	}
}

void interagir(void) {
	unsigned int i = 1; // Le sprite 0 est le joueur, et on ne peut pas (et ne doit pas) interagir avec lui.
	PosPixel posVert	 = positionVertJoueur;
	PosPixel posHoriz	 = positionHorizJoueur;
	Sprite* sprite;
	Sprite* sprDest		 = NULL;
	
	switch(direction) {
		case HAUT:
			posVert		-= HAUTEUR_TILE;
		break;
		case BAS:
			posVert		+= HAUTEUR_TILE;
		break;
		case GAUCHE:
			posHoriz	-= LARGEUR_TILE;
		break;
		case DROITE:
			posHoriz	+= LARGEUR_TILE;
		break;
		default: // Hm. C'est invalide ? Très bien !
			direction	 = HAUT;
			posVert		-= HAUTEUR_TILE;
	}
	
	for( ; i < NB_SPRITES_MAX; i++) {
		sprite = &spritesMapCourante[i];
		if(sprite != NULL && sprite->positionVert == posVert && sprite->positionHoriz == posHoriz && sprite->couche == coucheJoueur && sprite->IDtableInteractions != (unsigned int)NON_INTERACTIBLE) {
			if(sprDest != NULL) {
				return; // Empêcher les conflits si plusieurs sprites se bousculent.
			} else {
				sprDest = sprite;
			}
		}
	}
	if(sprDest != NULL) {
		// On tourne le sprite s'il n'ets pas fixé.
		if(sprDest->direction < VALIDER) {
			sprDest->direction = direction ^ 1;
		}
		// Puis on interagit.
		interaction(sprDest->IDtableInteractions);
	}
}



// Fonctions de maps.
void chargerMap(unsigned int IDmap) {
	DIRE("Chargement de la map ")
	fprintf(fichierLog, "%d.", IDmap);
	
	if(IDmap >= NB_MAPS) { // Ne rien faire si le numéro de map est invalide.
		ERROR("La map est invalide ! Elle n'a pas été chargée.")
	} else {
		numMapCourante = IDmap;
		
		memcpy(&enTeteMapCourante, enTetes[IDmap], sizeof(Map));
		
		// On va charger les couches via leur fichier.
		unsigned int i = 0;
		FILE* fichierExterne = NULL;
		
		for( ; i < enTeteMapCourante.nbCouches && i < NB_COUCHES_MAX; i++) {
			fichierExterne = chargerFichier("couches", enTeteMapCourante.fichiersCouches[i], "r");
			if(!fichierExterne) {
				ERROR("Chargement de la map ")
				fprintf(fichierLog, "%u", IDmap);
				ERROR("Impossible de charger le fichier ");
				fprintf(fichierLog, enTeteMapCourante.fichiersCouches[i]);
				ERROR(strerror(errno));
				if(IDmap != ECRAN_CRASH) {
					chargerMap(ECRAN_CRASH);
				} else {
					FATALERROR("Le chargement de l'écran de crash a échoué.", ERREUR_CHARGEMENT_COUCHES);
				}
				return;
			}
			fread(&couchesMapCourante[i], sizeof(Couche), 1, fichierExterne);
			
			fclose(fichierExterne);
		}
		
		// On va charger les sprites via leur fichier.
		fichierExterne = chargerFichier("sprites", enTeteMapCourante.fichierSprites, "r");
		if(!fichierExterne) {
			ERROR("Chargement de la map ")
			fprintf(fichierLog, "%u", IDmap);
			ERROR("Impossible de charger le fichier ");
			fprintf(fichierLog, enTeteMapCourante.fichierSprites);
			ERROR(strerror(errno));
			if(IDmap != ECRAN_CRASH) {
				chargerMap(ECRAN_CRASH);
			} else {
				FATALERROR("Le chargement de l'écran de crash a échoué.", ERREUR_CHARGEMENT_SPRITES);
			}
			return;
		}
		fread(&spritesMapCourante[1], sizeof(Sprite), NB_SPRITES_MAX - 1, fichierExterne);
		
		fclose(fichierExterne);
		
		scriptFrame = enTetes[IDmap]->script;
		
		if(enTetes[IDmap]->scriptChargement) {
			enTetes[IDmap]->scriptChargement();
		}
		
		DIRE("Terminé !")
	}
}

void warperVersMap(unsigned int IDmap, unsigned int IDwarp) {
	if(IDmap < NB_MAPS && IDwarp < enTetes[IDmap]->nbWarps && actionEnCours == NULL) { // Ne rien faire si le numéro de map ou de warp est invalide.
		Warp* warp = enTetes[IDmap]->warps[IDwarp];
		if(warp->condition == NULL || warp->condition()) { // Si la condition est validée,
			if(warp->animation != NULL) { // On effectue l'éventuelle transition,
				warp->animation();
				SDL_Delay(100);
			}
			
			positionVertJoueur	= warp->positionVert;
			positionHorizJoueur	= warp->positionHoriz;
			
			direction			= warp->direction;
			
			coucheJoueur		= warp->couche;
			
			chargerMap(IDmap); // On charge la map,
			
			if(!FLAG(CAMERA_FIXE)) {
				positionVertCamera	= positionVertJoueur - (HAUTEUR_FENETRE - HAUTEUR_TILE) / 2;
				positionHorizCamera	= positionHorizJoueur - (LARGEUR_FENETRE - LARGEUR_TILE) / 2;
			}
			if((signed int)positionVertCamera < 0) {
				positionVertCamera = 0;
			}
			if((signed int)positionHorizCamera < 0) {
				positionHorizCamera = 0;
			}
			
			if(warp->script != NULL) { // Puis on exécute l'éventuel script.
				warp->script();
			}
		}
	}
}


void ajusterJoueur(void) {
	spritesMapCourante[0].positionVert = positionVertJoueur;
	spritesMapCourante[0].positionHoriz = positionHorizJoueur;
	spritesMapCourante[0].direction = direction;
	spritesMapCourante[0].couche = coucheJoueur;
}

