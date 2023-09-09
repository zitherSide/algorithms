#pragma once
#include <algorithm>
#include <array>
#include <vector>

template<class T, size_t N>
class UnionFindTree {
	std::array<T, N> parents_;

public:
	UnionFindTree() {
		for (int i = 0; i < parents_.size(); ++i)
			parents_[i] = i;
	}

	T Root(const T& leaf) {
		if (parents_[leaf] == leaf) return leaf;
		else return Root(parents_[leaf]);
	}

	void Unite(const T& src, const T& dest) {
		if (IsSame(src, dest)) return;

		parents_[Root(src)] = Root(dest);
	}

	bool IsSame(const T& src, const T& dest) {
		return Root(src) == Root(dest);
	}
};

template<class T>
class DynamicUnionFindTree {
	std::vector<T> parents_;

public:
	DynamicUnionFindTree(const size_t size) {
		parents_.resize(size);
		for (int i = 0; i < parents_.size(); ++i)
			parents_[i] = i;
	}

	T Root(const T& leaf) {
		if (parents_[leaf] == leaf) return leaf;
		else return Root(parents_[leaf]);
	}

	void Unite(const T& src, const T& dest) {
		if (IsSame(src, dest)) return;

		parents_[Root(src)] = Root(dest);
	}

	bool IsSame(const T& src, const T& dest) {
		return Root(src) == Root(dest);
	}
};