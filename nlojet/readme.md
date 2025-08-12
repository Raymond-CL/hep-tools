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
