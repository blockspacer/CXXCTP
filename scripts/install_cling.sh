#!/bin/bash

# BEFORE RUN:
# sudo apt-get update && sudo apt-get upgrade
# sudo apt-get install clang libstdc++6
# sudo update-alternatives --config c++
# sudo update-alternatives --config cc
# ldconfig

set +x
set -e

# see https://root.cern.ch/cling-build-instructions
# see https://github.com/alandefreitas/find_package_online/blob/master/Modules/ExternalProjectCling.cmake

# mkdir from scripts/
mkdir -p ../cling-build
cd ../cling-build

git clone http://root.cern.ch/git/llvm.git src
cd src
git checkout cling-patches
cd tools
git clone http://root.cern.ch/git/cling.git
#cd cling
#git checkout master
#cd ..
git clone http://root.cern.ch/git/clang.git
cd clang
git checkout cling-patches
cd ../../..

mkdir build
cd build

# add parallel build support
# https://stackoverflow.com/questions/601970/how-do-i-utilise-all-the-cores-for-nmake
# set CL=/MP

#export CC=clang-7
#export CXX=clang++-7
export CC=gcc
export CXX=g++

#TODO -Dcxx11=ON --with-cxx11

# NOTE: on MAC set -stdlib=libstdc++
# -DCMAKE_CXX_FLAGS="-stdlib=libc++" -DCMAKE_C_COMPILER=clang-7 -DCMAKE_CXX_COMPILER=clang++-7 -DCMAKE_EXE_LINKER_FLAGS="-stdlib=libc++ -lc++abi"
#cmake -DCMAKE_INSTALL_PREFIX=../release -DCMAKE_BUILD_TYPE=Release ../src -DCMAKE_CXX_FLAGS="-stdlib=libc++" -DCMAKE_EXE_LINKER_FLAGS="-stdlib=libc++ -lc++abi"
# NOTE: use -DLLVM_BUILD_TOOLS=Off, see https://github.com/root-project/cling/issues/297
cmake -DCMAKE_CXX_STANDARD=17 -DLLVM_BUILD_TOOLS=Off -DCMAKE_INSTALL_PREFIX=../release -DCMAKE_BUILD_TYPE=Release ../src

cmake --build . -- -j6

# no install
# cmake --build . --target install

# NOTE: if you get error
# /home/denis/workspace/cling-cmake/cling-build/src/include/llvm/ExecutionEngine/Orc/OrcRemoteTargetClient.h:722:26: error: could not convert ‘((llvm::orc::remote::OrcRemoteTargetClient<ChannelT>*)this)->callB<llvm::orc::remote::OrcRemoteTargetRPCAPI::ReadMem>(Src, Size)’ from ‘Expected<vector<unsigned char,allocator<unsigned char>>>’ to ‘Expected<vector<char,allocator<char>>>’
# return callB<ReadMem>(Src, Size);
# than apply patch (replace char with uint8_t) https://aur.archlinux.org/cgit/aur.git/tree/gcc-build-fix.patch?h=llvm50

