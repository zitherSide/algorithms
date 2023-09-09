#pragma once
#include "graph.hpp"

class Kruskal {
	graph::Graph g_;
public:
	Kruskal(const graph::Graph& g) :g_(g) {}
	std::vector<graph::BiEdge> Solve();
};