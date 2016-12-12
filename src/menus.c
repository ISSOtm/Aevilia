
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
// ###### Moteur de menus ######
// #############################


#include <SDL2/SDL.h>
#include <string.h>
#include <wchar.h>

#include "menus.h"
#include "defines.h"
#include "aevilia.h"
#include "moteur_graphique.h"
#include "utilitaires.h"
#include "objets.h"


wchar_t chainesOuiNon[2][LONG_NOM_OPTIONS]	= {L"Oui", L"Non"};
Commande attendreEtTerminer			= CMD_ATTENDRE(NULL);


// Le tableau des fonctions parmettant d'exécuter les Commandes.
unsigned int (*commandes[])()			=  {afficherChaine,
											pause,
											fonction,
											sauter,
											appeler,
											nouveauMenu,
											attendre,
											effacer,
											options,
											objets,
											warp,
											octet,
											editionFlag,
											entrerTexte,
											demanderEntier};


Menu* dernierMenu(void) {
	// Éviter la segfault à la première itération.
	if(menuArendre == NULL) {
		return NULL;
	}
	
/*	Menu* pointeur = menuArendre;
	while(pointeur->prochainMenu) {
		pointeur = pointeur->prochainMenu;
	}
	return pointeur; */
	
	Menu** pointeur = &menuArendre;
	while((*pointeur)->prochainMenu) {
		pointeur = &(*pointeur)->prochainMenu;
	}
	return *pointeur;
}

void ajouterMenu(Menu* menu) {
	// Pour comprendre l'intérêt de l'existence de cette fonction et celui du ajouterMenuRapide(), lire menus.h
	Menu* dernier = dernierMenu();
	if(dernier) {
		ajouterMenuRapide(menu, &dernierMenu()->prochainMenu);
	} else {
		ajouterMenuRapide(menu, &menuArendre);
	}
}

void ajouterMenuRapide(Menu* menuAajouter, Menu** menuDajout) {
	// On retire le contrôle au joueur si aucun menu ne l'avait déjà fait avant nous.
	if(!menuArendre) {
		ETEINDRE_FLAG(CONTROLE_JOUEUR);
	}
	
	if(IMPROBABLE(*menuDajout)) {
#ifndef PRODUCTION
		WARN("ajouterMenuRapide : menuDajout invalide ! ")
		fprintf(fichierLog, "%p (addr %p)", *menuDajout, menuDajout);
#endif

		ajouterMenu(menuAajouter);
		return;
	}
	
	// On ajoute le menu.
	*menuDajout = menuAajouter;
	
	// On évite l'ajout de multiples menus d'un coup.
	menuAajouter->prochainMenu = NULL;
	
	// On va "dérouler" le menu.
	menuAajouter->fermeture = 0;
	menuAajouter->tailleHorizCourante = 0;
	
#ifndef PRODUCTION
	LOGGER("Ajout d'un menu. Pointeur : ")
	fprintf(fichierLog, "%p. Frame : %u.", menuAajouter, IDframe);
#endif
}

void retirerDernierMenu(void) {
	retirerMenu(dernierMenu());
}

void retirerMenu(Menu* menu) {
	// On réinitialise son texte,
	effacerMenu(menu);
	// et sa commande.
	menu->prochaineCommande = menu->commande;
#ifndef PRODUCTION
	LOGGER("Retrait d'un menu. Pointeur : ")
	fprintf(fichierLog, "%p. Frame : %u.", menu, IDframe);
#endif
	menu->fermeture = 1;
}

// Rendre tous les menus, puis exécuter la commande actuelle du dernier.
void activerMenus(void) {
	Menu* pointeur = menuArendre;
	if(pointeur == NULL) { // On retourne s'il n'y a rien à faire.
		return;
	}
	rendreMenu(pointeur); // On rend le premier menu,
	
	// On aura forcément besoin de pointeur->prochaineCommande, EXCEPTÉ si rendreMenu() crashe. De toute façon la performance n'est pas vraiment un souci dans ce cas-là.
	__builtin_prefetch(pointeur->prochaineCommande, PREFETCH_READWRITE, 2);
	
	while(pointeur->prochainMenu) { // Et on fait pareil s'il y en a d'autres.
		pointeur = pointeur->prochainMenu;
		
		// On prefetch le prochain menu pendant son traitement. Il est rare que rendreMenu() crashe.
		__builtin_prefetch(pointeur->prochainMenu, PREFETCH_READONLY, 0);
		
		rendreMenu(pointeur);
	}
	
	if(pointeur->tailleHoriz != pointeur->tailleHorizCourante) {
		return;
	}
	
	Commande* cmd = pointeur->prochaineCommande; // On sélectionne la commande à exécuter.
	
	if(cmd) { // Éviter la segfault.
		// Si la commande est invalide, on passe.
		// Sinon, on exécute la commande du menu.
		if(cmd->commande >= NB_CMD || !commandes[cmd->commande](cmd)) {
			// La fonction indique qu'elle a terminé. On passe à la commande suivante.
			pointeur->prochaineCommande = cmd->suivante;
		}
	}
	if(!pointeur->prochaineCommande) {
		// S'occupe aussi de remettre le menu à son état initial.
		retirerMenu(pointeur);
		
		// On réactive les menus afin de retirer ceux qui doivent encore l'être.
		//activerMenus();
	}
}

