#include "Meshes.h"

Mesh* Meshes::GeneratePlane(int width, int height)
{
    std::vector<BasicVertex> verticesVector;
    std::vector<WORD> indices;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            float xLower, xUpper, yLower, yUpper;

            //-width and -height so that the center of the plane is (0,0,-1) in model space
            xLower = (x * 2.0f) - width;
            xUpper = 2.0f + (x * 2.0f) - width;
            yLower = (y * 2.0f) - height;
            yUpper = 2.0f + (y * 2.0f) - height;

            BasicVertex vertex1 = { Vector3D(xLower, yUpper, -1.0f), Vector4D(1.0f, 0.0f, 0.0f, 1.0f) };
            BasicVertex vertex2 = { Vector3D(xUpper, yUpper, -1.0f), Vector4D(0.0f, 1.0f, 0.0f, 1.0f) };
            BasicVertex vertex3 = { Vector3D(xLower, yLower, -1.0f), Vector4D(0.0f, 0.0f, 1.0f, 1.0f) };
            BasicVertex vertex4 = { Vector3D(xUpper, yLower, -1.0f), Vector4D(1.0f, 1.0f, 0.0f, 1.0f) };

            verticesVector.push_back(vertex1);
            verticesVector.push_back(vertex2);
            verticesVector.push_back(vertex3);
            verticesVector.push_back(vertex4);
        }
    }

    for (int i = 0; i < width * height; i++)
    {
        indices.push_back(0 + 4 * i);
        indices.push_back(1 + 4 * i);
        indices.push_back(2 + 4 * i);
        indices.push_back(2 + 4 * i);
        indices.push_back(1 + 4 * i);
        indices.push_back(3 + 4 * i);
    }

    Mesh* mesh = new Mesh(verticesVector.data(), sizeof(BasicVertex), verticesVector.size(), indices.data(), indices.size());
    return mesh;
}
