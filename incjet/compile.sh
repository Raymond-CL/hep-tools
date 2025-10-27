rm incjet.exe *.o results.txt
g++ -c ct11pdf.cc
g++ -Wall -Wextra -Wpedantic -O3 -c incjet.cpp
g++ -o incjet.exe ct11pdf.o incjet.o -lgsl