// Rend le menu passé en argument.
void rendreMenu(Menu* menu) {
	if(menu->fermeture) {
		if(!--menu->tailleHorizCourante) {
			if(!menuArendre) {
				return;
			}
			
			if(menuArendre == menu) {
				menuArendre = menu->prochainMenu;
//				menu->prochainMenu = NULL;
				
				if(!menuArendre) {
					ALLUMER_FLAG(CONTROLE_JOUEUR);	
				}
				return;
			}
			
			Menu* pointeur = menuArendre;
			while(pointeur->prochainMenu && pointeur->prochainMenu != menu) {
				pointeur = pointeur->prochainMenu;
			}
			
			// Si on n'a pas trouvé menu dans la chaîne, on quitte.
			if(!pointeur->prochainMenu) {
				return;
			}
			
			// On retire menu de la chaîne...
			pointeur->prochainMenu = menu->prochainMenu;
//			menu->prochainMenu = NULL;
			
			// Et si on a tout viré on donne le contrôle au joueur.
			if(!menuArendre) {
				ALLUMER_FLAG(CONTROLE_JOUEUR);
			}
			
			return;
		}
	} else if(menu->tailleHorizCourante < menu->tailleHoriz) {
		menu->tailleHorizCourante++;
	}
	
	int positionHoriz = menu->positionHoriz + (menu->tailleHoriz - menu->tailleHorizCourante) * LARGEUR_TILE / 2;
	SDL_Rect rectDest = TILE(positionHoriz, menu->positionVert);
	SDL_Rect rectSource = RECT_TILE;
	int compteur = 0;
	
	// On commence par rendre le cadre :
	// Bord haut,
	ciblerTile(COIN_HAUT_GAUCHE, &rectSource);
	rendreCopie(&rectSource, &rectDest);
	
	ciblerTile(BORD_HAUT, &rectSource);
	rectDest.x += LARGEUR_TILE;
	rectDest.w = LARGEUR_TILE * menu->tailleHorizCourante;
	rendreCopie(&rectSource, &rectDest);
	
	rectDest.x += rectDest.w;
	rectDest.w = LARGEUR_TILE;
	ciblerTile(COIN_HAUT_DROITE, &rectSource);
	rendreCopie(&rectSource, &rectDest);
	
	// Bord gauche,
	rectDest.x = positionHoriz;
	rectDest.y += HAUTEUR_TILE;
	rectDest.h = LARGEUR_TILE * menu->tailleVert;
	ciblerTile(BORD_GAUCHE, &rectSource);
	rendreCopie(&rectSource, &rectDest);
	
	// Intérieur du menu,
	rectDest.x += LARGEUR_TILE;
	ciblerTile(' ', &rectSource);
	rectDest.w = menu->tailleHorizCourante * LARGEUR_TILE;
	rendreCopie(&rectSource, &rectDest);
	rectDest.w = LARGEUR_TILE;
	
	// Bord droit,
	ciblerTile(BORD_DROIT, &rectSource);
	rectDest.x += menu->tailleHorizCourante * LARGEUR_TILE;
	rendreCopie(&rectSource, &rectDest);
	
	// Bord bas.
	rectDest.x = positionHoriz;
	rectDest.y += rectDest.h;
	rectDest.h = HAUTEUR_TILE;
	ciblerTile(COIN_BAS_GAUCHE, &rectSource);
	rendreCopie(&rectSource, &rectDest);
	
	ciblerTile(BORD_BAS, &rectSource);
	rectDest.x += LARGEUR_TILE;
	rectDest.w = LARGEUR_TILE * menu->tailleHorizCourante;
	rendreCopie(&rectSource, &rectDest);
	
	rectDest.x += rectDest.w;
	rectDest.w = LARGEUR_TILE;
	ciblerTile(COIN_BAS_DROITE, &rectSource);
	rendreCopie(&rectSource, &rectDest);
	
	// La structure du menu est rendue, on va maintenant afficher son texte.
	rectDest.x = positionHoriz + LARGEUR_TILE;
	rectDest.y = menu->positionVert  + HAUTEUR_TILE;
	
	if(!(IDframe % vitesseTexte)) {
		menu->nbCharsArendre++;
	}
	unsigned int nbCharsAffich = wcslen(menu->texte);
	// On cappe le nombre de caractères à rendre. De plus, si la touche ANNULER est enfoncée et qu'on ne force pas le défilement du texte, on rend tous les caractères.
	if(menu->nbCharsArendre > nbCharsAffich || (etatTouches[ANNULER] == TOUCHE_ENFONCEE && !FLAG(FORCER_DEFIL_TEXTE))) {
		menu->nbCharsArendre = nbCharsAffich;
	}
	// Selon l'état de la touche VALIDER, on marque le texte comme étant déjà passé, ou non.
	if(etatTouches[VALIDER] == TOUCHE_ENFONCEE) {
		ALLUMER_FLAG(TEXTE_PASSE);
	} else {
		ETEINDRE_FLAG(TEXTE_PASSE);
	}
	
	if(menu->tailleHorizCourante != menu->tailleHoriz) {
		return;
	}
	
	// On va afficher les caractères un par un.
	nbCharsAffich = 0;
	while(menu->texte[compteur] != L'\0' && nbCharsAffich < menu->nbCharsArendre) {
		if(menu->texte[compteur] != ENTREE) {
			ciblerTile(menu->texte[compteur], &rectSource);
			rendreCopie(&rectSource, &rectDest);
		} else {
			rectDest.x = positionHoriz + LARGEUR_TILE * menu->tailleHoriz;
		}
		if((unsigned int)rectDest.x == positionHoriz + LARGEUR_TILE * menu->tailleHoriz) {
			rectDest.y += HAUTEUR_TILE;
			rectDest.x = positionHoriz;
		}
		rectDest.x += LARGEUR_TILE;
		compteur++;
		nbCharsAffich++;

		// Éviter de dépasser du cadre.
		if((unsigned int)rectDest.y >= menu->positionVert + HAUTEUR_TILE * (menu->tailleVert + 1) && menu->texte[compteur] != L'\0') {
			// On cherche le premier caractère à afficher après le scroll.
			wchar_t* dernierCaractere = wmemchr(menu->texte, ENTREE, menu->tailleHoriz - 1);
			if(dernierCaractere == NULL) {
				// On n'a pas trouvé d'ENTREE, on va donc retirer toute une ligne.
				dernierCaractere = menu->texte + menu->tailleHoriz - 1;
			}
			// On scrolle.
			menu->nbCharsArendre -= dernierCaractere - menu->texte;
			wcscpy(menu->texte, dernierCaractere + 1);
			
			// On recommence l'affichage.
			nbCharsAffich = 0;
			compteur = 0;
			rectDest.x = positionHoriz + LARGEUR_TILE;
			rectDest.y = menu->positionVert  + HAUTEUR_TILE;
		}
	}
}



