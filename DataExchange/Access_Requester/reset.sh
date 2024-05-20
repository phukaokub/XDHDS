#!/bin/bash

# Check if an argument is provided
if [ -z "$1" ]; then
  echo "Usage: $0 <total_files>"
  exit 1
fi

# Read the input to determine the total number of files
total_files=$1

# Loop through the numbers from 0 to total_files
for ((x=0; x<=total_files; x++)); do
  # Delete files in the current directory
  rm -f "decrypted_${x}.pdf"
  rm -f "${x}decrypted_key"

  # Delete files in the cpabe_keys folder
  rm -f "cpabe_keys/AR_repriv${x}"
  rm -f "cpabe_keys/AR_repriv${x}reencrypted_key.cpabe"
  rm -f "encrypted_${x}.cpabe"
done

echo "Files deleted successfully."