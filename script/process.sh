#!/usr/bin/env bash

help_message() {
    echo "File Processor"
    echo "Usage: ./process.sh {input_file} {output_file}"
}

# Show a help message if not enough arguments
if [ $# -lt 2 ]; then
    help_message
    exit
fi

INPUT_FILE=$1
OUTPUT_FILE=$2

echo "Chosen input file: ${INPUT_FILE}"
echo "Chosen output file: ${OUTPUT_FILE}"

if [ ! -f ${INPUT_FILE} ]; then
    echo "${INPUT_FILE} not found. Aborting."
    exit
fi

if [ -f ${OUTPUT_FILE} ]; then
    echo "${OUTPUT_FILE} exists. Do you want to overwrite it? (y/n)"
    read ANSWER

    if [ ${ANSWER} != "y" ]; then
        echo "Aborting..."
        exit
    fi

    echo "You have chosen to overwrite ${OUTPUT_FILE}"
fi

PATTERNS_MATCH=("PCW" "PCH" "PCD")
PATTERNS_REPLACE=("Pth_x" "Pth_y" "Pth_z")

SED_PATTERN=

for x in $(seq 0 $((${#PATTERNS_MATCH[@]} - 1))); do
    SED_PATTERN="${SED_PATTERN};s/${PATTERNS_MATCH[$x]}/${PATTERNS_REPLACE[$x]}/"
    echo "Replacing ${PATTERNS_MATCH[$x]} with ${PATTERNS_REPLACE[$x]}"
done

sed "${SED_PATTERN}" $INPUT_FILE > $OUTPUT_FILE

