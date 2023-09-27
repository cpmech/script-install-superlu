FROM ubuntu:22.04

# disable tzdata questions
ENV DEBIAN_FRONTEND=noninteractive

# use bash
SHELL ["/bin/bash", "-c"]

# install apt-utils
RUN apt-get update -y && \
  apt-get install -y apt-utils 2> >( grep -v 'debconf: delaying package configuration, since apt-utils is not installed' >&2 ) \
  && apt-get clean && rm -rf /var/lib/apt/lists/*

# essential tools
RUN apt-get update -y && apt-get install -y --no-install-recommends \
  ca-certificates \
  netbase \
  curl \
  gdb \
  git \
  gnupg \
  wget \
  && apt-get clean && rm -rf /var/lib/apt/lists/*

# copy files
COPY . /tmp/script-install-superlu
WORKDIR /tmp/script-install-superlu

# install deps
RUN bash install-deps.bash

# install SuperLU
RUN bash install-superlu.bash

# configure image for remote development
RUN bash scripts/common-debian.sh
