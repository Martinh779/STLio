// 
// Copyright (c) 2025 Martin Hertel. All rights reserved.
// 
// This software is released under the MIT License.
// See the LICENSE file for more details.
//

#include "../include/stlio_reader.h"
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

/**
 * Reads an STL file and returns an STLModel
 * @param filename
 * @return STLModel
 */
stlio::STLModel stlio::STLReader::read(const std::string &filename) {
    std::ifstream stl_file(filename);

    if (!stl_file) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    stlio::STLModel stl_model{};
    stlio::Face temp_face{};
    std::string line;
    int vertex_count = 0;

    while (std::getline(stl_file, line)) {
        std::istringstream iss(line);
        std::string keyword;
        iss >> keyword;

        if (keyword == "facet") {
            // Read normal vector
            temp_face.normal = getVector3DFromLine(1, iss);
        } else if (keyword == "vertex") {
            // Read vertices
            switch (vertex_count) {
                case 0:
                    temp_face.triangle.v1 = getVector3DFromLine(0, iss);
                    vertex_count++;
                    break;
                case 1:
                    temp_face.triangle.v2 = getVector3DFromLine(0, iss);
                    vertex_count++;
                    break;
                case 2:
                    temp_face.triangle.v3 = getVector3DFromLine(0, iss);
                    stl_model.addFace(temp_face);
                    vertex_count = 0;
                    temp_face = {};
                    break;
                default:
                    throw std::runtime_error("Invalid vertex count in STL file: " + filename);
            }
        } else if (keyword == "solid") {
            // Read name of the model
            std::string name;
            iss >> name;
            stl_model.setName(name);
        }
    }

    if (vertex_count != 0) {
        throw std::runtime_error("Incomplete face in STL file: " + filename);
    }

    return stl_model;
}


/**
 * Extracts a Vector3D from a line
 * @param numberOfSkips number of characters to skip at the beginning of the line
 * @param iss input stream
 * @return Vector3D
 */
stlio::Vector3D stlio::STLReader::getVector3DFromLine(int numberOfSkips, std::istringstream &iss) {
    std::string skip;
    while (numberOfSkips--) {
        iss >> skip;
    }

    float n_i, n_j, n_k;
    if (!(iss >> n_i >> n_j >> n_k)) {
        throw std::runtime_error("Invalid STL file format");
    }

    return {n_i, n_j, n_k};
}
