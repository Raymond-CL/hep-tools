# Makefile for compiling main.f90

FC = gfortran
FFLAGS = -O2
TARGET = ex_fortran
SRC = main.f90

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(FC) $(FFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.mod
