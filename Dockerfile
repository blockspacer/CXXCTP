# NOTE: you can use docker_pull.py if docker hub blocked under corp proxy
# See:
# + https://gist.github.com/blockspacer/893b31e61c88f6899ffd0813111b3e41#file-docker-conf-proxy-rxt
# + https://stackoverflow.com/a/53551452
# + https://medium.com/@saniaky/configure-docker-to-use-a-host-proxy-e88bd988c0aa
# + https://stackoverflow.com/a/28093517
# + https://stackoverflow.com/a/38901128
# + https://dev.to/shriharshmishra/behind-the-corporate-proxy-2jd8
# + https://stackoverflow.com/a/38901128
FROM        ubuntu:18.04

# Give docker the rights to access X-server
# sudo -E xhost +local:docker

# build Dockerfile
# sudo -E docker build --no-cache -t cpp-docker-cxxctp .
#
# OR under proxy:
# sudo -E docker build  \
#  --build-arg http_proxy=http://172.17.0.1:3128 \
#  --build-arg https_proxy=http://172.17.0.1:3128 \
#  --build-arg no_proxy=localhost,127.0.0.*,10.*,192.168.*,*.somecorp.ru,*.mycorp.ru \
#  --build-arg HTTP_PROXY=http://172.17.0.1:3128 \
#  --build-arg HTTPS_PROXY=http://172.17.0.1:3128 \
#  --build-arg NO_PROXY=localhost,127.0.0.*,10.*,192.168.*,*.somecorp.ru,*.mycorp.ru \
#  --no-cache -t cpp-docker-cxxctp .
# OR
# --network=host. This will make the build command use the network settings of the host.

# Now let’s check if our image has been created.
# sudo -E docker images

# Run a terminal in container
# sudo -E docker run --rm -v "$PWD":/home/u/cxxctp -w /home/u/cxxctp  -it  -e DISPLAY         -v /tmp/.X11-unix:/tmp/.X11-unix  cpp-docker-cxxctp

# NOTE: you can set up proxy when running the container
# docker container run -e http_proxy nginx

# The usual way of running this is as follows:
# docker run -v `pwd`:`pwd` -w `pwd` -u `id -u`:`id -g` <tagged-container-name> <app> <options>

# Run in container without leaving host terminal
# sudo -E docker run -v "$PWD":/home/u/cxxctp -w /home/u/cxxctp cpp-docker-cxxctp CXTPL_tool -version --version

# An example of how to build (with Makefile generated from cmake) inside the container
# Mounts $PWD to /home/u/cxxctp and runs command
# mkdir build
# sudo -E docker run --rm -v "$PWD":/home/u/cxxctp -w /home/u/cxxctp/build cpp-docker-cxxctp cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..

# Run resulting app in host OS:
# ./build/<app>

# https://askubuntu.com/a/1013396
# RUN export DEBIAN_FRONTEND=noninteractive
# Set it via ARG as this only is available during build:
ARG DEBIAN_FRONTEND=noninteractive

ENV LC_ALL C.UTF-8
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US:en
#ENV TERM screen

ENV PATH=/usr/lib/clang/6.0/include:/usr/lib/llvm-6.0/include/:$PATH

ARG APT="apt-get -qq --no-install-recommends"

# docker build --build-arg NO_SSL="False" APT="apt-get -qq --no-install-recommends" .
ARG NO_SSL="True"

# https://www.peterbe.com/plog/set-ex
RUN set -ex

