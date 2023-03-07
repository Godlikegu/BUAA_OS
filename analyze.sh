#!/bin/bash

if [ $# -eq 1 ];
then
   grep -E "WARN|ERROR" $1 > bug.txt

else
    case $2 in
    "--latest")
    tail -n5 $1 

    ;;
    "--find")
       grep "$3" $1 > $3.txt 

    ;;
    "--diff")
        diff -q $1 $3;
	if [ $? -eq 0 ] 
		then 
		echo same
	fi
	if [ $? -ne 0 ]
		then 
		echo different
	fi
    ;;
    esac
fi
