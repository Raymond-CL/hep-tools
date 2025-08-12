# setup Python

0. It is worth noting that Ubuntu will not support Python-2 as of version 24.04. \
   This means that you will not be able to install `python` or `python2` through the `apt` package manager. \
   And `python3` is preinstalled in the latest Ubuntu.
1. To get the base Python environment: `sudo apt install python3 python-is-python3`.
2. To get the extra stuff: `sudo apt install python3-dev python3-numpy python3-pip cython3`. \
   Note that `python3-dev` and `cython3` is needed to install `LHAPDF`.
3. For plotting: `sudo apt install python3-matplotlib`.
