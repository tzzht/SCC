/**
 * @file merger.h
 * @author htzhu (htzhu@univista-isg.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef MERGE_H
#define MERGE_H

#include <vector>
#include <set>

#include "blif.h"
#include "aiger.h"

using namespace std;

aigerspace::Aiger merger(aigerspace::Aiger aiger1, aigerspace::Aiger aiger2);
aigerspace::Aiger aag_merge(aigerspace::Aiger aiger, aigerspace::Aiger dummy_aiger);
aigerspace::Aiger change_literal(aigerspace::Aiger aiger, int offset);
void process_constraints(aigerspace::Aiger &aiger);
#endif