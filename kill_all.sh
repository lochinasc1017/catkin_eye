#!/bin/bash


IDs=`ps -ef | grep "bash" | awk '{print $2}'`

for id in $IDs
do
    kill -9 $id
done
