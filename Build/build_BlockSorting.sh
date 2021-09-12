#!/bin/bash

cd `dirname $0`

# 名前を分解してbuildcommon.shに引数を渡す
name=$(basename $0 | sed 's/\.[^\.]*$//')
IFS=_ read -ra ARR <<< "${name}"
./common.sh ${ARR[1]}
