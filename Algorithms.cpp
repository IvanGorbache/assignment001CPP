#include "Algorithms.hpp"
#include "Graph.hpp"

namespace ariel
{
    //In order to check if a graph is connected, we run BFS on the graph and check if all the vertecies have been painted black(visited)
    bool Algorithms::isConnected(const Graph &g){
        //Getting the matrix
        std::vector<std::vector<int>> adjacencyMatrix = g.getAdjacencyMatrix();
        
        //getting the number of vertecies, an array for the prvious vertex
        unsigned int vertexCount = adjacencyMatrix.size(), color[vertexCount], current = 0;
        
        //All the vertecies are white because they are yet to be visited
        std::fill_n(color, vertexCount, WHITE);

        //Starting BFS visit on the first vertex
        visitBFS(adjacencyMatrix, vertexCount, color, 0, 0);

        //iterating over the vertecies to check if all of them were visited
        for(unsigned int vertexColor:color)
        {
            //if a vertex is white, it wasn't visited and thus the graph is not connected
            if (vertexColor==WHITE)
            {
                return false;
            }   
        }
        return true;
    }
    void Algorithms::visitBFS(std::vector<std::vector<int>> &adjacencyMatrix, const unsigned int vertexCount, unsigned int color[], const unsigned int u, const unsigned int parent)
    {
        //Marking the vertex as visited by coloring it gray
        color[u] = GRAY;
        //Iterating over all of the posible neighbors
        for (unsigned int v = 0; v < vertexCount; v++)
        {
            //visitng both directions of the edge even if the graph is directed
            if (adjacencyMatrix[u][v] || adjacencyMatrix[v][u])
            {
                //if the vertex hasn't been visited, we vist it and its neighbors
                if (color[v] == WHITE)
                {
                    visitBFS(adjacencyMatrix, vertexCount, color, v, u);
                }
            }
        }
        //Marking the vertex as finished by coloring it black
        color[u] = BLACK;
    }
    //Relaxing the edge for use in the bellmanFord algorithm
    bool Algorithms::relaxVert(std::vector<std::vector<int>> &adjacencyMatrix, unsigned int previous[], int weights[], const unsigned int u, const unsigned int v)
    {
        if (weights[v] > weights[u] + adjacencyMatrix[u][v] && weights[u] != INT_MAX)
        {
            //relaxing the vertex
            weights[v] = weights[u] + adjacencyMatrix[u][v];
            previous[v] = u;
            return true;
        }
        return false;
    }
    //calling bellmanford
    std::string Algorithms::shortestPath(const Graph &g, const unsigned int a, const unsigned int b)
    {
        return bellmanFord(g,a,b,false);
    }
    std::string Algorithms::bellmanFord(const Graph &g, const unsigned int a, const unsigned int b, const bool checkForNegativeCycle)
    {
        //the string that represents the shortest path
        std::string result;
        std::vector<std::vector<int>> adjacencyMatrix = g.getAdjacencyMatrix();
        unsigned int vertexCount = adjacencyMatrix.size(), previous[vertexCount], current = b;
        int weights[vertexCount];

        //checking if the vertecies exist in the graph
        if(a >= vertexCount || b >= vertexCount)
        {
            return "-1";
        }

        //an array used to mark any vertex connected to negative cycle
        bool inNegativeCycle[vertexCount];

        //filling them up with default values
        std::fill_n(previous, vertexCount, -1);
        std::fill_n(weights, vertexCount, INT_MAX);
        std::fill_n(inNegativeCycle,vertexCount,false);

        weights[a] = 0;

        //Running the bellman ford algorithm
        for (int n = 0; n < vertexCount - 1; n++)
        {
            for (unsigned int i = 0; i < vertexCount; i++)
            {
                for (unsigned int j = 0; j < vertexCount; j++)
                {
                    //If an edge exists, we relax it
                    if (adjacencyMatrix[i][j])
                    {
                        relaxVert(adjacencyMatrix, previous, weights, i, j);
                    }
                }
            }
        }
        //If the edges can be realxed once more, we have a negative cycle
        for (unsigned int i = 0; i < vertexCount; i++)
        {
            for (unsigned int j = 0; j < vertexCount; j++)
            {
                if (adjacencyMatrix[i][j] && relaxVert(adjacencyMatrix, previous, weights, i, j))
                {
                    //Marking the edge as a part of the negative cycle
                    inNegativeCycle[i] = true;
                    inNegativeCycle[j] = true;
                    //Used if the function is in negative cycle detection mode
                    if(checkForNegativeCycle)
                    {
                        throw std::invalid_argument("Negative cycle detected!");
                    }
                }
            }
        }
        //In case we somehow didn't vist b
        if (weights[b] == INT_MAX)
        {
            return "-1";
        }
        //Begining the construction of the string of the shortest path
        result = std::to_string(current);
        while (current != a)
        {
            //used to check if the path crosses a negative cycle
            if(inNegativeCycle[current])
            {
                return "-1";
            }
            //Adding the previous vertex in the shortest path
            result = std::to_string(previous[current]) + "->" + result;
            current = previous[current];
        }
        return result;
    }

