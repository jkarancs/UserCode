#!/bin/sh
#
# first:
#
# source /afs/cern.ch/cms/LCG/LCG-2/UI/cms_ui_env.csh
# source /afs/cern.ch/cms/ccs/wm/scripts/Crab/crab.csh
# cmsenv

# run:
# 
# test/scripts/SubmitRA4.sh

# useage:
#
# test/scripts/inputFilesintoCFG.sh   name of the config and root file   dataset path
# test/scripts/makeCrabConfig.sh server_name pset total_number_of_events events_per_job output_file ce_white_list se_white_list


test/scripts/inputFilesintoCFG.sh LM0_RA4Synchronization /home/aranyi/CMSSW_2_2_9/data/LM0_dataset.txt
test/scripts/makeCrabConfig.sh crab_LM0.cfg test/LM0_RA4Synchronization_cfg_grid.py 202686 202686 LM0_RA4Synchronization.root grid107.kfki.hu
# max event: 202686
crab -cfg crab_LM0.cfg -create
crab -submit

test/scripts/inputFilesintoCFG.sh LM1_RA4Synchronization /home/aranyi/CMSSW_2_2_9/data/LM1_dataset.txt
test/scripts/makeCrabConfig.sh crab_LM1.cfg test/LM1_RA4Synchronization_cfg_grid.py 104800 104800 LM1_RA4Synchronization.root grid107.kfki.hu
# max event: 104800
crab -cfg crab_LM1.cfg -create
crab -submit

test/scripts/inputFilesintoCFG.sh TTbar_RA4Synchronization /home/aranyi/CMSSW_2_2_9/data/TTbar_dataset.txt
test/scripts/makeCrabConfig.sh crab_TTbar.cfg test/TTbar_RA4Synchronization_cfg_grid.py 200000 200000 TTbar_RA4Synchronization.root grid107.kfki.hu
# max event: 946644
crab -cfg crab_TTbar.cfg -create
crab -submit

test/scripts/inputFilesintoCFG.sh Wjets_1_RA4Synchronization /home/aranyi/CMSSW_2_2_9/data/Wjets_1_dataset.txt
test/scripts/makeCrabConfig.sh crab_Wjets_1.cfg test/Wjets_1_RA4Synchronization_cfg_grid.py 200000 200000 Wjets_1_RA4Synchronization.root grid107.kfki.hu
# max event: ~9745661/4
crab -cfg crab_Wjets_1.cfg -create
crab -submit

# test/scripts/inputFilesintoCFG.sh Wjets_2_RA4Synchronization /home/aranyi/CMSSW_2_2_9/data/Wjets_2_dataset.txt
# test/scripts/makeCrabConfig.sh crab_Wjets_2.cfg test/Wjets_2_RA4Synchronization_cfg_grid.py 200000 200000 Wjets_2_RA4Synchronization.root grid107.kfki.hu
# # max event: ~9745661/4
# crab -cfg crab_Wjets_2.cfg -create
# crab -submit
# 
# test/scripts/inputFilesintoCFG.sh Wjets_3_RA4Synchronization /home/aranyi/CMSSW_2_2_9/data/Wjets_3_dataset.txt
# test/scripts/makeCrabConfig.sh crab_Wjets_3.cfg test/Wjets_3_RA4Synchronization_cfg_grid.py 200000 200000 Wjets_3_RA4Synchronization.root grid107.kfki.hu
# # max event: ~9745661/4
# crab -cfg crab_Wjets_3.cfg -create
# crab -submit
# 
# test/scripts/inputFilesintoCFG.sh Wjets_4_RA4Synchronization /home/aranyi/CMSSW_2_2_9/data/Wjets_4_dataset.txt
# test/scripts/makeCrabConfig.sh crab_Wjets_4.cfg test/Wjets_4_RA4Synchronization_cfg_grid.py 200000 200000 Wjets_4_RA4Synchronization.root grid107.kfki.hu
# # max event: ~9745661/4
# crab -cfg crab_Wjets_4.cfg -create
# crab -submit

test/scripts/inputFilesintoCFG.sh Zjets_RA4Synchronization /home/aranyi/CMSSW_2_2_9/data/Zjets_dataset.txt
test/scripts/makeCrabConfig.sh crab_Zjets.cfg test/Zjets_RA4Synchronization_cfg_grid.py 200000 200000 Zjets_RA4Synchronization.root grid107.kfki.hu
# max event: 1262816
crab -cfg crab_Zjets.cfg -create
crab -submit