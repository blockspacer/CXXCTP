# NOTE: you can use docker_pull.py if docker hub blocked under corp proxy
# See:
# + https://gist.github.com/blockspacer/893b31e61c88f6899ffd0813111b3e41#file-docker-conf-proxy-rxt
# + https://stackoverflow.com/a/53551452
# + https://medium.com/@saniaky/configure-docker-to-use-a-host-proxy-e88bd988c0aa
# + https://stackoverflow.com/a/28093517
# + https://stackoverflow.com/a/38901128
# + https://dev.to/shriharshmishra/behind-the-corporate-proxy-2jd8
# + https://stackoverflow.com/a/38901128
ARG UBUNTU_VERSION=18.04
FROM        ubuntu:${UBUNTU_VERSION} as cxxctp_build_env

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
# https://github.com/phusion/baseimage-docker/issues/319
# RUN export DEBIAN_FRONTEND=noninteractive
# Set it via ARG as this only is available during build:
ARG DEBIAN_FRONTEND=noninteractive

ARG ENABLE_LLVM="True"

ARG GIT_EMAIL="you@example.com"

ARG GIT_USERNAME="Your Name"

ENV LC_ALL=C.UTF-8 \
    LANG=en_US.UTF-8 \
    LANGUAGE=en_US:en \
    #TERM=screen \
    PATH=/usr/lib/clang/6.0/include:/usr/lib/llvm-6.0/include/:$PATH \
    GIT_AUTHOR_NAME=$GIT_USERNAME \
    GIT_AUTHOR_EMAIL=$GIT_EMAIL \
    GIT_COMMITTER_NAME=$GIT_USERNAME \
    GIT_COMMITTER_EMAIL=$GIT_EMAIL

ARG APT="apt-get -qq --no-install-recommends"

# docker build --build-arg NO_SSL="False" APT="apt-get -qq --no-install-recommends" .
ARG NO_SSL="True"

# TODO
# better dev-env https://github.com/aya/infra/blob/318b16621c7f6d3cd33cfd481f46eed5d750b6aa/stack/ide/docker/ide/Dockerfile

# https://www.peterbe.com/plog/set-ex
# RUN set -ex

# NO_SSL usefull under proxy, you can disable it with --build-arg NO_SSL="False"
# Also change http-proxy.conf and ~/.docker/config.json like so https://medium.com/@saniaky/configure-docker-to-use-a-host-proxy-e88bd988c0aa
#
# read https://docs.docker.com/network/proxy/
#
# NOTE:
#
# (!!!) Turns off SSL verification on the whole system (!!!)
#
RUN set -ex \
  && \
  if [ "$NO_SSL" = "True" ]; then \
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
  fi \
  && \
  $APT update \
  && \
  $APT install -y --reinstall software-properties-common \
  && \
  $APT install -y gnupg2 wget \
  && \
  wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key --no-check-certificate | apt-key add -

# See `How to add an Ubuntu apt-get key from behind a firewall`
# + http://redcrackle.com/blog/how-add-ubuntu-apt-get-key-behind-firewall

# NOTE: need to set at least empty http-proxy
# https://github.com/EtiennePerot/parcimonie.sh/issues/15
RUN set -ex \
  && \
  if [ ! -z "$http_proxy" ]; then \
    apt-key adv --keyserver-options http-proxy=$http_proxy --keyserver keyserver.ubuntu.com --recv-keys 94558F59 \
    && \
    apt-key adv --keyserver-options http-proxy=$http_proxy --keyserver keyserver.ubuntu.com --recv-keys 1E9377A2BA9EF27F \
    && \
    apt-key adv --keyserver-options http-proxy=$http_proxy --keyserver keyserver.ubuntu.com --recv-keys 2EA8F35793D8809A \
    ; \
  else \
    apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 94558F59 \
    && \
    apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 1E9377A2BA9EF27F \
    && \
    apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 2EA8F35793D8809A \
    ; \
  fi \
  && \
  apt-key adv --keyserver-options http-proxy=$http_proxy --fetch-keys http://llvm.org/apt/llvm-snapshot.gpg.key \
  && \
  apt-add-repository -y "deb http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu $(lsb_release -sc) main" \
  && \
  apt-add-repository -y "deb http://apt.llvm.org/xenial/ llvm-toolchain-xenial-5.0 main" \
  && \
  apt-add-repository -y "deb http://apt.llvm.org/xenial/ llvm-toolchain-xenial-6.0 main" \
  && \
  apt-add-repository -y "deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic-7 main" \
  && \
  apt-add-repository -y "deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic-8 main" \
  && \
  $APT update \
  && \
  $APT install -y \
                    ca-certificates \
                    software-properties-common \
                    git \
                    wget \
                    locales
