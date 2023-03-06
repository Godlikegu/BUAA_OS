#!/bin/bash
#
mkdir mydir
chmod a+wrX mydir
echo 2023 > myfile
mv moveme mydir
cp copyme mydir
mv mydir/copyme mydir/copied
cat readme
gcc bad.c 2> err.txt

mkdir gen
a=1
if [ $# -eq 0 ] 
then 
	while [ $a -le 10 ]
	do
		touch $a.txt
		mv $a.txt gen
		let a=a+1
	done
fi

if [ $# -ne 0 ]
then 
	while [ $a -le $1 ]
	do
		touch $a.txt
		mv $a.txt gen
		let a=a+1
	done
fi


