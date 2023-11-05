#include <ranges>
#include "kruskal.hpp"
#include "union_find.hpp"

using namespace std;
using namespace graph;

NonDirectedGraph Kruskal::Solve() {
	size_t NumVertices = ranges::max_element(g_, [](const auto& lhs, const auto& rhs) {return lhs.first < rhs.first; })->first + 1;
	DynamicUnionFindTree<Vertex> mst(NumVertices);
	NonDirectedGraph ret;
	
	auto allEdges = g_ | views::transform([](const auto& elem){ 
		vector<BiEdge> ret;
		for (const auto& e : elem.second) {
			ret.emplace_back(BiEdge(elem.first, e));
		}
		return ret;
	});
	const vector<vector<BiEdge>> ae(allEdges.begin(), allEdges.end());
		
	auto flatEdges = ae | views::join;
	vector<BiEdge> edges(flatEdges.begin(), flatEdges.end());

	while (true) {
		auto candidates = edges | views::filter([&mst](const auto& e) { return !mst.IsSame(e.from, e.to); });
		if (candidates.empty()) break;

		auto min = ranges::min_element(candidates, [](const auto& lhs, const auto& rhs) { return lhs.cost < rhs.cost; });
		mst.Unite(min->from, min->to);
		ret.emplace_back(*min);
	}

	return ret;
}

NonDirectedGraph kruskal(const NonDirectedGraph& graph) {
	NonDirectedGraph ret;
	NonDirectedGraph sorted{ graph };
	//auto sorted = ranges::sort(graph, [](const auto& lhs, const auto& rhs) { return lhs.cost < rhs.cost; });
	sort(sorted.begin(), sorted.end(), [](const auto& lhs, const auto& rhs) { return lhs.cost < rhs.cost; });
	DynamicUnionFindTree<Vertex> mst(
		max(
			ranges::max_element(graph, [](const auto& lhs, const auto& rhs) { return lhs.from < rhs.from; })->from,
			ranges::max_element(graph, [](const auto& lhs, const auto& rhs) { return lhs.to < rhs.to; })->to
		) + 1
	);

	for(const auto& e: sorted) {
		if (!mst.IsSame(e.from, e.to)) {
			mst.Unite(e.from, e.to);
			ret.emplace_back(e);
		}
	};
	return ret;
}