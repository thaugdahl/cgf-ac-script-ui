#!/bin/bash

ROOT_DIR=$(realpath $(dirname $(readlink -f $0)))
echo $ROOT_DIR

export PATH=${PATH}:${ROOT_DIR}
