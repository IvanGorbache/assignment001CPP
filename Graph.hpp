#pragma once
#include <iostream>
#include <vector>

namespace ariel{
    class Graph{
        private:
            std::vector<std::vector<int>> adjacencyMatrix;
        public:
            Graph();
            void loadGraph(const std::vector<std::vector<int>> &g);
            void printGraph() const;
            std::vector<std::vector<int>> getAdjacencyMatrix() const;
    };
};