// 
// Copyright (c) 2025 Martin Hertel. All rights reserved.
// 
// This software is released under the MIT License.
// See the LICENSE file for more details.
#ifndef STLIO_READER_H
#define STLIO_READER_H

#include <string>
#include "stl_model.h"
#include <sstream>

namespace stlio {

    class STLReader {

    public:
        static STLModel read(const std::string &filename);
    };

} // namespace stlio

#endif //STLIO_READER_H