# NO_SSL usefull under proxy, you can disable it with --build-arg NO_SSL="False"
# Also change http-proxy.conf and ~/.docker/config.json like so https://medium.com/@saniaky/configure-docker-to-use-a-host-proxy-e88bd988c0aa
#
# read https://docs.docker.com/network/proxy/
#
# NOTE:
#
# (!!!) Turns off SSL verification on the whole system (!!!)
#
RUN if [ "$NO_SSL" = "True" ]; then \
    echo 'NODE_TLS_REJECT_UNAUTHORIZED=0' >> ~/.bashrc \
    && \
    echo "strict-ssl=false" >> ~/.npmrc \
    && \
    echo "registry=http://registry.npmjs.org/" > ~/.npmrc \
    && \
    echo ':ssl_verify_mode: 0' >> ~/.gemrc \
    && \
    echo "sslverify=false" >> /etc/yum.conf \
    && \
    echo "sslverify=false" >> ~/.yum.conf \
    && \
    echo "APT{Ignore {\"gpg-pubkey\"; }};" >> /etc/apt.conf \
    && \
    echo "Acquire::http::Verify-Peer \"false\";" >> /etc/apt.conf \
    && \
    echo "Acquire::https::Verify-Peer \"false\";" >> /etc/apt.conf \
    && \
    echo "APT{Ignore {\"gpg-pubkey\"; }};" >> ~/.apt.conf \
    && \
    echo "Acquire::http::Verify-Peer \"false\";" >> ~/.apt.conf \
    && \
    echo "Acquire::https::Verify-Peer \"false\";" >> ~/.apt.conf \
    && \
    echo "Acquire::http::Verify-Peer \"false\";" >> /etc/apt/apt.conf.d/00proxy \
    && \
    echo "Acquire::https::Verify-Peer \"false\";" >> /etc/apt/apt.conf.d/00proxy \
    && \
    echo "check-certificate = off" >> /etc/.wgetrc \
    && \
    echo "check-certificate = off" >> ~/.wgetrc \
    && \
    echo "insecure" >> /etc/.curlrc \
    && \
    echo "insecure" >> ~/.curlrc \
    ; \
  fi

RUN $APT update

RUN $APT install -y --reinstall software-properties-common

RUN $APT install -y gnupg2 wget

RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key --no-check-certificate | apt-key add -

# See `How to add an Ubuntu apt-get key from behind a firewall`
# + http://redcrackle.com/blog/how-add-ubuntu-apt-get-key-behind-firewall

# NOTE: need to set at least empty http-proxy

RUN apt-key adv --keyserver-options http-proxy=$http_proxy --keyserver keyserver.ubuntu.com --recv-keys 1E9377A2BA9EF27F

RUN apt-key adv --keyserver-options http-proxy=$http_proxy --keyserver keyserver.ubuntu.com --recv-keys 94558F59

RUN apt-key adv --keyserver-options http-proxy=$http_proxy --keyserver keyserver.ubuntu.com --recv-keys 2EA8F35793D8809A

# RUN apt-key adv --keyserver-options http-proxy=$http_proxy --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 0xB01FA116

RUN apt-key adv --keyserver-options http-proxy=$http_proxy --keyserver hkp://keyserver.ubuntu.com:80 --recv 7F0CEB10

RUN apt-key adv --keyserver-options http-proxy=$http_proxy --keyserver keyserver.ubuntu.com --recv-keys 16126D3A3E5C1192

RUN apt-key adv --keyserver-options http-proxy=$http_proxy --keyserver keyserver.ubuntu.com --recv-keys 4C1CBC1B69B0E2F4

RUN apt-key adv --keyserver-options http-proxy=$http_proxy --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 36A1D7869245C8950F966E92D8576A8BA88D21E9

RUN apt-key adv --keyserver-options http-proxy=$http_proxy --keyserver keyserver.ubuntu.com --recv-keys 1397BC53640DB551

RUN apt-key adv --keyserver-options http-proxy=$http_proxy --keyserver keyserver.ubuntu.com --recv-keys 40976EAF437D05B5

# https://launchpad.net/~boost-latest/+archive/ubuntu/ppa
# RUN apt-key adv --keyserver-options http-proxy=$http_proxy --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys D9CFF117BD794DCE7C080E310CFB84AE029DB5C7
#RUN apt-key adv --keyserver-options http-proxy=$http_proxy --keyserver keyserver.ubuntu.com --recv-keys D9CFF117BD794DCE7C080E310CFB84AE029DB5C7

