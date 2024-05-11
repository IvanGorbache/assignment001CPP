#pragma once
#include <iostream>
#include <vector>

namespace ariel{
    class Graph{
        private:
            std::vector<std::vector<int>> adjacencyMatrix;
            int vertexCount;
        public:
            Graph();
            void loadGraph(std::vector<std::vector<int>> g);
            void printGraph();

            std::vector<std::vector<int>> getAdjacencyMatrix();
            int getVertexCount();

    };
};