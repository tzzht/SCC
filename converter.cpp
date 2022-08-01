/**
 * @file converter.cpp
 * @author htzhu (htzhu@univista-isg.com)
 * @brief
 *  1.convert class Blif to equivalent class Aag.
 * @version 0.1
 * @date 2022-07-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "converter.h"

aigerspace::Aiger converter(blifspace::Blif blif) {
    aigerspace::Aiger aiger;

    process_variables(aiger, blif);

    process_inputs(aiger, blif.get_inputs());

    process_latches(aiger, blif.get_all_latch());

    process_names(aiger, blif.get_all_names());
    
    process_outputs(aiger, blif.get_outputs());

    return aiger;
}

void process_variables(aigerspace::Aiger &aiger, blifspace::Blif blif) {
    vector<string> inputs = blif.get_inputs();
    vector<blifspace::Latch> all_latches = blif.get_all_latch();
    vector<string> outputs = blif.get_outputs();

    for (auto &it : inputs) {
        aiger.add_var(it);
        aiger.add_var("pre_" + it);
        aiger.add_var("pre_func_" + it);
    }

    aiger.add_var("first_cycle");
    aiger.add_var("$true", 1);
    aiger.add_var("$false", 0);
    aiger.add_var("$undef", 0);

    for (auto &it : all_latches) {
        aiger.add_var(it.output);
        aiger.add_var(it.control);
        aiger.add_var("pre_" + it.control);
        aiger.add_var("pre_func_" + it.control);
        aiger.add_var(it.input);
    }

    for (auto &it : outputs) {
        aiger.add_var(it);
    }


    vector<blifspace::Names> all_names = blif.get_all_names();
    for (auto &it : all_names) {
        // Handle the case where the variable is defined as true or false first to prevent it from being redefined as 0 or 1 after a literal has already been assigned.
        if (blifspace::names_is_true(it)) {
            aiger.add_var(it.output, 1);
        } else if (blifspace::names_is_false(it)) {
            aiger.add_var(it.output, 0);
        } else {
            aiger.add_var(it.output);
        }
    }

    int first_cycle_literal = aiger.add_latch("first_cycle", 0, 1);

    // pre_input = (first_cycle -> input) & (!first_cycle -> pre(input))
    for (auto &it : inputs) {
        aiger.add_pre(it);
    }

    for(auto &it : all_latches)
    {
        if(it.control != "")
            aiger.add_pre(it.control);
    }

}

/**
 * @brief process .inputs.
 * @param all_blif_inputs
 */
void process_inputs(aigerspace::Aiger &aiger, vector<string> all_blif_inputs) {
    for (auto &it : all_blif_inputs) {
        aiger.add_input(it);
    }
}

/**
 * @brief process .latch.
 * output = (type_clk -> pre_input) & (!type_clk -> pre_output)
 * @param all_blif_inputs
 */
void process_latches(aigerspace::Aiger &aiger, vector<blifspace::Latch> all_blif_latches) {
    int first_cycle_literal = aiger.get_literal("first_cycle");

    for (int i = 0; i < all_blif_latches.size(); i++) {
        blifspace::Latch blif_latch = all_blif_latches[i];
        string latch_input = blif_latch.input;
        string latch_output = blif_latch.output;
        blifspace::LatchType latch_type = blif_latch.type;
        string latch_clock = blif_latch.control;
        int latch_init;
        if (blif_latch.init == blifspace::LogicValue::TRUE) {
            latch_init = 1;
        } else if (blif_latch.init == blifspace::LogicValue::FALSE) {
            latch_init = 0;
        } else {
            cerr << "latch " << latch_output << " init value undefined!" << endl;
            exit(1);
        }

        if(latch_type == blifspace::LatchType::UNSPECIFIED)
        {
            int blif_input_literal = aiger.get_literal(latch_input);
            int blif_output_literal = aiger.get_literal(latch_output);
            aiger.add_latch(latch_output, blif_input_literal, latch_init);
        }
        else
        {

            // type_clk
            int type_clk_literal = type_clock(aiger, latch_clock, latch_type, first_cycle_literal);
            // blif_input
            int input_literal = aiger.get_literal(latch_input);
            // blif_output
            int output_literal = aiger.get_literal(latch_output);
            // input out1 ah clk 1
            // input out2 ah clk 0?
            // input1 out1 re clk 0
            // input2 out2 re out1 0
            // pre_blif_input
            // int pre_input_literal = aiger.get_literal("pre_" + latch_input);
            // if(aiger.has_andgate(pre_input_literal) == false)
            // {
            //     aiger.add_latch("pre_" + latch_input, input_literal, 0);
            // }
            // // pre_blif_output
            // int pre_output_literal = aiger.get_literal("pre_" + latch_output);
            // if(aiger.has_andgate(pre_output_literal) == false)
            // {
            //     aiger.add_latch("pre_" + latch_output, output_literal, 0);
            // }

            string pre_input_for_this_latch = "pre_" + latch_output + "_" + latch_input; 
            int pre_input_for_this_latch_literal = aiger.add_var(pre_input_for_this_latch);
            aiger.add_latch(pre_input_for_this_latch, input_literal, latch_init);

            string pre_output_for_this_latch = "pre_" + latch_output + "_" + latch_output; 
            int pre_output_for_this_latch_literal = aiger.add_var(pre_output_for_this_latch);
            aiger.add_latch(pre_output_for_this_latch, output_literal, latch_init);

            // (type_clk -> pre_blif_input)
            int branch_if_literal = aiger.add_imply(type_clk_literal, pre_input_for_this_latch_literal);
            // (!type_clk -> pre_blif_output)
            int branch_else_literal = aiger.add_imply(aigerspace::get_negation(type_clk_literal), pre_output_for_this_latch_literal);

            // blif_output = (type_clk -> pre_blif_input) & (!type_clk -> pre_blif_output)
            // blif_output = (!type_clk | pre_blif_input) & (type_clk | pre_blif_output)
            // blif_output = !(type_clk & pre_blif_input) & !(!type_clk & pre_blif_output)
            aiger.add_andgate(output_literal, branch_if_literal, branch_else_literal);
        }
    }
}

