#!/bin/bash

NAME="cpmech/script-install-superlu"
VERSION="latest"

docker run --rm -it $NAME:$VERSION /bin/bash
