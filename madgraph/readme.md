# setup MadGraph

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