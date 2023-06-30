#pragma once

#include <vector>
#include <limits>
#include "graph.hpp"

class BellmanFord {
private:
	static constexpr int Inf = std::numeric_limits<int>::max();

	graph::Graph edges_;
	const int NumVertices_;

public:
	BellmanFord(int numVertices, const graph::Graph& edges)
		:NumVertices_(numVertices), edges_(edges){}
	std::vector<int> calcShortestPathCosts(int startVertex);

private:
	bool shouldUpdate(int prevCost, int currentCost, int newCost){
		const bool isReady = prevCost < Inf;
		const bool isCheaper = prevCost + newCost < currentCost;
		return isReady && isCheaper;
	}

};