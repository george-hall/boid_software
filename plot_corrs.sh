#! /bin/bash

if [ $# -ne 1 ]
then
    echo "usage: $0 <file>"
    exit 1
fi

IN_FILE=$1
DATA_FILES=""
TEMP_FILES=""

for CORR_LEN in 10 30 50; do
    AWK_COMMAND='{if ($4 == "'$CORR_LEN':") {print $5}}'
    awk "$AWK_COMMAND" "$IN_FILE" > tmp
    awk '{print NR "\t" $0}' tmp > "corr_length_"$CORR_LEN".tmp"
    TEMP_FILES=$TEMP_FILES'corr_length_'$CORR_LEN'.tmp '
    DATA_FILES=$DATA_FILES'"corr_length_'$CORR_LEN'.tmp" using 1:2, '
    rm tmp
done

gnuplot -p <<EOF
set yr [-2:2]; plot $DATA_FILES
EOF

rm $TEMP_FILES