// FONCTIONS DE TRAITEMENT DE COMMANDES

unsigned int afficherChaine(Commande* commande) {
	Menu* menu		= dernierMenu();
	wchar_t* dest	= wcschr(menu->texte, L'\0'); // On se place à la première occurence de NUL.
	wchar_t* src	= (wchar_t*)commande->pointeur;
	
	if(commande->phase != 0) {
	
		if(menu->nbCharsArendre >= wcslen(menu->texte)) {
			commande->phase = 0;
			return 0;
		} else {
			return 1;
		}
		
	} else {
	
		while(*src != L'\0') {
			switch(*src) {
				// Les cas particuliers de caractères précèdent le default (afficher le caractère).
				
				// Affiche "on" ou "a" selon le sexe du joueur (prévu pour être utilisé pour "mon"/"ma", "son"/"sa", etc.
				case MON_MA:
					if(sexeJoueur == GARCON) {
						*dest = L'o';
						dest++;
						*dest = L'n';
					} else {
						*dest = L'a';
					}
					dest++;
				break;
				// Affiche un "e" si le joueur est une fille (permet de mettre au féminin dynamiquement).
				case E_SEXE:
					if(sexeJoueur) {
						*dest = L'e';
						dest++;
					}
				break;
				// Affiche le nom du joueur.
				case NOM_JOUEUR:
					dest = wcpcpy(dest, nomJoueur);
				break;
				// Affiche le pronom désignant le joueur.
				case IL_ELLE:
					if(sexeJoueur == GARCON) {
						*dest = L'i';
						dest++;
						*dest = L'l';
					} else {
						*dest = L'e';
						dest++;
						*dest = L'l';
						dest++;
						*dest = L'l';
						dest++;
						*dest = L'e';
					}
					dest++;
				break;
			
				// Cas normal : on affiche simplement le caractère.
				default:
					*dest = *src; // On copie un caractère,
					dest++; // Et on avance.
			}
			src++; // Caractère suivant, siouplaît !
		}
	
		*dest = L'\0'; // On rajoute un terminateur, et on a copié la chaîne.
		commande->phase = 1;
		
		if(commande->compteur) {
			AFFICHAGE_INSTANTANE(menu);
		}
		
		return 1; // On va attendre qu'elle soit affichée.
	}
}

