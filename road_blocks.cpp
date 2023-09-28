#include <unordered_map>
#include <queue>
#include <utility>
#include <vector>
#include <functional>
#include <ranges>
#include "road_blocks.hpp"

using namespace graph;
using namespace std;

Weight RoadBlocks::calcSecondShortest(const Vertex s, const Vertex e)
{
	unordered_map<Vertex, Weight> shortests;
	unordered_map<Vertex, Weight> seconds;

	auto vertices = g_ | views::keys;
	for (const auto& v : vertices) {
		shortests[v] = Inf;
		seconds[v] = Inf;
	}

	shortests[s] = 0;

	using Cost = pair<Weight, Vertex>;
	priority_queue<Cost, vector<Cost>, greater<Cost>> unused;
	unused.push({shortests[s], s});

	while (!unused.empty()) {
		const auto current = unused.top();
		unused.pop();

		const auto& edges = g_[current.second];
		for(const auto& e: edges){
			const auto& dest = e.to;
			auto newCost = current.first + e.cost;
			if (newCost < shortests[dest]) {
				swap(newCost, shortests[dest]);
				unused.push({ shortests[dest], dest });
			}
			if (newCost < seconds[dest]) {
				seconds[dest] = newCost;
				unused.push({ seconds[dest], dest });
			}
		}
	}

	return seconds[e];
}
