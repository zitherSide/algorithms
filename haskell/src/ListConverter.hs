module ListConverter(
    list2array
) where

import Data.Array
import Data.List (minimumBy, maximumBy, groupBy, sortBy)
import Data.Function
import Debug.Trace
import Data.Function (on)

groupByFirst :: Eq a => Ord a => [(a, b, c)] -> [[(a, b, c)]]
groupByFirst input = groupBy isSameFrom $ sortBy (compare `on` first) input
    where
        isSameFrom :: Eq a => (a, b, c) -> (a, b, c) -> Bool
        isSameFrom (from1, _, _) (from2, _, _) = from1 == from2

first :: (a, b, c) -> a
first (x, _, _) = x

list2array :: [(Int, Int, Int)] -> Array Int [(Int, Int)]
list2array input = array (minId, maxId) grouped
    where
        minId = first $ minimumBy (compare `on` first) input
        maxId = first $ maximumBy (compare `on` first) input

        grouped = makeGroup input

makeGroup :: [(Int, Int, Int)] -> [(Int, [(Int, Int)])]
makeGroup input = [(makeKey list, stripFirst list) | list <- grouplist]
    where
        grouplist :: [[(Int, Int, Int)]]
        -- grouplist = trace ("group list: " ++ show (groupByFirst input)) groupByFirst input
        grouplist = groupByFirst input
        stripFirst :: [(Int, Int, Int)] -> [(Int, Int)]
        stripFirst tuple = map (\(_, v1, v2) -> (v1, v2)) tuple
        makeKey :: [(Int, Int, Int)] -> Int
        makeKey (x: _) = first x
