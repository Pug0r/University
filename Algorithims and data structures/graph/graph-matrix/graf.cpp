#include <fstream>
#include "Graf.h"

Graf::Graf()
{
    numberOfVertices = 0;
    numberOfEdges = 0;
}

bool Graf::isLegalVertex(int index)
{
    if ((index >= 0) && (index < numberOfVertices))
        return true;
    return false;
}

void Graf::createVertices(int ile)
{
    if ((ile < 0) || (ile > MAX_SIZE))
        return;

    for (int i = numberOfVertices; i < ile; i++)
    {
        matrix[i][i] = 1;
    }
    numberOfVertices += ile;
}

void Graf::addEdge(int i_Vertex_Index_1, int i_Vertex_Index_2)
{
    if (isLegalVertex(i_Vertex_Index_1) && isLegalVertex(i_Vertex_Index_2))
    {
        if (!(checkEdge(i_Vertex_Index_1, i_Vertex_Index_2)))
        {
        matrix[i_Vertex_Index_1][i_Vertex_Index_2] = 1;
        matrix[i_Vertex_Index_2][i_Vertex_Index_1] = 1;
        numberOfEdges += 1;
        }
    }
    return;
}

void Graf::removeEdge(int i_Vertex_Index_1, int i_Vertex_Index_2)
{
    if (isLegalVertex(i_Vertex_Index_1) && isLegalVertex(i_Vertex_Index_2))
    {
        if (checkEdge(i_Vertex_Index_1, i_Vertex_Index_2))
        {
            matrix[i_Vertex_Index_1][i_Vertex_Index_2] = 0;
            matrix[i_Vertex_Index_2][i_Vertex_Index_1] = 0;
            numberOfEdges -= 1;
        }

    }
    return;

}

bool Graf::checkEdge(int i_Vertex_Index_1, int i_Vertex_Index_2)
{
    if (isLegalVertex(i_Vertex_Index_1) && isLegalVertex(i_Vertex_Index_2))
        return matrix[i_Vertex_Index_1][i_Vertex_Index_2]; 
    return false;
}

int Graf::vertexDegree(int idx)
{
    int result = 0;
    for (int i = 0; i < numberOfVertices; i++)
    {
        if (matrix[idx][i] == 1)
            result += 1;
    }
    // Vertex doesn't count as it's own neighbour 
    return result-1;
}

 std::vector<int> Graf::getNeighbourIndices(int idx)
 {
    std::vector<int> result;

    for (int i = 0; i < numberOfVertices; i++)
    {
        if (matrix[idx][i] == 1 && (i != idx))
            result.push_back(i);
    }
    return result;
 }

 void Graf::printNeighbourIndices(int idx)
 {
    std::cout << "\n" << "Neighbour indicies of " << idx << ": ";
    for (int i = 0; i < numberOfVertices; i++)
    {
        if (matrix[idx][i] == 1 && (i != idx))
            std::cout << i << " ";
    }
    std::cout << std::endl;
 }

 int Graf::getNumberOfEdges()
 {
    return numberOfEdges;
 }

 void Graf::readFromFile(std::string path)
 {
    int numberOfVertices, v1, v2;
    std::ifstream infile(path);
    infile >> numberOfVertices;
    createVertices(numberOfVertices);
    while (infile >> v1 >> v2)
    {
        addEdge(v1, v2);
    }
 }


void test1()
{
    Graf* G = new Graf();    
    G->createVertices(10);
    G->addEdge(1, 2);
    G->addEdge(2, 3);
    G->addEdge(1, 5);
    std::cout << G->vertexDegree(1)<<"\n";
    std::cout << G->vertexDegree(8) << "\n";
    G->printNeighbourIndices(1);
    G->printNeighbourIndices(1);
    std::cout << G->checkEdge(1, 2)<<"\n";
    G->removeEdge(1, 2);
    G->printNeighbourIndices(1);
    std::cout << G->checkEdge(1, 2) << "\n\n\n\n\n";   
}

void test2(std::string path)
{
    Graf* G = new Graf();
    G->readFromFile(path);
    G->printNeighbourIndices(1);
    std::cout << G->getNumberOfEdges();
}

int main()
{
    test1();
    test2("GrafS.txt");  
    test2("GrafL.txt");  
}




