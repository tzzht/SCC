/**
 * @file blif.h
 * @author htzhu (htzhu@univista-isg.com)
 * @brief
 * @version 0.1
 * @date 2022-07-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef BLIF_H
#define BLIF_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>

namespace blifspace
{
    /*
     * Enumerations
     */
    enum class LogicValue
    {
        FALSE = 0, // Logic zero
        TRUE = 1,  // Logic one
        DONT_CARE  // Don't care
    };

    enum class LatchType
    {
        FALLING_EDGE,
        RISING_EDGE,
        ACTIVE_HIGH,
        ACTIVE_LOW,
        ASYNCHRONOUS,
        UNSPECIFIED // If no type is specified
    };

    /*
     * Function Declarations
     */

    typedef struct Names
    {
        std::vector<std::string> inpus;
        std::string output;
        std::vector<std::vector<LogicValue>> so_cover;
    } Names;

    typedef struct Latch
    {
        std::string input;
        std::string output;
        LatchType type;
        std::string control;
        LogicValue init;
    } Latch;

    // class to store blif
    class Blif
    {
    public:
        Blif() : model_name_(),
                 inputs_(),
                 outputs_(),
                 all_names_(),
                 all_latch_() {}

        void set_model(std::string model_name);
        void add_inputs(std::string inputs);
        void add_outputs(std::string outputs);
        void add_names(std::vector<std::string> inputs, std::string output, std::vector<std::vector<LogicValue>> so_cover);
        void add_latch(std::string input, std::string output, LatchType type, std::string control, LogicValue init);
        void write_blif(std::string output_path);

    
        std::string get_model_name_() { return model_name_; }
        std::vector<std::string> get_inputs() { return inputs_; }
        std::vector<std::string> get_outputs() { return outputs_; }
        std::vector<Names> get_all_names() { return all_names_; }
        std::vector<Latch> get_all_latch() { return all_latch_; }

    private:
        std::string model_name_;
        std::vector<std::string> inputs_;
        std::vector<std::string> outputs_;
        std::vector<Names> all_names_;
        std::vector<Latch> all_latch_;
    };

    bool names_is_true(Names names);
    bool names_is_false(Names names);
    std::string get_type_str(LatchType type);
    std::string get_logic_str(LogicValue v);
    std::string get_logic_str(std::vector<LogicValue> vs);
}

#endif