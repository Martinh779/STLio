// 
// Copyright (c) 2025 Martin Hertel. All rights reserved.
// 
// This software is released under the MIT License.
// See the LICENSE file for more details.
//

#include <sstream>
#include <fstream>
#include "../include/stl_writer.h"
#include "../src/parsers/parser_ascii.h"
#include "parsers/parser_binary.h"

namespace stlio {

    void STLWriter::writeToASCII(const std::string &filename, const stlio::STLModel &stlModel) {
        std::string data = ParserASCII::write(stlModel);

        std::ofstream file(filename);
        if (file) {
            file << data;
            file.close();
        }
    }

    void STLWriter::writeToBinary(const std::string &filename, const STLModel &stlModel) {
        ParserBinary::write(filename, stlModel);
    }
}