# CPP Assignment 001 / Namespaces and classes

0) Namespace ariel:

0-0)class Graph:

    private:

        adjacencyMatrix - A 2D vector of integers which represents the adjacency matrix of a graph.

    public:

        loadGraph - A function used to load a 2D vector into the adjacency matrix of the graph.

        printGraph- A function the prints out the number of vertecies and edges in the graph according to the adjacency matrix of the graph.

        getAdjacencyMatrix- A function that returns the adjacency matrix of the graph.

0-1)class Algorithms: 

    public:

        isConnected- A function that checks if the graph is connected by running the BFS algorithm starting from vertex 0 and then checking if all the vertecies have been painted black (visited).

        shortestPath- A function that searches for the shortest path between two vertecies using the bellman ford algorithm function or detects a possible negative cycle. Please note that if the function is set to search for a shortest path, it will return the shortest path even if a negative cycle is present if the shortest path doesn't visit any of the vertecies marked as a part of the negative cycle 

        isContainsCycle- A function that searches for the a cycle using the DFS algorithm to detect a back edge (If the vertex V is already gray when we first visit the vertex U, then uv is a back edge) which can determine if a graph contains a cycle

        isBipartite- A function that return the partition of the vertecies into two disjoint and independent sets if such a partition exists by using a modified version of the DFS algorithm that colors the neighboring vertecies in the opposite color of the current vertex if all of them are white (gray -> black, black -> gray). If a one of the neighboring vertecies has the same color, then there is no partition and it sends 0. If we don't run into such a situation, we return the partition according to the coloring

        negativeCycle- A function that takes the graph and creates a new graph with it that contains a new vertex that is connected to all vertecies with a weight of 1 on all edges to make the graph connected so that we can detect a negative cycle even if it's disjointed. Then the function calls the bellman ford function to detect a negtive cycle.

    private:

        colorDFS- A function used to return the partition of the vertecies into two disjoint and independent sets if such a partition exists by using a modified version of the DFS algorithm that colors the neighboring vertecies in the opposite color of the current vertex if all of them are white (gray -> black, black -> gray). If a one of the neighboring vertecies has the same color, then there is no partition and it sends 0. If we don't run into such a situation, we return the partition according to the coloring
        
        visitDFS- A function used to visit the vertecies using the DFS algorithm to detect a back edge to check if the graph contains a cycle. 

        visitBFS- A function used to visit the vertecies of the graph using the BFS algorithm to check if the graph is connected.

        relaxVert- A function used in the bellman ford algorithm to relax an edge.
        
        bellmanFord- A function that can be used to either find the shortest path from one vertex to all the other vertecies or to detect a negative cycle