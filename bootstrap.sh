#!/bin/bash -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

(
	cd "$DIR/deps/curlpp-0.7.3"

	./configure --prefix="$DIR/deps"
	make all CXXFLAGS="-Wno-unused-function"
	make install
)