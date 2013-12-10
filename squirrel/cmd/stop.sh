#!/bin/bash

rf=$(pwd)'/../'

if [ ! -f $rf'source/config/pids' ]; then
	for proc in `ps -ef | grep node | grep index.js | awk '{print $2}'`; do
		echo 'killing2 '$proc
		kill   $proc ; 
	done
else
	cat $rf'source/config/pids' | while read line; do
		echo 'killing1 '$line ;
		kill $line
	done
	rm -r $rf'source/config/pids'
fi