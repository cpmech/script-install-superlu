#!/bin/bash

set -e

BDIR=/tmp/build-superlu-examples
mkdir -p $BDIR

HERE=`pwd`
SOURCE="${HERE}/examples"

cd $BDIR
cmake -S $SOURCE
make

./example01
