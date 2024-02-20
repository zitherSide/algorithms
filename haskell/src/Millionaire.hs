module Millionaire (
    calcWinProbability
) where

import Data.Array (Array, array, (!), (//))
import Debug.Trace

type RoundProb = Array Int Double
type Dp = Array Int RoundProb

calcWinProbability :: Double -> Int -> Int -> Int -> Double
calcWinProbability winProb winMoney initialMoney numRounds = (dp ! numRounds) ! (initialQuantum)
    where
        numBidPattern :: Int
        numBidPattern = 2 ^ numRounds

        bidQuantum :: Double
        bidQuantum = fromIntegral winMoney / fromIntegral numBidPattern
        -- bidQuantum = trace ("BidQuantum: " ++ show bidQuantum') bidQuantum'
        
        iqd :: Double
        iqd = fromIntegral initialMoney / bidQuantum
        -- iqd = trace ("IQD: " ++ show iqd') iqd'

        initialQuantum :: Int
        -- initialQuantum' =  floor $ fromIntegral initialMoney / bidQuantum
        initialQuantum =  floor iqd
        -- initialQuantum = trace ("initialQuantum: " ++ show initialQuantum') initialQuantum'

        initDp = array (0,numRounds) [ (i, array (0, numBidPattern-1) [
                (j, if ((i == 0) && (j == numBidPattern-1)) then 1.0 else 0.0) | j <- [0..numBidPattern-1]
            ]) | i <- [0..numRounds]]
        dp = calcDp winProb numBidPattern initDp [1..numRounds] [0..(numBidPattern-1)]
        -- dp = trace ("dp: " ++ show dp') dp'

calcDp :: Double -> Int -> Dp -> [Int] -> [Int] -> Dp
calcDp winProb numBidPattern prevDp roundRange bidRange = dp
    where
        -- roundRange = trace ("roundRange: " ++ show roundRange') roundRange'
        -- bidRange = trace ("BidRange: " ++ show bidRange') bidRange'
        dp = foldl (calcRound winProb numBidPattern bidRange) prevDp roundRange

calcRound:: Double -> Int -> [Int] -> Dp -> Int -> Dp
calcRound winProb numBidPattern bidRange acc curRound = dp
    where
        -- curRound = trace ("CurRound: " ++ show curRound') curRound'
        newDp = foldl (calcBid winProb numBidPattern curRound) acc bidRange
        dp :: Dp
        dp = acc // [(curRound, newDp ! curRound)]

calcBid :: Double -> Int -> Int -> Dp -> Int -> Dp
calcBid winProb numBidPattern curRound acc bid = newDp
    where
        -- bid = trace ("bid: " ++ show bid') bid'
        newDp = acc // [(curRound, newRoundDp)]
        newRoundDp = (acc ! curRound) // [(bid, maxProb)]
        maxProb = maximum bidProbs
        prevRound = curRound - 1
        prevRoundPs :: RoundProb
        prevRoundPs = acc ! prevRound
        bidProbs = [(prevRoundPs ! (bid-i)) * (1-winProb) + (prevRoundPs ! (bid+i)) * winProb| i <- [0..maxBid]]
        maxBid = minimum [bid, numBidPattern - 1- bid]
        -- maxBid = trace ("maxBid: " ++ show maxBid') maxBid'

