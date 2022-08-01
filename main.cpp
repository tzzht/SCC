/**
 * @file main.cpp
 * @author htzhu (htzhu@univista-isg.com)
 * @brief
 *  1.Read before.v, after.v, constraint.
 *  2.Call ConstraintHandler to handle constrain.
 *  3.Call Yosys to conver before.v and after.v to before.blif and after.blif
 *  4.Call blif2aag to convert before.blif and after.blif to before.aag and after.aag, then merge before.aag and after.aag and add constraints.
 *  5.Call SimpleCar to do equivalence checking.
 * @version 0.1
 * @date 2022-07-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <algorithm>
#include <vector>

#include "blif2aag.h"

using namespace std;

void print_usage()
{
    cout << "Usage: SCC <-e> <verilog file1> <verilog file2> <output directory> <constraint string>" << endl;
    cout << "       SCC <-c> <verilog file> <output directory>" << endl;
    cout << "        -e        do equivalence check of dut_b.v dut_a.v" << endl;
    cout << "        -c        conver model.v to model.blif and model.aag" << endl;
    exit(0);
}

string extract_file_name(string path)
{
    reverse(path.begin(), path.end());
    path = path.substr(path.find('.') + 1);
    path = path.substr(0, path.find('/'));
    reverse(path.begin(), path.end());
    return path;
}

void handle_constraint()
{
}

void handle_yosys(string input1_path, string input2_path, string output_dir_path, vector<string> libs_path)
{
    system(("mkdir -p " + output_dir_path + "/yosys_script").c_str());
    system(("mkdir -p " + output_dir_path + "/blif").c_str());
    string yosys_script1_path = output_dir_path + "/yosys_script/script1.ys";
    string yosys_script2_path = output_dir_path + "/yosys_script/script2.ys";
    string blif1_path = output_dir_path + "/blif/blif1.blif";
    string blif2_path = output_dir_path + "/blif/blif2.blif";


    // generate yosys script
    ofstream yosys_script1;
    yosys_script1.open(yosys_script1_path.c_str());
    if (yosys_script1.is_open())
    {
        yosys_script1 << "read_verilog " << input1_path << endl;
        yosys_script1 << "hierarchy";
        for(auto it : libs_path)
        {
            yosys_script1 << " -libdir " << it;
        }
        yosys_script1 << endl;
        yosys_script1 << "synth -flatten" << endl;
        yosys_script1 << "async2sync" << endl;
        yosys_script1 << "dffunmap" << endl;
        yosys_script1 << "opt_clean -purge" << endl;
        yosys_script1 << "write_blif " << blif1_path << endl;
        yosys_script1.close();
    }
    else
    {
        cerr << "Failed to create yosys script" << endl;
        exit(1);
    }

    ofstream yosys_script2;
    yosys_script2.open(yosys_script2_path.c_str());
    if (yosys_script2.is_open())
    {
        yosys_script2 << "read_verilog " << input2_path << endl;
        yosys_script2 << "hierarchy";
        for(auto it : libs_path)
        {
            yosys_script2 << " -libdir " << it;
        }
        yosys_script2 << endl;
        yosys_script2 << "synth -flatten" << endl;
        yosys_script2 << "async2sync" << endl;
        yosys_script2 << "dffunmap" << endl;
        yosys_script2 << "opt_clean -purge" << endl;
        yosys_script2 << "write_blif " << blif2_path << endl;
        yosys_script1.close();
    }
    else
    {
        cerr << "Failed to create yosys script" << endl;
        exit(1);
    }

    string yosys_command1 = "yosys " + yosys_script1_path;
    string yosys_command2 = "yosys " + yosys_script2_path;
    system(yosys_command1.c_str());
    system(yosys_command2.c_str());
}

void handle_blif2aag(string output_dir_path)
{
    system(("mkdir -p " + output_dir_path + "/aag/").c_str());
    blif2aag(output_dir_path);
}


void handle_simplecar(string output_dir_path)
{
    string aig_dir = output_dir_path + "/aig/";
    string aig_path = aig_dir + "/merge.aig";
    string res_dir = output_dir_path + "/res/";
    system(("mkdir -p " + aig_dir).c_str());
    system(("mkdir -p " + res_dir).c_str());
    string aag2aig_command = "aigtoaig " + output_dir_path + "/aag/merge.aag " + aig_path;
    system(aag2aig_command.c_str());

    string simplecar_command = "simplecar -b -e -end " + aig_path + " " + res_dir;
    system(simplecar_command.c_str());
}

void handle_res(string output_dir_path)
{
    string res_path = output_dir_path + "/res/merge.res";
    string report_path = output_dir_path + "report.txt";
    ofstream report_file;
    report_file.open(report_path.c_str());
    if(report_file.is_open())
    {
        ifstream res_file;
        res_file.open(res_path.c_str());
        if(res_file.is_open())
        {
            string word;
            res_file >> word;
            if(res_file.eof())
            {
                report_file << "-" << endl;
            }
            else
            {
                bool equiv = true;
                string b;
                string dot;
                do
                {
                    if(word == "0")
                    {
                        res_file >> b;
                        res_file >> dot;

                        if(b == "b")
                        {
                            equiv = false;
                            //
                            cout << "simplecar error" << endl;
                            break;
                        }
                    }
                    else
                    {
                        equiv = false;
                        break;
                    }
                } while (res_file.eof());
                if(equiv == true)
                {
                    report_file << "0" << endl;
                }
                else
                {
                    report_file << "1" << endl;
                }
            }

        }
        else
        {
            report_file << "-" << endl;
        }
        res_file.close();
    }
    else
    {
        cerr << "Failed to create report file!" << endl;
        exit(1);
    }
    report_file.close();
    
}

int main(int argc, char **argv)
{
    bool equiv_check = false;
    bool convert = false;

    bool input_path1_set = false;
    bool input_path2_set = false;
    bool output_dir_set = false;
    bool constraint_string_set = false;

    string input1_path;
    string input2_path;
    string output_dir_path;
    string constraint_string;
    vector<string> libs_path;
    


    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-e") == 0)
        {
            equiv_check = true;
        }
        else if (strcmp(argv[i], "-c") == 0)
        {
            convert = true;
        }
        else if (strcmp(argv[i], "-l") == 0)
        {
            libs_path.push_back(string(argv[i+1]));
            i++;
        }
        else if (input_path1_set == false)
        {
            input1_path = string(argv[i]);
            input_path1_set = true;
        }
        else if (input_path2_set == false)
        {
            input2_path = string(argv[i]);
            input_path2_set = true;
        }
        else if (output_dir_set == false)
        {
            output_dir_path = string(argv[i]);
            output_dir_set = true;
        }
        else if (constraint_string_set == false)
        {
            constraint_string = string(argv[i]);
            constraint_string_set = true;
        }
        else
        {
            print_usage();
        }
    }

    if (equiv_check == true)
    {
        handle_constraint();
        handle_yosys(input1_path, input2_path, output_dir_path, libs_path);
        handle_blif2aag(output_dir_path);
        handle_simplecar(output_dir_path);
        handle_res(output_dir_path);
    }

    if (convert = true)
    {
    }
    return 0;
}
