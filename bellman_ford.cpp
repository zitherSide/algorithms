#include <algorithm>
#include <exception>
#include "bellman_ford.hpp"

using namespace std;

vector<int> BellmanFord::calcShortestPathCosts(int startVertex)
{
	vector<int> costs(NumVertices_);
	for_each(costs.begin(), costs.end(), [](auto& elem) { elem = Inf; });

	costs[startVertex] = 0;
	int count = 0;

	while (true) {
		bool hasUpdated = false;
		for (const auto& v_info : edges_) {
			const auto prev = v_info.first;
			const auto edges = v_info.second;

			for (const auto& e : edges) {
				const auto& cur = e.to;
				const bool updates = shouldUpdate(costs[prev], costs[cur], e.cost);
				costs[cur] = updates ? costs[prev] + e.cost : costs[cur];
				hasUpdated |= updates;
			}
		}

		if (!hasUpdated)
			break;
		
		++count;
		if (count >= NumVertices_)
			throw exception("Negative edge detected");
	}
	return costs;
}

std::vector<int> BellmanFord::calcShortestPathCosts(int startVertex, std::unordered_map<graph::Vertex, graph::Vertex>& path) {
	path.clear();

	vector<int> costs(NumVertices_);
	for_each(costs.begin(), costs.end(), [](auto& elem) { elem = Inf; });

	costs[startVertex] = 0;
	int count = 0;

	while (true) {
		bool hasUpdated = false;
		for (const auto& v_info : edges_) {
			const auto prev = v_info.first;
			const auto edges = v_info.second;

			for (const auto& e : edges) {
				const auto& cur = e.to;
				const bool updates = shouldUpdate(costs[prev], costs[cur], e.cost);
				if (updates) {
					costs[cur] = costs[prev] + e.cost;
					path[cur] = prev;
				}
				hasUpdated |= updates;
			}
		}

		if (!hasUpdated)
			break;

		++count;
		if (count >= NumVertices_)
			throw exception("Negative edge detected");
	}
	return costs;
}