/**
 * @brief process all .names
 *
 * @param all_blif_names
 */
//
void process_names(aigerspace::Aiger &aiger, vector<blifspace::Names> all_blif_names) {
    for (int i = 0; i < all_blif_names.size(); i++) {
        blifspace::Names names = all_blif_names[i];
        if (blifspace::names_is_false(names) || blifspace::names_is_true(names)) {
            continue;
        } else {
            vector<string> inputs = names.inpus;
            string output = names.output;
            vector<vector<blifspace::LogicValue>> so_cover = names.so_cover;

            vector<int> literal_array = get_literal_array(aiger, inputs);

            int output_literal = aiger.get_literal(output);

            int processed_row_literal = trans_a_row(aiger, so_cover[0], literal_array);
            int row_literal;
            for (int j = 1; j < so_cover.size(); j++) {
                row_literal = trans_a_row(aiger, so_cover[j], literal_array);
                processed_row_literal = aiger.add_or(processed_row_literal, row_literal);
            }
            aiger.add_andgate(output_literal, 1, processed_row_literal);
        }
    }
}

/**
 * @brief process outputs
 *
 * @param all_blif_outputs
 */
void process_outputs(aigerspace::Aiger &aiger, vector<string> all_blif_outputs) {
    for (int i = 0; i < all_blif_outputs.size(); i++) {
        aiger.add_output(all_blif_outputs[i]);
    }
}

/**
 * @brief type(clock) function
 *
 * @param clk
 * @param type_clk
 * @return int
 */
int type_clock(aigerspace::Aiger &aiger, string clk, blifspace::LatchType type_clk, int first_cycle_literal) {
    if (type_clk == blifspace::LatchType::RISING_EDGE) {
        int pre_clk_literal = aiger.add_pre(clk);
        int clk_literal = aiger.get_literal(clk);
        // !pre_clk & clk
        return aiger.add_andgate(aigerspace::get_negation(pre_clk_literal), clk_literal);
    } else if (type_clk == blifspace::LatchType::FALLING_EDGE) {
        int pre_clk_literal = aiger.add_pre(clk);
        int clk_literal = aiger.get_literal(clk);
        // pre_clk & !clk
        return aiger.add_andgate(pre_clk_literal, aigerspace::get_negation(clk_literal));
    } else if (type_clk == blifspace::LatchType::ACTIVE_HIGH) {
        int clk_literal = aiger.get_literal(clk);
        return clk_literal;
    } else if (type_clk == blifspace::LatchType::ACTIVE_LOW) {
        int clk_literal = aiger.get_literal(clk);
        return aigerspace::get_negation(clk_literal);
    } else {
        cerr << "Cannot handle ASYNCHRONOUS latch type!" << endl;
        exit(1);
    }
}

/**
 * @brief get the literal array of variables array.
 *
 * @param variables
 * @return vector<int>
 */
vector<int> get_literal_array(aigerspace::Aiger &aiger, vector<string> variables) {
    vector<int> literal_array;

    for (int i = 0; i < variables.size(); i++) {
        literal_array.push_back(aiger.get_literal(variables[i]));
    }
    return literal_array;
}

/**
 * @brief transfer a row of so_cover into andgate
 *
 * @param a_row
 * @param literal_array
 * @return int
 */
int trans_a_row(aigerspace::Aiger &aiger, vector<blifspace::LogicValue> a_row, vector<int> literal_array) {
    string logic_str = blifspace::get_logic_str(a_row);
    int processed_literal = 1;
    for (int i = 0; i < logic_str.size(); i++) {
        if (logic_str[i] == '0') {
            processed_literal = aiger.add_andgate(processed_literal, aigerspace::get_negation(literal_array[i]));
        } else if (logic_str[i] == '1') {
            processed_literal = aiger.add_andgate(processed_literal, literal_array[i]);
        } else {
            // case '-'
        }
    }
    return processed_literal;
}