/**
 * @file blif.cpp
 * @author htzhu (htzhu@univista-isg.com)
 * @brief
 *  Store blif.
 * @version 0.1
 * @date 2022-07-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "blif.h"

namespace blifspace
{
    void Blif::set_model(std::string model_name)
    {
        this->model_name_ = model_name;
        std::clog << ".model " << model_name << std::endl;
    }
    void Blif::add_inputs(std::string input)
    {
        this->inputs_.push_back(input);
        std::clog << ".inputs " << input << std::endl;
    }
    void Blif::add_outputs(std::string output)
    {
        this->outputs_.push_back(output);
        std::clog << ".outputs " << output << std::endl;
    }
    void Blif::add_names(std::vector<std::string> inputs, std::string output, std::vector<std::vector<LogicValue>> so_cover)
    {
        this->all_names_.push_back(Names{inputs, output, so_cover});
        std::clog << ".names " << output << std::endl;
    }
    void Blif::add_latch(std::string input, std::string output, LatchType type, std::string control, LogicValue init)
    {
        this->all_latch_.push_back(Latch{input, output, type, control, init});
        std::clog << ".latch " << output << std::endl;
    }
    void Blif::write_blif(std::string output_path)
    {
        std::ofstream blif_file;
        blif_file.open(output_path.c_str());
        if(blif_file.is_open())
        {
            blif_file << ".model " << model_name_ << std::endl;

            blif_file << ".inputs";
            for(int i = 0; i < inputs_.size(); i ++)
            {
                blif_file << " " << inputs_[i];
            }
            blif_file << std::endl;
            
            blif_file << ".outputs";
            for(int i = 0; i < outputs_.size(); i ++)
            {
                blif_file << " " << outputs_[i];
            }
            blif_file << std::endl;

            for(int i = 0; i < all_latch_.size(); i ++)
            {
                std::string type = get_type_str(all_latch_[i].type);
                if(type == "")
                {
                    blif_file << ".latch " << all_latch_[i].input << " " << all_latch_[i].output << " " << type << std::endl;
                }
                else
                {
                    blif_file << ".latch " << all_latch_[i].input << " " << all_latch_[i].output << " " << type << " " << all_latch_[i].control << " " << get_logic_str(all_latch_[i].init) << std::endl;
                }
            }

            for(int i = 0; i < all_names_.size(); i ++)
            {
                blif_file << ".names";
                Names names = all_names_[i];
                if(names_is_true(names))
                {
                    blif_file << " " << names.output << std::endl;
                    blif_file << "1" << std::endl;
                }
                else if(names_is_false(names))
                {
                    blif_file << " " << names.output << std::endl;
                }
                else
                {
                    for(int j = 0; j < names.inpus.size(); j ++)
                    {
                        blif_file << " " << names.inpus[j];
                    }
                    blif_file << " " << names.output << std::endl;
                    for(int j = 0; j < names.so_cover.size(); j ++)
                    {
                        blif_file << get_logic_str(names.so_cover[j]) << " 1" << std::endl;
                    }
                }
            }

            blif_file << ".end" << std::endl;
        }
        else
        {
            std::cerr << "Failed to create blif file." << std::endl;
            exit(1);
        }
        blif_file.close();
    }
    std::string get_type_str(LatchType type)
    {
        if(type == LatchType::ACTIVE_HIGH)
        {
            return "ah";
        }
        if(type == LatchType::ACTIVE_LOW)
        {
            return "al";
        }
        if(type == LatchType::ASYNCHRONOUS)
        {
            return "as";
        }
        if(type == LatchType::FALLING_EDGE)
        {
            return "fe";
        }
        if(type == LatchType::RISING_EDGE)
        {
            return "re";
        }
        std::cerr << "get_type_str error." << std::endl;
        exit(1);
    }
    std::string get_logic_str(LogicValue v)
    {
        if(v == LogicValue::TRUE)
        {
            return "1";
        }
        if(v == LogicValue::FALSE)
        {
            return "0";
        }
        if(v == LogicValue::DONT_CARE)
        {
            return "-";
        }
        std::cerr << "get_logic_str error." << std::endl;
        exit(1);
    }
    std::string get_logic_str(std::vector<LogicValue> vs)
    {
        std::string ret = "";
        for(int i = 0; i < vs.size(); i ++)
        {
            ret = ret + get_logic_str(vs[i]);
        }
        return ret;
    }

    bool names_is_true(Names names)
    {
        if(names.inpus.size() == 0 && names.so_cover.size() == 1 && get_logic_str(names.so_cover[0])  == "1")
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool names_is_false(Names names)
    {
        if(names.inpus.size() == 0 && names.so_cover.size() == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
