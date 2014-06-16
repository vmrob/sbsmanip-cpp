README
======

Dependencies
------------

This library was built with Boost 1.55 and expects Boost headers and libraries to be accessible to the build system. Specifically, boost_filesystem (and thus boost_system) are required to build the unit tests. Building the library only requires Boost headers.

Building
--------

You'll need [Boost Build](https://github.com/boostorg/build) to actually build the project. Once you have Boost Build installed and accessible via your PATH, building should be as simple as running `b2` from the root directory.

    cd sbsmanip-cpp
    b2
