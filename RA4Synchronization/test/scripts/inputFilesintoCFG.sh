#!/bin/bash 

#FILE="brr.cfg"

CFG="test/$1_cfg.py"
DATA=`cat $2`
TMP="tmp.cfg"
TMP3="tmp3.cfg"
TMP4="tmp4.cfg"

FILE=`echo $CFG | sed -e "s/.py/_grid.py/"`;

cat $2 \
| sed -e "1,1s/^/\\\/" | sed -e "s/'/\\\'/g" \
| sed -e "s:/:\\\/:g" | sed -e "/,/s/$/ \\\/"> $TMP

TMP2=`cat $TMP`

# cat $CFG \
# | sed -e "/file:/s/^/#/" | sed -e "/fileNames =/a $TMP2" > $FILE

cat $CFG \
| sed "/file:/d" | sed -e "/fileNames =/a $TMP2" > $TMP3

cat $TMP3 \
| sed "/input = cms.untracked.int32/d" | sed -e "/process.maxEvents = cms.untracked.PSet/a input = cms.untracked.int32(-1)" > $TMP4

cat $TMP4 \
| sed "/fileName = cms.string(/d" | sed -e "/process.TFileService = cms.Service/a fileName = cms.string('$1.root')"> $FILE

rm -f $TMP $TMP3 $TMP4 

echo "$FILE generated."


















