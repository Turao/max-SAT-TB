#/bin/bash
FILES=../data/*
OUTPUT=../solution/
for f in $FILES
do
	echo "Processing $f file..."
	# take action on each file. $f store current file name
	./maxsat < $f > $OUTPUT$(basename "$f").out
done
echo "Acabou. Pressione qualquer tecla."
read
