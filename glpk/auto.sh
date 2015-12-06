#/bin/bash

tlimit=$1

FILES=./data/compatible/*
OUTPUT=./solution/$tlimit/

mkdir $OUTPUT

for f in $FILES
do
	echo "Processing $f file..."
	# take action on each file. $f store current file name
	glpsol --math -m ./model/solver_max-sat.mod -d $f --output $OUTPUT$(basename "$f" .dat).out --tmlim $tlimit
	echo "$f done!"
done
echo "Acabou. Pressione qualquer tecla."
