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
        static void write(const std::string &filename, const stlio::STLModel &stl_model);

    private:
        static std::string buildStringFromSTLModel(const stlio::STLModel &stl_model);

        static std::string vector3DToString(const stlio::Vector3D &v);

        static std::string triangleToSTLString(const stlio::Triangle &t);
    };

}

#endif //STLIO_WRITER_H
