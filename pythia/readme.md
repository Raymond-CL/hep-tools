# setup PYTHIA

0. It is recommended to install the above packages before installing PYTHIA8. \
   Which are `FastJet3`, `HepMC3`, `LHAPDF6`, `Root6`, `Python3`, `OpenMP`, `mpich`, `HDF5`.
1. Check [here](https://pythia.org/releases/) for the latest version of PYTHIA8. \
   Download and install with

   ```bash
   mkdir $HOME/prog_pythia8 && cd $HOME/prog_pythia8
   wget https://pythia.org/download/pythia83/pythia8312.tar -O pythia8.tar
   tar -xf pythia8.tar
   cd pythia8312/
   ./configure  --prefix=/usr/local \
     --with-fastjet3 --with-hepmc3 --with-lhapdf6 --with-hdf5 \
     --with-python --with-python-include=/usr/include/python3.12/ \
     --with-mpich --with-mpich-include=/usr/lib/x86_64-linux-gnu/mpich/include/ \
     --with-root --with-gzip --with-openmp --cxx=g++
   sudo make -j4 install
   sudo ldconfig
   ```

   If the previous packages are installed correctly, the configuration process should not give error. \
   There are some packages that are ignored, such as PowhegBox and MagGraph5. But they are not necessary, for now. \
   PYTHIA needs the path to `Python.h` and `mpich.h`. If you don't know where it is, find it in `/usr` with (because it is installed with `apt`):

   ```bash
   find . \( -name "Python.h" -o -name "mpi.h" \)
   ```

2. We can then verify the installation with `pythia8-config --version`.
3. You can test any of the sample programs found [here](https://pythia.org/latest-manual/SampleMainPrograms.html), \
   or within the source code directory `$HOME/prog_pythia8/pythia8312/examples/`. \
   To test correct linking to a certain package, search for the package name (e.g. fastjet) in the online samples, and look for the corresponding program number. \
   To test the `FastJet3` package, run:

   ```bash
   make main212 && ./main212 > main212.log
   ```

   To test the `HepMC3` package, run:

   ```bash
   make main131 && ./main131 > main131.log
   ```

   To test the `LHAPDF6` package, run:

   ```bash
   sudo getpdf.sh NNPDF31_nnlo_as_0118_luxqed
   make main201 && ./main201 > main201.log
   ```

   To test the `Python3` interface, run:

   ```bash
   python main291.py > main291.log
   ```

   To test the `Root` package, run (produces `fig142.pdf`):

   ```bash
   make main142 && ./main142 > main142.log
   ```

   To test the `openmp` package, run:

   ```bash
   make main402 && ./main402 > main402.log
   ```