#!/bin/bash
# Copyright (c) 2019 Denis Trofimov (den.a.trofimov@yandex.ru)
# Distributed under the MIT License.
# See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT

set -ev

#version=3.13.3

# no error if existing, make parent directories as needed
mkdir -vp ~/temp

# cd ~/temp
pushd ~/temp

# https://ftp.osuosl.org/pub/blfs/conglomeration/cmake/cmake-$version.tar.gz

#wget https://github.com/Kitware/CMake/releases/download/v$version/cmake-$version-Linux-x86_64.sh
#
#rm -rf /opt/cmake || true
#mkdir /opt/cmake
#
#sh cmake-$version-Linux-x86_64.sh --prefix=/opt/cmake --skip-license
#
#rm /usr/local/bin/cmake || true
#ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake

# NOTE: github may be down, so prefer cmake.org/files
# see https://anglehit.com/how-to-install-the-latest-version-of-cmake-via-command-line/
version=3.15
build=3
mkdir ~/temp || true
cd ~/temp
wget --no-check-certificate https://cmake.org/files/v$version/cmake-$version.$build.tar.gz
tar -xzvf cmake-$version.$build.tar.gz
cd cmake-$version.$build/
./bootstrap
make -j4
make install

cmake --version
