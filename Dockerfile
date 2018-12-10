FROM ubuntu:18.04

RUN apt-get update -qq && apt-get upgrade -y
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y tzdata
RUN apt-get install --fix-missing -y build-essential libgtest-dev gdb wget software-properties-common

RUN add-apt-repository ppa:ubuntu-toolchain-r/test && \
    apt-get update && \
    apt-get install -y gcc-8 g++-8

RUN echo "set nu" > ~/.vimrc && echo "inoremap jk <esc>" >> ~/.vimrc

RUN cd /tmp && \
wget https://github.com/Kitware/CMake/releases/download/v3.13.1/cmake-3.13.1.tar.gz && \
tar -xzvf cmake-3.13.1.tar.gz && \
cd cmake-3.13.1 && \
./bootstrap && make && make install

# ----------- Build gtest ------------
RUN cd /usr/src/gtest && \
    cmake CMakeLists.txt && \
    make && \
    cp *.a /usr/lib
# ------------------------------------

RUN apt-get install -y vim-gtk
ENV APP_HOME /code

RUN mkdir $APP_HOME

WORKDIR $APP_HOME
