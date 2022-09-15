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

which mpath_migration_m3 2>/dev/null

# if [ $? -gt 0 ]; then
#     echo "mpath_migration_m3 not found. Add it to your PATH and try again"
#     exit
# fi

DIN_DIR=${INPUT_DIN%/*}

cd $DIN_DIR

ls $RUN_PREFIX*
