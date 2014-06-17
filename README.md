README
======

Dependencies
------------

This library was built with Boost 1.55 and expects Boost headers and libraries to be accessible to the build system. Specifically, boost_filesystem (and thus boost_system) are required to build the unit tests. Building the library only requires Boost headers.

Curlpp 0.7.3 is also a dependency but is self-contained and will build using the supplied build scripts.

Building
--------

First, you'll need to build the self-contained dependencies. To do this, run the `bootstrap.sh` script:

    cd sbsmanip-cpp
    ./bootstrap.sh

You'll need [Boost Build](https://github.com/boostorg/build) to actually build the project. Once you have Boost Build installed and accessible via your PATH, building should be as simple as running `b2` from the root directory.

    cd sbsmanip-cpp
    b2
