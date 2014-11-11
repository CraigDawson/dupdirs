# Makefile for DupDirs
# 2014-11-11

all:
	make -C hashlib2plus/trunk/src
	cd src; \
	qmake
	make -C src

doc:
	pandoc README.md -o README.pdf
	pandoc TODO.md -o TODO.pdf

clean:
	make -C hashlib2plus/trunk/src clean
	make -C src clean
