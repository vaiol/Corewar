#!/bin/bash

if [ $# -eq 0 ]; then
    FILES=*.s
else
    FILES=$1/*.s
fi

if [ ! -f asm ]; then
    echo "File asm not found!"
    exit
fi

if [ ! -f asmm ]; then
    echo "File asmm not found!"
    exit
fi

for f in $FILES
do
    echo "Processing $f"
    ./asm $f > o.error
    ./asmm $f > m.error
    filename="${f%.*}"
    filename="$filename.cor"
    if [ "$(< o.error)" == "$(< m.error)" ]; then
        #echo "  -Messages are equal: '$(< o.error)'"
        message=$(< o.error)
        if [[ ${message:0:14} == "Writing output" ]]; then
            rm o.error m.error zi.res > /dev/null 2>&1
            ./asm $f > /dev/null 2>&1
            xxd $filename > o.error
            rm $filename
            ./asmm $f > /dev/null 2>&1
            xxd $filename > m.error
            rm $filename
            diff o.error m.error > zi.res
            cat zi.res
            rm o.error m.error zi.res
        fi
    else
        echo "  -Original: '$(< o.error)'"
        echo "  -My      : '$(< m.error)'"
        rm o.error m.error
    fi
done