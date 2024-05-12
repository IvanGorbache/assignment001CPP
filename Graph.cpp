#include "Graph.hpp"

    ariel::Graph::Graph(){
        //Creates an empty 2D vector
        this->adjacencyMatrix;
    }
    void ariel::Graph::loadGraph(const std::vector<std::vector<int>> &g){
        //Checks if the number of rows matches the number of columns in the matrix.
        if(g.size()!=g[0].size())
        {
            throw std::invalid_argument("The number of rows and columbs are differnet!");
        }
        //Loards the new matrix
        this->adjacencyMatrix = g;
    }
    void ariel::Graph::printGraph() const{
        int count = 0;

        for(std::vector<int> row : this->adjacencyMatrix)
        {
            for(int weight : row)
            {
                count += weight?1:0;
            }
        }
        std::cout<<"Graph with "<<this->adjacencyMatrix.size()<<" vertices and "<<count<<" edges."<<std::endl;
    }
    std::vector<std::vector<int>> ariel::Graph::getAdjacencyMatrix() const{
        return this->adjacencyMatrix;
    }
