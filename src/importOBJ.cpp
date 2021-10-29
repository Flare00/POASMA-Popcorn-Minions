#include "importOBJ.h"

using namespace std;

// Construct & Destruct
objModelInfo::objModelInfo() {}
objModelInfo::~objModelInfo() {}

vector<Vec3> objModelInfo::getVertices()
{
    return this->vertices;
}
vector<Vec3> objModelInfo::getNormals()
{
    return this->normals;
}
vector<Vec3> objModelInfo::getFaces()
{
    return this->faces;
}

void objModelInfo::fillMyData(string path_file)
{
    // Open File
    ifstream fileOBJ(path_file);
    if (fileOBJ.fail())
    {
        cout << "File does not exist!" << endl;
    }

    // Init Reader
    string readLine;

    // Read file
    while (getline(fileOBJ, readLine))
    {
        // Get First Word
        string input = readLine.c_str();
        vector<string> allWordsLine;
        splitString(input, allWordsLine);

        // What am i reading?
        if (allWordsLine[0].compare("v") == 0)
        {
            this->vertices.push_back(Vec3(stof(allWordsLine[1]), stof(allWordsLine[2]), stof(allWordsLine[3])));
        }
        if (allWordsLine[0].compare("vn") == 0)
        {
            this->normals.push_back(Vec3(stof(allWordsLine[1]), stof(allWordsLine[2]), stof(allWordsLine[3])));
        }
        if (allWordsLine[0].compare("f") == 0)
        {

            // Triangle Faces
            if (allWordsLine.size() == 4)
            { // 4 car je compte le "f" en plus
                this->faces.push_back(Vec3((float)(allWordsLine[1][0] - '0'), (float)(allWordsLine[2][0] - '0'), (float)(allWordsLine[3][0] - '0')));
            }
            // Quad Faces
            if (allWordsLine.size() == 5)
            { // 5 car je compte le "f" en plus
                this->faces.push_back(Vec3((float)(allWordsLine[1][0] - '0'), (float)(allWordsLine[2][0] - '0'), (float)(allWordsLine[3][0] - '0')));
                this->faces.push_back(Vec3((float)(allWordsLine[4][0] - '0'), (float)(allWordsLine[2][0] - '0'), (float)(allWordsLine[3][0] - '0')));
            }
        }
    }

    // Close file
    fileOBJ.close();
}

void objModelInfo::printMyData()
{
    // Print Vertex ("v X Y Z")
    for (int i = 0, max = this->vertices.size(); i < max; i++)
    {
        cout << "v " << vertices[i][0] << " " << vertices[i][1] << " " << vertices[i][2] << endl;
    }
    // Print Normal ("vn X Y Z")
    for (int i = 0, max = this->normals.size(); i < max; i++)
    {
        cout << "vn " << normals[i][0] << " " << normals[i][1] << " " << normals[i][2] << endl;
    }
    // Print Triangle ("f v1 v2 v3")
    for (int i = 0, max = this->faces.size(); i < max; i++)
    {
        cout << "f " << faces[i][0] << " " << faces[i][1] << " " << faces[i][2] << endl;
    }
}

void splitString(const string &str, vector<string> &output)
{
    string::size_type start = 0;
    string::size_type last = str.find_first_of(" ");

    while (last != string::npos)
    {
        if (last > start)
        {
            output.push_back(str.substr(start, last - start));
        }
        start = ++last;
        last = str.find_first_of(" ", last);
    }
    output.push_back(str.substr(start));
}
