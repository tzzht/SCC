/**
 * @file converter.h
 * @author htzhu (htzhu@univista-isg.com)
 * @brief
 * @version 0.1
 * @date 2022-07-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef CONVERT_H
#define CONVERT_H
#include "aiger.h"
#include "blif.h"

using namespace std;
aigerspace::Aiger converter(blifspace::Blif blif);

void process_variables(aigerspace::Aiger &aiger, blifspace::Blif blif);
void process_inputs(aigerspace::Aiger &aiger, vector<string> all_blif_inputs);
void process_latches(aigerspace::Aiger &aiger, vector<blifspace::Latch> all_blif_latches);
void process_names(aigerspace::Aiger &aiger, vector<blifspace::Names> all_blif_names);
void process_outputs(aigerspace::Aiger &aiger, vector<string> all_blif_outputs);

int type_clock(aigerspace::Aiger &aiger, string clk, blifspace::LatchType type_clk, int first_cycle_literal);

vector<int> get_literal_array(aigerspace::Aiger &aiger, vector<string> var_names);
int trans_a_row(aigerspace::Aiger &aiger, vector<blifspace::LogicValue> a_row, vector<int> literal_array);
#endif