# Now to verify that apt-key worked, run this command (from this answer):
# apt-key list

# Newer versions of apt also support the following:
# apt-key adv --fetch-keys http://deb.opera.com/archive.key

# apt-key adv --list-public-keys --with-fingerprint --with-colons

# RUN curl -sSL 'http://llvm.org/apt/llvm-snapshot.gpg.key' | apt-key add --keyserver-options http-proxy=$http_proxy -
RUN apt-key adv --keyserver-options http-proxy=$http_proxy --fetch-keys http://llvm.org/apt/llvm-snapshot.gpg.key

RUN apt-add-repository -y "deb http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu $(lsb_release -sc) main"

RUN apt-add-repository -y "deb http://apt.llvm.org/xenial/ llvm-toolchain-xenial-5.0 main"

RUN apt-add-repository -y "deb http://apt.llvm.org/xenial/ llvm-toolchain-xenial-6.0 main"

RUN apt-add-repository -y "deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic-7 main"

RUN apt-add-repository -y "deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic-8 main"

#RUN apt-add-repository -y "deb http://archive.ubuntu.com/ubuntu $(lsb_release -sc) universe"

#RUN echo "deb http://ppa.launchpad.net/boost-latest/ppa/ubuntu $(lsb_release -sc) main" >> /etc/apt/sources.list

#RUN echo "deb-src http://ppa.launchpad.net/boost-latest/ppa/ubuntu $(lsb_release -sc) main" >> /etc/apt/sources.list

#RUN         $APT update

# RUN apt-add-repository -y "deb http://ppa.launchpad.net/boost-latest/ppa/ubuntu $(lsb_release -sc) main"
#RUN add-apt-repository -y "ppa:boost-latest/ppa"

#RUN apt-add-repository -y "ppa:ubuntu-toolchain-r/test"
#RUN apt-add-repository -y "deb http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu $(lsb_release -sc) main"

# update and install dependencies
RUN         $APT update

RUN         $APT install -y \
                    ca-certificates \
                    software-properties-common \
                    git \
                    wget \
                    locales

RUN if [ "$NO_SSL" = "True" ]; then \
    git config --global http.sslVerify false\
    && \
    git config --global http.postBuffer 1048576000 \
    && \
    export GIT_SSL_NO_VERIFY=true \
    ; \
  fi

RUN         $APT update

RUN         $APT install -y \
                    make \
                    git \
                    curl \
                    vim \
                    vim-gnome

RUN         $APT install -y cmake

RUN         $APT install -y \
                    build-essential \
                    clang-6.0 python-lldb-6.0 lldb-6.0 lld-6.0 llvm-6.0-dev \
                    clang-tools-6.0 libclang-common-6.0-dev libclang-6.0-dev \
                    libc++abi-dev libc++-dev libclang-common-6.0-dev libclang1-6.0 libclang-6.0-dev \
                    libstdc++6 libstdc++-6-dev

RUN         $APT install -y libboost-dev \
                    openmpi-bin \
                    openmpi-common \
                    libopenmpi-dev \
                    libevent-dev \
                    libdouble-conversion-dev \
                    libgoogle-glog-dev \
                    libgflags-dev \
                    libiberty-dev \
                    liblz4-dev \
                    liblzma-dev \
                    libsnappy-dev \
                    zlib1g-dev \
                    binutils-dev \
                    libjemalloc-dev \
                    libssl-dev \
                    pkg-config \
                    autoconf-archive \
                    bison \
                    flex \
                    gperf \
                    joe \
                    libboost-all-dev \
                    libcap-dev \
                    libkrb5-dev \
                    libpcre3-dev \
                    libpthread-stubs0-dev \
                    libnuma-dev \
                    libsasl2-dev \
                    libsqlite3-dev \
                    libtool \
                    netcat-openbsd \
                    sudo \
                    unzip \
                    gcc \
                    g++ \
                    gnutls-bin \
                    openssl \
                    libgtest-dev \
                    fakeroot \
                    dpkg-dev \
                    libcurl4-openssl-dev

