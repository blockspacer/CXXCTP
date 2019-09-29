#!/usr/bin/env bash
# Copyright (c) 2018 Denis Trofimov (den.a.trofimov@yandex.ru)
# Distributed under the MIT License.
# See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT

set -ev

cmake -E make_directory libunwind-tmp


pushd libunwind-tmp

git clone --depth 1 git://github.com/pathscale/libunwind.git

pushd libunwind

./autogen.sh

./configure CFLAGS="-fPIC" \
  LDFLAGS="-L$PWD/src/.libs"

make

make install prefix=/usr/local

cd ../..

cmake -E remove_directory libunwind-tmp