unsigned int pause(Commande* commande) {
#define A_ATTENDRE	compteur
#define ECOULEES	compteur2
	
	commande->ECOULEES++;
	if(commande->ECOULEES < commande->A_ATTENDRE) {
		return 1;
	} else {
		commande->ECOULEES = 0;
		return 0;
	}
}

unsigned int fonction(Commande* commande) {
	
	commande->fonction2(commande); // La fonction doit modifier le compteur pour indiquer si elle a fini.
	return commande->compteur;
}

unsigned int sauter(Commande* commande) {
#define SI_SUCCES	pointeur
#define SI_ECHEC	pointeur2
#define CONDITION	fonction

	if(commande->CONDITION == NULL || commande->CONDITION() != 0) {
		commande->suivante = commande->SI_SUCCES;
	} else {
		commande->suivante = commande->SI_ECHEC;
	}
	return 0;
}

// Cette commande "wrappe" une exécution de commandes. C'est une copie du script de activerMenus(), à ceci près que :
// pointeur->commande est devenu commande->pointeur ;
// pointeur->prochaineCommande est devenu commande->pointeur2 ;
// quand toutes les commandes ont été exécutées, on ne retire pas le dernier menu, on retourne un valeur nulle.
unsigned int appeler(Commande* commande) {
#define DEPART		pointeur
#define PROCHAINE	pointeur2
	
	Commande* cmd = commande->PROCHAINE;
	if(!cmd) { // S'il n'y a pas de commande...
		return 0;
	}
	// On exécute la commande à traiter.
	if(!commandes[cmd->commande](cmd)) {
		// La fonction indique qu'elle a terminé. On prépare le passage à la commande suivante.
		if(cmd->suivante) {
			// Il y a encore des commandes à exécuter.
			commande->PROCHAINE = cmd->suivante;
		} else {
			// Il n'y a plus de commandes à exécuter.
			commande->PROCHAINE = commande->DEPART;
			return 0;
		}
	}
	return 1;
}

unsigned int nouveauMenu(Commande* commande) {
#define P_MENU		pointeur
#define MENU_AJOUTE	phase
#define CONSERVER	compteur
	if(commande->MENU_AJOUTE == commande->CONSERVER) {
		ajouterMenu(commande->P_MENU);
	}
	
	// Si on a forcé la frame d'inactivité.
	if(commande->MENU_AJOUTE) {
		commande->MENU_AJOUTE = commande->CONSERVER;
		return 0;
	}
	
	commande->MENU_AJOUTE = 1;
	return 1; // On force une frame d'inactivité. Ça empêche de nombreux bugs.
}

unsigned int attendre(void) {
	if(touchesPressees[VALIDER]) {
		touchesPressees[VALIDER] = TOUCHE_RELACHEE;
		return 0;
	}
	
	Menu* menu = dernierMenu();
	afficherTile(FLECHE_BAS, menu->positionVert + menu->tailleVert * HAUTEUR_TILE, menu->positionHoriz + menu->tailleHoriz * LARGEUR_TILE);
	return 1;
}

unsigned int effacer(void) {
	return effacerMenu(dernierMenu());
}

unsigned int effacerMenu(Menu* menu) {
	wmemset(menu->texte, L'\0', LONG_TEXTE_MENU);
	menu->nbCharsAsauter = 0;
	return 0;
}

Commande* derniereOption;

