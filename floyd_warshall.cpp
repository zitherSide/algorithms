#include <iostream>
#include <ranges>
#include "floyd_warshall.hpp"

using namespace std;
using namespace graph;

namespace {
	Weight GetCost(const unordered_map<Vertex, unordered_map<Vertex, Weight>>& costs, Vertex i, Vertex j) {
		if (costs.count(i) > 0 && costs.at(i).count(j) > 0)
			return costs.at(i).at(j);
		else
			return Inf;
	}

	unordered_map<Vertex, unordered_map<Vertex, Weight>> init(const Graph& g) {
		unordered_map<Vertex, unordered_map<Vertex, Weight>> res;
		for (const auto& Edges : g) {
			const auto From = Edges.first;
			for (const auto& E : Edges.second) {
				res[From][E.to] = E.cost;
			}
		}

		for (const auto v : g | views::keys) {
			res[v][v] = 0;
		}
		return res;
	}
}

unordered_map<Vertex, unordered_map<Vertex, Weight>> FloydWarshall::solve()
{
	unordered_map<Vertex, unordered_map<Vertex, Weight>> res = init(graph_);

	auto vertices = graph_ | views::keys;
	for (const auto MaxAvailableVertex : vertices) {
		for (const auto From : vertices) {
			for(const auto To: vertices){
				const auto PrevCost = GetCost(res, From, To);
				const auto PrevFirst = GetCost(res, From, MaxAvailableVertex);
				const auto PrevLast = GetCost(res, MaxAvailableVertex, To);
				res[From][To] = min(
					PrevCost,
					PrevFirst + PrevLast
				);
				cout << MaxAvailableVertex << From << To << endl;
			}
		}
	}
	return res;
}

