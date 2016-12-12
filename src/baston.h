
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
// ###### Header -- BASTON #####
// #############################


#pragma once


#include "defines.h"


extern unsigned int numFormationBataille;

// Wrapper de SDL_RenderCopyEx().
extern void rendreCopieEx(SDL_Texture* texture, const SDL_Rect* rectSource, const SDL_Rect* rectDest, const double angle, const SDL_Point* centre, const SDL_RendererFlip flip) __nonnull ((1, 2, 3, 5)) __attribute__ ((hot));
// Rend une TextureCombat.
extern void rendreTextureCombat(TextureCombat* texture) __nonnull ((1));
// Rend un protagoniste.
extern void rendreProtagoniste(Protagoniste* protagoniste) __nonnull ((1));

// Charge un Protagoniste.
extern Protagoniste* chargerProtagoniste(const char* nomFichierProtagoniste) __nonnull ((1)) __attribute__ ((warn_unused_result)) __attribute__ ((malloc));
// Décharge un Protagoniste.
extern void dechargerProtagoniste(Protagoniste* __restrict__ protagoniste);
// Charge une TextureCombat.
extern TextureCombat* chargerTextureCombat(const char* nomFichierTexture) __attribute__ ((warn_unused_result)) __attribute__ ((malloc));
// Décharge une TextureCombat.
extern void dechargerTextureCombat(TextureCombat* __restrict__ texture) __nonnull ((1));

// Démarre une bataille.
extern void demarrerBataille(unsigned int numFormation);
// Effectue l'inverse.
extern void terminerBataille(void);

// Script exécuté à chaque frame de la bataille.
extern void main__bataille(void);