#define ARGUMENT_APPEL_1	pointeur
#define ARGUMENT_APPEL_2	pointeur2
#define POINTEURS_OPTIONS	pointeur3
#define NOMS_OPTIONS		pointeur4
#define NB_OPTIONS			compteur
#define PHASE				compteur2 // On ne peut pas utiliser commande.phase à cause de afficherChaine() !
#define POSITION_CURSEUR	compteur3
#define POSITION_FENETRE	compteur4
#define TAILLE_FENETRE		dernierMenu()->tailleVert
// Les quatre scripts pour déplacer le curseur de sélection.
void monterCurseur(void) {
	derniereOption->POSITION_CURSEUR--;
}
void descendreCurseur(void) {
	derniereOption->POSITION_CURSEUR++;
}
void monterFenetre(void) {
	derniereOption->POSITION_FENETRE -= TAILLE_FENETRE;
	derniereOption->POSITION_CURSEUR  = TAILLE_FENETRE - 1;
}
void descendreFenetre(void) {
	derniereOption->POSITION_FENETRE += TAILLE_FENETRE;
	derniereOption->POSITION_CURSEUR  = 0;
}
unsigned int options(Commande* commande) {
	// Ce code est - involontairement, je l'admets - surprenamment stable ; je m'explique :
	// 1. En utilisation "normale" (en somme, dans le cadre que j'ai prévu : options bien définies, nombre d'options > 0, etc.), le code se comporte très bien. Je n'ai pas encore trouvé de bugs dedans, mais je suis certain qu'au moins un m'a échappé.
	// 2. Les noms d'options trop longs ne posent en fait pas de problème - tant que ça ne déborde pas le menu. En fait, l'option suivante se placera gentiment sur la ligne d'après (l'option trop large n'est donc pas écrasée), et le curseur saute la ligne sur laquelle l'option a débordé). Si ça fait scroller le menu, l'option du haut sera cachée par le scrolling du menu, donc attention tout de même. Aucun code n'est prévu pour handler ce cas-là... mais ça pourra venir.
	// 3. Ce code s'auto-corrige. Simplement, si le code est exécuté avec des paramètres invalides (je ne parle pas des pointeurs), le code se replacera dans un cadre valide. Par exemple, les phases invalides causent la fermeture immédiate du menu. Les positions invalides - attention, elles arrivent pendant un gameplay legit, puisque les scripts qui les modifient ne font pas de bounds check, d'où les positions invalides - sont corrigées avant d'être utilisées.
	
	// Phase d'appel. Cette phase est totalement indépendante du reste - pas de scripts, pas de réécriture du texte du menu... D'où sa séparation totale du reste du menu.
	if(commande->PHASE == PHASE_OPTION_APPELS) {
		if(!appeler(commande)) {
			commande->PHASE = PHASE_OPTION_TERMINER;
		}
		
	} else {
	
		wchar_t chaine[LONG_TEXTE_MENU]	= L"";
		unsigned int i					= 0;
		wchar_t* dest					= chaine;
		
		// Phase de setup.
		if(commande->PHASE == PHASE_OPTION_SETUP) {
			derniereOption = commande;
			
			commande->POSITION_FENETRE = 0;
			commande->POSITION_CURSEUR = 0;
	
			pousserScript(HAUT, monterCurseur);
			pousserScript(BAS, descendreCurseur);
			pousserScript(GAUCHE, monterFenetre);
			pousserScript(DROITE, descendreFenetre);
		
			commande->PHASE = PHASE_OPTION_DEPL;
			
			commande->ARGUMENT_APPEL_2 = NULL;
			
			commande->phase = 0;
		}
	
		if(commande->PHASE == PHASE_OPTION_DEPL) {
			// Si la fenêtre est trop haute,
			if(commande->POSITION_FENETRE < 0) {
				// On remonte tout.
				commande->POSITION_FENETRE = 0; // A moins qu'il n'y ait 0 options, c'est valide.
				commande->POSITION_CURSEUR = 0;
			}
			// Si la fenêtre est trop loin (le curseur n'a pas d'importance ici),
			if((unsigned int)commande->POSITION_FENETRE >= commande->NB_OPTIONS) {
				// On redescend la fenêtre jusqu'à ce que le bas de la fenêtre coïncide 
				commande->POSITION_FENETRE = commande->NB_OPTIONS - dernierMenu()->tailleVert;
				commande->POSITION_CURSEUR = dernierMenu()->tailleVert - 1;
				if(commande->POSITION_FENETRE < 0) {
					commande->POSITION_FENETRE = 0;
					commande->POSITION_CURSEUR = commande->NB_OPTIONS - 1;
				}
			}
			// A partir d'ici, la position de la fenêtre est forcément valide.
			// Les fonctions de modification de la position de la fenêtre doivent simplement vérifier qu'elles conservent la validité de cette position. Elles peuvent (doivent ?) supposer sans risque que la position de la fenêtre est valide avant modification.
		
			// Si le curseur est au-dessus de la fenêtre,
			if(commande->POSITION_CURSEUR < 0) {
				// Si la fenêtre n'est pas déjà tout en haut, on la remonte.
				if(commande->POSITION_FENETRE != 0) {
					commande->POSITION_FENETRE--;
				}
				// On met le curseur en haut de la fenêtre. Corrige aussi les positions invalides.
				commande->POSITION_CURSEUR = 0;
			}
		
			// Si le curseur a dépassé la fenêtre.
			if(commande->POSITION_CURSEUR >= (signed int)TAILLE_FENETRE) {
				// Si le curseur n'a pas dépassé la fin de la liste, on descend la fenêtre.
				// On vérifie simplement que la nouvelle position du curseur sera valide.
				if(commande->POSITION_FENETRE + TAILLE_FENETRE < commande->NB_OPTIONS) {
					commande->POSITION_FENETRE++;
				}
				// On met le curseur en bas de la fenêtre. Corrige aussi les positions invalides.
				commande->POSITION_CURSEUR = TAILLE_FENETRE - 1;
			}
		
			// Si le curseur est au-delà de la fin de la liste.
			if(commande->POSITION_CURSEUR + commande->POSITION_FENETRE >= (signed int)commande->NB_OPTIONS) {
				// On déplace le curseur à la valeur maximale vérifiant la condition ci-dessus.
				commande->POSITION_CURSEUR = commande->NB_OPTIONS - commande->POSITION_FENETRE - 1;
			}
		
			// On est maintenant sûrs que la somme qui va servir d'index ci-dessous est valide.
		
			// Tout doit être NICKEL avant d'exécuter ce bout de code.
			if(touchesPressees[VALIDER] == TOUCHE_ENFONCEE || touchesPressees[ANNULER] == TOUCHE_ENFONCEE) {
				// On prépare les appels à appeler().
				dernierChoixMenu = (touchesPressees[ANNULER] == TOUCHE_ENFONCEE) ? (signed int)commande->NB_OPTIONS - 1 : commande->POSITION_CURSEUR + commande->POSITION_FENETRE;
			
				// Si on ANNULE, on quitte sans rien faire. appeler() retourne 0 direct.
				commande->ARGUMENT_APPEL_1 = (touchesPressees[ANNULER] == TOUCHE_ENFONCEE) ? NULL : ((Commande*(*))commande->POINTEURS_OPTIONS)[dernierChoixMenu];
				commande->ARGUMENT_APPEL_2 = commande->ARGUMENT_APPEL_1;
			
				// On passe en phase 3.
				commande->PHASE = PHASE_OPTION_FIN;
			}
		}
	
		// Ne pas fusionner avec la phase 2 !!
		// Cette phase est un "hook", en ce que des fonctions étrangères au menu peuvent forcer la sélection d'une option de la manière suivante :
		// 1. Initialiser les 
		if(commande->PHASE == PHASE_OPTION_FIN) {
			// On rétablit les scripts.
			popperScript(HAUT);
			popperScript(BAS);
			popperScript(GAUCHE);
			popperScript(DROITE);
			
			// On force au moins une frame en phase 4, pour permettre au curseur de devenir blanc.
			commande->PHASE = PHASE_OPTION_APPELS;
		}
	
		// On va générer le texte du menu.
		commande->pointeur = chaine;
		if(!commande->phase) {
			effacer();
		}
	
		for( ; i < TAILLE_FENETRE && i + (unsigned int)commande->POSITION_FENETRE < commande->NB_OPTIONS; i++) {	
			// Si on a validé le menu, on met un curseur "creux".
			*dest = ((signed int)i == commande->POSITION_CURSEUR) ? (/*commande->PHASE != PHASE_OPTION_APPELS &&*/ !commande->ARGUMENT_APPEL_2) ? CURSEUR : CURSEUR_VIDE : ' ';
			dest++;
			*dest = ' ';
			dest++;
			dest = wcpcpy(dest, ((wchar_t(*)[LONG_NOM_OPTIONS])commande->NOMS_OPTIONS)[i + commande->POSITION_FENETRE]); // Positionne au niveau du \0.
			*dest = ENTREE;
			dest++;
		}
		dest--; // On écrase le dernier ENTREE.
		*dest = L'\0';
		
		AFFICHAGE_INSTANTANE(dernierMenu());
		afficherChaine(commande);
	}
	
	if(commande->PHASE >= PHASE_OPTION_TERMINER) {
		commande->PHASE = PHASE_OPTION_SETUP;
		return 0;
	}
	
	return 1;
}

