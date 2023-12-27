#include <unordered_map>
#include <algorithm>
#include "bribe_the_prisoners.hpp"

using namespace std;

namespace {
	vector<int> createWithSentinel(const vector<int>& org, int sentinel) {
		vector<int> ret = org;
		ret.insert(ret.begin(), 0);
		ret.emplace_back(sentinel);
		return ret;
	}
}

Cost CalcMinCost(int numPrisoners, const vector<int> Releases) {
	//1 <= N <=10000
	// 1 <= Q <= 100
	constexpr int MaxNum = 10000;
	constexpr int MaxRelease = 100;
	constexpr Cost MaxCost = MaxNum * MaxRelease;
	static_assert(MaxCost > MaxNum);

	const vector<int> ReleaseWS = createWithSentinel(Releases, numPrisoners+1);

	unordered_map<int, unordered_map<int, Cost>> dp;
	for (int i = 0; i < ReleaseWS.size() - 1; ++i)
		dp[i][i + 1] = 0;

	for (int span = 2; span < ReleaseWS.size(); ++span) {
		for (int start = 0; start < ReleaseWS.size() - span; ++start) {
			const int End = start + span;
			dp[start][End] = 1000000;
			for (int k = start + 1; k < End; ++k) {
				dp[start][End] = min(dp.at(start).at(k) + dp.at(k).at(End), dp[start][End]);
			}
			dp[start][End] += ReleaseWS.at(End) - ReleaseWS.at(start) - 2;
		}
	}

	return dp[0][ReleaseWS.size() - 1];
}

