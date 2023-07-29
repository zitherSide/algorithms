#pragma once
#include <unordered_map>
#include "graph.hpp"

class FloydWarshall {
	graph::Graph graph_;
public:
	FloydWarshall(const graph::Graph& g) : graph_(g) {}
	std::unordered_map<graph::Vertex, std::unordered_map<graph::Vertex, graph::Weight>> solve();
};