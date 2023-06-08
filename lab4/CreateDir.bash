#!/bin/bash
#CreateDir.bash

if [[   "$#" -eq 1  ]]; then
	mkdir $1
	echo "Directory $1 created on $(date)" 
	
fi
