#!/bin/bash

echo "Enter the range to find prime numbers: "
read range

echo "Prime numbers between 1 and $range:"

for ((i=2;i<=range;i++))
do
  count=0
  for ((j=1;j<=i;j++))
  do
    if ((i%j==0))
    then
      ((count++))
    fi
  done
  if ((count==2))
  then
    echo $i
  fi
done
