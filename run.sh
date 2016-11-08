#!/bin/bash
benchmark=("mcf" "leslie3d")
allocation1=("0x00008" "0x0000c" "0x0000e" "0x0000f")  
allocation2=("0x00001" "0x00003" "0x00007" "0x0000f")
  
len1=${#allocation1[@]}
len2=${#allocation2[@]}

for ((i=0;i<len1;i++));  
do  
  a1=(${allocation1[$i]}) 
  for ((j=0;j<len2;j++));  
  do  
    a2=(${allocation2[$j]})  
    command="./aet 1 ${benchmark[0]} ${a1} ${benchmark[1]} ${a2}"
    $command >> result.txt
  done  
done
