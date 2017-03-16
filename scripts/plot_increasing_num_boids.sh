python print_medians.py ../../Data/out | sort -n -k 1 > m0;

echo '
set xlabel "Number of Boids";
set ylabel "Iterations Until Flock";
set yrange [0:20000];

plot "m0" using 1:2
' | gnuplot -p; rm m0 
