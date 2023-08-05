module Prim(
    prim
) where

import Graph
import Data.List (delete, minimumBy)
import Data.Set (toList, fromList)
import Data.Function (on)

chooseMinEdge :: [Vertex] -> [TupleEdge] -> TupleEdge
chooseMinEdge visiteds edges = minimumBy (compare `on` thd) [
    e | e@(u, v, weight) <- edges, bridges u v
    ]
    where
        bridges :: Vertex -> Vertex -> Bool
        bridges u v = (u `elem` visiteds && v `notElem` visiteds) || (u `notElem` visiteds && v `elem` visiteds)

thd ::  (a, b, c) -> c
thd (_, _, x) = x

prim :: TupleEdgeGraph -> TupleEdgeGraph
prim [] = []
prim allEdges = prim' [0] allEdges
    where
        prim' :: [Vertex] -> TupleEdgeGraph -> TupleEdgeGraph
        prim' _ [] = []
        prim' visiteds edges'
            | length visiteds == numVertices = []
            | otherwise = minEdge: prim' (newVertex: visiteds) (delete minEdge edges')
            where
                numVertices = length $ allVertices allEdges
                minEdge@(u, v, _) = chooseMinEdge visiteds edges'
                newVertex = if u `elem` visiteds then v else u

allVertices :: TupleEdgeGraph -> [Vertex]
allVertices graph = Data.Set.toList $ Data.Set.fromList $ extractVertices graph
    where
        extractVertices :: TupleEdgeGraph -> [Vertex]
        extractVertices [] = []
        extractVertices ((u, v, _): edges) = u : v : allVertices edges

-- ghci> a = [1, 2]
-- ghci> b = 1: a
-- ghci> b
-- [1,1,2]

-- ghci> minimum [1, 2, 3]
-- 1

-- ghci> a = [1, 2, 3, 4, 5]
-- ghci> b = [x | x <- a, even x, x < 4]
-- ghci> b
-- [2]

-- ghci> import Data.List
-- ghci> a
-- [1,2,3]
-- ghci> b = delete 2 a
-- ghci> b
-- [1,3]

-- ghci> minimum [(1, 0, 10), (0, 2, 5)]
-- (0,2,5)