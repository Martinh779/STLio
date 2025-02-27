// 
// Copyright (c) 2025 Martin Hertel. All rights reserved.
// 
// This software is released under the MIT License.
// See the LICENSE file for more details.
//

#include "../include/stl_reader.h"
#include "../src/parsers/parser_ascii.h"
#include "../src/parsers/parser_binary.h"
#include <iostream>
#include <fstream>

namespace {
    /**
     * Number of characters to skip in the STL file
     * since a STL file has the following structure:
     *
     * facet normal ni nj nk
     *       outer loop
     *          vertex v1x v1y v1z
     *          vertex v2x v2y v2z
     *          vertex v3x v3y v3z
     *      endloop
     +  endfacet
     */
    const int NORMAL_VECTOR_SKIP = 1;
    const int VERTEX_SKIP = 0;
}

namespace stlio {
    /**
     * Reads an STL file and returns an STLModel
     * @param filename
     * @return STLModel
     */
    STLModel STLReader::read(const std::string &filename) {
        std::ifstream stl_file(filename);

        if (!stl_file) {
            throw std::runtime_error("Could not open file: " + filename);
        }

        std::string line;

        std::getline(stl_file, line);
        std::istringstream iss(line);
        std::string keyword;
        iss >> keyword;

        // It's in ASCII encoded if we can find an ASCII keyword, else It's probably in binary
        return keyword == "solid" ? ParserASCII::read(filename) : ParserBinary::read(filename);
    }
}