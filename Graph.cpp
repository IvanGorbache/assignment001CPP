#include "Graph.hpp"
    void ariel::Graph::loadGraph(const std::vector<std::vector<int>> &g){
        //Checks if the number of rows matches the number of columns in the matrix.
        if(g.size()!=g[0].size())
        {
            //throwing back an exception in case that the number of rows and columns differ from each other.
            throw std::invalid_argument("The number of rows and columbs are differnet!");
        }
        //Loards the new matrix
        this->adjacencyMatrix = g;
    }
    void ariel::Graph::printGraph() const{
        //a counter for the number of edges
        int count = 0;

        //a loop to iterate over the rows of the matrix
        for(std::vector<int> row : this->adjacencyMatrix)
        {
            //a loop to iterate over the columns of the matrix
            for(int weight : row)
            {
                //an edge is a cell in the matrix with a non zero value
                count += weight?1:0;
            }
        }

        //printing out the number of vertecies and edges in the graph
        std::cout<<"Graph with "<<this->adjacencyMatrix.size()<<" vertices and "<<count<<" edges."<<std::endl;
    }
    std::vector<std::vector<int>> ariel::Graph::getAdjacencyMatrix() const{
        //returning the adjacencyMatrix
        return this->adjacencyMatrix;
    }
