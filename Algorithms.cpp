#include "Algorithms.hpp"
#include "Graph.hpp"

namespace ariel
{
    
    bool Algorithms::isConnected(const Graph &g){
        std::vector<std::vector<int>> adjacencyMatrix = g.getAdjacencyMatrix();
        unsigned int vertexCount = adjacencyMatrix.size();
        unsigned int previous[vertexCount], color[vertexCount], current = 0;
        std::fill_n(previous, vertexCount, -1);
        std::fill_n(color, vertexCount, WHITE);
        visitDFS(adjacencyMatrix, vertexCount, previous, color, 0, 0);
        for(unsigned int vertexColor:color)
        {
            if (vertexColor==WHITE)
            {
                return false;
            }   
        }
        return true;
    }
    void Algorithms::visitBFS(std::vector<std::vector<int>> &adjacencyMatrix, const unsigned int vertexCount, unsigned int previous[], unsigned int color[], const unsigned int u, const unsigned int parent)
    {
        color[u] = GRAY;
        for (unsigned int v = 0; v < vertexCount; v++)
        {
            if (adjacencyMatrix[u][v])
            {
                if (color[v] == WHITE)
                {
                    visitDFS(adjacencyMatrix, vertexCount, previous, color, v, u);
                }
            }
        }
        color[u] = BLACK;
    }
    bool Algorithms::relaxVert(std::vector<std::vector<int>> &adjacencyMatrix, unsigned int previous[], int weights[], const unsigned int u, const unsigned int v)
    {
        if (weights[v] > weights[u] + adjacencyMatrix[u][v] && weights[u] != INT_MAX)
        {
            weights[v] = weights[u] + adjacencyMatrix[u][v];
            previous[v] = u;
            return true;
        }
        return false;
    }
    std::string Algorithms::shortestPath(const Graph &g, const unsigned int a, const unsigned int b)
    {
        return bellmanFord(g,a,b,false);
    }
    std::string Algorithms::bellmanFord(const Graph &g, const unsigned int a, const unsigned int b, const bool checkForNegativeCycle)
    {
        std::string result;
        std::vector<std::vector<int>> adjacencyMatrix = g.getAdjacencyMatrix();
        unsigned int vertexCount = adjacencyMatrix.size();
        unsigned int previous[vertexCount];
        int weights[vertexCount];
        unsigned int current = b;
        bool inNegativeCycle[vertexCount];
        std::fill_n(previous, vertexCount, -1);
        std::fill_n(weights, vertexCount, INT_MAX);
        std::fill_n(inNegativeCycle,vertexCount,false);
        weights[a] = 0;
        for (int n = 0; n < vertexCount - 1; n++)
        {
            for (unsigned int i = 0; i < vertexCount; i++)
            {
                for (unsigned int j = 0; j < vertexCount; j++)
                {
                    if (adjacencyMatrix[i][j])
                    {
                        relaxVert(adjacencyMatrix, previous, weights, i, j);
                    }
                }
            }
        }
        for (unsigned int i = 0; i < vertexCount; i++)
        {
            for (unsigned int j = 0; j < vertexCount; j++)
            {
                if (adjacencyMatrix[i][j] && relaxVert(adjacencyMatrix, previous, weights, i, j))
                {
                    inNegativeCycle[i] = true;
                    inNegativeCycle[j] = true;
                    if(checkForNegativeCycle)
                    {
                        throw std::invalid_argument("Negative cycle detected!");
                    }
                }
            }
        }
        if (weights[b] == INT_MAX)
        {
            return "-1";
        }
        result = std::to_string(current);
        while (current != a)
        {
            if(inNegativeCycle[current])
            {
                return "-1";
            }
            result = std::to_string(previous[current]) + "->" + result;
            current = previous[current];
        }
        return result;
    }

