#!/usr/bin/env bash

if [ $# -eq 0 ]; then
    FILES=*.s
else
    FILES=$1/*.s
fi

if [ ! -f asmm ]; then
    echo "File asmm not found!"
    exit
fi

make -C ../asm
cp ../asm/asm ./asmm
make -C ../asm fclean

echo ""

for f in $FILES
do
    filename="${f%.*}"
    filename="$filename.cor"
    ( ./asmm $f > /dev/null 2>&1 &
    rm $filename > /dev/null 2>&1
    printf "%-30s: %s\n" "$f" "$(leaks $! | sed '19q;d')"
    kill $! );
done



#cat file
# file
#rm file

