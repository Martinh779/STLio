// 
// Copyright (c) 2025 Martin Hertel. All rights reserved.
// 
// This software is released under the MIT License.
// See the LICENSE file for more details.
#include <fstream>
#include "parser_binary.h"
#include <cinttypes>
#include <iostream>
#include <cstring>

using std::vector;

namespace {
    const uint8_t HEADER_BYTES = 80;
    const uint8_t NUM_TRIANGLES_BYTES = 4;
    const uint8_t FACE_BYTES = 50;
}

namespace stlio {
    /* A binary STL file has the following structure:
     * 80 bytes - Header
     * 4 bytes - Number of triangles
     * 50 bytes - Triangle 1
     *  consisiting of:
     *   12 bytes - Normal vector
     *   12 bytes - Vertex 1
     *   12 bytes - Vertex 2
     *   12 bytes - Vertex 3
     *   2 bytes - Attribute byte count
     * ...
     * 50 bytes - Triangle n
     */


    /**
     * Reads a binary STL file.
     * @param filename The name of the file to read.
     * @return The STL model.
     */
    STLModel ParserBinary::read(const std::string &filename) {
        std::ifstream stl_file(filename, std::ios::binary);
        vector<char> bytes((std::istreambuf_iterator<char>(stl_file)), std::istreambuf_iterator<char>());

        // Num of triangles
        uint32_t num_triangles;
        std::memcpy(&num_triangles, &bytes[80], sizeof(uint32_t));

        vector<geometry::Face> faces(num_triangles);
        for (int i = 0; i < num_triangles; i++) {
            std::memcpy(&faces[i].normal, &bytes[84 + i * 50], sizeof(geometry::Vector3D));
            geometry::Triangle &triangle = faces[i].triangle;
            std::memcpy(&triangle.v1, &bytes[96 + i * 50], sizeof(geometry::Vector3D));
            std::memcpy(&triangle.v2, &bytes[108 + i * 50], sizeof(geometry::Vector3D));
            std::memcpy(&triangle.v3, &bytes[120 + i * 50], sizeof(geometry::Vector3D));
        }
        STLModel stl_model;
        stl_model.setFaces(faces);
        return stl_model;
    }


    /**
     * Writes a binary STL file.
     * @param filename The name of the file to write to.
     * @param stlModel The STL model to write.
     */
    void ParserBinary::write(const std::string &filename, STLModel stlModel) {
        std::ofstream stl_file(filename, std::ios::binary);

        // calculate size of file and allocate buffer
        uint32_t size = HEADER_BYTES + NUM_TRIANGLES_BYTES + FACE_BYTES * stlModel.getFaces().size();
        std::vector<char> buffer(size);

        // modify buffer
        fillBufferWithModel(buffer.data(), stlModel);

        // write to file
        stl_file.write(buffer.data(), size);
        stl_file.close();
    }


    /**
     * Fills the buffer with the STL model.
     * @param buffer The buffer to fill.
     * @param stlModel The STL model to fill the buffer with.
     */
    void ParserBinary::fillBufferWithModel(char* buffer, STLModel stlModel) {
        uint8_t offset_bytes = HEADER_BYTES + NUM_TRIANGLES_BYTES;
        vector<geometry::Face> faces = stlModel.getFaces();
        uint32_t numOfFaces = faces.size();

        // skip header, since we don't need it

        // Num of triangles
        std::memcpy(&buffer[80], &numOfFaces, sizeof(uint32_t));

        // Faces
        for (int i = 0; i < numOfFaces; i++) {
            std::memcpy(&buffer[offset_bytes + i * FACE_BYTES], &faces[i], sizeof(geometry::Face));
        }

    }
} // stlio