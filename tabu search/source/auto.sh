#/bin/bash
p1=$1
p2=$2
p3=$3

FILES=../data/*
OUTPUT=../solution/$p1.$p2.$p3/

mkdir $OUTPUT

for f in $FILES
do
	echo "Processing $f file..."
	# take action on each file. $f store current file name
	./maxsat $p1 $p2 $p3 < $f > $OUTPUT$(basename "$f").out
done
echo "Acabou. Pressione qualquer tecla."
read
