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

# TODO: move to pydocker https://github.com/moby/moby/issues/16058#issuecomment-489116273

# Give docker the rights to access X-server
# sudo -E xhost +local:docker

# build Dockerfile
# sudo -E docker build --no-cache -t cpp-docker-cxxctp .
#
# OR under proxy:
# sudo -E DOCKER_OPTS='--insecure-registry registry.docker.io --insecure-registry production.cloudflare.docker.com' \
#  docker build  \
#  --build-arg http_proxy=http://172.17.0.1:3128 \
#  --build-arg https_proxy=http://172.17.0.1:3128 \
#  --build-arg no_proxy=192.168.99.0/24,$(minikube ip),localhost,127.0.0.*,10.*,192.168.*,*.somecorp.ru,*.mycorp.ru \
#  --build-arg HTTP_PROXY=http://172.17.0.1:3128 \
#  --build-arg HTTPS_PROXY=http://172.17.0.1:3128 \
#  --build-arg NO_PROXY=192.168.99.0/24,$(minikube ip),localhost,127.0.0.*,10.*,192.168.*,*.somecorp.ru,*.mycorp.ru \
#  --no-cache -t cpp-docker-cxxctp .
# OR
# --network=host. This will make the build command use the network settings of the host.

# Now let's check if our image has been created.
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

ARG ENABLE_LLVM="True"
ARG GIT_EMAIL="you@example.com"
ARG GIT_USERNAME="Your Name"
# SEE: http://kefhifi.com/?p=701
ARG GIT_WITH_OPENSSL=""
# see git config --global http.sslCAInfo
ARG GIT="git"
ARG GIT_CA_INFO=""
ENV LC_ALL=C.UTF-8 \
    LANG=en_US.UTF-8 \
    LANGUAGE=en_US:en \
    #TERM=screen \
    PATH=/usr/local/bin/:/usr/local/include/:/usr/local/lib/:/usr/lib/clang/6.0/include:/usr/lib/llvm-6.0/include/:$PATH \
    LD_LIBRARY_PATH=/usr/local/lib/:$LD_LIBRARY_PATH \
    GIT_AUTHOR_NAME=$GIT_USERNAME \
    GIT_AUTHOR_EMAIL=$GIT_EMAIL \
    GIT_COMMITTER_NAME=$GIT_USERNAME \
    GIT_COMMITTER_EMAIL=$GIT_EMAIL \
    WDIR=/opt
RUN mkdir -p $WDIR
ARG APT="apt-get -qq --no-install-recommends"
# docker build --build-arg NO_SSL="False" APT="apt-get -qq --no-install-recommends" .
ARG NO_SSL="True"
# https://askubuntu.com/a/1013396
# https://github.com/phusion/baseimage-docker/issues/319
# RUN export DEBIAN_FRONTEND=noninteractive
# Set it via ARG as this only is available during build:
RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections

# TODO
# better dev-env https://github.com/aya/infra/blob/318b16621c7f6d3cd33cfd481f46eed5d750b6aa/stack/ide/docker/ide/Dockerfile

# https://www.peterbe.com/plog/set-ex
# RUN set -ex



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

# RUN cat $HOME/.pip/pip.conf

# pip install setuptools --upgrade

# /usr/lib/python3.6/distutils/dist.py:261: UserWarning: Unknown distribution option: 'long_description_content_type'

