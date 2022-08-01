/**
 * @file blif2aag.cpp
 * @author htzhu (htzhu@univista-isg.com)
 * @brief
 *  1.Call blifParser to parse before.blif and after.blif
 *  2.Call Converter to conver before.blif and after.blif to before.aag and after.aag
 *  3.Call Merger to merge before.aag and after.aag and constraints.
 * @version 0.1
 * @date 2022-07-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "blif2aag.h"
using namespace std;

void blif2aag(string output_dir_path) {
    blifspace::Blif blif1 = blif_parser(output_dir_path + "/blif/blif1.blif");
    blifspace::Blif blif2 = blif_parser(output_dir_path + "/blif/blif2.blif");

    aigerspace::Aiger aag1 = converter(blif1);
    aigerspace::Aiger aag2 = converter(blif2);

    // blif1.write_blif(output_dir_path + "/blif1.blif");
    // blif2.write_blif(output_dir_path + "/blif2.blif");

    // aag1.write_aiger(output_dir_path + "/aag1.aag");
    // aag2.write_aiger(output_dir_path + "/aag2.aag");

    aigerspace::Aiger aag_merge = merger(aag1, aag2);

    aag_merge.write_aiger(output_dir_path + "aag/merge.aag");
}
