/**
 * @file blifparser.h
 * @author htzhu (htzhu@univista-isg.com)
 * @brief
 *  1.Read file.blif and return class Blif.
 * @version 0.1
 * @date 2022-07-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef BLIFPARSER_H
#define BLIFPARSER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "blif.h"


using namespace std;

vector<string> split(string in);

blifspace::Blif blif_parser(string blif_path);

#endif