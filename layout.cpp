#include <algorithm>
#include <unordered_map>
#include "layout.hpp"

using namespace std;
using namespace graph;

namespace {
unordered_map<Vertex, Weight> bellmanFord(const Graph& g, Vertex numVertices) {
	unordered_map<Vertex, Weight> res;
	for (Vertex i = 0; i < numVertices; ++i) res[i] = Inf;
	res[1] = 0;

	bool hasUpdated = true;
	while (hasUpdated) {
		hasUpdated = false;
		for (Vertex i = 1; i < numVertices; ++i) {
			for (auto e : g.at(i)) {
				const Vertex j = e.to;
				if (res[i] + e.cost < res[j]) {
					hasUpdated = true;
					res[j] = res[i] + e.cost;
				}
			}
		}
	}
	return res;
}

Graph makeGraph(Vertex numVertices, const vector<LayoutConstraint>& constraints) {
	Graph g;
	for (const auto& c : constraints) {
		auto [from, to] = c.constraint > 0 ? make_pair(c.from, c.to) : make_pair(c.to, c.from);
		g[from].push_back({ to, c.constraint });
	}
	for (int i = 2; i < numVertices; ++i) {
		g[i].push_back({ i-1, 0 });
	}
	return g;
}
}

Weight calcLongestLayout(Vertex numVertices, const vector<LayoutConstraint>& constraints) {

	const auto res = bellmanFord(makeGraph(numVertices, constraints), numVertices);
	return res.at(numVertices - 1);
}

Vertex getMaxVertex(const vector<LayoutConstraint>& constraints)
{
	const auto MaxFrom = ranges::max_element(constraints, [](auto& lhr, auto& rhs) { return lhr.from < rhs.from; })->from;
	const auto MaxTo = ranges::max_element(constraints, [](auto& lhs, auto& rhs) { return lhs.to < rhs.to; })->to;
	return std::max(MaxFrom, MaxTo);
}
