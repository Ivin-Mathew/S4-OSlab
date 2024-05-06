#!/bin/bash
#QN 3 b
#Read data from csv file and display in table form
#Ivin Mathew S4 CSE B2 roll 33
file="$1"
IFS=','
[ ! -f "$file" ] && { echo "$file file not found"; exit 1; }
count=0
allPass=0
s1p=0
s2p=0
s3p=0
s4p=0
s5p=0
s6p=0
while IFS=, read -r id s1 s2 s3 s4 s5 s6; do
    if [[ "$id" == "id" ]]; then
        continue
    fi
    count=$((count + 1))
    temp=0
    if [[ $s1 -ge 50 ]]; then
        s1p=$((s1p + 1))
        temp=$((temp + 1))
    fi
    if [[ $s2 -ge 50 ]]; then
        s2p=$((s2p + 1))
        temp=$((temp + 1))
    fi
    if [[ $s3 -ge 50 ]]; then
        s3p=$((s3p + 1))
        temp=$((temp + 1))
    fi
    if [[ $s4 -ge 50 ]]; then
        s4p=$((s4p + 1))
        temp=$((temp + 1))
    fi
    if [[ $s5 -ge 50 ]]; then
        s5p=$((s5p + 1))
        temp=$((temp + 1))
    fi
    if [[ $s6 -ge 50 ]]; then
        s6p=$((s6p + 1))
        temp=$((temp + 1))
    fi
    if [[ $temp -eq 6 ]]; then
        allPass=$((allPass + 1))
    fi
done < "$file"

echo "Total students = $count"
echo "All pass = $allPass"
echo "Subject | Pass | Fail | Pass %"
echo "s1 | $s1p | $((count - s1p)) | $((count > 0 ? s1p * 100 / count : 0))"
echo "s2 | $s2p | $((count - s2p)) | $((count > 0 ? s2p * 100 / count : 0))"
echo "s3 | $s3p | $((count - s3p)) | $((count > 0 ? s3p * 100 / count : 0))"
echo "s4 | $s4p | $((count - s4p)) | $((count > 0 ? s4p * 100 / count : 0))"
echo "s5 | $s5p | $((count - s5p)) | $((count > 0 ? s5p * 100 / count : 0))"
echo "s6 | $s6p | $((count - s6p)) | $((count > 0 ? s6p * 100 / count : 0))"


