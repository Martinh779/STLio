// 
// Copyright (c) 2025 Martin Hertel. All rights reserved.
// 
// This software is released under the MIT License.
// See the LICENSE file for more details.
#include <fstream>
#include <sstream>
#include "parser_ascii.h"

namespace {
    const std::string SOLID_NAME = "solid";
    const std::string FACET = "facet";
    const std::string NORMAL = "normal";
    const std::string OUTER_LOOP = "outer loop";
    const std::string END_LOOP = "endloop";
    const std::string END_FACET = "endfacet";
    const std::string END_SOLID = "endsolid";
    const std::string VERTEX = "vertex";
}

namespace stlio {

    STLModel ParserASCII::read(const std::string &filename) {
        std::ifstream stl_file(filename);

        if (!stl_file) {
            throw std::runtime_error("Could not open file: " + filename);
        }

        STLModel stl_model{};
        geometry::Face temp_face{};
        std::string line;
        int vertex_count = 0;

        while (std::getline(stl_file, line)) {
            std::istringstream iss(line);
            std::string keyword;
            iss >> keyword;

            if (keyword == FACET) {
                // Read normal vector
                temp_face.normal = getVector3DFromLine(1, iss);
            } else if (keyword == VERTEX) {
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
            } else if (keyword == SOLID_NAME) {
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
     * Writes a STLModel to an ASCII file string
     * @param stl_model STLModel
     * @param filename filename
     * @return string
     */
    std::string ParserASCII::write(STLModel stl_model) {
        std::stringstream ss;

        // insert name
        ss << SOLID_NAME << " " << stl_model.getName() << std::endl;

        // insert faces
        for (const auto &face: stl_model.getFaces()) {
            // normal vector
            const auto &normal = face.normal;
            ss << FACET << " " << NORMAL << " " << normal.toString() << std::endl;

            // triangle
            ss << triangleToSTLString(face.triangle) << std::endl;

            // end face
            ss << END_FACET << std::endl;
        }
        // end solid
        ss << END_SOLID << std::endl;

        return ss.str();
    }


    /**
     * Extracts a Vector3D from a line
     * @param numberOfSkips number of characters to skip at the beginning of the line
     * @param iss input stream
     * @return Vector3D
     */
    geometry::Vector3D ParserASCII::getVector3DFromLine(int numberOfSkips, std::istringstream &iss) {
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


    /**
     * Converts a triangle to a stl file string
     * @param t triangle
     * @return string
     */
    std::string ParserASCII::triangleToSTLString(const geometry::Triangle &t) {
        std::stringstream ss;

        ss << " " << OUTER_LOOP << std::endl;

        ss << "  " << VERTEX << " " << t.v2.toString();
        ss << "  " << VERTEX << " " << t.v3.toString();
        ss << "  " << VERTEX << " " << t.v1.toString();

        ss << " " << END_LOOP;

        return ss.str();
    }
} // stlio