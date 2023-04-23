#include "Graf.h"

Graf::Graf(){};

bool Graf::isLegalVertex(int index)
{
    if ((index >= 0) && (index < vertexList.size()))
        return true;
    return false;
}

void Graf::createVertices(int ile)
{
    if (ile < 0)
        return;

    for (int i = vertexList.size(); i < ile; i++)
    {
        std::vector<int> temp;
        vertexList.push_back(temp);
    }

}

void Graf::addEdge(int i_Vertex_Index_1, int i_Vertex_Index_2)
{
    if (i_Vertex_Index_1 == i_Vertex_Index_2)
        return;
    if (isLegalVertex(i_Vertex_Index_1) && isLegalVertex(i_Vertex_Index_2))
    {
        if (!(checkEdge(i_Vertex_Index_1, i_Vertex_Index_2)))
        {
            vertexList[i_Vertex_Index_1].push_back(i_Vertex_Index_2);
            vertexList[i_Vertex_Index_2].push_back(i_Vertex_Index_1);
            numberOfEdges += 1;
        }
    }
    return;
}

void Graf::removeEdge(int i_Vertex_Index_1, int i_Vertex_Index_2)
{
    if (isLegalVertex(i_Vertex_Index_1) && isLegalVertex(i_Vertex_Index_2))
    {
        for (int i = 0; i < vertexList[i_Vertex_Index_1].size(); i++)
        {
            if (vertexList[i_Vertex_Index_1][i] == i_Vertex_Index_2)
            {
                vertexList[i_Vertex_Index_1].erase(vertexList[i_Vertex_Index_1].begin()+i);
                numberOfEdges -= 1;
            }
        }

        for (int i = 0; i < vertexList[i_Vertex_Index_2].size(); i++)
        {
            if (vertexList[i_Vertex_Index_1][i] == i_Vertex_Index_1)
            {
                vertexList[i_Vertex_Index_2].erase(vertexList[i_Vertex_Index_2].begin()+i);
                numberOfEdges -= 1;
            }
        }
    }
    return;
}

bool Graf::checkEdge(int i_Vertex_Index_1, int i_Vertex_Index_2)
{
    if (isLegalVertex(i_Vertex_Index_1) && isLegalVertex(i_Vertex_Index_2))
    {
        for (int i: vertexList[i_Vertex_Index_1])
        {
            if (i == i_Vertex_Index_2)
            {
                return true;
            }
        }
    }
    return false;
}

int Graf::vertexDegree(int idx)
{
    if (isLegalVertex(idx))
        return vertexList[idx].size();
    return -1;
}

 std::vector<int> Graf::getNeighbourIndices(int idx)
 {
    if (isLegalVertex(idx))
        return std::vector<int>(vertexList[idx]);
    return std::vector<int>();
        
 }

 void Graf::printNeighbourIndices(int idx)
 {
    if (isLegalVertex(idx))
    {
        std::cout << "Neighbour indicies of " << idx << " are: ";
        for (int i: vertexList[idx])
        {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
    return;
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
    std::cout << std::endl;
}

int main()
{
    test1();
    test2("GrafS.txt");  
    test2("GrafL.txt");  
}




