#include "graph.hpp"

using namespace std;
using namespace graph;

const Graph graph::TestData{
		{0, {
				{1, 2},
				{2, 5},
			}
		},
		{1, {
				{0, 2},
				{2, 4},
				{3, 6},
				{4, 10}
			}

		},
		{2, {
				{0, 5},
				{1, 4},
				{3, 2}
			}
		},
		{3, {
				{1, 6},
				{2, 2},
				{5, 1}
			}
		},
		{4, {
				{1, 10},
				{5, 3},
				{6, 5}
			}
		},
		{5, {
				{3, 1},
				{4, 3},
				{6, 9}
			}
		},
		{6, {
				{4, 5},
				{5, 9}
			}
		}
};

vector<Vertex> graph::RestorePath(Vertex start, Vertex end, const unordered_map<Vertex, Vertex>& path) {
	vector<Vertex> res;
	Vertex v = end;
	while (v != start) {
		res.emplace_back(v);
		v = path.at(v);
	}
	res.emplace_back(v);

	reverse(res.begin(), res.end());
	return res;
}

