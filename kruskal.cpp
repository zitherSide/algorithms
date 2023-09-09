#include <ranges>
#include "kruskal.hpp"
#include "union_find.hpp"

using namespace std;
using namespace graph;

vector<BiEdge> Kruskal::Solve() {
	size_t NumVertices = ranges::max_element(g_, [](const auto& lhs, const auto& rhs) {return lhs.first < rhs.first; })->first + 1;
	DynamicUnionFindTree<Vertex> mst(NumVertices);
	vector<BiEdge> ret;
	
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
