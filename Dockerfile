FROM ubuntu:18.04

RUN apt-get update -qq && apt-get upgrade -y
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y tzdata
RUN apt-get install -y build-essential cmake libgtest-dev gdb

RUN echo "set nu" > ~/.vimrc && echo "inoremap jk <esc>" >> ~/.vimrc

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
