# Shell. Osef la compatibilité, je développe bien un jeu qui utilise l'accélération matérielle !
.SHELL: /bin/bash

# Règles spéciales
.PHONY: all, Aevilia, SaveIlia, couches, sprites, combat, rmlog, clean, mrproper, rebuild, dist

# Pas de règles implicites externes
.SUFFIXES:

# Par défaut... le jeu !
.DEFAULT_GOAL: all

# Variables standard
Debug      = enabled
bindir     = ./jeu
includedir = ./include
libdir     = ./lib
objdir     = ./objects
srcdir     = ./src
layrdir    = $(bindir)/couches
sprdir     = $(bindir)/sprites
combatdir  = $(bindir)/combat

ifeq ($(Debug),enabled) # Si debug, alors on devient verbeux sur les warnings, et on envoie du pâté pour GDB.
	debugflags = -Wall -Wextra -ggdb3
else
	debugflags = 
endif

# Niveaux d'optimisation
                      # +------------+-----------+-----------+--------------+
                      # | Exec speed | Code size | Mem usage | Compile time |
                      # +------------+-----------+-----------+--------------+
optiCompil        = 0 # |     -      |    +      |     -     |      -       |
                      # +------------+-----------+-----------+--------------+
optiSizeSpeed     = 1 # |     +      |    -      |     +     |      +       |
                      # +------------+-----------+-----------+--------------+
optiSpeed1        = 2 # |     ++     |           |     +     |      ++      |
                      # +------------+-----------+-----------+--------------+
optiSpeed2        = 3 # |    +++     |           |     +     |     +++      |
                      # +------------+-----------+-----------+--------------+
optiSize          = s # |            |    --     |           |      +       |
                      # +------------+-----------+-----------+--------------+
optiFastMath   = fast # |    +++     |           |     +     |     +++      |
                      # +------------+-----------+-----------+--------------+
optiDebugFriendly = g # |     +      |    +      |           |      +       | N'interfère pas avec le debug.
                      # +------------+-----------+-----------+--------------+
optiLvl       = $(optiDebugFriendly)


COMMONFLAGS	= $(debugflags) -L$(libdir) -I$(includedir)

CONLYFLAGS	= -x c -O$(optiLvl)
CFLAGS		= $(COMMONFLAGS) $(CONLYFLAGS) # Flags du compilateur

LONLYFLAGS	= -lSDL2-2.0
LFLAGS		= $(COMMONFLAGS) $(LONLYFLAGS) # Flags du linker

CLFLAGS		= $(COMMONFLAGS) $(CONLYFLAGS) $(LONLYFLAGS) # Flags quand le fichier .o n'est pas nécessaire


# Linker l'exécutable. Directive par défaut.
all : Aevilia couches sprites combat

Aevilia : $(bindir)/Aevilia

$(bindir)/Aevilia : $(objdir)/aevilia.o $(objdir)/baston.o $(objdir)/cinematique.o $(objdir)/maps.o $(objdir)/menus.o $(objdir)/moteur_graphique.o $(objdir)/objets.o $(objdir)/sauvegarde.o $(objdir)/utilitaires.o
	@echo
	@echo
	@echo ===== JEU Aevilia =====
ifeq ($(Debug),enabled)
	@echo
	@echo !! MODE DEBUG ACTIF !!
endif
	@echo
	@echo Compilation du jeu...
	@echo
	$(CC) $(LFLAGS) $^ -o $@
	@echo
	@echo


# Règles pour compiler chacun des objets. Pas de règle générique car les dépendances sont différents pour chaque fichier.
$(objdir)/%.o: $(srcdir)/%.c $(srcdir)/typedefs.h $(srcdir)/defines.h $(srcdir)/%.h
	@echo
	@echo
	@echo ===== OBJET $(@F) =====
	@echo
	$(CC) $(CFLAGS) -c $< -o $@
	@echo

$(objdir)/aevilia.o : $(srcdir)/tiles.c $(srcdir)/baston.h $(srcdir)/utilitaires.h $(srcdir)/moteur_graphique.h $(srcdir)/menus.h $(srcdir)/objets.h $(srcdir)/sauvegarde.h $(srcdir)/cinematique.h $(srcdir)/maps.h

$(objdir)/baston.o : $(srcdir)/moteur_graphique.h $(srcdir)/menus.h $(srcdir)/aevilia.h

$(objdir)/cinematique.o : $(srcdir)/aevilia.h $(srcdir)/moteur_graphique.h $(srcdir)/utilitaires.h $(srcdir)/objets.h

