#pragma once
#include "Graph.hpp"
#include <string>
#include <climits>
#define BLACK 2
#define GRAY 1
#define WHITE 0
namespace ariel {

    class Algorithms {
    public:

        /*
        Input: Graph class object g.
        Output: A boolean value determining whether the graph is connected or not.
        */
        static bool isConnected(Graph g);

        /*
        Input: Graph class object g, a starting point a, an ending point b. 
        Output: A string representing the shortest path between two points if there is a path, or -1 if there is no path.
        */
        static std::string shortestPath(Graph g, int a, int b);

        /*
        Input: Graph class object g.
        Output: A boolean value determining whether the graph contains a cycle or not.
        */
        static bool isContainsCycle(Graph g);

        /*
        Input: Graph class object g.
        Output: A string representing a partition of the vertecies into two disjoint and independent sets if such a partition exists, or 0 if there is no such partition.
        */
        static std::string isBipartite(Graph g);

        /*
        Input: Graph class object g.
        Output: A boolean value determining whether the graph contains a negative cycle or not.
        */
        static bool negativeCycle(Graph g);

    //Private auxiliary function used in the algorithms.
    private:

        /*
        Input: An adjacency matrix representing a graph, the number of vertecies in the graph, an array where the index contains the previous vertex of the vertex with corresponding index, an array that represents the color of the vertecies, the index of the next vertex to be checked, the index of the parent vertex.
        Output: A boolean value determining if a partition of the vertecies into two disjoint and independent sets exists
        */
        static bool colorDFS(std::vector<std::vector<int>> adjacencyMatrix, unsigned int vertexCount, int previous[], int color[], unsigned int u, unsigned int parent);

        /*
        Input: An adjacency matrix representing a graph, the number of vertecies in the graph, an array where the index contains the previous vertex of the vertex with corresponding index, an array that represents the color of the vertecies, the index of the next vertex to be checked, the index of the parent vertex.
        Output: A boolean value determining if a back edge exists in the graph
        */
        static bool visitDFS(std::vector<std::vector<int>> adjacencyMatrix, unsigned int vertexCount, int previous[], int color[], unsigned int u, unsigned int parent);

        /*
        Input: An adjacency matrix representing a graph, an array where the index contains the previous vertex of the vertex with corresponding index, an array of the weight of each of the vertecies in the graph, the starting point of the edge, the ending point of the edge
        Output: A boolean value determining if the edge has been relaxed
        */
        static bool relaxVert(std::vector<std::vector<int>> adjacencyMatrix, int previous[], int weights[], unsigned int u, unsigned int v);
    };   
}; 

