#!/usr/bin/bash

start_line=$1
end_line=$2
infile=$3
outfile=$4

# echo $infile, $outfile
sed -n  "$start_line,$end_line"'p' $infile  > $outfile
# awk 'NR>=206 && NR<=10501' '1630525642:25f627f4e8ed6760b4ceabf7c5ffbfdf.log.md' > samples/02.in 