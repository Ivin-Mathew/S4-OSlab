#!/bin/bash

INPUT=$1
count=0
pass=0

IFS=','
[ ! -f $INPUT ] && { echo "$INPUT file not found"; exit 99; }
while read id s1 s2 s3
do
  echo "Processing line: $id, $s1, $s2, $s3"
  
  if [ "$id" == "id" ]
  then
    continue
  fi
  
  echo "ID : $id"
  echo "s1 : $s1"
  echo "s2 : $s2"
  echo "s3 : $s3"
  echo ""
  
  count=$((count+1))
done < $INPUT

echo "Total lines processed: $count"
