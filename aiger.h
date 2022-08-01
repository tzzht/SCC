/**
 * @file aiger.h
 * @author htzhu (htzhu@univista-isg.com)
 * @brief
 * @version 0.1
 * @date 2022-07-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef AIGER_H
#define AIGER_H

#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace aigerspace {

typedef struct VarLiteral {
    int literal;
    std::string variable;
} VarLiteral;

typedef struct Latch {
    int current_state;  // only unnegated literal allowed
    int next_state;
    int init;
    std::string variable;
} Latch;

typedef struct AndGate {
    int lhs;  // only unnegated literal allowed
    int rhs1;
    int rhs2;
} AndGate;

// store the aiger which is transfered from blif
class Aiger {
public:
    Aiger() : var_literal_map_(),
              max_var_idx_(0),  
              inputs_(),
              latches_(),
              outputs_(),
              andgates_(),
              num_bad_states_(0),
              constraints_() {}

    bool has_literal(std::string variable);
    bool has_input(int literal);
    bool has_latch(int literal);
    bool has_output(int literal);
    bool has_andgate(int literal);

    int get_literal(std::string variable);

    Latch get_latch(int literal);
    AndGate get_andgate(int litereal);

    int new_literal();
    int add_var(std::string variable);
    int add_var(std::string variable, int literal);
    int add_input(std::string variable);
    int add_latch(std::string variable, int next_state_literal, int init_val);
    int add_output(std::string variable);
    int add_output(std::string variable, int literal);
    int add_andgate(int rhs1, int rhs2);
    int add_andgate(int lhs, int rhs1, int rhs2);
    void add_constraint(int constraint);
    int add_imply(int lhs, int rhs);
    int add_or(int lhs, int rhs);
    int add_xnor(int lhs, int rhs);
    int add_xor(int lhs, int rhs);
    int add_pre(std::string variable);

    /*
     * Write functions
     */
    void write_aiger(std::string output_path);

    int get_max_var_idx_() { return max_var_idx_; }
    std::vector<VarLiteral> get_inputs_() { return inputs_; }
    std::vector<Latch> get_latches_() { return latches_; }
    std::vector<VarLiteral> get_outputs_() { return outputs_; }
    std::vector<AndGate> get_andgates_() { return andgates_; }
    std::map<std::string, int> get_var_literal_map_() { return var_literal_map_; }

    void set_max_var_idx_(int max_var_idx) { max_var_idx_ = max_var_idx; }
    void set_var_literal_map_(std::map<std::string, int> var_literal_map) { var_literal_map_ = var_literal_map; }
    void set_inputs_(std::vector<VarLiteral> inputs) { inputs_ = inputs; }
    void set_latches_(std::vector<Latch> latches) { latches_ = latches; }
    void set_outputs_(std::vector<VarLiteral> outputs) { outputs_ = outputs; }
    void set_andgates_(std::vector<AndGate> andgates) { andgates_ = andgates; }

private:
    std::map<std::string, int> var_literal_map_;  // mapping of variables to literal

    int max_var_idx_;

    std::vector<VarLiteral> inputs_;
    std::vector<Latch> latches_;
    std::vector<VarLiteral> outputs_;
    std::vector<AndGate> andgates_;

    int num_bad_states_;
    std::vector<int> constraints_;
};

int get_negation(int literal);

}  // namespace aigerspace

#endif