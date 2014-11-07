#!/bin/bash
cd hashlib2plus/trunk/src/
make clean
rm libhl++.a 
cd ../../..
cd src
make clean
rm dupdirs
rm -rf dupdirs.app
