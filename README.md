## libskylark -- Cross-platform C library for networking Swift Navigation devices

[![Build status][1]][2]

libskylark is a fast, simple, and minimal library for interfacing the
[Piksi GPS Receiver](http://swiftnav.com/piksi.html) with our external
networking services.

## Installation

Once you have the dependencies installed, create a build directory
where the library will be built:

```shell
mkdir build
cd build
```

Then invoke CMake to configure the build, and then build and install,

```shell
cmake ../
make
sudo make install
```

By default, libskylark will be built both as a shared library
`libskylark` and a static library `libskylark-static`. It will also
produce a binary `connect` intended to open a two-way data connection
to Swift's networking services.

## Command Line Usage

To connect your devices to the

```shell
Usage: sky-connect <device-uid> <tty> <baudrate>
```

## Library Usage

## License

Copyright © 2016 Swift Navigation

Distributed under MIT License.

[1]: https://travis-ci.org/swift-nav/libskylark.png
[2]: https://travis-ci.org/swift-nav/libskylark
