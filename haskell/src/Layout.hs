module Layout(
    calcLongestLayout
) where

import Graph
import Data.Array (Array, array, (//), (!), assocs)
import ListConverter
import Debug.Trace

calcLongestLayout :: Int -> [(Vertex, Vertex, Weight)] -> [(Vertex, Vertex, Weight)] -> Array Vertex Weight
calcLongestLayout numVertices intimacies detachments = bellmanford numVertices graph costs 0
    where
        -- graph = trace ("graph: " ++ show (makeGraph numVertices intimacies detachments)) makeGraph numVertices intimacies detachments
        graph = makeGraph numVertices intimacies detachments
        costs = array (0, numVertices) [(i, if i == 0 then 0 else infinity) | i <- [0..numVertices]]

bellmanford :: Int -> Graph -> Array Vertex Weight -> Int -> Array Vertex Weight
bellmanford numVertices graph costs loop 
    | loop > numVertices = array (0, numVertices) [(i, infinity) | i <- [0..numVertices]]
    | hasUpdated = bellmanford numVertices graph costs' $ loop + 1
    | not hasUpdated = costs'
    where
        costs' = foldl updateEdges costs $ assocs graph 
        updateEdges :: Array Vertex Weight -> (Vertex, [(Vertex, Weight)]) -> Array Vertex Weight
        updateEdges sum (from, edges) = foldl (updateEdge from) sum edges
        updateEdge :: Vertex -> Array Vertex Weight -> (Vertex, Weight) -> Array Vertex Weight
        updateEdge from sum (to, cost) =
            if new < old then sum // [(to, new)]
            else sum
            where
                old = sum ! to
                new = sum ! from + cost
        hasUpdated = costs' /= costs

makeGraph :: Int -> [(Vertex, Vertex, Weight)] -> [(Vertex, Vertex, Weight)] -> Graph
makeGraph numVertices intimacies detachments = list2array wholeList
    where
        dList = map (\(from, to, cost) -> (to, from, -cost)) detachments
        orderList = [(from+1, from, 0) | from <- [0..numVertices-2] ]
        wholeList = intimacies ++ dList ++ orderList