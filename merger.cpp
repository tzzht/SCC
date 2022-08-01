/**
 * @file merger.cpp
 * @author htzhu (htzhu@univista-isg.com)
 * @brief
 *  Merge constraint, before.aag and after.aag.
 * @version 0.1
 * @date 2022-07-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "merger.h"

aigerspace::Aiger merger(aigerspace::Aiger aiger1, aigerspace::Aiger aiger2) {
    int offset = aiger1.get_max_var_idx_() * 2;
    aigerspace::Aiger dummy_aiger = change_literal(aiger2, offset);

    aigerspace::Aiger ret_aiger = aag_merge(aiger1, dummy_aiger);
    
    process_constraints(ret_aiger);

    return ret_aiger;

}

void process_constraints(aigerspace::Aiger &aiger)
{
    // By default, first input is clk
    // (pre_clk xor clk) -> (pre_input xnor input) 和 (pre_input xor input) -> (pre_clk xnor clk)
    vector<aigerspace::VarLiteral> inputs = aiger.get_inputs_();
    string clk = inputs[0].variable;
    int clk_literal = aiger.get_literal(clk);
    int pre_clk_literal = aiger.get_literal("pre_" + clk);
    int pre_clk_xor_clk_literal = aiger.add_xor(pre_clk_literal, clk_literal);
    int pre_clk_xnor_clk_literal = aiger.add_xnor(pre_clk_literal, clk_literal);


    int all_pre_inputs_xnor_inputs_and = 1;
    int all_pre_inputs_xor_inputs_or = 1;
    for(int i = 1; i < inputs.size(); i ++)
    {
        string input = inputs[i].variable;
        int input_literal = aiger.get_literal(input);
        int pre_input_literal = aiger.get_literal("pre_" + input);
        int pre_input_xor_input_literal = aiger.add_xor(pre_input_literal, input_literal);
        int pre_input_xnor_input_literal = aiger.add_xnor(pre_input_literal, input_literal);
        all_pre_inputs_xnor_inputs_and = aiger.add_andgate(all_pre_inputs_xnor_inputs_and, pre_input_xnor_input_literal);
        all_pre_inputs_xor_inputs_or = aiger.add_or(all_pre_inputs_xor_inputs_or, pre_input_xor_input_literal);
    }

    int constraint1 = aiger.add_imply(pre_clk_xor_clk_literal, all_pre_inputs_xnor_inputs_and);
    int constraint2 = aiger.add_imply(all_pre_inputs_xor_inputs_or, pre_clk_xnor_clk_literal);

    aiger.add_constraint(constraint1);
    aiger.add_constraint(constraint2);
}


aigerspace::Aiger change_literal(aigerspace::Aiger aiger, int offset) {
    aigerspace::Aiger ret_aiger;
    // literals that don't change
    set<int> remains;
    vector<aigerspace::VarLiteral> inputs = aiger.get_inputs_();
    for (int i = 0; i < inputs.size(); i++) {
        remains.insert(inputs[i].literal);
        remains.insert(aigerspace::get_negation(inputs[i].literal));
    }
    remains.insert(0);
    remains.insert(1);

    int max_var_idx = aiger.get_max_var_idx_() + offset / 2;
    ret_aiger.set_max_var_idx_(max_var_idx);

    ret_aiger.set_inputs_(aiger.get_inputs_());

    map<string, int> var_literal_map_original = aiger.get_var_literal_map_();
    map<string, int> var_literal_map;
    for (auto &it : var_literal_map_original) {
        int literal = it.second;
        if (remains.count(literal) == 0) {
            var_literal_map["duplicate_" + it.first] = it.second + offset;
        }
    }
    ret_aiger.set_var_literal_map_(var_literal_map);

    std::vector<aigerspace::Latch> latches = aiger.get_latches_();
    for (auto &it : latches) {
        it.variable = "duplicate_" + it.variable;
        it.current_state += offset;
        if (remains.count(it.next_state) == 0)
            it.next_state += offset;
    }
    ret_aiger.set_latches_(latches);

    std::vector<aigerspace::VarLiteral> outputs = aiger.get_outputs_();
    for (auto &it : outputs) {
        it.variable = "duplicate_" + it.variable;
        if (remains.count(it.literal) == 0)
            it.literal += offset;
    }
    ret_aiger.set_outputs_(outputs);

    std::vector<aigerspace::AndGate> andgates = aiger.get_andgates_();
    for (auto &it : andgates) {
        if (remains.count(it.lhs) == 0)
            it.lhs += offset;

        if (remains.count(it.rhs1) == 0)
            it.rhs1 += offset;

        if (remains.count(it.rhs2) == 0)
            it.rhs2 += offset;
    }
    ret_aiger.set_andgates_(andgates);
    return ret_aiger;
}

aigerspace::Aiger aag_merge(aigerspace::Aiger aiger, aigerspace::Aiger dummy_aiger)
{
    aigerspace::Aiger ret_aiger;

    ret_aiger.set_var_literal_map_(aiger.get_var_literal_map_());

    ret_aiger.set_max_var_idx_(dummy_aiger.get_max_var_idx_());

    ret_aiger.set_inputs_(aiger.get_inputs_());

    std::vector<aigerspace::Latch> latches = aiger.get_latches_();
    std::vector<aigerspace::Latch> tmp_latches = dummy_aiger.get_latches_();
    latches.insert(latches.end(), tmp_latches.begin(), tmp_latches.end());
    ret_aiger.set_latches_(latches);

    std::vector<aigerspace::AndGate> andgates = aiger.get_andgates_();
    std::vector<aigerspace::AndGate> tmp_andgates = dummy_aiger.get_andgates_();
    andgates.insert(andgates.end(), tmp_andgates.begin(), tmp_andgates.end());
    ret_aiger.set_andgates_(andgates);

    std::vector<aigerspace::VarLiteral> outputs = aiger.get_outputs_();
    std::vector<aigerspace::VarLiteral> tmp_outputs = dummy_aiger.get_outputs_();
    for(int i = 0; i < outputs.size(); i ++)
    {
        int literal1 = outputs[i].literal;
        int literal2 = tmp_outputs[i].literal;
        string variable = outputs[i].variable + " xor duplicate_" + tmp_outputs[i].variable;

        int literal = ret_aiger.add_xor(literal1, literal2);

        ret_aiger.add_output(variable, literal);
    }
    return ret_aiger;
}