#include <iterator>
#include <iostream>
#include <algorithm>
#include "bellman_ford.hpp"
#include "dijkstra.hpp"

using namespace std;
using namespace graph;

void solve_bellman_ford() {
	BellmanFord solver(7, TestData);
	const auto res = solver.calcShortestPathCosts(0);

	copy(res.cbegin(), res.cend(), ostream_iterator<int>(cout, ", "));
}

int main() {
	Dijkstra solver(TestData);
	solver.solve(0);
	return 0;
}