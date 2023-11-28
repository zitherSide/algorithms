module CrazyRow (
    calcMinimumSteps,
    testData
) where

import Data.Matrix (Matrix, fromLists, toLists)
import Data.Array (Array, array, (!), (//), bounds)
import Data.Ix (inRange)
import Debug.Trace

testData :: Matrix Int
testData = fromLists [
    [1,1,1,0],
    [1,1,0,0],
    [1,1,0,0],
    [1,0,0,0]
    ]


calcMinimumSteps :: Matrix Int -> Maybe Int
calcMinimumSteps input = ans
    where 
        rankData = calcRankData input
        -- rankData = trace ("rankData: " ++ show (calcRankData input)) calcRankData input
        (_, ans) = foldl fixRow (rankData, Just 0) [0..numRows-1]
        (_, numRows) = bounds rankData


fixRow :: (Array Int Int, Maybe Int) -> Int -> (Array Int Int, Maybe Int)
fixRow (rankData, Nothing) _ = (rankData, Nothing)
fixRow (rankData, Just prevSteps) n = (newArr, newSteps)
    where
        target = findClosestCandidate rankData n
        (newArr, localSteps) = case target of
            Nothing -> (rankData, Nothing)
            Just x -> (arr, Just steps) where (arr, steps) = swapUp rankData n x
        newSteps = case localSteps of
            Nothing -> Nothing
            Just x -> Just $ x + prevSteps

calcRankData :: Matrix Int -> Array Int Int
calcRankData matrix = array range $ zip [0..lastIndex] posList
    where
        rows = toLists matrix
        posList = map findPos rows
        -- rows = trace ("rows: " ++ show (toLists matrix)) toLists matrix
        -- posList = trace ("posList: " ++ show( map findPos rows)) map findPos rows
        lastIndex = (length posList) - 1
        range = (0, lastIndex)



swapUp :: Array Int Int -> Int -> Int -> (Array Int Int, Int)
swapUp arr dest src 
    | dest < src = (swapped, src - dest)
    | otherwise = (arr, 0)
    where
        swapped = foldl swap arr (reverse [dest+1..src])
        swap :: Array Int Int -> Int -> Array Int Int
        swap sum target = sum // [(target - 1, sum ! target), (target, sum ! (target - 1))]

findPos :: [Int] -> Int
findPos list = go (reverse list) $ (length list) - 1
    where
        go [] _ = -1
        go (x:xs) index
            | x == 1 = index
            | otherwise = go xs index - 1

findClosestCandidate :: Array Int Int -> Int -> Maybe Int
findClosestCandidate ranks base = check ranks base base
    where
        check :: Array Int Int -> Int -> Int -> Maybe Int
        check ranks' limit index
            | not (inRange (bounds ranks') index) = Nothing
            | ranks' ! index <= limit = Just index
            | otherwise = check ranks' base $ index+1