# setup HepMC

0. We can install ROOT before installing HEPMC3 to test some `ROOTIO` examples, but not necessary.
1. Check [here](https://hepmc.web.cern.ch/hepmc/index.html) for the latest release version of HEPMC3 and copy the link. \
   Download and install with:

   ```bash
   mkdir $HOME/prog_hepmc3 && cd $HOME/prog_hepmc3
   wget https://hepmc.web.cern.ch/hepmc/releases/HepMC3-3.3.0.tar.gz -O hepmc3.tar.gz
   tar -xf hepmc3.tar.gz
   mkdir ./hepmc3_build && cd ./hepmc3_build
   cmake -DCMAKE_INSTALL_PREFIX=/usr/local \
     -DHEPMC3_ENABLE_ROOTIO:BOOL=OFF \
     -DHEPMC3_ENABLE_PROTOBUFIO:BOOL=OFF \
     -DHEPMC3_ENABLE_TEST:BOOL=ON \
     -DHEPMC3_INSTALL_INTERFACES:BOOL=ON \
     -DHEPMC3_BUILD_STATIC_LIBS:BOOL=OFF \
     -DHEPMC3_BUILD_DOCS:BOOL=ON \
     -DHEPMC3_BUILD_EXAMPLES:BOOL=ON \
     -DHEPMC3_ENABLE_PYTHON:BOOL=ON \
     -DHEPMC3_PYTHON_VERSIONS=3.12 \
     -DHEPMC3_Python_SITEARCH=/usr/local/lib/python3.12/dist-packages \
     ../HepMC3-3.3.0
   sudo make -j8 install
   sudo ldconfig
   ```

   which is a bit different from the procedure given [here](https://gitlab.cern.ch/hepmc/HepMC3), but no matter.
2. We can then verify the installation with `HepMC3-config --version` and show features with `HepMC3-config --features`.
3. We now test an example, copy the codes from [this](https://hepmc.web.cern.ch/hepmc/basic_tree_8cc-example.html) online example to `$HOME/examples/ex-hepmc.cc`. \
   Then compile with

   ```bash
   g++ $HOME/examples/ex-hepmc.cc -o $HOME/examples/ex-hepmc `HepMC3-config --cflags --ldflags`
   ```
