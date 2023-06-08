# !/bin/bash
# array.bash
os=(' linux ' 'windows ')
os[2]=' mac '
echo "${os[1]} " # print windows
echo "${os[@]} " # print array values
echo "${!os[@]} " # print array indices
echo "${#os[@]} " # length of array