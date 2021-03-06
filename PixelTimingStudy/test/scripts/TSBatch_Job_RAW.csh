#!/bin/tcsh
##########################################################################
# Script to run TimingStudy on RAW data on an lxbatch node.
# It runs a cmsRun on a specified file and moves the output to EOS:
# /store/caf/user/<username>/...
# Make sure to modify USERDIR (and OUTDIR, TSBatch.csh does it automatically)
# on the bottom of the script
#
# Default settings:
# INCOMPLETE, SPLIT 1, Nstrip > 0
#
# Usage:
# source TS_BatchJob_RAW.csh [CMSSW version] [GlobalTag] [job number] [/store/...] [Nevent = -1]
# example:
# source TS_BatchJob_RAW.csh CMSSW_5_2_3_patch1 GR_R_52_V7 0001 /store/...
##########################################################################
echo
echo "--------------------------------------------------------------------------------"
echo "--------------------------------------------------------------------------------"
echo "                          Creating JOB ["$3"]"
echo

source ${VO_CMS_SW_DIR}/cmsset_default.csh
if ( $1 =~ "CMSSW_5_"* ) then
    if ( $1 =~ "CMSSW_5_0_"* ) then
	setenv SCRAM_ARCH slc5_amd64_gcc434
    endif
else
    setenv SCRAM_ARCH slc5_amd64_gcc434
endif
cmsrel $1
cd $1/src
cmsenv
mkdir DPGAnalysis
cd DPGAnalysis
cvs co -d PixelTimingStudy UserCode/Debrecen/PixelTimingStudy
cd PixelTimingStudy/

# Set Job Number for output
sed -i "s;MB_RAW.root;MB_RAW_"$3".root;" test/MB_RAW_cfg.py

# Set SPLIT mode, number of strip hits stored (current: INCOMPLETE, SPLIT 1, Nstrip>0)
#sed -i "s;#define SPLIT 1;#define SPLIT 2;" plugins/TimingStudy.cc
sed -i "s;#minNStripHits = cms.int32(0),;minNStripHits = cms.int32(0),;" test/MB_RAW_cfg.py

#revert TimingStudy version to a previos one (eg for scans: v3029):
#cvs update -r 1.30 plugins/TimingStudy.cc
#cvs update -r 1.29 plugins/TimingStudy.h

# GlobalTag
sed -i "s;GR_R_53_V9F;"$2";" test/MB_RAW_cfg.py

# Input file:
sed -i "s;/store/data/Run2012B/MinimumBias/RAW/v1/000/193/786/B6532FB4-F999-E111-A81A-E0CB4E4408E7.root;"$4";" test/MB_RAW_cfg.py

# Set Number of Events if specified (all by default)
if ( $5 ) then
    sed -i "s;input = cms.untracked.int32(10);input = cms.untracked.int32("$5");" test/MB_RAW_cfg.py
else
    sed -i "s;input = cms.untracked.int32(10);input = cms.untracked.int32(-1);" test/MB_RAW_cfg.py
endif

echo
echo "--------------------------------------------------------------------------------"
echo "                                JOB ["$3"] ready"
echo "                                  Compiling..."
echo

cmsenv
scram b
echo
echo "--------------------------------------------------------------------------------"
echo "                                 Compiling ready"
echo "                               Starting JOB ["$3"]"
echo

cmsRun test/MB_RAW_cfg.py

echo
echo "--------------------------------------------------------------------------------"
echo "                               JOB ["$3"] Finished"
echo "                            Writing output to EOS..."
echo

# Copy to Eos
set USERDIR = "jkarancs/crab"
set OUTDIR = "outdir"
cmsLs /store/caf/user/$USERDIR | grep $OUTDIR > ! checkdir.txt
if ( -z checkdir.txt ) then
    cmsMkdir /store/caf/user/$USERDIR/$OUTDIR
    echo "Created directory on EOS"
endif
rm checkdir.txt

cmsStage MB_RAW_$3.root /store/caf/user/$USERDIR/$OUTDIR

echo
echo "Output: "
cmsLs /store/caf/user/$USERDIR/$OUTDIR/MB_RAW_$3.root

cd ../../../..
rm -r $1

echo
echo "--------------------------------------------------------------------------------"
echo "                                 JOB ["$3"] DONE"
echo "--------------------------------------------------------------------------------"
echo "--------------------------------------------------------------------------------"