    bool Algorithms::visitDFS(std::vector<std::vector<int>> &adjacencyMatrix, const unsigned int vertexCount, unsigned int previous[], unsigned int color[], const unsigned int u, const unsigned int parent)
    {
        color[u] = GRAY;
        for (unsigned int v = 0; v < vertexCount; v++)
        {
            if (adjacencyMatrix[u][v])
            {
                if (color[v] == GRAY && parent != v)
                {
                    previous[v] = u;
                    return true;
                }
                else if (color[v] == WHITE)
                {
                    previous[v] = u;
                    if (visitDFS(adjacencyMatrix, vertexCount, previous, color, v, u))
                    {
                        return true;
                    }
                }
            }
        }
        color[u] = BLACK;
        return false;
    }
    bool Algorithms::isContainsCycle(const Graph &g)
    {
        std::string result;
        std::vector<std::vector<int>> adjacencyMatrix = g.getAdjacencyMatrix();
        unsigned int vertexCount = adjacencyMatrix.size();
        unsigned int previous[vertexCount], color[vertexCount], current = 0;
        std::fill_n(previous, vertexCount, -1);
        std::fill_n(color, vertexCount, WHITE);
        for (unsigned int i = 0; i < vertexCount; i++)
        {
            if (color[i] == WHITE)
            {
                if (visitDFS(adjacencyMatrix, vertexCount, previous, color, i, i))
                {

                    result = std::to_string(i);
                    current = i;
                    do
                    {
                        result = std::to_string(previous[current]) + "->" + result;
                        current = previous[current];
                    } while (previous[current] != i);
                    result = std::to_string(previous[current]) + "->" + result;
                    std::cout << result << std::endl;

                    return true;
                }
            }
        }
        return false;
    }
    bool Algorithms::colorDFS(std::vector<std::vector<int>> &adjacencyMatrix, const unsigned int vertexCount, unsigned int previous[], unsigned int color[], const unsigned int u, const unsigned int parent)
    {
        for (unsigned int v = 0; v < vertexCount; v++)
        {
            if (adjacencyMatrix[u][v])
            {
                if (color[v] == color[u] && u != v)
                {
                    return false;
                }
                if (color[v] == WHITE && previous[u] != v)
                {
                    if (color[u] == GRAY)
                    {
                        color[v] = BLACK;
                        if (!colorDFS(adjacencyMatrix, vertexCount, previous, color, v, u))
                        {
                            return false;
                        }
                    }
                    else
                    {
                        color[v] = GRAY;
                        if (!colorDFS(adjacencyMatrix, vertexCount, previous, color, v, u))
                        {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }
    std::string Algorithms::isBipartite(const Graph &g)
    {
        bool moreThanOne = false;
        std::string result;
        std::vector<std::vector<int>> adjacencyMatrix = g.getAdjacencyMatrix();
        unsigned int vertexCount = adjacencyMatrix.size();
        unsigned int previous[vertexCount], color[vertexCount], current = 0;
        std::fill_n(previous, vertexCount, -1);
        std::fill_n(color, vertexCount, WHITE);
        color[0] = GRAY;
        for (unsigned int i = 0; i < vertexCount; i++)
        {
            if (!colorDFS(adjacencyMatrix, vertexCount, previous, color, i, i))
            {
                return "0";
            }
        }


        result = "The graph is bipartite: A={";
        for (int i = 0; i < vertexCount; i++)
        {

            if (color[i] == GRAY)
            {
                if (moreThanOne)
                {
                    result += ", ";
                }
                result += std::to_string(i);
                moreThanOne = true;
            }
        }
        moreThanOne = false;
        result += "}, B={";
        for (int i = 0; i < vertexCount; i++)
        {
            if (color[i] == BLACK)
            {
                if (moreThanOne)
                {
                    result += ", ";
                }
                result += std::to_string(i);
                moreThanOne = true;
            }
        }
        result += "}";
        return result;
    }
    bool Algorithms::negativeCycle(const Graph &g)
    {
        try
        {
            //copying the adjacency matrix of the graph g.
            std::vector<std::vector<int>> adjacencyMatrix = g.getAdjacencyMatrix();

            //creating a new graph with a new vertex to the graph that is connected to all the other vertecies of the previous graph by resizing the matrix andsetting all the weights of the edges to 1
            unsigned int newSize = adjacencyMatrix.size()+1;
            adjacencyMatrix.resize(newSize);
            
            for(std::vector<int>&row : adjacencyMatrix)
            {
                row.resize(newSize,1);
            }
            adjacencyMatrix[newSize-1][newSize-1] = 0;
            ariel::Graph newG;
            newG.loadGraph(adjacencyMatrix);

            //Using bellmanFord to detect the negative cycle
            bellmanFord(newG,newSize-1,newSize-1,true);
        }
        catch (const std::invalid_argument &e) //bellmanford throws an exception when a negative cycle is detected, by catching it we can determine if there is negative cycle
        {
            return true;
        }
        return false;
    }
};