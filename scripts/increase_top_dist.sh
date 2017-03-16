for TOP_DIST in `seq 2 50`; do
    for i in `seq 1 20`; do
        ../boids -n 50 -m 2 -t $TOP_DIST -x 1500 -y 1500 -h 1500 -w 1500 -p -q
    done
done