unsigned int objets(Commande* commande) {
	if(!commande->phase) {
		afficherObjetObtenu(commande->compteur, commande->compteur2);
		commande->phase = PHASE_OBJETS_OBTENU;
		return 1;
	}
	
	commande->phase = PHASE_OBJETS_OBTENIR;
	return 0;
}

unsigned int warp(Commande* commande) {
	mapDestination = commande->compteur;
	warpDestination = commande->compteur2;
	return 0;
}

unsigned int octet(Commande* commande) {
	switch(commande->compteur2) {
		case OCTET_CHAR:
			*(unsigned char*)commande->pointeur	= (unsigned char)commande->compteur;
		break;
		case OCTET_WCHAR:
			*(wchar_t*)commande->pointeur		= (wchar_t)commande->compteur;
		break;
		case OCTET_INT:
			*(unsigned int*)commande->pointeur	= commande->compteur; // Déjà un unsigned int...
	}
	
	return 0;
}

unsigned int editionFlag(Commande* commande) {
	if(commande->compteur2) {
		ALLUMER_FLAG(commande->compteur);
	} else {
		ETEINDRE_FLAG(commande->compteur);
	}
	
	return 0;
}

wchar_t chaineEntree[] = L"\
                           \
\1\
 A B C D E F G H I J K L M \
 N O P Q R S T U V W X Y Z \
 a b c d e f g h i j k l m \
 n o p q r s t u v w x y z \
 à â ä ç è é ê ë î ï ô ö ù \
 û ü -                   OK";

