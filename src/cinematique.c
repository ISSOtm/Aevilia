
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
// ### Moteur de cinématique ###
// #############################


#include "cinematique.h"
#include "defines.h"
#include "aevilia.h"
#include "menus.h"



unsigned int (*actions[NB_ACTIONS])() =	   {bouger,
											attendreTouche,
											valider,
											actionMenu,
											attendreMenu,
											deplacerSpr,
											attendreFrames,
											tileSprite,
											ecrireOctet,
											djnz,
											flag,
											execFonction,
											modifTile};

#define NB_CINEMATIQUES_PILE				10
ElemCinematique* fileDactions[NB_CINEMATIQUES_PILE];
void ajouterCinematique(ElemCinematique* action) {
	if(actionEnCours == NULL) {
		actionEnCours = action;
	} else {
		unsigned int i = 0;
		while(fileDactions[i] != NULL) {
			i++;
		}
		if(i < NB_CINEMATIQUES_PILE) {
			fileDactions[i] = action;
		} else {
			actionEnCours = NULL;
			warperVersMap(ECRAN_CRASH, 0);
		}
	}
}

void terminerCinematique(void) {
	unsigned int i = 0;
	actionEnCours = fileDactions[0];
	while(fileDactions[i] != NULL) {
		fileDactions[i] = fileDactions[++i];
	}
}


unsigned int bouger(ElemCinematique* action) {
	direction = action->argumentUint;
	unsigned int i = 0;
	for( ; i < (unsigned int)action->argumentSint; i++) {
		avancer();
	}
	
	return 0;
}

unsigned int attendreTouche(ElemCinematique* action) {
	return !etatTouches[action->argumentUint]; // On continue si la touche est relâchée.
}

unsigned int valider(ElemCinematique* action) {
	if(action->argumentUint == 0 && etatTouches[VALIDER] == TOUCHE_ENFONCEE) {
		action->argumentUint = 1;
	}
	
	if(action->argumentUint != 0 && etatTouches[VALIDER] == TOUCHE_RELACHEE) {
		action->argumentUint = 0;
		return 0;
	}
	
	return 1;
}

unsigned int actionMenu(ElemCinematique* action) {
	ajouterMenu((Menu*)action->argumentPtr1);
	
	return 0;
}

unsigned int attendreMenu(void) {
	return menuArendre != NULL;
}

// Fun fact : déplacer de zéro... tourne, sans bouger !
unsigned int deplacerSpr(ElemCinematique* action) {
	((Sprite*)action->argumentPtr1)->direction = action->argumentUint;
	
	if(!(direction & 2)) {
		((Sprite*)action->argumentPtr1)->positionHoriz += ((direction & 1) * 2 - 1) * action->argumentSint;
	} else {
		((Sprite*)action->argumentPtr1)->positionVert += ((direction & 1) * 2 - 1) * action->argumentSint;
	}
	
	return 0;
}

unsigned int attendreFrames(ElemCinematique* action) {
	if(action->argumentUint > (unsigned int)action->argumentSint) {
		action->argumentSint++;
	} else {
		action->argumentSint = 0;
	}
	
	return action->argumentSint;
}

unsigned int tileSprite(ElemCinematique* action) {
	spritesMapCourante[action->argumentSint].tile = (wchar_t)action->argumentUint;
	
	return 0;
}

unsigned int ecrireOctet(ElemCinematique* action) {
	switch(action->argumentSint) {
		case OCTET_CHAR:
			*(unsigned char*)action->argumentPtr1 = (unsigned char)action->argumentUint;
		break;
		case OCTET_WCHAR:
			*(wchar_t*)action->argumentPtr1 = (wchar_t)action->argumentUint;
		break;
		case OCTET_INT:
			*(unsigned int*)action->argumentPtr1 = action->argumentUint;
	}
	
	return 0;
}

unsigned int djnz(ElemCinematique* action) {
	if(action->argumentUint == (unsigned int)action->argumentSint) {
		action->argumentSint = 0;
		action->elemSuivant = (ElemCinematique*)action->argumentPtr2;
	} else {
		action->argumentSint++;
		action->elemSuivant = (ElemCinematique*)action->argumentPtr1;
	}
	
	return 0;
}

unsigned int flag(ElemCinematique* action) {
	if(action->argumentSint == 0) {
		ETEINDRE_FLAG(action->argumentUint);
	} else {
		ALLUMER_FLAG(action->argumentUint);
	}
	
	return 0;
}

unsigned int execFonction(ElemCinematique* action) {
	return ((unsigned int(*)(void))action->argumentPtr1)();
}

unsigned int modifTile(ElemCinematique* action) {
	((Couche*)action->argumentPtr1)->tilemap[action->argumentUint] = (wchar_t)action->argumentSint;
	
	return 0;
}


void cinematique(void) {
	// On prefetch l'élément suivant avant le traitement de l'élément en cours, car il y a de grandes chances qu'on le lise. La plupart des actions de cinématique ne prennent qu'une seule frame de toute façon.
	__builtin_prefetch(actionEnCours->elemSuivant, PREFETCH_READONLY, 2);
	
	if(actionEnCours->action >= NB_ACTIONS || actions[actionEnCours->action](actionEnCours) == 0) {
		if(actionEnCours->elemSuivant != NULL) {
			actionEnCours = actionEnCours->elemSuivant;
		} else {
			actionEnCours = NULL;
			terminerCinematique();
		}
	}
}


void chargerFilm(Film* film) {

}

