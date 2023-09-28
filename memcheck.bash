#!/bin/bash

set -e

SOURCE=`pwd`

bash build-examples.bash
cd /tmp/build-superlu-examples
valgrind --leak-check=full \
    --show-leak-kinds=all \
    --suppressions=${SOURCE}/valgrind.supp \
    ./example01