#define CHARS_MAX		compteur
#undef	PHASE
#define PHASE			compteur2
#define POSITION_VERT	compteur3
#define POSITION_HORIZ	compteur4
void effacerCurseur(void) {
	Commande* cmd = dernierMenu()->prochaineCommande;
	chaineEntree[cmd->POSITION_VERT * 27 + cmd->POSITION_HORIZ * 2 + 28] = L' ';
}
void entrerGauche(void) {
	effacerCurseur();
	dernierMenu()->prochaineCommande->POSITION_HORIZ--;
}
void entrerDroite(void) {
	effacerCurseur();
	dernierMenu()->prochaineCommande->POSITION_HORIZ++;
}
void entrerHaut(void) {
	effacerCurseur();
	dernierMenu()->prochaineCommande->POSITION_VERT--;
}
void entrerBas(void) {
	effacerCurseur();
	dernierMenu()->prochaineCommande->POSITION_VERT++;
}
void entrerValider(void) {
	dernierMenu()->prochaineCommande->PHASE = 2;
}
void entrerAnnuler(void) {
	// Si au moins un caractère a été entré,
	if((wchar_t*)dernierMenu()->prochaineCommande->pointeur2 > entreeUtilisateur) {
		// On revient en arrière et on écrit un \0.
		dernierMenu()->prochaineCommande->pointeur2 -= sizeof(wchar_t);
		*(wchar_t*)dernierMenu()->prochaineCommande->pointeur2 = 0;
	}
}
unsigned int entrerTexte(Commande* commande) {
	if(commande->CHARS_MAX > 14) {
		commande->CHARS_MAX = 14;
	}
	
	if(!commande->PHASE) {
		commande->pointeur2 = entreeUtilisateur;
		entreeUtilisateur[0] = 0;
		chaineEntree[6] = CURSEUR;
		
		pousserScript(GAUCHE, entrerGauche);
		pousserScript(DROITE, entrerDroite);
		pousserScript(HAUT, entrerHaut);
		pousserScript(BAS, entrerBas);
		pousserScript(VALIDER, entrerValider);
		pousserScript(ANNULER, entrerAnnuler);
		
		commande->PHASE = 1;
	}
	
	if(commande->POSITION_HORIZ < 0) {
		commande->POSITION_HORIZ = 12;
	} else if(commande->POSITION_HORIZ > 12) {
		commande->POSITION_HORIZ = 0;
	}
	if(commande->POSITION_VERT < 0) {
		commande->POSITION_VERT = 5;
	} else if(commande->POSITION_VERT > 5) {
		commande->POSITION_VERT = 0;
	}
	
	wmemset(&chaineEntree[8], L' ', 14);
	wcscpy(&chaineEntree[8], entreeUtilisateur);
	chaineEntree[wcslen(chaineEntree)] = L' ';
	chaineEntree[commande->POSITION_VERT * 27 + commande->POSITION_HORIZ * 2 + 28] = CURSEUR;
	
	effacer();
	commande->phase = 0;
	AFFICHAGE_INSTANTANE(dernierMenu());
	afficherChaine(commande);
	
	if(commande->PHASE == 2) {
		commande->PHASE = 1;
		
		if(commande->POSITION_VERT == 5 && commande->POSITION_HORIZ == 12) {
			if((wchar_t*)commande->pointeur2 != entreeUtilisateur) {
				popperScript(GAUCHE);
				popperScript(DROITE);
				popperScript(HAUT);
				popperScript(BAS);
				popperScript(VALIDER);
				popperScript(ANNULER);
		
				commande->PHASE = 3;
			}
		} else if((wchar_t*)commande->pointeur2 - entreeUtilisateur < commande->CHARS_MAX) {
			*(wchar_t*)commande->pointeur2 = chaineEntree[commande->POSITION_VERT * 27 + commande->POSITION_HORIZ * 2 + 29];
			commande->pointeur2 += sizeof(wchar_t);
			*(wchar_t*)commande->pointeur2 = 0;
		}
	}
	
	if(commande->PHASE == 3 && etatTouches[VALIDER] == TOUCHE_RELACHEE) {
		commande->PHASE = 0;
		return 0;
	}
	
	return 1;
}

