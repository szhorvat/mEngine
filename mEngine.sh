#!/bin/sh

MATLAB=/Applications/MATLAB_R2012b.app

export DYLD_LIBRARY_PATH=$MATLAB/bin/maci64:$DYLD_LIBRARY_PATH
export PATH=$MATLAB/bin:$PATH

./mEngine $@