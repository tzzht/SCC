#!/bin/bash
WORK_DIR=/home/tzzht/Documents/work/
source ${WORK_DIR}/shell
SCC -e ${WORK_DIR}/verilog/before_tck/dut_b.v ${WORK_DIR}/verilog/after_tck/dut_a.v ${WORK_DIR}
cat ${WORK_DIR}/report.txt

