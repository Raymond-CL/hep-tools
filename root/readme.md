# setup Root

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
