# setup HDF5

0. HDF5 might require `c++` and `gfortran`.
1. Check [here](https://www.hdfgroup.org/download-hdf5/source-code/) for the latest version of HDF5. \
   Download and install with:

   ```bash
   mkdir $HOME/prog_hdf5 && cd $HOME/prog_hdf5
   wget https://support.hdfgroup.org/releases/hdf5/v1_14/v1_14_5/downloads/hdf5-1.14.5.tar.gz -O hdf5.tar.gz
   tar -xf hdf5.tar.gz
   cd hdf5-1.14.5/
   ./configure --prefix=/usr/local  --enable-fortran  --enable-cxx
   sudo make -j4 install
   sudo ldconfig
   ```

   There are some features that are ignored, we don't really need them.
2. We can then verify the installation with `h5dump --version` and show features with `h5cc -showconfig`.