# TODO
#RUN set -ex \
#    && for key in \
#    4ED778F539E3634C779C87C6D7062848A1AB005C \
#    B9E2F5981AA6E0CD28160D9FF13993A75599653C \
#    94AE36675C464D64BAFA68DD7434390BDBE9B9C5 \
#    B9AE9905FFD7803F25714661B63B535A4C206CA9 \
#    77984A986EBC2AA786BC0F66B01FBB92821C587A \
#    71DCFD284A79C3B38668286BC97EC7A07EDE3FC1 \
#    FD3A5288F042B6850C66B31F09FE44734EB7990E \
#    8FCCA13FEF1D0C2E91008E09770F7A9A5AE15600 \
#    C4F0DFFF4E8C1A8236409D08E73BC641CC11F4C8 \
#    DD8F2338BAE7501E3DD5AC78C273792F7D83545D \
#    A48C2BEE680E841632CD4E44F07496B3EB3C1762 \
#    ; do \
#    gpg --batch --keyserver ipv4.pool.sks-keyservers.net --recv-keys "$key" || \
#    gpg --batch --keyserver pool.sks-keyservers.net --recv-keys "$key" || \
#    gpg --batch --keyserver pgp.mit.edu --recv-keys "$key" || \
#    gpg --batch --keyserver keyserver.pgp.com --recv-keys "$key" || \
#    gpg --batch --keyserver ha.pool.sks-keyservers.net --recv-keys "$key" ; \
#    done

RUN set -ex \
  && \
  if [ "$NO_SSL" = "True" ]; then \
    git config --global http.sslVerify false \
    && \
    git config --global http.postBuffer 1048576000 \
    && \
    export GIT_SSL_NO_VERIFY=true \
    ; \
  fi \
  && \
  $APT update \
  && \
  $APT install -y \
                    make \
                    git \
                    curl \
                    vim \
                    vim-gnome \
  && \
  $APT install -y cmake build-essential \
  && \
    if [ "$ENABLE_LLVM" = "True" ]; then \
    $APT install -y \
                    clang-6.0 python-lldb-6.0 lldb-6.0 lld-6.0 llvm-6.0-dev \
                    clang-tools-6.0 libclang-common-6.0-dev libclang-6.0-dev \
                    libc++abi-dev libc++-dev libclang-common-6.0-dev libclang1-6.0 libclang-6.0-dev \
                    libstdc++6 libstdc++-6-dev \
    ; \
    fi \
  && \
  $APT install -y libboost-dev \
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
                    libcurl4-openssl-dev \
  && \
  $APT install -y mesa-utils \
                            libglu1-mesa-dev \
                            dbus-x11 \
                            libx11-dev \
                            xorg-dev \
                            libssl-dev \
                            python3 \
                            python3-pip \
                            python3-dev \
                            python3-setuptools \
  && \
  $APT install -y nano \
                            mc

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

# TODO https://github.com/moby/moby/issues/1799#issuecomment-489119778
RUN mkdir -p $HOME/.pip/ \
  && \
  echo "[global]" >> $HOME/.pip/pip.conf \
  && \
  echo "timeout = 60" >> $HOME/.pip/pip.conf \
  && \
  echo "index-url = https://pypi.python.org/simple" >> $HOME/.pip/pip.conf \
  && \
  echo "extra-index-url = http://151.101.112.223/root/pypi/+simple" >> $HOME/.pip/pip.conf \
  && \
  echo "                  http://pypi.python.org/simple" >> $HOME/.pip/pip.conf \
  && \
  echo "trusted-host = download.zope.org" >> $HOME/.pip/pip.conf \
  && \
  echo "               pypi.python.org" >> $HOME/.pip/pip.conf \
  && \
  echo "               secondary.extra.host" >> $HOME/.pip/pip.conf \
  && \
  echo "               https://pypi.org" >> $HOME/.pip/pip.conf \
  && \
  echo "               pypi.org" >> $HOME/.pip/pip.conf \
  && \
  echo "               pypi.org:443" >> $HOME/.pip/pip.conf \
  && \
  echo "               151.101.128.223" >> $HOME/.pip/pip.conf \
  && \
  echo "               151.101.128.223:443" >> $HOME/.pip/pip.conf \
  && \
  echo "               https://pypi.python.org" >> $HOME/.pip/pip.conf \
  && \
  echo "               pypi.python.org" >> $HOME/.pip/pip.conf \
  && \
  echo "               pypi.python.org:443" >> $HOME/.pip/pip.conf \
  && \
  echo "               151.101.112.223" >> $HOME/.pip/pip.conf \
  && \
  echo "               151.101.112.223:443" >> $HOME/.pip/pip.conf \
  && \
  echo "               https://files.pythonhosted.org" >> $HOME/.pip/pip.conf \
  && \
  echo "               files.pythonhosted.org" >> $HOME/.pip/pip.conf \
  && \
  echo "               files.pythonhosted.org:443" >> $HOME/.pip/pip.conf \
  && \
  echo "               151.101.113.63" >> $HOME/.pip/pip.conf \
  && \
  echo "               151.101.113.63:443" >> $HOME/.pip/pip.conf

