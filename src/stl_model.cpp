// 
// Copyright (c) 2025 Martin Hertel. All rights reserved.
// 
// This software is released under the MIT License.
// See the LICENSE file for more details.
#include "../include/stl_model.h"
#include "stl_writer.h"
#include "stl_reader.h"

using std::endl;

namespace stlio {
    STLModel::STLModel(const string &filepath) {
        *this = STLReader::read(filepath);
    }


   string STLModel::toString() const {
        std::ostringstream oss;
        string tab_once = "    ";
        string tab_twice = "        ";
        string name = !m_name.empty() ? m_name : "NULL";
        oss << "Name: " << name << endl;
        for (int i = 0; i < m_faces.size(); i++) {
            auto triangle = m_faces[i].triangle;

            oss << "Face " << i << ":" << endl;
            oss << tab_once << "normal: " << m_faces[i].normal.toString() << endl;
            oss << tab_once << "triangle:" << endl;
            oss << tab_twice << triangle.v1.toString() << endl;
            oss << tab_twice << triangle.v2.toString() << endl;
            oss << tab_twice << triangle.v3.toString() << endl;
        }
        return oss.str();
    }


    void STLModel::writeToFile(const string &filename, bool binary) const {
        if (binary) {
            STLWriter::writeToBinary(filename, *this);
        } else {
            STLWriter::writeToASCII(filename, *this);
        }
    }
}



