#include <iterator>
#include <iostream>
#include <algorithm>
#include <numeric>
#include "graph.hpp"
#include "bellman_ford.hpp"
#include "dijkstra.hpp"
#include "floyd_warshall.hpp"
#include "prim.hpp"
#include "union_find.hpp"
#include "kruskal.hpp"
#include "road_blocks.hpp"
#include "layout.hpp"

using namespace std;
using namespace graph;

void solve_bellman_ford() {
	BellmanFord solver(7, TestData);
	const auto res = solver.calcShortestPathCosts(0);

	copy(res.cbegin(), res.cend(), ostream_iterator<int>(cout, ", "));
}

void solve_dijkstra() {
	Dijkstra solver(TestData);
	const auto res = solver.solve2(0);
}

void solve_floyd_warshall() {
	FloydWarshall solver(TestData);
	solver.solve();
}

void solve_and_find_path() {
	unordered_map<Vertex, Vertex> path;
	Dijkstra solver(TestData);
	const auto res = solver.solve2(0, path);
	const auto p = RestorePath(0, 6, path);
	copy(p.cbegin(), p.cend(), ostream_iterator<Vertex>(cout, ", "));
	cout << endl;

	BellmanFord solverB(7, TestData);
	solverB.calcShortestPathCosts(0, path);
	copy(p.cbegin(), p.cend(), ostream_iterator<Vertex>(cout, ", "));
}

void solve_prim() {
	Prim p(TestData);
	const auto res = p.solve();
	cout << res << endl;
}

void union_find_test() {
	UnionFindTree<int, 10> uf;
	cout << boolalpha << uf.IsSame(1, 0) << endl;
	uf.Unite(2, 6);
	uf.Unite(6, 3);
	cout << boolalpha << uf.IsSame(2, 3) << endl;
}

void kruskal_test() {
	Kruskal solver(TestData);
	const auto res = solver.Solve();
}

void road_block() {
	RoadBlocks solver(TestData);
	solver.calcSecondShortest(0, 6);
}

void conscription() {
	const NonDirectedGraph Intimacy{ {4, 3, 6831}, {1, 3, 4583}, {0, 0, 6592}, {0, 1, 3063}, {3, 3, 4975}, {1, 3, 2049}, {4, 2, 2104}, {2, 2, 781} };
	constexpr size_t NumFemale = 5;
	constexpr size_t NumMale = 5;
	constexpr int Cost = 10000;
	NonDirectedGraph intimacyGraph(Intimacy.size());
	transform(Intimacy.cbegin(), Intimacy.cend(), intimacyGraph.begin(), ([&](auto& e) { return BiEdge(e.from, e.to + NumMale, -e.cost); }));

	const auto mst = kruskal(intimacyGraph);
	const auto reduction = accumulate(mst.cbegin(), mst.cend(), 0, [](const auto sum, const auto& elem) -> int {
		return sum + elem.cost;
		});
	const auto cost = (NumFemale + NumMale) * Cost + reduction;
}

int main() {
	const vector<LayoutConstraint> Constraints{
		{1, 3, 10}, {2, 4, 20}, {2, 3, -3}
	};
	const auto MaxV = getMaxVertex(Constraints);
	const auto Res = calcLongestLayout(MaxV+1, Constraints);
	return 0;
}