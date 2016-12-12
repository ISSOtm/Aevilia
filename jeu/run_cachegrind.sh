#!/bin/bash


CACHEGRIND_OPTIONS=
CG_ANNOTATE="cg_annotate --sort=D1mr,DLmr,D1mw,DLmw --show=D1mr,DLmr,D1mw,DLmw"
STARTLINE=19
HOWMANYLINES=22
ENDLINE=$(($STARTLINE + $HOWMANYLINES - 1))

ROOTPATH=~/Dropbox/Aevilia/Dev
SRCPATH="$ROOTPATH/src"
GAMEPATH="$ROOTPATH/jeu"
CACHEGRINDOUTPATH="$ROOTPATH/Cachegrind"


echo
echo
echo "Cachegrind wrapper for Aevilia version 0.4.0"
echo "By ISSOtm, 26/11/2016"
echo
echo "Cachegrind will be run with options \"$CACHEGRIND_OPTIONS\""
echo

cd "$CACHEGRINDOUTPATH"

INDEX=0
while [ -f "cachegrind_$INDEX.txt" ]; do
	let INDEX=$((INDEX + 1))
done

echo "File ID $INDEX found to be free. Running Cachegrind..."
echo

cd "$GAMEPATH"
valgrind --tool=cachegrind --cachegrind-out-file="$CACHEGRINDOUTPATH/cachegrind_$INDEX.txt" $CACHEGRIND_OPTIONS "$GAMEPATH/Aevilia"

if [ $? -ne 0 ]; then
	echo
	echo "Something is wrong with Cachegrind ! Stopping."
	
	exit 1
fi

echo
echo "I'm done !"
echo

cd "$CACHEGRINDOUTPATH"
$CG_ANNOTATE "cachegrind_$INDEX.txt" > "cg_annotated_$INDEX.txt"

echo "Printing lines $STARTLINE-$ENDLINE of $CACHEGRINDOUTPATH/cg_annotated_$INDEX.txt."
echo

lineID=0
while IFS='' read -r line && [[ $lineID -lt $ENDLINE ]]; do
	if [ $lineID -ge $STARTLINE ]; then
		echo "$line"
	fi
	
	let lineID=$((lineID + 1))
	
done < "cg_annotated_$INDEX.txt"

echo "Done !"
echo
echo "Do you want to annotate a file ? Do not input anything if nope."
echo -n "$SRCPATH/"
read ANNOTATEDFILE
ANNOTATEDPATH="$SRCPATH/$ANNOTATEDFILE"

if [ -n "$ANNOTATEDFILE" ]; then
	echo "Annotating $ANNOTATEDPATH..."
	$CG_ANNOTATE cachegrind_$INDEX.txt "$ANNOTATEDPATH" > cg_annotated_$INDEX.txt
fi

echo "Done !"

echo "Do you want to create a differential file ?"
echo -n "Input its ID, or nothing if nope. "
read DIFF

if [ -n "$DIFF" ]; then
	cg_diff cachegrind_$DIFF.txt cachegrind_$INDEX.txt > cachegrind_$INDEX-$DIFF.txt
	echo "Written comparison to cachegrind_$INDEX-$DIFF.txt"
fi

exit 0

