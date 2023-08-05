#pragma once
#include "graph.hpp"

class Prim {
	graph::Graph graph_;
public:
	Prim(const graph::Graph& g):graph_(g){}
	graph::Weight solve();
};