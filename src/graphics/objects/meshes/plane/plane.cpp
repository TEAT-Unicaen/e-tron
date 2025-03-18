#include "plane.h"

Plane::Plane(Renderer& renderer, float width, float height, UINT nWidth, UINT nHeight) {
    std::vector<Mesh::Vertex> vertices;
    std::vector<unsigned short> indices;

    // Calculate the step size for subdivisions along the width and height
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;

    float stepX = width / nWidth;
    float stepZ = height / nHeight;

    // Reserve memory for the vertices and indices
    vertices.reserve((nWidth + 1) * (nHeight + 1));  // One vertex per grid point
    indices.reserve(nWidth * nHeight * 6);           // Two triangles per grid square (6 indices)

    // Generate the vertices
    for (int j = 0; j <= nHeight; ++j) {
        for (int i = 0; i <= nWidth; ++i) {
            float x = -halfWidth + i * stepX;
            float z = halfHeight - j * stepZ;
            dx::XMFLOAT3 position(x, 0.0f, z);  // Plane is on the X-Y plane

            // Normals pointing in the Z direction (since the plane is flat)
            dx::XMFLOAT3 normal(0.0f, 1.0f, 0.0f);

            // Add vertex
            vertices.push_back(Mesh::Vertex{ position, normal });
        }
    }

    // Generate the indices for the two triangles per grid square
    for (int j = 0; j < nHeight; ++j) {
        for (int i = 0; i < nWidth; ++i) {
            unsigned short topLeft = j * (nWidth + 1) + i;
            unsigned short topRight = j * (nWidth + 1) + (i + 1);
            unsigned short bottomLeft = (j + 1) * (nWidth + 1) + i;
            unsigned short bottomRight = (j + 1) * (nWidth + 1) + (i + 1);

            // First triangle
            indices.push_back(topLeft);
            indices.push_back(topRight);
            indices.push_back(bottomLeft);

            // Second triangle
            indices.push_back(topRight);
            indices.push_back(bottomRight);
            indices.push_back(bottomLeft);
        }
    }

    // Create the vertex buffer and index buffer
    this->vertexBuffer = std::make_shared<VertexBuffer>(renderer, vertices, 0u);
    this->indexBuffer = std::make_shared<IndexBuffer>(renderer, indices);
}
