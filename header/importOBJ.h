#ifndef IMPORTOBJ_H
#define IMPORTOBJ_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Vec3.h"

using namespace std;

class objModelInfo
{
private:
    vector<Vec3> vertices; // liste : v [Position] (X,Y,Z)
    vector<Vec3> normals;  // liste : vn [Normal] (X,Y,Z)
    vector<vector<int>> faces;    // liste : f [Triangles] (v1[i],v2[i],v3[i])
public:
    // Construct & Destruct
    objModelInfo();
    ~objModelInfo();
    
    // Getters
    vector<Vec3> getVertices();
    vector<Vec3> getNormals();
    vector<vector<int>> getFaces();

    // OBJ files
    void fillMyData(string path_file);
    void printMyData();
};

void splitString(const string &str, vector<string> &output);

#endif


/*
    objModelInfo myCube;
    myCube.fillMyData("./obj/cube.obj");
    myCube.printMyData();
*/