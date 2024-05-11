#include "Graph.hpp"
namespace ariel{
    Graph::Graph(){
        this->adjacencyMatrix;
    }
    void Graph::loadGraph(std::vector<std::vector<int>> g){
        if(g.size()!=g[0].size())
        {
            throw std::invalid_argument("The number of rows and columbs are differnet!");
        }
        this->adjacencyMatrix = g;
    }
    void Graph::printGraph(){
        int count = 0;

        for(std::vector<int> row : this->adjacencyMatrix)
        {
            for(int weight : row)
            {
                count += weight?1:0;
            }
        }
        std::cout<<"Graph with "<<this->vertexCount<<" vertices and "<<count<<" edges."<<std::endl;
    }
    std::vector<std::vector<int>> Graph::getAdjacencyMatrix()
    {
        return this->adjacencyMatrix;
    }
};
