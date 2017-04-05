## A flocking model using boids

This program implements a variation of Craig Reynolds' Boids model for
simulating flocks of birds. It is highly customisable via the command line. It
includes several different models.

The program can be compiled simply by running `make` in its root directory.

It can then be run using `./boids`. This will use all its default values (as shown below).

Command Line Options:

Option | Command Line Flag | Default Value
-------|-------------------|--------------
window width (pixels) | -w | 1000
window height (pixels) | -h | 650
plane x length | -x | same as window width
plane y length | -y | same as window height
number of boids | -n | 50
neighbourhood radius | -s | 50
danger zone radius | -d | 10
old velocity weight | -o | 1
avoidance weight | -a | 1
cohesion weight | -c | 1
alignment weight | -l | 1
input file name | -f | blank by defult
periodic boundary conditions | -p | false
print velocity correlation length | -k | false
verbose output | -v | false
quiet (don’t display simulation graphically) | -q | false
neighbourhood mode | -m | 0
number of neighbours in neighbourhood (only in topological mode) | -t | 7
vision angle (only in vision modes) | -b | 45
