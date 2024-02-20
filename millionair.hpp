#pragma once
#include <cassert>

class MillionairSolver {
public:
	using Round = int;
	using Price = double;

private:
	const Round NumRound;
	const Price ClearPrice;
	const size_t NumBetPattern;
	const Price BetQuantum;
	const double WinProbability;

	static constexpr Round MaxRound = 15;

public:
	MillionairSolver(Round numRound, Price clearPrice, double winProbability) :
		NumRound(numRound),
		ClearPrice(clearPrice),
		NumBetPattern(1 << NumRound),
		BetQuantum(ClearPrice / NumBetPattern),
		WinProbability(winProbability)
	{
		static_assert(1 << MaxRound > 0);
		assert(WinProbability >= 0.0);
		assert(WinProbability <= 1.0);
	}

	double CalcProbability(const Price InitialMoney);
};