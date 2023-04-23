#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#define MAX_SIZE 1000


class Graf
{
    int matrix[MAX_SIZE][MAX_SIZE] = { 0 };
    int numberOfVertices = 0;
    int numberOfEdges = 0;

public:
    Graf();
    bool isLegalVertex(int index);
    void createVertices(int ile);    
    void addEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);    
    void removeEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);
    bool checkEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);
    int vertexDegree(int idx); 
    std::vector<int> getNeighbourIndices(int idx);
    void printNeighbourIndices(int idx);
    int getNumberOfEdges();
    void readFromFile(std::string path); 

private:
    void clear();
};

