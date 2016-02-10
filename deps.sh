#!/usr/bin/env bash

set -e

function install_deps_debian () {
    # Sudo'd version of travis installation instructions
    sudo apt-get update -qq
    sudo apt-get install python-software-properties
    sudo add-apt-repository --yes ppa:kalakris/cmake
    sudo apt-get update -qq
    sudo apt-get -y install cmake \
         build-essential \
         libcurl-dev \
         pkg-config \
         cmake \
         doxygen
}

function install_deps_osx () {
    # TODO: Add OS X brew installation dependencies
    if [[ ! -x /usr/local/bin/brew ]]; then
        echo "You're missing Homebrew!"
        exit 1
    fi
    brew install cmake pkg-config doxygen
}

function build_lib () {
    mkdir -p build && cd build/
    cmake ../
    make
    sudo make install
}

if [[ "$OSTYPE" == "linux-"* ]]; then
    install_deps_debian
elif [[ "$OSTYPE" == "darwin"* ]]; then
    install_deps_osx
else
    echo "This script does not support this platform. Please file a Github issue!"
    exit 1
fi
build_lib
