#pragma once

#include <windows.h>
#include "Structures.h"
#include "Mesh.h"

namespace Meshes
{
    namespace Vertices
    {
        static LightVertex cubeVertices[] =
        {
            { Vector3D(-1.0f, 1.0f, -1.0f), Vector3D(0.0f, 0.0f, -1.0f),    Vector2D(0.0f,0.0f) },       //0
            { Vector3D(1.0f, 1.0f, -1.0f),  Vector3D(0.0f, 0.0f, -1.0f),    Vector2D(1.0f,0.0f) },       //1
            { Vector3D(-1.0f, -1.0f, -1.0f),Vector3D(0.0f, 0.0f, -1.0f),    Vector2D(0.0f,1.0f) },       //2
            { Vector3D(1.0f, -1.0f, -1.0f), Vector3D(0.0f, 0.0f, -1.0f),    Vector2D(1.0f,1.0f) },       //3
                                                                            
            { Vector3D(1.0f, 1.0f, -1.0f),  Vector3D(1.0f, 0.0f, 0.0f),     Vector2D(0.0f,0.0f) },       //4
            { Vector3D(1.0f, 1.0f, 1.0f),   Vector3D(1.0f, 0.0f, 0.0f),     Vector2D(1.0f,0.0f) },       //5
            { Vector3D(1.0f, -1.0f, -1.0f), Vector3D(1.0f, 0.0f, 0.0f),     Vector2D(0.0f,1.0f) },       //6
            { Vector3D(1.0f, -1.0f, 1.0f),  Vector3D(1.0f, 0.0f, 0.0f),     Vector2D(1.0f,1.0f) },       //7
                                                                            
            { Vector3D(1.0f, 1.0f, 1.0f),   Vector3D(0.0f, 0.0f, 1.0f),     Vector2D(1.0f,0.0f) },       //8
            { Vector3D(-1.0f, 1.0f, 1.0f),  Vector3D(0.0f, 0.0f, 1.0f),     Vector2D(0.0f,0.0f) },       //9
            { Vector3D(1.0f, -1.0f, 1.0f),  Vector3D(0.0f, 0.0f, 1.0f),     Vector2D(1.0f,1.0f) },       //10
            { Vector3D(-1.0f, -1.0f, 1.0f), Vector3D(0.0f, 0.0f, 1.0f),     Vector2D(0.0f,1.0f) },       //11
                                                                            
            { Vector3D(-1.0f, 1.0f, 1.0f),  Vector3D(-1.0f, 0.0f, 0.0f),    Vector2D(0.0f,0.0f) },       //12
            { Vector3D(-1.0f, 1.0f, -1.0f), Vector3D(-1.0f, 0.0f, 0.0f),    Vector2D(1.0f,0.0f) },       //13
            { Vector3D(-1.0f, -1.0f, 1.0f), Vector3D(-1.0f, 0.0f, 0.0f),    Vector2D(0.0f,1.0f) },       //14
            { Vector3D(-1.0f, -1.0f, -1.0f),Vector3D(-1.0f, 0.0f, 0.0f),    Vector2D(1.0f,1.0f) },       //15
                                                                            
            { Vector3D(-1.0f, 1.0f, 1.0f),  Vector3D(0.0f, 1.0f, 0.0f),     Vector2D(0.0f,0.0f) },       //16
            { Vector3D(1.0f, 1.0f, 1.0f),   Vector3D(0.0f, 1.0f, 0.0f),     Vector2D(1.0f,0.0f) },       //17
            { Vector3D(-1.0f, 1.0f, -1.0f), Vector3D(0.0f, 1.0f, 0.0f),     Vector2D(0.0f,1.0f) },       //18
            { Vector3D(1.0f, 1.0f, -1.0f),  Vector3D(0.0f, 1.0f, 0.0f),     Vector2D(1.0f,1.0f) },       //19
                                                                            
                                                                            
            { Vector3D(-1.0f, -1.0f, 1.0f), Vector3D(0.0f, -1.0f, 0.0f),    Vector2D(0.0f,0.0f) },       //20
            { Vector3D(-1.0f, -1.0f, -1.0f),Vector3D(0.0f, -1.0f, 0.0f),    Vector2D(1.0f,0.0f) },       //21
            { Vector3D(1.0f, -1.0f, 1.0f),  Vector3D(0.0f, -1.0f, 0.0f),    Vector2D(0.0f,1.0f) },       //22
            { Vector3D(1.0f, -1.0f, -1.0f), Vector3D(0.0f, -1.0f, 0.0f),    Vector2D(1.0f,1.0f) },       //23

        };    

        static BasicVertex pyramidVertices[] =
        {
            { Vector3D(-1.0f, -1.0f, 1.0f),     Vector4D(0.0f, 1.0f, 0.0f, 1.0f) },      //0
            { Vector3D(1.0f, -1.0f, 1.0f),      Vector4D(0.0f, 1.0f, 0.0f, 1.0f) },       //1
            { Vector3D(-1.0f, -1.0f, -1.0f),    Vector4D(0.0f, 1.0f, 0.0f, 1.0f) },     //2
            { Vector3D(1.0f, -1.0f, -1.0f),     Vector4D(0.0f, 1.0f, 0.0f, 1.0f) },      //3
                                                
            { Vector3D(0.0f, 1.0f, 0.0f),       Vector4D(1.0f, 0.0f, 0.0f, 1.0f) },       //4
        };

