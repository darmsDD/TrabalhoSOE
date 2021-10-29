#!/bin/sh

cd 
cd Documents/TrabalhoSOE/src
make clean
make
echo `date +"%T"` > compilado
exit 0