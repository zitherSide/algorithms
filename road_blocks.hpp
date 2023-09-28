#pragma once

#include "graph.hpp"

class RoadBlocks {
	graph::Graph g_;
public:
	RoadBlocks(const graph::Graph& g) :g_(g) {}
	graph::Weight calcSecondShortest(const graph::Vertex s, const graph::Vertex e);
};
