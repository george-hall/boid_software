CC=gcc
CXX=g++

# It looks like I can get away without using all these flags
# CPP_FLAGS=-std=c++11 -lsfml-graphics -lsfml-window -lsfml-system
CPP_FLAGS=-std=c++11 -Wall -Wextra

SRCS=boids.cpp vector_misc.cpp other_misc.cpp command_line_parsing.cpp main.cpp
OBJS=$(SRCS:.cpp=.o)

PROG_NAME=boids

$(PROG_NAME): $(OBJS)
	$(CXX) $(CPP_FLAGS) -o boids $(OBJS)

%.o : %.cpp
	$(CXX) $(CPP_FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm *.o $(PROG_NAME) -f
