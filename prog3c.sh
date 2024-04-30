#!/bin/bash

# Function to summarize a directory
summarize_dir() {
    # Check if the directory exists
    if [[ ! -d $1 ]]; then
        echo "Directory $1 does not exist."
        return 1
    fi

    # Initialize an associative array to store the count of each extension
    declare -A ext_counts

    # Iterate over the files in the directory and its subdirectories
    while IFS= read -r -d '' file; do
        # Increment the total number of files
        ((total_files++))

        # Get the extension of the file
        ext="${file##*.}"

        # Increment the count of this extension
        ((ext_counts[$ext]++))
    done < <(find "$1" -type f -print0)

    # Print the total number of files
    echo "Total number of files: $total_files"

    # Print the extensions and their counts
    echo "Extensions and their counts:"
    for ext in "${!ext_counts[@]}"; do
        echo "$ext: ${ext_counts[$ext]}"
    done
}

# Export the function so it can be used as a command
export -f summarize_dir
