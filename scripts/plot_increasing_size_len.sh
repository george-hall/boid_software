python print_medians.py iters_until_flock_m0 | sort -n -k 1 > m0;
python print_medians.py iters_until_flock_m1 | sort -n -k 1 > m1;
python print_medians.py iters_until_flock_m2 | sort -n -k 1 > m2;

echo '
set key left top;
set xlabel "Side Length";
set ylabel "Iterations Until Flock";

plot "m0" using 1:2, "m1" using 1:2, "m2" using 1:2
' | gnuplot -p; rm m0 m1 m2
