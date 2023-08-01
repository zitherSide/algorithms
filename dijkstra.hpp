#pragma once

#include <vector>
#include <unordered_map>
#include "graph.hpp"

class Dijkstra {
private:
	graph::Graph graph_;
public:
	Dijkstra(const graph::Graph& graph) : graph_(graph) {}
	std::unordered_map<graph::Vertex, graph::Weight> solve(graph::Vertex start);
	std::unordered_map<graph::Vertex, graph::Weight> solve2(graph::Vertex start);
	std::unordered_map<graph::Vertex, graph::Weight> solve2(graph::Vertex start, std::unordered_map<graph::Vertex, graph::Vertex>& path);
};