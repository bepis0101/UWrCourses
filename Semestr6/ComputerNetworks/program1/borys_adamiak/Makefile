CC = g++
CFLAGS = -Wall -Wextra -std=c++20
SRC = src/main.cpp src/utils.cpp src/network.cpp src/icmp.cpp src/timer.cpp src/debug.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = traceroute

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

distclean: clean
	rm -f $(EXEC)
