mEngine
=======

Call MATLAB from Mathematica.

This is an updated version of Robert Zhang's mEngine from http://library.wolfram.com/infocenter/Demos/4821/

It works with OS X and 64 bit versions of MATLAB and Mathematica

Compiling
=========

First edit the Makefile and ensure that the paths to the Mathematica and MATLAB directories are correct for your machine

    cd mEngineSource
    make
    cp mEngine ..

Edit `mEngine.sh` and ensure that the path to your MATLAB installation is correct.

Test mEngine using the examples from `mEngine.nb`.

A precompiled binary for 64 bit OS X 10.6 or later is available [here](https://dl.dropbox.com/u/38623/mEngineBinary.zip).

**Important:** Do not forget to edit mEngine.sh and set the correct path to your MATLAB installation so mEngine can find the matlab executable!