# RUN cat $HOME/.pip/pip.conf

WORKDIR /opt

# pip install setuptools --upgrade

# /usr/lib/python3.6/distutils/dist.py:261: UserWarning: Unknown distribution option: 'long_description_content_type'
RUN pip3 install --index-url=https://pypi.python.org/simple/ --trusted-host pypi.org --trusted-host pypi.python.org --trusted-host files.pythonhosted.org wheel \
  && \
  pip3 install --index-url=https://pypi.python.org/simple/ --trusted-host pypi.org --trusted-host pypi.python.org --trusted-host files.pythonhosted.org virtualenv \
  && \
  pip3 install --index-url=https://pypi.python.org/simple/ --trusted-host pypi.org --trusted-host pypi.python.org --trusted-host files.pythonhosted.org conan \
  && \
  pip3 install --index-url=https://pypi.python.org/simple/ --trusted-host pypi.org --trusted-host pypi.python.org --trusted-host files.pythonhosted.org conan_package_tools

RUN conan remote update conan-center https://conan.bintray.com False

# TODO: use conan profile new https://github.com/conan-io/conan/issues/1541#issuecomment-321235829
RUN mkdir -p $HOME/.conan/profiles/ \
  && \
  echo "[settings]" >> ~/.conan/profiles/clang \
  && \
  echo "os_build=Linux" >> ~/.conan/profiles/clang \
  && \
  echo "os=Linux" >> ~/.conan/profiles/clang \
  && \
  echo "arch_build=x86_64" >> ~/.conan/profiles/clang \
  && \
  echo "arch=x86_64" >> ~/.conan/profiles/clang \
  && \
  echo "compiler=clang" >> ~/.conan/profiles/clang \
  && \
  echo "compiler.version=6.0" >> ~/.conan/profiles/clang \
  && \
  echo "compiler.libcxx=libstdc++11" >> ~/.conan/profiles/clang \
  && \
  echo "" >> ~/.conan/profiles/clang \
  && \
  echo "[env]" >> ~/.conan/profiles/clang \
  && \
  echo "CC=/usr/bin/clang" >> ~/.conan/profiles/clang \
  && \
  echo "CXX=/usr/bin/clang++" >> ~/.conan/profiles/clang

# TODO: use conan profile new https://github.com/conan-io/conan/issues/1541#issuecomment-321235829
RUN mkdir -p $HOME/.conan/profiles/ \
  && \
  echo "[settings]" >> ~/.conan/profiles/gcc \
  && \
  echo "os_build=Linux" >> ~/.conan/profiles/gcc \
  && \
  echo "os=Linux" >> ~/.conan/profiles/gcc \
  && \
  echo "arch_build=x86_64" >> ~/.conan/profiles/gcc \
  && \
  echo "arch=x86_64" >> ~/.conan/profiles/gcc \
  && \
  echo "compiler=gcc" >> ~/.conan/profiles/gcc \
  && \
  echo "compiler.version=7" >> ~/.conan/profiles/gcc \
  && \
  echo "compiler.libcxx=libstdc++11" >> ~/.conan/profiles/gcc \
  && \
  echo "" >> ~/.conan/profiles/gcc \
  && \
  echo "[env]" >> ~/.conan/profiles/gcc \
  && \
  echo "CC=/usr/bin/gcc" >> ~/.conan/profiles/gcc \
  && \
  echo "CXX=/usr/bin/g++" >> ~/.conan/profiles/gcc

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

# allows individual sections to be run by doing: docker build --target cxxctp_tool ...
FROM        cxxctp_build_env as cxxctp_tool

