# setup LHAPDF

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
