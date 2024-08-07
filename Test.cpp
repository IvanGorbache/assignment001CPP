#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Test isConnected")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph0 = {
        {0, 0},
        {1, 0}};
    g.loadGraph(graph0);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph2 = {
        {0, 0, 1, 0, 1},
        {0, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {1, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == true);

        vector<vector<int>> graph3 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == true);
}

TEST_CASE("Test shortestPath")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1");
}
TEST_CASE("Test isContainsCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isContainsCycle(g) == false);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == true);
}
TEST_CASE("Test isBipartite")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 0},
        {1, 0, 3, 0, 0},
        {0, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2, 4}, B={1, 3}");
}
TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));
}
TEST_CASE("Test negativeCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, -1, 0},
        {0, 0, -1},
        {-1, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::negativeCycle(g)==true);

    vector<vector<int>> graph2 = {
        {0, -1, 0, -1, 0},
        {0, 0, 0, 0, 0},
        {0, -1, 0, 0, 3},
        {0, 0, 4, 0, 0},
        {0, 0, 0, -1, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::negativeCycle(g)==false);

    vector<vector<int>> graph3 = {
        {0, -1, 0, -1, 0},
        {0, 0, 0, 0, 0},
        {0, -1, 0, 0, 3},
        {0, 0, -4, 0, 0},
        {0, 0, 0, -1, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::negativeCycle(g)==true);
}

TEST_CASE("Test shortest path with graphs that contain negative cycles")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, -6, 0, 0, 0}, 
        {0, 0, 0, -1, 0}, 
        {0, 2, 0, 0, 0}, 
        {-4, 0, 0, 0, 0}, 
        {0, 0, 5, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 4, 2) == "4->2");

    vector<vector<int>> graph2 = {
        {0, -6, 0, 0, 0}, 
        {0, 0, 0, -1, 0}, 
        {0, 2, 0, 0, 0}, 
        {-4, 0, 0, 0, 0}, 
        {0, 0, 5, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 4, 3) == "-1");


    vector<vector<int>> graph3 = {
        {0, -6, 0, 0, 0}, 
        {0, 0, 0, -1, 0}, 
        {0, 2, 0, 0, 0}, 
        {-4, 0, 0, 0, 0}, 
        {0, 0, 5, 0, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::shortestPath(g, 4, 1) == "-1");
}

TEST_CASE("Test negativeCycle on disjointed graphs")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 0, 5, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 3, 0, 7, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {1, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, -1, 0}, 
        {0, 0, 0, 0, 0, 0, 0, -1}, 
        {0, 0, 0, 0, 0, -4, 0, 0}}; 

    g.loadGraph(graph);
    CHECK(ariel::Algorithms::negativeCycle(g)==true);
}

TEST_CASE("Test isBipartite on cycles")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 0, 1, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 1}, 
        {0, 0, 0, 1, 0, 0, 0}, 
        {0, 0, 0, 0, 1, 0, 0}, 
        {0, 1, 0, 0, 0, 0, 0}, 
        {1, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 0, 0}, 
        {0, 0, 1, 0, 0, 0}, 
        {0, 0, 0, 1, 0, 0}, 
        {0, 0, 0, 0, 1, 0}, 
        {0, 0, 0, 0, 0, 1}, 
        {1, 0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2, 4}, B={1, 3, 5}");
}


TEST_CASE("Test shortestPath on disjointed graphs")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 5, 0, 0, 0, 0}, 
        {0, 0, 5, 42, 0, 0}, 
        {0, 0, 0, 5, 0, 0}, 
        {0, 0, 7, 0, 0, 5}, 
        {0, 0, 0, 0, 0, 0}, 
        {0, 0, 3, 0, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1");
}

TEST_CASE("Test isBipartite on disjointed graphs")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 7, 0, 0, 0, 0}, 
        {7, 0, 7, 0, 0, 0}, 
        {0, 7, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 5, 11}, 
        {0, 0, 0, 5, 0, 1}, 
        {0, 0, 0, 11, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph2 = {
        {0, 7, 0, 0, 0, 0}, 
        {7, 0, 7, 0, 0, 0}, 
        {0, 7, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 5, 0}, 
        {0, 0, 0, 5, 0, 1}, 
        {0, 0, 0, 0, 1, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2, 3, 5}, B={1, 4}");
}