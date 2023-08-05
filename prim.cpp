#include <ranges>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <iostream>
#include "prim.hpp"

using namespace std;
using namespace graph;
using namespace ranges;


graph::Weight Prim::solve() {
	struct Cost {
		Weight cost;
		bool isInST;

		Cost() = default;
		Cost(Weight cost, bool used): cost(cost), isInST(used) {}
	};

	const auto costsRange = graph_ |
		views::keys | 
		views::transform([](const Vertex v) { return  make_pair(v, Cost(Inf, false)); });
	unordered_map<Vertex, Cost> costsFromST(costsRange.begin(), costsRange.end()); //SpanningTreeから各頂点への最小コスト

	constexpr auto startV = 0;
	costsFromST[startV].cost = 0;

	Weight res = 0;
	while (true) {
		auto unused = costsFromST | views::filter([](const auto& elem) {return !elem.second.isInST; });
		if (unused.empty())
			break;

		//choose min vertex to fit into the spanning tree
		const auto [minV, edgeCost] = *ranges::min_element(unused, [](const auto& lhs, const auto& rhs) {return lhs.second.cost < rhs.second.cost; });
		costsFromST[minV].isInST = true;
		res += edgeCost.cost;

		//update Costs from new vertex
		for (const auto [to, cost] : graph_[minV]) {
			if (!costsFromST[to].isInST) {
				costsFromST[to].cost = (std::min)(costsFromST[to].cost, cost);
			}
		}
	}


	return res;
}
