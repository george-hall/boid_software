for NUM_BOIDS in `seq 10 10 150`; do
    for i in `seq 1 20`; do
        ../boids -n $NUM_BOIDS -m 1 -x 1500 -y 1500 -h 1500 -w 1500 -p -q
    done
done
