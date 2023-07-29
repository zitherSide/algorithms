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

using Edges = std::vector<Edge>;
using Graph = std::unordered_map<Vertex, Edges>;

constexpr Weight Inf = std::numeric_limits<Weight>::max() / 2;

extern const Graph TestData;

}
