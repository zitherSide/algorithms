#include <vector>
#include <algorithm>

#include "millionair.hpp"

using namespace std;

double MillionairSolver::CalcProbability(const Price InitialMoney) {
	vector<vector<double>> dp(NumRound + 1);
	for (auto& v : dp) {
		v.resize(NumBetPattern);
	}
	
	for (auto& v : dp[0]) v = 0.0;	//残りラウンド0でクリア金額未達なら敗北
	dp[0][NumBetPattern - 1] = 1.0;	//残りラウンド0でクリア金額なら勝利

	for (int residue_round = 1; residue_round <= NumRound; ++residue_round) {
		for (size_t money = 0; money < NumBetPattern; ++money) {
			const size_t MaxBettable = min(NumBetPattern - money - 1, money);
			
			auto& current = dp[residue_round][money];
			current = 0;
			for (size_t i = 0; i <= MaxBettable; ++i) {
				const auto win = dp[residue_round - 1][money + i] * WinProbability;
				const auto loose = dp[residue_round - 1][money - i] * (1 - WinProbability);
				current = max(current, win + loose);
			}
		}
	}

	const size_t StartBet = InitialMoney / BetQuantum;
	return dp[NumRound][StartBet];
}