        static BasicVertex icosphereVertices[] =
        {
            { Vector3D(0.0f,        -1.000000f,  0.000000f),  Vector4D(1.0f,                       1.0f,                       1.0f,                       1.0f) },     //0
            { Vector3D(0.7236f,      -0.447215f,  0.525720f), Vector4D(1.0f - (0.25f / 3.0f) * 1,  1.0f - (0.25f / 3.0f) * 1,  1.0f - (0.25f / 3.0f) * 1,  1.0f) },     //1
            { Vector3D(-0.276385f,   -0.447215f, 0.850640f),  Vector4D(1.0f - (0.25f / 3.0f) * 2,  1.0f - (0.25f / 3.0f) * 2,  1.0f - (0.25f / 3.0f) * 2,  1.0f) },     //2
            { Vector3D(-0.894425f,   -0.447215f, 0.000000f),  Vector4D(1.0f - (0.25f / 3.0f) * 3,  1.0f - (0.25f / 3.0f) * 3,  1.0f - (0.25f / 3.0f) * 3,  1.0f) },     //3
            { Vector3D(-0.276385f,   -0.447215f, -0.850640f), Vector4D(1.0f - (0.25f / 3.0f) * 4,  1.0f - (0.25f / 3.0f) * 4,  1.0f - (0.25f / 3.0f) * 4,  1.0f) },     //4
            { Vector3D(0.723600f,    -0.447215f,  -0.525720f),Vector4D(1.0f - (0.25f / 3.0f) * 5,  1.0f - (0.25f / 3.0f) * 5,  1.0f - (0.25f / 3.0f) * 5,  1.0f) },     //5
            { Vector3D(0.276385f,     0.447215f, 0.850640f),  Vector4D(1.0f - (0.25f / 3.0f) * 6,  1.0f - (0.25f / 3.0f) * 6,  1.0f - (0.25f / 3.0f) * 6,  1.0f) },     //6
            { Vector3D(-0.723600f,    0.447215f,  0.525720f), Vector4D(1.0f - (0.25f / 3.0f) * 7,  1.0f - (0.25f / 3.0f) * 7,  1.0f - (0.25f / 3.0f) * 7,  1.0f) },     //7
            { Vector3D(-0.723600f,    0.447215f,  -0.525720f),Vector4D(1.0f - (0.25f / 3.0f) * 8,  1.0f - (0.25f / 3.0f) * 8,  1.0f - (0.25f / 3.0f) * 8,  1.0f) },     //8
            { Vector3D(0.276385f,     0.447215f, -0.850640f), Vector4D(1.0f - (0.25f / 3.0f) * 9,  1.0f - (0.25f / 3.0f) * 9,  1.0f - (0.25f / 3.0f) * 9,  1.0f) },     //9
            { Vector3D(0.894425f,     0.447215f, 0.000000f),  Vector4D(1.0f - (0.25f / 3.0f) * 10, 1.0f - (0.25f / 3.0f) * 10, 1.0f - (0.25f / 3.0f) * 10, 1.0f) },     //10
            { Vector3D(0.000000f,     1.000000f, 0.000000f),  Vector4D(1.0f - (0.25f / 3.0f) * 11, 1.0f - (0.25f / 3.0f) * 11, 1.0f - (0.25f / 3.0f) * 11, 1.0f) },     //11
        };        
    }

    namespace Indices
    {
        static WORD cubeIndices[] =
        {
            0, 1, 2,
            2, 1, 3,

            4, 5, 6,
            6, 5, 7,

            8, 9,10,
            10,9,11,

            12,13,14,
            14,13,15,

            16,17,18,
            18,17,19,

            20,21,22,
            22,21,23
        };

        static WORD pyramidIndices[] =
        {
            0,2,1,
            1,2,3,

            0,1,4,
            1,3,4,
            3,2,4,
            2,0,4
        };

        static WORD icosphereIndices[] =
        {
           0, 1, 2,
           1, 0, 5,
           0, 2, 3,
           0, 3, 4,

           0, 4, 5,
           1, 5, 10,
           2, 1, 6,
           3, 2, 7,

           4, 3, 8,
           5, 4, 9,
           1, 10,6,
           2, 6, 7,

           3, 7, 8,
           4, 8, 9,
           5, 9,10,
           6, 10,11,

           7, 6, 11,
           8, 7, 11,
           9,8, 11,
           10,9,11,

        };
    }

    static Mesh Cube = Mesh(Vertices::cubeVertices, sizeof(LightVertex), sizeof(Vertices::cubeVertices) / sizeof(Vertices::cubeVertices[0]), Indices::cubeIndices, sizeof(Indices::cubeIndices) / sizeof(WORD));
    static Mesh Pyramid = Mesh(Vertices::pyramidVertices, sizeof(BasicVertex), sizeof(Vertices::pyramidVertices) / sizeof(Vertices::pyramidVertices[0]), Indices::pyramidIndices, sizeof(Indices::pyramidIndices) / sizeof(WORD));
    static Mesh Icosphere = Mesh(Vertices::icosphereVertices, sizeof(BasicVertex), sizeof(Vertices::icosphereVertices) / sizeof(Vertices::icosphereVertices[0]), Indices::icosphereIndices, sizeof(Indices::icosphereIndices) / sizeof(WORD));
    
    //Generates a plane of size width*height, with vertices ranging from -width to width in x, and -height to height
    Mesh* GeneratePlane(int width, int height);
}