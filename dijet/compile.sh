g++ -c ct11pdf.cc
g++ -Wall -Wextra -Wpedantic -O3 -c main.cpp
g++ -fopenmp -o incjet ct11pdf.o main.o -lgsl