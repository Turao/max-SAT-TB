#/bin/bash
DIRECTORIES=../solution/*/
FILES=./*.out
OUTPUT=../solution/resultados.csv

echo "" > $OUTPUT

for d in $DIRECTORIES
do
	pasta=$(echo $d | cut -d'/' -f 3 | cut -d'/' -f 1)

	pasta1=$(echo $pasta | cut -d'.' -f 1)
	pasta2=$(echo $pasta | cut -d'.' -f 2)
	pasta3=$(echo $pasta | cut -d'.' -f 3)

	echo -n "$pasta1;$pasta2;$pasta3;" >> $OUTPUT

	for f in $d$FILES
	do
		filename="${f%.*}"
		nome="${filename%.*}"
		nome=$(basename $nome)

		i=0

		while IFS='' read -r line || [[ -n "$line" ]] ; do

			i=$(($i + 1))
		
			if [ $i == 9 ]
			then
				solucao=$(echo "$line" | cut -d':' -f 2 | cut -d' ' -f 2 | cut -d'.' -f 1)
			elif [ $i == 10 ]
			then
				tempo=$(echo "$line" | cut -d':' -f 2 | cut -d' ' -f 2 | cut -d's' -f 1 | tr '.' ',')
				echo -n "$solucao;$tempo;" >> $OUTPUT
				break
			fi
		done < "$f"
	done
	echo "" >> $OUTPUT
done
echo "Acabou. Pressione qualquer tecla."
read
