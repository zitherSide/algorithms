module BribePrisoners(
    calcMinBribe
) where

import Data.Array (Array, array, (!), bounds, (//))
type Cost = Int

inf :: Cost
inf = 100000

initDP :: Int -> Array Int (Array Int Cost)
initDP numReleaseCandidates =
    array (0, numReleaseCandidates-1) [
    (i, array (i+1, numReleaseCandidates-1)
        [
            (j, if j - i <= 1 then 0 else inf) |j <- [(i+1)..numReleaseCandidates-1]
        ]
    )
    | i <- [0..(numReleaseCandidates-1)]
    ]

calcMinBribe :: Int -> [Int] -> Cost
calcMinBribe numPrisoners releaseCandidates = (dp ! 0) ! (numRel-1)
    where
        initial = initDP numRel
        releaseCandidates' = (0: releaseCandidates)
        releaseCandidates'' = reverse (numPrisoners+1: reverse releaseCandidates')
        numRel = length releaseCandidates''
        dp = foldl (updateDP releaseCandidates'' (numRel-1)) initial [2..(numRel-1)]

updateDP :: [Int] -> Int -> Array Int (Array Int Cost) -> Int -> Array Int (Array Int Cost)
updateDP pos lastStart currentCost width = foldl (updateRow posArr width) currentCost [0..lastStart]
    where
        posArr = array (0, lastStart) $ zip [0..lastStart] pos

updateRow :: Array Int Int -> Int -> Array Int (Array Int Cost) -> Int -> Array Int (Array Int Cost)
updateRow pos width currentCost startIndex
    | endIndex > maxLen = currentCost
    | otherwise = currentCost // [
        (startIndex,
        (currentCost ! startIndex) // [(endIndex, newCost)])
        ]
    where
        endIndex = startIndex + width
        (_, maxLen) = bounds $ currentCost ! startIndex

        newCost = (minimum costList) + rightPos - leftPos - 2
        leftPos = pos ! startIndex
        rightPos = pos ! (startIndex + width)

        costList = [
            leftCost + rightCost | (k) <- [(startIndex + 1)..(endIndex-1)],
            let leftCost = (currentCost ! startIndex) ! k,
            let rightCost = (currentCost ! k) ! endIndex
            ]
