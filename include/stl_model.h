// 
// Copyright (c) 2025 Martin Hertel. All rights reserved.
// 
// This software is released under the MIT License.
// See the LICENSE file for more details.
#ifndef STLIO_STL_MODEL_H
#define STLIO_STL_MODEL_H

#include <vector>
#include <string>

namespace stlio {

    struct Vector3D {
        double x = 0;
        double y = 0;
        double z = 0;
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

    class STLModel {
    public:
        STLModel() = default;

        // Getters
        [[nodiscard]] std::string getName() const { return m_name; }

        [[nodiscard]] std::vector<Face> getFaces() const { return m_faces; }

        // Setters
        void setName(const std::string &name) { m_name = name; }


        void addFace(Face face);

    private:
        std::string m_name;
        std::vector<Face> m_faces;
    };

} // namespace stlio

#endif //STLIO_STL_MODEL_H