$(objdir)/maps.o : $(srcdir)/maps/*.c $(srcdir)/sauvegarde.h $(srcdir)/moteur_graphique.h $(srcdir)/utilitaires.h $(srcdir)/menus.h

$(objdir)/menus.o : $(srcdir)/aevilia.h $(srcdir)/moteur_graphique.h $(srcdir)/utilitaires.h $(srcdir)/objets.h

$(objdir)/moteur_graphique.o : $(srcdir)/utilitaires.h $(srcdir)/aevilia.h $(srcdir)/menus.h

$(objdir)/objets.o : $(srcdir)/utilitaires.h $(srcdir)/aevilia.h $(srcdir)/menus.h $(srcdir)/objets/*.c $(srcdir)/objets/*.h

$(objdir)/sauvegarde.o : $(srcdir)/aevilia.h $(srcdir)/utilitaires.h

$(objdir)/utilitaires.o : $(srcdir)/aevilia.h


couches : $(layrdir)/ $(layrdir)/TEST_0.layr $(layrdir)/TEST_1.layr $(layrdir)/TEST_2.layr $(layrdir)/EcranTitre_0.layr $(layrdir)/MaisonTEST_0.layr $(layrdir)/MaisonTEST_1.layr $(layrdir)/MaisonTEST_2.layr $(layrdir)/Intro_0.layr $(layrdir)/EcranCrash_0.layr

$(layrdir)/ :
	mkdir $(layrdir)

$(layrdir)/%.layr : $(srcdir)/maps/couches/%.layr $(srcdir)/maps/couches/LayrExport
	@echo
	@echo
	@echo ===== COUCHE $(@F) =====
	@echo
	$(srcdir)/maps/couches/LayrExport $< $@
	@echo
	@echo

$(srcdir)/maps/couches/LayrExport : $(srcdir)/maps/couches/LayrExport.c $(srcdir)/typedefs.h
	@echo
	@echo
	@echo ===== PROGRAMME LayrExport =====
	@echo
	$(CC) $(CLFLAGS) $< -o $@
	@echo


sprites : $(sprdir)/ $(sprdir)/TEST.spr $(sprdir)/EcranTitre.spr $(sprdir)/MaisonTEST.spr $(sprdir)/Intro.spr $(sprdir)/EcranCrash.spr

$(sprdir)/ :
	mkdir $(sprdir)/

$(sprdir)/%.spr : $(srcdir)/maps/sprites/%.spr $(srcdir)/maps/sprites/SprExport
	@echo
	@echo
	@echo ===== SPRITE $(@F) =====
	@echo
	$(srcdir)/maps/sprites/SprExport $< $@
	@echo

$(srcdir)/maps/sprites/SprExport : $(srcdir)/maps/sprites/SprExport.c $(srcdir)/typedefs.h
	@echo
	@echo
	@echo ===== PROGRAMME SprExport =====
	@echo
	$(CC) $(CLFLAGS) $< -o $@
	@echo


# .dtc : Données Texture Combat. No pun intended... quoique :3
combat : $(combatdir)/
# $(combatdir)/joueurTest/tete.dtc

$(combatdir)/ :
	mkdir $(combatdir)/

$(combatdir)/%.dtc : $(srcdir)/combat/%.dtc $(srcdir)/combat/TextureInfoExport
	@echo
	@echo
	@echo ===== INFO TEXTURE $(@F) =====
	@echo
	$(srcdir)/combat/TextureInfoExport $< $@
	@echo

$(srcdir)/combat/TextureInfoExport : $(srcdir)/combat/TextureInfoExport.c $(srcdir)/typedefs.h
	@echo
	@echo
	@echo ===== PROGRAMME TextureExport =====
	@echo
	$(CC) $(CLFLAGS) $< -o $@
	@echo


# Éditeur de sauvegardes pour Aevilia
SaveIlia : ./SaveIlia/SaveIlia

./SaveIlia/SaveIlia : ./SaveIlia/SaveIlia.o $(objdir)/sauvegarde.o $(objdir)/utilitaires.o
	@echo
	@echo
	@echo ===== SaveIlia =====
	@echo
	$(CC) $(LFLAGS) $^ -o $@
	@echo

./SaveIlia/SaveIlia.o : ./SaveIlia/src/main.c $(srcdir)/typedefs.h $(srcdir)/defines.h
	@echo
	@echo
	@echo ===== OBJET SaveIlia.o =====
	@echo
	$(CC) $(CFLAGS) -c $< -o $@
	@echo


# Nettoyage du log. Elle est là parce que au final je l'utilise x)
rmlog :
	rm -rf $(bindir)/aevilia.log
	@echo

# Cleanup de ce qui n'est pas l'exe.
clean : rmlog
	rm -rf $(objdir)/*.o
	rm -rf Aevilia.tar.gz
	@echo

# Cleanup total en vue d'un rebuild.
mrproper : clean
	rm -rf $(bindir)/Aevilia $(layrdir)/ $(sprdir)/ $(combatdir)/
	@echo

# Reconsruction complète : cleanup puis build.
rebuild : mrproper all

# Création d'une tarball distribuable. N'inclut pas le log !
dist : rebuild
	tar -czf Aevilia.tar.gz jeu/Aevilia jeu/img jeu/combat jeu/couches jeu/sprites jeu/readme.txt
	@echo

