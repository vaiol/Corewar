#!/usr/bin/env bash
make -C ../asm
cp ../asm/asm ./asmm
make -C ../asm fclean
sh zi.sh champs