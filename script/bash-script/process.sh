#!/usr/bin/env bash

DEFAULT_IFS=$IFS

# The functionality is implemented in `functions.sh`
source functions.sh

# Show a help message if not enough arguments
if [ $# -lt 2 ]; then
    help_message
    exit
fi

# Read the arguments
INPUT_FILE=$1
OUTPUT_FILE=$2

# The File Suffix to handle
FILE_SUFFIX=".GRDECL"


# Modes:
# 0 = Single-File Mode
# 1 = Directory Mode
MODE=0

echo "Chosen input path: ${INPUT_FILE}"
echo "Chosen output path: ${OUTPUT_FILE}"

# - Checks existence of input file
# - Prompts the user for confirmation if about to overwrite output file.
# - Sets the mode based on whether INPUT_FILE is a directory
file_checks

# Reads patterns from `patterns.txt` file
read_patterns

# Copy .DIN and .PVT files
if [ $MODE -eq 1 ]; then
    COPY_FILES=($(ls ${INPUT_FILE} | grep -v -i .grdecl))
    printf "%s\n" ${COPY_FILES[@]} | xargs -I{} cp -r ${INPUT_FILE}/{} ${OUTPUT_FILE}
fi

# Default back to default patterns if read_patterns fails
if [ $result -eq 0 ]; then
    set_default_patterns
fi

if [ $MODE -eq 1 ]; then
    replace_entire_directory
else
    sed "${SED_PATTERN}" $INPUT_FILE > $OUTPUT_FILE
fi

# -------------- REPLACE PROCEDURE COMPLETED ---------------


