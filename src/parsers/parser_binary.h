// 
// Copyright (c) 2025 Martin Hertel. All rights reserved.
// 
// This software is released under the MIT License.
// See the LICENSE file for more details.
#ifndef STLIO_PARSER_BINARY_H
#define STLIO_PARSER_BINARY_H

#include "stl_model.h"

namespace stlio {

    class ParserBinary {

    public:
        static STLModel read(const std::string &filename);

        static void write(const std::string &filename, STLModel stlModel);

    private:
        static void fillBufferWithModel(char* buffer, STLModel stlModel);
    };

} // stlio

#endif //STLIO_PARSER_BINARY_H
