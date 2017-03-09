for BOARD_SIZE in `seq 200 100 2500`; do
    for i in `seq 1 20`; do
        ./boids -q -p -x $BOARD_SIZE -y $BOARD_SIZE -m 2
    done
done
