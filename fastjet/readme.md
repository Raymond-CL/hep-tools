# setup FastJet

0. Note that it does require Python, install Python first.
1. Check [here](https://fastjet.fr/all-releases.html) for the latest release version of FastJet3. \
   Download and install with:

   ```bash
   mkdir $HOME/prog_fastjet3 && cd $HOME/prog_fastjet3
   wget https://fastjet.fr/repo/fastjet-3.4.3.tar.gz -O fastjet3.tar.gz
   tar -xf fastjet3.tar.gz
   cd fastjet-3.4.3/
   sudo ./configure --prefix=/usr/local --enable-allplugins --enable-pyext
   sudo make -j4 install
   sudo ldconfig
   ```

   It is not necessary to include the last 2 flags, which are some uncommon jet algorithms used by D0, ATLAS and CMS. But it doesn't hurt to install all. \
   You can check out the recommended installation guide [here](https://fastjet.fr/quickstart.html).
2. We can then verify the installation with `fastjet-config --version` and show plugins with `fastjet-config --list-plugins`.
3. We now test an example, copy the codes from [this](https://fastjet.fr/quickstart.html) online example to `$HOME/examples/ex-fastjet.cc`. \
   Then compile with:

   ```bash
   g++ $HOME/examples/ex-fastjet.cc -o $HOME/examples/ex-fastjet `fastjet-config --cxxflags --libs`
   ```
