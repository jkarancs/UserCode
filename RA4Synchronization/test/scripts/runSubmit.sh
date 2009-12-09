#!/bin/sh
#
# first:
#
# source /afs/cern.ch/cms/LCG/LCG-2/UI/cms_ui_env.csh
# source /afs/cern.ch/cms/ccs/wm/scripts/Crab/crab.csh
# cmsenv

# run:
#
# test/scripts/runSubmit.sh

# useage:
#
# test/scripts/inputFilesintoCFG.sh   name of the config and root file   dataset path
# test/scripts/makeCrabConfig.sh server_name pset total_number_of_events events_per_job output_file ce_white_list se_white_list

test/scripts/inputFilesintoCFG.sh LM0_RA4Synchronization /home/aranyi/CMSSW_2_2_9/data/LM0_dataset.txt
test/scripts/makeCrabConfig.sh crab_LM0.cfg test/LM0_RA4Synchronization_cfg_grid.py 100 100 LM0_RA4Synchronization.root grid107.kfki.hu

crab -cfg crab_LM0.cfg -create
crab -submit

