#!/bin/bash
#assoc-array.bash

declare -A user

user=(
		[ frodeh ]= " Frode Haug "
		[ ivarm ]= " Ivar Moe "
	 )
user[lailas]="Laila Skiaker"
echo "${user[ivarm]}" # print Ivar Moe
echo "${user[@]}" # print array values
echo "${!user[@]}" # print array indices ( keys )
echo "${#user[@]}" # length of array