Menu menuDemandeEntier = MENU(0, 0, 1, 3, NULL);
void ajouter1(void) {
	entreeEntier |= 1;
}
void retirer1(void) {
	entreeEntier |= 2;
}
void deplacerCurseurGauche(void) {
	entreeEntier |= 4;
}
void deplacerCurseurDroite(void) {
	entreeEntier |= 8;
}
unsigned int demanderEntier(Commande* commande) {
	if(!commande->phase) {
		// Refuser de démarrer tant que VALIDER est enfoncé.
		if(etatTouches[VALIDER]) {
			return 1;
		}
		commande->phase = 1;
		pousserScript(HAUT, ajouter1);
		pousserScript(BAS, retirer1);
		pousserScript(GAUCHE, deplacerCurseurGauche);
		pousserScript(DROITE, deplacerCurseurDroite);
		entreeEntier = 0;
		menuDemandeEntier.positionVert = commande->compteur;
		menuDemandeEntier.positionHoriz = commande->compteur2;
		menuDemandeEntier.tailleHoriz = 3;
		if(commande->compteur3 > 9) {
			menuDemandeEntier.tailleHoriz = 2;
			if(commande->compteur3 > 99) {
				menuDemandeEntier.tailleHoriz = 3;
			}
		}
		wcscpy(menuDemandeEntier.texte, L"000");
		AFFICHAGE_INSTANTANE(&menuDemandeEntier);
		positionCurseurEntree = 2;
	}
	
	if(entreeEntier > 7) {
		if(positionCurseurEntree < 2) {
			positionCurseurEntree++;
		} else {
			positionCurseurEntree = 2;
		}
		entreeEntier -= 8;
	}
	if(entreeEntier > 3) {
		if(positionCurseurEntree) {
			positionCurseurEntree--;
		} else {
			positionCurseurEntree = 0;
		}
		entreeEntier -= 4;
	}
	if(entreeEntier > 1) {
		menuDemandeEntier.texte[positionCurseurEntree] = (menuDemandeEntier.texte[positionCurseurEntree] != L'0') ? menuDemandeEntier.texte[positionCurseurEntree] - 1 : L'9';
		entreeEntier -= 2;
	}
	if(entreeEntier) {
		menuDemandeEntier.texte[positionCurseurEntree] = (menuDemandeEntier.texte[positionCurseurEntree] != L'9') ? menuDemandeEntier.texte[positionCurseurEntree] + 1 : L'0';
		entreeEntier--;
	}
	// entreeEntier vaut 0 à ce point.
	
	rendreMenu(&menuDemandeEntier);
	afficherTile(FLECHE_HAUT, menuDemandeEntier.positionVert + 6, menuDemandeEntier.positionHoriz + (positionCurseurEntree + 1) * LARGEUR_TILE);
	afficherTile(FLECHE_BAS, menuDemandeEntier.positionVert + HAUTEUR_TILE * 2 - 5, menuDemandeEntier.positionHoriz + (positionCurseurEntree + 1) * LARGEUR_TILE);
	
	if(touchesPressees[VALIDER]) {
		popperScript(HAUT);
		popperScript(BAS);
		popperScript(GAUCHE);
		popperScript(DROITE);
		swscanf(menuDemandeEntier.texte, L"%u", &entreeEntier);
		commande->phase = 0;
		return 0;
	}
	return 1;
}

