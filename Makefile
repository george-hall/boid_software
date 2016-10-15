CC=gcc
CXX=g++
CPP_FLAGS=-std=c++11 -lsfml-graphics -lsfml-window -lsfml-system

SRCS=boids.cpp main.cpp
OBJS=$(SRCS:.cpp=.o)

PROG_NAME="boids"

all: $(PROG_NAME)

$(PROG_NAME): $(OBJS)
	$(CXX) $(CPP_FLAGS) -o boids $(OBJS)

%.o : %.cpp
	$(CXX) $(CPP_FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm *.o $(PROG_NAME) -f
