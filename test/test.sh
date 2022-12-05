#!/bin/sh

#  Script.sh
#  
#
#  Created by SleepyFish on 2022/11/23.
#

# define PATH
TEST_PATH="../../test"
DATA_PATH="../data"
RESULT_PATH="../result"
LOG_PATH="../log"
PLOT_PATH="../plot"

GenData_PATH="../Gen_Data/build"
NG_PATH="../Naive_Greedy/build"
LDG_PATH="../Linear_Deterministic_Greedy/build"
BLG_PATH="../Baseline_Greedy/build"

# compile and copy
cd ${GenData_PATH}
make
cd ${TEST_PATH}

cd ${NG_PATH}
make
cd ${TEST_PATH}

cd ${LDG_PATH}
make
cd ${TEST_PATH}

cd ${BLG_PATH}
make
cd ${TEST_PATH}

cp ${GenData_PATH}/GenData GenData
cp ${NG_PATH}/NG NG
cp ${LDG_PATH}/LDG LDG
cp ${BLG_PATH}/BLG BLG

# test
col=10
row=10
for((k=1;k<10;k++))
do
    base=0.1
    block_num=4
    random=$(echo "$base*$k" | bc -l)
    
    for((i=16;i<=16;i=i*2))
    do
        echo "********************** Test" `expr $col \* $i`*`expr $row \* $i` "**********************" > ${LOG_PATH}/test${k}_`expr $col \* $i`_`expr $row \* $i`.log
        echo "BLOCK_NUM = "${block_num}"    RANDOM = 0"${random} >> ${LOG_PATH}/test${k}_`expr $col \* $i`_`expr $row \* $i`.log
        for((j=1;j<=10;j++))
        do
            echo "--------------------------------------------------------" >> ${LOG_PATH}/test${k}_`expr $col \* $i`_`expr $row \* $i`.log
            echo "This is" $j "time(s)!"  >> ${LOG_PATH}/test${k}_`expr $col \* $i`_`expr $row \* $i`.log
            echo "--------------------------------------------------------" >> ${LOG_PATH}/test${k}_`expr $col \* $i`_`expr $row \* $i`.log
            ./GenData `expr $col \* $i` `expr $row \* $i` $random ${DATA_PATH}/data`expr $col \* $i`_`expr $row \* $i`.dat
            ./NG ${DATA_PATH}/data`expr $col \* $i`_`expr $row \* $i`.dat ${RESULT_PATH}/result_NG`expr $col \* $i`_`expr $row \* $i`.dat ${block_num} ${RESULT_PATH}/plot_NG${k}_`expr $col \* $i`_`expr $row \* $i`.dat >> ${LOG_PATH}/test${k}_`expr $col \* $i`_`expr $row \* $i`.log
            ./LDG ${DATA_PATH}/data`expr $col \* $i`_`expr $row \* $i`.dat ${RESULT_PATH}/result_LDG`expr $col \* $i`_`expr $row \* $i`.dat ${block_num} ${RESULT_PATH}/plot_LDG${k}_`expr $col \* $i`_`expr $row \* $i`.dat >> ${LOG_PATH}/test${k}_`expr $col \* $i`_`expr $row \* $i`.log
            ./BLG ${DATA_PATH}/data`expr $col \* $i`_`expr $row \* $i`.dat ${RESULT_PATH}/result_BLG`expr $col \* $i`_`expr $row \* $i`.dat ${block_num} ${RESULT_PATH}/plot_BLG${k}_`expr $col \* $i`_`expr $row \* $i`.dat >> ${LOG_PATH}/test${k}_`expr $col \* $i`_`expr $row \* $i`.log
        done
        echo "************************** END *************************" >> ${LOG_PATH}/test${k}_`expr $col \* $i`_`expr $row \* $i`.log
    done
done


# result analysis
