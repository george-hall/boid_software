#! /bin/bash

if [ $# -ne 1 ]
then
    echo "usage: $0 <file>"
    exit 1
fi

IN_FILE=$1
DATA_FILES=""
TEMP_FILES=""

# for CORR_LEN in 1 3 5 7 9 11 13; do
for CORR_LEN in 43; do
    AWK_COMMAND='{if ($1 == "'$CORR_LEN'") {print $2" "$1}}'
    awk "$AWK_COMMAND" "$IN_FILE" > tmp
    awk '{print NR "\t" $0}' tmp > "corr_length_"$CORR_LEN".tmp"
    TEMP_FILES=$TEMP_FILES'corr_length_'$CORR_LEN'.tmp '
    DATA_FILES=$DATA_FILES'"corr_length_'$CORR_LEN'.tmp" using 1:3:2, '
    rm tmp
done

gnuplot -p <<EOF
set nokey; set xlabel "Iteration"; set ylabel "Length"; set zlabel "Correlation"; splot $DATA_FILES;
EOF

rm $TEMP_FILES
