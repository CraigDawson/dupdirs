#!/bin/bash
cd hashlib2plus/trunk/src/
make
cd ../../..
cd src
qmake
make
if [ "$(uname)" == "Darwin" ]; then
    open dupdirs.app --args $PWD/../tests/root1 $PWD/../tests/root3
    open dupdirs.app --args $PWD/../tests/root1 $PWD/../tests/root2
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    ./dupdirs ../tests/root1 ../tests/root3
    ./dupdirs ../tests/root1 ../tests/root2
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ]; then
    echo MS Windows not currently supported
fi

