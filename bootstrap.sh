#!/bin/bash -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

(
	cd "$DIR/deps/boost"

	./bootstrap.sh
	./b2 --build-dir="$DIR/temp/boost/" --prefix="$DIR/deps/" --variant=release --link=static --runtime-link=static --with-program_options --with-filesystem install
)