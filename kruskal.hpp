#pragma once
#include "graph.hpp"

class Kruskal {
	graph::Graph g_;
public:
	Kruskal(const graph::Graph& g) :g_(g) {}
	graph::NonDirectedGraph Solve();
};

graph::NonDirectedGraph kruskal(const graph::NonDirectedGraph& graph);