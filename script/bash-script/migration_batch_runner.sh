#!/bin/bash

help_message() {
    echo "Usage:"
    echo "./runner.sh [input_din_file] [run_prefix]"
}

if [ $# -lt 2 ]; then
    help_message
    exit
fi

INPUT_DIN=$1
RUN_PREFIX=$2

MIGRATION_EXECUTABLE=mpath_migration_m3_64

which ${MIGRATION_EXECUTABLE} 2>/dev/null

if [ $? -gt 0 ]; then
    echo "${MIGRATION_EXECUTABLE} not found. Add it to your PATH and try again"
    exit
fi

# DIN_DIR=${INPUT_DIN%/*}

# echo $DIN_DIR
#cd $DIN_DIR

GRDECL_FILES=($(ls $RUN_PREFIX*.GRDECL | grep -v COORD | grep -v ACTNUM | grep -v ZCORN))

DIN_FILE_NO_SUFFIX=${INPUT_DIN%.*}

for FILE in ${GRDECL_FILES[@]}; do
    FILE_NO_SUFFIX=${FILE%.*}

    # Handle the DIN file
    NEW_DIN_FILE=$FILE_NO_SUFFIX.din
    sed "s/${DIN_FILE_NO_SUFFIX}/${FILE_NO_SUFFIX}/" $INPUT_DIN > $NEW_DIN_FILE

    echo $NEW_DIN_FILE
    # ${MIGRATION_EXECUTABLE} $NEW_DIN_FILE

done