#                    libssl1.0-dev # https://serverfault.com/a/929084
#                    build-dep \ # Unable to locate package build-dep

RUN         $APT install -y mesa-utils \
                            libglu1-mesa-dev \
                            dbus-x11 \
                            libx11-dev \
                            xorg-dev \
                            libssl-dev \
                            python3 \
                            python3-pip \
                            python3-dev \
                            python3-setuptools

#                            python \
#                            python-dev \
#                            python-pip \
#                            python-setuptools

# RUN mkdir ~/.pip && echo "[global]\n#index-urls:  https://pypi.douban.com, https://mirrors.aliyun.com/pypi,\ncheckout https://www.pypi-mirrors.org/ for more available mirror servers\nindex-url = https://pypi.douban.com/simple\ntrusted-host = pypi.douban.com" > ~/.pip/pip.conf

# pip install pip setuptools --index-url=https://pypi.python.org/simple/ --trusted-host pypi.org --trusted-host pypi.python.org --trusted-host files.pythonhosted.org

# RUN mkdir -p $HOME/.config/pip/
# # https://stackoverflow.com/a/54397762
# RUN echo $'
# [global]
# timeout = 60
# index-url = https://pypi.python.org/simple/
# extra-index-url = http://151.101.112.223/root/pypi/+simple/
#                 http://pypi.python.org/simple
# trusted-host = download.zope.org
#             pypi.python.org
#             secondary.extra.host
#             https://pypi.org
#             pypi.org
#             pypi.org:443
#             151.101.128.223
#             151.101.128.223:443
#             https://pypi.python.org
#             pypi.python.org
#             pypi.python.org:443
#             151.101.112.223
#             151.101.112.223:443
#             https://files.pythonhosted.org
#             files.pythonhosted.org
#             files.pythonhosted.org:443
#             151.101.113.63
#             151.101.113.63:443
# ' >> $HOME/.config/pip/pip.conf

RUN mkdir -p $HOME/.pip/
# TODO https://github.com/moby/moby/issues/1799#issuecomment-489119778
RUN echo "[global]" >> $HOME/.pip/pip.conf
RUN echo "timeout = 60" >> $HOME/.pip/pip.conf
RUN echo "index-url = https://pypi.python.org/simple" >> $HOME/.pip/pip.conf
RUN echo "extra-index-url = http://151.101.112.223/root/pypi/+simple" >> $HOME/.pip/pip.conf
RUN echo "                  http://pypi.python.org/simple" >> $HOME/.pip/pip.conf
RUN echo "trusted-host = download.zope.org" >> $HOME/.pip/pip.conf
RUN echo "               pypi.python.org" >> $HOME/.pip/pip.conf
RUN echo "               secondary.extra.host" >> $HOME/.pip/pip.conf
RUN echo "               https://pypi.org" >> $HOME/.pip/pip.conf
RUN echo "               pypi.org" >> $HOME/.pip/pip.conf
RUN echo "               pypi.org:443" >> $HOME/.pip/pip.conf
RUN echo "               151.101.128.223" >> $HOME/.pip/pip.conf
RUN echo "               151.101.128.223:443" >> $HOME/.pip/pip.conf
RUN echo "               https://pypi.python.org" >> $HOME/.pip/pip.conf
RUN echo "               pypi.python.org" >> $HOME/.pip/pip.conf
RUN echo "               pypi.python.org:443" >> $HOME/.pip/pip.conf
RUN echo "               151.101.112.223" >> $HOME/.pip/pip.conf
RUN echo "               151.101.112.223:443" >> $HOME/.pip/pip.conf
RUN echo "               https://files.pythonhosted.org" >> $HOME/.pip/pip.conf
RUN echo "               files.pythonhosted.org" >> $HOME/.pip/pip.conf
RUN echo "               files.pythonhosted.org:443" >> $HOME/.pip/pip.conf
RUN echo "               151.101.113.63" >> $HOME/.pip/pip.conf
RUN echo "               151.101.113.63:443" >> $HOME/.pip/pip.conf

