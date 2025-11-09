# WSL-setup

setup procedure for *Windows Subsystem for Linux* (WSL). \
The following guide shows how one can install and setup some of the most common applications and utilities needed for numerical analysis in high-energy physics. \
The setup is for a WSL environment, and also suitable for Ubuntu operating systems. Not for Mac OS or other Linux distributions. \
If you are reading this on Github, click on the top right button to show table of contents. \
Most of the operations below required that you have a stable internet connection. \
Most of the application or packages source codes will first be downloaded in the `$HOME/prog_PACKAGE` directory, which can be deleted after installation to free up disk usage. \

Table of contents:
[WSL](WSL-setup.md#setup-wsl),
[Git](WSL-setup.md#setup-git),
[compilers](WSL-setup.md#setup-compilers),
[utilities](WSL-setup.md#setup-utilities),
[Python](WSL-setup.md#setup-python),
[TexLive](WSL-setup.md#setup-texlive),
[Root](WSL-setup.md#setup-root),
[HepMC](WSL-setup.md#setup-hepmc),
[LHAPDF](WSL-setup.md#setup-lhapdf),
[FastJet](WSL-setup.md#setup-fastjet),
[HDF5](WSL-setup.md#setup-hdf5),
[PYTHIA](WSL-setup.md#setup-pythia),
[NLOjet](WSL-setup.md#setup-nlojet),
[MadGraph](WSL-setup.md#setup-madgraph),
[MCFM](WSL-setup.md#setup-mcfm),

> [!NOTE]
> Please respect the installation destination. \
> `/usr` is reserved for packages installed by `apt`. \
> `/usr/local` is where we will install these 3rd-party programmes. \
> `$HOME` is where we keep some of the source codes, examples, and develop our projects. \
> This is just my convention, it will save time configuring system `$PATH`, but some steps will need root access. \

```md
├── home
│   └── $(whoami) [home directory]
│       ├── examples
│       ├── prog_fastjet3
│       ├── prog_hdf5
│       ├── prog_hepmc3
│       ├── prog_lhapdf6
│       ├── prog_nlojet
│       ├── prog_pythia8
│       └── prog_root6
├── mnt
|   ├── c [Windows C drive]
|   └── wslg [WSL distro if running WSL2]
└── usr [packages managed by apt]
    ├── bin
    ├── include
    ├── lib
    ├── share
    └── local [please install here]
        ├── bin [binary files]
        ├── include [header .h files]
        ├── lib [library .so files]
        └── share [usually data files]
```

## before we begin

- Since we are installing most of the programs in `/usr/local`, WSL should automatically recognize the paths to binaries, headers, and libraries.
- If not, append path to binaries with `export PATH=/path/to/binary:$PATH`.
- append path to libraries with `export LD_LIBRARY_PATH=/path/to/libraries:$LD_LIBRARY_PATH`. \
  When new libraries are added to `/usr/lib` or `/usr/local/lib`, usually right after fresh installation, the `ld.so.conf` file is not updated. \
  The system then might not be able to search for the new libraries, so running `sudo ldconfig` might help before exporting to `LD_LIBRARY_PATH`.
- append path to Python libraries with `export PYTHONPATH=/path/to/python/libraries:$PYTHONPATH`.

## setup WSL

0. Show the list of installed WSL distributions in your system by running `wsl --list` or `wslconfig /l` in *Windows Powershell*. \
   Where you can unregister a distribution for a clean installation with `wsl --unregister Ubuntu` or `wslconfig /u Ubuntu`.
1. List the available WSL distributions online by running `wsl --list --online`. \
   We then choose to install the lastest Ubuntu distribution with `wsl --install Ubuntu`. \
   You can find more information [here](https://learn.microsoft.com/en-us/windows/wsl/).
2. Complete the Ubuntu setup by entering a user name and password, then *Powershell* will automatically open the new Ubuntu kernel.
3. We can verify the install by showing the installation version with `hostnamectl`.
4. Update Ubuntu packages with the following `sudo apt update && sudo apt upgrade && sudo apt autoremove`.
5. It is then recommended to code using Visual Studio Code. \
   If you don't have it installed, get the Windows version from [here](https://code.visualstudio.com/Download). \
   Then simply enter `code .` in WSL to open remote connect from Windows to WSL via VScode.
6. To access WSL files in Windows, simply enter `explorer.exe .` in WSL to open a connection. \
   Depending on your WSL version, it will either be in the user directory, or a localhost network.
7. From now on, we will run WSL via VScode using a remote connection. \
   Open VScode in Windows, then click the bottom left blue button, or `ctrl+shift+P` and enter WSL.

## setup Git

0. Git should already be installed in the latest Ubuntu, to verify, run `git --version`.
1. Before we configure git, you should already have a Github account. We then configure using:

   ```bash
   git config --global user.name "username"
   git config --global user.email "user@email"
   ```

2. We want to connect to Git using SSH protocol. Check that you have SSH installed: `ssh -V`. \
   You can check whether you have a public key generated, see if `ls -al $HOME/.ssh` shows a `.pub` file. \
   If not, generate one using: `ssh-keygen -t ed25519 -C "comment"`, where we usually put our email address in the comment. \
   Follow the instructions (just skip the passphrase) will create a public key for you. (ED25519 is better than RSA, so I've heard)
3. We then need to install Github CLI. For Ubuntu, we need to run the following lines found [here](https://github.com/cli/cli/blob/trunk/docs/install_linux.md).

   ```bash
   (type -p wget >/dev/null || (sudo apt update && sudo apt-get install wget -y)) \
    && sudo mkdir -p -m 755 /etc/apt/keyrings \
    && wget -qO- https://cli.github.com/packages/githubcli-archive-keyring.gpg | sudo tee /etc/apt/keyrings/githubcli-archive-keyring.gpg > /dev/null \
    && sudo chmod go+r /etc/apt/keyrings/githubcli-archive-keyring.gpg \
    && echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | sudo tee /etc/apt/sources.list.d/github-cli.list > /dev/null \
    && sudo apt update \
    && sudo apt install gh -y

   ```

   Verify with: `gh --version`
4. Now that we have a Github account, an SSH key, and Github CLI, we need to establish a secure authentication connection with `gh auth login`. \
   Use *GitHub.com*, use *SSH* protocol, use the *.pub* public key generated, and choose login with web browser, enter the code and we are done. \
   We can test the connection by cloning this repository `gh repo clone Raymond-CL/Raymond-CL`. \
   In VScode, source control should automatically detect Git and it will display commit options. Make some minor modification to this repo and try to commit&push (need comment).

## setup compilers

0. It is strongly recommended to install the GNU collection of compilers (GCC) and support free software.
1. Install C, C++ compiler `sudo apt install build-essential`.
2. Install Fortran compiler `sudo apt install gfortran`.
3. Install Assembly compiler `sudo apt install binutils`.

## setup utilities

1. Install some utilities `sudo apt install cmake dpkg-dev htop mpich`. \
   optimize `htop` with `alias htop='htop -d 20 -u $(whoami) -s Command'`.

## setup Python

0. It is worth noting that Ubuntu will not support Python-2 as of version 24.04. \
   This means that you will not be able to install `python` or `python2` through the `apt` package manager. \
   And `python3` is preinstalled in the latest Ubuntu.
1. To get the base Python environment: `sudo apt install python3 python-is-python3`.
2. To get the extra stuff: `sudo apt install python3-dev python3-numpy python3-pip cython3`. \
   Note that `python3-dev` and `cython3` is needed to install `LHAPDF`.
3. For plotting: `sudo apt install python3-matplotlib`.

## setup TexLive

0. Install base `sudo apt install texlive-base`. (getting `texlive-full` might take up a lot of space)
1. Install latex compiler `sudo apt install texlive-latex-base texlive-latex-extra texlive-latex-recommended`.
2. Install latex fonts `sudo apt install texlive-fonts-extra texlive-fonts-recommended`.
3. If you need `revtex4` for publication, install publishers `sudo apt install texlive-publishers`.
4. If you need `simple wick` for Wicks contraction, install science `sudo apt install texlive-science`.
5. There are other external packages like `cm-super`, install only when you need them.

## setup Root

0. Root require some libraries before installation, the core libraries can be install with

   ```bash
   sudo apt install libssl-dev libx11-dev libxext-dev libxft-dev libxpm-dev libtbb-dev libvdt-dev libgif-dev
   ```

   Then there are other optional packages (but we'll install them anyway) that can be install with

   ```bash
   sudo apt install libavahi-compat-libdnssd-dev libblas-dev libcfitsio-dev libedit-dev \
     libfftw3-dev libftgl-dev libgl2ps-dev libglew-dev libglu1-mesa-dev libgraphviz-dev libgsl-dev \
     libjpeg-dev libjpeg-dev libkrb5-dev libldap2-dev liblz4-dev liblzma-dev libmysqlclient-dev \
     libpcre2-dev libpcre3-dev libtiff-dev libtiff-dev libxml2-dev libxxhash-dev libzstd-dev \
     nlohmann-json3-dev postgresql qtwebengine5-dev terminfo
   ```

   These dependencies are a bit different from the official recommendations [here](https://root.cern/install/dependencies/).
1. It is recommended to build from [source](https://root.cern/install/#build-from-source). \

   ```bash
   mkdir $HOME/prog_root6 && cd $HOME/prog_root6
   git clone --branch latest-stable --depth=1 https://github.com/root-project/root.git ./root6_src
   mkdir ./root6_build && cd ./root6_build
   cmake -DCMAKE_INSTALL_PREFIX=/usr/local \
     -Dgnuinstall=ON \
     -Dbuiltin_xrootd=ON \
     ../root6_src
   sudo make -j8 install
   sudo ldconfig
   ```

   There are some libraries that are ignored, such as CUDA-compiler, `cudnn`, PostgreSQL, SQLite, Davix, OCaml, RapidYAML. But they are not necessary. \
   Because the make process might take an hour, I'm using 8 cores to build those binaries. \
   Keep an eye on the memory, the installation takes alot of memory, reduce the parallel core number.
2. We can then verify the installation with `root --version` and show features with `root-config --features`.
3. We now test an example, copy the codes from [this](https://root.cern.ch/root/htmldoc/guides/primer/ROOTPrimer.html#a-more-complete-example) online example to `$HOME/examples/ex-root.C`. Then compile with

   ```bash
   g++ $HOME/examples/ex-root.C -o $HOME/examples/ex-root `root-config --cflags --libs`
   ```

   which should produce a `.pdf` file and can be opened with VScode.

## setup HepMC

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

## setup LHAPDF

0. It is recommended to get the C++ version (LHAPDF6) instead of the Fortran version (LHAPDF5). \
   Note that it does require Python, install Python first.
1. Check [here](https://lhapdf.hepforge.org/downloads/) for the latest release version of LHAPDF6. \
   Download and install with:

   ```bash
   mkdir $HOME/prog_lhapdf6 && cd $HOME/prog_lhapdf6
   wget https://lhapdf.hepforge.org/downloads/?f=LHAPDF-6.5.4.tar.gz -O lhapdf6.tar.gz
   tar -xf lhapdf6.tar.gz
   cd LHAPDF-6.5.4
   sudo ./configure --prefix=/usr/local
   sudo make -j4 install
   sudo ldconfig
   ```

   You can check out the recommended installation guide [here](https://lhapdf.hepforge.org/install.html).
2. We can verify the installation with `lhapdf --version`.
3. We will need to install some PDF sets with `lhapdf` (need permission), create the following script `getpdf.sh`:

   ```shell
   #!/bin/bash
   export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
   export PYTHONPATH=/usr/local/local/lib/python3.12/dist-packages/lhapdf:$PYTHONPATH
   lhapdf install ${1:-CT18NNLO}

   ```

   Because we don't need to download and install using `lhapdf` most of the time, there is no need to configure `ld.so.conf` permanently. \
   run the script with permission `sudo ./getpdf.sh <pdf-set-name>` to download and install the PDF, or leave it empty to get only `CT18NNLO` set. \
   For convenience, move this script to `sudo mv getpdf.sh /usr/local/bin/` so it can be run anyway in the future. \
   Keep in mind that in WSL, the user is not root, but can promote to root with their own password. \
   Thus, this step can also be done by first `sudo su` to enter root, then export the paths and run `lhapdf` to install PDF. \
   When the two paths are set a shell, we can see that `listdir` and `pdfdir` when entered `lhapdf --help` displays the correct default directory `/usr/local/share/LHAPDF`.
4. We now test an example, copy the codes from [this](https://lhapdf.hepforge.org/_2examples_2testpdf_8cc-example.html) online example to `$HOME/examples/ex-lhapdf.cc`. \
   Then compile and run with (takes about half a minute):

   ```bash
   g++ $HOME/examples/ex-lhapdf.cc -o $HOME/examples/ex-lhapdf `lhapdf-config --cflags --libs`
   $HOME/examples/ex-lhapdf CT18NNLO 0
   ```

5. There is a `plotpdfs` python script in the source code directory. \
   If you need to run a test (need to export those paths again), you need to install `python3-matplotlib`, `texlive`, and `cm-super`. \
   Then run it with `./plotpdfs CT18NNLO`, which will produce some `.pdf` plots.

## setup FastJet

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

## setup HDF5

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

## setup PYTHIA

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

## setup NLOJET

0. We need to download and install `cteqpdf` that works hand-in-hand from [here](https://www.desy.de/~znagy/Site/CTEQ_PDF.html). \

   ```bash
   mkdir $HOME/prog_nlojet && cd $HOME/prog_nlojet
   wget http://desy.de/~znagy/hep-programs/cteq-pdf/cteq-pdf-1.0.4.tar.gz -O cteqpdf.tar.gz
   tar -xf cteqpdf.tar.gz
   cd cteq-pdf-1.0.4/
   ./configure --prefix=/usr/local
   sudo make -j4 install
   sudo ldconfig
   ```

1. We then download and install `nlojet++` from [here](https://www.desy.de/~znagy/Site/NLOJet++.html). \

   ```bash
   cd $HOME/prog_nlojet
   wget http://desy.de/~znagy/hep-programs/nlojet++/nlojet++-4.1.3.tar.gz -O nlojet.tar.gz
   tar -xf nlojet.tar.gz
   cd nlojet++-4.1.3/
   ./configure --prefix=/usr/local
   sudo make -j4 install
   sudo ldconfig
   ```

2. we can verify the installation with `nlojet++ --help`.
3. For testing, download the example modules from [here](https://www.desy.de/~znagy/Site/NLOJet++.html).

   ```bash
   cd $HOME/prog_nlojet
   wget http://desy.de/~znagy/hep-programs/nlojet++-modules/modules-4.1.0.tar.gz -O modules.tar.gz
   tar -xf modules.tar.gz
   cd $HOME/prog_nlojet/modules-4.1.0/'pp->jets'/'Twojet for Bruce Mellado'/
   ```

   Compile, run and add results with:

   ```bash
   create-nlojet-user twojet.cc -o twojet -Wx,-D_KT_,-O3,-Wall,-I/usr/local/include/cteq -Wl,-lcteqpdf
   nlojet++ --calculate -n dijet -c full -u ./twojet.la --max-event 1000000
   nlojet++ --add dijet -u ./twojet.la 
   ```

   where the results will be in the `./result/hhc` directory. \
   Note that the accompanied `Makefile` has a similar compile command, but that the `cteqpdf` is assumed to installed in `$HOME/`.

## setup MadGraph

0. MadGraph5 requires `Python3`, `perl` and `gfortran`.
1. Check [here](http://madgraph.phys.ucl.ac.be/) for the latest version of MadGraph5. \
   Download and run with:

   ```bash
   mkdir $HOME/prog_madgraph && cd $HOME/madgraph
   wget https://launchpad.net/mg5amcnlo/lts/2.9.x/+download/MG5_aMC_v2.9.22.tar.gz -O madgraph.tar.gz
   tar -xf madgraph.tar.gz
   cd MG5_aMC_v2_9_22
   ./bin/mg5_amc
   ```

2. For first use, set the path to `LHAPDF6`. \

   ```bash
   MG5_aMC>set lhapdf /usr/bin/lhapdf-config
   ```

   assuming that you have followed the steps to install [LHAPDF6](WSL-setup.md#setup-lhapdf).
3. You can run a tutorial provided in MG5, or run a specific process. \
   We will try a simple proton-proton to dijet event. \

## setup MCFM
