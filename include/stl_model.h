// 
// Copyright (c) 2025 Martin Hertel. All rights reserved.
// 
// This software is released under the MIT License.
// See the LICENSE file for more details.
#ifndef STLIO_STL_MODEL_H
#define STLIO_STL_MODEL_H

#include <vector>
#include <string>
#include "Face.h"

using std::string;
using std::vector;

namespace stlio {

    class STLModel {
    public:
        STLModel() = default;

        STLModel(const string &filepath);

        // Getters
        [[nodiscard]] string getName() const { return m_name; }

        [[nodiscard]] vector<geometry::Face>& getFaces() { return m_faces; }

        // Setters
        void setName(const string &name) { m_name = name; }

        void setFaces(const vector<geometry::Face> &faces) { m_faces = faces; }

        // Add face
        void addFace(geometry::Face face) { m_faces.push_back(face); }

        // Remove face by index
        void removeFace(int index) { m_faces.erase(m_faces.begin() + index); }

        [[nodiscard]] string toString() const;

        // Write to file
        void writeToFile(const string &filename, bool binary = false) const;

    private:
        string m_name;
        vector<geometry::Face> m_faces;
    };

} // namespace stlio

#endif //STLIO_STL_MODEL_H
