#!/bin/sh

TEMPLATE=test/scripts/crabConfigTemplate.cfg
FILE=$1
PSET=$2
TOT_NUM_EVENTS=$3
EVENTS_PER_JOB=$4
OUTPUT_FILE=$5
CE=$6

#SERVER_NAME=$1
#SE=$7

#FILE="crab_LM0.cfg";

cat $TEMPLATE \
| sed -e "s:template_pset:$PSET:" \
| sed -e "s/template_total_number_of_events/$TOT_NUM_EVENTS/" \
| sed -e "s/template_events_per_job/$EVENTS_PER_JOB/" \
| sed -e "s/template_output_file/$OUTPUT_FILE/" \
| sed -e "s/template_ce_white_list/$CE/" >$FILE

echo "$FILE generated."

#LM0_RA4Synchronization.root
#| sed -e "s/template_server_name/$SERVER_NAME/" \
#| sed -e "s/template_se_white_list/$SE/"  >$FILE