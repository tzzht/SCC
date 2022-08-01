/**
 * @file blifparser.cpp
 * @author htzhu (htzhu@univista-isg.com)
 * @brief
 * @version 0.1
 * @date 2022-07-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "blifparser.h"

using namespace std;

vector<string> split(string str)
{
    istringstream in(str);
    vector<string> ret;
    string t;

    while (getline(in, t, ' '))
    {
        ret.push_back(t);
    }
    return ret;
}

blifspace::Blif blif_parser(string blif_path)
{
    ifstream blif_file;
    blifspace::Blif blif_ret;

    blif_file.open(blif_path.c_str());
    if (blif_file.is_open())
    {
        string line;

        // omit comment
        do
        {
            getline(blif_file, line);
        } while (line.substr(0, 6) != ".model");

        while (blif_file.eof() == false)
        {
            if (line.substr(0, 6) == ".model")
            {
                string model_name = line.substr(7);
                blif_ret.set_model(model_name);
                getline(blif_file, line);
            }
            else if (line.substr(0, 7) == ".inputs")
            {
                vector<string> identifers;
                identifers = split(line.substr(8));
                for (auto identifer : identifers)
                {
                    blif_ret.add_inputs(identifer);
                }
                getline(blif_file, line);
            }
            else if (line.substr(0, 8) == ".outputs")
            {
                vector<string> identifers;
                identifers = split(line.substr(9));
                for (auto identifer : identifers)
                {
                    blif_ret.add_outputs(identifer);
                }
                getline(blif_file, line);
            }
            else if (line.substr(0, 6) == ".names")
            {
                vector<string> identifers;
                identifers = split(line.substr(7));
                string out = identifers.back();
                identifers.pop_back();
                vector<vector<blifspace::LogicValue>> so_cover;

                getline(blif_file, line);
                while (line[0] != '.')
                {
                    vector<string> planes;
                    vector<blifspace::LogicValue> logic_values;
                    planes = split(line);
                    if (planes.size() == 1) // case 1
                    {
                        if (planes[0] == "1")
                        {
                            logic_values.push_back(blifspace::LogicValue::TRUE);
                            so_cover.push_back(logic_values);
                        }
                        else
                        {
                            cerr << "Failed to parse blif, illegal format of .names." << endl;
                            exit(1);
                        }
                    }
                    else if (planes.size() == 2) // other cases
                    {
                        if (planes[1] == "1" && planes[0].size() == identifers.size())
                        {
                            for (int i = 0; i < planes[0].size(); i++)
                            {
                                if (planes[0][i] == '0')
                                {
                                    logic_values.push_back(blifspace::LogicValue::FALSE);
                                }
                                else if (planes[0][i] == '1')
                                {
                                    logic_values.push_back(blifspace::LogicValue::TRUE);
                                }
                                else if (planes[0][i] == '-')
                                {
                                    logic_values.push_back(blifspace::LogicValue::DONT_CARE);
                                }
                                else
                                {
                                    cerr << "Failed to parse blif, illegal format of .names." << endl;
                                    exit(1);
                                }
                            }
                            so_cover.push_back(logic_values);
                        }
                        else
                        {
                            cerr << "Failed to parse blif, illegal format of .names." << endl;
                            exit(1);
                        }
                    }
                    else
                    {
                        cerr << "Failed to parse blif, illegal format of .names." << endl;
                        exit(1);
                    }
                    getline(blif_file, line);
                }

                blif_ret.add_names(identifers, out, so_cover);
            }
            else if (line.substr(0, 6) == ".latch")
            {
                vector<string> latch_stuff;
                latch_stuff = split(line.substr(7));
                if (latch_stuff.size() == 5) // .latch input output type control init
                {
                    string in = latch_stuff[0];
                    string out = latch_stuff[1];
                    blifspace::LatchType type;
                    string control = latch_stuff[3];
                    blifspace::LogicValue init;
                    if (latch_stuff[2] == "fe")
                    {
                        type = blifspace::LatchType::FALLING_EDGE;
                    }
                    else if (latch_stuff[2] == "re")
                    {
                        type = blifspace::LatchType::RISING_EDGE;
                    }
                    else if (latch_stuff[2] == "ah")
                    {
                        type = blifspace::LatchType::ACTIVE_HIGH;
                    }
                    else if (latch_stuff[2] == "al")
                    {
                        type = blifspace::LatchType::ACTIVE_LOW;
                    }
                    else if (latch_stuff[2] == "as")
                    {
                        type = blifspace::LatchType::ASYNCHRONOUS;
                    }
                    else
                    {
                        cerr << "Failed to parse blif, illegal format of .names." << endl;
                        exit(1);
                    }

                    if (latch_stuff[4] == "0")
                    {
                        init = blifspace::LogicValue::FALSE;
                    }
                    else if (latch_stuff[4] == "1")
                    {
                        init = blifspace::LogicValue::TRUE;
                    }
                    else
                    {
                        cerr << "Failed to parse blif, illegal format of .names." << endl;
                        exit(1);
                    }

                    blif_ret.add_latch(in, out, type, control, init);
                }
                else if (latch_stuff.size() == 3) // .latch intput output init
                {
                    string in = latch_stuff[0];
                    string out = latch_stuff[1];
                    blifspace::LatchType type = blifspace::LatchType::UNSPECIFIED;
                    string control = "";
                    blifspace::LogicValue init;
                    if (latch_stuff[2] == "0")
                    {
                        init = blifspace::LogicValue::FALSE;
                    }
                    else if (latch_stuff[2] == "1")
                    {
                        init = blifspace::LogicValue::TRUE;
                    }
                    else
                    {
                        cerr << "Failed to parse blif, illegal format of .names." << endl;
                        exit(1);
                    }
                    blif_ret.add_latch(in, out, type, control, init);
                }
                else
                {
                    cerr << "Failed to parse blif, illegal format of .names." << endl;
                    exit(1);
                }
                getline(blif_file, line);
            }
            else if (line.substr(0, 4) == ".end")
            {
                getline(blif_file, line);
            }
            else
            {
                cerr << "Failed to parse blif, illegal format." << endl;
                exit(1);
            }
        }
    }
    else
    {
        cerr << "Failed to open blif file." << endl;
        exit(1);
    }
    blif_file.close();

    return blif_ret;
}