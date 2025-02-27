// 
// Copyright (c) 2025 Martin Hertel. All rights reserved.
// 
// This software is released under the MIT License.
// See the LICENSE file for more details.
#ifndef STLIO_WRITER_H
#define STLIO_WRITER_H

#include <string>
#include "../include/stl_model.h"

namespace stlio {

    class STLWriter {
    public:
        static void writeToASCII(const std::string &filename, const STLModel &stlModel);

        static void writeToBinary(const std::string &filename, const STLModel &stlModel);
    };

}

#endif //STLIO_WRITER_H
