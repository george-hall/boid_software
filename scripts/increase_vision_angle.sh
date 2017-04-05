for ANGLE in `seq 55 5 180`; do
    for i in `seq 1 20`; do
        ../boids -n 50 -m 1 -b $ANGLE -x 1500 -y 1500 -h 1500 -w 1500 -p -q
    done
done
