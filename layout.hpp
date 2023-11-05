#pragma once

#include <vector>
#include "graph.hpp"

struct LayoutConstraint {
	graph::Vertex from;
	graph::Vertex to;
	graph::Weight constraint;
	LayoutConstraint() = default;
	LayoutConstraint(graph::Vertex f, graph::Vertex t, graph::Weight c) : from(f), to(t), constraint(c) {}
};

graph::Weight calcLongestLayout(graph::Vertex numVertices, const std::vector<LayoutConstraint>& constraints);
graph::Vertex getMaxVertex(const std::vector<LayoutConstraint>& constraints);