# RUN cat $HOME/.pip/pip.conf

WORKDIR /opt
#RUN git clone https://github.com/conan-io/conan.git
#WORKDIR /opt/conan
RUN pip3 install --index-url=https://pypi.python.org/simple/ --trusted-host pypi.org --trusted-host pypi.python.org --trusted-host files.pythonhosted.org conan
#RUN pip3 install --index-url=https://pypi.python.org/simple/ --trusted-host pypi.org --trusted-host pypi.python.org --trusted-host files.pythonhosted.org -r conans/requirements.txt
#WORKDIR /opt

RUN pip3 install --index-url=https://pypi.python.org/simple/ --trusted-host pypi.org --trusted-host pypi.python.org --trusted-host files.pythonhosted.org conan_package_tools

WORKDIR /opt

# libunwind
# WORKDIR /opt
# RUN git clone --depth=1 --recurse-submodules --single-branch --branch=master git://github.com/pathscale/libunwind.git
# WORKDIR /opt/libunwind
# RUN ./autogen.sh
# RUN ./configure CFLAGS="-fPIC" LDFLAGS="-L$PWD/src/.libs"
# RUN make -j4
# RUN make install prefix=/usr/local
# RUN rm -rf /opt/libunwind

# g3log
# WORKDIR /opt
# RUN git clone --depth=1 --recurse-submodules --single-branch --branch=master https://github.com/KjellKod/g3log.git
# WORKDIR /opt/g3log
# RUN cmake . -DBUILD_STATIC_LIBS=ON -DG3_SHARED_LIB=OFF -DBUILD_SHARED_LIBS=OFF -DBUILD_STATIC=ON # -DCPACK_PACKAGING_INSTALL_PREFIX=. -DCMAKE_BUILD_TYPE=Release
# RUN cmake --build . --config Release --clean-first -- -j4
# RUN make install
# RUN rm -rf /opt/g3log

# gflags
# WORKDIR /opt
# RUN cmake -E make_directory build-gflags
# WORKDIR /opt/build-gflags
# RUN wget https://github.com/gflags/gflags/archive/v2.2.2.tar.gz && \
#     tar zxf v2.2.2.tar.gz && \
#     rm -f v2.2.2.tar.gz && \
#     cd gflags-2.2.2 && \
#     cmake -DGFLAGS_BUILD_SHARED_LIBS=OFF -DGFLAGS_BUILD_STATIC_LIBS=ON -DCMAKE_POSITION_INDEPENDENT_CODE=ON . && \
#     make && \
#     make install
# RUN rm -rf /opt/build-gflags

# gtest
# WORKDIR /opt
# RUN cmake -E make_directory build-gtest
# WORKDIR /opt/build-gtest
# RUN wget https://github.com/google/googletest/archive/release-1.8.0.tar.gz && \
#     tar zxf release-1.8.0.tar.gz && \
#     rm -f release-1.8.0.tar.gz && \
#     cd googletest-release-1.8.0 && \
#     cmake . && \
#     make && \
#     make install
# RUN rm -rf /opt/build-gtest

WORKDIR /opt

COPY . /opt/CXXCTP
# RUN git clone --depth=1 --recurse-submodules --single-branch --branch=master https://github.com/blockspacer/CXXCTP.git

WORKDIR /opt/CXXCTP

# openssl: relocation error: openssl: symbol EVP_mdc2 version OPENSSL_1_1_0 not defined in file libcrypto.so.1.1 with link time reference
# https://stackoverflow.com/a/51565653/1373413
# RUN cmake -E make_directory /opt/openssl
# WORKDIR /opt/openssl
# RUN wget https://www.openssl.org/source/old/1.1.0/openssl-1.1.0g.tar.gz --no-check-certificate
# RUN tar xzvf openssl-1.1.0g.tar.gz
# WORKDIR /opt/openssl/openssl-1.1.0g
# RUN ./config
# RUN make
# RUN make install

