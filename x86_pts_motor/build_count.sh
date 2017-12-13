#!/bin/bash
cur=`cat $1`
let "new = cur + 1"
echo $new > "$1"
