#!/bin/bash
#Qn 3c
#Count all files and file extensions
#Ivin Mathew S4 CSE B2 roll 33
#1/3/2024
summarize_dir() {
if [[ ! -d $1 ]]; then
echo "Directory $1 does not exist."
return 1
fi

declare -A ext_counts

while IFS= read -r -d '' file; do
((total_files++))
ext="${file##*.}"
((ext_counts[$ext]++)) 
done < <(find "$1" -type f -print0)
echo "Total number of files: $total_files"
echo "Extensions and their counts:"
for ext in "${!ext_counts[@]}"; do
echo "$ext: ${ext_counts[$ext]}"
done
}
summarize_dir $1