# NOTE: create folder `.ca-certificates` with custom certs
# switch to root
#USER root
COPY ./.ca-certificates/* /usr/local/share/ca-certificates/
RUN update-ca-certificates --fresh
# switch back to custom user
#USER docker

# TODO https://stackoverflow.com/a/40465312
# git submodule deinit --all -f
RUN git submodule sync --recursive || true
RUN git fetch --recurse-submodules || true
RUN git submodule update --init --recursive --depth 5 || true
RUN git submodule update --force --recursive --init --remote || true
RUN ls -artl /opt/CXXCTP/
RUN ls -artl /opt/CXXCTP/scripts
RUN ls -artl /opt/CXXCTP/submodules

# cling
# NOTE: run from scripts folder!
WORKDIR /opt/CXXCTP/scripts
RUN ["chmod", "+x", "/opt/CXXCTP/scripts/install_cling.sh"]
WORKDIR /opt/CXXCTP

# CMake
RUN ["chmod", "+x", "/opt/CXXCTP/scripts/install_cmake.sh"]

# NOTE: need libunwind with -fPIC (POSITION_INDEPENDENT_CODE) support
RUN ["chmod", "+x", "/opt/CXXCTP/scripts/install_libunwind.sh"]

WORKDIR /opt/CXXCTP/submodules/CXTPL

# g3log
RUN ["chmod", "+x", "/opt/CXXCTP/submodules/CXTPL/scripts/install_g3log.sh"]

# gtest
RUN ["chmod", "+x", "/opt/CXXCTP/submodules/CXTPL/scripts/install_gtest.sh"]

# gflags
RUN ["chmod", "+x", "/opt/CXXCTP/submodules/CXTPL/scripts/install_gflags.sh"]

RUN export CC=gcc
RUN export CXX=g++
# create build dir
RUN cmake -E make_directory build
# configure
RUN cmake -E chdir build cmake -E time cmake -DBUILD_EXAMPLES=FALSE -DENABLE_CLING=FALSE -DCMAKE_BUILD_TYPE=Debug ..
# build
RUN cmake -E chdir build cmake -E time cmake --build . -- -j6
# install lib and CXTPL_tool
RUN cmake -E chdir build make install

WORKDIR /opt/CXXCTP

RUN export CC=clang
RUN export CXX=clang++
RUN cmake -E make_directory build
RUN cmake -E make_directory resources/cxtpl/generated
RUN cmake -E chdir build cmake -E time cmake -DENABLE_CLING=TRUE -DBUILD_SHARED_LIBS=TRUE -DALLOW_PER_PROJECT_CTP_SCRIPTS=TRUE RUN -DBUILD_EXAMPLES=FALSE -DBUNDLE_EXAMPLE_SCRIPTS=FALSE -DCMAKE_BUILD_TYPE=Debug -DENABLE_CXXCTP=TRUE ..
RUN cmake -E chdir build cmake -E time cmake --build . -- -j6
# you can install CXXCTP_tool:
RUN cmake -E chdir build make install
# check supported plugins
RUN /usr/local/bin/CXXCTP_tool --plugins

# folly
# NOTE: we patched folly for clang support https://github.com/facebook/folly/issues/976
RUN ["chmod", "+x", "/opt/CXXCTP/submodules/CXTPL/scripts/install_folly.sh"]

WORKDIR /opt/CXXCTP

RUN rm -rf /opt/CXXCTP

# reset
WORKDIR /opt
CMD LD_LIBRARY_PATH=/usr/lib:/usr/local/lib

# remove unused apps after install
RUN         $APT remove -y \
                    git \
                    wget

RUN echo ClientAliveInterval 60 >> /etc/ssh/sshd_config
RUN service ssh restart
