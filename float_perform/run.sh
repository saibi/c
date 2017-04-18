#!/bin/sh
if [ $# -ne 2 ]
then
	echo "$0 [program] [out.txt]"
	exit 0
fi

echo "time $1" >> $2
for i in 1 2 3 4 5 6 7 8 9 10
do
	/usr/bin/time -a -o $2 -f "user %U system %S elapsed %e" $1 
done

echo >> $2
