#!/bin/bash

skip=0
sum=0

while IFS= read -r line; do
        if [[ "$line" == "don't()" ]]; then
    skip=1
                echo "skipping\n"
    continue
  fi

  if [[ "$line" == "do()" ]]; then
    skip=0
                echo "end skipping\n"
    continue
  fi

  if [[ $skip -eq 0 && "$line" =~ mul\([0-9]+,[0-9]+\) ]]; then
    if [[ "$line" =~ mul\(([0-9]+),([0-9]+)\) ]]; then
      num1=${BASH_REMATCH[1]}
      num2=${BASH_REMATCH[2]}
      sum=$((sum + num1 * num2))
    fi
  fi
done

echo "Total sum: $sum"
