#include <limits>
#include <algorithm>
#include <iterator>
#include <utility>
#include <ranges>
#include <iostream>
#include <queue>
#include "dijkstra.hpp"

using namespace std;
using namespace graph;

template<class Container, class Range>
Container ToContainer(const Range&& r) {
	return { r.begin(), r.end() };
}

unordered_map<Vertex, Weight> Dijkstra::solve(Vertex start) {
	constexpr Weight Inf = std::numeric_limits<Weight>::max();

	const auto Vertices = graph_ | views::keys;

	const auto costsRange = Vertices | views::transform([&start](const auto v) { return make_pair(v, v == start ? 0 : Inf); });
	unordered_map<Vertex, Weight> costs{ costsRange.begin(), costsRange.end() };

	const auto hasExpandes = Vertices | views::transform([](const auto v) { return make_pair(v, false); });
	unordered_map<Vertex, bool> expandeds{ hasExpandes.begin(), hasExpandes.end() };

	while (true) {
		auto candidates = expandeds
			| views::filter([](const auto v) {return !v.second; })
			| views::keys
			| views::transform([&costs](const auto v) {return make_pair(v, costs[v]); });

		if (candidates.empty()) {
			break;
		}
		auto currentVertex = ranges::min(candidates, [](const auto& lhs, const auto& rhs) {return lhs.second < rhs.second; }).first;

		auto edges = graph_.at(currentVertex);
		
		for (const auto& e : edges) {
			costs[e.to] = std::min(costs[e.to], costs[currentVertex] + e.cost);
		}
		expandeds[currentVertex] = true;
	}
	return costs;
}

unordered_map<Vertex, Weight> Dijkstra::solve2(Vertex start) {
	constexpr Weight Inf = std::numeric_limits<Weight>::max();

	const auto Vertices = graph_ | views::keys;

	const auto costsRange = Vertices | views::transform([&start](const auto v) { return make_pair(v, v == start ? 0 : Inf); });
	unordered_map<Vertex, Weight> costs{ costsRange.begin(), costsRange.end() };


	using VertexCost = pair<Vertex, Weight>;
	priority_queue<VertexCost, vector<VertexCost>, greater<VertexCost>> visiteds;
	visiteds.emplace(VertexCost(0, start));

	while (true) {

		if (visiteds.empty())
			break;

		auto currentVertex = visiteds.top().second;
		visiteds.pop();
		const auto edges = graph_.at(currentVertex);


		for (const auto& e : edges) {
			if (costs[currentVertex] + e.cost < costs[e.to]) {
				costs[e.to] = std::min(costs[e.to], costs[currentVertex] + e.cost);
				visiteds.emplace(VertexCost(costs[e.to], e.to));
			}
		}
	}
	return costs;
}

unordered_map<Vertex, Weight> Dijkstra::solve2(Vertex start, std::unordered_map<Vertex, Vertex>& path) {
	constexpr Weight Inf = std::numeric_limits<Weight>::max();
	path.clear();

	const auto Vertices = graph_ | views::keys;

	const auto costsRange = Vertices | views::transform([&start](const auto v) { return make_pair(v, v == start ? 0 : Inf); });
	unordered_map<Vertex, Weight> costs{ costsRange.begin(), costsRange.end() };


	using VertexCost = pair<Vertex, Weight>;
	priority_queue<VertexCost, vector<VertexCost>, greater<VertexCost>> visiteds;
	visiteds.emplace(VertexCost(0, start));

	while (true) {

		if (visiteds.empty())
			break;

		auto currentVertex = visiteds.top().second;
		visiteds.pop();
		const auto edges = graph_.at(currentVertex);


		for (const auto& e : edges) {
			if (costs[currentVertex] + e.cost < costs[e.to]) {
				if (costs[currentVertex] + e.cost < costs[e.to]) {
					costs[e.to] = costs[currentVertex] + e.cost;
					path[e.to] = currentVertex;
				}
				visiteds.emplace(VertexCost(costs[e.to], e.to));
			}
		}
	}
	return costs;
}