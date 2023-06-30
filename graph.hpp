#pragma once
#include <vector>
#include <unordered_map>

namespace graph {

using Vertex = int;
using Weight = int;

struct Edge {
	Vertex to;
	Weight cost;
};

using Edges = std::vector<Edge>;
using Graph = std::unordered_map<Vertex, Edges>;

extern const Graph TestData;

}
