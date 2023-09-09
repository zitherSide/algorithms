#pragma once
#include <vector>
#include <unordered_map>
#include <limits>

namespace graph {

using Vertex = int;
using Weight = int;

struct Edge {
	Vertex to;
	Weight cost;
};

struct BiEdge {
	Vertex from = 0;
	Vertex to = 0;
	Weight cost = 0;

	BiEdge(){}
	BiEdge(Vertex f, Edge e) :from(f), to(e.to), cost(e.cost) {}
};

using Edges = std::vector<Edge>;
using Graph = std::unordered_map<Vertex, Edges>;

constexpr Weight Inf = std::numeric_limits<Weight>::max() / 2;

extern const Graph TestData;

std::vector<Vertex> RestorePath(Vertex start, Vertex end, const std::unordered_map<Vertex, Vertex>& path);

}
