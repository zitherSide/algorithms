module Dijkstra
    (
        dijkstra
    ) where

import Graph
import Data.Map (Map, fromList, singleton, size, toList, lookup, insert, filter, filterWithKey)
import Data.Set (Set, size, singleton, insert, empty, member)
import Data.Function (on)
import Data.List (minimumBy)
import Data.Maybe (fromJust)
import Debug.Trace

dijkstra :: MapGraph -> Vertex -> Map Vertex Weight
dijkstra graph start = go (Data.Map.singleton start 0) (Data.Set.empty)
    where
        go :: Map Vertex Weight -> Set Vertex -> Map Vertex Weight
        go distances visiteds
            | Data.Set.size visiteds == Data.Map.size graph = distances
            | otherwise =
                let unvisiteds = Data.Map.filterWithKey (\k _ -> not (Data.Set.member k visiteds)) distances
                    comp = compare `on` snd 
                    currentVtx = fst $ minimumBy comp $ Data.Map.toList $ unvisiteds
                    _ = trace("currentVtx: " ++ show currentVtx)
                    currentCost = fromJust $ Data.Map.lookup currentVtx distances
                    edges = maybe [] id $ Data.Map.lookup currentVtx graph
                    newDistances = Prelude.foldl (relaxNeighbors currentCost) distances edges
                    newVisiteds = Data.Set.insert currentVtx visiteds
                in go newDistances newVisiteds
                where
                    relaxNeighbors :: Weight -> Map Vertex Weight -> (Vertex, Weight) -> Map Vertex Weight
                    relaxNeighbors curCost prevCosts (to, cost) =
                        case Data.Map.lookup to prevCosts of
                            Just prevCost -> Data.Map.insert to (min prevCost (curCost + cost)) prevCosts
                            Nothing -> Data.Map.insert to (curCost + cost) prevCosts

-- on (+) snd (2,2) (0  ,2)

-- Curry化して関数として利用
-- f2 = on (+) snd
-- f2 (2, 2) (0, 2)

-- 2高演算子化
-- f2 = (+) `on` snd
-- f2 (1, 2) (1, 2)

-- letは前提条件を先に書き、inの後ろが評価対象、と捉えれば良い？
-- let x = 5 in x + 2
-- let x = 0 in x > 0

-- foldl
-- ghci> f acc x = ((fst acc), x * (snd acc))
-- ghci> f (1,1) 5
-- (1,5)
-- ghci> Prelude.foldl f (1,1) [1, 2, 3]
-- (1,6)

-- restrictKeys
-- ghci> f = Data.Map.restrictKeys m $ Data.Set.fromList [0, 1]
-- ghci> f
-- fromList [(1,0)]

-- maybe
-- ghci> id $ Just 1
-- Just 1
-- ghci> maybe 0 id $ Just 1      
-- 1

-- elem
-- ghci> elem 1 [1, 2]
-- True

-- Set.member
-- ghci> Data.Set.member 1 $ Data.Set.fromList [1, 2]
-- True

-- filterWithKey
-- ghci> f = Data.Map.filterWithKey (\k _ -> k > 1) m
-- ghci> f
-- fromList [(2,0)]
-- ghci> f = Data.Map.filterWithKey (\k _ -> not (Data.Set.member k pool)) m
-- ghci> f
-- fromList [(2,0)]