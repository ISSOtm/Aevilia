#!/bin/bash


echo

sourceFile=./Aevilia.tar.gz
targetFile=../../Public/Aevilia/Aevilia-$1.tar.gz

if [ "$1" = "" ]; then
	echo "publier.sh : Aucune version donnée !"
	echo "Syntaxe    : publier.sh num_de_version"
	echo "Exemple    : ./publier.sh 0.3.0"
else
	if [ ! -f $sourceFile ]; then
		echo "publier.sh : Fichier source inexistant !"
		echo "publier.sh : $sourceFile non trouvé."
		echo
		echo
		exit 1
	fi
	
	if [ -f $targetFile -a "$2" != "ecraser" ]; then
		echo "publier.sh : Fichier destination existant !"
		echo "publier.sh : Je refuse de remplacer $targetFile !"
		echo "Syntaxe    : publier.sh $1 ecraser"
		echo
		echo
		exit 1
	fi
	
	cp $sourceFile ../Archives/Stables/Aevilia-$1.tar.gz
	mv $sourceFile $targetFile
	if [ $? = 0 ]; then
		echo "Le fichier Aevilia-$1.tar.gz a été transféré !"
	fi
fi
echo
echo