    bool Algorithms::visitDFS(std::vector<std::vector<int>> &adjacencyMatrix, const unsigned int vertexCount, unsigned int previous[], unsigned int color[], const unsigned int u, const unsigned int parent)
    {
        //Coloring the current vertex as gray
        color[u] = GRAY;

        //Iterating over all of the possible neighbors
        for (unsigned int v = 0; v < vertexCount; v++)
        {
            //if an edge exists, we check if it hasn't been visited yet
            if (adjacencyMatrix[u][v])
            {
                //checking if the edge has been visited and that we didn't accidently visit ourselves
                if (color[v] == GRAY && parent != v)
                {
                    //in case we detect a back edge
                    previous[v] = u;
                    return true;
                }
                //checking if the edge hasn't been visited 
                else if (color[v] == WHITE)
                {
                    previous[v] = u;
                    //visiting the vertex and its neighbors
                    if (visitDFS(adjacencyMatrix, vertexCount, previous, color, v, u))
                    {
                        return true;
                    }
                }
            }
        }
        //finishing visiting the vertex
        color[u] = BLACK;
        return false;
    }
    bool Algorithms::isContainsCycle(const Graph &g)
    {
        std::string result;
        std::vector<std::vector<int>> adjacencyMatrix = g.getAdjacencyMatrix();
        unsigned int vertexCount = adjacencyMatrix.size(), previous[vertexCount], color[vertexCount], current = 0;
        std::fill_n(previous, vertexCount, -1);
        std::fill_n(color, vertexCount, WHITE);

        //performing the DFS algorithm on the graph
        for (unsigned int i = 0; i < vertexCount; i++)
        {
            //visiting unvisited vetecies
            if (color[i] == WHITE)
            {
                //checking if one of the edges has been marked as a back edge during the visit
                if (visitDFS(adjacencyMatrix, vertexCount, previous, color, i, i))
                {
                    //printing the cycle
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
                //If the colors match, we don't have a partition
                if (color[v] == color[u] && u != v)
                {
                    return false;
                }
                //If the vertex hasn't been colored, we give it the opposite color of the current vertex
                if (color[v] == WHITE && previous[u] != v)
                {
                    if (color[u] == GRAY)
                    {
                        color[v] = BLACK;
                    }
                    else
                    {
                        color[v] = GRAY;
                    }
                    //propagating the result up the recursive calls
                    if (!colorDFS(adjacencyMatrix, vertexCount, previous, color, v, u))
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    }
    std::string Algorithms::isBipartite(const Graph &g)
    {
        //a boolean used to check if commas should be added
        bool moreThanOne = false;
        std::string result;
        std::vector<std::vector<int>> adjacencyMatrix = g.getAdjacencyMatrix();
        unsigned int vertexCount = adjacencyMatrix.size(), previous[vertexCount], color[vertexCount], current = 0;
        std::fill_n(previous, vertexCount, -1);
        std::fill_n(color, vertexCount, WHITE);

        //paritioning the graph by coloring it using a modified DFS
        
        for (unsigned int i = 0; i < vertexCount; i++)
        {
            //in case we run into disjointed graphs
            if(color[i]==WHITE)
            {
                color[i] = GRAY;
                if (!colorDFS(adjacencyMatrix, vertexCount, previous, color, i, i))
                {
                    return "0";
                }
            }
        }

        //constructing the string
        //constructing the first group
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

        //constructing the second group
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

            //creating a new graph with a new vertex to the graph that is connected to all the other vertecies of the previous graph by resizing the matrix and setting all the weights of the edges to 1
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