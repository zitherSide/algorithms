#include <iterator>
#include <iostream>
#include <algorithm>
#include "graph.hpp"
#include "bellman_ford.hpp"
#include "dijkstra.hpp"
#include "floyd_warshall.hpp"
#include "prim.hpp"
#include "union_find.hpp"
#include "kruskal.hpp"
#include "road_blocks.hpp"

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

void kruskal() {
	Kruskal solver(TestData);
	const auto res = solver.Solve();
}
int main() {
	RoadBlocks solver(TestData);
	solver.calcSecondShortest(0, 6);
	return 0;
}