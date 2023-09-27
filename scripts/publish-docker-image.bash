#!/bin/bash

NAME="cpmech/script-install-superlu"
VERSION="latest"

docker logout
docker login
docker push $NAME:$VERSION
