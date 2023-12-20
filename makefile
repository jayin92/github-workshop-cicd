# Compile all files in the HW* folder
.PHONY: all HW1 HW2 HW3 HW4 HW5
# Variables
CC = g++

# Flags
CFLAGS = -std=c++11

# Directories and removing the last slash
DIRECTORY = $(shell ls -d */ | sed 's/\/$$//g')

# Targets
all: $(DIRECTORY)

# Using for loop to generate targets	

HW1: HW1/p1.cpp HW1/p2.cpp HW1/p3.cpp
	for i in 1 2 3; do \
		$(CC) $(CFLAGS) HW1/p$$i.cpp -o HW1/p$$i.out; \
		echo "HW1/p$$i.out"; \
	done

HW2: HW2/p1.cpp HW2/p2.cpp HW2/p3.cpp
	for i in 1 2 3; do \
		$(CC) $(CFLAGS) HW2/p$$i.cpp -o HW2/p$$i.out; \
	done

HW3: HW3/p1.cpp HW3/p2.cpp HW3/p3.cpp
	for i in 1 2 3; do \
		$(CC) $(CFLAGS) HW3/p$$i.cpp -o HW3/p$$i.out; \
	done

HW4: HW4/p1.cpp HW4/p2.cpp HW4/p3.cpp
	for i in 1 2 3; do \
		$(CC) $(CFLAGS) HW4/p$$i.cpp -o HW4/p$$i.out; \
	done

HW5: HW5/p1.cpp HW5/p2.cpp HW5/p3.cpp
	for i in 1 2 3; do \
		$(CC) $(CFLAGS) HW5/p$$i.cpp -o HW5/p$$i.out; \
	done

clean:
	rm -rf */*.out

test:
	python3 test.py