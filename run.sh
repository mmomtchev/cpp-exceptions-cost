#!/bin/bash

for TEST in test-*; do
  if [ -f ${TEST} ]; then
    SIZE=0
    for SYM in `nm --print-size ${TEST} | grep fibonacci | cut -f 2 -d " "`; do
      SIZE=$(( ${SIZE} + 0x${SYM} ))
    done
    echo -ne "${TEST}\t${SIZE} bytes\t"
    /usr/bin/time -f %U ./${TEST}
  fi
done