# NOTE: create folder `.ca-certificates` with custom certs
# switch to root
#USER root
COPY ./.ca-certificates/* /usr/local/share/ca-certificates/
RUN update-ca-certificates --fresh
# switch back to custom user
#USER docker

WORKDIR /opt

# NOTE: ADD invalidate the cache for the copy
ADD . /opt/CXXCTP

# RUN git clone --depth=1 --recurse-submodules --single-branch --branch=master https://github.com/blockspacer/CXXCTP.git

WORKDIR /opt/CXXCTP

# need some git config to apply git patch
RUN git config --global user.email "$GIT_EMAIL" \
  && \
  git config --global user.name "$GIT_USERNAME"

# TODO https://stackoverflow.com/a/40465312
# RUN git submodule deinit -f . || true
#RUN git pull --recurse-submodules || true
#RUN git submodule sync --recursive || true
#RUN git fetch --recurse-submodules || true
RUN git submodule update --init --recursive --depth 5 || true
#RUN git submodule update --force --recursive --init --remote || true

RUN ls -artl /opt/CXXCTP/ \
  && \
  ls -artl /opt/CXXCTP/scripts \
  && \
  ls -artl /opt/CXXCTP/submodules

# CMake
#RUN ["chmod", "+x", "/opt/CXXCTP/scripts/install_cmake.sh"]
#RUN /bin/bash -c "source /opt/CXXCTP/scripts/install_cmake.sh"
#RUN cmake --version

# cling
# NOTE: run from scripts folder!
WORKDIR /opt/CXXCTP/scripts
RUN ["chmod", "+x", "/opt/CXXCTP/scripts/install_cling.sh"] \
  && \
  /bin/bash -c "source /opt/CXXCTP/scripts/install_cling.sh"
WORKDIR /opt/CXXCTP

# NOTE: need libunwind with -fPIC (POSITION_INDEPENDENT_CODE) support
RUN ["chmod", "+x", "/opt/CXXCTP/scripts/install_libunwind.sh"] \
  && \
  /bin/bash -c "source /opt/CXXCTP/scripts/install_libunwind.sh"

WORKDIR /opt/CXXCTP/submodules/CXTPL

# g3log
RUN ["chmod", "+x", "/opt/CXXCTP/submodules/CXTPL/scripts/install_g3log.sh"] \
  && \
  /bin/bash -c "source /opt/CXXCTP/submodules/CXTPL/scripts/install_g3log.sh" \
  && \
  # gtest \
  ["chmod", "+x", "/opt/CXXCTP/submodules/CXTPL/scripts/install_gtest.sh"] \
  && \
  /bin/bash -c "source /opt/CXXCTP/submodules/CXTPL/scripts/install_gtest.sh" \
  && \
  # gflags \
  ["chmod", "+x", "/opt/CXXCTP/submodules/CXTPL/scripts/install_gflags.sh"] \
  && \
  /bin/bash -c "source /opt/CXXCTP/submodules/CXTPL/scripts/install_gflags.sh" \
  && \
  # folly \
  # NOTE: we patched folly for clang support https://github.com/facebook/folly/issues/976 \
  ["chmod", "+x", "/opt/CXXCTP/submodules/CXTPL/scripts/install_folly.sh"] \
  && \
  /bin/bash -c "source /opt/CXXCTP/submodules/CXTPL/scripts/install_folly.sh"

RUN export CC=gcc \
  && \
  export CXX=g++ \
  # create build dir \
  && \
  cmake -E make_directory build \
  && \
  # configure \
  && \
  cmake -E chdir build conan install --build=missing --profile gcc .. \
  && \
  cmake -E chdir build cmake -E time cmake -DBUILD_EXAMPLES=FALSE -DENABLE_CLING=FALSE -DCMAKE_BUILD_TYPE=Debug .. \
  # build \
  && \
  cmake -E chdir build cmake -E time cmake --build . -- -j6 \
  # install lib and CXTPL_tool \
  && \
  cmake -E chdir build make install

WORKDIR /opt/CXXCTP

RUN export CC=clang \
  && \
  export CXX=clang++ \
  && \
  cmake -E make_directory build \
  && \
  cmake -E make_directory resources/cxtpl/generated \
  && \
  cmake -E chdir build conan install --build=missing --profile clang .. \
  && \
  cmake -E chdir build cmake -E time cmake -DENABLE_CLING=TRUE -DBUILD_SHARED_LIBS=TRUE -DALLOW_PER_PROJECT_CTP_SCRIPTS=TRUE RUN -DBUILD_EXAMPLES=FALSE -DBUNDLE_EXAMPLE_SCRIPTS=FALSE -DCMAKE_BUILD_TYPE=Debug -DENABLE_CXXCTP=TRUE .. \
  && \
  cmake -E chdir build cmake -E time cmake --build . -- -j6 \
  #  you can install CXXCTP_tool: \
  && \
  cmake -E chdir build make install \
  #  check supported plugins \
  && \
  /usr/local/bin/CXXCTP_tool --plugins

WORKDIR /opt/CXXCTP

RUN rm -rf /opt/CXXCTP

# reset
WORKDIR /opt
# LD_LIBRARY_PATH=/usr/lib:/usr/local/lib

# remove unused apps after install
RUN         $APT remove -y \
                    git \
                    wget

RUN echo ClientAliveInterval 60 >> /etc/ssh/sshd_config

#RUN service ssh restart

#ENV DEBIAN_FRONTEND teletype

# default
FROM        cxxctp_tool

CMD ["bash"]

