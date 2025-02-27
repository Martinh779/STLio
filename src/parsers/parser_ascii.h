// 
// Copyright (c) 2025 Martin Hertel. All rights reserved.
// 
// This software is released under the MIT License.
// See the LICENSE file for more details.
#ifndef STLIO_PARSER_ASCII_H
#define STLIO_PARSER_ASCII_H

#include "stl_model.h"

namespace stlio {

    class ParserASCII {

    public:
        static STLModel read(const std::string &filename);

        static std::string write(STLModel stl_model);

    private:
        static geometry::Vector3D getVector3DFromLine(int numberOfSkips, std::istringstream &iss);

        static std::string triangleToSTLString(const geometry::Triangle &t);
    };

} // stlio

#endif //STLIO_PARSER_ASCII_H
