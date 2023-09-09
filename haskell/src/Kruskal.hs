module Kruskal(
    kruskal
) where

import Graph
import Data.List (sortBy)
import Data.Function (on)

thrd :: (a, b, c) -> c
thrd (_, _, x) = x

kruskal :: TupleEdgeGraph -> TupleEdgeGraph
kruskal edges = kruskal' [] $ sortBy (compare `on` thrd) edges

kruskal' :: TupleEdgeGraph -> TupleEdgeGraph -> TupleEdgeGraph
kruskal' mst [] = mst
kruskal' mst ((u, v, cost): tail)
    | not (createsCycle u v mst) = kruskal' ((u, v, cost): mst) tail
    | otherwise = kruskal' mst tail

createsCycle :: Vertex -> Vertex -> TupleEdgeGraph -> Bool
createsCycle u v mst = dfs [] u
    where
        dfs :: [Vertex] -> Vertex -> Bool
        dfs visited current
            | current == v = True
            | otherwise = any (dfs (current: visited)) next
                where
                    next = [v' | (u', v', _) <- mst, u' == current, v' `notElem` visited ]

            