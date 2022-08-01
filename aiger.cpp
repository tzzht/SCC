/**
 * @file aiger.cpp
 * @author htzhu (htzhu@univista-isg.com)
 * @brief
 *  Store aag.
 * @version 0.1
 * @date 2022-07-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "aiger.h"

namespace aigerspace {

/**
 * @brief Determine if the variable has been stored in var_literal_map_, if so, return true, otherwise return false.
 *
 * @param variable
 * @return true
 * @return false
 */
bool Aiger::has_literal(std::string variable) {
    if (var_literal_map_.find(variable) != var_literal_map_.end()) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Determine if the input has been stored, if so, return true, otherwise return false.
 *
 * @param variable
 * @return bool
 */
bool Aiger::has_input(int literal) {
    for (int i = 0; i < inputs_.size(); i++) {
        if (inputs_[i].literal == literal)
            return true;
    }
    return false;
}
/**
 * @brief Determine if the latch has been stored, if so, return true, otherwise return false.
 *
 * @param variable
 * @return bool
 */
bool Aiger::has_latch(int literal) {
    for (int i = 0; i < latches_.size(); i++) {
        if (latches_[i].current_state == literal)
            return true;
    }
    return false;
}
/**
 * @brief Determine if the output has been stored, if so, return true, otherwise return false.
 *
 * @param variable
 * @return bool
 */
bool Aiger::has_output(int literal) {
    for (int i = 0; i < outputs_.size(); i++) {
        if (outputs_[i].literal == literal)
            return true;
    }
    return false;
}

/**
 * @brief Determine if the andgate has been stored, if so, return true, otherwise return false.
 *
 * @param variable
 * @return bool
 */
bool Aiger::has_andgate(int literal) {
    for (int i = 0; i < andgates_.size(); i++) {
        if (andgates_[i].lhs == literal)
            return true;
    }
    return false;
}

/**
 * @brief if var_literal_map_ has this variable, return the variable's literal,
 * else error.
 * @param variable
 * @return int
 */
int Aiger::get_literal(std::string variable) {
    int literal;
    if (has_literal(variable) == true) {
        literal = var_literal_map_[variable];
        return literal;
    } else {
        std::cerr << "Fail to get_literal, no such variable: " << variable << std::endl;
        exit(1);
    }
}

Latch Aiger::get_latch(int literal) {
    if (has_latch(literal) == true) {
        Latch latch;
        for (int i = 0; i < latches_.size(); i++) {
            if (latches_[i].current_state == literal) {
                latch = latches_[i];
            }
        }
        return latch;
    } else {
        std::cerr << "latch " << literal << " is undefined!" << std::endl;
        exit(1);
    }
}
AndGate Aiger::get_andgate(int literal) {
    if (has_andgate(literal) == true) {
        AndGate andgate;
        for (int i = 0; i < andgates_.size(); i++) {
            if (andgates_[i].lhs == literal) {
                andgate = andgates_[i];
            }
        }
        return andgate;
    } else {
        std::cerr << "andgate " << literal << " is undefined!" << std::endl;
        exit(1);
    }
}

/**
 * @brief max_var_idx ++, return max_var_idx*2
 *
 * @return int
 */
int Aiger::new_literal() {
    max_var_idx_++;
    return max_var_idx_ * 2;
}

/**
 * @brief map this variable with (++ max_var_idx)*2 in var_literal_map_
 *
 * @param variable
 * @return int
 */
int Aiger::add_var(std::string variable) {
    if (has_literal(variable)) {
        std::clog << "add_var: " << variable << " is already added." << std::endl;
        return get_literal(variable);
    } else {
        int literal = new_literal();
        var_literal_map_[variable] = literal;
        std::clog << "add_var: " << variable << " " << literal << "." << std::endl;
        return literal;
    }
}

/**
 * @brief map this variable with (++ max_var_idx)*2 in var_literal_map_
 *
 * @param variable
 * @return int
 */
int Aiger::add_var(std::string variable, int literal) {
    if (has_literal(variable)) {
        int first_literal = get_literal(variable);
        if (first_literal == literal) {
            std::clog << "add_var: " << variable << " is already added." << std::endl;
            return first_literal;
        } else {
            std::cerr << "add_var: " << variable << " is redefined!" << std::endl;
            std::cerr << "first: " << first_literal << std::endl;
            std::cerr << "second: " << literal << std::endl;
            exit(1);
        }
    } else {
        var_literal_map_[variable] = literal;
        std::clog << "add_var: " << variable << " " << literal << "." << std::endl;
        return literal;
    }
}

/**
 * @brief Add an input variable (if this variable already exists, return its literal
 * @param variable
 * @return int
 */
int Aiger::add_input(std::string variable) {
    int literal = get_literal(variable);

    if (has_input(literal) == true) {
        std::clog << "input " << variable << " is already defined." << std::endl;
        std::clog << literal << std::endl;
    } else {
        VarLiteral input{literal, variable};
        inputs_.push_back(input);
        std::clog << "add_input: " << variable << " " << literal << "." << std::endl;
    }
    return literal;
}
/**
 * @brief Add a latch (if this latch already exists, return its literal)
 *
 * @param variable
 * @param next_state_literal
 * @param init_val
 * @return int
 */
int Aiger::add_latch(std::string variable, int next_state_literal, int init_val) {
    int literal = get_literal(variable);

    if (has_latch(literal) == true) {
        Latch latch = get_latch(literal);
        if (latch.next_state != next_state_literal) {
            std::cerr << "latch " << variable << " redefined!" << std::endl;
            std::cerr << "First: " << latch.current_state << " " << latch.next_state << " " << latch.init << std::endl;
            std::cerr << "Second: " << literal << " " << next_state_literal << " " << init_val << std::endl;
            exit(1);
        } else if (init_val != latch.init) {
            std::cerr << "latch " << variable << " redefined!" << std::endl;
            std::cerr << "First: "
                      << " " << latch.current_state << " " << latch.next_state << " " << latch.init << std::endl;
            std::cerr << "Second: "
                      << " " << literal << " " << next_state_literal << " " << init_val << std::endl;
            exit(1);
        } else {
            std::clog << "add_latch: " << variable << " is already defined." << std::endl;
            std::clog << latch.current_state << " " << latch.next_state << " " << latch.init << std::endl;
        }
    } else {
        literal = get_literal(variable);
        Latch latch{literal, next_state_literal, init_val, variable};
        std::clog << "add_latch: " << variable << " " << literal << std::endl;
        std::clog << latch.current_state << " " << latch.next_state << " " << latch.init << std::endl;
        latches_.push_back(latch);
    }
    return literal;
}

/**
 * @brief Add an output
 *
 * @param variable
 * @return int
 */
int Aiger::add_output(std::string variable) {
    int literal = get_literal(variable);

    if (has_output(literal) == true) {
        std::clog << "input " << variable << " is already defined." << std::endl;
        std::clog << literal << std::endl;
    } else {
        VarLiteral varliteral{literal, variable};
        outputs_.push_back(varliteral);
        std::clog << "add_output: " << variable << " " << literal << "." << std::endl;
    }
    return literal;
}

/**
 * @brief Add an output
 *
 * @param variable
 * @return int
 */
int Aiger::add_output(std::string variable, int literal) {
    VarLiteral varliteral{literal, variable};
    outputs_.push_back(varliteral);
    std::clog << "add_output: " << variable << " " << literal << "." << std::endl;
    return literal;
}

/**
 * @brief Add an andgate, its literal is max_var_idx*2. Return its literal.
 *
 * @param rhs1
 * @param rhs2
 * @return int
 */
int Aiger::add_andgate(int rhs1, int rhs2) {
    int literal = new_literal();
    AndGate andgate{literal, rhs1, rhs2};
    andgates_.push_back(andgate);
    std::clog << "add_andgate: " << literal << " " << rhs1 << " " << rhs2 << std::endl;
    return literal;
}
/**
 * @brief Add an andgate, its literal is lhs. Return its literal.
 *
 * @param lhs
 * @param rhs1
 * @param rhs2
 * @return int
 */
int Aiger::add_andgate(int lhs, int rhs1, int rhs2) {
    if (has_andgate(lhs)) {
        AndGate andgate = get_andgate(lhs);
        if (!(andgate.rhs1 == rhs1 && andgate.rhs2 == rhs2) && !(andgate.rhs1 == rhs2 && andgate.rhs2 == rhs1)) {
            std::cerr << "andgate " << lhs << " redefined!" << std::endl;
            std::cerr << "First: " << andgate.lhs << " " << andgate.rhs1 << " " << andgate.rhs2 << std::endl;
            std::cerr << "Second: " << lhs << " " << rhs1 << " " << rhs2 << std::endl;
            exit(1);
        } else {
            std::clog << "andgate " << lhs << " is already defined." << std::endl;
            std::clog << lhs << std::endl;
        }
    } else {
        AndGate andgate{lhs, rhs1, rhs2};
        andgates_.push_back(andgate);
        std::clog << "add_andgate: " << lhs << " " << rhs1 << " " << rhs2 << std::endl;
    }
    return lhs;
}

void Aiger::add_constraint(int constraint)
{
    constraints_.push_back(constraint);
    std::clog << "add_constraint: " << constraint << std::endl;
}

/**
 * @brief Add andgates to represent lhs -> rhs.
 *
 * @param lhs
 * @param rhs
 * @return int
 */
int Aiger::add_imply(int lhs, int rhs) {
    return add_or(get_negation(lhs), rhs);
    std::clog << "add_imply: " << lhs << " -> " << rhs << std::endl;
}

/**
 * @brief Add andgates to represent lhs | rhs.
 *
 * @param lhs
 * @param rhs
 * @return int
 */
int Aiger::add_or(int lhs, int rhs) {
    int literal = add_andgate(get_negation(lhs), get_negation(rhs));
    std::clog << "add_or: " << lhs << " or " << rhs << std::endl;
    return get_negation(literal);
}

/**
 * @brief Add andgates to represent (lhs & rhs) | (!lhs & !rhs).
 *
 * @param lhs
 * @param rhs
 * @return int
 */
int Aiger::add_xnor(int lhs, int rhs) {
    std::clog << "add_xnor: " << lhs << " xnor " << rhs << std::endl;
    return add_or(add_andgate(lhs, rhs), add_andgate(get_negation(lhs), get_negation(rhs)));
}
/**
 * @brief Add andgates to represent (lhs & !rhs) | (!lhs & rhs).
 *
 * @param lhs
 * @param rhs
 * @return int
 */
int Aiger::add_xor(int lhs, int rhs) {
    std::clog << "add_xor: " << lhs << " xnor " << rhs << std::endl;
    return add_or(add_andgate(get_negation(lhs), rhs), add_andgate(lhs, get_negation(rhs)));
}

/**
 * @brief pre_var = (first_cycle -> var) & (!first_cycle -> pre(var))
 *
 * @param variable
 * @return int
 */
int Aiger::add_pre(std::string variable) {
    std::string pre_var = "pre_" + variable;
    std::string pre_func_var = "pre_func_" + variable;
    int pre_var_literal = get_literal(pre_var);
    int first_cycle_literal = get_literal("first_cycle");

    if (has_andgate(pre_var_literal) == true) {
        std::clog << "pre_" << variable << " is already defined." << std::endl;
    } else {
        int var_literal = get_literal(variable);
        // we don't care first cycle pre_var_func value
        int pre_var_func_literal = add_latch(pre_func_var, var_literal, 0);
        // pre_var = (first_cycle -> var) & (!first_cycle -> pre(var))
        add_andgate(pre_var_literal, add_imply(first_cycle_literal, var_literal), add_imply(get_negation(first_cycle_literal), pre_var_func_literal));
    }
    return pre_var_literal;
}

void Aiger::write_aiger(std::string output_path) {
    std::ofstream aag_file;
    aag_file.open(output_path.c_str());
    if (aag_file.is_open()) {
        aag_file << "aag" << ' ' << max_var_idx_ << ' ' << inputs_.size() << ' ' << latches_.size() << ' ' << outputs_.size() << ' ' << andgates_.size() << ' ' << num_bad_states_ << ' ' << constraints_.size() << std::endl;
        for (int i = 0; i < inputs_.size(); i++) {
            aag_file << inputs_[i].literal << std::endl;
        }

        for (int i = 0; i < latches_.size(); i++) {
            Latch latch = latches_[i];
            aag_file << latch.current_state << ' ' << latch.next_state << ' ' << latch.init << std::endl;
        }

        for (int i = 0; i < outputs_.size(); i++) {
            aag_file << outputs_[i].literal << std::endl;
        }

        for(auto it : constraints_)
        {
            aag_file << it << std::endl;
        }

        for (int i = 0; i < andgates_.size(); i++) {
            AndGate andgate = andgates_[i];
            aag_file << andgate.lhs << ' ' << andgate.rhs1 << ' ' << andgate.rhs2 << std::endl;
        }

        for (int i = 0; i < inputs_.size(); i++) {
            aag_file << "i" << i << ' ' << inputs_[i].variable << std::endl;
        }

        for (int i = 0; i < latches_.size(); i++) {
            aag_file << "l" << i << ' ' << latches_[i].variable << std::endl;
        }

        for (int i = 0; i < outputs_.size(); i++) {
            aag_file << "o" << i << ' ' << outputs_[i].variable << std::endl;
        }

        aag_file << "c" << std::endl;
        for (auto it = var_literal_map_.begin(); it != var_literal_map_.end(); it++) {
            aag_file << it->first << ' ' << it->second << std::endl;
        }
    } else {
        std::cerr << "Failed to create aag file." << std::endl;
        exit(1);
    }
    aag_file.close();
}

/**
 * @brief Get negation of a literal
 *
 */
int get_negation(int literal) {
    if (literal < 0) {
        std::cerr << "Fail to get_negation of " << literal << std::endl;
    }
    if (literal % 2 == 0) {
        return literal + 1;
    } else {
        return literal - 1;
    }
}

}  // namespace aigerspace