COPY ./.ca-certificates/* /usr/local/share/ca-certificates/

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
  ldconfig \
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
  wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key --no-check-certificate | apt-key add - \
  # See `How to add an Ubuntu apt-get key from behind a firewall` \
  # + http://redcrackle.com/blog/how-add-ubuntu-apt-get-key-behind-firewall \
  # NOTE: need to set at least empty http-proxy \
  # https://github.com/EtiennePerot/parcimonie.sh/issues/15 \
  && \
  export GNUPGHOME="$(mktemp -d)" \
  && \
  (mkdir ~/.gnupg || true) \
  && \
  echo "keyserver-options auto-key-retrieve" >> ~/.gnupg/gpg.conf \
  && \
  wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key --no-check-certificate | apt-key add - \
  && \
  # Try more keyservers to fix unstable builds \
  # see https://unix.stackexchange.com/a/361220 \
  keyservers="hkp://keyserver.ubuntu.com:80"\ "keyserver.ubuntu.com:80"\ "pool.sks-keyservers.net"\ "keyserver.ubuntu.com"\ "ipv4.pool.sks-keyservers.net"\ "Zpool.sks-keyservers.net"\ "keyserver.pgp.com"\ "ha.pool.sks-keyservers.net"\ "hkp://p80.pool.sks-keyservers.net:80"\ "pgp.mit.edu" \
  && \
  keys=94558F59\ 1E9377A2BA9EF27F\ 2EA8F35793D8809A \
  && \
  if [ ! -z "$http_proxy" ]; then \
    echo 'WARNING: GPG SSL CHECKS DISABLED! SEE http_proxy IN DOCKERFILE' \
    && \
    for key in $keys; do \
    for server in $keyservers; do \
    echo "Fetching GPG key ${key} from ${server}" \
    && \
    (gpg --keyserver "$server" --keyserver-options http-proxy=$http_proxy --recv-keys "${key}" || true) \
    ; done \
    ; done \
    ; \
  else \
    for key in $keys; do \
    for server in $keyservers; do \
    echo "Fetching GPG key ${key} from ${server}" \
    && \
    (gpg --keyserver "$server" --keyserver-options timeout=10 --recv-keys "${key}" || true) \
    ; done \
    ; done \
    ; \
  fi \
  && \
  gpg --list-keys \
  && \
  (apt-key adv --keyserver-options http-proxy=$http_proxy --fetch-keys http://llvm.org/apt/llvm-snapshot.gpg.key || true) \
  && \
  echo "added llvm-snapshot.gpg.key" \
  #&& \
  #apt-add-repository -y "deb http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu $(lsb_release -sc) main" \
  && \
  apt-add-repository -y "deb http://apt.llvm.org/xenial/ llvm-toolchain-xenial-5.0 main" \
  && \
  apt-add-repository -y "deb http://apt.llvm.org/xenial/ llvm-toolchain-xenial-6.0 main" \
  && \
  apt-add-repository -y "deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic-7 main" \
  && \
  apt-add-repository -y "deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic-8 main" \
  && \
  echo "added llvm-toolchain repository" \
  && \
  ldconfig \
  && \
  $APT update \
  && \
  $APT install -y \
                    ca-certificates \
                    software-properties-common \
                    #git \
                    wget \
                    locales \
                    make \
                    autoconf automake autotools-dev libtool \
                    curl \
                    vim \
  && \
  update-ca-certificates --fresh \
  && \
  $APT install -y build-essential \
  && \
    if [ "$ENABLE_LLVM" = "True" ]; then \
    $APT install -y \
                    clang-6.0 libstdc++6 \
    ; \
    fi \
  && \
  $APT install -y \
                    libboost-dev \
                    libevent-dev \
                    libdouble-conversion-dev \
                    libiberty-dev \
                    liblz4-dev \
                    liblzma-dev \
                    libsnappy-dev \
                    zlib1g-dev \
                    libboost-all-dev \
                    #
                    #libgoogle-glog-dev \
                    #libgflags-dev \
                    #libgtest-dev \
                    #libzstd-dev \
                    #libjemalloc-dev \
                    openmpi-bin \
                    openmpi-common \
                    libopenmpi-dev \
                    binutils-dev \
                    libssl-dev \
                    pkg-config \
                    autoconf-archive \
                    bison \
                    flex \
                    gperf \
                    joe \
                    libcap-dev \
                    libkrb5-dev \
                    libpcre3-dev \
                    libpthread-stubs0-dev \
                    libnuma-dev \
                    libsasl2-dev \
                    libsqlite3-dev \
                    libtool \
                    netcat-openbsd \
                    unzip \
                    gcc \
                    g++ \
                    gnutls-bin \
                    openssl \
                    fakeroot \
                    dpkg-dev \
                    libcurl4-openssl-dev \
  && \
  $APT install -y mesa-utils \
                            libegl1-mesa-dev \
                            libgles2-mesa-dev \
                            libglu1-mesa-dev \
                            dbus-x11 \
                            libx11-dev \
                            xorg-dev \
                            libssl-dev \
                            python3 \
                            python3-pip \
                            python3-dev \
                            python3-setuptools  \
  # For convenience, alias (but don't sym-link) python & pip to python3 & pip3 as recommended in: \
  # http://askubuntu.com/questions/351318/changing-symlink-python-to-python3-causes-problems \
  && \
  if [ "$GIT_WITH_OPENSSL" = "True" ]; then \
    echo 'building git from source, see ARG GIT_WITH_OPENSSL' \
    && \
    # Ubuntu's default git package is built with broken gnutls. Rebuild git with openssl.
    $APT update \
    #&& \
    #add-apt-repository ppa:git-core/ppa  \
    #apt-add-repository "deb http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu $(lsb_release -sc) main" \
    #&& \
    #apt-key add 1E9377A2BA9EF27F \
    #&& \
    #printf "deb-src http://ppa.launchpad.net/git-core/ppa/ubuntu ${CODE_NAME} main\n" >> /etc/apt/sources.list.d/git-core-ubuntu-ppa-bionic.list \
    && \
    $APT install -y --no-install-recommends \
       software-properties-common \
       fakeroot ca-certificates tar gzip zip \
       autoconf automake bzip2 file g++ gcc \
       #imagemagick libbz2-dev libc6-dev libcurl4-openssl-dev \
       #libglib2.0-dev libevent-dev \
       #libdb-dev  libffi-dev libgeoip-dev libjpeg-dev libkrb5-dev \
       #liblzma-dev libncurses-dev \
       #libmagickcore-dev libmagickwand-dev libmysqlclient-dev libpng-dev \
       libssl-dev libtool libxslt-dev \
       #libpq-dev libreadline-dev libsqlite3-dev libwebp-dev libxml2-dev \
       #libyaml-dev zlib1g-dev \
       make patch xz-utils unzip curl  \
    && \
    sed -i -- 's/#deb-src/deb-src/g' /etc/apt/sources.list \
    && \
    sed -i -- 's/# deb-src/deb-src/g' /etc/apt/sources.list \
    && \
    $APT update \
    && \
    $APT install -y gnutls-bin openssl \
    && \
    $APT install -y build-essential fakeroot dpkg-dev -y \
    #&& \
    #($APT remove -y git || true ) \
    && \
    $APT build-dep git -y \
    && \
    # git build deps
    $APT install -y libcurl4-openssl-dev liberror-perl git-man -y \
    && \
    mkdir source-git \
    && \
    cd source-git/ \
    && \
    $APT source git \
    && \
    cd git-2.*.*/ \
    && \
    sed -i -- 's/libcurl4-gnutls-dev/libcurl4-openssl-dev/' ./debian/control \
    && \
    sed -i -- '/TEST\s*=\s*test/d' ./debian/rules \
    && \
    dpkg-buildpackage -rfakeroot -b -uc -us \
    && \
    dpkg -i ../git_*ubuntu*.deb \
    ; \
  else \
    $APT install -y git \
    ; \
  fi \
  && \
  if [ "$NO_SSL" = "True" ]; then \
    echo 'WARNING: GIT SSL CHECKS DISABLED! SEE NO_SSL FLAG IN DOCKERFILE' \
    && \
    ($GIT config --global http.sslVerify false || true) \
    && \
    ($GIT config --global https.sslVerify false || true) \
    && \
    ($GIT config --global http.postBuffer 1048576000 || true) \
    && \
    # solves 'Connection time out' on server in company domain. \
    ($GIT config --global url."https://github.com".insteadOf git://github.com || true) \
    && \
    export GIT_SSL_NO_VERIFY=true \
    ; \
  fi \
  && \
  if [ "$GIT_CA_INFO" != "" ]; then \
    echo 'WARNING: GIT_CA_INFO CHANGED! SEE GIT_CA_INFO FLAG IN DOCKERFILE' \
    && \
    ($GIT config --global http.sslCAInfo $GIT_CA_INFO || true) \
    && \
    ($GIT config --global http.sslCAPath $GIT_CA_INFO || true) \
    ; \
  fi \
  && \
  echo "alias python='python3'" >> /root/.bash_aliases \
  && \
  echo "alias pip='pip3'" >> /root/.bash_aliases \
  && \
  $APT install -y nano \
                            mc \
                            bash \
  && \
  mkdir -p $HOME/.pip/ \
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
  echo "               151.101.113.63:443" >> $HOME/.pip/pip.conf \
  && \
  $APT clean \
  && \
  $APT autoremove \
  && \
  rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* \
  && \
  cd $WDIR \
  && \
  pip3 install --no-cache-dir --index-url=https://pypi.python.org/simple/ --trusted-host pypi.org --trusted-host pypi.python.org --trusted-host files.pythonhosted.org wheel \
  && \
  pip3 install --no-cache-dir --index-url=https://pypi.python.org/simple/ --trusted-host pypi.org --trusted-host pypi.python.org --trusted-host files.pythonhosted.org virtualenv \
  && \
  pip3 install --no-cache-dir --index-url=https://pypi.python.org/simple/ --trusted-host pypi.org --trusted-host pypi.python.org --trusted-host files.pythonhosted.org conan \
  && \
  pip3 install --no-cache-dir --index-url=https://pypi.python.org/simple/ --trusted-host pypi.org --trusted-host pypi.python.org --trusted-host files.pythonhosted.org conan_package_tools \
  && \
  conan remote update conan-center https://conan.bintray.com False \
  # TODO: use conan profile new https://github.com/conan-io/conan/issues/1541#issuecomment-321235829 \
  && \
  mkdir -p $HOME/.conan/profiles/ \
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
  echo "CC=/usr/bin/clang-6.0" >> ~/.conan/profiles/clang \
  && \
  echo "CXX=/usr/bin/clang++-6.0" >> ~/.conan/profiles/clang \
  && \
  # TODO: use conan profile new https://github.com/conan-io/conan/issues/1541#issuecomment-321235829 \
  mkdir -p $HOME/.conan/profiles/ \
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

WORKDIR $WDIR

# allows individual sections to be run by doing: docker build --target cxxctp_tool ...
FROM        cxxctp_build_env as cxxctp_tool
ARG GIT_EMAIL="you@example.com"
ARG GIT_USERNAME="Your Name"
ARG APT="apt-get -qq --no-install-recommends"
ARG GIT="git"
ARG GIT_CA_INFO=""
ARG NO_SSL="True"
# NOTE: UPPERCASE (TRUE or FALSE)
ARG ENABLE_CLING="TRUE"
ENV LC_ALL=C.UTF-8 \
    LANG=en_US.UTF-8 \
    LANGUAGE=en_US:en \
    #TERM=screen \
    PATH=/usr/local/bin/:/usr/local/include/:/usr/local/lib/:/usr/lib/clang/6.0/include:/usr/lib/llvm-6.0/include/:$PATH \
    LD_LIBRARY_PATH=/usr/local/lib/:$LD_LIBRARY_PATH \
    GIT_AUTHOR_NAME=$GIT_USERNAME \
    GIT_AUTHOR_EMAIL=$GIT_EMAIL \
    GIT_COMMITTER_NAME=$GIT_USERNAME \
    GIT_COMMITTER_EMAIL=$GIT_EMAIL \
    WDIR=/opt
RUN mkdir -p $WDIR
# https://askubuntu.com/a/1013396
# https://github.com/phusion/baseimage-docker/issues/319
# RUN export DEBIAN_FRONTEND=noninteractive
# Set it via ARG as this only is available during build:
RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections
RUN ldconfig

# NOTE: create folder `.ca-certificates` with custom certs
# switch to root
#USER root
COPY ./.ca-certificates/* /usr/local/share/ca-certificates/
RUN update-ca-certificates --fresh
# switch back to custom user
#USER docker

WORKDIR $WDIR

# NOTE: ADD invalidate the cache for the copy
ADD . $WDIR/CXXCTP

# RUN git clone --depth=1 --recurse-submodules --single-branch --branch=master https://github.com/blockspacer/CXXCTP.git

WORKDIR $WDIR/CXXCTP


# TODO https://stackoverflow.com/a/40465312
# RUN git submodule deinit -f . || true
#RUN git pull --recurse-submodules || true
#RUN git submodule sync --recursive || true
#RUN git fetch --recurse-submodules || true
#RUN git submodule update --init --recursive --depth 5 || true
#RUN git submodule update --force --recursive --init --remote || true

# CMake
#RUN /bin/bash -c "source $WDIR/CXXCTP/scripts/install_cmake.sh"
#RUN cmake --version

# cling
# NOTE: run from scripts folder!

#RUN set -ex \
#  && \
#  /bin/bash -c "source $WDIR/CXXCTP/scripts/install_cmake.sh" \
#  && \
#  /bin/bash -c "source $WDIR/CXXCTP/scripts/install_cling.sh"

# NOTE: need libunwind with -fPIC (POSITION_INDEPENDENT_CODE) support
#RUN set -ex \
#  && \
#  /bin/bash -c "source $WDIR/CXXCTP/scripts/install_libunwind.sh"

#RUN set -ex \
#  && \
#  /bin/bash -c "source $WDIR/CXXCTP/submodules/CXTPL/scripts/install_g3log.sh" \
#  && \
#  # gtest \
#  /bin/bash -c "source $WDIR/CXXCTP/submodules/CXTPL/scripts/install_gtest.sh" \
#  && \
#  # gflags \
#  /bin/bash -c "source $WDIR/CXXCTP/submodules/CXTPL/scripts/install_gflags.sh" \
#  && \
#  # folly \
#  # NOTE: we patched folly for clang support https://github.com/facebook/folly/issues/976 \
#  /bin/bash -c "source $WDIR/CXXCTP/submodules/CXTPL/scripts/install_folly.sh"

RUN set -ex \
  && \
  if [ "$NO_SSL" = "True" ]; then \
    echo 'WARNING: GIT SSL CHECKS DISABLED! SEE NO_SSL FLAG IN DOCKERFILE' \
    && \
    ($GIT config --global http.sslVerify false || true) \
    && \
    ($GIT config --global https.sslVerify false || true) \
    && \
    ($GIT config --global http.postBuffer 1048576000 || true) \
    && \
    # solves 'Connection time out' on server in company domain. \
    ($GIT config --global url."https://github.com".insteadOf git://github.com || true) \
    && \
    export GIT_SSL_NO_VERIFY=true \
    ; \
  fi \
  && \
  if [ "$GIT_CA_INFO" != "" ]; then \
    echo 'WARNING: GIT_CA_INFO CHANGED! SEE GIT_CA_INFO FLAG IN DOCKERFILE' \
    && \
    ($GIT config --global http.sslCAInfo $GIT_CA_INFO || true) \
    && \
    ($GIT config --global http.sslCAPath $GIT_CA_INFO || true) \
    ; \
  fi \
  && \
  # need some git config to apply git patch
  git config --global user.email "$GIT_EMAIL" \
  && \
  git config --global user.name "$GIT_USERNAME" \
  && \
  (git submodule update --init --recursive --depth 50 --progress || true) \
  && \
  # Uninstall the default version provided by Ubuntu package manager, so we can install custom one
  ($APT purge -y cmake || true) \
  && \
  cd $WDIR/CXXCTP/scripts \
  && \
  chmod +x $WDIR/CXXCTP/scripts/install_cmake.sh \
  && \
  chmod +x $WDIR/CXXCTP/scripts/install_cling.sh \
  && \
  chmod +x $WDIR/CXXCTP/scripts/install_libunwind.sh \
  && \
  chmod +x $WDIR/CXXCTP/submodules/CXTPL/scripts/install_g3log.sh \
  && \
  chmod +x $WDIR/CXXCTP/submodules/CXTPL/scripts/install_gtest.sh \
  && \
  chmod +x $WDIR/CXXCTP/submodules/CXTPL/scripts/install_gflags.sh \
  && \
  chmod +x $WDIR/CXXCTP/submodules/CXTPL/scripts/install_folly.sh \
  && \
  bash $WDIR/CXXCTP/scripts/install_cmake.sh \
  && \
  if [ "$ENABLE_CLING" = "TRUE" ]; then \
    cd $WDIR/CXXCTP/scripts \
    && \
    bash install_cling.sh \
    && \
    ls $WDIR/CXXCTP/cling-build \
    && \
    ls $WDIR/CXXCTP/cling-build/build \
    && \
    ls $WDIR/CXXCTP/cling-build/build/lib \
    && \
    # must exist
    file $WDIR/CXXCTP/cling-build/build/lib/cmake/llvm/LLVMConfig.cmake \
    ; \
  fi \
  && \
  cd $WDIR/CXXCTP \
  #&& \
  #bash $WDIR/CXXCTP/scripts/install_libunwind.sh \
  && \
  cd $WDIR/CXXCTP/submodules/CXTPL \
  #&& \
  #bash $WDIR/CXXCTP/submodules/CXTPL/scripts/install_g3log.sh \
  #&& \
  #bash $WDIR/CXXCTP/submodules/CXTPL/scripts/install_gtest.sh \
  #&& \
  #bash $WDIR/CXXCTP/submodules/CXTPL/scripts/install_gflags.sh \
  #&& \
  #bash $WDIR/CXXCTP/submodules/CXTPL/scripts/install_folly.sh
  && \
  export CC=clang-6.0 \
  && \
  export CXX=clang++-6.0 \
  #&& \
  #cmake -E remove_directory build \
  #&& \
  #cmake -E remove_directory *-build \
  && \
  # create build dir \
  cmake -E make_directory build \
  && \
  mkdir -p ~/.tmp \
  && \
  cd ~/.tmp \
  && \
  #type_safe
  conan remote add Manu343726 https://api.bintray.com/conan/manu343726/conan-packages False \
  && \
  git clone http://github.com/foonathan/type_safe.git -b v0.2.1 \
  && \
  cd type_safe \
  && \
  # NOTE: change `build_type=Debug` to `build_type=Release` in production
  CONAN_REVISIONS_ENABLED=1 \
      CONAN_VERBOSE_TRACEBACK=1 \
      CONAN_PRINT_RUN_COMMANDS=1 \
      CONAN_LOGGING_LEVEL=10 \
      GIT_SSL_NO_VERIFY=true \
      conan create . conan/stable -s build_type=Debug --profile clang --build missing \
  && \
  cd ~/.tmp \
  && \
  #corrade
  # NOTE: change `build_type=Debug` to `build_type=Release` in production
  git clone http://github.com/mosra/corrade.git  \
  && \
  cd corrade \
  && \
  CONAN_REVISIONS_ENABLED=1 \
      CONAN_VERBOSE_TRACEBACK=1 \
      CONAN_PRINT_RUN_COMMANDS=1 \
      CONAN_LOGGING_LEVEL=10 \
      GIT_SSL_NO_VERIFY=true \
      conan create . magnum/stable -s build_type=Debug --profile clang --build missing -tf package/conan/test_package \
  && \
  rm -rf ~/.tmp \
  && \
  cd $WDIR/CXXCTP/submodules/CXTPL \
  && \
  cmake -E time conan config install conan/remotes_disabled_ssl/ \
  && \
  cmake -DEXTRA_CONAN_OPTS="--profile;clang;-s;build_type=Debug;--build;missing" -P tools/buildConanThirdparty.cmake \
  && \
  # configure \
  cmake -E chdir build conan install --build=missing --profile clang .. \
  && \
  cmake -E chdir build cmake -E time cmake -DCLING_DIR="$WDIR/CXXCTP/cling-build/" -DCONAN_AUTO_INSTALL=OFF -DBUILD_EXAMPLES=FALSE -DENABLE_CLING=FALSE -DCMAKE_BUILD_TYPE=Debug .. \
  && \
  # build \
  cmake -E chdir build cmake -E time cmake --build . -- -j6 \
  && \
  # install lib and CXTPL_tool \
  cmake -E chdir build make install \
  #&& \
  #cmake -E remove_directory build \
  #&& \
  # \
  #cmake -E remove_directory *-build \
  && \
  rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* \
  && \
  cd $WDIR/CXXCTP \
  && \
  export CC=clang-6.0 \
  && \
  export CXX=clang++-6.0 \
  #&& \
  #cmake -E remove_directory build \
  #&& \
  #cmake -E remove_directory *-build \
  && \
  cmake -E make_directory build \
  && \
  cmake -E time conan config install conan/remotes_disabled_ssl/ \
  && \
  cmake -DEXTRA_CONAN_OPTS="--profile;clang;-s;build_type=Debug;--build;missing" -P tools/buildConanThirdparty.cmake \
  && \
  cmake -E make_directory resources/cxtpl/generated \
  && \
  cmake -E chdir build conan install --build=missing --profile clang .. \
  && \
  cmake -E chdir build cmake -E time cmake -DCLING_DIR="$WDIR/CXXCTP/cling-build/" -DCONAN_AUTO_INSTALL=OFF -DENABLE_CLING=$ENABLE_CLING -DBUILD_SHARED_LIBS=TRUE -DALLOW_PER_PROJECT_CTP_SCRIPTS=TRUE RUN -DBUILD_EXAMPLES=FALSE -DBUNDLE_EXAMPLE_SCRIPTS=FALSE -DCMAKE_BUILD_TYPE=Debug -DENABLE_CXXCTP=TRUE .. \
  && \
  cmake -E chdir build cmake -E time cmake --build . -- -j6 \
  #  you can install CXXCTP_tool: \
  && \
  cmake -E chdir build make install \
  #  check supported plugins \
  && \
  /usr/local/bin/CXXCTP_tool --plugins \
  #&& \
  #cmake -E remove_directory build \
  #&& \
  #cmake -E remove_directory *-build \
  && \
  rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* /usr/share/doc/* /build/* \
  # remove unused apps after install
  && \
  rm -rf $WDIR/CXXCTP \
  && \
  $APT remove -y \
                    git \
                    wget \
  && \
  $APT clean \
  && \
  $APT autoremove \
  && \
  mkdir -p /etc/ssh/ && echo ClientAliveInterval 60 >> /etc/ssh/sshd_config \
  && \
  rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* /usr/share/doc/* /build/* \
  && \
  ($GIT config --global --unset http.proxyAuthMethod || true) \
  && \
  ($GIT config --global --unset http.proxy || true) \
  && \
  ($GIT config --global --unset https.proxy || true) \
  && \
  mkdir -p /etc/ssh/ && echo ClientAliveInterval 60 >> /etc/ssh/sshd_config

#RUN service ssh restart

#ENV DEBIAN_FRONTEND teletype

# default
FROM        cxxctp_tool
WORKDIR $WDIR
ENTRYPOINT ["/bin/bash"]
CMD ["bash"]
