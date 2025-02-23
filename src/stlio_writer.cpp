// 
// Copyright (c) 2025 Martin Hertel. All rights reserved.
// 
// This software is released under the MIT License.
// See the LICENSE file for more details.
//

#include <sstream>
#include <fstream>
#include "../include/stlio_writer.h"

/**
 * STL File structure:
 * solid name
 * facet normal ni nj nk
 *    outer loop
 *       vertex v1x v1y v1z
 *       vertex v2x v2y v2z
 *       vertex v3x v3y v3z
 *     endloop
 * endfacet
 * ...
 * endsolid name
 */

namespace {
    const std::string SOLID_NAME = "solid";
    const std::string FACET_NORMAL = "facet normal";
    const std::string OUTER_LOOP = "outer loop";
    const std::string END_LOOP = "endloop";
    const std::string END_FACET = "endfacet";
    const std::string END_SOLID = "endsolid";
    const std::string VERTEX = "vertex";
}

namespace stlio {

    void STLWriter::write(const std::string &filename, const stlio::STLModel &stl_model) {
        std::string data = buildStringFromSTLModel(stl_model);

        std::ofstream file(filename);
        if (file) {
            file << data;
            file.close();
        }
    }

    std::string STLWriter::buildStringFromSTLModel(const stlio::STLModel &stl_model) {
        std::stringstream ss;

        // insert name
        ss << SOLID_NAME << " " << stl_model.getName() << std::endl;

        // insert faces
        for (const auto &face: stl_model.getFaces()) {
            // normal vector
            const auto &normal = face.normal;
            ss << FACET_NORMAL << " " << vector3DToString(normal);

            // triangle
            ss << triangleToSTLString(face.triangle) << std::endl;

            // end face
            ss << END_FACET << std::endl;
        }
        // end solid
        ss << END_SOLID << std::endl;

        return ss.str();
    }

    std::string STLWriter::vector3DToString(const stlio::Vector3D &v) {
        std::stringstream ss;

        ss << v.x << " " << v.y << " " << v.z << std::endl;

        return ss.str();
    }

    std::string STLWriter::triangleToSTLString(const stlio::Triangle &t) {
        std::stringstream ss;

        ss << " " << OUTER_LOOP << std::endl;

        ss << "  " << VERTEX << " " << vector3DToString(t.v1);
        ss << "  " << VERTEX << " " << vector3DToString(t.v2);
        ss << "  " << VERTEX << " " << vector3DToString(t.v3);

        ss << " " << END_LOOP;

        return ss.str();
    }
}