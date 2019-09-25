# How to build
generate files by CXXCTP_tool, than run:

```
export CC=gcc
export CXX=g++
rm -rf build
mkdir build
cd build
cmake -DENABLE_CLING=TRUE -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . -- -j6
./CXXCTP_example
```
