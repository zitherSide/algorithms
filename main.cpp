#include <iterator>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <ranges>
#include "graph.hpp"
#include "bellman_ford.hpp"
#include "dijkstra.hpp"
#include "floyd_warshall.hpp"
#include "prim.hpp"
#include "union_find.hpp"
#include "kruskal.hpp"
#include "road_blocks.hpp"
#include "layout.hpp"
#include "bribe_the_prisoners.hpp"

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

void layout() {
	const vector<LayoutConstraint> Constraints{
		{1, 3, 10}, {2, 4, 20}, {2, 3, -3}
	};
	const auto MaxV = getMaxVertex(Constraints);
	const auto Res = calcLongestLayout(MaxV+1, Constraints);
}

void MinimumProduct() {
	using Value = long long int;
	{
		//resultoverflow test
		constexpr Value min = -100000;
		constexpr Value max = 100000;
		constexpr Value res = max * min;
		static_assert(res <= numeric_limits<Value>::max());
		static_assert(res >= numeric_limits<Value>::min());
		static_assert(min * max < min);
		static_assert(max * max > max);
		cout << res << endl;
	}

	vector<Value> v1{ 1, 2, 3, 4, 5 };
	vector<Value> v2{ 1, 0, 1, 0, 1 };
	ranges::sort(v1);
	ranges::sort(v2, ranges::greater());

	//copy(v1.begin(), v1.end(), ostream_iterator<Value>(cout, ", "));
	//copy(v2.begin(), v2.end(), ostream_iterator<Value>(cout, ", "));

	Value res = 0;
	for (auto i = 0; i < v1.size(); ++i) res += v1.at(i) * v2.at(i);

	cout << res << endl;;
}

void SolveCrazyRows() {
	//1 <= N <= 40
	using Row = vector<int>;
	using Matrix = vector<Row>;

	const Matrix Input = {
		{1, 1, 1, 0},
		{1, 1, 0, 0},
		{1, 1, 0, 0},
		{1, 0, 0, 0}
	};

	constexpr int Undefined = -1;

	vector<int> position(Input.size());
	transform(Input.cbegin(), Input.cend(), position.begin(), [](const Row& row) {
		int index = Undefined;
		for (int i = 0; i < row.size(); ++i) {
			index = (row.at(i) == 1) ? i : index;
		}
		return index;
		});
	//copy(position.begin(), position.end(), ostream_iterator<int>(cout, ", "));

	size_t res = 0;
	for (size_t i = 0; i < position.size(); ++i) {
		size_t swapTarget = Undefined;
		for (size_t j = i; j < position.size(); ++j) {
			if (position[j] <= i) {
				swapTarget = j;
				break;
			}
		}

		for (size_t j = swapTarget; j > i; --j) {
			swap(position[j], position[j - 1]);
			++res;
		}
	}
	cout << res << endl;
}

int main() {
	cout << "Cost: " << CalcMinCost(20, { 3, 6, 14 }) << endl;

	return 0;
}