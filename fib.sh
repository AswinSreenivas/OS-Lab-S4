#!/bin/bash

echo "Enter the number of Fibonacci numbers to generate: "
read n

a=0
b=1

echo "Fibonacci sequence up to $n terms:"

for ((i=1;i<=n;i++))
do
  echo -n "$a "
  fn=$((a + b))
  a=$b
  b=$fn
done
echo
