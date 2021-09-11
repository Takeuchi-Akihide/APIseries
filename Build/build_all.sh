#!/bin/bash

cd `dirname $0`

# APIseries下のディレクトリ名を取得
cd ../
dirs=`find -maxdepth 1 -type d | egrep -v "Build|git"`
# 各ディレクトリについてビルドを実行
for dir in $dirs;
do
    basedir=`basename $dir`
    if [ $basedir != "." ]; then
        echo $basedir
        cd ./Build
        ./buildcommon.sh $basedir
        cd -
    fi
done
