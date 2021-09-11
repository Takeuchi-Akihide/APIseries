#!/bin/bash

cd `dirname $0`

# 移動してmakeを実行
cd ../$1/src/

# resultディレクトリがある場合は削除し、再び作成
Destdir=../result/
rm -rf $Destdir
mkdir $Destdir

# makeを実行し、生成物をresultに移動
make
mv *.o ../result/

# resultに移動してresを実行し、res.txtに書き込む
cd ../result/
./res > ./res.txt
