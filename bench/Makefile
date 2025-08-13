FC = gfortran
FFLAGS = -O3
Fsrc = PIn_fort.f90
Fexe = PIn_fort.exe

CC = g++
CFLAGS = -O3
Csrc = PIn_cpp.cc
Cexe = PIn_cpp.exe

HC = ghc
HFLAGS = -O2 -v0
Hsrc = PIn_hask.hs
Hexe = PIn_hask.exe

RC = rustc
RFLAGS = -C opt-level=3
Rsrc = PIn_rust.rs
Rexe = PIn_rust.exe

PC = cython3
PFLAGS = --embed --3str
Psrc = PIn_py.py
PCC = gcc
PCFLAGS = $(shell python3-config --cflags --ldflags) -lpython3.12 -lpthread -lutil
PCsrc = PIn_py.c
Pexe = PIn_py.exe

fort: $(Fsrc)
	$(FC) $(Fsrc) -o $(Fexe) $(FFLAGS)

cpp: $(Csrc)
	$(CC) $(Csrc) -o $(Cexe) $(CFLAGS)

hask: $(Hsrc)
	$(HC) $(Hsrc) -o $(Hexe) $(HFLAGS)

rust: $(Rsrc)
	$(RC) $(Rsrc) -o $(Rexe) $(RFLAGS)

python: $(Psrc)
	$(PC) $(Psrc) -o $(PCsrc) $(PFLAGS)
	@$(PCC) $(PCsrc) -o $(Pexe) $(PCFLAGS)

run: fort cpp hask rust python
	@./$(Fexe) && ./$(Cexe) && ./$(Hexe)  && ./$(Rexe) && ./$(Pexe)

clean:
	rm -rf $(Fexe) $(Cexe) $(Hexe) $(Rexe) $(PCsrc) $(Pexe) *.o *.hi