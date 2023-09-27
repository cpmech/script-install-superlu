#!/bin/bash

set -e

# fake sudo function to be used by docker build
sudo () {
  [[ $EUID = 0 ]] || set -- command sudo "$@"
  "$@"
}

# options
PREFIX="/usr/local"
INCDIR=$PREFIX/include/superlu
LIBDIR=$PREFIX/lib/superlu

# download the source code
cd /tmp
if ! [ -d "superlu" ]; then
    git clone https://github.com/xiaoyeli/superlu.git
fi
cd superlu

# function to compile and copy results to local directories
action () {
    local dir=$1
    cd $dir
    make local
    make install
    cd ..
}

# compile and copy results to local directories
action SuiteSparse_config
action AMD
action CAMD
action CCOLAMD
action COLAMD
action CHOLMOD
action SuperLU

# copy include files
sudo mkdir -p $INCDIR/
sudo cp -av include/*.h $INCDIR/

# copy libray files
sudo mkdir -p $LIBDIR/
sudo cp -av lib/* /usr/local/lib/superlu

# update ldconfig
echo "${LIBDIR}" | sudo tee /etc/ld.so.conf.d/superlu.conf >/dev/null
sudo ldconfig
