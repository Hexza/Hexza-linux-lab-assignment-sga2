#!/bin/bash
# Redirect all standard error output to a separate error log file
exec 2> error.log

# Create necessary directories
mkdir -p submissions backup

# Initialize counters
processed=0
backed_up=0
duplicates=0

# Associative array to store file hashes
declare -A file_hashes

echo "Starting submission processing..."

# Loop through all files in the submissions directory
for file in submissions/*; do
    if [ -f "$file" ]; then
        ((processed++))
        
        # Calculate the MD5 hash of the file to check its content
        hash=$(md5sum "$file" | awk '{print $1}')
        
        # Check if hash already exists in our array
        if [[ -n "${file_hashes[$hash]}" ]]; then
            echo "Duplicate found: $file"
            ((duplicates++))
        else
            # New unique file: record hash and backup
            file_hashes[$hash]=1
            cp "$file" backup/
            ((backed_up++))
        fi
    fi
done

# Generate the final report
echo "--- Processing Report ---" > report.txt
echo "Total Files Processed: $processed" >> report.txt
echo "Unique Files Backed Up: $backed_up" >> report.txt
echo "Duplicate Files Ignored: $duplicates" >> report.txt

cat report.txt
