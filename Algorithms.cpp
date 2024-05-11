#include "Algorithms.hpp"
#include "Graph.hpp"

namespace ariel
{
    bool Algorithms::isConnected(Graph g)
    {
        std::vector<std::vector<int>> adjacencyMatrix = g.getAdjacencyMatrix();
        unsigned int vertexCount = adjacencyMatrix.size();
        bool visited[vertexCount];
        visited[0] = true;
        for (unsigned int i = 0; i < vertexCount; i++)
        {
            if (!visited[i])
            {
                return false;
            }
            for (unsigned int j = 0; j < vertexCount; j++)
            {
                if (adjacencyMatrix[i][j] && visited[i])
                {
                    visited[j] = true;
                }
            }
        }

        return true;
    }
    bool Algorithms::relaxVert(std::vector<std::vector<int>> adjacencyMatrix, int previous[], int weights[], unsigned int u, unsigned int v)
    {
        if (weights[v] > weights[u] + adjacencyMatrix[u][v] && weights[u] != INT_MAX)
        {
            weights[v] = weights[u] + adjacencyMatrix[u][v];
            previous[v] = (int)u;
            return true;
        }
        return false;
    }
    std::string Algorithms::shortestPath(Graph g, int a, int b)
    {
        std::string result;
        std::vector<std::vector<int>> adjacencyMatrix = g.getAdjacencyMatrix();
        unsigned int vertexCount = adjacencyMatrix.size();
        int previous[vertexCount], weights[vertexCount], current = b;
        std::fill_n(previous, vertexCount, -1);
        std::fill_n(weights, vertexCount, INT_MAX);
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
                    throw std::invalid_argument("Negative cycle detected!");
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
            result = std::to_string(previous[current]) + "->" + result;
            current = previous[current];
        }
        return result;
    }
    bool Algorithms::visitDFS(std::vector<std::vector<int>> adjacencyMatrix, unsigned int vertexCount, int previous[], int color[], unsigned int u, unsigned int parent)
    {
        color[u] = GRAY;
        for (unsigned int v = 0; v < vertexCount; v++)
        {
            if (adjacencyMatrix[u][v])
            {
                if (color[v] == GRAY && parent != v)
                {
                    previous[v] = (int)u;
                    return true;
                }
                else if (color[v] == WHITE)
                {
                    previous[v] = (int)u;
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
    bool Algorithms::isContainsCycle(Graph g)
    {
        std::string result;
        std::vector<std::vector<int>> adjacencyMatrix = g.getAdjacencyMatrix();
        unsigned int vertexCount = adjacencyMatrix.size();
        int previous[vertexCount], color[vertexCount], current = 0;
        std::fill_n(previous, vertexCount, -1);
        std::fill_n(color, vertexCount, WHITE);
        for (unsigned int i = 0; i < vertexCount; i++)
        {
            if (color[i] == WHITE)
            {
                if (visitDFS(adjacencyMatrix, vertexCount, previous, color, i, i))
                {

                    result = std::to_string(i);
                    current = (int)i;
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
    bool Algorithms::colorDFS(std::vector<std::vector<int>> adjacencyMatrix, unsigned int vertexCount, int previous[], int color[], unsigned int u, unsigned int parent)
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
    std::string Algorithms::isBipartite(Graph g)
    {
        bool moreThanOne = false;
        std::string result;
        std::vector<std::vector<int>> adjacencyMatrix = g.getAdjacencyMatrix();
        unsigned int vertexCount = adjacencyMatrix.size();
        int previous[vertexCount], color[vertexCount], current = 0;
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
    bool Algorithms::negativeCycle(Graph g)
    {
        try
        {
            shortestPath(g, 0, 0);
        }
        catch (const std::invalid_argument &e)
        {
            return true;
        }
        return false;
    }
};