
   ▄▄▄      ▓█████ ██▒   █▓ ██▓ ██▓     ██▓ ▄▄▄      
  ▒████▄    ▓█   ▀▓██░   █▒▓██▒▓██▒    ▓██▒▒████▄    
  ▒██  ▀█▄  ▒███   ▓██  █▒░▒██▒▒██░    ▒██▒▒██  ▀█▄  
  ░██▄▄▄▄██ ▒▓█  ▄  ▒██ █░░░██░▒██░    ░██░░██▄▄▄▄██ 
   ▓█   ▓██▒░▒████▒  ▒▀█░  ░██░░██████▒░██░ ▓█   ▓██▒
   ▒▒   ▓▒█░░░ ▒░ ░  ░ ▐░  ░▓  ░ ▒░▓  ░░▓   ▒▒   ▓▒█░
    ▒   ▒▒ ░ ░ ░  ░  ░ ░░   ▒ ░░ ░ ▒  ░ ▒ ░  ▒   ▒▒ ░
    ░   ▒      ░       ░░   ▒ ░  ░ ░    ▒ ░  ░   ▒   
        ░  ░   ░  ░     ░   ░      ░  ░ ░        ░  ░
 _   _               _ ░             _____    ___  _____
| | | |             (_)             |  _  |  /   ||  _  |
| | | | ___ _ __ ___ _  ___  _ __   | |/' | / /| || |/' |
| | | |/ _ \ '__/ __| |/ _ \| '_ \  |  /| |/ /_| ||  /| |
\ \_/ /  __/ |  \__ \ | (_) | | | | \ |_/ /\___  |\ |_/ /
 \___/ \___|_|  |___/_|\___/|_| |_|  \___(_)   |_(_)___/ 

NOTE A ENLEVER EN PROD
NB : les polices sont respectivement "Bloody" puis "Doom", réarrangées ensemble à la main.



Une documentation est également disponible en ouvrant le terminal dans ce dossier et en tapant "man ./aeviman".

[0000] INSTALLATION
[1000] CONTRÔLES
 [1100] Naviguer dans l'overworld
 [1200] Naviguer dans les menus
 [1300] Notes sur les boîtes de dialogue
 [1400] Notes sur le plein écran
[D000] BUGS CONNUS
[E000] CONTACT
[F000] CRÉDITS



[0000] INSTALLATION

Pour jouer à ce jeu, il vous faut le paquet sdl2.

-> Avec Synaptic
1. Lancez Synaptic.
2. Dans le champ "Recherche", tapez (sans les guillemets) "sdl2".
3. Cherchez dans la liste "libsdl2-2.0-0".
4. Si la case à cocher juste devant est verte, passez à l'étape 6.
5. Double-cliquez sur le "libsdl2-2.0-0", puis appliquez les changements.
6. Fermez Synaptic.
7. C'est prêt, lancez Aevilia !

-> Avec un terminal
1. Si vous êtes déjà root / administrateur, passez à l'étape 3.
2. Tapez (sans les guillemets) "su" puis le mot de passe root / administrateur.
3. Tapez (sans les guillemets) "apt-get install libsdl2-2.0-0"
4. Quand c'est fini, tapez "exit" (sans les guillemets) deux fois.
5. C'est prêt, lancez Aevilia !



[1000] CONTRÔLES

Ces contrôles sont toujours valides.
ECHAP						- Ferme le jeu.
(Vous pouvez aussi utiliser la croix en haut à droite, ou Alt + F4, mais ça sera un poil différent)
F11                     	- Plein écran (activer / désactiver).


[1100] Naviguer dans l'overworld

HAUT, BAS, GAUCHE, DROITE	- Se déplacer.
(Attention, n'utilise pas le pavé numérique)
Z                       	- Interagir.
E                       	- Inventaire (ouvrir / fermer).
SHIFT GAUCHE            	- Sprinter (maintenir enfoncé).


[1200] Naviguer dans les menus

HAUT, BAS               	- Déplacer le curseur d'une option à la fois.
GAUCHE, DROITE          	- Déplacer le curseur d'une "page" entière.
(N'utilise toujours pas le pavé numérique)
Z                       	- Valider.
W                       	- Annuler.


[1300] Notes sur les boîtes de dialogue

Les seules touches habituellement actives dans une boîte de dialogue sont Z et W, qui servent respectivement à VALIDER et ANNULER.
W permet d'afficher tout le texte de la boîte de dialogue d'une seule traite, au lieu d'attendre qu'il défile.
Parfois, le jeu attendra que vous appuyiez sur Z pour continuer le texte. Dans ce cas, une petite flèche appraîtra en bas à droite de la boîte de dialogue.
Dans certaines boîtes de dialogue (clavier, menu d'options, etc.), les flèches directionnelles seront actives.
À noter aussi que certaines boîtes de dialogue laissent au joueur la possibilité de se déplacer, ce sera normalement explicitement indiqué.


[1400] Notes sur le plein écran

Quand vous passez le jeu en plein écran, si le jeu détecte qu'il en a la place, il doublera la taille de l'affichage.
Si ce n'est pas le cas, soit :
1. Votre écran est trop petit, il n'y a pas la place de passer en plein écran ;
2. La librairie graphique n'a pas réussi à détecter qu'il y a de la place sur votre écran. Désolé.

Le jeu peut ne pas passer en plein écran s'il rencontre une erreur.



[D000] BUGS CONNUS
Aucun pour le moment !



[E000] CONTACT

Pour me contacter, envoyez-moi un mail à :
eldredhabert0@gmail.com
S'il vous plaît, mettez dans l'objet du mail que vous me parlez d'Aevilia, sinon je ne saurai pas forcément de quoi vous parlez.

Si vous me contactez à cause d'un bug, rendrez-moi un p'tit service : fermez d'abord le jeu, puis joignez une copie du fichier aevilia.log dans le message. Ça m'aide beaucoup, particulièrement si c'est un crash.



[F000] CRÉDITS

PROGRAMME
ISSOtm (juillet 2016 - octobre 2016)

SCÉNARIO
Aeghiss

GRAPHISMES
ISSOtm
Mian

REMERCIEMENTS
Citx (soutien moral et bonnes idées)
Ciapa-Noir (aide au code)
Xorl (soutien moral intense)
Toi, rien que pour avoir lu ce fichier...
 et si tu l'as lu avant d'avoir joué au jeu, vraiment, merci !
Merci, man ! Enjoy !



[????] BONBON

___    .-"""-.    ___
\  \  /\ \ \ \\  /  /
 }  \/\ \ \ \ \\/  {
 }  /\ \ \ \ \ /\  {
/__/  \ \ \ \ /  \__\
       '-...-'

