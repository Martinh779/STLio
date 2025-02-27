// 
// Copyright (c) 2025 Martin Hertel. All rights reserved.
// 
// This software is released under the MIT License.
// See the LICENSE file for more details.
#ifndef STLIO_UTILS_H
#define STLIO_UTILS_H

#include <sstream>

namespace stlio {

#pragma pack(push, 1) // Ensure no padding is added
    struct Vector3D {
        float x = 0;
        float y = 0;
        float z = 0;

        [[nodiscard]] std::string toString() const {
            std::ostringstream oss;
            oss << x << " " << y << " " << z;
            return oss.str();
        }
    };

    struct Triangle {
        Vector3D v1;
        Vector3D v2;
        Vector3D v3;
    };

    struct Face {
        Vector3D normal;
        Triangle triangle;
    };
#pragma pack(pop)
}
#endif //STLIO_UTILS_H
